////////////////////////////////////////////////////////////////////////////////
/// @file  f2dRenderDeviceImpl.h
/// @brief fancy2D��Ⱦ�豸�ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dRenderer.h"

#include "f2dWindowImpl.h"

#include <stack>
#include <vector>
#include <list>

#include <d3d9.h>
#include <d3dx9.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief d3d9��ʽ����
////////////////////////////////////////////////////////////////////////////////
class f2dRenderDeviceAPI
{
private:
	// DX9
	typedef IDirect3D9* (WINAPI *pDLLEntry_Direct3DCreate9)(UINT SDKVersion);

	// D3DX9
	typedef HRESULT (WINAPI *pDLLEntry_D3DXSaveSurfaceToFileInMemory)(
        LPD3DXBUFFER*             ppDestBuf,
        D3DXIMAGE_FILEFORMAT      DestFormat,
        LPDIRECT3DSURFACE9        pSrcSurface,
        CONST PALETTEENTRY*       pSrcPalette,
        CONST RECT*               pSrcRect);
	typedef HRESULT (WINAPI *pDLLEntry_D3DXCreateFontW)(
        LPDIRECT3DDEVICE9       pDevice,  
        INT                     Height,
        UINT                    Width,
        UINT                    Weight,
        UINT                    MipLevels,
        BOOL                    Italic,
        DWORD                   CharSet,
        DWORD                   OutputPrecision,
        DWORD                   Quality,
        DWORD                   PitchAndFamily,
        LPCWSTR                 pFaceName,
        LPD3DXFONT*             ppFont);
	typedef HRESULT (WINAPI *pDLLEntry_D3DXCreateTextureFromFileInMemoryEx)(
		LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
		DWORD                     Filter,
		DWORD                     MipFilter,
		D3DCOLOR                  ColorKey,
		D3DXIMAGE_INFO*           pSrcInfo,
		PALETTEENTRY*             pPalette,
		LPDIRECT3DTEXTURE9*       ppTexture);
	typedef HRESULT (WINAPI *pDLLEntry_D3DXCreateEffectEx)(
		LPDIRECT3DDEVICE9               pDevice,
		LPCVOID                         pSrcData,
		UINT                            SrcDataLen,
		CONST D3DXMACRO*                pDefines,
		LPD3DXINCLUDE                   pInclude,
		LPCSTR                          pSkipConstants, 
		DWORD                           Flags,
		LPD3DXEFFECTPOOL                pPool,
		LPD3DXEFFECT*                   ppEffect,
		LPD3DXBUFFER*                   ppCompilationErrors);
	typedef HRESULT (WINAPI *pDLLEntry_D3DXCreateEffectFromFileExW)(
        LPDIRECT3DDEVICE9               pDevice,
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pSkipConstants, 
        DWORD                           Flags,
        LPD3DXEFFECTPOOL                pPool,
        LPD3DXEFFECT*                   ppEffect,
        LPD3DXBUFFER*                   ppCompilationErrors);
private:
	HMODULE m_hModuleD3D9;
	HMODULE m_hModuleD3DX9;

	pDLLEntry_Direct3DCreate9 m_Entry_pDirect3DCreate9;

	pDLLEntry_D3DXSaveSurfaceToFileInMemory m_Entry_pD3DXSaveSurfaceToFileInMemory;
	pDLLEntry_D3DXCreateFontW m_Entry_pD3DXCreateFontW;
	pDLLEntry_D3DXCreateTextureFromFileInMemoryEx m_Entry_pD3DXCreateTextureFromFileInMemoryEx;
	pDLLEntry_D3DXCreateEffectEx m_Entry_pD3DXCreateEffectEx;
	pDLLEntry_D3DXCreateEffectFromFileExW m_Entry_pD3DXCreateEffectFromFileExW;
public:
	IDirect3D9* DLLEntry_Direct3DCreate9(UINT SDKVersion);

