#include "FMMExporter.h"

#include <fcyMisc\fcyStringHelper.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/// @brief ��������
class CErrorProc : 
	public IGameErrorCallBack
{
public:
	void ErrorProc(IGameError ErrCode)
	{
		DebugPrint("[ CFMMExporter ] ErrorCode = %d; ErrorText = %s\n", ErrCode, GetLastIGameErrorText());
	}
};

////////////////////////////////////////////////////////////////////////////////

CFMMExporter::CFMMExporter(void)
{
}

CFMMExporter::~CFMMExporter(void)
{
}

int CFMMExporter::DoExport(const MCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{
	// ���ļ�
	fcyFileStream* tFile;
	try
	{
		tFile = new fcyFileStream(fcyStringHelper::MultiByteToWideChar(name).c_str(), true);
	}
	catch(...)
	{
		MessageBoxW(0, L"�����ļ�ʧ�ܡ�", L"FMMExporter - ����", 0);
		return FALSE;
	}
	tFile->SetLength(0);
	tFile->SetPosition(FCYSEEKORIGIN_BEG, 0);

	bool bExportSelectedObj = (options & SCENE_EXPORT_SELECTED) ? true : false;

	// ��������
	CErrorProc tErrorProc;
	SetErrorCallBack(&tErrorProc);

	// ���Ľӿ�
	Interface * pCore = GetCOREInterface();

	// �汾��Ϣ
	DebugPrint("[ CFMMExporter ] IGame Supported 3DS Version = %.2f; IGame Version = %.2f\n" , GetSupported3DSVersion(), GetIGameVersion());
	
	// ��ʾ����ѡ��
	if(suppressPrompts)
	{
		// ...
	}

	// ���IGame�ӿڲ�����
	IGameScene * pIGame = GetIGameInterface();
	IGameConversionManager * pIGameConvManager = GetConversionManager();
	pIGame->InitialiseIGame(bExportSelectedObj);  // ��ʼ��
	pIGameConvManager->SetCoordSystem(IGameConversionManager::IGAME_D3D);  // ��������ϵͳ

	// ��ʼ��������
	pCore->ProgressStart("Exporting fancy Model Mesh...", TRUE, ProgressFunc, NULL);

	// ׼��ģ������
	OutputContext tContext;
	{
		tContext.VertexLabel = new fcyModelVertexLabel();
		tContext.VertexLabel->Release();
		tContext.MeshData.GetLabelList().push_back(*tContext.VertexLabel);

		tContext.IndexLabel = new fcyModelIndexLabel();
		tContext.IndexLabel->Release();
		tContext.MeshData.GetLabelList().push_back(*tContext.IndexLabel);

		// ע�ᶥ����Ϣ
		tContext.VertexLabel->ResizeElement(4);
		tContext.VertexLabel->GetVertexElement(0).Type = fcyModelVertexLabel::ELEMENTTYPE_FLOAT3;
		tContext.VertexLabel->GetVertexElement(0).Usage = FMM_MAKE_LABELNAME8("POSITION");
		tContext.VertexLabel->GetVertexElement(0).UsageIndex = 0;
		tContext.VertexLabel->GetVertexElement(1).Type = fcyModelVertexLabel::ELEMENTTYPE_FLOAT3;
		tContext.VertexLabel->GetVertexElement(1).Usage = FMM_MAKE_LABELNAME8("NORMAL\0\0");
		tContext.VertexLabel->GetVertexElement(1).UsageIndex = 0;
		tContext.VertexLabel->GetVertexElement(2).Type = fcyModelVertexLabel::ELEMENTTYPE_COLOR;
		tContext.VertexLabel->GetVertexElement(2).Usage = FMM_MAKE_LABELNAME8("COLOR\0\0\0");
		tContext.VertexLabel->GetVertexElement(2).UsageIndex = 0;
		tContext.VertexLabel->GetVertexElement(3).Type = fcyModelVertexLabel::ELEMENTTYPE_FLOAT2;
		tContext.VertexLabel->GetVertexElement(3).Usage = FMM_MAKE_LABELNAME8("TEXCOORD");
		tContext.VertexLabel->GetVertexElement(3).UsageIndex = 0;
	}

	// �������в���
	int tMatCount = pIGame->GetRootMaterialCount();
	for(int i = 0; i<tMatCount; i++)
	{
		IGameMaterial* pMat = pIGame->GetRootMaterial(i);

		ExportMaterial(&tContext, pMat);
	}

	// �������нڵ�
	int cTopNodeCount = pIGame->GetTopLevelNodeCount();
	for(int i = 0; i<cTopNodeCount; i++)
	{
		IGameNode * pGameNode = pIGame->GetTopLevelNode(i);

		if(pGameNode->IsTarget())
			continue;

		// �����ڵ�
		ExportSubNode(&tContext, pGameNode);
	}

	// ��������
	tContext.MeshData.Save(tFile);
	FCYSAFEKILL(tFile);

	pCore->ProgressEnd();
	
	// �ͷ�IGame
	pIGame->ReleaseIGame();

	return TRUE;
}

void CFMMExporter::FillFaceVertex(IGameMesh* pMesh, FaceEx* pFace, Vertex Out[])
{
	Point3 tPos;
	Point3 tNormal;
	float tAlpha;
	Point3 tColor;
	Point2 tTex;

	pMesh->GetVertex(pFace->vert[0], tPos);
	pMesh->GetNormal(pFace->norm[0], tNormal);
	pMesh->GetTexVertex(pFace->texCoord[0], tTex);
	if(!pMesh->GetAlphaVertex(pFace->alpha[0], tAlpha))
		tAlpha = 1.f;
	if(!pMesh->GetColorVertex(pFace->color[0], tColor))
		tColor.x = tColor.y = tColor.z = 0;

	Out[0].Position.x = tPos.x; Out[0].Position.y = tPos.y; Out[0].Position.z = tPos.z;
	Out[0].Normal.x = tNormal.x; Out[0].Normal.y = tNormal.y; Out[0].Normal.z = tNormal.z;
	Out[0].TexCoord.x = tTex.x; Out[0].TexCoord.y = 1.f + tTex.y;
	Out[0].Diffuse = fcyColor(tAlpha, tColor.x, tColor.y, tColor.z);

	pMesh->GetVertex(pFace->vert[1], tPos);
	pMesh->GetNormal(pFace->norm[1], tNormal);
	pMesh->GetTexVertex(pFace->texCoord[1], tTex);
	if(!pMesh->GetAlphaVertex(pFace->alpha[1], tAlpha))
		tAlpha = 1.f;
	if(!pMesh->GetColorVertex(pFace->color[1], tColor))
		tColor.x = tColor.y = tColor.z = 0;

	Out[1].Position.x = tPos.x; Out[1].Position.y = tPos.y; Out[1].Position.z = tPos.z;
	Out[1].Normal.x = tNormal.x; Out[1].Normal.y = tNormal.y; Out[1].Normal.z = tNormal.z;
	Out[1].TexCoord.x = tTex.x; Out[1].TexCoord.y = 1.f + tTex.y;
	Out[1].Diffuse = fcyColor(tAlpha, tColor.x, tColor.y, tColor.z);

	pMesh->GetVertex(pFace->vert[2], tPos);
	pMesh->GetNormal(pFace->norm[2], tNormal);
	pMesh->GetTexVertex(pFace->texCoord[2], tTex);
	if(!pMesh->GetAlphaVertex(pFace->alpha[2], tAlpha))
		tAlpha = 1.f;
	if(!pMesh->GetColorVertex(pFace->color[2], tColor))
		tColor.x = tColor.y = tColor.z = 0;

	Out[2].Position.x = tPos.x; Out[2].Position.y = tPos.y; Out[2].Position.z = tPos.z;
	Out[2].Normal.x = tNormal.x; Out[2].Normal.y = tNormal.y; Out[2].Normal.z = tNormal.z;
	Out[2].TexCoord.x = tTex.x; Out[2].TexCoord.y = 1.f + tTex.y;
	Out[2].Diffuse = fcyColor(tAlpha, tColor.x, tColor.y, tColor.z);
}

std::wstring CFMMExporter::ExportProperty(IGameProperty* pProp)
{
	wstring tRet;
	wchar_t tTextBuffer[256];

	if(pProp)
	{
		switch(pProp->GetType())
		{
		case IGAME_POINT3_PROP:
			{
				Point3 p; 
				pProp->GetPropertyValue(p);

				swprintf_s(tTextBuffer, L"%f,%f,%f", p.x, p.y, p.z);
				tRet = tTextBuffer;
			}
			break;
		case IGAME_FLOAT_PROP:
			{
				float p; 
				pProp->GetPropertyValue(p);

				swprintf_s(tTextBuffer, L"%f", p);
				tRet = tTextBuffer;
			}
			break;
		case IGAME_STRING_PROP:
			{
				const char* pStr = NULL;
				pProp->GetPropertyValue(pStr);

				tRet = fcyStringHelper::MultiByteToWideChar(pStr);
			}
			break;
		}
	}

	return tRet;
}

void CFMMExporter::ExportFXProperty(fcyXmlElement& Node, IGameFXProperty* pProp)
{
	Node.SetAttribute(L"Name", fcyStringHelper::MultiByteToWideChar(pProp->GetPropertyName()));

	// ... ��ε���������
}

void CFMMExporter::ExportMaterial(OutputContext* pContext, IGameMaterial* pMat, int ID)
{
	// �������
	wstring tName = fcyStringHelper::MultiByteToWideChar(pMat->GetMaterialName());
	
	// ע�����
	if(ID != -1)
		pContext->MatCache[ID] = tName;

	// ��������
	if(pMat->IsMultiType())
	{
		int tCount = pMat->GetSubMaterialCount();
		for(int i = 0; i<tCount; i++)
		{
			ExportMaterial(pContext, pMat->GetSubMaterial(i), pMat->GetMaterialID(i));
		}
	}
	else
	{
		// ��������XML����
		fcyXmlDocument tXmlData;

		// ������
		fcyXmlElement* tRoot = tXmlData.CreateElement(L"fancyModelMaterial");
		
		// ������׼��������
		{
			fcyXmlElement* tNode = tXmlData.CreateElement(L"Diffuse");
			tNode->SetContent(ExportProperty(pMat->GetDiffuseData()));
			tRoot->AppendNode(tNode);

			tNode = tXmlData.CreateElement(L"Ambient");
			tNode->SetContent(ExportProperty(pMat->GetAmbientData()));
			tRoot->AppendNode(tNode);

			tNode = tXmlData.CreateElement(L"Specular");
			tNode->SetContent(ExportProperty(pMat->GetSpecularData()));
			tRoot->AppendNode(tNode);

			tNode = tXmlData.CreateElement(L"Glossiness");
			tNode->SetContent(ExportProperty(pMat->GetGlossinessData()));
			tRoot->AppendNode(tNode);

			tNode = tXmlData.CreateElement(L"Opacity");
			tNode->SetContent(ExportProperty(pMat->GetOpacityData()));
			tRoot->AppendNode(tNode);

			tNode = tXmlData.CreateElement(L"SpecularLevel");
			tNode->SetContent(ExportProperty(pMat->GetSpecularLevelData()));
			tRoot->AppendNode(tNode);
		}

		// ����������
		{
			int tCount = pMat->GetNumberOfTextureMaps();
			for(int i = 0; i<tCount; i++)
			{
				IGameTextureMap* pTextureMap = pMat->GetIGameTextureMap(i);

				fcyXmlElement* tNode = tXmlData.CreateElement(L"Texture");
				tNode->SetAttribute(L"Name", fcyStringHelper::MultiByteToWideChar(pTextureMap->GetTextureName()));
				tNode->SetAttribute(L"Slot", fcyStringHelper::ToWideStr(pTextureMap->GetStdMapSlot()));
				
				if(pTextureMap->IsEntitySupported())
				{
					// λͼ
					tNode->SetAttribute(L"ClipU", ExportProperty(pTextureMap->GetClipUData()));
					tNode->SetAttribute(L"ClipV", ExportProperty(pTextureMap->GetClipVData()));
					tNode->SetAttribute(L"ClipW", ExportProperty(pTextureMap->GetClipWData()));
					tNode->SetAttribute(L"ClipH", ExportProperty(pTextureMap->GetClipHData()));

					tNode->SetAttribute(L"Filename", fcyStringHelper::MultiByteToWideChar(pTextureMap->GetBitmapFileName()));
				}

				tRoot->AppendNode(tNode);
			}
		}

		// ����FX����
		/*
		IGameFX * pFXData = pMat->GetIGameFX();
		if(pFXData)
		{
			fcyXmlElement tFXNode;
			tFXNode.SetName(L"FX");
			tFXNode.SetAttribute(L"Filename", fcyStringHelper::MultiByteToWideChar((fcStr)pFXData->GetEffectFile().GetFileName()).c_str());

			// ��������
			for(int i=0; i<pFXData->GetNumberOfProperties(); i++)
			{
				IGameFXProperty* pFXProp = pFXData->GetIGameFXProperty(i);
				
				fcyXmlElement tPropNode;
				tPropNode.SetName(L"Param");
				ExportFXProperty(tPropNode, pFXProp);

				tFXNode.AppendNode(tPropNode);
			}
			
			tRoot.AppendNode(tFXNode);
		}
		*/

		// ���ø�
		tXmlData.SetRootElement(tRoot);

		// ����������Ϣ
		fcyRefPointer<fcyModelMaterialLabel> pMat = new fcyModelMaterialLabel();
		pMat->Release();

		wstring tXMLStr;
		tXmlData.Save(tXMLStr);

		pMat->SetMaterialName(tName);
		pMat->SetMaterialXMLData(tXMLStr);

		pContext->MeshData.GetLabelList().push_back(*pMat);
	}
}

void CFMMExporter::ExportSubNode(OutputContext* pContext, IGameNode* pNode)
{
	// ����ǰ�ڵ�
	IGameObject * pObj = pNode->GetIGameObject();

	if(pObj)
	{
		switch(pObj->GetIGameType())
		{
		case IGameObject::IGAME_MESH:
			ExportMesh(pContext, pNode, (IGameMesh*)pObj);
			break;
		}
	}

	pNode->ReleaseIGameObject();

	// �����ӽڵ�
	for(int i = 0; i<pNode->GetChildCount(); i++)
	{
		IGameNode * pGameNode = pNode->GetNodeChild(i);

		if(pGameNode->IsTarget())
			continue;

		ExportSubNode(pContext, pGameNode);
	}
}

void CFMMExporter::ExportMesh(OutputContext* pContext, IGameNode* pParent, IGameMesh* pObj)
{
	// �Ӽ�����
	string tName = pParent->GetName();

	// ��ʼ��
	pObj->SetCreateOptimizedNormalList();
	pObj->InitializeData();

	// ����
	unordered_map<int, vector<fuInt> > tSubsetCache; // ���������Ӽ�
	unordered_map<int, string> tSubsetNameCache;     // �Ӽ����ƻ���
	
	unordered_map<Vertex, fuInt>& tIndexCache = pContext->IndexCache;

	// �ռ�ÿ����Ķ�����Ϣ
	fInt tFaceCount = pObj->GetNumberOfFaces();
	for(int i = 0; i<tFaceCount; i++)
	{
		FaceEx* pFace = pObj->GetFace(i);
		int tMat = pObj->GetFaceMaterialID(i);

		// ������Ķ���
		Vertex tVert[3];
		FillFaceVertex(pObj, pFace, tVert);

		// �ӻ����ѯ
		unordered_map<Vertex, fuInt>::iterator v0 = tIndexCache.find(tVert[0]);
		if(v0 == tIndexCache.end())
		{
			int tIndex = tIndexCache.size();
			tIndexCache[tVert[0]] = tIndex;
			v0 = tIndexCache.find(tVert[0]);

			pContext->VertexLabel->PushVertex(&tVert[0]);
		}
		unordered_map<Vertex, fuInt>::iterator v1 = tIndexCache.find(tVert[1]);
		if(v1 == tIndexCache.end())
		{
			int tIndex = tIndexCache.size();
			tIndexCache[tVert[1]] = tIndex;
			v1 = tIndexCache.find(tVert[1]);
			
			pContext->VertexLabel->PushVertex(&tVert[1]);
		}
		unordered_map<Vertex, fuInt>::iterator v2 = tIndexCache.find(tVert[2]);
		if(v2 == tIndexCache.end())
		{
			int tIndex = tIndexCache.size();
			tIndexCache[tVert[2]] = tIndex;
			v2 = tIndexCache.find(tVert[2]);
			
			pContext->VertexLabel->PushVertex(&tVert[2]);
		}

		// ��������
		if(tSubsetCache.find(tMat) == tSubsetCache.end())
		{
			tSubsetNameCache[tMat] = tName + "@" + fcyStringHelper::ToStr((fInt)tSubsetCache.size());
		}
		tSubsetCache[tMat].push_back(v0->second);
		tSubsetCache[tMat].push_back(v1->second);
		tSubsetCache[tMat].push_back(v2->second);
	}

	// --- ����������д��Mesh ---
	unordered_map<int, vector<fuInt> >::iterator i = tSubsetCache.begin();
	while(i != tSubsetCache.end())
	{
		// ��ѯ�Ӽ��Ĳ���
		const wstring& tMatName = pContext->MatCache[i->first];
		
		// �����Ӽ�
		fcyRefPointer<fcyModelSubsetLabel> pSubsetLabel = new fcyModelSubsetLabel();
		pSubsetLabel->Release();
		
		pSubsetLabel->SetSubsetName(fcyStringHelper::MultiByteToWideChar(tSubsetNameCache[i->first]));
		pSubsetLabel->SetMaterialName(tMatName);
		pSubsetLabel->SetStartIndex(pContext->IndexLabel->GetSize());
		pSubsetLabel->SetPrimitiveType(fcyModelSubsetLabel::PRIMTYPE_TRIANGLELIST);
		pSubsetLabel->SetPrimitiveCount(i->second.size() / 3);

		// д������
		for(fuInt j = 0; j<i->second.size(); j++)
		{
			pContext->IndexLabel->Push(i->second[j]);
		}

		pContext->MeshData.GetLabelList().push_back(*pSubsetLabel);

		i++;
	}
}
