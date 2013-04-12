#include "f2dRendererImpl.h"

#include "f2dEngineImpl.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

f2dSpriteImpl::f2dSpriteImpl(f2dTexture* pTex)
	: m_pTex(NULL), m_FlipType(F2DSPRITEFLIP_NONE), m_ZValue(0.f)
{
	m_pTex = pTex;
	m_pTex->AddRef();

	m_Org.b.x = (fFloat)pTex->GetWidth();
	m_Org.b.y = (fFloat)pTex->GetHeight();

	m_HotSpot = m_Org.GetCenter();

	recalcu();
}

f2dSpriteImpl::f2dSpriteImpl(f2dTexture* pTex, fcyRect SrcRect)
	: m_pTex(NULL), m_FlipType(F2DSPRITEFLIP_NONE), m_ZValue(0.f)
{
	m_pTex = pTex;
	m_pTex->AddRef();

	m_Org = SrcRect;

	m_HotSpot = m_Org.GetCenter();

	recalcu();
}

f2dSpriteImpl::f2dSpriteImpl(f2dTexture* pTex, fcyRect SrcRect, fcyVec2 HotSpot)
	: m_pTex(NULL), m_FlipType(F2DSPRITEFLIP_NONE), m_ZValue(0.f)
{
	m_pTex = pTex;
	m_pTex->AddRef();

	m_Org = SrcRect;

	m_HotSpot = HotSpot;

	recalcu();
}

f2dSpriteImpl::~f2dSpriteImpl()
{
	FCYSAFEKILL(m_pTex);
}

void f2dSpriteImpl::recalcu()
{
	fuInt tWidth = m_pTex->GetWidth();
	fuInt tHeight = m_pTex->GetHeight();

	// ����UV
	switch(m_FlipType)
	{
	case F2DSPRITEFLIP_H:  // ˮƽ
		m_UV.a.x = m_Org.b.x / tWidth;
		m_UV.a.y = m_Org.a.y / tHeight;
		m_UV.b.x = m_Org.a.x / tWidth;
		m_UV.b.y = m_Org.b.y / tHeight;
		break;
	case F2DSPRITEFLIP_V:  // ��ֱ
		m_UV.a.x = m_Org.a.x / tWidth;
		m_UV.a.y = m_Org.b.y / tHeight;
		m_UV.b.x = m_Org.b.x / tWidth;
		m_UV.b.y = m_Org.a.y / tHeight;
		break;
	case F2DSPRITEFLIP_HV: // ˮƽ&��ֱ
		m_UV.a.x = m_Org.b.x / tWidth;
		m_UV.a.y = m_Org.b.y / tHeight;
		m_UV.b.x = m_Org.a.x / tWidth;
		m_UV.b.y = m_Org.a.y / tHeight;
		break;
	default:
		m_UV.a.x = m_Org.a.x / tWidth;
		m_UV.a.y = m_Org.a.y / tHeight;
		m_UV.b.x = m_Org.b.x / tWidth;
		m_UV.b.y = m_Org.b.y / tHeight;
		break;
	}

	// ����ο�SpriteRect
	m_SpriteRect.a = m_Org.a - m_HotSpot;
	m_SpriteRect.b = m_Org.b - m_HotSpot;
}

f2dTexture* f2dSpriteImpl::GetTexture()
{
	return m_pTex;
}

fResult f2dSpriteImpl::SetTexture(f2dTexture* pTex)
{
	if(!pTex)
		return FCYERR_INVAILDPARAM;

	f2dTexture* tOrg = m_pTex;
	m_pTex = pTex;
	m_pTex->AddRef();
	FCYSAFEKILL(tOrg);

	recalcu();

	return FCYERR_OK;
}

fcyRect f2dSpriteImpl::GetTexRect()
{
	return m_Org;
}

fResult f2dSpriteImpl::SetTexRect(fcyRect Rect)
{
	m_Org = Rect;

	recalcu();

	return FCYERR_OK;
}

fcyVec2 f2dSpriteImpl::GetHotSpot()
{
	return m_HotSpot;
}

fResult f2dSpriteImpl::SetHotSpot(fcyVec2 Point)
{
	m_HotSpot = Point;

	recalcu();

	return FCYERR_OK;
}

F2DSPRITEFLIP f2dSpriteImpl::GetFlipType()
{
	return m_FlipType;
}

fResult f2dSpriteImpl::SetFlipType(F2DSPRITEFLIP Type)
{
	m_FlipType = Type;

	recalcu();

	return FCYERR_OK;
}

fFloat f2dSpriteImpl::GetZ()
{
	return m_ZValue;
}

fResult f2dSpriteImpl::SetZ(fFloat Value)
{
	m_ZValue = Value;

	return FCYERR_OK;
}

fcyColor f2dSpriteImpl::GetColor(fuInt Index)
{
	if(Index>=4)
		return 0;
	else
		return m_Color[Index];
}

fResult f2dSpriteImpl::SetColor(fcyColor Color)
{
	m_Color[0] = Color;
	m_Color[1] = Color;
	m_Color[2] = Color;
	m_Color[3] = Color;

	return FCYERR_OK;
}

fResult f2dSpriteImpl::SetColor(fuInt Index, fcyColor Color)
{
	if(Index>=4)
		return FCYERR_INVAILDPARAM;

	m_Color[Index] = Color;

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyRect& Dest)
{
	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ Dest.a.x, Dest.a.y, m_ZValue, m_Color[0].argb, m_UV.a.x, m_UV.a.y },
		{ Dest.b.x, Dest.a.y, m_ZValue, m_Color[1].argb, m_UV.b.x, m_UV.a.y },
		{ Dest.b.x, Dest.b.y, m_ZValue, m_Color[2].argb, m_UV.b.x, m_UV.b.y },
		{ Dest.a.x, Dest.b.y, m_ZValue, m_Color[3].argb, m_UV.a.x, m_UV.b.y }
	};

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyRect& Dest, const fcyRect& SubTex)
{
	float tUVWidth = m_UV.b.x - m_UV.a.x;
	float tUVHeight = m_UV.b.y - m_UV.a.y;

	fcyRect tUV(
		m_UV.a.x + tUVWidth * SubTex.a.x,
		m_UV.a.y + tUVHeight * SubTex.a.y,
		m_UV.a.x + tUVWidth * SubTex.b.x,
		m_UV.a.y + tUVHeight * SubTex.b.y
		);

	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ Dest.a.x, Dest.a.y, m_ZValue, m_Color[0].argb, tUV.a.x, tUV.a.y },
		{ Dest.b.x, Dest.a.y, m_ZValue, m_Color[1].argb, tUV.b.x, tUV.a.y },
		{ Dest.b.x, Dest.b.y, m_ZValue, m_Color[2].argb, tUV.b.x, tUV.b.y },
		{ Dest.a.x, Dest.b.y, m_ZValue, m_Color[3].argb, tUV.a.x, tUV.b.y }
	};

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyVec2& Center)
{
	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ m_SpriteRect.a.x + Center.x, m_SpriteRect.a.y + Center.y, m_ZValue, m_Color[0].argb, m_UV.a.x, m_UV.a.y },
		{ m_SpriteRect.b.x + Center.x, m_SpriteRect.a.y + Center.y, m_ZValue, m_Color[1].argb, m_UV.b.x, m_UV.a.y },
		{ m_SpriteRect.b.x + Center.x, m_SpriteRect.b.y + Center.y, m_ZValue, m_Color[2].argb, m_UV.b.x, m_UV.b.y },
		{ m_SpriteRect.a.x + Center.x, m_SpriteRect.b.y + Center.y, m_ZValue, m_Color[3].argb, m_UV.a.x, m_UV.b.y }
	};

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale)
{
	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ m_SpriteRect.a.x * Scale.x + Center.x, m_SpriteRect.a.y * Scale.y + Center.y, m_ZValue, m_Color[0].argb, m_UV.a.x, m_UV.a.y },
		{ m_SpriteRect.b.x * Scale.x + Center.x, m_SpriteRect.a.y * Scale.y + Center.y, m_ZValue, m_Color[1].argb, m_UV.b.x, m_UV.a.y },
		{ m_SpriteRect.b.x * Scale.x + Center.x, m_SpriteRect.b.y * Scale.y + Center.y, m_ZValue, m_Color[2].argb, m_UV.b.x, m_UV.b.y },
		{ m_SpriteRect.a.x * Scale.x + Center.x, m_SpriteRect.b.y * Scale.y + Center.y, m_ZValue, m_Color[3].argb, m_UV.a.x, m_UV.b.y }
	};

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, const fcyRect& SubTex)
{
	float tUVWidth = m_UV.b.x - m_UV.a.x;
	float tUVHeight = m_UV.b.y - m_UV.a.y;

	fcyRect tUV(
		m_UV.a.x + tUVWidth * SubTex.a.x,
		m_UV.a.y + tUVHeight * SubTex.a.y,
		m_UV.a.x + tUVWidth * SubTex.b.x,
		m_UV.a.y + tUVHeight * SubTex.b.y
		);

	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ m_SpriteRect.a.x * Scale.x + Center.x, m_SpriteRect.a.y * Scale.y + Center.y, m_ZValue, m_Color[0].argb, tUV.a.x, tUV.a.y },
		{ m_SpriteRect.b.x * Scale.x + Center.x, m_SpriteRect.a.y * Scale.y + Center.y, m_ZValue, m_Color[1].argb, tUV.b.x, tUV.a.y },
		{ m_SpriteRect.b.x * Scale.x + Center.x, m_SpriteRect.b.y * Scale.y + Center.y, m_ZValue, m_Color[2].argb, tUV.b.x, tUV.b.y },
		{ m_SpriteRect.a.x * Scale.x + Center.x, m_SpriteRect.b.y * Scale.y + Center.y, m_ZValue, m_Color[3].argb, tUV.a.x, tUV.b.y }
	};

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation)
{
	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ m_SpriteRect.a.x * Scale.x, m_SpriteRect.a.y * Scale.y, m_ZValue, m_Color[0].argb, m_UV.a.x, m_UV.a.y },
		{ m_SpriteRect.b.x * Scale.x, m_SpriteRect.a.y * Scale.y, m_ZValue, m_Color[1].argb, m_UV.b.x, m_UV.a.y },
		{ m_SpriteRect.b.x * Scale.x, m_SpriteRect.b.y * Scale.y, m_ZValue, m_Color[2].argb, m_UV.b.x, m_UV.b.y },
		{ m_SpriteRect.a.x * Scale.x, m_SpriteRect.b.y * Scale.y, m_ZValue, m_Color[3].argb, m_UV.a.x, m_UV.b.y }
	};

	float tSin = sin(Rotation);
	float tCos = cos(Rotation);

	fcyVec2* p;
	for(int i = 0; i<4; i++)
	{
		p = (fcyVec2*)&tVerts[i];
		p->RotationSC(tSin, tCos);
		(*p) += Center;
	}

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

