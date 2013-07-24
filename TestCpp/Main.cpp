// �����Ҫ����fcyStream�������f2d֮ǰ����
#include <fcyIO/fcyStream.h>
#include <fcyFile/fcyModelMeshFile.h>
#include <fcyFile/fcyModelMeshExporter.h>
#include <fcyOS/fcyDebug.h>
#include <fcyOS/fcyMultiThread.h>

// UI��
#include <fcyUIBase/fuiPage.h>
#include <fcyUIBase/fuiFactory.h>

// f2dͷ�ļ�
#include <f2d.h>

#include <iostream>
#include <string>
#include <vector>

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

	// ��Ⱦ��
	fcyRefPointer<f2dGraphics2D> m_pGraph2D;
	fcyRefPointer<f2dGraphics3D> m_pGraph3D;

	// ����
	fcyRefPointer<f2dInputKeyboard> m_KeyBoard;

	// ������
	fuiResProviderImpl tProvider;
	fcyRefPointer<fuiPage> m_pRootUIPage;

	fcyRefPointer<f2dSprite> m_Sprite;
	fcyRefPointer<f2dParticlePool> m_ParticlePool;
private:  // ���ܺ���
	void showSelfInfo()
	{
		f2dCPUInfo tInfo;

		m_pEngine->GetCPUInfo(tInfo);

		cout<<"f2d Version"<<(F2DVERSION>>16)<<"."<<(F2DVERSION & 0x0000FFFF)<<"\n"<<endl;

		cout<<"[ CPU������ ] "<<tInfo.CPUString<<endl;
		cout<<"[  CPUƷ��  ] "<<tInfo.CPUBrandString<<"\n"<<endl;

		cout<<"[ �Կ����� ] "<<m_pDev->GetDeviceName()<<"\n"<<endl;

		for(fuInt i = 0; i<m_pDev->GetSupportResolutionCount(); ++i)
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
protected: // ������Ϣ
	fBool OnUpdate(fDouble ElapsedTime, f2dFPSController* pFPSController, f2dMsgPump* pMsgPump)
	{
		static fcyVec2 tMouse = fcyVec2(300.f, 300.f);

		// ��Ϣ����
		f2dMsg tMsg;
		while(FCYOK(pMsgPump->GetMsg(&tMsg)))
		{
			switch(tMsg.Type)
			{
			case F2DMSG_WINDOW_ONCLOSE:
				m_pEngine->Abort();
				break;
			case F2DMSG_WINDOW_ONMOUSEMOVE:
				{
					tMouse.x = (float)tMsg.Param1;
					tMouse.y = (float)tMsg.Param2;
				}
			default:
				m_pRootUIPage->DealF2DMsg(tMsg);
				break;
			}
		}

		// ����UI
		m_pRootUIPage->Update(ElapsedTime);

		{
			f2dParticleCreationDesc tDesc = 
			{
				fcyRect(fcyVec2(-0.1f, -2.f), fcyVec2(0.1f, -1.0f)),
				fcyVec2(100.f, 200.f),  // V
				fcyVec2(-3.14f / 2, -3.14f / 2),  // VAngle
				fcyVec2(100.f, 150.f),   // AR
				fcyVec2(-10.f, 10.f),   // AT
				fcyVec2(),
				fcyVec2(0.3f, 0.5f),
				fcyColor(255,255,255,200),
				fcyVec2(0, 0),
				fcyColor(0,255,242,0),
				fcyVec2(1.3f,1.3f),
				fcyVec2(-0.5f,0.3f),
				fcyVec2(0.f,0.f)
			};

			f2dParticleCreationDesc tDesc2 = 
			{
				fcyRect(fcyVec2(-1.0f, -1.0f), fcyVec2(1.0f, 1.0f)),
				fcyVec2(100.f, 200.f),  // V
				fcyVec2(0.f, 2*3.14f),  // VAngle
				fcyVec2(-100.f, -50.f),      // AR
				fcyVec2(50.f, 100.f),   // AT
				fcyVec2(),
				fcyVec2(3.f, 5.f),
				fcyColor(255,255,255,255),
				fcyVec2(0, 0),
				fcyColor(0,50,50,250),
				fcyVec2(1.3f,1.3f),
				fcyVec2(-0.5f,0.3f),
				fcyVec2(0.f,0.f)
			};

			static float s_Timer = 0;
			s_Timer += ElapsedTime;
			if(s_Timer > 0.01f)
			{
				s_Timer = 0.f;
				m_ParticlePool->Emitted(m_Sprite, tMouse, fcyVec2(10.f, 20.f), tDesc);

				m_ParticlePool->Emitted(m_Sprite, fcyVec2(400.f, 300.f), fcyVec2(10.f, 20.f), tDesc);

				m_ParticlePool->Emitted(m_Sprite, fcyVec2(200.f, 200.f), fcyVec2(3.f, 5.f), tDesc2);
			}

			m_ParticlePool->Update(ElapsedTime);
		}

		fCharW tBuffer[256];
		swprintf_s(tBuffer, L"FPS:%.2lf ����:%d", pFPSController->GetFPS(), m_ParticlePool->GetCount());
		m_pRootUIPage->FindControl(L"TestLabel")->RawSetProperty(L"Text", tBuffer);

		return true;
	}
	fBool OnRender(fDouble ElapsedTime, f2dFPSController* pFPSController)
	{
		// ��ͼ
		m_pDev->Clear(0xFF000000);

		// ����UI
		m_pRootUIPage->Render();

		m_pGraph2D->Begin();

		// ��������ͼ...
		m_ParticlePool->Render(m_pGraph2D);

		m_pGraph2D->End();

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
			fcyRect(50.f, 50.f, 640.f + 50.f, 480.f + 50.f), // 640x480
			L"�ޱ���",               // ����
			true,
			true,  // VSYNC
			F2DAALEVEL_NONE,
			this,
			&m_pEngine,
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
			m_pFileSys->LoadRealPath(L"Res", L"DemoRes\\");
			m_pFileSys->LoadRealPath(L"Simple", L"DemoRes\\Simple\\");

			// ������Ⱦ��
			m_pDev->CreateGraphics2D(0, 0, &m_pGraph2D);
			m_pDev->CreateGraphics3D(NULL, &m_pGraph3D);
			m_pGraph3D->SetWorldTransform(fcyMatrix4::GetScaleMatrix(0.8f));
			m_pGraph3D->SetProjTransform(fcyMatrix4::GetPespctiveLH(4.f/3.f, 3.14f/4.f, 0.1f, 1000.f));
			m_pGraph3D->SetViewTransform(fcyMatrix4::GetLookAtLH(fcyVec3(0.f,0.f,100.f), fcyVec3(), fcyVec3(0.f,1.f,0.f)));

			// ��������
			m_pInputSys->CreateKeyboard(-1, false, &m_KeyBoard);

			tProvider = fuiResProviderImpl(m_pFileSys, m_pRenderer);

			try
			{
				m_pRootUIPage.DirectSet(new fuiPage(L"Main", m_pRenderer, m_pGraph2D));
				m_pRootUIPage->GetControlStyle()->LoadResFromFile(m_pFileSys->GetStream(L"Simple\\Style.xml"), &tProvider);
				m_pRootUIPage->LoadLayoutFromFile(m_pFileSys->GetStream(L"Simple\\Layout.xml"));
				m_pRootUIPage->SetDebugMode(false);

				m_pRootUIPage->FindControl(L"TestEditBox")->GetEvent(L"OnTextChanged") +=
					[&](fuiControl* p, fuiEventArgs* pArgs)
					{
						m_pRootUIPage->FindControl(L"TestLabel")->RawSetProperty(L"Text", p->RawGetProperty(L"Text"));
					};
			}
			catch(const fcyException& e)
			{
				fChar pBuffer[1024];
				sprintf_s(pBuffer, "��ʼ��ʧ�ܣ�\nʱ�����%u\n������Դ��%s\n����������%s", e.GetTime(), e.GetSrc(), e.GetDesc());
				MessageBoxA(0, pBuffer, "f2d ��ʼ��ʧ��", MB_ICONERROR);

				return;
			}

			// Particle
			fcyRefPointer<f2dTexture2D> pTex;
			m_pDev->CreateTextureFromStream(
				m_pFileSys->GetStream(L"Res\\Particle.png"),
				0, 0, false, true, &pTex);
			m_pRenderer->CreateSprite2D(pTex, &m_Sprite);
			
			m_pRenderer->CreateParticlePool(&m_ParticlePool);
		}

		// ��ʾ����
		m_pEngine->GetMainWindow()->SetVisiable(true);
		m_pEngine->GetMainWindow()->MoveToCenter();

		// �������
		m_pEngine->GetMainWindow()->HideMouse(false);

		// ����
		m_pEngine->Run(F2DENGTHREADMODE_MULTITHREAD);
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

	// system("pause");
	return 0;
}
