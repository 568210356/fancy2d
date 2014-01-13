////////////////////////////////////////////////////////////////////////////////
/// @file  fuiLabelEx.h
/// @brief fancyUI �߼���ǩ
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI �߼���ǩ
////////////////////////////////////////////////////////////////////////////////
class fuiLabelEx :
	public fuiControl
{
	struct DrawCmd // ��ͼ����
	{
		enum TYPE
		{
			TYPE_NULL,
			TYPE_COLOR, // �ı�������ɫ
			TYPE_FONT   // �ı�����
		};

		TYPE Type;
		union
		{
			struct
			{
				fByte b;
				fByte g;
				fByte r;
				fByte a;
			} ColorData;
			f2dFontProvider* FontData;
		};
	};
protected: // ��ͼ����
	std::vector<std::wstring> m_DrawText; // �����ı�
	std::vector<DrawCmd> m_DrawCmd;       // ��������
	std::unordered_map<std::wstring, fcyRefPointer<fuiFont>> m_FontList; // �������õ�����
	float m_LineHeight;                   // �и�
	float m_MaxAscender;                  // ����Ͻ�
	fuInt m_TotalTextLength;              // ���ı�����
	float m_YOffset;                      // Y�����ƫ��
	fcyVec2 m_PenEndPos;                  // ���λ��

	// �ַ���ʾ����
	fuInt m_CurDisplayCount;               // ��ǰ��ʾ�ı�����
	float m_CharWait;                      // ��ǰ�ȴ�ʱ��
protected: // ����
	std::wstring m_Text;
	std::wstring m_FontName;
	fcyColor m_FontColor;
	fcyRefPointer<fuiFont> m_Font;
	float m_ZValue;
	float m_CharDisplaySpeed;
	int m_TotalAlpha;  // ����Alpha [0~255]

	fuiPropertyAccessor<std::wstring> m_Text_Accessor;
	fuiPropertyAccessor<std::wstring> m_FontName_Accessor;
	fuiPropertyAccessor<fcyColor> m_FontColor_Accessor;
	fuiPropertyAccessor<float> m_ZValue_Accessor;
	fuiPropertyAccessor<float> m_CharDisplaySpeed_Accessor;
	fuiPropertyAccessor<int> m_TotalAlpha_Accessor;
	fuiPropertyAccessor<float> m_YOffset_Accessor;          // Y�����ƫ��

	// ֻ������
	fuiPropertyAccessor<float> m_LineHeight_Accessor;       // �и�
	fuiPropertyAccessor<float> m_MaxAscender_Accessor;      // ����Ͻ�
	fuiPropertyAccessor<fcyVec2> m_PenEndPos_Accessor;      // ���λ��
protected:
	fcyVec2 drawText(f2dGraphics2D* pGraph, const std::wstring& Text, int Count, f2dFontProvider* pFontProvider, const fcyColor& BlendColor, const fcyVec2& StartPos, float Margin = 2.f);
	fcyVec2 calcuTextEndDrawPos();
protected: // �¼�
	void OnTextChanged(fuiControl* pThis, fuiEventArgs* pArgs);
	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ʵ�ֽӿ�
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiLabelEx(fuiPage* pRootPage, const std::wstring& Name);
	~fuiLabelEx();
};