fResult f2dSpriteImpl::Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation, const fcyRect& SubTex)
{
	float tUVWidth = m_UV.b.x - m_UV.a.x;
	float tUVHeight = m_UV.b.y - m_UV.a.y;

	fcyRect tUV(
		m_UV.a.x + tUVWidth * SubTex.a.x,
		m_UV.a.y + tUVHeight * SubTex.a.y,
		m_UV.a.x + tUVWidth * SubTex.b.x,
		m_UV.a.y + tUVHeight * SubTex.b.y
		);

	// ׼������
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ m_SpriteRect.a.x * Scale.x, m_SpriteRect.a.y * Scale.y, m_ZValue, m_Color[0].argb, tUV.a.x, tUV.a.y },
		{ m_SpriteRect.b.x * Scale.x, m_SpriteRect.a.y * Scale.y, m_ZValue, m_Color[1].argb, tUV.b.x, tUV.a.y },
		{ m_SpriteRect.b.x * Scale.x, m_SpriteRect.b.y * Scale.y, m_ZValue, m_Color[2].argb, tUV.b.x, tUV.b.y },
		{ m_SpriteRect.a.x * Scale.x, m_SpriteRect.b.y * Scale.y, m_ZValue, m_Color[3].argb, tUV.a.x, tUV.b.y }
	};

	float tSin = sin(Rotation);
	float tCos = cos(Rotation);

	fcyVec2* p;
	for(int i = 0; i<4; i++)
	{
		p = (fcyVec2*)&tVerts[i];
		p->RotationSC(tSin, tCos);
		(*p) += Center;
	}

	pGraph->DrawQuad(m_pTex, tVerts);

	return FCYERR_OK;
}

////////////////////////////////////////////////////////////////////////////////

f2dFontRendererImpl::f2dFontRendererImpl(f2dRenderDevice* pDev, fcyStream* pStream, fuInt FontWidth, fuInt FontHeight, fuInt FaceIndex)
	: m_pDev(pDev), m_pStream(pStream), 
	m_Cache(NULL), m_CacheTex(NULL), 
	m_UsedNode(NULL), m_FreeNode(NULL)
{
	m_ZValue = 0.f;
	m_FlipType = F2DSPRITEFLIP_NONE;

	// --- ��ʼ��freetype ---
	FT_Error tErr = FT_Init_FreeType( &m_FontLib );
	if(tErr)
		throw fcyException("f2dFontRendererImpl::f2dFontRendererImpl", "FT_Init_FreeType Failed.");

	// --- ׼���� ---
	pStream->SetPosition(FCYSEEKORIGIN_BEG, 0);
	memset(&m_Args, 0, sizeof(m_Args));
	memset(&m_Stream, 0, sizeof(m_Stream));
	m_Args.flags = FT_OPEN_STREAM;
	m_Args.stream = &m_Stream;
	m_Stream.size = (unsigned long)m_pStream->GetLength();
	m_Stream.descriptor.pointer = m_pStream;
	m_Stream.read = streamRead;
	m_Stream.close = streamClose;
	m_pStream->AddRef();

	// --- �������� ---
	tErr = FT_Open_Face(m_FontLib, &m_Args, FaceIndex, &m_Face);
	if(tErr)
	{
		FT_Done_FreeType(m_FontLib);

		FCYSAFEKILL(m_pStream);

		throw fcyException("f2dFontRendererImpl::f2dFontRendererImpl", "FT_New_Memory_Face Failed.");
	}

	// --- ���������С ---
	FT_Set_Pixel_Sizes(m_Face, FontWidth, FontHeight);

	// --- ���������� ---
	if(!makeCache(20,20))
	{
		FT_Done_Face(m_Face);
		FT_Done_FreeType(m_FontLib);

		FCYSAFEKILL(m_pStream);

		throw fcyException("f2dFontRendererImpl::f2dFontRendererImpl", "makeCache Failed.");
	}

	// --- �󶨼����� ---
	pDev->AttachListener(this);
}

f2dFontRendererImpl::~f2dFontRendererImpl()
{
	FT_Done_Face(m_Face);
	FT_Done_FreeType(m_FontLib);

	FCYSAFEDELARR(m_Cache);
	FCYSAFEKILL(m_CacheTex);

	FCYSAFEKILL(m_pStream);

	m_pDev->RemoveListener(this);
}

unsigned long f2dFontRendererImpl::streamRead(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count)
{
	f2dStream* pStream = (f2dStream*)stream->descriptor.pointer;
	
	pStream->Lock();

	fLen tRealReaded = 0;
	pStream->SetPosition(FCYSEEKORIGIN_BEG, offset);
	pStream->ReadBytes(buffer, count, &tRealReaded);

	pStream->Unlock();

	return (unsigned long)tRealReaded;
}

void f2dFontRendererImpl::streamClose(FT_Stream stream)
{
	// ������������������
}

void f2dFontRendererImpl::addUsedNode(TextureCache* p)
{
	// ���ӱ��ڵ�
	if(m_UsedNode)
	{
		p->pPrev = m_UsedNode->pPrev;
		p->pNext = m_UsedNode;
	}
	else
	{
		p->pPrev = p->pNext = p;
	}

	// ���뱾�ڵ�
	if(m_UsedNode)
	{
		m_UsedNode->pPrev->pNext = p;
		m_UsedNode->pPrev = p;
	}
	m_UsedNode = p;
}

