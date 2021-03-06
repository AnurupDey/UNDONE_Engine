/******************************************************************************
Project	:	UNDONE Engine
File	:   Behavior.h
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

#ifndef _UNDONE_BEHAVIOR_H_
#define _UNDONE_BEHAVIOR_H_


#include "Undone_Engine.h"

namespace UNDONE_ENGINE {


    /*-------------------------------------------------------------------------
    This interface must be implimented by all behavior scripts to be written
    for the UNDONE Engine.
    -------------------------------------------------------------------------*/
    class Behavior {
    public: 
        virtual void Load( ) = 0;
        virtual void UnLoad( ) = 0;
    
        UNDONE_API static unInput*        Input;
        UNDONE_API static unGraphics*     Graphics;
        UNDONE_API static unObjectBuffer* Objectbuffer;

        #define _GENDEC_DEF_BEHAVIOR_CPP_
        #include "GENERATE_FUNCTIONS.h"
        GENFUNCS_ONLY_FOR_COMPONENTS()

        
    };
}
#endif