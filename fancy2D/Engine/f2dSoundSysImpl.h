////////////////////////////////////////////////////////////////////////////////
/// @file  f2dSoundSysImpl.h
/// @brief fancy2D��Ƶϵͳ�ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"
#include "fcyOS/fcyMultiThread.h"

#include "f2dSoundDecoder.h"

#include <deque>

#include <dsound.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief ��̬����dSound
////////////////////////////////////////////////////////////////////////////////
class f2dSoundSysAPI
{
private:
	typedef HRESULT (WINAPI *pDLLEntry_DirectSoundCreate8)(LPCGUID pcGuidDevice, LPDIRECTSOUND8 *ppDS8, LPUNKNOWN pUnkOuter);
private:
	HMODULE m_hModule;

	pDLLEntry_DirectSoundCreate8 m_Entry_pDirectSoundCreate8;
public:
	HRESULT DLLEntry_DirectSoundCreate8(LPCGUID pcGuidDevice, LPDIRECTSOUND8 *ppDS8, LPUNKNOWN pUnkOuter);
public:
	f2dSoundSysAPI();
	~f2dSoundSysAPI();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��̬��������
////////////////////////////////////////////////////////////////////////////////
class f2dSoundBufferStatic :
	public fcyRefObjImpl<f2dSoundBuffer>
{
	friend class f2dSoundSysImpl;
protected:
	IDirectSoundBuffer* m_pBuffer; ///< @brief ��������
	
	fBool m_bLoop;      ///< @brief �Ƿ�ѭ��
	fuInt m_BufferSize; ///< @brief ��������С
	fuInt m_psSize;     ///< @brief һ������ռ�ֽ���
public: // �ӿ�ʵ��
	fBool IsDynamic();

	void Play();
	void Stop();
	void Pause();

	fBool IsLoop();
	void SetLoop(fBool bValue);
	fBool IsPlaying();
	fDouble GetTotalTime();
	fDouble GetTime();
	fResult SetTime(fDouble Time);
	fFloat GetVolume();
	fResult SetVolume(fFloat Value);
	fFloat GetPan();
	fResult SetPan(fFloat Value);
	fuInt GetFrequency();
	fResult SetFrequency(fuInt Value);
protected: // ��ֱֹ��new/delete
	f2dSoundBufferStatic(IDirectSound8* pSound, f2dSoundDecoder* pDecoder, fBool bGlobalFocus);
	~f2dSoundBufferStatic();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��̬��������
/// @note  ��ʽ���壬ʹ��Ԥ��׼����64kb�Ŀռ�����������
////////////////////////////////////////////////////////////////////////////////
class f2dSoundBufferDynamic :
	public fcyRefObjImpl<f2dSoundBuffer>
{
	friend class f2dSoundSysImpl;
private:
	static const fuInt BufferSize;  ///< @brief ��������СΪ64kb
	/// @brief ��ͬ���߳�
	class SoundBufferFiller :
		public fcyBaseThread
	{
	private:
		f2dSoundBufferDynamic* m_pParent;
	private:
		fuInt ThreadJob();
	public:
		SoundBufferFiller(f2dSoundBufferDynamic* pParent);
		~SoundBufferFiller();
	};
protected:
	// �ӿ�
	IDirectSoundBuffer* m_pBuffer;
	IDirectSoundNotify* m_pNotify;
	f2dSoundDecoder* m_pDecoder;
	// ���߳�
	SoundBufferFiller* m_pFiller;  ///< @brief ������߳�
	fcyCriticalSection m_Sec;      ///< @brief �ٽ���
	fcyEvent m_EvtBegin;           ///< @brief ��ͷ����־��
	fcyEvent m_EvtHalf;            ///< @brief ��;����־��
	fcyEvent m_EvtStop;            ///< @brief ��ֹλ��
	fBool m_bHalt;                 ///< @brief �߳���ֹ��Ϣ
	// ��������
	fuInt m_StartPos;        ///< @brief ���ſ�ʼλ��
	fInt  m_PlayTime;        ///< @brief ����ʱ��
	fBool m_bLoop;           ///< @brief ѭ����־
	fuInt m_psSize;          ///< @brief ��������С
	fuInt m_BufferSize;      ///< @brief �����С
private:
	void preInit(fuInt StartPos);  ///< @brief ���̰߳�ȫ����ʼ������仺����
	void updateTime();             ///< @brief �����̰߳�ȫ������ʱ��
	void fillBuffer(fuInt Index);  ///< @brief �����̰߳�ȫ�����ڲ������������Ƶ������
	void regNotify();              ///< @brief �����̰߳�ȫ��ע�����
	void regStopNotify(fuInt Pos); ///< @brief �����̰߳�ȫ��ע��ֹͣ
	fBool isThreadHalt();          ///< @brief ���̰߳�ȫ���ж��߳��˳��¼�
	void haltThread();             ///< @brief ���̰߳�ȫ����ȫ��ֹ�߳�
public: // �ӿ�ʵ��
	fBool IsDynamic();

	void Play();
	void Stop();
	void Pause();

	fBool IsLoop();
	void SetLoop(fBool bValue);
	fBool IsPlaying();
	fDouble GetTotalTime();
	fDouble GetTime();
	fResult SetTime(fDouble Time);
	fFloat GetVolume();
	fResult SetVolume(fFloat Value);
	fFloat GetPan();
	fResult SetPan(fFloat Value);
	fuInt GetFrequency();
	fResult SetFrequency(fuInt Value);
protected: // ��ֱֹ��new/delete
	f2dSoundBufferDynamic(IDirectSound8* pSound, f2dSoundDecoder* pDecoder, fBool bGlobalFocus);
	~f2dSoundBufferDynamic();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Ч����
////////////////////////////////////////////////////////////////////////////////
class f2dSoundSpriteImpl : 
	public fcyRefObjImpl<f2dSoundSprite>
{
	friend class f2dSoundSysImpl;
private:
	IDirectSound8* m_pParent;
	IDirectSoundBuffer* m_pBuffer;                 ///< @brief ԭʼ����
	std::deque<IDirectSoundBuffer*> m_BufferList;  ///< @brief ʹ���л���
	fuInt m_BufferSize;
	fuInt m_psSize;
public: // �ӿ�ʵ��
	void Play();
	void Stop();
	void Pause();
	fDouble GetTotalTime();

	fResult PlayNewSound(fFloat Volume, fFloat Pan);
protected: // ��ֱֹ��new/delete
	f2dSoundSpriteImpl(IDirectSound8* pSound, f2dSoundDecoder* pDecoder, fBool bGlobalFocus);
	~f2dSoundSpriteImpl();
};

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief ����ϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dSoundSysImpl :
	public fcyRefObjImpl<f2dSoundSys>
{
private:
	f2dEngineImpl* m_pEngine;

	f2dSoundSysAPI m_API;

	IDirectSound8* m_pDSound8;
public:
	fResult CreateStaticBuffer(f2dSoundDecoder* pDecoder, fBool bGlobalFocus, f2dSoundBuffer** pOut);
	fResult CreateDynamicBuffer(f2dSoundDecoder* pDecoder, fBool bGlobalFocus, f2dSoundBuffer** pOut);
	fResult CreateSoundSprite(f2dSoundDecoder* pDecoder, fBool bGlobalFocus, f2dSoundSprite** pOut);

	fResult CreateWaveDecoder(f2dStream* pStream, f2dSoundDecoder** pOut);
	fResult CreateOGGVorbisDecoder(f2dStream* pStream, f2dSoundDecoder** pOut);
public:
	f2dSoundSysImpl(f2dEngineImpl* pEngine);
protected:
	~f2dSoundSysImpl();
};
