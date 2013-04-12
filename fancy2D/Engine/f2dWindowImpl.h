////////////////////////////////////////////////////////////////////////////////
/// @file  f2dWindowImpl.h
/// @brief fancy2D��Ⱦ���ڽӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dWindow.h"

#include <string>
#include <unordered_map>

#include <Windows.h>

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief ������
////////////////////////////////////////////////////////////////////////////////
class f2dWindowClass
{
	friend class f2dWindowImpl;
private:
	std::wstring m_ClsName;
private:
	static std::unordered_map<HWND, f2dWindowImpl*> s_WindowCallBack;
	static LRESULT CALLBACK WndProc(HWND Handle, UINT Msg, WPARAM wParam, LPARAM lParam);
public:
	fcStrW GetName()const; // ��ô���������
	fResult CreateRenderWindow(f2dEngineImpl* pEngine, const fcyRect& Pos, fcStrW Title, fBool Visiable, F2DWINBORDERTYPE Border, f2dWindowImpl** pOut); // ��������
public:
	f2dWindowClass(fcStrW ClassName);
	~f2dWindowClass();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ����DC
////////////////////////////////////////////////////////////////////////////////
class f2dWindowDC
{
protected:
	HBITMAP	m_hBmp;
	HDC		m_hDC;
	char*   m_pBits;

	fInt m_Width;
	fInt m_Height;
public:
	void Delete();
	void Create(int nWidth, int nHeight);
	HDC GetSafeHdc(void){
		return m_hDC;
	}
	HBITMAP GetBmpHandle(void){
		return m_hBmp;
	}
	DWORD* GetBits(void){
		return (DWORD*)m_pBits;
	}
	fInt GetWidth()
	{
		return m_Width;
	}
	fInt GetHeight()
	{
		return m_Height;
	}
public:
	f2dWindowDC();
    ~f2dWindowDC();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Ⱦ����
////////////////////////////////////////////////////////////////////////////////
class f2dWindowImpl :
	public fcyRefObjImpl<f2dWindow>
{
	friend class f2dWindowClass;
private:
	// ״̬
	HWND m_hWnd;
	bool m_bShow;
	std::wstring m_CaptionText;

	// ������
	f2dWindowEventListener* m_pListener;
public: // �ӿ�ʵ��
	f2dWindowEventListener* GetListener();
	fResult SetListener(f2dWindowEventListener* pListener);

	fInt GetHandle();

	F2DWINBORDERTYPE GetBorderType();
	fResult SetBorderType(F2DWINBORDERTYPE Type);
	fcStrW GetCaption();
	fResult SetCaption(fcStrW Caption);
	fBool GetVisiable();
	fResult SetVisiable(fBool Visiable);
	fcyRect GetRect();
	fResult SetRect(const fcyRect& Range);
	fcyRect GetClientRect();
	fResult SetClientRect(const fcyRect& Range);
	void MoveToCenter();
	fBool IsTopMost();
	fResult SetTopMost(fBool TopMost);
protected:
	f2dWindowImpl(f2dWindowClass* WinCls, const fcyRect& Pos, fcStrW Title, fBool Visiable, F2DWINBORDERTYPE Border);
	~f2dWindowImpl();
};