void f2dFontRendererImpl::removeFreeNode(TextureCache* p)
{
	// ����Ƿ�Ϊ��ͷ
	if(p == m_FreeNode)
		m_FreeNode = p->pNext;

	// �Ƴ����������
	if(p->pPrev)
		p->pPrev->pNext = p->pNext;
	if(p->pNext)
		p->pNext->pPrev = p->pPrev;

	// ���ֵ
	p->pNext = p->pPrev = NULL;
}

void f2dFontRendererImpl::removeUsedNode(TextureCache* p)
{
	// �Ƿ����׽ڵ�
	if(p == m_UsedNode)
		if(p->pNext == p)
			m_UsedNode = NULL;
		else
			m_UsedNode = p->pNext;

	// �Ƴ����������
	p->pNext->pPrev = p->pPrev;
	p->pPrev->pNext = p->pNext;

	p->pPrev = p->pNext = NULL;
}

float f2dFontRendererImpl::widthSizeToPixel(int Size)
{
	float tXScale = m_Face->size->metrics.x_scale / 65536.f;
	return (Size / 64.f) * tXScale;
}

float f2dFontRendererImpl::heightSizeToPixel(int Size)
{
	float tYScale = m_Face->size->metrics.y_scale / 65536.f;
	return (Size / 64.f) * tYScale;
}

f2dFontRendererImpl::TextureCache* f2dFontRendererImpl::getChar(fCharW Char)
{
	// �����ֵ�����Ѱ��
	TextureCache* pCache = m_Dict[Char];

	// �ҵ��Ļ�ֱ�ӷ���
	if(pCache)
	{
		// �ҵ�UsedList�ж�Ӧ��λ�ã���ɾ���ڵ㣬�����Ƶ���λ
		removeUsedNode(pCache);
		addUsedNode(pCache);

		return pCache;
	}

	// �������Ƿ��п�λ��������
	if(m_FreeNode)
	{
		// �п�λ
		pCache = m_FreeNode;

		// ���б����Ƴ�
		removeFreeNode(pCache);

		// ��������
		renderCache(pCache, Char, false);

		// ��¼
		m_Dict[Char] = pCache;

		// ����MRU�б�
		addUsedNode(pCache);

		// ����
		return pCache;
	}

	// û�п�λ��
	{
		// ��UsedList�����ȡ��
		pCache = m_UsedNode->pPrev;

		// ��ն�Ӧ�Ļ�������
		m_Dict[pCache->fontChar] = NULL;

		// �Ƴ�
		removeUsedNode(pCache);

		// ����
		renderCache(pCache, Char, false);

		// ��¼
		m_Dict[Char] = pCache;

		// ����MRU�б�
		addUsedNode(pCache);

		// ����
		return pCache;
	}
}

bool f2dFontRendererImpl::makeCache(fuInt XCount, fuInt YCount)
{
	m_Dict.clear();
	FCYSAFEDELARR(m_Cache);
	FCYSAFEKILL(m_CacheTex);

	m_CacheXMax = XCount;
	m_CacheYMax = YCount;

	// ����������󳤿�
	{
		FT_BBox tBox = m_Face->bbox;
		
		// 2��������
		m_CacheCurWidth = (fuInt)widthSizeToPixel(tBox.xMax - tBox.xMin) + 2;
		m_CacheCurHeight = (fuInt)widthSizeToPixel(tBox.yMax - tBox.yMin) + 2;
	}

	// �����ı����������ı���
	fuInt tTexWidth = m_CacheCurWidth * m_CacheXMax > 2048 ? 2048 : m_CacheCurWidth * m_CacheXMax;
	fuInt tTexHeight = m_CacheCurHeight * m_CacheYMax > 2048 ? 2048 : m_CacheCurHeight * m_CacheYMax;

	m_CacheXMax = tTexWidth / m_CacheCurWidth;
	m_CacheYMax = tTexHeight / m_CacheCurHeight;

	if(m_CacheXMax * m_CacheYMax < 3)
		return false;

	// �������建����
	if(FCYFAILED(m_pDev->CreateDynamicTexture(m_CacheCurWidth * m_CacheXMax, m_CacheCurHeight * m_CacheYMax, (f2dTexture**)&m_CacheTex)))
		return false;
	// ��ջ�����
	{
		fuInt tPitch = 0;
		fData tData = NULL;
		if(FCYFAILED(m_CacheTex->Lock(NULL, true, &tPitch, &tData)))
			return false;

		for(fuInt i = 0;i<m_CacheTex->GetHeight(); i++)
		{
			fcyColor* pColor = (fcyColor*)tData;
			for(fuInt j = 0; j<m_CacheTex->GetWidth(); j++)
			{
				pColor[j].argb = 0x00000000;
			}
			tData += tPitch;
		}

		m_CacheTex->Unlock();
	}
	
	m_Cache = new TextureCache[ m_CacheXMax * m_CacheYMax ];

	// ���ӻ�����
	m_Cache[0].pPrev = NULL;
	m_Cache[0].pNext = &m_Cache[1];
	m_Cache[m_CacheXMax * m_CacheYMax - 1].pNext = NULL;
	m_Cache[m_CacheXMax * m_CacheYMax - 1].pPrev = &m_Cache[ m_CacheXMax * m_CacheYMax - 2 ];
	for(fuInt i = 1; i<m_CacheXMax * m_CacheYMax - 1; i++)
	{
		m_Cache[i].pPrev = &m_Cache[i - 1];
		m_Cache[i].pNext = &m_Cache[i + 1];
	}

	m_UsedNode = NULL;
	m_FreeNode = m_Cache;

	return true;
}

bool f2dFontRendererImpl::renderCache(TextureCache* pCache, fCharW Char, bool Discard)
{
	// �������ֵ����β۲���Ⱦ
	FT_Load_Char( m_Face, Char, FT_LOAD_RENDER );

	// ���ͼ��
	FT_Bitmap* tBitmap = &m_Face->glyph->bitmap;

	// д���Ӧ����
	pCache->fontChar = Char;
	pCache->fontWidth = tBitmap->width;
	pCache->fontHeight = tBitmap->rows;
	pCache->fontTop = m_Face->glyph->bitmap_top;
	pCache->fontLeft = m_Face->glyph->bitmap_left;
	pCache->fontAdvance.x = m_Face->glyph->advance.x / 64.f;
	pCache->fontAdvance.y = m_Face->glyph->advance.y / 64.f;
	
	// ��������Ӧλ��
	{
		// ��������
		int tIndex = (int)(((fLen)pCache - (fLen)m_Cache) / sizeof(TextureCache));
		int XIndex = tIndex % m_CacheXMax;
		int YIndex = tIndex / m_CacheXMax;

		// ������������
		fcyRect tLockRect( 
			(float)(XIndex * m_CacheCurWidth),
			(float)(YIndex * m_CacheCurHeight), 
			(float)((XIndex+1) * m_CacheCurWidth), 
			(float)((YIndex+1) * m_CacheCurHeight));

		// ����UV
		pCache->uv.a.x = tLockRect.a.x / m_CacheTex->GetWidth();
		pCache->uv.a.y = tLockRect.a.y / m_CacheTex->GetHeight();
		pCache->uv.b.x = (tLockRect.a.x + pCache->fontWidth) / m_CacheTex->GetWidth();
		pCache->uv.b.y = (tLockRect.a.y + pCache->fontHeight) / m_CacheTex->GetHeight();

		fuInt tPitch = 0;
		fData tData = NULL;
		fData tSrcData = tBitmap->buffer;
		if(FCYFAILED(m_CacheTex->Lock(&tLockRect, Discard, &tPitch, &tData)))
			return false;
		
		for(int i = 0;i <tBitmap->rows; i++)
		{
			fcyColor* pColor = (fcyColor*)tData;
			for(int j = 0; j < tBitmap->width; j++)
			{
				pColor[j].argb = 0x00000000;
				pColor[j].a = tSrcData[j];
			}
			tSrcData += tBitmap->pitch;
			tData += tPitch;
		}

		m_CacheTex->Unlock();
	}

	return true;
}

