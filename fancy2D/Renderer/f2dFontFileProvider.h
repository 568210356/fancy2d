////////////////////////////////////////////////////////////////////////////////
/// @file  f2dFontFileProvider.h
/// @brief fancy2D �����ṩ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyRefObj.h>
#include "../f2dRenderer.h"

#include <unordered_map>

#include <ft2build.h> 
#include FT_FREETYPE_H

////////////////////////////////////////////////////////////////////////////////
/// @brief �����ṩ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dFontFileProvider :
	public fcyRefObjImpl<f2dFontProvider>
{
	friend class f2dRendererImpl;
protected:
	// ���建������
	struct FontCacheInfo
	{
		// ��������
		fCharW Character;
		fcyRect UV;

		// ������
		FontCacheInfo* pPrev;
		FontCacheInfo* pNext;
	};
protected:
	f2dFontFileProvider();
	~f2dFontFileProvider();
};