	HRESULT DLLEntry_D3DXSaveSurfaceToFileInMemory(
        LPD3DXBUFFER*             ppDestBuf,
        D3DXIMAGE_FILEFORMAT      DestFormat,
        LPDIRECT3DSURFACE9        pSrcSurface,
        CONST PALETTEENTRY*       pSrcPalette,
        CONST RECT*               pSrcRect);
	HRESULT DLLEntry_D3DXCreateFontW(
        LPDIRECT3DDEVICE9       pDevice,  
        INT                     Height,
        UINT                    Width,
        UINT                    Weight,
        UINT                    MipLevels,
        BOOL                    Italic,
        DWORD                   CharSet,
        DWORD                   OutputPrecision,
        DWORD                   Quality,
        DWORD                   PitchAndFamily,
        LPCWSTR                 pFaceName,
        LPD3DXFONT*             ppFont);
	HRESULT DLLEntry_D3DXCreateTextureFromFileInMemoryEx(
		LPDIRECT3DDEVICE9         pDevice,
        LPCVOID                   pSrcData,
        UINT                      SrcDataSize,
        UINT                      Width,
        UINT                      Height,
        UINT                      MipLevels,
        DWORD                     Usage,
        D3DFORMAT                 Format,
        D3DPOOL                   Pool,
        DWORD                     Filter,
        DWORD                     MipFilter,
        D3DCOLOR                  ColorKey,
        D3DXIMAGE_INFO*           pSrcInfo,
        PALETTEENTRY*             pPalette,
        LPDIRECT3DTEXTURE9*       ppTexture);
	HRESULT DLLEntry_D3DXCreateEffectEx(
		LPDIRECT3DDEVICE9               pDevice,
		LPCVOID                         pSrcData,
		UINT                            SrcDataLen,
		CONST D3DXMACRO*                pDefines,
		LPD3DXINCLUDE                   pInclude,
		LPCSTR                          pSkipConstants, 
		DWORD                           Flags,
		LPD3DXEFFECTPOOL                pPool,
		LPD3DXEFFECT*                   ppEffect,
		LPD3DXBUFFER*                   ppCompilationErrors);
	HRESULT DLLEntry_D3DXCreateEffectFromFileExW(
        LPDIRECT3DDEVICE9               pDevice,
        LPCWSTR                         pSrcFile,
        CONST D3DXMACRO*                pDefines,
        LPD3DXINCLUDE                   pInclude,
        LPCSTR                          pSkipConstants, 
        DWORD                           Flags,
        LPD3DXEFFECTPOOL                pPool,
        LPD3DXEFFECT*                   ppEffect,
        LPD3DXBUFFER*                   ppCompilationErrors);
public:
	f2dRenderDeviceAPI();
	~f2dRenderDeviceAPI();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�����ڲ��ӿ�
////////////////////////////////////////////////////////////////////////////////
struct f2dTextureInternal : public f2dTexture
{
	virtual IDirect3DBaseTexture9* GetHandle()=0;  ///< @brief ��������ָ�룬���������ü���
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��̬����ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dTextureStatic : 
	public fcyRefObjImpl<f2dTextureInternal>
{
	friend class f2dRenderDeviceImpl;
private:
	IDirect3DTexture9* m_pTex;  ///< @brief ������ʵ����ָ��
	fuInt m_Width;              ///< @brief ������
	fuInt m_Height;             ///< @brief ����߶�
public: // �ӿ�ʵ��
	fBool IsDynamic();
	fBool IsRenderTarget();
	fuInt GetWidth();
	fuInt GetHeight();
	fResult Lock(fcyRect* pLockRect, fBool Discard, fuInt* Pitch, fData* pOut);
	fResult Unlock();

	IDirect3DBaseTexture9* GetHandle();
protected:
	f2dTextureStatic(IDirect3DTexture9* pTex, fuInt Width, fuInt Height);
	~f2dTextureStatic();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��̬����ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dTextureDynamic : 
	public fcyRefObjImpl<f2dTextureInternal>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRenderDeviceImpl;
private:
	f2dRenderDeviceImpl* m_pDev;///< @brief �������´�������
	IDirect3DTexture9* m_pTex;  ///< @brief ������ʵ����ָ��
	fuInt m_Width;              ///< @brief ������
	fuInt m_Height;             ///< @brief ����߶�
public: // ��Ϣ����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fBool IsDynamic();
	fBool IsRenderTarget();
	fuInt GetWidth();
	fuInt GetHeight();
	fResult Lock(fcyRect* pLockRect, fBool Discard, fuInt* Pitch, fData* pOut);
	fResult Unlock();

	IDirect3DBaseTexture9* GetHandle();
protected:
	f2dTextureDynamic(f2dRenderDeviceImpl* pDev, IDirect3DTexture9* pTex, fuInt Width, fuInt Heights);
	~f2dTextureDynamic();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��ȾĿ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dTextureRenderTarget : 
	public fcyRefObjImpl<f2dTextureInternal>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRenderDeviceImpl;
private:
	f2dRenderDeviceImpl* m_pDev;   ///< @brief �������´�������
	IDirect3DTexture9* m_pTex;     ///< @brief ������ʵ����ָ��
	IDirect3DSurface9* m_pSurface; ///< @breif ��Ⱦ����
	fuInt m_Width;                 ///< @brief ������
	fuInt m_Height;                ///< @brief ����߶�
public:
	IDirect3DSurface9* GetSurface(); ///< @brief �����Ⱦ����
public: // ��Ϣ����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fBool IsDynamic();
	fBool IsRenderTarget();
	fuInt GetWidth();
	fuInt GetHeight();
	fResult Lock(fcyRect* pLockRect, fBool Discard, fuInt* Pitch, fData* pOut);
	fResult Unlock();

	IDirect3DBaseTexture9* GetHandle();
protected:
	f2dTextureRenderTarget(f2dRenderDeviceImpl* pDev, IDirect3DTexture9* pTex, fuInt Width, fuInt Height);
	~f2dTextureRenderTarget();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Graphics2Dʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dGraphics2DImpl :
	public fcyRefObjImpl<f2dGraphics2D>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRenderDeviceImpl;
private:
	static const fuInt ConstantConvert[F2DRENDERSTATE_MASK];      // ��������
	static const fuInt FVF;                // �����ʶ
	struct RenderCommand
	{
		f2dTextureInternal* pTex;  // ��Ⱦ�õ������ɿ�
		fuInt VertCount;           // ���ƺķѵĶ�����
		fuInt IndexCount;          // ���ƺķѵ�������
	};
private:
	f2dRenderDeviceImpl* m_pParentDev;
	IDirect3DDevice9* m_pDev;

	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DIndexBuffer9* m_pIB;
	fuInt m_VBMaxCount;   // ���㻺���������
	fuInt m_IBMaxCount;   // ���������������
	fuInt m_VBUsedCount;  // ���㻺�������ÿռ�
	fuInt m_IBUsedCount;  // �������������ÿռ�
	fuInt m_VBAlloced;    // ��flush
	fuInt m_IBAlloced;    // ��flush
	f2dGraphics2DVertex* m_pVBData;
	fuShort* m_pIBData;

	// --- ��Ⱦָ�� ---
	std::vector<RenderCommand> m_Commands;

	// --- ��ǰ״̬ ---
	bool m_RenderStart;
	fcyMatrix4 m_CurMatrix;
	fcyMatrix4 m_CurProj;
	std::stack<fcyMatrix4> m_MatList;
	fuInt m_CurStates[F2DRENDERSTATE_MASK];
private:
	void flush(bool Discard=false);    // ִ�����л�ͼָ��
	bool alloc(fuInt VertCountToAlloc, fuInt IndexCountToAlloc, f2dGraphics2DVertex** pVertexOut, fuShort** pIndexOut); // �����ڴ�
	void pushcommand(f2dTextureInternal* pTex, fuInt VertCount, fuInt IndexCount); // ׷��������кϲ�
public: // ��Ϣ����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fuInt GetRenderState(F2DRENDERSTATE State);
	void SetRenderState(F2DRENDERSTATE State, fuInt Value);
	void GetProjTransform(fcyMatrix4* pOut);
	void SetProjTransform(const fcyMatrix4& pTrans);
	void GetWorldTransform(fcyMatrix4* pOut);
	void SetWorldTransform(const fcyMatrix4& pTrans);
	void PushWorldTransform();
	void PopWorldTransform();
	
	void SyncStates();
	fResult Begin();
	fResult End();
	fResult Flush();

	fResult DrawQuad(f2dTexture* pTex,
		const f2dGraphics2DVertex& v1, 
		const f2dGraphics2DVertex& v2, 
		const f2dGraphics2DVertex& v3, 
		const f2dGraphics2DVertex& v4
		);
	fResult DrawQuad(f2dTexture* pTex, const f2dGraphics2DVertex* arr);
	fResult DrawRaw(f2dTexture* pTex, fuInt VertCount, fuInt IndexCount, const f2dGraphics2DVertex* VertArr, const fuShort* IndexArr);
protected:
	f2dGraphics2DImpl(f2dRenderDeviceImpl* pDev, fuInt VertexBufferCount, fuInt IndexBufferCount);
	~f2dGraphics2DImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D ����Ч�����
////////////////////////////////////////////////////////////////////////////////
class f2dPostEffectImpl :
	public fcyRefObjImpl<f2dPostEffect>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRenderDeviceImpl;
private:
	f2dRenderDeviceImpl* m_pDev;
	ID3DXEffect* m_pEffect;
	bool m_StartEffect;

	f2dTextureRenderTarget* m_pRT;
	std::vector<f2dTextureRenderTarget*> m_AdditionRT; // �������ȾĿ��
	std::vector<IDirect3DSurface9*> m_PassTarget;      // ��¼ÿһ��pass��Ŀ��
private:
	void preInitEffect(); // ����Ч����Ԥ����
public: // ��Ϣ����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fFloat GetFloat(fcStr ParamName);
	fResult GetFloatArr(fcStr ParamName, fFloat* Dest, fuInt Count);
	fResult SetValue(fcStr ParamName, fFloat Value);
	fResult SetValue(fcStr ParamName, fuInt Index, fFloat Value);
	fResult SetFloatArr(fcStr ParamName, const fFloat* Src, fuInt Count);
	fResult SetTexture(fcStr ParamName, f2dTexture* pTex);

	fResult Begin();
	fResult End();
protected:
	f2dPostEffectImpl(f2dRenderDeviceImpl* pDev, ID3DXEffect* pEffect);
	~f2dPostEffectImpl();
};

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ�豸ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dRenderDeviceImpl :
	public fcyRefObjImpl<f2dRenderDevice>
{
private:
	struct ListenerNode
	{
		f2dRenderDeviceEventListener* pListener;
		ListenerNode* pNext;
	};
private:
	f2dEngineImpl* m_pEngine;

	// API���
	f2dRenderDeviceAPI m_API;

	// DirectX���
	IDirect3D9* m_pD3D9;
	IDirect3DDevice9* m_pDev;
	D3DPRESENT_PARAMETERS m_D3Dpp;
	D3DVIEWPORT9 m_ViewPort;
	std::wstring m_DevName;
	
	// ������
	ListenerNode* m_ListenerList;

	// �豸״̬
	bool m_bDevLost;                              // �豸��ʧ��־
	std::stack<f2dTextureRenderTarget*> m_RTList; // ��ȾĿ���ջ
	IDirect3DSurface9* m_pBackBuffer;             // ����ȾĿ��
	RECT m_ScissorRect;                           // �ü�����

	// Window
	HWND m_hWnd;
	f2dWindowDC m_DC;
	IDirect3DSurface9* m_pWinSurface;
private:
	void initState();         // ��ʼ��״̬
	void sendDevLostMsg();    // �����豸��ʧ�¼�
	void sendDevResetMsg();   // �����豸�����¼�
	void clearRenderTarget(); // �����ȾĿ���ջ�����ָ���ȾĿ��
public: // �ڲ�����
	fResult SyncDevice();          // Э�����ԣ�����豸��ʧ����
	fResult Present();             // ����
public: // �ӿ�ʵ��
	void* GetHandle(); // ������ʵ�豸ָ��

	fResult AttachListener(f2dRenderDeviceEventListener* Listener);
	fResult RemoveListener(f2dRenderDeviceEventListener* Listener);

	fResult CreateDynamicTexture(fuInt Width, fuInt Height, f2dTexture** pOut);
	fResult CreateTextureFromStream(f2dStream* pStream, fuInt Width, fuInt Height, fBool IsDynamic, fBool HasMipmap, f2dTexture** pOut);
	fResult CreateRenderTarget(fuInt Width, fuInt Height, f2dTexture** pOut);
	fResult CreateGraphics2D(fuInt VertexBufferSize, fuInt IndexBufferSize, f2dGraphics2D** pOut);

	fResult CreatePostEffect(f2dStream* pStream, f2dPostEffect** pOut, f2dStream** pErrOut);

	fResult Clear(const fcyColor& BackBufferColor, fFloat ZValue);
	fResult ClearColor(const fcyColor& BackBufferColor);
	fResult ClearZBuffer(fFloat Value);

	f2dTexture* GetRenderTarget();
	fResult PushRenderTarget(f2dTexture* pTarget);
	fResult PopRenderTarget();
	fcyRect GetScissorRect();
	fResult SetScissorRect(const fcyRect& pRect);

	fcStrW GetDeviceName();
	fuInt GetBufferWidth();
	fuInt GetBufferHeight();
	fBool IsWindowed();
	F2DAALEVEL GetAALevel();
	fBool CheckMultiSample(F2DAALEVEL AALevel, fBool Windowed);
	fResult SetBufferSize(fuInt Width, fuInt Height, fBool Windowed, fBool VSync, F2DAALEVEL AALevel);

	fResult SaveScreen(f2dStream* pStream);
	fResult SaveTexture(f2dStream* pStream, f2dTexture* pTex);

	fResult UpdateScreenToWindow(fcyColor KeyColor, fByte Alpha);
public:
	f2dRenderDeviceImpl(f2dEngineImpl* pEngine, fuInt BackBufferWidth, fuInt BackBufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel);
	~f2dRenderDeviceImpl();
};
