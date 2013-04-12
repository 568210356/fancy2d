////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoImpl.h
/// @brief fancy2D��Ƶ����ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dVideoStream.h"

#include "fcyMisc/fcyStopWatch.h"

#include "../f2dRenderer.h"
#include "../f2dVideoSys.h"

#include <Dvdmedia.h>

class f2dVideoSysImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ��Ⱦ������
////////////////////////////////////////////////////////////////////////////////
class f2dVideoRenderer : 
	public CBaseVideoRenderer
{
private:
	// {598256BC-185B-4F8C-9881-DA12AB50CC74}
	static const GUID GUID_f2dVideoRenderer;
	enum SUPPORTMEDIATYPE
	{
		SUPPORTMEDIATYPE_RGB24,
		SUPPORTMEDIATYPE_RGB32,
		SUPPORTMEDIATYPE_ARGB32,
		SUPPORTMEDIATYPE_YUY2
	};
private:
	fInt m_TexWidth;                 // ������
	fInt m_TexHeight;                // ����߶�

	SUPPORTMEDIATYPE m_RawDataType;  // ԭʼ��ʽ
	fuInt m_lVideoWidth;             // ��Ƶ���
	fuInt m_lVideoHeight;            // ��Ƶ�߶�
	fuInt m_lVideoPitch;             // ��Ƶ���ݲ���ֵ

	CCritSec m_Lock;                 // ��

	// ������
	fInt m_BufferFlag;           // ��������ʶ���������ʹ�õĻ�����
	fcyColor* m_TexBuffer[2];    // ������������
	CCritSec m_BufferLock[2];    // ��������

	f2dVideoRendererListener* m_pListener; // ������

	// ����������
	fcyStopWatch m_Watch;
	fFloat m_TimeTotal;
	fLen m_DataTotal;
	fLen m_FPSTotal;
	fFloat m_DataPerSecond;
	fFloat m_FPS;
private:
	FCYINLINE fByte clip255(fInt value)
	{
		if(value < 0)
			return 0;
		else if(value > 255)
			return 255;
		return (fByte)value;
	}

	void renderRGBSample(fcData pVideo, fcyColor* pTex);
	void renderYUY2Sample(fcData pVideo, fcyColor* pTex);
public:
	f2dVideoRendererListener* GetRendererListener();
	void SetRendererListener(f2dVideoRendererListener* pListener);
	fcyColor* GetInternalPtr(fuInt Index);
	fuInt GetVideoWidth();
	fuInt GetVideoHeight();
	fResult CopyDataToTexture(f2dTexture* pTex);
	fFloat GetDataPerSecond();
	fFloat GetVideoRenderFPS();
public: // �ӿ�ʵ��
	HRESULT CheckMediaType(const CMediaType *pMediaType);
	HRESULT SetMediaType(const CMediaType *pMediaType);
	HRESULT DoRenderSample(IMediaSample *pMediaSample);
public:
	f2dVideoRenderer(HRESULT *phr = NULL);
	~f2dVideoRenderer();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ��������Ϣ
////////////////////////////////////////////////////////////////////////////////
struct f2dVideoFilterInfo
{
	HINSTANCE hDLLInstance; ///< @brief DLLʵ��
	GUID FilterGUID;        ///< @brief ������GUID
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ����ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dVideoImpl :
	public fcyRefObjImpl<f2dVideo>
{
private:
	// --- ��Ƶ������ ---
	f2dVideoStream* m_pStream;
	f2dVideoStreamReader* m_pReader;

	// --- DEBUG�� ---
	DWORD m_ObjectTableEntry;

	// --- DShow��� ---
	IGraphBuilder* m_pFilterGraph;  ///< @brief ������������
	IMediaControl* m_pMediaControl; ///< @brief ý�������
	IMediaEventEx* m_pMediaEvent;   ///< @brief ý���¼�
	IMediaSeeking* m_pMediaSeek;    ///< @brief ý��Ѱַ
	IVideoFrameStep* m_pVideoStep;  ///< @brief ��Ƶ������Ⱦ����
	IBasicAudio* m_pAudioControl;   ///< @brief ��������

	// --- ������� ---
	f2dVideoRenderer* m_pRenderer;
	f2dTexture* m_pTex;

	// --- ״̬ ---
	fBool m_bLoop;
private:
	void clearUp();
	void registerDebug();
	void unregisterDebug();
private:
	fBool addFilter(const f2dVideoFilterInfo& Filter);
	void clearUselessFilter();
public: // �ӿ�ʵ��
	f2dVideoRendererListener* GetRendererListener();
	void SetRendererListener(f2dVideoRendererListener* pListener);

	fResult Update();
	f2dTexture* GetVideoTex();

	fuInt GetVideoWidth();
	fuInt GetVideoHeight();
	fFloat GetVideoDataRate();
	fFloat GetVideoRenderFPS();
	fResult CopyDataToTexture(f2dTexture* pTex);

	fBool IsLoop();
	void SetLoop(fBool bLoop);
	F2DVIDEOSTATE GetState();
	fResult Play();
	fResult Pause();
	fResult Stop();

	fDouble GetTotalTime();
	fDouble GetCurTime();
	fResult SetCurTime(fDouble Time);
	fResult Seek(fuInt KeyFrame);
	fDouble GetRate();
	fResult SetRate(fDouble Rate);
	fFloat  GetVolume();
	fResult SetVolume(fFloat Volume);
	fFloat  GetPan();
	fResult SetPan(fFloat Pan);
public:
	f2dVideoImpl(f2dVideoSysImpl* pParent, f2dStream* pStream, fuInt Flag);
	~f2dVideoImpl(void);
};

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dVideoSysImpl :
	public fcyRefObjImpl<f2dVideoSys>
{
	friend class f2dVideoImpl;
private:
	f2dEngineImpl* m_pEngine;

	f2dRenderDevice* m_pDev;
	std::vector<f2dVideoFilterInfo> m_FliterGUIDList;
private:
	GUID strToGUID(fcStrW pGUIDStr);
	static BOOL createInstanceFromDll(HINSTANCE hDll, REFCLSID rclsid, REFIID riid, LPVOID * ppv);
public:
	f2dRenderDevice* GetRenderDevice();
public: // �ӿ�ʵ��
	fResult LoadFilter(fcStrW pGUIDStr);
	fResult LoadFilterFromAX(fcStrW AXFilePath, fcStrW pGUIDStr);
	fResult CreateVideo(f2dStream* pStream, fuInt Flag, f2dVideo** pOut);
public:
	f2dVideoSysImpl(f2dEngineImpl* pEngine);
	~f2dVideoSysImpl();
};
