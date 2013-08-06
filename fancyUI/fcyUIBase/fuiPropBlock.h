////////////////////////////////////////////////////////////////////////////////
/// @file  fuiPropBlock.h
/// @brief fancyUI ���Կ�
/// @note  ���ڱ���ؼ�����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyRefObj.h>
#include <fcyException.h>

#include "fuiProperty.h"

class fuiControl;

/// @brief ���Կ�
/// @note  ���ڱ���ؼ�����״̬
class fuiPropBlock
{
	friend class fuiPropBlock;
protected:
	fuiControl* m_pControl;

	std::unordered_map<std::wstring, std::wstring> m_ControlProp;
	std::vector<fuiPropBlock> m_SubControlProp;
protected:
	void getAllProp(fuiPropBlock& Block, fuiControl* p);
	void setAllProp(fuiPropBlock& Block);
public:
	/// @brief �������Կ����󶨵Ŀؼ�
	fuiControl* GetBindControl();
	/// @brief ���»�ȡ��������
	void Get();
	/// @brief ������������
	void Set();
protected:
	fuiPropBlock();
public:
	/// @brief ���첢�󶨵��ؼ�
	fuiPropBlock(fuiControl* pControl, fBool CaptureImmediate=true);
	fuiPropBlock(const fuiPropBlock& Org);
	~fuiPropBlock();
};
