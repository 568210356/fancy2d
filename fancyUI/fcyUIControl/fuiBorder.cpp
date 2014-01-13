#include "fuiBorder.h"

#include "fuiExceptionMacro.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

fuiBorder::fuiBorder(fuiPage* pRootPage, const std::wstring& Name)
	: fuiControl(pRootPage, Name)
{
	// Ĭ������
	SetClip(false);

	m_BorderImage_Accessor = fuiPropertyAccessor<wstring>(
		&m_BorderImage,
		fuiPropertyAccessorHelper<wstring>::DefaultGetter,
		[&](const std::wstring& PropData, std::wstring* Value) {
			m_BorderImage = PropData;

			ExecEvent(L"OnStyleChanged");
		}
	);
	m_BlendColor_Accessor = fuiPropertyAccessor<fcyColor>(&m_BlendColor);

	// ע������
	RegisterProperty(L"BorderImage", &m_BorderImage_Accessor);
	RegisterProperty(L"BlendColor", &m_BlendColor_Accessor);

	// ע���¼�
	GetEvent(L"OnStyleChanged") += fuiDelegate::EventCallBack(this, &fuiBorder::OnStyleChanged);
}

fuiBorder::~fuiBorder()
{}

void fuiBorder::OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs)
{
	fcyRefPointer<fuiBorderSprite> tBorderSprite;

	FUIGETRESANDCHECK(m_BorderImage, tBorderSprite, fuiBorderSprite, fuiRes::RESTYPE_BORDERSPRITE, "fuiBorder::OnStyleChanged");

	m_pBorderImageSprite = tBorderSprite;
}

void fuiBorder::Update(fDouble ElapsedTime)
{
	fuiControl::Update(ElapsedTime);
}

void fuiBorder::Render(fuiGraphics* pGraph)
{
	if(m_pBorderImageSprite)
		m_pBorderImageSprite->Draw(pGraph, fcyRect(0.f, 0.f, GetWidth(), GetHeight()), m_BlendColor);

	fuiControl::Render(pGraph);
}
