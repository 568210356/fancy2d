#include <string>

// �����Ҫ����fcyStream�������f2d֮ǰ����
#include "fcyIO/fcyStream.h"
#include "fcyUIBase/fuiContainer.h"
#include "fcyUIControl/fuiBoard.h"
#include "fcyUIControl/fuiHProgressBar.h"
#include "fcyUIControl/fuiVProgressBar.h"
#include "fcyUIControl/fuiSpriteButton.h"
#include "fcyUIControl/fuiHSliderBar.h"
#include "fcyUIControl/fuiLabel.h"
#include "fcyUIControl/fuiEditBox.h"

// f2dͷ�ļ�
#include "f2d.h"

using namespace std;

// For Test
fuiHProgressBar* g_pHProgress;

class MyBoard :
	public fuiBoard
{
private:
	bool m_bMyMouseDown;
	fcyVec2 m_LastMouse;
public:
	fBool OnMouseMove(fFloat X, fFloat Y)
	{
		if(fuiBoard::OnMouseMove(X,Y))
			return true;

		if(m_bMyMouseDown)
		{
			fcyVec2 tOffset(X - m_LastMouse.x,
				Y - m_LastMouse.y);

			const fcyRect& tOrg = GetRect();
			SetRect(fcyRect(tOrg.a + tOffset, tOrg.b + tOffset));
		}

		return true;
	}

	void OnLMouseUp(fFloat X, fFloat Y)
	{
		fuiBoard::OnLMouseUp(X,Y);

		m_bMyMouseDown = false;

		m_MouseEvent = FUIMOUSEEVENT_MOVE;
		m_pMouseCatch = NULL;
	}

	fBool OnLMouseDown(fFloat X, fFloat Y)
	{
		if(fuiBoard::OnLMouseDown(X,Y))
			return true;

		m_MouseEvent = FUIMOUSEEVENT_LDOWN;
		m_pMouseCatch = this;

		g_pHProgress->SetParent(this);
		SetControlLayer(0);
		m_bMyMouseDown = true;
		m_LastMouse = fcyVec2(X,Y);

		return true;
	}
public:
	MyBoard(fuiContainer* pContainer)
		: fuiBoard(pContainer), m_bMyMouseDown(false)
	{
		SetStyle(L"Default");
	}
};

class MyAppUIPage :
	public fuiContainer
{
private:
	f2dRenderer* m_pRenderer;
	f2dGraphics2D* m_pGraph;
	fuiRenderer* m_pUIRenderer;
	fuiContext* m_pUIContext;
protected:
	void init()
	{
		fcyFileStream* pStream = NULL;
		
		pStream = new fcyFileStream(L"DemoRes\\DemoUISprite.xml", false);
		m_pUIContext->LoadSprite(pStream);
		FCYSAFEKILL(pStream);
		
		pStream = new fcyFileStream(L"DemoRes\\DemoUIStyle.xml", false);
		m_pUIContext->LoadStyle(pStream);
		FCYSAFEKILL(pStream);

		pStream = new fcyFileStream(L"DemoRes\\DemoUIFont.xml", false);
		m_pUIContext->LoadFontStyle(pStream);
		FCYSAFEKILL(pStream);
	}
	void initUI()
	{
		fuiBoard* pBoard = new MyBoard(this);
		pBoard->SetRect(fcyRect(10.f, 10.f, 150.f, 150.f));

		pBoard = new MyBoard(this);
		pBoard->SetRect(fcyRect(200.f, 200.f, 600.f, 500.f));

		g_pHProgress = new fuiHProgressBar(this, 0.5);
		g_pHProgress->SetStyle(L"Default");
		g_pHProgress->SetRect(fcyRect(10.f, 10.f, 300.f, 50.f));

		fuiVProgressBar* t = new fuiVProgressBar(this, 0.5);
		t->SetStyle(L"Default");
		t->SetRect(fcyRect(10.f, 10.f, 50.f, 300.f));

		fuiSpriteButton* pButton = new fuiSpriteButton(this);
		pButton->SetStyle(L"PlayButton");
		pButton->SetRect(fcyRect(50.f, 50.f, 80.f, 80.f));
		pButton->SetEvt_OnClick(std::bind(&MyAppUIPage::PlayButton_OnClick, this));

		fuiHSliderBar* pSliderBar = new fuiHSliderBar(pBoard);
		pSliderBar->SetStyle(L"Default");
		pSliderBar->SetRect(fcyRect(20.f, 100.f, 220.f, 150.f));

		fuiLabel* pLabel = new fuiLabel(pBoard);
		pLabel->SetRect(fcyRect(10.f, 100.f, 250.f, 150.f));
		pLabel->SetStyle(L"Default");
		pLabel->SetCaption(L"");

		fuiEditBox* pEditBox = new fuiEditBox(pBoard);
		pEditBox->SetRect(fcyRect(10.f, 200.f, 400.f, 250.f));
		pEditBox->SetStyle(L"Default");
		pEditBox->SetText(L"haha��ȥ��fkܳ������������");
	}
	fuiContext* OnQueryContext()
	{
		return m_pUIContext;
	}
protected:
	void PlayButton_OnClick()
	{
		fcyFileStream* pStream = new fcyFileStream(L"Screen.png", true);
		m_pRenderer->GetDevice()->SaveScreen(pStream);
		FCYSAFEKILL(pStream);
	}
public:
	void RenderUI()
	{
		m_pUIRenderer->Begin();

		Render(m_pUIRenderer);

		m_pUIRenderer->End();
	}
public:
	MyAppUIPage(f2dRenderer* pRenderer, f2dGraphics2D* pGraph)
		: fuiContainer(NULL), m_pRenderer(pRenderer), m_pGraph(pGraph),
		m_pUIRenderer(NULL), m_pUIContext(NULL)
	{
		m_pUIContext = new fuiContext(m_pRenderer);
		m_pUIRenderer = new fuiRenderer(m_pRenderer, m_pGraph);

		init();
		initUI();
	}
	~MyAppUIPage()
	{
		FCYSAFEKILL(m_pUIRenderer);
		FCYSAFEKILL(m_pUIContext);
	}
};

