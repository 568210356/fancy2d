////////////////////////////////////////////////////////////////////////////////
/// @file  fuiBorder.h
/// @brief fancyUI �߿�
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI �߿�
////////////////////////////////////////////////////////////////////////////////
class fuiBorder :
	public fuiControl
{
protected: // ����
	std::wstring m_BorderImage;
	fcyColor m_BlendColor;
	
	fuiPropertyAccessor<std::wstring> m_BorderImage_Accessor;
	fuiPropertyAccessor<fcyColor> m_BlendColor_Accessor;
protected: // ��ͼ��Դ
	fcyRefPointer<fuiBorderSprite> m_pBorderImageSprite;
	
	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ʵ�ֽӿ�
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiBorder(fuiPage* pRootPage, const std::wstring& Name);
	~fuiBorder();
};