fBool f2dFontRendererImpl::parseAdvancedCommand(fcStrW Text, fuInt Count, fuInt& Pos, fCharW Cmd[])
{
	fCharW tChar;
	int i = 0;
	do
	{
		tChar = Text[Pos];
		Pos++;
		if(tChar == L':')
			return true;
		if(tChar == L']')
		{
			Pos--;
			return true;
		}
		else if(tChar == L'+' || tChar == L'-' || iswalpha(tChar))
		{
			if(i >= 1)
				return false;

			Cmd[i] = tChar;
			i++;
		}
		else
			return false;
	}
	while(Pos < Count);

	return false;
}

fBool f2dFontRendererImpl::parseAdvancedParam(fcStrW Text, fuInt Count, fuInt& Pos, AdvancedTextParam Param[], fuInt& ParamCount)
{
	fCharW tChar = 0;
	int i = 0;
	int tType = 0; // 0 δ���� 1 ���� 2 ����
	fCharW tBuffer[256] = { 0 };
	int tBufferPos = 0;

	Param[0].IntData = Param[1].IntData = 0;

	do
	{
		tChar = Text[Pos];
		Pos++;
		if(tChar == L']')
		{
			Pos--;
			break;
		}
		else if(tChar == L',')
		{
			if(i >= 2)
				return false;

			if(tType == 1)
			{
				Param[i].IntData = 0;
				if(tBufferPos > 0)
					swscanf_s(tBuffer, L"%x", &Param[i].IntData);
			}
			else
			{
				Param[i].FloatData = 0;
				if(tBufferPos > 0)
					Param[i].FloatData = (float)_wtof(tBuffer);
			}

			tType = 0;
			tBufferPos = 0;
			i++;
		}
		else if(tChar == L'#')
		{
			if(tType != 0)
				return false;

			tType = 1;
		}
		else
		{
			if(tType == 0)
				tType = 2;

			tBuffer[tBufferPos] = tChar;
			tBufferPos++;
		}
	}
	while(Pos < Count);

	if(tType != 0)
	{
		if(tType == 1)
		{
			Param[i].IntData = 0;
			if(tBufferPos > 0)
				swscanf_s(&tBuffer[0], L"%x", &Param[i].IntData);
		}
		else
		{
			Param[i].FloatData = 0;
			if(tBufferPos > 0)
				Param[i].FloatData = (float)_wtof(tBuffer);
		}
		i++;
	}

	ParamCount = i;

	return true;
}

fCharW f2dFontRendererImpl::parseAdvancedText(fcStrW Text, fuInt Count, fuInt& Pos, AdvanceTextFormat& Fmt)
{
	while(Pos < Count)
	{
		fCharW tRet = Text[Pos];
		Pos++;

		if(tRet == L'[')
		{
			if(Pos >= Count) // EOF
				return L'[';
			else if(Text[Pos] == L'[') // ת�� [[ -> [
			{
				Pos++;
				return L'[';
			}
			else
			{
				fCharW tCmd[4] = { 0, 0, 0, 0 };
				fInt tPos = Pos;
				AdvancedTextParam tParam[2];
				fuInt tParamCount = 0;

				// ����������������Ϊ1���ַ�
				if(!parseAdvancedCommand(Text, Count, Pos, tCmd))
				{
					// ʧ�ܣ���λ������
					Pos = tPos;
					return L'[';
				}

				// �������������2������
				if(!parseAdvancedParam(Text, Count, Pos, tParam, tParamCount))
				{
					// ʧ�ܣ���λ������
					Pos = tPos;
					return L'[';
				}

				// ����ĩβ�� ] 
				if(Pos >= Count || Text[Pos] != L']')
				{
					// ʧ�ܣ���Ϊ������
					Pos = tPos;
					return L'[';
				}
				else
					Pos++;  // ���� ] �ַ�

				// ��������
				bool tFailed = false;
				switch(tCmd[0])
				{
				case L'c':
					// ��ɫ
					switch(tParamCount)
					{
					case 1:
						Fmt.Verts[0].color = tParam[0].IntData;
						Fmt.Verts[1].color = tParam[0].IntData;
						Fmt.Verts[2].color = tParam[0].IntData;
						Fmt.Verts[3].color = tParam[0].IntData;
						break;
					case 2:
						{
							fuInt tIndex = (fuInt)tParam[0].FloatData;
							if(tIndex > 3)
								tFailed = true;
							Fmt.Verts[tIndex].color = tParam[1].IntData;
						}
						break;
					default:
						tFailed = true;
					}
					break;
				case L'f':
					// ��ת
					if(tParamCount == 1)
					{
						fuInt tConst = (fuInt)tParam[0].FloatData;
						if(tConst > 3)
							tFailed = true;
						Fmt.FlipType = (F2DSPRITEFLIP)tConst;
					}
					else
						tFailed = true;
					break;
				case L'b':
					// ��б
					if(tParamCount == 1)
						Fmt.Bias = tParam[0].FloatData;
					else
						tFailed = true;
					break;
				case L'o':
					// ƫ��
					if(tParamCount == 2)
						Fmt.Pos += fcyVec2(tParam[0].FloatData, tParam[1].FloatData);
					else
						tFailed = true;
					break;
				case L'j':
					// ����
					if(tParamCount == 1)
						Fmt.Pos.y += tParam[0].FloatData * Fmt.LineHeight;
					else
						tFailed = true;
					break;
				case L'n':
					// �ص�����
					if(tParamCount == 0)
						Fmt.Pos.x = Fmt.StartPos.x;
					else
						tFailed = true;
					break;
				case L's':
					// �ص���ͷ
					if(tParamCount == 0)
						Fmt.Pos = Fmt.StartPos;
					else
						tFailed = true;
					break;
				case L'+':
					// ��¼λ��
					if(tParamCount == 1)
					{
						fuInt tIndex = (fuInt)tParam[0].FloatData;
						if(Fmt.PosCache && tIndex < Fmt.CacheCount)
							Fmt.PosCache[tIndex] = Fmt.Pos;
						else
							tFailed = true;
					}
					else
						tFailed = true;
					break;
				case L'-':
					// ����λ��
					if(tParamCount == 1)
					{
						fuInt tIndex = (fuInt)tParam[0].FloatData;
						if(Fmt.PosCache && tIndex < Fmt.CacheCount)
							Fmt.Pos = Fmt.PosCache[tIndex];
						else
							tFailed = true;
					}
					else
						tFailed = true;
					break;
				default:
					tFailed = true;
				}
			}
		}
		else
			return tRet;
	}
	return L'\0';
}

void f2dFontRendererImpl::OnRenderDeviceLost()
{
	m_Dict.clear();
	
	// ���������ѻ��������
	m_Using.clear();
	m_Using.reserve(m_CacheXMax * m_CacheYMax + 1);

	TextureCache* pCache = m_UsedNode;
	do
	{
		if(pCache)
		{
			m_Using += pCache->fontChar;
			pCache = pCache->pNext;
		}
		else
			break;
	}
	while(pCache != m_UsedNode);
}

void f2dFontRendererImpl::OnRenderDeviceReset()
{
	makeCache(m_CacheXMax, m_CacheYMax);

	// ���»���
	Cache(m_Using.c_str());
	m_Using.clear();
	m_Using.reserve(0);
}

fuInt f2dFontRendererImpl::GetFaceCount()
{
	return m_Face->num_faces;
}

fFloat f2dFontRendererImpl::GetLineHeight()
{
	return m_Face->size->metrics.height / 64.f;
}

f2dTexture* f2dFontRendererImpl::GetCache()
{
	return m_CacheTex;
}

void f2dFontRendererImpl::Cache(fcStrW Text)
{
	fuInt tLen = wcslen(Text);
	for(fuInt i = 0; i<tLen; i++)
	{
		if(Text[i] != '\n')
			getChar(Text[i]);
	}
}

fFloat f2dFontRendererImpl::GetZ()
{
	return m_ZValue;
}

void f2dFontRendererImpl::SetZ(fFloat ZValue)
{
	m_ZValue = ZValue;
}

fcyColor f2dFontRendererImpl::GetColor(fuInt Index)
{
	if(Index>=4)
		return 0;
	else
		return m_BlendColor[Index];
}

void f2dFontRendererImpl::SetColor(const fcyColor& Color)
{
	m_BlendColor[0] = Color;
	m_BlendColor[1] = Color;
	m_BlendColor[2] = Color;
	m_BlendColor[3] = Color;
}

