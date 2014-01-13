////////////////////////////////////////////////////////////////////////////////
/// @file  fuiSliderBar.h
/// @brief fancyUI ˮƽ������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

#include "fuiImagedButton.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI ˮƽ������
////////////////////////////////////////////////////////////////////////////////
class fuiHSliderBar :
	public fuiControl
{
protected: // �ӿؼ�
	fcyRefPointer<fuiImagedButton> m_pSliderButton;
protected: // ����
	std::wstring m_BackBorderSprite;   // ��������
	std::wstring m_FrontBorderSprite;  // ǰ������
	fcyRect m_SliderBorder;            // �������߽�
	
	fuiPropertyAccessor<std::wstring> m_BackBorderSprite_Accessor;
	fuiPropertyAccessor<std::wstring> m_FrontBorderSprite_Accessor;
	fuiPropertyAccessor<fcyRect> m_SliderBorder;
protected: // ��ͼ����
	fcyRefPointer<fuiBorderSprite> m_BackBorderSprite;
	fcyRefPointer<fuiBorderSprite> m_FrontBorderSprite;

	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ʵ�ֽӿ�
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiHSliderBar(fuiPage* pRootPage, const std::wstring& Name);
	~fuiHSliderBar();
};
