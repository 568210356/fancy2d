////////////////////////////////////////////////////////////////////////////////
/// @file  f2dRendererImpl.h
/// @brief fancy2D��Ⱦ���ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dRenderDeviceImpl.h"

#include <unordered_map>

#include <ft2build.h> 
#include FT_FREETYPE_H

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D Spriteʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dSpriteImpl : 
	public fcyRefObjImpl<f2dSprite>
{
	friend class f2dRendererImpl;
private:
	f2dTexture* m_pTex;
	F2DSPRITEFLIP m_FlipType;
	fcyRect m_Org;
	fcyVec2 m_HotSpot;
	fcyColor m_Color[4];
	float m_ZValue;

	fcyRect m_UV;
	fcyRect m_SpriteRect;
private:
	void recalcu();
public: // �ӿ�ʵ��
	f2dTexture* GetTexture();
	fResult SetTexture(f2dTexture* pTex);
	fcyRect GetTexRect();
	fResult SetTexRect(fcyRect Rect);
	fcyVec2 GetHotSpot();
	fResult SetHotSpot(fcyVec2 Point);
	F2DSPRITEFLIP GetFlipType();
	fResult SetFlipType(F2DSPRITEFLIP Type);
	fFloat GetZ();
	fResult SetZ(fFloat Value);
	fcyColor GetColor(fuInt Index);
	fResult SetColor(fcyColor Color);
	fResult SetColor(fuInt Index, fcyColor Color);
	fResult Draw(f2dGraphics2D* pGraph, const fcyRect& Dest);
	fResult Draw(f2dGraphics2D* pGraph, const fcyRect& Dest, const fcyRect& SubTex);
	fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center);
	fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale);
	fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, const fcyRect& SubTex);
	fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation);
	fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation, const fcyRect& SubTex);
protected:
	f2dSpriteImpl(f2dTexture* pTex);
	f2dSpriteImpl(f2dTexture* pTex, fcyRect SrcRect);
	f2dSpriteImpl(f2dTexture* pTex, fcyRect SrcRect, fcyVec2 HotSpot);
	~f2dSpriteImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D ������Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dFontRendererImpl :
	public fcyRefObjImpl<f2dFontRenderer>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRendererImpl;
private:
	// ���建��
	struct TextureCache
	{
		// ��������
		fCharW fontChar;    // �ַ�
		fuInt fontWidth;    // ����ͼ����Ч���
		fuInt fontHeight;   // ����ͼ����Ч�߶�
		int fontLeft;       // ������˾���������ľ���
		int fontTop;        // ���ֶ��˾�����ߵĸ߶�
		fcyVec2 fontAdvance;// ���Ƶ��ƽ���

		// ��Ⱦ����
		fcyRect uv;

		// ������
		TextureCache* pPrev;
		TextureCache* pNext;
	};

	// �߼����������
	struct AdvancedTextParam
	{
		union
		{
			int IntData;
			float FloatData;
		};
	};

	// �߼�������
	struct AdvanceTextFormat
	{
		F2DSPRITEFLIP FlipType;       // ��ת
		float Bias;                   // ��б
		const fcyVec2& StartPos;      // ��ʼλ��
		fcyVec2 Pos;                  // �ʴ�λ��
		fcyVec2* PosCache;            // ����
		fuInt CacheCount;             // ��������
		float LineHeight;             // �и�
		f2dGraphics2DVertex Verts[4]; // ����
	};
private:
	f2dRenderDevice* m_pDev;
	f2dStream* m_pStream;
	std::wstring m_Using;     // ���ڻָ�����

	// --- ��Ⱦѡ�� ---
	F2DSPRITEFLIP m_FlipType;
	fcyColor m_BlendColor[4];
	fFloat m_ZValue;

	// --- freetype��� ---
	FT_Open_Args m_Args;
	FT_StreamRec m_Stream;
	FT_Library m_FontLib;
	FT_Face m_Face;

	// --- �������� ---
	fuInt m_CacheXMax;              // �����������
	fuInt m_CacheYMax;              // ������������
	fuInt m_CacheCurWidth;          // ���嵥��������
	fuInt m_CacheCurHeight;         // ���嵥������߶�
	TextureCache* m_Cache;          // ������
	f2dTextureDynamic* m_CacheTex;  // ����������

	// --- ���ʹ�� ---
	std::unordered_map<fCharW, TextureCache*> m_Dict; // ��ѯ��
	TextureCache* m_UsedNode;  // ʹ���нڵ㣬��֤Ϊѭ������
	TextureCache* m_FreeNode;  // ���нڵ㣬��������
private:
	static unsigned long streamRead(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count);
	static void streamClose(FT_Stream stream);
private:
	void addUsedNode(TextureCache* p);      // �������ʹ�ýڵ�
	void removeFreeNode(TextureCache* p);   // �Ƴ����нڵ�p������
	void removeUsedNode(TextureCache* p);   // �Ƴ�ʹ���нڵ�p������
	float widthSizeToPixel(int Size);       // ��ȵ�λ������
	float heightSizeToPixel(int Size);      // �߶ȵ�λ������
	TextureCache* getChar(fCharW Char);     // �������
	bool makeCache(fuInt XCount, fuInt YCount);                        // ���������������XCount * YCount������
	bool renderCache(TextureCache* pCache, fCharW Char, bool Discard); // �ڻ�������[x][y]λ�û�������Char
private:
	fBool parseAdvancedCommand(fcStrW Text, fuInt Count, fuInt& Pos, fCharW Cmd[]);
	fBool parseAdvancedParam(fcStrW Text, fuInt Count, fuInt& Pos, AdvancedTextParam Param[], fuInt& ParamCount);
	// �����߼����ֲ���������
	// ���ؿɴ�ӡ�ַ�
	fCharW parseAdvancedText(fcStrW Text, fuInt Count, fuInt& Pos, AdvanceTextFormat& Fmt);
public: // �¼�����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fuInt GetFaceCount();
	fFloat GetLineHeight();
	f2dTexture* GetCache();
	void Cache(fcStrW Text);
	fFloat GetZ();
	void SetZ(fFloat ZValue);
	fcyColor GetColor(fuInt Index);
	void SetColor(const fcyColor& Color);
	void SetColor(fuInt Index, const fcyColor& Color);
	F2DSPRITEFLIP GetFlipType();
	void SetFlipType(F2DSPRITEFLIP Type);
	fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, const fcyVec2& StartPos);
	fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosOut);
	fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, fFloat Bias, const fcyVec2& StartPos, fcyVec2* PosOut);
	fResult DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, const fcyRect& DestRect, fuInt* pCountRendered);
	fResult DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fuInt* pCountRendered);
	fResult DrawAdvancedText(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosCache, fuInt PosCacheCount);
	fResult DrawAdvancedTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fcyVec2* PosCache, fuInt PosCacheCount, fuInt* pCountRendered);
protected:
	f2dFontRendererImpl(f2dRenderDevice* pDev, fcyStream* pStream, fuInt FontWidth, fuInt FontHeight, fuInt FaceIndex);
	~f2dFontRendererImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��������Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dGeometryRendererImpl :
	public fcyRefObjImpl<f2dGeometryRenderer>
{
	friend class f2dRendererImpl;
private:
	fcyColor m_PenColor[3];
	fFloat m_PenSize;
	fFloat m_ZValue;

	std::vector<f2dGraphics2DVertex> m_CacheVerts;
	std::vector<fuShort> m_CacheIndex;
public:
	fFloat GetZ();
	void SetZ(fFloat ZValue);
	fcyColor GetPenColor(fuInt Index);
	void SetPenColor(fuInt Index, const fcyColor& Color);
	fFloat GetPenSize();
	void SetPenSize(fFloat Size);

	fResult DrawLine(f2dGraphics2D* pGraph, const fcyVec2& Begin, const fcyVec2& End);
	fResult DrawRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect);
	fResult DrawCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, fuInt Divide);

	fResult FillRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect, const fcyColor* pColorArr);
	fResult FillCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, const fcyColor& CenterColor, const fcyColor& BoundColor, fuInt Divide);
protected:
	f2dGeometryRendererImpl();
	~f2dGeometryRendererImpl();
};

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dRendererImpl :
	public fcyRefObjImpl<f2dRenderer>
{
private:
	f2dEngineImpl* m_pEngine;

	f2dRenderDeviceImpl* m_pDev;
public: // �ӿ�ʵ��
	f2dRenderDevice* GetDevice();

	fResult CreateSprite2D(f2dTexture* pTex, f2dSprite** pOut);
	fResult CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, f2dSprite** pOut);
	fResult CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, const fcyVec2& HotSopt, f2dSprite** pOut);

	fResult CreateFontRenderer(f2dStream* pStream, fuInt FontWidth, fuInt FontHeight, fuInt FaceIndex, f2dFontRenderer** pRenderer);

	fResult CreateGeometryRenderer(f2dGeometryRenderer** pOut);
public:
	f2dRendererImpl(f2dEngineImpl* pEngine, fuInt BackBufferWidth, fuInt BackBufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel);
	~f2dRendererImpl();
};
