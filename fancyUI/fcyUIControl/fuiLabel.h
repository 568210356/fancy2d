#pragma once
#include "../fcyUIBase/fuiControl.h"

#include <vector>
#include <string>

class fuiLabel :
	public fuiControl
{
private:
	static const fCharW ControlName[];
protected:
	enum LABELHSTYLE  // ˮƽ��ʽ
	{
		LABELHSTYLE_LEFT,
		LABELHSTYLE_CENTER,
		LABELHSTYLE_RIGHT
	};
	enum LABELVSTYLE  // ��ֱ��ʽ
	{
		LABELVSTYLE_TOP,
		LABELVSTYLE_CENTER,
		LABELVSTYLE_BOTTOM
	};
	struct LabelStyle
	{
		LABELHSTYLE HStyle;
		LABELVSTYLE VStyle;
		fcyColor FontColor;
		f2dFontRenderer* pFont;

		LabelStyle()
			: pFont(NULL) {}
	};
protected:
	LabelStyle m_Style;
	float m_FontHeight;

	std::vector<std::wstring> m_Caption;  // ����
	std::vector<float> m_LineLength;      // ���г���

	fcyVec2 m_RefPos;  // �ο�����λ��
private:
	void recalcuPos(const fcyRect& UIRect);
	void recalcuLineLength();
public:
	void GetCaption(std::wstring& Out);
	void SetCaption(fcStrW Text);
	fuInt GetLineCount();
	fcyColor GetFontColor();
	void SetFontColor(const fcyColor& Color);
protected: // ��д��Ϣ
	void OnRender(fuiRenderer* pRenderer);
	void OnResized(fcyRect& NewSize);
	void OnStyleChanged(fcStrW NewStyleName);
	void OnQueryControlName(std::wstring& Out);

	// ��͸���������κ���Ϣ
	fBool OnMouseMove(fFloat X, fFloat Y) { return false; }
	fBool OnLMouseDown(fFloat X, fFloat Y) { return false; }
	fBool OnRMouseDown(fFloat X, fFloat Y) { return false; }
	fBool OnMMouseDown(fFloat X, fFloat Y) { return false; }
public:
	fuiLabel(fuiContainer* pContainer);
	~fuiLabel(void);
};
