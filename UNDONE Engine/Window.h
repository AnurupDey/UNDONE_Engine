/******************************************************************************
File	:	Window.h
Author	:	Anurup Dey

				Copyright (C) 2015  Anurup Dey

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_
//inculudes
#include "SystemComponent.h"


namespace UNDONE_ENGINE {
	class IWindowUser;


	/*-----------------------------------------------------------------------------
	Summary: This is the header for the Windows window wrapper.
	-----------------------------------------------------------------------------*/
	class Window : IWindowEventHandeller {
	public:
		Window( );
		void			Initialize(const char* title,
								   IWindowUser* winUser,
								   int width, int height,
								   bool windowed = true);

		void			ToggleFullscreen( );

		WindowHandle	GetHandle( ) { return m_hWnd; }

		virtual void OnCreate( );
		virtual void OnPaint( );
		virtual void OnMinimized( );
		virtual void OnMaximized(int newWidth, int newHieght);
		virtual void OnResize(int newWidth, int newHieght);
		virtual void OnDestroy( );

		int			m_width;
		int			m_hieght;
		int			m_fullscreenwidth;
		int			m_fullscreenheight;
		bool		m_windowed;

	private:

		WindowHandle		m_hWnd;
		IWindowUser*		m_User;
		SystemComponent*	m_pSystem;



		WindowPlacementPtr	m_placement;
		char*				m_title;
	};
}
#endif
