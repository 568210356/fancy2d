////////////////////////////////////////////////////////////////////////////////
/// @file  FMMExport.h
/// @brief FFMģ�͵������ʵ��
/// @note  ʵ��SceneExport
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <unordered_map>
#include <string>

#include <Max.h>
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>

#include <IGame\IGame.h>
#include <IGame\IGameError.h>

#include <fcyMisc\fcyHash.h>
#include <fcyFile\fcyModelMesh.h>
#include <fcyMath.h>

#include "resource.h"

struct Vertex
{
	fcyVec3 Position;
	fcyVec3 Normal;
	fcyColor Diffuse;
	fcyVec2 TexCoord;
};

namespace std
{
	template<> 
	struct hash<Vertex>
	{
		inline size_t operator()(const Vertex& v) const
		{
			return fcyHash::SuperFastHash(v);
		}
	};

	template<>
	struct equal_to<Vertex>
		: public binary_function<Vertex, Vertex, bool>
	{	
		// functor for operator==
		bool operator()(const Vertex& _Left, const Vertex& _Right) const
		{	
			if(memcmp(&_Left, &_Right, sizeof(Vertex))!=0)
				return false;
			return true;
		}
	};
};

class CFMMExporter : 
	public SceneExport
{
public:
	/// @brief ������ID
	/// @note  ʹ��help/gencid.exe����
	static Class_ID GetClassID()
	{
		return Class_ID(0x58cc7c23, 0xcd63d85);
	}

	/// @brief �������̵Ľ���������
	static DWORD WINAPI ProgressFunc(LPVOID arg)
	{
		return 0;
	}
protected:
	fcyModelMesh<Vertex> m_MeshData;
	std::unordered_map<int, std::wstring> m_MatCache;
	std::unordered_map<Vertex, fuInt> m_IndexCache;        // �������ж��������
protected:
	void FillFaceVertex(IGameMesh* pMesh, FaceEx* pFace, Vertex Out[]);

	std::wstring ExportProperty(IGameProperty* pProp);
	void ExportMaterial(IGameMaterial* pMat, int ID = -1);
	void ExportSubNode(IGameNode* pNode);
	void ExportMesh(IGameNode* pParent, IGameMesh* pObj);
public: // �ӿ�ʵ��
	/// @brief ����֧�ֵ���չ������
	int	ExtCount() { return 1; }
	/// @brief ������չ��������'.'��
	const char* Ext(int n) { return "FFM"; }
	/// @brief ������չ��˵��
	const char* LongDesc() { return "fancy Model Mesh File"; }
	/// @brief ���ض�˵��
	const char* ShortDesc() { return "fancy Model"; }
	/// @brief ��������
	const char* AuthorName() { return "Chu"; }
	/// @brief ���ذ�Ȩ��Ϣ
	const char* CopyrightMessage() { return "Copyright Chu"; }
	/// @brief ����������Ϣ1
	const char* OtherMessage1() { return ""; }
	/// @brief ����������Ϣ2
	const char* OtherMessage2() { return ""; }
	/// @brief ���ذ汾
	/// @note  v3.01 = 301
	unsigned int Version() { return 100; }
	/// @brief ��ʾ���ڶԻ���
	/// @note  ��ѡ
	void ShowAbout(HWND hWnd) {  }
	/// @brief ��׺֧�ֶȼ��
	BOOL SupportsOptions(int ext, DWORD options) { return TRUE; }

	/// @brief ��ʼ����
	int DoExport(const MCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
public:
	CFMMExporter(void);
	~CFMMExporter(void);
};
