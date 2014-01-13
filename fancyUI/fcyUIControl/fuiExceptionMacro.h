////////////////////////////////////////////////////////////////////////////////
/// @file  fuiExceptionMacro.h
/// @brief �����쳣��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyMisc/fcyStringHelper.h>

/// @brief ��ȡ��Դ�����Ϸ���
#define FUIGETRESANDCHECK(ResName, ResVar, ResType, ResCheck, ExceptionSrc) \
	ResVar = (ResType*)GetControlStyle()->QueryRes(ResName);             \
	if(!ResName.empty() && !ResVar)                                      \
		throw fcyException(                                              \
			ExceptionSrc,                                                \
			"in control '%s' : Res '%s' not found.",                     \
			fcyStringHelper::WideCharToMultiByte(GetName()).c_str(),     \
			fcyStringHelper::WideCharToMultiByte(ResName).c_str()        \
			);                                                           \
	else if(ResVar && ResVar->GetResType() != ResCheck)                  \
	{                                                                    \
		ResVar = NULL;                                                   \
		throw fcyException(                                              \
			ExceptionSrc,                                                \
			"in control '%s' : Res '%s' type error.",                    \
			fcyStringHelper::WideCharToMultiByte(GetName()).c_str(),     \
			fcyStringHelper::WideCharToMultiByte(ResName).c_str()        \
			);                                                           \
	}                                                                    
