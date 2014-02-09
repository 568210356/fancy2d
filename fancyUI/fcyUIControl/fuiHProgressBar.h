////////////////////////////////////////////////////////////////////////////////
/// @file  fuiProgressBar.h
/// @brief fancyUI ���������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI ���������
////////////////////////////////////////////////////////////////////////////////
class fuiHProgressBar :
	public fuiControl
{
protected: // ����
	std::wstring m_BackSprite;
	std::wstring m_LeftImage;
	std::wstring m_RightImage;
	std::wstring m_CenterImage;
	fcyColor m_BlendColor;
	float m_MaxValue;
	float m_MinValue;
	float m_Value;
	fcyRect m_ProgressMargin;

	fuiPropertyAccessor<std::wstring> m_BackSprite_Accessor;
	fuiPropertyAccessor<std::wstring> m_LeftImage_Accessor;
	fuiPropertyAccessor<std::wstring> m_RightImage_Accessor;
	fuiPropertyAccessor<std::wstring> m_CenterImage_Accessor;
	fuiPropertyAccessor<fcyColor> m_BlendColor_Accessor;
	fuiPropertyAccessor<float> m_MaxValue_Accessor;
	fuiPropertyAccessor<float> m_MinValue_Accessor;
	fuiPropertyAccessor<float> m_Value_Accessor;
	fuiPropertyAccessor<fcyRect> m_ProgressMargin_Accessor;
protected: // ��ͼ��Դ
	fcyRefPointer<fuiBorderSprite> m_pBackSprite;
	fcyRefPointer<fuiSprite> m_pLeftImage;
	fcyRefPointer<fuiSprite> m_pRightImage;
	fcyRefPointer<fuiSprite> m_pCenterImage;
	float m_LeftImageWidth;
	float m_RightImageWidth;
	float m_CenterImageWidth;
	float m_Percent;
	
	void UpdateValue();

	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ʵ�ֽӿ�
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiHProgressBar(fuiPage* pRootPage, const std::wstring& Name);
	~fuiHProgressBar();
};
