////////////////////////////////////////////////////////////////////////////////
/// @file  fcyRefObj.h
/// @brief ������ʵ�������ü����ӿ�
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyType.h"

#include <Windows.h>

#define FCYREFOBJ

////////////////////////////////////////////////////////////////////////////////
/// @brief ���ü����ӿڶ���
/// @note  AddRef��Release����Ӧ������
////////////////////////////////////////////////////////////////////////////////
struct fcyRefObj
{
	virtual void AddRef()=0;  ///< @brief ���ӽӿڵ����ü���
	virtual void Release()=0; ///< @brief ���ٽӿڵ����ü���
	                          ///< @note  ����������0ʱ���ٶ���
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ���ü����ӿ�ʵ��
/// @note  ʹ��ģ����д��븴�÷�ֹ�������μ̳�
////////////////////////////////////////////////////////////////////////////////
template<class T>
class fcyRefObjImpl : 
	public T
{
private:
	fuInt m_cRef;
public:
	/// @brief AddRefʵ��
	virtual void AddRef()
	{
		InterlockedIncrement(&m_cRef);
	}

	/// @brief Releaseʵ��
	virtual void Release()
	{
		fuInt tRet = InterlockedDecrement(&m_cRef);
		if(tRet == 0)
			delete this;
	}
public:
	fcyRefObjImpl()
		: m_cRef(1) {}
	virtual ~fcyRefObjImpl() {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ����ָ��
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class fcyRefPointer
{
protected:
	T* m_pPointer;
public:
	bool operator==(const fcyRefPointer& Right)const
	{
		return (m_pPointer == Right);
	}
	fcyRefPointer& operator=(const fcyRefPointer& Right)
	{
		if(m_pPointer != Right.m_pPointer)
		{
			FCYSAFEKILL(m_pPointer);
			m_pPointer = Right.m_pPointer;
			if(m_pPointer)
				m_pPointer->AddRef();
		}
		return *this;
	}
	T*& operator->()
	{
		return m_pPointer;
	}
	T*& operator*()
	{
		return m_pPointer;
	}
	T** operator&()
	{
		return &m_pPointer;
	}
	operator T*()
	{
		return m_pPointer;
	}
public:
	fcyRefPointer()
		: m_pPointer(NULL) {}
	fcyRefPointer(T* pObj)
		: m_pPointer(pObj) 
	{
		if(pObj)
			pObj->AddRef();
	}
	fcyRefPointer(const fcyRefPointer& Right)
		: m_pPointer(Right.m_pPointer)
	{
		if(pObj)
			pObj->AddRef();
	}
	~fcyRefPointer()
	{
		FCYSAFEKILL(m_pPointer);
	}
};
