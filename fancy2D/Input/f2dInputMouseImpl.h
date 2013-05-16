////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInputMouseImpl.h
/// @brief fancy2D����ϵͳ ���ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dInputSys.h"

#include "f2dInputSysAPI.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief ����豸ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputMouseImpl :
	public fcyRefObjImpl<f2dInputMouse>
{
	friend class f2dInputSysImpl;
private:
	static const fuInt BufferSize;
	static const DIDATAFORMAT DIDF_Mouse;
	static const DIOBJECTDATAFORMAT DIODF_Mouse[7];
private:
	IDirectInputDevice8* m_pDev;
	f2dInputMouseEventListener* m_pListener;
	
	int m_TotalOffsetX;
	int m_TotalOffsetY;
	int m_TotalOffsetZ;
	bool m_BtnState[8];
public: // �ӿ�ʵ��
	f2dInputMouse* ToMouse();
	f2dInputKeyboard* ToKeyboard();
	f2dInputJoystick* ToJoystick();

	fResult UpdateState(); 

	f2dInputMouseEventListener* GetListener();
	fResult SetListener(f2dInputMouseEventListener* pListener);
	
	fBool IsLeftBtnDown();
	fBool IsRightBtnDown();
	fBool IsMiddleBtnDown();
	fBool IsAdditionBtnDown(fuInt Index);
	fInt GetOffsetX();
	fInt GetOffsetY();
	fInt GetOffsetZ();
protected: // ��ֱֹ��new/delete
	f2dInputMouseImpl(IDirectInput8* pDev, HWND Win, const GUID& pGUID, fBool bGlobalFocus);
	~f2dInputMouseImpl();
};