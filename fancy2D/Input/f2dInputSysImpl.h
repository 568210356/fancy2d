////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInputSysImpl.h
/// @brief fancy2D����ϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInputSysAPI.h"

#include "../f2dInputSys.h"

#include <vector>

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief ����ϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputSysImpl :
	public fcyRefObjImpl<f2dInputSys>
{
private:
	f2dEngineImpl* m_pEngine;

	f2dInputSysAPI m_API;

	IDirectInput8* m_pDInput;
	HWND m_hWinHandle;
	std::vector<DIDEVICEINSTANCEW> m_MouseList;    // ����б�
	std::vector<DIDEVICEINSTANCEW> m_KeyboardList; // �����б�
	std::vector<DIDEVICEINSTANCEW> m_GameCtrlList; // �������б�
private:
	static BOOL PASCAL enumMouse(LPCDIDEVICEINSTANCE pInfo, void* pThis);    // ö�����
	static BOOL PASCAL enumKeyboard(LPCDIDEVICEINSTANCE pInfo, void* pThis); // ö�ټ���
	static BOOL PASCAL enumGameCtrl(LPCDIDEVICEINSTANCE pInfo, void* pThis); // ö����Ϸ�ֱ�
private:
	void enumDevice();  // ö�������豸
public:
	fuInt GetDeviceCount(F2DINPUTDEVTYPE Type);
	fcStrW GetDeviceName(F2DINPUTDEVTYPE Type, fuInt Index);
	fcStrW GetDeviceProductName(F2DINPUTDEVTYPE Type, fuInt Index);
	
	fResult CreateMouse(fInt DevIndex, fBool bGlobalFocus, f2dInputMouse** pOut);
	fResult CreateKeyboard(fInt DevIndex, fBool bGlobalFocus, f2dInputKeyboard** pOut);
	fResult CreateJoystick(fInt DevIndex, fBool bGlobalFocus, f2dInputJoystick** pOut);
public:
	f2dInputSysImpl(f2dEngineImpl* pEngine);
protected:
	~f2dInputSysImpl();
};
