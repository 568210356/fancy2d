#include "f2dEngineImpl.h"

#include "f2dInputSysImpl.h"
#include "f2dSoundSysImpl.h"
#include "f2dRendererImpl.h"
#include "f2dVideoSysImpl.h"

#include "fcyOS/fcyDebug.h"
#include "fcyMisc/fcyStopWatch.h"

#define F2DEXPORT
#include "../f2d.h"

////////////////////////////////////////////////////////////////////////////////
// ��������
extern "C" fResult F2DDLLFUNC CreateF2DEngine(fuInt Version, f2dEngineEventListener* pEngineEventListener, f2dEngine** pOut)
{
	if(Version != F2DVERSION)
		return FCYERR_INVAILDVERSION;
	if(!pOut)
		return FCYERR_ILLEGAL;

	*pOut = NULL;
	try
	{
		*pOut = new f2dEngineImpl();

		if(pEngineEventListener)
			(*pOut)->SetListener(pEngineEventListener);
	}
	catch(const fcyException& e)
	{
		if(pEngineEventListener)
			pEngineEventListener->OnException(e.GetTime(), e.GetSrc(), e.GetDesc());
		
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

extern "C" fResult F2DDLLFUNC CreateF2DEngineAndInit(fuInt Version, const fcyRect& WinPos, fcStrW Title, fBool Windowed, fBool VSync, F2DAALEVEL AA, f2dEngineEventListener* pEngineEventListener, f2dEngine** pOut)
{
	if(Version != F2DVERSION)
		return FCYERR_INVAILDVERSION;
	if(!pOut)
		return FCYERR_ILLEGAL;

	*pOut = NULL;

	// ��ͼ��ʼ�����
	{
		fResult tVR;
		f2dEngine* pRet = NULL;
		try
		{
			pRet = new f2dEngineImpl();

			if(pEngineEventListener)
				pRet->SetListener(pEngineEventListener);
		}
		catch(const fcyException& e)
		{
			if(pEngineEventListener)
				pEngineEventListener->OnException(e.GetTime(), e.GetSrc(), e.GetDesc());
			return FCYERR_INTERNALERR;
		}

		tVR = pRet->InitWindow(WinPos, Title, false, F2DWINBORDERTYPE_FIXED);
		if(FCYFAILED(tVR))
		{
			FCYSAFEKILL(pRet);
			return FCYERR_INTERNALERR;
		}

		tVR = pRet->InitSoundSys();
		if(FCYFAILED(tVR))
		{
			FCYSAFEKILL(pRet);
			return FCYERR_INTERNALERR;
		}

		tVR = pRet->InitInputSys();
		if(FCYFAILED(tVR))
		{
			FCYSAFEKILL(pRet);
			return FCYERR_INTERNALERR;
		}

		tVR = pRet->InitRenderer((fuInt)WinPos.GetWidth(), (fuInt)WinPos.GetHeight(), Windowed, VSync, AA);
		if(FCYFAILED(tVR))
		{
			FCYSAFEKILL(pRet);
			return FCYERR_INTERNALERR;
		}

		tVR = pRet->InitVideoSys();
		if(FCYFAILED(tVR))
		{
			FCYSAFEKILL(pRet);
			return FCYERR_INTERNALERR;
		}

		*pOut = pRet;
	}

	return FCYERR_OK;
}

////////////////////////////////////////////////////////////////////////////////
f2dEngineImpl::f2dEngineImpl()
	: m_bStop(true), m_bPresent(true), m_cFPS(0.f), m_iFPSMax(0), m_FrameDelay(0.f),
	m_pListener(NULL),
	m_WinClass(L"F2DRenderWindow"),
	m_pWindow(NULL), m_pSoundSys(NULL), m_pInputSys(NULL), m_pRenderer(NULL), m_pVideoSys(NULL)
{
}

f2dEngineImpl::~f2dEngineImpl()
{
	// �������
	FCYSAFEKILL(m_pVideoSys);
	FCYSAFEKILL(m_pRenderer);
	FCYSAFEKILL(m_pInputSys);
	FCYSAFEKILL(m_pSoundSys);
	FCYSAFEKILL(m_pWindow);
}

void f2dEngineImpl::ThrowException(const fcyException& e)
{
	FCYDEBUGEXCPT(e);

	if(m_pListener)
		m_pListener->OnException(e.GetTime(), e.GetSrc(), e.GetDesc());
}

void f2dEngineImpl::ThrowException(fuInt TimeTick, fcStr Src, fcStr Desc)
{
	fcyDebug::Trace("[ TimeTick = %u ] fcyException @%s : %s\n",  \
		TimeTick, Src, Desc); 

	if(m_pListener)
		m_pListener->OnException(TimeTick, Src, Desc);
}

f2dEngineEventListener* f2dEngineImpl::GetListener()
{
	return m_pListener;
}

fResult f2dEngineImpl::SetListener(f2dEngineEventListener* pListener)
{
	m_pListener = pListener;
	return FCYERR_OK;
}

fResult f2dEngineImpl::InitWindow(const fcyRect& Pos, fcStrW Title, fBool Visiable, F2DWINBORDERTYPE Border)
{
	if(m_pWindow)
		return FCYERR_ILLEGAL;

	return m_WinClass.CreateRenderWindow(this, Pos, Title, Visiable, Border, &m_pWindow);
}

fResult f2dEngineImpl::InitSoundSys()
{
	if(m_pSoundSys || !m_pWindow)
		return FCYERR_ILLEGAL;

	try
	{
		m_pSoundSys = new f2dSoundSysImpl(this);
	}
	catch(const fcyException& e)
	{
		ThrowException(e);
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

fResult f2dEngineImpl::InitInputSys()
{
	if(m_pInputSys || !m_pWindow)
		return FCYERR_ILLEGAL;

	try
	{
		m_pInputSys = new f2dInputSysImpl(this);
	}
	catch(const fcyException& e)
	{
		ThrowException(e);
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

fResult f2dEngineImpl::InitRenderer(fuInt BufferWidth, fuInt BufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel)
{
	if(m_pRenderer || !m_pWindow)
		return FCYERR_ILLEGAL;

	try
	{
		m_pRenderer = new f2dRendererImpl(this, BufferWidth, BufferHeight, Windowed, VSync, AALevel);
	}
	catch(const fcyException& e)
	{
		ThrowException(e);
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

fResult f2dEngineImpl::InitVideoSys()
{
	if(m_pVideoSys || !m_pRenderer)
		return FCYERR_ILLEGAL;

	try
	{
		m_pVideoSys = new f2dVideoSysImpl(this);
	}
	catch(const fcyException& e)
	{
		ThrowException(e);
		return FCYERR_INTERNALERR;
	}

	return FCYERR_OK;
}

f2dWindow* f2dEngineImpl::GetMainWindow()
{
	return m_pWindow;
}

f2dFileSys* f2dEngineImpl::GetFileSys()
{
	return &m_FileSys;
}

f2dSoundSys* f2dEngineImpl::GetSoundSys()
{
	return m_pSoundSys;
}

f2dInputSys* f2dEngineImpl::GetInputSys()
{
	return m_pInputSys;
}

f2dRenderer* f2dEngineImpl::GetRenderer()
{
	return m_pRenderer;
}

f2dVideoSys* f2dEngineImpl::GetVideoSys()
{
	return m_pVideoSys;
}

void f2dEngineImpl::Abort()
{
	m_bStop = true;
}

void f2dEngineImpl::Run()
{
	m_bStop = false;

	// ��Ⱦ�豸
	f2dRenderDeviceImpl* tDev = NULL;
	fResult tDevSync = FCYERR_INTERNALERR;

	// ��ʼ��������
	fcyStopWatch tWatch;
	fDouble tTime=0., tPageCount=0., tTotalTime=0.;

	// ������ʼ����Ϣ
	if(m_pListener)
		m_pListener->OnStartLoop();

	// ��ʼ��ʱ
	tWatch.Reset();

	// ִ�г���ѭ��
	MSG tMsg;
	timeBeginPeriod(1); // ���ڼ�ʱ������
	while(!m_bStop)
	{
		// Ӧ�ó�����Ϣ����
		tWatch.Pause();
		{
			if(PeekMessage(&tMsg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&tMsg);
				DispatchMessage(&tMsg);

				// �����˳���Ϣ
				if(tMsg.message==WM_QUIT)
					if(m_pListener) // �����˳���Ϣ
						m_pListener->OnAppExit();
			}
		}
		tWatch.Resume();

		// FPS����
		{
			// FPS����
			if(m_iFPSMax)
			{
				tTime = tWatch.GetElpased();	// �������ʱ��

				if(tTime < m_FrameDelay)
				{
					fuInt tTimeToSleep = (fuInt)((m_FrameDelay - tTime) * 1000.f);
					
					// Sleep�������ٲ�����CPUռ��
					if(tTimeToSleep)
						Sleep(tTimeToSleep - 1);

					// while��ȷ����
					while((tTime = tWatch.GetElpased()) < m_FrameDelay) {}
				}
			}
			else
			{
				// ��������ʱ��
				tTime = tWatch.GetElpased();
			}

			// ���ü���������ʼ��ʱ
			tWatch.Reset();

			// ����FPS
			tPageCount+= 1.;
			tTotalTime += tTime;
			if(tTotalTime>=1.)
			{
				m_cFPS = (float)(tPageCount/tTotalTime);
				tTotalTime=0.;
				tPageCount=0.;

				if(m_pListener) // ����FPS������Ϣ
					m_pListener->OnFPSUpdate(m_cFPS);
			}
		}

		// ִ����Ⱦ�¼�
		if(m_pRenderer)
		{
			tDev = (f2dRenderDeviceImpl*)m_pRenderer->GetDevice();

			// ͬ���豸״̬�������豸��ʧ
			if(FCYOK(tDevSync = tDev->SyncDevice()))
			{
				if(m_pListener) // ������Ⱦ�¼�
					m_pListener->OnRender(tTime);
			}
			else
				Sleep(1); // ��Ⱦʧ��ʱ��ʱ
		}
		else
			Sleep(1);     // ����Ⱦ��ʱ��ʱ

		// ִ�и����¼�
		if(m_pListener)
			m_pListener->OnUpdate(tTime);

		// �ݽ�����
		if(FCYOK(tDevSync) && tDev && m_bPresent)
			tDev->Present();
	}
	timeEndPeriod(1); // ������ʱ������

	// �����˳�ѭ����Ϣ
	if(m_pListener)
		m_pListener->OnAbortLoop();
}

fFloat f2dEngineImpl::GetFPS()
{
	return m_cFPS;
}

fuInt f2dEngineImpl::GetMaxFPS()
{
	return m_iFPSMax;
}

void f2dEngineImpl::SetMaxFPS(fuInt FPS)
{
	m_iFPSMax = FPS;
	if(FPS)
		m_FrameDelay = 1.f / FPS;
}

void f2dEngineImpl::DisablePresent()
{
	m_bPresent = !m_bPresent;
}
