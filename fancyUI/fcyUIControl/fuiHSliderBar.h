#pragma once
#include "../fcyUIBase/fuiContainer.h"
#include "../fcyUIControl/fuiHProgressBar.h"
#include "../fcyUIControl/fuiSpriteButton.h"

class fuiHSliderBarButton :
	public fuiSpriteButton
{
	friend class fuiHSliderBar;
private:
	static const fCharW ControlName[];
protected:
	float m_ButtonPos;

	bool m_bMyMouseDown;
	fcyVec2 m_MouseEnable;

	// �ص�
	std::function<void(fFloat)> m_Evt_OnValueChanged;
	std::function<void(void)> m_Evt_OnStartDrag;
	std::function<void(void)> m_Evt_OnEndDrag;
private:
	fFloat calcuMaxLen(const fcyRect& ParentUISize);                    ///< @brief ������϶���Χ����
public:
	void UpdatePos(const fcyRect& ParentNewSize);                       ///< @brief ����λ��
	fFloat GetButtonPos();                                              ///< @brief ��ð�ťλ��[0-1]
	void SetButtonPos(fFloat Pos, fBool ExecEvent=true);                ///< @brief ���ð�ťλ��[0-1]
	void SetEvt_OnValueChanged(const std::function<void(fFloat)>& Evt); ///< @brief ���ûص�
	void SetEvt_OnStartDrag(const std::function<void(void)>& Evt);      ///< @brief ���ûص�
	void SetEvt_OnEndDrag(const std::function<void(void)>& Evt);        ///< @brief ���ûص�
protected: // ��д��Ϣ
	fBool OnMouseMove(fFloat X, fFloat Y);
	void OnLMouseUp(fFloat X, fFloat Y);
	fBool OnLMouseDown(fFloat X, fFloat Y);
	void OnQueryControlName(std::wstring& Out);
protected:
	fuiHSliderBarButton(fuiContainer* pContainer);
	~fuiHSliderBarButton();
};

class fuiHSliderBar :
	public fuiContainer
{
	friend class fuiHSliderBarButton;
private:
	struct HSliderBarStyle
	{
		fcyVec2 ProgressBarMargin;
		fcyVec2 SpriteButtonMargin;
	};
private:
	static const fCharW ControlName[];
protected:
	HSliderBarStyle m_Style;

	fuiHProgressBar* m_pProgressBar;
	fuiHSliderBarButton* m_pSpriteButton;
private:
	void recalcuRect(const fcyRect& UISize);
public:
	fFloat GetProgPos();                                                ///< @brief ��ý�����λ��[0-1]
	void SetProgPos(fFloat Pos);                                        ///< @brief ���ý�����λ��[0-1]
	fFloat GetButtonPos();                                              ///< @brief ��ð�ťλ��[0-1]
	void SetButtonPos(fFloat Pos, fBool ExecEvent=true);                ///< @brief ���ð�ťλ��[0-1]
	void SetEvt_OnValueChanged(const std::function<void(fFloat)>& Evt); ///< @brief ���ûص�
	void SetEvt_OnStartDrag(const std::function<void(void)>& Evt);      ///< @brief ���ûص�
	void SetEvt_OnEndDrag(const std::function<void(void)>& Evt);        ///< @brief ���ûص�
protected: // ��д��Ϣ
	void OnResized(fcyRect& NewSize);
	void OnStyleChanged(fcStrW NewStyleName);
	void OnQueryControlName(std::wstring& Out);

	fBool OnMouseMove(fFloat X, fFloat Y);
	fBool OnLMouseDown(fFloat X, fFloat Y);
public:
	fuiHSliderBar(fuiContainer* pParent);
	~fuiHSliderBar(void);
};