void f2dFontRendererImpl::SetColor(fuInt Index, const fcyColor& Color)
{
	if(Index < 4)
		m_BlendColor[Index] = Color;
}

F2DSPRITEFLIP f2dFontRendererImpl::GetFlipType()
{
	return m_FlipType;
}

void f2dFontRendererImpl::SetFlipType(F2DSPRITEFLIP Type)
{
	m_FlipType = Type;
}

fResult f2dFontRendererImpl::DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, const fcyVec2& StartPos)
{
	return DrawTextW(pGraph, Text, -1, StartPos, NULL);
}

fResult f2dFontRendererImpl::DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosOut)
{
	// --- ׼������ ---
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ 0.f, 0.f, m_ZValue, m_BlendColor[0].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[1].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[2].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[3].argb, 0.f, 0.f }
	};

	// --- ������Ҫ���Ƶ����� ---
	fuInt tCount = wcslen(Text);                         // �ַ�����
	if(Count != -1)
		tCount = tCount < Count ? tCount : Count;
	fcyVec2 tPos = StartPos;                             // �ʴ�λ��
	float tHeight = m_Face->size->metrics.height / 64.f; // �и�

	// --- ����ÿһ���ַ� ---
	for(fuInt i = 0; i<tCount; i++)
	{
		// ���д���
		if(Text[i] == '\n')
		{
			tPos.x = StartPos.x;
			tPos.y += tHeight;
			continue;
		}

		// ����Ƿ���Ҫflush
		if(pGraph && m_FreeNode==NULL && !m_Dict[Text[i]])
			pGraph->Flush();

		// ȡ������
		TextureCache* pCache = getChar(Text[i]);

		// ������ͼuv��Ϣ�����з�ת����
		switch (m_FlipType)
		{
		case F2DSPRITEFLIP_NONE:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_H:
			tVerts[1].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[2].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_V:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_HV:
			tVerts[2].u = pCache->uv.a.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[0].v = pCache->uv.b.y;
			tVerts[1].u = pCache->uv.a.x;
			tVerts[1].v = pCache->uv.b.y;
			break;
		default:
			return FCYERR_ILLEGAL;
		}

		// ����λ�þ���
		tVerts[0].x = tPos.x + pCache->fontLeft;
		tVerts[0].y = tPos.y - pCache->fontTop;
		tVerts[1].x = tPos.x + pCache->fontLeft + pCache->fontWidth;
		tVerts[1].y = tPos.y - pCache->fontTop;
		tVerts[2].x = tPos.x + pCache->fontLeft + pCache->fontWidth;
		tVerts[2].y = tPos.y - pCache->fontTop + pCache->fontHeight;
		tVerts[3].x = tPos.x + pCache->fontLeft;
		tVerts[3].y = tPos.y - pCache->fontTop + pCache->fontHeight;

		// ����
		tPos += pCache->fontAdvance;

		// ����
		if(pGraph)
			pGraph->DrawQuad(GetCache(), tVerts);
	}

	// �����µ�λ��
	if(PosOut)
		*PosOut = tPos;

	return FCYERR_OK;
}

fResult f2dFontRendererImpl::DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, fFloat Bias, const fcyVec2& StartPos, fcyVec2* PosOut)
{
	// --- ׼������ ---
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ 0.f, 0.f, m_ZValue, m_BlendColor[0].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[1].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[2].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[3].argb, 0.f, 0.f }
	};

	// --- ������Ʋ��� ---
	fuInt tCount = wcslen(Text);                         // ���ָ���
	if(Count != -1)
		tCount = tCount < Count ? tCount : Count;
	float tHeight = m_Face->size->metrics.height / 64.f; // �и�
	fcyVec2 tPos = StartPos;                             // �ʴ�λ��
	Bias = tan(Bias);                                    // ������б��

	// --- ����ÿһ���ַ� ---
	for(fuInt i = 0; i<tCount; i++)
	{
		// ���д���
		if(Text[i] == '\n')
		{
			tPos.x = StartPos.x;
			tPos.y += tHeight;
			continue;
		}

		// ����Ƿ���Ҫflush
		if(pGraph && m_FreeNode==NULL && !m_Dict[Text[i]])
			pGraph->Flush();

		// ȡ������
		TextureCache* pCache = getChar(Text[i]);

		// ������ͼuv��Ϣ�����з�ת����
		switch (m_FlipType)
		{
		case F2DSPRITEFLIP_NONE:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_H:
			tVerts[1].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[2].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_V:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_HV:
			tVerts[2].u = pCache->uv.a.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[0].v = pCache->uv.b.y;
			tVerts[1].u = pCache->uv.a.x;
			tVerts[1].v = pCache->uv.b.y;
			break;
		default:
			return FCYERR_ILLEGAL;
		}

		// ����λ�þ���
		float tBias = Bias * pCache->fontHeight;

		tVerts[0].x = tPos.x + pCache->fontLeft + tBias;
		tVerts[0].y = tPos.y - pCache->fontTop;
		tVerts[1].x = tPos.x + pCache->fontLeft + pCache->fontWidth + tBias;
		tVerts[1].y = tPos.y - pCache->fontTop;
		tVerts[2].x = tPos.x + pCache->fontLeft + pCache->fontWidth;
		tVerts[2].y = tPos.y - pCache->fontTop + pCache->fontHeight;
		tVerts[3].x = tPos.x + pCache->fontLeft;
		tVerts[3].y = tPos.y - pCache->fontTop + pCache->fontHeight;

		// ����
		tPos += pCache->fontAdvance;

		// ����
		if(pGraph)
			pGraph->DrawQuad(GetCache(), tVerts);
	}

	// �����µ�λ��
	if(PosOut)
		*PosOut = tPos;

	return FCYERR_OK;
}

fResult f2dFontRendererImpl::DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, const fcyRect& DestRect, fuInt* pCountRendered)
{
	return DrawTextInRect(pGraph, Text, -1, DestRect, pCountRendered);
}

fResult f2dFontRendererImpl::DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fuInt* pCountRendered)
{
	// --- ׼������ ---
	f2dGraphics2DVertex tVerts[4] = 
	{
		{ 0.f, 0.f, m_ZValue, m_BlendColor[0].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[1].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[2].argb, 0.f, 0.f },
		{ 0.f, 0.f, m_ZValue, m_BlendColor[3].argb, 0.f, 0.f }
	};

	// --- ������Ʋ��� ---
	fuInt tCount = wcslen(Text);                             // �ַ�����
	if(Count != -1)
		tCount = tCount < Count ? tCount : Count;
	float tLineHeight = m_Face->size->metrics.height / 64.f; // �и�
	fcyVec2 tPos(DestRect.a.x, DestRect.a.y + tLineHeight);  // �ʴ�λ��

	// --- ����ÿһ���ַ� ---
	if(pCountRendered)
		*pCountRendered = 0;
	
	fuInt i;
	for( i = 0; i<tCount; i++)
	{
		// ���д���
		if(Text[i] == '\n')
		{
			tPos.x = DestRect.a.x;
			tPos.y += tLineHeight;
			// ���Խ��
			if(tPos.y > DestRect.b.y)
				break;

			continue;
		}

		// ����Ƿ���Ҫflush
		if(pGraph && m_FreeNode==NULL && !m_Dict[Text[i]])
			pGraph->Flush();

		// ȡ������
		TextureCache* pCache = getChar(Text[i]);

		// ����Ƿ���Ҫ����
		fcyVec2 tPrePos = tPos + pCache->fontAdvance;
		while(tPrePos.x > DestRect.b.x)
		{
			// ����
			tPos.x = DestRect.a.x;
			tPos.y += tLineHeight;
			// ���Խ��
			if(tPos.y > DestRect.b.y)
				break;

			tPrePos = tPos + pCache->fontAdvance;
		}
		if(!DestRect.Contain(tPos))
			break;

		// ������ͼuv��Ϣ�����з�ת����
		switch (m_FlipType)
		{
		case F2DSPRITEFLIP_NONE:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_H:
			tVerts[1].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.b.y;
			tVerts[2].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_V:
			tVerts[0].u = pCache->uv.a.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[1].u = pCache->uv.b.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[2].u = pCache->uv.b.x;
			tVerts[1].v = pCache->uv.b.y;
			tVerts[3].u = pCache->uv.a.x;
			tVerts[0].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_HV:
			tVerts[2].u = pCache->uv.a.x;
			tVerts[2].v = pCache->uv.a.y;
			tVerts[3].u = pCache->uv.b.x;
			tVerts[3].v = pCache->uv.a.y;
			tVerts[0].u = pCache->uv.b.x;
			tVerts[0].v = pCache->uv.b.y;
			tVerts[1].u = pCache->uv.a.x;
			tVerts[1].v = pCache->uv.b.y;
			break;
		default:
			return FCYERR_ILLEGAL;
		}

		// ����λ�þ���
		tVerts[0].x = tPos.x + pCache->fontLeft;
		tVerts[0].y = tPos.y - pCache->fontTop;
		tVerts[1].x = tPos.x + pCache->fontLeft + pCache->fontWidth;
		tVerts[1].y = tPos.y - pCache->fontTop;
		tVerts[2].x = tPos.x + pCache->fontLeft + pCache->fontWidth;
		tVerts[2].y = tPos.y - pCache->fontTop + pCache->fontHeight;
		tVerts[3].x = tPos.x + pCache->fontLeft;
		tVerts[3].y = tPos.y - pCache->fontTop + pCache->fontHeight;

		// ����
		tPos = tPrePos;

		// ����
		if(pGraph)
			pGraph->DrawQuad(GetCache(), tVerts);
	}

	if(pCountRendered)
		*pCountRendered = i;

	return FCYERR_OK;
}

