////////////////////////////////////////////////////////////////////////////////
/// @file  f2d.h
/// @brief fancy2Dͷ�ļ�
/// @note  �����˵������������������б����ͷ�ļ�
////////////////////////////////////////////////////////////////////////////////
#pragma once

// ������������
#ifdef F2DEXPORT
#define F2DDLLFUNC __declspec(dllexport)
#else
/// @brief F2DDLL���뺯��
#define F2DDLLFUNC __declspec(dllimport)
#endif

#include "f2dEngine.h"

/// @addtogroup f2d����
/// @{

/// @brief F2D�汾 0.5
#define F2DVERSION ((fuInt)(0<<16 | 5))

/// @brief      ����fancy2D����
/// @param[in]  Version              ����ΪF2DVERSION�����ڼ��DLL�汾
/// @param[in]  pEngineEventListener �ɿգ��������������������
/// @param[out] pOut                 ���������ָ��
extern "C" fResult F2DDLLFUNC CreateF2DEngine(
	fuInt Version, 
	f2dEngineEventListener* pEngineEventListener,
	f2dEngine** pOut);

/// @brief      ����fancy2D���沢��ʼ���������
/// @param[in]  Version              ����ΪF2DVERSION�����ڼ��DLL�汾
/// @param[in]  WinPos               �����û���λ��
/// @param[in]  Title                ���ڱ���
/// @param[in]  Windowed             �Ƿ񴰿ڻ�
/// @param[in]  VSync                �Ƿ�ֱͬ��
/// @param[in]  AA                   ָ������ݵȼ�
/// @param[in]  pEngineEventListener �ɿգ��������������������
/// @param[out] pOut                 ���������ָ��
extern "C" fResult F2DDLLFUNC CreateF2DEngineAndInit(
	fuInt Version, 
	const fcyRect& WinPos, 
	fcStrW Title, 
	fBool Windowed, 
	fBool VSync,
	F2DAALEVEL AA,
	f2dEngineEventListener* pEngineEventListener,
	f2dEngine** pOut);

/// @}