class MyApp :
	public f2dWindowEventListener,  // ������Ϣ����
	public f2dEngineEventListener   // ������Ϣ����
{
private:
	// ��Ҫ���
	f2dEngine* m_pEngine;
	f2dFileSys* m_pFileSys;
	f2dRenderer* m_pRenderer;
	f2dRenderDevice* m_pDev;
	f2dSoundSys* m_pSoundSys;
	f2dInputSys* m_pInputSys;
	f2dVideoSys* m_pVideoSys;

	// ��ͼ����
	f2dGraphics2D* m_pGraph;

	f2dSprite* m_pSprite;

	// UIҳ
	MyAppUIPage* m_pUIPage;
private:  // ������Ϣ
	// ���ڹر���Ϣ
	void OnClose()
	{
		m_pEngine->Abort();
	}
	// ��������
	void OnKeyDown(fuInt KeyCode, fuInt Flag)
	{
		switch(KeyCode)
		{
		case 'P':
			try
			{
				fcyFileStream* pFile = new fcyFileStream(L"Screen.png", true);
				m_pDev->SaveScreen(pFile);
				pFile->Release();
			}
			catch(const fcyException& e)
			{
				MessageBoxA(0, e.GetDesc(), "����ʧ��", 0);
			}
			break;
		default:
			m_pUIPage->SendKeyboardEvent(FUIKEYBOARDEVENT_KEYDOWN, fuiHelper::VKCodeToF2DKeyCode(KeyCode));
		}
	}
	void OnKeyUp(fuInt KeyCode, fuInt Flag)
	{
		m_pUIPage->SendKeyboardEvent(FUIKEYBOARDEVENT_KEYUP, fuiHelper::VKCodeToF2DKeyCode(KeyCode));
	}
	// ����¼�
	void OnMouseLBDown(fShort X, fShort Y, fuInt Flag)
	{
		m_pUIPage->SendMouseEvent(FUIMOUSEEVENT_LDOWN, (float)X, (float)Y);
	}
	void OnMouseLBUp(fShort X, fShort Y, fuInt Flag)
	{
		m_pUIPage->SendMouseEvent(FUIMOUSEEVENT_LUP, (float)X, (float)Y);
	}
	void OnMouseMove(fShort X, fShort Y, fuInt Flag)
	{
		m_pUIPage->SendMouseEvent(FUIMOUSEEVENT_MOVE, (float)X, (float)Y);
	}
	void OnCharInput(fCharW CharCode, fuInt Flag)
	{
		m_pUIPage->SendKeyboardEvent(FUIKEYBOARDEVENT_CHARINPUT, (F2DINPUTKEYCODE)CharCode);
	}
private: // ������Ϣ
	// ����ѭ��
	void OnStartLoop()
	{
	}
	// ���߼��¼�
	void OnUpdate(double ElapsedTime)
	{
		m_pUIPage->Update(ElapsedTime);
	}
	// ����Ⱦ�¼�
	void OnRender(double ElapsedTime)
	{
		m_pDev->Clear(0x00FFFFFF);

		m_pGraph->Begin();

		m_pUIPage->RenderUI();

		// m_pSprite->Draw(m_pGraph, fcyVec2(400.f, 300.f));

		m_pGraph->End();		
	}
	// �쳣
	void OnException(fuInt TimeTick, fcStr Src, fcStr Desc)
	{
		char tData[1024];
		sprintf_s(tData, "ʱ�����%u\n�쳣Դ��%s\n�쳣��Ϣ��%s", TimeTick, Src, Desc);
		MessageBoxA(NULL, tData, "�쳣", 0);
	}
public:
	MyApp()
		: m_pEngine(NULL), m_pGraph(NULL)
	{
		// ��������
		if(FCYFAILED(CreateF2DEngineAndInit(
			F2DVERSION,
			fcyRect(50.f, 50.f, 800.f + 50.f, 600.f + 50.f), // 800x600
			L"f2d 0.4 - Hello fancyUI!",                     // ����
			true,
			true,
			F2DAALEVEL_NONE,
			this,
			&m_pEngine)))
		{
			MessageBox(0, L"��������ʱʧ��", L"����", MB_ICONERROR);
			return;
		}

		// ������
		m_pFileSys = m_pEngine->GetFileSys();
		m_pRenderer = m_pEngine->GetRenderer();
		m_pDev = m_pEngine->GetRenderer()->GetDevice();
		m_pSoundSys = m_pEngine->GetSoundSys();
		m_pInputSys = m_pEngine->GetInputSys();
		m_pVideoSys = m_pEngine->GetVideoSys();

		// ע����Ϣ������
		m_pEngine->GetMainWindow()->SetListener(this);

		// ������Դ
		{
			// ӳ�䱾���ļ���DemoRes���ڵ�Res
			m_pFileSys->LoadRealPath(L"Res", L"DemoRes");

			// ����Graphics
			m_pRenderer->GetDevice()->CreateGraphics2D(0,0,&m_pGraph);

			// ����UI
			m_pUIPage = new MyAppUIPage(m_pRenderer, m_pGraph);
			m_pUIPage->SetRect(fcyRect(0.f, 0.f, 800.f, 600.f));

			// ����Sprite
			f2dTexture* pTex = NULL;
			m_pRenderer->GetDevice()->CreateTextureFromStream(
				m_pFileSys->GetStream(L"Res\\TEST.png"),
				0, 0, false, true, &pTex);
			m_pRenderer->CreateSprite2D(pTex, &m_pSprite);
			pTex->Release();
		}

		// ��ʾ����
		m_pEngine->GetMainWindow()->SetVisiable(true);

		// ����
		m_pEngine->Run();
	}
	~MyApp()
	{
		// ж����Դ
		{
			FCYSAFEKILL(m_pSprite);
			FCYSAFEDEL(m_pUIPage);
			FCYSAFEKILL(m_pGraph);
		}

		// ��������
		FCYSAFEKILL(m_pEngine);
	}
};

/*
#include "fcyOS\fcySocket.h"
#include "fcyNet\fcyHTTP.h"
#include "fcyParser\fcyXml.h"
*/

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(11532);
#endif

	/*
	fcySocket::InitSocket();

	fcyStream* pStream;
	
	// fcyNet::HTTPReadFile("api.bilibili.tv/view?type=xml&id=314&page=0", &pStream);
	// fcyNet::HTTPReadFile("comment.bilibili.tv/314.xml", &pStream);
	// http://interface.bilibili.tv/playurl?otype=xml&cid=<CID>&type=flv
	// fcyXml tXml(pStream);

	fcyNet::HTTPReadFile("pic.66wz.com/0/01/06/87/1068780_728634.jpg", &pStream);

	fcyFileStream* tStream = new fcyFileStream(L"e:\\test2.jpg", true);
	fcyStreamHelper::FillStream(pStream, tStream, pStream->GetLength());
	FCYSAFEKILL(tStream);
	
	FCYSAFEKILL(pStream);

	fcySocket::HaltSocket();
	*/
	
	MyApp tApp;

	return 0;
}
