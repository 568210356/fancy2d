////////////////////////////////////////////////////////////////////////////////
/// @file  fuiParticleEmitter.h
/// @brief fancyUI ���ӷ�����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyUIBase/fuiControl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief UI ���ӷ�����
////////////////////////////////////////////////////////////////////////////////
class fuiParticleEmitter :
	public fuiControl
{
protected: // ��ͼ��Դ
	fcyRefPointer<fuiSprite> m_pImageSprite;
	fcyRefPointer<fuiParticleDesc> m_pParticleDesc;

	f2dParticlePool* m_pPool;
	fDouble m_NextTime;
protected: // ����
	std::wstring m_ParticleName;
	std::wstring m_ParticleSpriteName;
	fcyVec2 m_EmitterTimeRange;
	fcyVec2 m_EmitterCountRange;
	bool m_bEmitterEnable;

	fuiPropertyAccessor<std::wstring> m_Particle_Accessor;
	fuiPropertyAccessor<std::wstring> m_ParticleSprite_Accessor;
	fuiPropertyAccessor<fcyVec2> m_EmitterTimeRange_Accessor;
	fuiPropertyAccessor<fcyVec2> m_EmitterCountRange_Accessor;
	fuiPropertyAccessor<bool> m_bEmitterEnable_Accessor;
protected: // �����¼�
	void OnParentChanged(fuiControl* pThis, fuiEventArgs* pArgs);
	void OnStyleChanged(fuiControl* pThis, fuiEventArgs* pArgs);
public: // ʵ�ֽӿ�
	void Update(fDouble ElapsedTime);
	void Render(fuiGraphics* pGraph);
public:
	fuiParticleEmitter(fuiPage* pRootPage, const std::wstring& Name);
	~fuiParticleEmitter();
};
