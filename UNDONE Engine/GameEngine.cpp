/******************************************************************************
File	:	FrameWork.cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "FrameWork.h"
#include "GameObject.h"

namespace UNDONE_ENGINE {
	/*-----------------------------------------------------------------------------
	Default Constructor. Initialises variables to default values(mostly nulls).
	-----------------------------------------------------------------------------*/
	FrameWork::FrameWork(IApp* pApp) {
		m_pApplication = pApp;
		m_pSystemComponent = nullptr;
		m_pUserWindow = nullptr;
		m_pGraphicsEngine = nullptr;
		m_pObjectBuffer = nullptr;
		m_pInputHandeller = nullptr;
		m_pTimer = nullptr;

		m_running = false;
		m_active = true;
		m_renderingPaused = false;
		m_timerPaused = false;
		m_closing = false;
	}

	/*-----------------------------------------------------------------------------
	Summary: Destructor. Cleans up resources.
	-----------------------------------------------------------------------------*/
	void FrameWork::Release( ) {
		if (m_pUserWindow) {
			delete m_pUserWindow;
			m_pUserWindow = nullptr;
		}
		if (m_pGraphicsEngine) {
			delete m_pGraphicsEngine;
			m_pGraphicsEngine = nullptr;
		}
		if (m_pObjectBuffer) {
			m_pObjectBuffer->DeleteAll<GameObject>( );
			delete m_pObjectBuffer;
			m_pObjectBuffer = nullptr;
		}
		if (m_pInputHandeller) {
			delete m_pInputHandeller;
			m_pInputHandeller = nullptr;
		}
	}

	/*----------------------------------------------------------------------------
	Summary: Innitializes the Application. Creates the Window.
	Parameters:
	[IN]	title*		-Title of the window.
	[IN]	phInstance*	-pointer to the application instance.
	[IN]	width		-window Width.
	[IN]	height		-window hieght.
	[IN]	windowed	-window mode. true for windowed, false for fullscreen.
	Returns: true on success, false on falure.
	-----------------------------------------------------------------------------*/
	bool FrameWork::Initialise(char* title,
							   int width, int height,
							   bool windowed) {
		m_pSystemComponent = SystemComponent::GetInstance( );
		m_pUserWindow = new Window( );
		m_pGraphicsEngine = new GraphicsEngine( );
		m_pObjectBuffer = new DObjectBuffer( );
		m_pInputHandeller = new InputHandeller( );
		m_pTimer = new Timer( );

		//Initialize the subsystems..

		//the Window
		m_pUserWindow->Initialize(title, this, width, height, true);
		//the graphics engine
		if (!m_pGraphicsEngine->Initialize(m_pUserWindow->GetHandle( ), this, m_pObjectBuffer)) {
			return false;
		}
		//the Application
		m_pApplication->LoadScene(m_pObjectBuffer);

		if (!windowed) {
			//m_pGraphicsEngine->SetResolution(800, 600);
			ToggleFullscreen( );
		}
		//start the timer
		Pause(false, false);

		return true;	//mission complete!
	}

	/*-----------------------------------------------------------------------------
	Summary: Runs the application
	-----------------------------------------------------------------------------*/
	void FrameWork::Run( ) {
		m_running = true;
		while (m_running) {
			InputEvent InputEvent;
			while (m_pSystemComponent->GetInputEvent(&InputEvent)>0) {
				if (InputEvent.event.type==EVENT_QUIT) {
					//need to quit now...
					m_running = false;
					break;
				}
				//Handle other input
				m_pInputHandeller->HandleInput(InputEvent);
			}
			//Advance in game loop.
			if (m_pGraphicsEngine!=nullptr &&m_pTimer!=nullptr && m_active) {
				m_pTimer->Update( );
				m_pApplication->Update( );
				m_pGraphicsEngine->RenderScene( );
			}

		}
	}

	/*----------------------------------------------------------------------------
	Summary: Pauses or unpauses rendering and the timer.
	Parameters:
	[in] rendering - TRUE to pause rendering, FALSE to unpause rendering.
	[in] timer - TRUE to pause the timer, FALSE to unpause the timer.
	-----------------------------------------------------------------------------*/
	void FrameWork::Pause(bool rendering, bool timer) {
		m_renderingPauseCount += rendering ? 1 : -1;
		m_renderingPauseCount = (m_renderingPauseCount<0)?0:m_renderingPauseCount;

		m_timerPauseCount += timer ? 1 : -1;
		m_timerPauseCount = (m_timerPauseCount<0) ? 0 : m_timerPauseCount;

		m_renderingPaused = (m_renderingPauseCount>0);
		m_timerPaused = (m_timerPauseCount>0);

		if (m_timerPaused && m_pTimer!=NULL)		m_pTimer->Stop( );
		else if (!m_timerPaused && m_pTimer!=NULL)	m_pTimer->Start( );

	}

	/*-----------------------------------------------------------------------------
	Toggles between fulsreen and windowed modes.
	-----------------------------------------------------------------------------*/
	void FrameWork::ToggleFullscreen( ) {
		if (m_pGraphicsEngine==nullptr||m_pUserWindow==nullptr||!m_active) {
			return;
		}

		Pause(true, true);
		m_pUserWindow->m_fullscreenheight = m_pGraphicsEngine->GetDisplayMode( ).PelsHeight;
		m_pUserWindow->m_fullscreenwidth = m_pGraphicsEngine->GetDisplayMode( ).PelsWidth;
		m_pUserWindow->ToggleFullscreen( );
		m_pGraphicsEngine->ToggleFullscreen( );
		Pause(false, false);
	}

	/*-----------------------------------------------------------------------------
	Returns the input Context list from the Input handeller.
	------------------------------------------------------------------------------*/
	vector<InputContext>& FrameWork::GetInputContextListForEditing( ) {
		if (m_pInputHandeller) {
			return m_pInputHandeller->GetContextListForEditing( );
		} else {
			static vector<InputContext> fakelist;
			return fakelist;
		}
	}

	/*-----------------------------------------------------------------------------
	Summary: Window Response Functions
	-----------------------------------------------------------------------------*/
	void FrameWork::OnMinimized( ) {
		// Disable application on minimized
		m_active = false;
	}

	void FrameWork::OnResize(int newHieght, int newWidth,
							 int oldHieght, int oldWidth) {
		if (m_pGraphicsEngine)m_pGraphicsEngine->ResetScreen( );
		m_active = true;
	}

	/*-----------------------------------------------------------------------------
	Summary:	This function returns the current hieght of the render screen.
	-----------------------------------------------------------------------------*/
	const int FrameWork::GetScreenHieght( )const {
		if (!m_pUserWindow && !m_pGraphicsEngine) return 0;

		if (m_pUserWindow->m_windowed) {
			return m_pUserWindow->m_hieght;
		} else {
			return m_pGraphicsEngine->GetDisplayMode( ).PelsHeight;
		}
	}

	/*-----------------------------------------------------------------------------
	Summary: Returns the Width of the render screen.
	-----------------------------------------------------------------------------*/
	const int FrameWork::GetScreenWidth( ) const {
		if (!m_pUserWindow && !m_pGraphicsEngine) return 0;

		if (m_pUserWindow->m_windowed) {
			return m_pUserWindow->m_width;
		} else {
			return m_pGraphicsEngine->GetDisplayMode( ).PelsWidth;
		}
	}

	/*-----------------------------------------------------------------------------
	Summary: Gets the framerate
	-----------------------------------------------------------------------------*/
	const float FrameWork::GetFPS( ) const {
		if (m_pTimer!=nullptr) {
			return m_pTimer->GetFPS( );
		}
		return 0.0f;
	}

	/*-----------------------------------------------------------------------------
	Summary:	Retruns the time elapse since the last update;
	-----------------------------------------------------------------------------*/
	const float FrameWork::GetElapsedTime( ) const {
		if (m_pTimer==nullptr) return 0.0f;
		return m_pTimer->GetElapsedTime( );
	}
}
///////////////////////////////////////////////////////////////////////////////