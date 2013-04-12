////////////////////////////////////////////////////////////////////////////////
/// @file  f2dEngineImpl.h
/// @brief fancy2D����ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dEngine.h"

#include "f2dFileSysImpl.h"
#include "f2dWindowImpl.h"

class f2dWindowImpl;
class f2dSoundSysImpl;
class f2dInputSysImpl;
class f2dRendererImpl;
class f2dVideoSysImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D����ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dEngineImpl :
	public fcyRefObjImpl<f2dEngine>
{
private:
	// ״̬
	bool m_bStop;
	bool m_bPresent;
	float m_cFPS;
	fuInt m_iFPSMax;      // ���FPS
	float m_FrameDelay;   // FPS����ѡ��

	// ������
	f2dEngineEventListener* m_pListener;

	// �����������
	f2dWindowClass m_WinClass;
	f2dFileSysImpl m_FileSys;

	// ���
	f2dWindowImpl*   m_pWindow;
	f2dSoundSysImpl* m_pSoundSys;
	f2dInputSysImpl* m_pInputSys;
	f2dRendererImpl* m_pRenderer;
	f2dVideoSysImpl* m_pVideoSys;
public: // �ڲ���������
	// ���쳣������ʱ���øú���
	void ThrowException(const fcyException& e);
	void ThrowException(fuInt TimeTick, fcStr Src, fcStr Desc);
public: // �ӿ�ʵ��
	f2dEngineEventListener* GetListener();
	fResult SetListener(f2dEngineEventListener* pListener);

	fResult InitWindow(const fcyRect& Pos, fcStrW Title, fBool Visiable, F2DWINBORDERTYPE Border);
	fResult InitSoundSys();
	fResult InitInputSys();
	fResult InitRenderer(fuInt BufferWidth, fuInt BufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel);
	fResult InitVideoSys();

	f2dWindow* GetMainWindow();
	f2dFileSys* GetFileSys();
	f2dSoundSys* GetSoundSys();
	f2dInputSys* GetInputSys();
	f2dRenderer* GetRenderer();
	f2dVideoSys* GetVideoSys();

	void Abort();
	void Run();

	fFloat GetFPS();
	fuInt GetMaxFPS();
	void SetMaxFPS(fuInt FPS);
	void DisablePresent();
public:
	f2dEngineImpl();
	~f2dEngineImpl();
};