fResult f2dFontRendererImpl::DrawAdvancedText(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosCache, fuInt PosCacheCount)
{
	// --- ������Ʋ��� ---
	fuInt tCount = wcslen(Text);                             // �ַ�����
	if(Count != -1)
		tCount = tCount < Count ? tCount : Count;

	// --- ������ ---
	AdvanceTextFormat tFmt = 
	{
		m_FlipType,
		0,
		StartPos,
		StartPos,
		PosCache,
		PosCacheCount,
		m_Face->size->metrics.height / 64.f,
		{
			{ 0.f, 0.f, m_ZValue, m_BlendColor[0].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[1].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[2].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[3].argb, 0.f, 0.f }
		}
	};

	// --- ������񲢻������� ---
	fuInt i = 0;
	while(i < tCount)
	{
		// --- �����߼����ֲ��޸ķ�� ---
		wchar_t tChar = parseAdvancedText(Text, tCount, i, tFmt);
		if(tChar == 0)
			break;

		// --- �������� ---
		// ���д���
		if(tChar == '\n')
		{
			tFmt.Pos.x = StartPos.x;
			tFmt.Pos.y += tFmt.LineHeight;
			continue;
		}

		// ����Ƿ���Ҫflush
		if(pGraph && m_FreeNode==NULL && !m_Dict[tChar])
			pGraph->Flush();

		// ȡ������
		TextureCache* pCache = getChar(tChar);

		// ������ͼuv��Ϣ�����з�ת����
		switch (tFmt.FlipType)
		{
		case F2DSPRITEFLIP_NONE:
			tFmt.Verts[0].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.a.y;
			tFmt.Verts[1].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.a.y;
			tFmt.Verts[2].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.b.y;
			tFmt.Verts[3].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_H:
			tFmt.Verts[1].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.a.y;
			tFmt.Verts[0].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.a.y;
			tFmt.Verts[3].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.b.y;
			tFmt.Verts[2].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_V:
			tFmt.Verts[0].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.a.y;
			tFmt.Verts[1].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.a.y;
			tFmt.Verts[2].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.b.y;
			tFmt.Verts[3].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_HV:
			tFmt.Verts[2].u = pCache->uv.a.x;
			tFmt.Verts[2].v = pCache->uv.a.y;
			tFmt.Verts[3].u = pCache->uv.b.x;
			tFmt.Verts[3].v = pCache->uv.a.y;
			tFmt.Verts[0].u = pCache->uv.b.x;
			tFmt.Verts[0].v = pCache->uv.b.y;
			tFmt.Verts[1].u = pCache->uv.a.x;
			tFmt.Verts[1].v = pCache->uv.b.y;
			break;
		default:
			return FCYERR_ILLEGAL;
		}
		
		// ����λ�þ���
		float tBias = tFmt.Bias * pCache->fontHeight;

		tFmt.Verts[0].x = tFmt.Pos.x + pCache->fontLeft + tBias;
		tFmt.Verts[0].y = tFmt.Pos.y - pCache->fontTop;
		tFmt.Verts[1].x = tFmt.Pos.x + pCache->fontLeft + pCache->fontWidth + tBias;
		tFmt.Verts[1].y = tFmt.Pos.y - pCache->fontTop;
		tFmt.Verts[2].x = tFmt.Pos.x + pCache->fontLeft + pCache->fontWidth;
		tFmt.Verts[2].y = tFmt.Pos.y - pCache->fontTop + pCache->fontHeight;
		tFmt.Verts[3].x = tFmt.Pos.x + pCache->fontLeft;
		tFmt.Verts[3].y = tFmt.Pos.y - pCache->fontTop + pCache->fontHeight;

		// ����
		tFmt.Pos += pCache->fontAdvance;

		// ����
		if(pGraph)
			pGraph->DrawQuad(GetCache(), tFmt.Verts);
	}

	return FCYERR_OK;
}

fResult f2dFontRendererImpl::DrawAdvancedTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fcyVec2* PosCache, fuInt PosCacheCount, fuInt* pCountRendered)
{
	if(pCountRendered)
		*pCountRendered = 0;

	// --- ������Ʋ��� ---
	fuInt tCount = wcslen(Text);                             // �ַ�����
	if(Count != -1)
		tCount = tCount < Count ? tCount : Count;

	// --- ������ ---
	float tHeight = m_Face->size->metrics.height / 64.f;
	fcyVec2 tStartPos(DestRect.a.x, DestRect.a.y + tHeight);
	AdvanceTextFormat tFmt = 
	{
		m_FlipType,
		0,
		tStartPos,
		tStartPos,
		PosCache,
		PosCacheCount,
		tHeight,
		{
			{ 0.f, 0.f, m_ZValue, m_BlendColor[0].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[1].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[2].argb, 0.f, 0.f },
			{ 0.f, 0.f, m_ZValue, m_BlendColor[3].argb, 0.f, 0.f }
		}
	};

	// --- ������񲢻������� ---
	fuInt i = 0;
	while(i < tCount)
	{
		// --- �����߼����ֲ��޸ķ�� ---
		wchar_t tChar = parseAdvancedText(Text, tCount, i, tFmt);
		if(tChar == 0)
			break;

		// --- �������� ---
		// ���д���
		if(tChar == '\n')
		{
			tFmt.Pos.x = tFmt.StartPos.x;
			tFmt.Pos.y += tFmt.LineHeight;
			// ���Խ��
			if(tFmt.Pos.y > DestRect.b.y)
				break;

			continue;
		}

		// ����Ƿ���Ҫflush
		if(pGraph && m_FreeNode==NULL && !m_Dict[tChar])
			pGraph->Flush();

		// ȡ������
		TextureCache* pCache = getChar(tChar);

		// ����Ƿ���Ҫ����
		fcyVec2 tPrePos = tFmt.Pos + pCache->fontAdvance;
		while(tPrePos.x > DestRect.b.x)
		{
			// ����
			tFmt.Pos.x = tFmt.StartPos.x;
			tFmt.Pos.y += tFmt.LineHeight;
			// ���Խ��
			if(tFmt.Pos.y > DestRect.b.y)
				break;

			tPrePos = tFmt.Pos + pCache->fontAdvance;
		}
		if(!DestRect.Contain(tFmt.Pos))
			break;

		// ������ͼuv��Ϣ�����з�ת����
		switch (tFmt.FlipType)
		{
		case F2DSPRITEFLIP_NONE:
			tFmt.Verts[0].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.a.y;
			tFmt.Verts[1].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.a.y;
			tFmt.Verts[2].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.b.y;
			tFmt.Verts[3].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_H:
			tFmt.Verts[1].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.a.y;
			tFmt.Verts[0].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.a.y;
			tFmt.Verts[3].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.b.y;
			tFmt.Verts[2].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_V:
			tFmt.Verts[0].u = pCache->uv.a.x;
			tFmt.Verts[3].v = pCache->uv.a.y;
			tFmt.Verts[1].u = pCache->uv.b.x;
			tFmt.Verts[2].v = pCache->uv.a.y;
			tFmt.Verts[2].u = pCache->uv.b.x;
			tFmt.Verts[1].v = pCache->uv.b.y;
			tFmt.Verts[3].u = pCache->uv.a.x;
			tFmt.Verts[0].v = pCache->uv.b.y;
			break;
		case F2DSPRITEFLIP_HV:
			tFmt.Verts[2].u = pCache->uv.a.x;
			tFmt.Verts[2].v = pCache->uv.a.y;
			tFmt.Verts[3].u = pCache->uv.b.x;
			tFmt.Verts[3].v = pCache->uv.a.y;
			tFmt.Verts[0].u = pCache->uv.b.x;
			tFmt.Verts[0].v = pCache->uv.b.y;
			tFmt.Verts[1].u = pCache->uv.a.x;
			tFmt.Verts[1].v = pCache->uv.b.y;
			break;
		default:
			return FCYERR_ILLEGAL;
		}
		
		// ����λ�þ���
		float tBias = tFmt.Bias * pCache->fontHeight;

		tFmt.Verts[0].x = tFmt.Pos.x + pCache->fontLeft + tBias;
		tFmt.Verts[0].y = tFmt.Pos.y - pCache->fontTop;
		tFmt.Verts[1].x = tFmt.Pos.x + pCache->fontLeft + pCache->fontWidth + tBias;
		tFmt.Verts[1].y = tFmt.Pos.y - pCache->fontTop;
		tFmt.Verts[2].x = tFmt.Pos.x + pCache->fontLeft + pCache->fontWidth;
		tFmt.Verts[2].y = tFmt.Pos.y - pCache->fontTop + pCache->fontHeight;
		tFmt.Verts[3].x = tFmt.Pos.x + pCache->fontLeft;
		tFmt.Verts[3].y = tFmt.Pos.y - pCache->fontTop + pCache->fontHeight;

		// ����
		tFmt.Pos += pCache->fontAdvance;

		// ����
		if(pGraph)
			pGraph->DrawQuad(GetCache(), tFmt.Verts);
	}

	if(pCountRendered)
		*pCountRendered = i;

	return FCYERR_OK;
}

