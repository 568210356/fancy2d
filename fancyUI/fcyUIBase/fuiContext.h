#pragma once

#include "fcyParser/fcyXml.h"

#include "f2d.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI��������Դ������
////////////////////////////////////////////////////////////////////////////////
struct fuiContextResLoader
{
	/// @brief  ��·����������
	/// @return ���󷵻�NULL
	virtual f2dTexture* GetTexture(fcStrW Path)=0;

	/// @brief  ��·����������
	/// @return ���󷵻�NULL
	virtual f2dFontRenderer* GetFont(fcStrW Path, fuInt Size)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancyUI������
////////////////////////////////////////////////////////////////////////////////
class fuiContext :
	public fcyRefObjImpl<fcyRefObj>
{
private:
	/// @brief Ĭ����Դ������
	class DefaultResLoader :
		public fuiContextResLoader
	{
	private:
		f2dRenderer* m_pRenderer;

		std::unordered_map<std::wstring, f2dTexture*> m_TexCache;      ///< @brief ������
		std::unordered_map<std::wstring, fcyStream*> m_pFontFileCache; ///< @brief �����ļ�����
		std::unordered_map<std::wstring, std::unordered_map<fuInt, f2dFontRenderer*> > m_FontCache; ///< @brief ���建��
	private:
		fcyStream* openStream(fcStrW Path);
	public:
		f2dTexture* GetTexture(fcStrW Path);
		f2dFontRenderer* GetFont(fcStrW Path, fuInt Size);
	public:
		DefaultResLoader(f2dRenderer* pRenderer);
		~DefaultResLoader();
	};
private:
	// === �ļ�Դ ===
	DefaultResLoader m_DefaultLoader;
	fuiContextResLoader* m_ResLoader;

	// === ������� ===
	f2dRenderer* m_pRenderer; ///< @brief  ������Դ����

	// === ���� ===
	std::unordered_map<std::wstring, f2dSprite*> m_SpriteCache;     ///< @brief ���黺��
	std::unordered_map<std::wstring, f2dFontRenderer*> m_FontCache; ///< @brief ���ֻ���

	// === ��ʽ��Ϣ ===
	std::unordered_map<std::wstring, std::unordered_map<std::wstring, fcyXmlNode> > m_Style;
public:
	/// @brief ������Դ������
	fuiContextResLoader* GetResLoader();
	/// @brief     ������Դ������
	/// @param[in] pLoader ������
	void SetResLoader(fuiContextResLoader* pLoader);
	/// @brief   ��վ���
	/// @warning UI���������Ծ�������á�����ȷ����ȫ��ǰ����ʹ�ñ�������
	void ClearSprite();
	/// @brief   ���������ʽ
	/// @warning UI����������������ʽ�����á�����ȷ����ȫ��ǰ����ʹ�ñ�������
	void ClearFontStyle();
	/// @brief �����ʽ
	void ClearStyle();
	/// @brief     ���ļ����ؾ��鶨��
	/// @exception fcyException fancy�쳣
	/// @param[in] pFile ���������XML�ļ�
	void LoadSprite(fcyStream* pFile);
	/// @brief     ��XML�ڵ���ض���
	/// @exception fcyException fancy�쳣
	/// @param[in] pNode ���������XML�ڵ�
	void LoadSprite(fcyXmlNode* pNode);
	/// @brief     ���ļ�����UI����
	/// @exception fcyException fancy�쳣
	/// @param[in] pFile ���������XML�ļ�
	void LoadStyle(fcyStream* pFile);
	/// @brief     ��XML�ڵ����UI����
	/// @exception fcyException fancy�쳣
	/// @param[in] pNode ���������XML�ڵ�
	void LoadStyle(fcyXmlNode* pNode);
	/// @brief     ���ļ�����������ʽ����
	/// @exception fcyException fancy�쳣
	/// @param[in] pFile ���������XML�ļ�
	void LoadFontStyle(fcyStream* pFile);
	/// @brief     ��XML�ڵ����������ʽ����
	/// @exception fcyException fancy�쳣
	/// @param[in] pNode ���������XML�ڵ�
	void LoadFontStyle(fcyXmlNode* pNode);
	/// @brief     ��þ���
	/// @param[in] SpriteName ��������
	f2dSprite* GetSprite(fcStrW SpriteName);
	/// @brief     �����ʽ
	/// @param[in] ControlType �ؼ�����
	/// @param[in] StyleName   ��ʽ����
	fcyXmlNode* GetStyle(fcStrW ControlType, fcStrW StyleName);
	/// @brief     �������
	/// @param[in] FontName ��������
	f2dFontRenderer* GetFont(fcStrW FontName);
public:
	/// @brief     ���캯��
	/// @param[in] f2d��Ⱦ��
	fuiContext(f2dRenderer* pRenderer);
protected:
	/// @brief ��ֱֹ������
	~fuiContext();
};
