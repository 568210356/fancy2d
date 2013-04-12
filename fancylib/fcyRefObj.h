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
