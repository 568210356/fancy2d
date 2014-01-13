////////////////////////////////////////////////////////////////////////////////
/// @file  fuiImagedButton.h
/// @brief fancyUI ͼ�ΰ�ť
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"
#include "fuiImageBox.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI ͼ�ΰ�ť
////////////////////////////////////////////////////////////////////////////////
class fuiImagedButton :
	public fuiImageBox
{
protected: // ����
	std::wstring m_ActiveImage;
	std::wstring m_ClickImage;
	fcyRect m_MouseEventMargin;

	fuiPropertyAccessor<std::wstring> m_ActiveImage_Accessor;
	fuiPropertyAccessor<std::wstring> m_ClickImage_Accessor;
	fuiPropertyAccessor<fcyRect> m_MouseEventMargin_Accessor;
protected: // ��ͼ��Դ
	bool m_bIsMoveIn;
	bool m_bIsMouseDown;

	fcyRefPointer<fuiSprite> m_pActiveImageSprite;
	fcyRefPointer<fuiSprite> m_pClickImageSprite;
	
	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
protected: // ʵ������¼�
	void OnMouseMove(fuiControl* pThis, fuiEventArgs* pArgs);
	void OnMouseLeave(fuiControl* pThis, fuiEventArgs* pArgs);
	void OnMouseLButtonDown(fuiControl* pThis, fuiEventArgs* pArgs);
	void OnMouseLButtonUp(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ����ImageBoxʵ��
	void Render(fuiGraphics* pGraph);
	fBool HitTest(const fcyVec2& Pos);
public:
	fuiImagedButton(fuiPage* pRootPage, const std::wstring& Name);
	~fuiImagedButton();
};