////////////////////////////////////////////////////////////////////////////////

f2dGeometryRendererImpl::f2dGeometryRendererImpl()
	: m_ZValue(0.f), m_PenSize(1.f)
{}

f2dGeometryRendererImpl::~f2dGeometryRendererImpl()
{}

fFloat f2dGeometryRendererImpl::GetZ()
{
	return m_ZValue;
}

void f2dGeometryRendererImpl::SetZ(fFloat ZValue)
{
	m_ZValue = ZValue;
}

fcyColor f2dGeometryRendererImpl::GetPenColor(fuInt Index)
{
	if(Index >= 3)
		return 0;
	else
		return m_PenColor[Index];
}

void f2dGeometryRendererImpl::SetPenColor(fuInt Index, const fcyColor& Color)
{
	if(Index < 3)
		m_PenColor[Index] = Color;
}

fFloat f2dGeometryRendererImpl::GetPenSize()
{
	return m_PenSize;
}

void f2dGeometryRendererImpl::SetPenSize(fFloat Size)
{
	m_PenSize = Size;
}

fResult f2dGeometryRendererImpl::DrawLine(f2dGraphics2D* pGraph, const fcyVec2& Begin, const fcyVec2& End)
{
	if(!pGraph || (Begin.x == End.x && Begin.y == End.y))
		return FCYERR_INVAILDPARAM;

	// ���㷽������
	fcyVec2 tDirect = End - Begin;
	tDirect.Normalize();
	tDirect.Rotation(-3.1415926535f/2.f);
	tDirect *= m_PenSize / 2;

	// ׼������
	f2dGraphics2DVertex tVerts[6] = 
	{
		{ Begin.x + tDirect.x, Begin.y + tDirect.y, m_ZValue, m_PenColor[0].argb, 0.f, 0.f },
		{ Begin.x            , Begin.y            , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		{ Begin.x - tDirect.x, Begin.y - tDirect.y, m_ZValue, m_PenColor[2].argb, 0.f, 0.f },
		{ End.x + tDirect.x  , End.y + tDirect.y  , m_ZValue, m_PenColor[0].argb, 0.f, 0.f },
		{ End.x              , End.y              , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		{ End.x - tDirect.x  , End.y - tDirect.y  , m_ZValue, m_PenColor[2].argb, 0.f, 0.f }
	};

	// ׼������
	static const fuShort tIndex[12] = 
	{
		0,3,1,
		3,4,1,
		1,4,5,
		1,5,2
	};

	// ����
	return pGraph->DrawRaw(NULL, 6, 12, tVerts, tIndex);
}

fResult f2dGeometryRendererImpl::DrawRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect)
{
	if(!pGraph)
		return FCYERR_INVAILDPARAM;

	// ������������
	fcyVec2 tDirect1(-0.7071067811f, -0.7071067811f);
	fcyVec2 tDirect2(0.7071067811f, -0.7071067811f);
	tDirect1 *= m_PenSize / 2;
	tDirect2 *= m_PenSize / 2;

	// ׼������
	f2dGraphics2DVertex tVerts[12] = 
	{
		{ Rect.a.x + tDirect1.x, Rect.a.y + tDirect1.y, m_ZValue, m_PenColor[0].argb, 0.f, 0.f },
		{ Rect.b.x + tDirect2.x, Rect.a.y + tDirect1.y, m_ZValue, m_PenColor[0].argb, 0.f, 0.f },
		{ Rect.b.x + tDirect2.x, Rect.b.y - tDirect1.y, m_ZValue, m_PenColor[0].argb, 0.f, 0.f },
		{ Rect.a.x + tDirect1.x, Rect.b.y - tDirect1.y, m_ZValue, m_PenColor[0].argb, 0.f, 0.f },

		{ Rect.a.x               , Rect.a.y             , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		{ Rect.b.x               , Rect.a.y             , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		{ Rect.b.x               , Rect.b.y             , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		{ Rect.a.x               , Rect.b.y             , m_ZValue, m_PenColor[1].argb, 0.f, 0.f },
		
		{ Rect.a.x - tDirect1.x, Rect.a.y - tDirect1.y, m_ZValue, m_PenColor[2].argb, 0.f, 0.f },
		{ Rect.b.x - tDirect2.x, Rect.a.y - tDirect1.y, m_ZValue, m_PenColor[2].argb, 0.f, 0.f },
		{ Rect.b.x - tDirect2.x, Rect.b.y + tDirect1.y, m_ZValue, m_PenColor[2].argb, 0.f, 0.f },
		{ Rect.a.x - tDirect1.x, Rect.b.y + tDirect1.y, m_ZValue, m_PenColor[2].argb, 0.f, 0.f },
	};

	// ׼������
	static const fuShort tIndex[48] = 
	{
		0,1,4,
		1,5,4,
		1,2,5,
		5,2,6,
		7,6,2,
		3,7,2,
		0,4,7,
		0,7,3,

		4,5,9,
		4,9,8,
		9,5,6,
		9,6,10,
		11,10,6,
		11,6,7,
		4,8,11,
		4,11,7
	};

	// ����
	return pGraph->DrawRaw(NULL, 12, 48, tVerts, tIndex);
}

fResult f2dGeometryRendererImpl::DrawCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, fuInt Divide)
{
	if(!pGraph)
		return FCYERR_INVAILDPARAM;
	if(Divide<10)
		Divide = 10;

	m_CacheVerts.resize(Divide * 3);
	m_CacheIndex.resize(Divide * 12);

	float tAng = 3.14f*2.f / (float)Divide;
	for(fuInt i = 0; i<Divide; i++)
	{
		// ���㵥λ����
		fcyVec2 tDirect(cos(tAng * i), sin(tAng * i));

		// ������
		fcyVec2 tExpand = tDirect * (m_PenSize / 2.f);

		// �ҵ����ĵ�
		fcyVec2 tCenter = tDirect * R;

		f2dGraphics2DVertex* pVerts = &m_CacheVerts[i * 3];
		// ���ö���
		// ��Ȧ
		pVerts->color = m_PenColor[0].argb;
		pVerts->z = m_ZValue;
		pVerts->u = pVerts->v = 0.f;
		pVerts->x = Center.x + tCenter.x + tExpand.x;
		pVerts->y = Center.y + tCenter.y + tExpand.y;
		pVerts++;

		// �м�Ȧ
		pVerts->color = m_PenColor[1].argb;
		pVerts->z = m_ZValue;
		pVerts->u = pVerts->v = 0.f;
		pVerts->x = Center.x + tCenter.x;
		pVerts->y = Center.y + tCenter.y;
		pVerts++;

		// ��Ȧ
		pVerts->color = m_PenColor[2].argb;
		pVerts->z = m_ZValue;
		pVerts->u = pVerts->v = 0.f;
		pVerts->x = Center.x + tCenter.x - tExpand.x;
		pVerts->y = Center.y + tCenter.y - tExpand.y;

		// ����Index
		fuShort* pIndex = &m_CacheIndex[i*12+0];
		if(i == Divide-1)
		{
			*pIndex = i*3;	    pIndex++;
			*pIndex = 0;	    pIndex++;
			*pIndex = i*3 + 1;	pIndex++;

			*pIndex = i*3 + 1;  pIndex++;
			*pIndex = 0;		pIndex++;
			*pIndex = 1;		pIndex++;

			*pIndex = i*3 + 1;  pIndex++;
			*pIndex = 1;		pIndex++;
			*pIndex = 2;		pIndex++;

			*pIndex = i*3 + 1;  pIndex++;
			*pIndex = 2;		pIndex++;
			*pIndex = i*3 + 2;  pIndex++;
		}
		else
		{
			*pIndex = i*3;	    pIndex++;
			*pIndex = (i+1)*3;  pIndex++;
			*pIndex = i*3 + 1;	pIndex++;

			*pIndex = i*3 + 1;      pIndex++;
			*pIndex = (i+1)*3;      pIndex++;
			*pIndex = (i+1)*3 + 1;  pIndex++;

			*pIndex = i*3 + 1;     pIndex++;
			*pIndex = (i+1)*3 + 1; pIndex++;
			*pIndex = (i+1)*3 + 2; pIndex++;

			*pIndex = i*3 + 1;     pIndex++;
			*pIndex = (i+1)*3 + 2; pIndex++;
			*pIndex = i*3 + 2;     pIndex++;
		}
	}

	// ����
	fResult tFR = pGraph->DrawRaw(NULL, Divide * 3, Divide * 12, &m_CacheVerts[0], &m_CacheIndex[0]);

	return tFR;
}

fResult f2dGeometryRendererImpl::FillRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect, const fcyColor* pColorArr)
{
	if(!pGraph || !pColorArr)
		return FCYERR_INVAILDPARAM;

	f2dGraphics2DVertex tVerts[4] = 
	{
		{ Rect.a.x, Rect.a.y, m_ZValue, pColorArr[0].argb, 0.f, 0.f },
		{ Rect.b.x, Rect.a.y, m_ZValue, pColorArr[1].argb, 0.f, 0.f },
		{ Rect.b.x, Rect.b.y, m_ZValue, pColorArr[2].argb, 0.f, 0.f },
		{ Rect.a.x, Rect.b.y, m_ZValue, pColorArr[3].argb, 0.f, 0.f }
	};

	return pGraph->DrawQuad(NULL, tVerts);
}

fResult f2dGeometryRendererImpl::FillCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, const fcyColor& CenterColor, const fcyColor& BoundColor, fuInt Divide)
{
	if(!pGraph)
		return FCYERR_INVAILDPARAM;
	if(Divide<10)
		Divide = 10;

	m_CacheVerts.resize(Divide + 1);
	m_CacheIndex.resize(Divide * 3);

	float tAng = 3.14f*2.f / (float)Divide;
	m_CacheVerts[0].color = CenterColor.argb;
	m_CacheVerts[0].x = Center.x;
	m_CacheVerts[0].y = Center.y;
	m_CacheVerts[0].u = m_CacheVerts[0].v = 0.f;
	m_CacheVerts[0].z = m_ZValue;
	for(fuInt i = 1; i<=Divide; i++)
	{
		// ���㵥λ����
		fcyVec2 tDirect(cos(tAng * i), sin(tAng * i));
		tDirect *= R;

		m_CacheVerts[i].color = BoundColor.argb;
		m_CacheVerts[i].u = m_CacheVerts[i].v = 0.f;
		m_CacheVerts[i].x = tDirect.x + Center.x;
		m_CacheVerts[i].y = tDirect.y + Center.y;
		m_CacheVerts[i].z = m_ZValue;
	}

	for(fuInt i = 0; i<Divide; i++)
	{
		fuShort* pIndex = &m_CacheIndex[i*3];

		*pIndex = 0;   pIndex++;
		*pIndex = i+1; pIndex++;
		if(i == Divide-1)
			*pIndex = 1;
		else
			*pIndex = i+2;
	}

	// ����
	fResult tFR = pGraph->DrawRaw(NULL, Divide + 1, Divide * 3, &m_CacheVerts[0], &m_CacheIndex[0]);

	return tFR;
}

////////////////////////////////////////////////////////////////////////////////

f2dRendererImpl::f2dRendererImpl(f2dEngineImpl* pEngine, fuInt BackBufferWidth, fuInt BackBufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel)
	: m_pEngine(pEngine), m_pDev(NULL)
{
	m_pDev = new f2dRenderDeviceImpl(pEngine, BackBufferWidth, BackBufferHeight, Windowed, VSync, AALevel);
}

f2dRendererImpl::~f2dRendererImpl()
{
	FCYSAFEKILL(m_pDev);
}

f2dRenderDevice* f2dRendererImpl::GetDevice()
{
	return m_pDev;
}

fResult f2dRendererImpl::CreateSprite2D(f2dTexture* pTex, f2dSprite** pOut)
{
	if(pOut)
		*pOut = NULL;
	else
		return FCYERR_INVAILDPARAM;

	if(!pTex)
		return FCYERR_INVAILDPARAM;

	*pOut = new f2dSpriteImpl(pTex);

	return FCYERR_OK;
}

fResult f2dRendererImpl::CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, f2dSprite** pOut)
{
	if(pOut)
		*pOut = NULL;
	else
		return FCYERR_INVAILDPARAM;

	if(!pTex)
		return FCYERR_INVAILDPARAM;

	*pOut = new f2dSpriteImpl(pTex, Org);

	return FCYERR_OK;
}

