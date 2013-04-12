////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInputSysImpl.h
/// @brief fancy2D����ϵͳ�ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dInputSys.h"

#include <vector>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief ��̬����DInput
////////////////////////////////////////////////////////////////////////////////
class f2dInputSysAPI
{
private:
	typedef HRESULT (WINAPI *pDLLEntry_DirectInput8Create)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
private:
	HMODULE m_hModule;

	pDLLEntry_DirectInput8Create m_Entry_pDirectInput8Create;
public:
	HRESULT DLLEntry_DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
public:
	f2dInputSysAPI();
	~f2dInputSysAPI();
};

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

////////////////////////////////////////////////////////////////////////////////
/// @brief �����豸ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputKeyboardImpl :
	public fcyRefObjImpl<f2dInputKeyboard>
{
	friend class f2dInputSysImpl;
private:
	static const fuInt BufferSize; 
	static const DIDATAFORMAT DIDF_Keyboard;
	static const DIOBJECTDATAFORMAT DIODF_Keyboard[256];
private:
	IDirectInputDevice8* m_pDev;
	f2dInputKeyboardEventListener* m_pListener;
	fBool m_ButtonState[256];
public:
	f2dInputMouse* ToMouse();
	f2dInputKeyboard* ToKeyboard();
	f2dInputJoystick* ToJoystick();

	fResult UpdateState(); 

	f2dInputKeyboardEventListener* GetListener();
	fResult SetListener(f2dInputKeyboardEventListener* pListener);
	
	fBool IsKeyDown(F2DINPUTKEYCODE KeyCode);
protected: // ��ֱֹ��new/delete
	f2dInputKeyboardImpl(IDirectInput8* pDev, HWND Win, const GUID& pGUID, fBool bGlobalFocus);
	~f2dInputKeyboardImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Ϸ�ֱ�ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputJoystickImpl :
	public fcyRefObjImpl<f2dInputJoystick>
{
	friend class f2dInputSysImpl;
private:
	static const fuInt BufferSize;
	static const DIDATAFORMAT DIDF_Joystick;
	static const DIOBJECTDATAFORMAT DIODF_Joystick[44];
private:
	IDirectInputDevice8* m_pDev;
	f2dInputJoystickEventListener* m_pListener;

	// ��Χֵ
	int m_lXHalf;
	int m_lXHalfLen;
	int m_lYHalf;
	int m_lYHalfLen;
	int m_lZHalf;
	int m_lZHalfLen;
	int m_lRxHalf;
	int m_lRxHalfLen;
	int m_lRyHalf;
	int m_lRyHalfLen;
	int m_lRzHalf;
	int m_lRzHalfLen;

	// ״̬
	float m_lX;               // X��λ��
    float m_lY;               // Y��λ��
    float m_lZ;               // Z��λ��
    float m_lRx;              // X����ת
    float m_lRy;              // Y����ת
    float m_lRz;              // Z����ת
	bool m_ButtonDown[32];    // ��ť״̬
	int m_Slider[2];          // Slider
	fuInt m_POV[4];            // POV
private:
	void initStates();
public:
	f2dInputMouse* ToMouse();
	f2dInputKeyboard* ToKeyboard();
	f2dInputJoystick* ToJoystick();

	fResult UpdateState(); 

	f2dInputJoystickEventListener* GetListener();
	fResult SetListener(f2dInputJoystickEventListener* pListener);

	// ״̬��ѯ
	fFloat GetXPosition();
	fFloat GetYPosition();
	fFloat GetZPosition();
	fFloat GetXRotation();
	fFloat GetYRotation();
	fFloat GetZRotation();
	fBool IsButtonDown(fuInt Index);
	fInt GetSlider(fuInt Index);
	fuInt GetPOV(fuInt Index);

	fFloat GetDeadZone();
	fResult SetDeadZone(fFloat Percent);
	fFloat GetSaturation();
	fResult SetSaturation(fFloat Percent);
protected: // ��ֱֹ��new/delete
	f2dInputJoystickImpl(IDirectInput8* pDev, HWND Win, const GUID& pGUID, fBool bGlobalFocus);
	~f2dInputJoystickImpl();
};

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
