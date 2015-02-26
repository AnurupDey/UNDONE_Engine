/******************************************************************************
File	:	_3DGraphic.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#ifndef __3DGRAPHIC_H_
#define __3DGRAPHIC_H_

#include "Component.h"			//_3DGraphic IS A Component
#include "GraphicalObject.h"	//the graphical Object header, the base class.
#include "WorldTransform.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "UNDONE_Engine_declr.h"

#include <glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

using namespace UNDONE_ENGINE;

/*-----------------------------------------------------------------------------
This struct represents data that is passed on to each 3d graphic on rendering.
-----------------------------------------------------------------------------*/
struct RenderParams {
	glm::mat4 View_x_Projection;
};

/*-----------------------------------------------------------------------------
This class represents a 3D graphical Object. Inherits most of its props
from the GraphicalObject. NOTE: All 3D graphics behave alike.
-----------------------------------------------------------------------------*/
struct UNDONE_API _3DGraphic : public GraphicalObject, public Component {
public:
	_3DGraphic();
	~_3DGraphic(){ Release(); }

	virtual void Release();
	virtual void Render(RenderParams& refRenderParams);
	virtual void Render ( ){ };

	virtual void OnInit();
	virtual void OnDestroy();

	DPointer<ShaderProgram>  GetShaderProgram() { return m_ppShaderProgram; }
	
	void SetShaderProgramToUse(DPointer<ShaderProgram> ppProgram);
	void SetParent(DPointer<GameObject> ppParent);

protected:
	DPointer<WorldTransform>	m_ppworldTransform;
	DPointer<ShaderProgram>		m_ppShaderProgram;
	DPointer<Mesh>				m_ppMesh;
	//Mesh, WorldTransfor, ShaderPrograms, etc	
};
#endif
///////////////////////////////////////////////////////////////////////////////