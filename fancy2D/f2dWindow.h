////////////////////////////////////////////////////////////////////////////////
/// @file  f2dWindow.h
/// @brief fancy2D��Ⱦ���ڽӿڶ���
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInterface.h"

/// @addtogroup f2d��Ⱦ����
/// @brief fancy2d������Ⱦ����
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2d��Ⱦ���ڱ߿�����
////////////////////////////////////////////////////////////////////////////////
enum F2DWINBORDERTYPE
{
	F2DWINBORDERTYPE_NONE,
	F2DWINBORDERTYPE_FIXED,
	F2DWINBORDERTYPE_SIZEABLE
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ�����¼�������
/// @note  ͨ����д�������ʵ����Ϣ�ص�
////////////////////////////////////////////////////////////////////////////////
struct f2dWindowEventListener
{
	/// @brief ���ڹر��¼�
	virtual void OnClose() {}

	/// @brief �����ػ��¼�
	virtual void OnPaint() {}

	/// @brief     ���ڴ�С�ı��¼�
	/// @param[in] ClientWidth  �µĿͻ������
	/// @param[in] ClientHeight �µĿͻ����߶�
	virtual void OnSize(fuInt ClientWidth, fuInt ClientHeight) {}

	/// @brief     ��������
	/// @param[in] KeyCode �������룬�����MSDN
	/// @param[in] Flag    �������ԣ������MSDN
	virtual void OnKeyDown(fuInt KeyCode, fuInt Flag) {}

	/// @brief     �����ſ�
	/// @param[in] KeyCode �������룬�����MSDN
	/// @param[in] Flag    �������ԣ������MSDN
	virtual void OnKeyUp(fuInt KeyCode, fuInt Flag) {}

	/// @brief     �ַ�����
	/// @param[in] CharCode �ַ�
	/// @param[in] Flag     �������ԣ������MSDN
	virtual void OnCharInput(fCharW CharCode, fuInt Flag) {}

	/// @brief ���뷨��ʼƴд
	virtual void OnIMEStartComposition() {}

	/// @brief ���뷨����ƴд
	virtual void OnIMEEndComposition() {}

	/// @brief     ���뷨����ƴд
	/// @param[in] CharCode �ַ�
	/// @param[in] Flag     �������ԣ������MSDN
	virtual void OnIMEComposition(fCharW CharCode, fuInt Flag) {}

	/// @brief     ����ƶ�
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseMove(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ���ֹ���
	/// @param[in] X     ������λ��
	/// @param[in] Y     �������λ��
	/// @param[in] Wheel ���ֹ�������
	/// @param[in] Flag  �������ԣ������MSDN
	virtual void OnMouseWheel(fShort X, fShort Y, fFloat Wheel, fuInt Flag) {}

	/// @brief     ����������
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseLBDown(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     �������ſ�
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseLBUp(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ������˫��
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseLBDouble(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����м�����
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseMBDown(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����м��ſ�
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseMBUp(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����м�˫��
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseMBDouble(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����Ҽ�����
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseRBDown(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����Ҽ��ſ�
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseRBUp(fShort X, fShort Y, fuInt Flag) {}

	/// @brief     ����Ҽ�˫��
	/// @param[in] X    ������λ��
	/// @param[in] Y    �������λ��
	/// @param[in] Flag �������ԣ������MSDN
	virtual void OnMouseRBDouble(fShort X, fShort Y, fuInt Flag) {}

	/// @brief ��ý���
	virtual void OnGetFocus() {}

	/// @brief ��ʧ����
	virtual void OnLostFocus() {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ����
////////////////////////////////////////////////////////////////////////////////
struct f2dWindow
{
	/// @brief ���ؼ�����
	virtual f2dWindowEventListener* GetListener()=0;

	/// @brief ���ü�����
	virtual fResult SetListener(f2dWindowEventListener* pListener)=0;

	/// @brief   ����Windows���ھ��
	/// @note    ��Ҫǿת��HWND
	/// @warning �����������Ӧ������ʹ�ñ�����
	virtual fInt GetHandle()=0;

	/// @brief ���ر߿�����
	virtual F2DWINBORDERTYPE GetBorderType()=0;

	/// @brief ���ñ߿�����
	virtual fResult SetBorderType(F2DWINBORDERTYPE Type)=0;

	/// @brief ���ش��ڱ���
	virtual fcStrW GetCaption()=0;

	/// @brief ���ô��ڱ���
	/// @note  ������1024���ַ�
	virtual fResult SetCaption(fcStrW Caption)=0;

	/// @brief �����Ƿ�ɼ�
	virtual fBool GetVisiable()=0;

	/// @brief �����Ƿ�ɼ�
	virtual fResult SetVisiable(fBool Visiable)=0;

	/// @brief ���ش���λ�ã����߿�
	virtual fcyRect GetRect()=0;

	/// @brief ���ô���λ�ã����߿�
	virtual fResult SetRect(const fcyRect& Range)=0;

	/// @brief ���ش��ڿͻ���λ��
	virtual fcyRect GetClientRect()=0;

	/// @brief ���ô��ڿͻ���λ��
	virtual fResult SetClientRect(const fcyRect& Range)=0;

	/// @brief �ƶ�����Ļ����
	virtual void MoveToCenter()=0;

	/// @brief �Ƿ��ö�
	virtual fBool IsTopMost()=0;

	/// @brief �����ö�
	virtual fResult SetTopMost(fBool TopMost)=0;
};

/// @}
