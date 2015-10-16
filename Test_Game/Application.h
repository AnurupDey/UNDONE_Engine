/*-----------------------------------------------------------------------------
File	:	Application.h
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

-----------------------------------------------------------------------------*/
#pragma once

#ifndef _APP_H_
#define _APP_H_

#include <vector>
#include <Undone_Engine.h>
using namespace UNDONE_ENGINE;
using namespace std;

class Application : public IApp{
public:
	Application();
	~Application(){ Release();}

	void Release();

	void LinkToEngine(UnFramework* pFrameWork);
	void LoadScene(UnObjectBuffer* pObjectBuffer);
	void Update();
protected:
	UnFramework*		m_pFrameWork;
	Camera*				m_pcam;
	vector<Command*>	m_Cmds;
	Dptr<unGameObject> BlockGroup;

	bool initialized;

	Yaw_PitchCommand* Yaw_Pitch ;
	Command* Exit ;
	Command* Move_Forward ;
	Command* Move_Backward ;
	Command* Enable_Mouse ;
	Command* Disable_Mouse ;
    Dptr<unGameObject>		cu;
    glm::vec3 forward;
};
#endif