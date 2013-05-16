////////////////////////////////////////////////////////////////////////////////
/// @file  f2dEngine.h
/// @brief fancy2D����ӿڶ���
/// @note  ������f2D������ӿ�
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInterface.h"

// �������
#include "f2dFileSys.h"
#include "f2dWindow.h"
#include "f2dInputSys.h"
#include "f2dSoundSys.h"
#include "f2dRenderer.h"
#include "f2dVideoSys.h"

/// @addtogroup f2d����
/// @brief fancy2d����ӿ�
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D CPU��Ϣ
////////////////////////////////////////////////////////////////////////////////
struct f2dCPUInfo
{
	fcStr CPUString;
	fcStr CPUBrandString;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�����¼�������
/// @note  ͨ����д�������ʵ����Ϣ�ص�
////////////////////////////////////////////////////////////////////////////////
struct f2dEngineEventListener
{
	/// @brief Ӧ�ó����յ��˳���Ϣ
	virtual void OnAppExit() {}
	/// @brief ����ѭ������
	virtual void OnStartLoop() {}
	/// @brief ����ѭ����ֹ
	virtual void OnAbortLoop() {}
	/// @brief     ����һ֡
	/// @note      Ӧ����������ɸ��²���
	/// @param[in] ElapsedTime ������һ֡������ʱ��
	virtual void OnUpdate(fDouble ElapsedTime) {}
	/// @brief     ��Ⱦһ֡
	/// @note      ���������������Ⱦ����
	/// @param[in] ElapsedTime ������һ֡������ʱ��
	virtual void OnRender(fDouble ElapsedTime) {}
	/// @brief     FPSˢ��
	/// @note      �ú������ܱ�֤�ϸ��һ��һ�ε��ã����ڼ����һ��Ĵ��»���Ƶ�ʺ����
	/// @param[in] FPS �µ�FPSֵ
	virtual void OnFPSUpdate(fFloat FPS) {}
	/// @brief     �ڲ��쳣������
	/// @note      ����������쳣ʱ����øú���
	/// @param[in] TimeTick ʱ���
	/// @param[in] Src      �쳣Դ
	/// @param[in] Desc     ����
	virtual void OnException(fuInt TimeTick, fcStr Src, fcStr Desc) {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D����
////////////////////////////////////////////////////////////////////////////////
struct f2dEngine : f2dInterface
{
	// --- ������ ---
	/// @brief ���ؼ�����
	virtual f2dEngineEventListener* GetListener()=0;

	/// @brief ���ü�����
	virtual fResult SetListener(f2dEngineEventListener* pListener)=0;

	// --- �����ʼ�� ---
	/// @brief     ��ʼ����Ⱦ����
	/// @note      ��Ⱦ���ڱ������������֮ǰ��ʼ��
	/// @param[in] Pos      �ͻ���λ��
	/// @param[in] Title    ���ڱ���
	/// @param[in] Visiable �ɼ�
	/// @param[in] Border   �߿�
	virtual fResult InitWindow(const fcyRect& Pos, fcStrW Title, fBool Visiable, F2DWINBORDERTYPE Border)=0;
	
	/// @brief ��ʼ������ϵͳ
	/// @note  ��ҪԤ�ȳ�ʼ����Ⱦ����
	virtual fResult InitSoundSys()=0;

	/// @brief ��ʼ������ϵͳ
	/// @note  ��ҪԤ�ȳ�ʼ����Ⱦ����
	virtual fResult InitInputSys()=0;

	/// @brief ��ʼ����Ⱦϵͳ
	/// @note  ��ҪԤ�ȳ�ʼ����Ⱦ����
	/// @param[in] BufferWidth  ���������
	/// @param[in] BufferHeight �������߶�
	/// @param[in] Windowed     ���ڻ�
	/// @param[in] VSync        ��ֱͬ��
	/// @param[in] AALevel      ����ݵȼ�
	virtual fResult InitRenderer(fuInt BufferWidth, fuInt BufferHeight, fBool Windowed, fBool VSync, F2DAALEVEL AALevel)=0;

	/// @brief ��ʼ����Ƶϵͳ
	/// @note  ��Ҫ��Ⱦϵͳ֧��
	virtual fResult InitVideoSys()=0;

	// --- ������ ---
	virtual f2dWindow* GetMainWindow()=0;  ///< @brief ���������
	virtual f2dFileSys* GetFileSys()=0;    ///< @brief ����ļ�ϵͳ
	virtual f2dSoundSys* GetSoundSys()=0;  ///< @brief �������ϵͳ
	virtual f2dInputSys* GetInputSys()=0;  ///< @brief �������ϵͳ
	virtual f2dRenderer* GetRenderer()=0;  ///< @brief �����Ⱦϵͳ
	virtual f2dVideoSys* GetVideoSys()=0;  ///< @brief �����Ƶϵͳ

	// --- ������� ---
	virtual void Abort()=0; ///< @brief ��ֹ����ѭ��
	virtual void Run()=0;   ///< @brief ִ�г���ѭ��

	// --- ���� ---
	virtual void GetCPUInfo(f2dCPUInfo& tInfo)=0; ///< @brief ����CPU��Ϣ
	virtual fFloat GetFPS()=0;                    ///< @brief ���FPS
	virtual fuInt GetMaxFPS()=0;                  ///< @brief ������FPS
	virtual void SetMaxFPS(fuInt FPS)=0;          ///< @brief �������FPS
	                                              ///< @note  ��Ϊ0��ʾ������
	virtual void DisablePresent()=0;              ///< @brief �ر�Present
};
/// @}
