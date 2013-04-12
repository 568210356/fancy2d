#pragma once

#include "fuiContext.h"
#include "fuiRenderer.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI���ԭ�¼�
////////////////////////////////////////////////////////////////////////////////
enum FUIMOUSEEVENT
{
	FUIMOUSEEVENT_MOVE,  ///< @brief ����ƶ�
	FUIMOUSEEVENT_LDOWN, ///< @brief �������
	FUIMOUSEEVENT_LUP,   ///< @brief ����ſ�
	FUIMOUSEEVENT_RDOWN, ///< @brief �Ҽ�����
	FUIMOUSEEVENT_RUP,   ///< @brief �Ҽ��ſ�
	FUIMOUSEEVENT_MDOWN, ///< @brief �м�����
	FUIMOUSEEVENT_MUP    ///< @brief �м��ſ�
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI����ԭ�¼�
////////////////////////////////////////////////////////////////////////////////
enum FUIKEYBOARDEVENT
{
	FUIKEYBOARDEVENT_KEYDOWN,  ///< @brief ��������
	FUIKEYBOARDEVENT_KEYUP,    ///< @brief �����ſ�
	FUIKEYBOARDEVENT_CHARINPUT ///< @brief ������ַ�
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI����
////////////////////////////////////////////////////////////////////////////////
class fuiHelper
{
private:
	static const F2DINPUTKEYCODE VKCodeToF2DKeyCodeTable[256];
public: // ��������
	static F2DINPUTKEYCODE VKCodeToF2DKeyCode(fByte VKCode);
	static fBool AttributeToBool(fcyXmlNode* pNode, fcStrW Attribute, fBool& pOut);
	static fBool AttributeToFloat(fcyXmlNode* pNode, fcStrW Attribute, fFloat& pOut);
	static fBool AttributeToRect(fcyXmlNode* pNode, fcStrW Attribute, fcyRect& pOut);
	static fBool AttributeToVec2(fcyXmlNode* pNode, fcStrW Attribute, fcyVec2& pOut);
	static fBool AttributeToVec3(fcyXmlNode* pNode, fcStrW Attribute, fcyVec3& pOut);
	static fBool AttributeToSprite(fuiContext* pContext, fcyXmlNode* pNode, fcStrW Attribute, f2dSprite* &pOut);
};

class fuiContainer;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI�ؼ�
////////////////////////////////////////////////////////////////////////////////
class fuiControl
{
	friend class fuiContainer;
private:
	static const fCharW ControlName[];
private: // ˽������
	std::wstring m_StyleName;///< @brief �������
	fuiContainer* m_pParent; ///< @brief ����������NULL��
	fcyRect m_UIRect;        ///< @brief UIλ��
	fcyVec2 m_UIMinSize;     ///< @brief UI��С��С
	fBool m_bVisiable;       ///< @brief �Ƿ����(render)
	fBool m_bUpdate;         ///< @brief �Ƿ����(update)
	fBool m_bClip;           ///< @brief �Ƿ����
protected: // ˽�в���
	/// @brief ���ÿؼ�����С��С
	/// @note  ����ǰ��СС����С��С������SetRect���õ���С��С
	void setMinSize(const fcyVec2& Size);
public: // �ؼ�����
	/// @brief ��ö������
	fuiControl* GetTopParent()const;
	/// @brief ���������
	fuiContext* GetContext();
	/// @brief �����С��С
	const fcyVec2& GetMinSize()const;
	/// @brief ��ø���
	fuiContainer* GetParent()const;
	/// @brief ���ø���
	void SetParent(fuiContainer* pParent);
	/// @brief ��ò�Σ�0Ϊ���ϲ�
	fuInt GetControlLayer();
	/// @brief ���ò��
	void SetControlLayer(fuInt Index);
	/// @brief �Ƿ����
	fBool IsVisiable()const;
	/// @brief ���ÿ���
	void SetVisiable(fBool bVisiable);
	/// @brief �Ƿ����
	fBool IsUpdatable()const;
	/// @brief ���ø���
	void SetUpdatable(fBool bUpdatable);
	/// @brief �Ƿ�ü�
	fBool IsClip()const;
	/// @brief ���òü�
	void SetClip(fBool bClip);
	/// @brief ��þ���
	const fcyRect& GetRect()const;
	/// @brief ���þ���
	void SetRect(const fcyRect& Range);
	/// @brief  ������ʽ
	/// @return ����ʽ����NULL
	fcStrW GetStyle();
	/// @brief �����ʽ
	void SetStyle(fcStrW pStyle);
	/// @brief ��ý���
	void GetFocus();
	/// @brief ��ʧ����
	void LostFocus();
	/// @brief     ��Ⱦ
	/// @param[in] pRenderer ��Ⱦ��
	void Render(fuiRenderer* pRenderer);
	/// @brief     ����
	/// @param[in] ElapsedTime ����ʱ��
	void Update(fDouble ElapsedTime);
	/// @brief     ���������Ϣ
	/// @param[in] Type �����Ϣ����
	/// @param[in] X    ��Ը��ؼ�λ��
	/// @param[in] Y    ��Ը��ؼ�λ��
	/// @return    �Ƿ������Ϣ
	fBool SendMouseEvent(FUIMOUSEEVENT Type, fFloat X, fFloat Y);
	/// @brief     ���ͼ�����Ϣ
	/// @param[in] Type    ������Ϣ����
	/// @param[in] KeyCode ���̴���
	/// @return    �Ƿ������Ϣ
	fBool SendKeyboardEvent(FUIKEYBOARDEVENT Type, F2DINPUTKEYCODE KeyCode);
protected: // �ɸ�д�¼�
	virtual void OnRender(fuiRenderer* pRenderer);      ///< @brief ��Ⱦ�¼�
	virtual void OnUpdate(fDouble ElapsedTime);         ///< @brief �����¼�
	virtual void OnResized(fcyRect& NewSize);           ///< @brief ��С�ı��¼�
	virtual void OnParentChanged(fuiContainer* pOld);   ///< @brief ������ı�
	virtual void OnStyleChanged(fcStrW NewStyleName);   ///< @brief ��۸ı�
	virtual void OnVisiableChanged();                   ///< @brief ���Ӹı�
	virtual fBool OnGetFocus();                         ///< @brief ��ý����¼�
	virtual void OnLostFocus();                         ///< @brief ��ʧ�����¼�
	virtual void OnMouseLeave();                        ///< @brief ����Ƴ��¼�
	virtual fBool OnMouseMove(fFloat X, fFloat Y);      ///< @brief ����ƶ��¼�
	virtual void OnLMouseUp(fFloat X, fFloat Y);        ///< @brief �������ſ�
	virtual fBool OnLMouseDown(fFloat X, fFloat Y);     ///< @brief ����������
	virtual void OnRMouseUp(fFloat X, fFloat Y);        ///< @brief ����Ҽ��ſ�
	virtual fBool OnRMouseDown(fFloat X, fFloat Y);     ///< @brief ����Ҽ�����
	virtual void OnMMouseUp(fFloat X, fFloat Y);        ///< @brief ����м��ſ�
	virtual fBool OnMMouseDown(fFloat X, fFloat Y);     ///< @brief ����м䰴��
	virtual void OnKeyUp(F2DINPUTKEYCODE KeyCode);      ///< @brief ���̰����ſ�
	virtual void OnKeyDown(F2DINPUTKEYCODE KeyCode);    ///< @brief ���̰�������
	virtual void OnCharInput(fCharW CharCode);          ///< @brief �����ַ�
	virtual void OnQuerySubControlOffset(fcyVec2& pOut);///< @brief ��ѯ�ӿؼ�����λ��
	virtual void OnQueryControlName(std::wstring& Out); ///< @brief ��ѯ�ؼ�������
	virtual const fcyRect& OnQueryClipRect();           ///< @brief ���زü�����
	virtual fuiContext* OnQueryContext();               ///< @brief ���������
public:
	fuiControl(fuiContainer* pParent);
	virtual ~fuiControl(void);
};
