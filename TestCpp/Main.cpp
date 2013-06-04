// �����Ҫ����fcyStream�������f2d֮ǰ����
#include <fcyIO/fcyStream.h>
#include <fcyFile/fcyModelMesh.h>
#include <fcyOS/fcyDebug.h>
#include <fcyOS/fcyMultiThread.h>

// f2dͷ�ļ�
#include <f2d.h>

#include <iostream>
#include <string>

using namespace std;

class MyApp :
	public f2dEngineEventListener
{
private:
	// ��Ҫ���
	fcyRefPointer<f2dEngine> m_pEngine;
	f2dFileSys* m_pFileSys;
	f2dRenderer* m_pRenderer;
	f2dRenderDevice* m_pDev;
	f2dSoundSys* m_pSoundSys;
	f2dInputSys* m_pInputSys;
	f2dVideoSys* m_pVideoSys;

	// FPS������
	fcyRefPointer<f2dGraphics2D> m_pGraph2D;
	fcyRefPointer<f2dTexture2D> m_FPSTexture;
	fcyRefPointer<f2dFontProvider> m_FPSFont;
	fcyRefPointer<f2dFontRenderer> m_FPSFontRenderer;

	// ������
	fcyRefPointer<f2dSprite> m_Pointer;
	fcyRefPointer<f2dInputKeyboard> m_pKeyboard;

	// ͬ����
	fcyCriticalSection m_Sec;
	fcyVec2 m_MousePos;
	std::wstring m_FPSOnUpdateThread;
	std::wstring m_FPSOnRenderThread;
private:  // ���ܺ���
	void showSelfInfo()
	{
		f2dCPUInfo tInfo;

		m_pEngine->GetCPUInfo(tInfo);

		cout<<"f2d Version"<<(F2DVERSION>>16)<<"."<<(F2DVERSION & 0x0000FFFF)<<"\n"<<endl;

		cout<<"[ CPU������ ] "<<tInfo.CPUString<<endl;
		cout<<"[  CPUƷ��  ] "<<tInfo.CPUBrandString<<"\n"<<endl;

		cout<<"[ �Կ����� ] "<<m_pDev->GetDeviceName()<<"\n"<<endl;

		for(fuInt i = 0; i<m_pDev->GetSupportResolutionCount(); i++)
		{
			fcyVec2 t = m_pDev->EnumSupportResolution(i);
			cout<<"[ �ֱ��� ] "<<(int)t.x<<"x"<<(int)t.y;

			cout<<" ( ����ݵȼ� ";
			for(int j = F2DAALEVEL_NONE; j != F2DAALEVEL_16; j++)
			{
				if(m_pDev->CheckMultiSample((F2DAALEVEL)j, true))
				{
					switch(j)
					{
					case F2DAALEVEL_NONE:
						cout<<"x0 ";
						break;
					case F2DAALEVEL_2:
						cout<<"x2 ";
						break;
					case F2DAALEVEL_4:
						cout<<"x4 ";
						break;
					case F2DAALEVEL_8:
						cout<<"x8 ";
						break;
					case F2DAALEVEL_16:
						cout<<"x16 ";
						break;
					}
				}
			}
			cout<<" )"<<endl;
		}

		cout<<endl;
	}
	void drawFPS(f2dFPSController* pFPS)
	{
		m_pDev->ClearZBuffer();
		m_pGraph2D->Begin();

		fCharW tBuffer[1024];
		swprintf_s(tBuffer, L"%c %lf\n%c %lf\n%c %lf", 
			(wchar_t)-10, pFPS->GetFPS(), (wchar_t)-11, pFPS->GetAvgFPS(), (wchar_t)-12, pFPS->GetMaxFPS());

		m_FPSFontRenderer->DrawTextW(m_pGraph2D, tBuffer, fcyVec2(0.f, m_FPSFont->GetAscender()));

		m_pGraph2D->End();
	}
protected: // ������Ϣ
	fBool OnUpdate(fDouble ElapsedTime, f2dFPSController* pFPSController, f2dMsgPump* pMsgPump)
	{
		// ��Ϣ����
		f2dMsg tMsg;
		while(FCYOK(pMsgPump->GetMsg(&tMsg)))
		{
			switch(tMsg.Type)
			{
			case F2DMSG_RENDER_ONDEVLOST:
				fcyDebug::Trace(L"�豸��ʧ��\n");
				break;
			case F2DMSG_RENDER_ONDEVRESET:
				fcyDebug::Trace(L"�豸���ã�\n");
				break;
			case F2DMSG_WINDOW_ONCLOSE:
				m_pEngine->Abort();
				break;
			case F2DMSG_WINDOW_ONMOUSEMOVE:
				break;

			case F2DMSG_KEYBOARD_ONKEYDOWN:
				// m_pEngine->GetMainWindow()->SetCaption(L"��������");
				m_Sec.Lock();
				if(tMsg.Param1 == F2DINPUTKEYCODE_RIGHT)
					m_MousePos.x += 10.f;
				m_Sec.UnLock();
				break;
			case F2DMSG_KEYBOARD_ONKEYUP:
				break;
			}
		}

		// ͬ������
		fCharW tBuffer[1024];
		swprintf_s(tBuffer, L"�����߳� FPS: %4.2lf ƽ��FPS: %4.2lf ���FPS: %4.2lf", pFPSController->GetFPS(), pFPSController->GetAvgFPS(), pFPSController->GetMaxFPS());
		
		m_Sec.Lock();
		m_FPSOnUpdateThread = tBuffer;
		m_Sec.UnLock();

		return true;
	}
	fBool OnRender(fDouble ElapsedTime, f2dFPSController* pFPSController)
	{
		// ͬ������
		fCharW tBuffer[1024];
		swprintf_s(tBuffer, L"��Ⱦ�߳� FPS: %4.2lf ƽ��FPS: %4.2lf ���FPS: %4.2lf", pFPSController->GetFPS(), pFPSController->GetAvgFPS(), pFPSController->GetMaxFPS());
		
		m_Sec.Lock();
		m_FPSOnRenderThread = tBuffer;
		m_Sec.UnLock();

		m_pDev->Clear();

		// drawFPS(pFPSController);

		m_pGraph2D->Begin();

		m_Sec.Lock();
		m_Pointer->Draw(m_pGraph2D, m_MousePos);
		m_Sec.UnLock();

		m_pGraph2D->End();

		// ����FPS����
		{
			m_pDev->ClearZBuffer();
			m_pGraph2D->Begin();

			fCharW tBuffer[1024];
			
			m_Sec.Lock();
			swprintf_s(tBuffer, L"%s\n%s", 
				m_FPSOnUpdateThread.c_str(), m_FPSOnRenderThread.c_str()
				);
			m_Sec.UnLock();

			m_FPSFontRenderer->SetColor(0xFFFFFFFF);
			m_FPSFontRenderer->DrawTextW(m_pGraph2D, tBuffer, fcyVec2(0.f, m_FPSFont->GetAscender()));

			m_pGraph2D->End();
		}

		return true; 
	}
public:
	MyApp()
	{
		struct : public f2dInitialErrListener {
			void OnErr(fuInt TimeTick, fcStr Src, fcStr Desc)
			{
				fChar pBuffer[1024];
				sprintf_s(pBuffer, "��ʼ��ʧ�ܣ�\nʱ�����%u\n������Դ��%s\n����������%s", TimeTick, Src, Desc);
				MessageBoxA(0, pBuffer, "f2d ��ʼ��ʧ��", MB_ICONERROR);
			}
		} tErrCallBack;

		// ��������
		if(FCYFAILED(CreateF2DEngineAndInit(
			F2DVERSION,
			fcyRect(50.f, 50.f, 800.f + 50.f, 600.f + 50.f), // 800x600
			L"fancy2D 0.5 ���湦��ģ����Գ���",                          // ����
			true,
			true,  // VSYNC
			F2DAALEVEL_NONE,
			this,
			&*m_pEngine,
			&tErrCallBack)))
		{ return; }

		// ������
		m_pFileSys = m_pEngine->GetFileSys();
		m_pRenderer = m_pEngine->GetRenderer();
		m_pDev = m_pEngine->GetRenderer()->GetDevice();
		m_pSoundSys = m_pEngine->GetSoundSys();
		m_pInputSys = m_pEngine->GetInputSys();
		m_pVideoSys = m_pEngine->GetVideoSys();

		// ��Ϣ�Ծ�
		showSelfInfo();

		// ������Դ
		{
			// ӳ�䱾���ļ���DemoRes���ڵ�Res
			m_pFileSys->LoadRealPath(L"Res", L"E:\\Projects\\fancy2D\\TestCpp\\DemoRes\\");

			// ��������
			m_pDev->CreateTextureFromStream(m_pFileSys->GetStream(L"Res\\FPSFont.png"), 0, 0, false, true, &m_FPSTexture);
			//m_pRenderer->CreateFontFromTex(m_pFileSys->GetStream(L"Res\\FPSFont.xml"), m_FPSTexture, &m_FPSFont);
			m_pRenderer->CreateFontFromFile(m_pFileSys->GetStream(L"Res\\������ͨ����.ttf"), 0, fcyVec2(20, 20), F2DFONTFLAG_NONE, &m_FPSFont);
			m_pRenderer->CreateFontRenderer(m_FPSFont, &m_FPSFontRenderer);

			// ����
			fcyRefPointer<f2dTexture2D> pTex;
			m_pDev->CreateTextureFromStream(m_pFileSys->GetStream(L"Res\\Pointer.png"), 0, 0, false, true, &pTex);
			m_pRenderer->CreateSprite2D(pTex, &m_Pointer);

			m_pInputSys->CreateKeyboard(-1, true, &m_pKeyboard);

			// ������Ⱦ��
			m_pDev->CreateGraphics2D(0, 0, &m_pGraph2D);
		}

		// ��ʾ����
		m_pEngine->GetMainWindow()->SetVisiable(true);

		// ����
		m_pEngine->Run(F2DENGTHREADMODE_FULLMULTITHREAD, 120, 0);
	}
	~MyApp()
	{
	}
};

//int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(5351);
#endif

	MyApp tApp;

	return 0;
}
