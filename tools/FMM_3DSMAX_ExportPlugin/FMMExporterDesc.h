////////////////////////////////////////////////////////////////////////////////
/// @file  FMMExportDesc.h
/// @brief FMMģ�͵����������
/// @note  ʵ��ClassDesc2
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "FMMExporter.h"

// DLLȫ����
extern HINSTANCE g_hDllInstance;
extern std::string GetResString(UINT ResID);

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyModelMesh �����������
/// @note  ������
////////////////////////////////////////////////////////////////////////////////
class CFMMExporterDesc : 
	public ClassDesc2
{
public:
	/// @brief ����ʵ��
	static CFMMExporterDesc* GetInstance()
	{
		static CFMMExporterDesc s_Instance;

		return &s_Instance;
	}
public: // �ӿ�ʵ��
	/// @brief �Ƿ񹫿�
	int IsPublic()
	{
		return TRUE;
	}
	/// @brief ������������
	LPCSTR ClassName()
	{
		static std::string s_ClassName = GetResString(IDS_CLASS_EXPORT_NAME);

		return s_ClassName.c_str();
	}
	/// @brief ���ظ�������
	SClass_ID SuperClassID()
	{
		return SCENE_EXPORT_CLASS_ID;
	}
	/// @brief �������
	const char* Category()
	{
		static std::string s_Category = GetResString(IDS_CLASS_EXPORT_CATEGORY);

		return s_Category.c_str();
	}
	/// @brief �����ڲ�����
	/// @note  �ű��ɼ�
	const char* InternalName() { return _T("IFMMExporter"); }
	/// @brief ����DLLʵ��
	HINSTANCE HInstance()
	{
		return g_hDllInstance;
	}

	/// @brief ��������
	void* Create(BOOL loading = FALSE)
	{
		return new CFMMExporter();
	}
	/// @brief ������ID
	Class_ID ClassID()
	{
		return CFMMExporter::GetClassID();
	}
public:
	CFMMExporterDesc() {}
	~CFMMExporterDesc() {}
};
