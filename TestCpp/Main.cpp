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

using namespace std;

class MyUIControl : 
	public fuiControl
{
public:
	MyUIControl(fuiPage* pRootPage, const std::wstring& Name)
		: fuiControl(pRootPage, Name)
	{
	}
};

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

	// FPS������
	fcyRefPointer<f2dFontProvider> m_FPSFontProvider;
	fcyRefPointer<f2dFontRenderer> m_FPSFontRenderer;

	// ����
	fcyRefPointer<f2dInputKeyboard> m_KeyBoard;

	// ������
	fuiResProviderImpl tProvider;
	fcyRefPointer<fuiPage> m_pRootUIPage;
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
	void drawFPS(f2dFPSController* pFPS, const std::wstring& AdditionData = L"")
	{
		m_pDev->ClearZBuffer();
		m_pGraph2D->Begin();

		fCharW tBuffer[1024];
		swprintf_s(tBuffer, L"FPS %4.2lf",
			pFPS->GetFPS()
			);

		m_FPSFontRenderer->SetColor(0xFF000000);
		m_FPSFontRenderer->DrawTextW(m_pGraph2D, tBuffer, fcyVec2(5.f, 5.f) + fcyVec2(0.f, m_FPSFontProvider->GetAscender()));
		m_FPSFontRenderer->SetColor(0xFF00FF00);
		m_FPSFontRenderer->DrawTextW(m_pGraph2D, tBuffer, fcyVec2(4.f, 4.f) + fcyVec2(0.f, m_FPSFontProvider->GetAscender()));

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
			case F2DMSG_WINDOW_ONCLOSE:
				m_pEngine->Abort();
				break;

			case F2DMSG_WINDOW_ONMOUSEMOVE:
				m_pRootUIPage->SendMouseMove(fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSELDOWN:
				m_pRootUIPage->SendMouseButtonDown(fuiPage::MOUSEBUTTON_L, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSELUP:
				m_pRootUIPage->SendMouseButtonUp(fuiPage::MOUSEBUTTON_L, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSERDOWN:
				m_pRootUIPage->SendMouseButtonDown(fuiPage::MOUSEBUTTON_R, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSERUP:
				m_pRootUIPage->SendMouseButtonUp(fuiPage::MOUSEBUTTON_R, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSEMDOWN:
				m_pRootUIPage->SendMouseButtonDown(fuiPage::MOUSEBUTTON_M, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONMOUSEMUP:
				m_pRootUIPage->SendMouseButtonUp(fuiPage::MOUSEBUTTON_M, &fcyVec2((float)tMsg.Param1, (float)tMsg.Param2));
				break;
			case F2DMSG_WINDOW_ONKEYDOWN:
				m_pRootUIPage->SendKeyDown(fuiPage::VKKeyToF2DKey(tMsg.Param1));
				break;
			case F2DMSG_WINDOW_ONKEYUP:
				m_pRootUIPage->SendKeyUp(fuiPage::VKKeyToF2DKey(tMsg.Param1));
				break;
			case F2DMSG_WINDOW_ONMOUSEWHEEL:
				m_pRootUIPage->SendMouseWheel(*(fDouble*)&tMsg.Param3);
				break;
			case F2DMSG_WINDOW_ONCHARINPUT:
				m_pRootUIPage->SendCharInput(tMsg.Param1);
				break;
			}
		}

		// ����UI
		m_pRootUIPage->Update(ElapsedTime);

		return true;
	}
	fBool OnRender(fDouble ElapsedTime, f2dFPSController* pFPSController)
	{
		// ��ͼ
		m_pDev->Clear();

		m_pGraph2D->Begin();

		m_pGraph2D->End();

		fCharW tBuffer[256];
		swprintf_s(tBuffer, L"FPS %4.2lf", pFPSController->GetFPS());
		m_pRootUIPage->FindControl(L"FPSLabel")->RawSetProperty(L"Text", tBuffer);

		// ����UI
		m_pRootUIPage->Render();

		// ����FPS����
		// drawFPS(pFPSController);

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
			false,  // VSYNC
			F2DAALEVEL_2,
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

			// ������Ⱦ��
			m_pDev->CreateGraphics2D(0, 0, &m_pGraph2D);
			m_pDev->CreateGraphics3D(NULL, &m_pGraph3D);
			m_pGraph3D->SetWorldTransform(fcyMatrix4::GetScaleMatrix(0.8f));
			m_pGraph3D->SetProjTransform(fcyMatrix4::GetPespctiveLH(4.f/3.f, 3.14f/4.f, 0.1f, 1000.f));
			m_pGraph3D->SetViewTransform(fcyMatrix4::GetLookAtLH(fcyVec3(0.f,0.f,100.f), fcyVec3(), fcyVec3(0.f,1.f,0.f)));

			// ��������
			m_pInputSys->CreateKeyboard(-1, false, &m_KeyBoard);

			// ����FPS����
			m_pRenderer->CreateFontFromFile(m_pFileSys->GetStream(L"Res\\Droid Sans Fallback.ttf"), 0, fcyVec2(16, 16), F2DFONTFLAG_NONE, &m_FPSFontProvider);
			m_pRenderer->CreateFontRenderer(m_FPSFontProvider, &m_FPSFontRenderer);

			// ����
			// m_pDev->CreateTextureFromStream(m_pFileSys->GetStream(L"Res\\Loading.png"), 0, 0, false, true, &m_pTexture);
			// m_pRenderer->CreateSprite2D(m_pTexture, &m_pSprite);

			fuiFactory::GetInstace()->RegisterControlCreator<MyUIControl>(L"MyUIControl");

			tProvider = fuiResProviderImpl(m_pFileSys, m_pRenderer);

			try
			{
				m_pRootUIPage.DirectSet(new fuiPage(L"Main", m_pRenderer, m_pGraph2D));
				m_pRootUIPage->GetControlStyle()->LoadResFromFile(m_pFileSys->GetStream(L"Res\\UIStyle.xml"), &tProvider);
				m_pRootUIPage->LoadLayoutFromFile(m_pFileSys->GetStream(L"Res\\UILayout.xml"));
				m_pRootUIPage->SetDebugMode(true);

				m_pRootUIPage->FindControl(L"Label_0")->GetEvent(L"OnCharInput") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						fuiCharEventArgs* tPos = (fuiCharEventArgs*)pArgs->QueryEvent(fuiEventArgs::EVENTTYPE_CHAR);
						
						pControl->RawSetProperty(L"Text", pControl->RawGetProperty(L"Text") + tPos->GetChar());
					};

				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseMove") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						fuiPositionEventArgs* pPosArgs = (fuiPositionEventArgs*)pArgs->QueryEvent(fuiEventArgs::EVENTTYPE_POSITION);

						fCharW tBuffer[256];
						swprintf_s(tBuffer, L"X=%.2f Y=%.2f", pPosArgs->GetPos().x, pPosArgs->GetPos().y);

						pControl->RawSetProperty(L"Text", tBuffer);
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseLeave") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����Ƴ�");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseLDown") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����������");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseLUp") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"�������ſ�");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseMDown") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����м�����");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseMUp") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����м��ſ�");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseRDown") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����Ҽ�����");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnMouseRUp") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"����Ҽ��ſ�");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnGetFocus") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"��ý���");
					};
				m_pRootUIPage->FindControl(L"Label")->GetEvent(L"OnLostFocus") +=
					[&](fuiControl* pControl, fuiEventArgs* pArgs)
					{
						pControl->RawSetProperty(L"Text", L"ʧȥ����");
					};
			}
			catch(const fcyException& e)
			{
				fChar pBuffer[1024];
				sprintf_s(pBuffer, "��ʼ��ʧ�ܣ�\nʱ�����%u\n������Դ��%s\n����������%s", e.GetTime(), e.GetSrc(), e.GetDesc());
				MessageBoxA(0, pBuffer, "f2d ��ʼ��ʧ��", MB_ICONERROR);

				return;
			}
		}

		// ��ʾ����
		m_pEngine->GetMainWindow()->SetVisiable(true);

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
