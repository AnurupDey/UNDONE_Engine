/******************************************************************************
Project	:	UNDONE Engine
File	:	UniformType.h
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

#ifndef _UNIFORMTYPE_H
#define _UNIFORMTYPE_H

namespace UNDONE_ENGINE {
	/*-------------------------------------------------------------------------
	Enumerates the various types of UNiform variables that can be passed to a 
	GLSL shader. Used as a medium of comunication between Graphical Materials
	and 3D Graphic objects.
	-------------------------------------------------------------------------*/
	enum UniformType {
		UNIFORMTYPE_WORLDTRANSFORMATIONMATRIX,
		UNIFORMTYPE_MODELVIEWPROJECTIONMATRIX,
		UNIFORMTYPE_GLTYPE,
		UNIFORMTYPE_UNKOWNDATA
	};
}

#endif