fResult f2dRendererImpl::CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, const fcyVec2& HotSopt, f2dSprite** pOut)
{
	if(pOut)
		*pOut = NULL;
	else
		return FCYERR_INVAILDPARAM;

	if(!pTex)
		return FCYERR_INVAILDPARAM;

	*pOut = new f2dSpriteImpl(pTex, Org, HotSopt);

	return FCYERR_OK;
}

fResult f2dRendererImpl::CreateFontRenderer(f2dStream* pStream, fuInt FontWidth, fuInt FontHeight, fuInt FaceIndex, f2dFontRenderer** pRenderer)
{
	if(pRenderer)
		*pRenderer = NULL;
	else
		return FCYERR_INVAILDPARAM;

	if(!pStream || (FontWidth==0 && FontWidth == 0))
		return FCYERR_INVAILDPARAM;

	try
	{
		*pRenderer = new f2dFontRendererImpl(m_pDev, pStream, FontWidth, FontHeight, FaceIndex);
	}
	catch(const fcyException& e)
	{
		m_pEngine->ThrowException(e);
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

fResult f2dRendererImpl::CreateGeometryRenderer(f2dGeometryRenderer** pOut)
{
	if(pOut)
		*pOut = NULL;
	else
		return FCYERR_INVAILDPARAM;

	*pOut = new f2dGeometryRendererImpl();

	return FCYERR_OK;
}
