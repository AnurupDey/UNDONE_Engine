/******************************************************************************
Project	:	UNDONE Engine
File	:	Font.h
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#pragma once 

#ifndef _FONT_H_
#define _FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
std::string;
using std::vector;
using namespace std;

#include "texture.h"
#include "DPointer.h"

namespace UNDONE_ENGINE {

	class ShaderProgram;

	class Font {
	public:
		Font( );
		~Font( );

		bool LoadFont(string file, int pixelSize);
		bool LoadSystemFont(string name, int pxelSize);

		const int GetTextWidth(string Text, int pixelSize);

		void print(string sText, int x, int y, int iPXSize = -1);
		void printFormatted(int x, int y, int iPXSize, char* sText, ...);

		void releaseFont( );

		void SetShaderProgram(DPointer<ShaderProgram> shaderProgram);

	private:
		void createChar(int iIndex);

		Texture tCharTextures[256];
		int iAdvX[256], iAdvY[256];
		int iBearingX[256], iBearingY[256];
		int iCharWidth[256], iCharHeight[256];
		int iLoadedPixelSize, iNewLine;

		bool bLoaded;

		unsigned m_uiVAO;
		//For buffer data.
		unsigned m_uiVBO;
		vector<unsigned char> vboData;

		FT_Library	m_ftLib;
		FT_Face		m_ftFace;
		DPointer<ShaderProgram> m_ppShaderProgram;
	};
}

#endif