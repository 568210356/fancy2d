#pragma once
#include "fuiControl.h"

#include <list>

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI����
////////////////////////////////////////////////////////////////////////////////
class fuiContainer :
	public fuiControl
{
	friend class fuiControl;
private:
	static const fCharW ControlName[];
protected:
	// === �����б� ===
	std::list<fuiControl*> m_SubControl;                                  ///< @brief �ӿؼ����ͷΪ��㣬Index=0
	std::vector<std::list<fuiControl*>::iterator*> m_IterList;            ///< @brief ���������
	std::vector<std::list<fuiControl*>::reverse_iterator*> m_RevIterList; ///< @brief ���������

	// === ��Ϣ���� ===
	fuiControl* m_pFocus;       ///< @brief ��ǰ�������
	fuiControl* m_pMouseObj;    ///< @brief ��ǰ���λ�ô��Ķ���
	fuiControl* m_pMouseCatch;  ///< @brief ��ǰ�����������Ϣ�Ķ���
	FUIMOUSEEVENT m_MouseEvent; ///< @brief ������������Ϣ
private:
	void updateMouseObj(fFloat X, fFloat Y);                 ///< @brief ������괦����
protected: // ����Control�������õ��ڲ�����
	void appendControl(fuiControl* pControl);                ///< @brief ׷���ӿؼ� 
	void removeControl(fuiControl* pControl);                ///< @brief �Ƴ��ӿؼ�
	fuInt getControlIndex(fuiControl* pControl);             ///< @brief ��ÿؼ�����
	void setControlIndex(fuiControl* pControl, fuInt Index); ///< @brief ���ÿؼ�����
	void clearControls();                                    ///< @brief ������пؼ�
	void subControlLostFocus(fuiControl* pControl);          ///< @brief �ӿؼ���ʧ����
	void subControlGetFocus(fuiControl* pControl);           ///< @brief �ӿؼ���ý���
	void subControlResized(fuiControl* pControl);            ///< @brief �ӿؼ���С�ı�
protected: // �ɸ�д����
	virtual void OnSubControlLostFocus(fuiControl* pControl);///< @brief �Ӷ���ʧ����
	virtual void OnSubControlGetFocus(fuiControl* pControl); ///< @brief �Ӷ���ʧ����
	virtual void OnSubControlResized(fuiControl* pControl);  ///< @brief �Ӷ����С����
protected: // ��д���෽��
	virtual void OnRender(fuiRenderer* pRenderer);
	virtual void OnUpdate(fDouble ElapsedTime);
	virtual fBool OnGetFocus();
	virtual void OnLostFocus();
	virtual void OnMouseLeave();
	virtual fBool OnMouseMove(fFloat X, fFloat Y);
	virtual void OnLMouseUp(fFloat X, fFloat Y);
	virtual fBool OnLMouseDown(fFloat X, fFloat Y);
	virtual void OnRMouseUp(fFloat X, fFloat Y);
	virtual fBool OnRMouseDown(fFloat X, fFloat Y);
	virtual void OnMMouseUp(fFloat X, fFloat Y);
	virtual fBool OnMMouseDown(fFloat X, fFloat Y);
	virtual void OnKeyUp(F2DINPUTKEYCODE KeyCode);
	virtual void OnKeyDown(F2DINPUTKEYCODE KeyCode);
	virtual void OnCharInput(fCharW CharCode);
	virtual void OnQueryControlName(std::wstring& Out);
public:
	fuiContainer(fuiContainer* pParnet);
	~fuiContainer(void);
};
