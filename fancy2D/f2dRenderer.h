////////////////////////////////////////////////////////////////////////////////
/// @file   f2dRenderer.h
/// @brief  fancy2D������Ⱦ���ӿڶ���
/// @note   ������f2D����Ⱦ���ӿ�
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInterface.h"

/// @addtogroup f2d��Ⱦϵͳ
/// @brief fancy2d�����е���Ⱦϵͳ���ṩ��2Dͼ�ε���Ⱦ֧�֡�
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief   fancy2D����
/// @note    Ϊ�򻯲�����Լ�����е������ʽ��ΪA8R8G8B8���˷���������RenderTarget��֧�ֿ���ݡ�
/// @warning ��̬�������ȾĿ�겻�ᴴ��Mipmaps��������ʹ������������ܻ�������Ⱦ�ٶ�
////////////////////////////////////////////////////////////////////////////////
struct f2dTexture : public f2dInterface
{
	virtual fBool IsDynamic()=0;       ///< @brief �Ƿ��Ƕ�̬����
	virtual fBool IsRenderTarget()=0;  ///< @brief �Ƿ�����ȾĿ��
	virtual fuInt GetWidth()=0;        ///< @brief ��ÿ��
	virtual fuInt GetHeight()=0;       ///< @brief ��ø߶�

	/// @brief      ��������
	/// @note       ֻ�ж�̬������Ա����������������ͽ���������ԣ���δ����ǰֻ������һ�Ρ�
	/// @param[in]  pLockRect ��������������ΪNULL��������������
	/// @param[in]  Discard   ���ԭʼ�������ڱ�ʹ��������ԭʼ����
	/// @param[out] Pitch     �ж����ֽ�
	/// @param[out] pOut      ���ص��ڴ�ָ�룬�Զ����㵽��������ֽ�
	virtual fResult Lock(fcyRect* pLockRect, fBool Discard, fuInt* Pitch, fData* pOut)=0;

	/// @brief ��������
	virtual fResult Unlock()=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��������
////////////////////////////////////////////////////////////////////////////////
enum F2DBLENDOPERATOR
{
	F2DBLENDOPERATOR_ADD         = 1, ///< @brief ��Ͻ�� = Դ���� + Ŀ������
	F2DBLENDOPERATOR_SUBTRACT    = 2, ///< @brief ��Ͻ�� = Դ���� - Ŀ������
	F2DBLENDOPERATOR_REVSUBTRACT = 3, ///< @brief ��Ͻ�� = Ŀ������ - Դ����
	F2DBLENDOPERATOR_MIN         = 4, ///< @brief ��Ͻ�� = MIN(Դ����, Ŀ������)
	F2DBLENDOPERATOR_MAX         = 5  ///< @brief ��Ͻ�� = MAX(Դ����, Ŀ������)
};

////////////////////////////////////////////////////////////////////////////////
/// @brief �������
/// @note  ��ɫ��Ϲ�ʽ��Color = SrcColor * SrcBlend + DestColor * DestBlend
////////////////////////////////////////////////////////////////////////////////
enum F2DBLENDFACTOR
{
    F2DBLENDFACTOR_ZERO               = 1,   ///< @brief �������(0, 0, 0, 0)
    F2DBLENDFACTOR_ONE                = 2,   ///< @brief �������(1, 1, 1, 1)
    F2DBLENDFACTOR_SRCCOLOR           = 3,   ///< @brief �������(Rs, Gs, Bs, As)
    F2DBLENDFACTOR_INVSRCCOLOR        = 4,   ///< @brief �������(1 - Rs, 1 - Gs, 1 - Bs, 1 - As)
    F2DBLENDFACTOR_SRCALPHA           = 5,   ///< @brief �������(As, As, As, As)
    F2DBLENDFACTOR_INVSRCALPHA        = 6,   ///< @brief �������(1 - As, 1 - As, 1 - As, 1 - As)
    F2DBLENDFACTOR_DESTALPHA          = 7,   ///< @brief �������(Ad, Ad, Ad, Ad)
    F2DBLENDFACTOR_INVDESTALPHA       = 8,   ///< @brief �������(1 - Ad, 1 - Ad, 1 - Ad, 1 - Ad)
    F2DBLENDFACTOR_DESTCOLOR          = 9,   ///< @brief �������(Rd, Gd, Bd, Ad)
    F2DBLENDFACTOR_INVDESTCOLOR       = 10,  ///< @brief �������(1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad)
    F2DBLENDFACTOR_SRCALPHASAT        = 11   ///< @brief �������(f, f, f, 1)������f = min(As, 1 - Ad)
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ������ɫ��Ϲ�ʽ
////////////////////////////////////////////////////////////////////////////////
enum F2DTEXOPERATOR
{
	F2DTEXOPT_DISABLE                     = 1,  ///< @brief �ر�
	F2DTEXOPT_SELECTARG1                  = 2,  ///< @brief Srgba = Arg1
	F2DTEXOPT_SELECTARG2                  = 3,  ///< @brief Srgba = Arg2
	F2DTEXOPT_MODULATE                    = 4,  ///< @brief Srgba = Arg1 x Arg2
	F2DTEXOPT_MODULATE2X                  = 5,  ///< @brief Srgba = (Arg1 x Arg2)<<1
	F2DTEXOPT_MODULATE4X                  = 6,  ///< @brief Srgba = (Arg1 x Arg2)<<2
	F2DTEXOPT_ADD                         = 7,  ///< @brief Srgba = Arg1 + Arg2
	F2DTEXOPT_ADDSIGNED                   = 8,  ///< @brief Srgba = Arg1 + Arg2 - 0.5
	F2DTEXOPT_ADDSIGNED2X                 = 9,  ///< @brief Srgba = (Arg1 + Arg2 - 0.5)<<1
	F2DTEXOPT_SUBTRACT                    = 10, ///< @brief Srgba = Arg1 - Arg2
	F2DTEXOPT_ADDSMOOTH                   = 11, ///< @brief Srgba = Arg1 + Arg2 * (1 - Arg1)
	F2DTEXOPT_BLENDDIFFUSEALPHA           = 12, 
	F2DTEXOPT_BLENDTEXTUREALPHA           = 13,
	F2DTEXOPT_BLENDFACTORALPHA            = 14,
	F2DTEXOPT_BLENDTEXTUREALPHAPM         = 15,
	F2DTEXOPT_BLENDCURRENTALPHA           = 16,
	F2DTEXOPT_PREMODULATE                 = 17,
	F2DTEXOPT_MODULATEALPHA_ADDCOLOR      = 18,
	F2DTEXOPT_MODULATECOLOR_ADDALPHA      = 19,
	F2DTEXOPT_MODULATEINVALPHA_ADDCOLOR   = 20,
	F2DTEXOPT_MODULATEINVCOLOR_ADDALPHA   = 21,
	F2DTEXOPT_BUMPENVMAP                  = 22,
	F2DTEXOPT_BUMPENVMAPLUMINANCE         = 23,
	F2DTEXOPT_DOTPRODUCT3                 = 24,
	F2DTEXOPT_MULTIPLYADD                 = 25,
	F2DTEXOPT_LERP                        = 26
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ������ɫ���Դ
////////////////////////////////////////////////////////////////////////////////
enum F2DTEXARG
{
	F2DTEXARG_DIFFUSE  = 0,  ///< @brief ѡ����������ɫ
	F2DTEXARG_CURRENT  = 1,  ///< @brief ѡ����һ����ɫ
	F2DTEXARG_TEXTURE  = 2,  ///< @brief ѡ��������ɫ
	F2DTEXARG_TFACTOR  = 3,  ///< @brief TFACTOR
	F2DTEXARG_SPECULAR = 4   ///< @brief ѡ������ɫ
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Graphics��Ⱦ״̬
////////////////////////////////////////////////////////////////////////////////
enum F2DRENDERSTATE
{
	F2DRENDERSTATE_BLENDOPT     = 0,   ///< @brief ������������ӦF2DBLENDOPERATOR��
	F2DRENDERSTATE_BLENDSRC     = 1,   ///< @brief ���Դ���ӣ���ӦF2DBLENDFACTOR��
	F2DRENDERSTATE_BLENDDEST    = 2,   ///< @brief ���Ŀ�����ӣ���ӦF2DBLENDFACTOR��
	F2DRENDERSTATE_TEXCOLOROPT  = 3,   ///< @brief ������ɫͨ��������������ӦF2DTEXOPERATOR��
	F2DRENDERSTATE_TEXCOLORARG1 = 4,   ///< @brief ������ɫͨ����ϲ���1����ӦF2DTEXARG��
	F2DRENDERSTATE_TEXCOLORARG2 = 5,   ///< @brief ������ɫͨ����ϲ���2����ӦF2DTEXARG��
	F2DRENDERSTATE_TEXALPHAOPT  = 6,   ///< @brief ����͸��ͨ��������������ӦF2DTEXOPERATOR��
	F2DRENDERSTATE_TEXALPHAARG1 = 7,   ///< @brief ����͸��ͨ����ϲ���1����ӦF2DTEXARG��
	F2DRENDERSTATE_TEXALPHAARG2 = 8,   ///< @brief ����͸��ͨ����ϲ���2����ӦF2DTEXARG��
	F2DRENDERSTATE_MASK         = 9    ///< @brief �������룬��Чֵ
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��άͼ����Ⱦ������
////////////////////////////////////////////////////////////////////////////////
struct f2dGraphics2DVertex
{
	fFloat x;      ///< @brief x����
	fFloat y;      ///< @brief y����
	fFloat z;      ///< @brief z����
	fuInt color;   ///< @brief ��������ɫ
	fFloat u;      ///< @brief ����u����
	fFloat v;      ///< @brief ����v����
};

////////////////////////////////////////////////////////////////////////////////
/// @brief   fancy2D��άͼ����Ⱦ��
/// @note    ��װ��άͼ�ε���Ⱦ����
/// @warning Graphics2D������Ƕ��ʹ��
////////////////////////////////////////////////////////////////////////////////
struct f2dGraphics2D : public f2dInterface
{
	// --- ��Ⱦ״̬���� ---
	/// @brief     ��û��״̬����
	/// @param[in] State ��Ⱦ״ֵ̬
	/// @return    ���ݲ�����ͬ���ز�ͬö������
	virtual fuInt GetRenderState(F2DRENDERSTATE State)=0;
	/// @brief     ���û��״̬����
	/// @param[in] State ��Ⱦ״ֵ̬
	/// @param[in] Value ����ֵ
	virtual void SetRenderState(F2DRENDERSTATE State, fuInt Value)=0;
	/// @brief      ���ر任����
	/// @param[out] pOut �������
	virtual void GetProjTransform(fcyMatrix4* pOut)=0;
	/// @brief     ���ñ任����
	/// @param[in] pTrans �任����
	virtual void SetProjTransform(const fcyMatrix4& pTrans)=0;
	/// @brief      ���ر任����
	/// @param[out] pOut �������
	virtual void GetWorldTransform(fcyMatrix4* pOut)=0;
	/// @brief     ���ñ任����
	/// @param[in] pTrans �任����
	virtual void SetWorldTransform(const fcyMatrix4& pTrans)=0;
	/// @brief ���浱ǰ���󵽶�ջ
	virtual void PushWorldTransform()=0;
	/// @brief ������ջ�б���ľ���
	virtual void PopWorldTransform()=0;
	
	// --- ���ƿ��� ---
	/// @brief   ״̬ͬ��
	/// @note    ��״̬�����ύ���豸�н���ͬ��
	/// @warning ������������ò���
	virtual void SyncStates()=0;
	/// @brief   ��������
	/// @warning ������Begin/End��������Ⱦ�豸�����κ�״̬�ϵ��л�
	virtual fResult Begin()=0;
	/// @brief ��������
	virtual fResult End()=0;
	/// @brief ������������ͼԪ
	virtual fResult Flush()=0;

	// --- ��ͼ���� ---
	/// @brief     �����ı���
	/// @param[in] pTex ����
	/// @param[in] v1   ����1�����Ͻ�
	/// @param[in] v2   ����2�����Ͻ�
	/// @param[in] v3   ����3�����½�
	/// @param[in] v4   ����4�����½�
	virtual fResult DrawQuad(
	  f2dTexture* pTex,
		const f2dGraphics2DVertex& v1, 
		const f2dGraphics2DVertex& v2, 
		const f2dGraphics2DVertex& v3, 
		const f2dGraphics2DVertex& v4
		)=0;
	/// @brief     �����ı���
	/// @param[in] pTex ����
	/// @param[in] arr  �ı�������
	virtual fResult DrawQuad(f2dTexture* pTex, const f2dGraphics2DVertex* arr)=0;

	/// @brief     ����ԭʼͼԪ
	/// @note      ����2Dͼ��ʱ��Ҫ�ֶ��Զ���(x,y)ƫ��+0.5������
	/// @param[in] pTex       �󶨵�����
	/// @param[in] VertCount  ��������
	/// @param[in] IndexCount ��������
	/// @param[in] VertArr    ��������
	/// @param[in] IndexArr   ��������
	virtual fResult DrawRaw(f2dTexture* pTex, fuInt VertCount, fuInt IndexCount, const f2dGraphics2DVertex* VertArr, const fuShort* IndexArr)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D����Ч���ӿ�
////////////////////////////////////////////////////////////////////////////////
struct f2dPostEffect : public f2dInterface
{
	/// @brief     ���ظ������ֵ
	/// @param[in] ParamName ������
	/// @return    ���ض�ӦԪ�ص�ֵ��ʧ�ܷ���0
	virtual fFloat GetFloat(fcStr ParamName)=0;

	/// @brief ���ظ�������
	/// @param[in]  ParamName ������
	/// @param[out] Dest      Ŀ������
	/// @param[in]  Count     Ԫ�ظ���
	virtual fResult GetFloatArr(fcStr ParamName, fFloat* Dest, fuInt Count)=0;

	/// @brief ���ø������ֵ
	/// @param[in] ParamName ������
	/// @param[in] Value     Ԫ��ֵ
	virtual fResult SetValue(fcStr ParamName, fFloat Value)=0;

	/// @brief ���ø�������Ԫ��
	/// @param[in] ParamName ������
	/// @param[in] Index     Ԫ���±�
	/// @param[in] Value     Ԫ��ֵ
	virtual fResult SetValue(fcStr ParamName, fuInt Index, fFloat Value)=0;

	/// @brief ���ø�������
	/// @param[in] ParamName ������
	/// @param[in] Src       ԭʼֵ
	/// @param[in] Count     Ԫ������
	virtual fResult SetFloatArr(fcStr ParamName, const fFloat* Src, fuInt Count)=0;

	/// @brief ��������
	/// @param[in] ParamName ������
	/// @param[in] pTex      ����ָ��
	virtual fResult SetTexture(fcStr ParamName, f2dTexture* pTex)=0;

	/// @brief ����������Ч���ռ�����
	virtual fResult Begin()=0;

	/// @brief ��ɺ�����Ч��������Ч��Ⱦ
	virtual fResult End()=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ�豸�¼�������
/// @note  ���豸��ʧ��������ʱ�������¼�
////////////////////////////////////////////////////////////////////////////////
struct f2dRenderDeviceEventListener
{
	/// @brief �豸��ʧ�¼�
	virtual void OnRenderDeviceLost(){}

	/// @brief �豸�����¼�
	virtual void OnRenderDeviceReset(){}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D����ݵȼ�
////////////////////////////////////////////////////////////////////////////////
enum F2DAALEVEL
{
	F2DAALEVEL_NONE = 0,     ///< @brief �رտ����
	F2DAALEVEL_2    = 1,     ///< @brief 2x�����
	F2DAALEVEL_4    = 2,     ///< @brief 4x�����
	F2DAALEVEL_8    = 3,     ///< @brief 8x�����
	F2DAALEVEL_16   = 4      ///< @brief 16x�����
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ�豸
/// @note  ������Ⱦ����Ĵ������豸����
////////////////////////////////////////////////////////////////////////////////
struct f2dRenderDevice
{
	/// @brief   ����D3D�豸ָ��
	/// @note    ��Ҫǿת��IDirect3DDevice9
	/// @warning ����������Ҫ��Ӧ������ʹ�ø÷���
	virtual void* GetHandle()=0;
	
	// --- ������ ---
	/// @brief     �ҽ�һ����Ϣ������
	/// @param[in] Listener Ҫ�󶨵ļ�����
	virtual fResult AttachListener(f2dRenderDeviceEventListener* Listener)=0;
	
	/// @brief     �Ƴ�һ����Ϣ������
	/// @param[in] Listener Ҫ�Ƴ��ļ�����
	virtual fResult RemoveListener(f2dRenderDeviceEventListener* Listener)=0;

	// --- ������ ---
	/// @brief      ����һ����̬����
	/// @note       ��̬����֮�е����ݻ����豸��ʧ֮����ʧ��
	/// @param[in]  Width  ���
	/// @param[in]  Height �߶�
	/// @param[out] pOut   ���������ָ��
	virtual fResult CreateDynamicTexture(fuInt Width, fuInt Height, f2dTexture** pOut)=0;

	/// @brief      ����������������
	/// @note       ����ѡ���Դ�����̬/��̬����
	/// @param[in]  pStream   ������������ȡ����������
	/// @param[in]  Width     ��ȣ���Ϊ0��ʹ����������ͼ��Ĭ�Ͽ��
	/// @param[in]  Height    �߶ȣ���Ϊ0��ʹ����������ͼ��Ĭ�ϸ߶�
	/// @param[in]  IsDynamic �Ƿ�Ϊ��̬����
	/// @param[in]  HasMipmap ����Mipmap�������ڼӿ�ͼ����Ⱦ���Զ�̬�������ȾĿ����Ч���Ƽ���Ϊtrue
	/// @param[out] pOut      ���������ָ��
	virtual fResult CreateTextureFromStream(f2dStream* pStream, fuInt Width, fuInt Height, fBool IsDynamic, fBool HasMipmap, f2dTexture** pOut)=0;

	/// @brief      ����һ����ȾĿ��
	/// @note       ��ȾĿ�����ڴ����Ⱦ���ݣ���������
	/// @warning    �����в�֧�ִ���Z������������ȾĿ���СӦ�ͺ󱸻�������Сһ��
	/// @param[in]  Width  ���
	/// @param[in]  Height �߶�
	/// @param[out] pOut   ���������ָ��
	virtual fResult CreateRenderTarget(fuInt Width, fuInt Height, f2dTexture** pOut)=0;

	/// @brief      ����һ��2D��Ⱦ��
	/// @param[in]  VertexBufferSize �ڲ����㻺������С����Ϊ0��Ĭ��
	/// @param[in]  IndexBufferSize  �ڲ�������������С����Ϊ0��Ĭ��
	/// @param[out] pOut             ���ָ��
	virtual fResult CreateGraphics2D(fuInt VertexBufferSize, fuInt IndexBufferSize, f2dGraphics2D** pOut)=0;

	/// @brief      ����һ������Ч��
	/// @param[in]  pStream Ч������(fx�ļ�)������ȡ������
	/// @param[out] pOut    �����Ч��
	/// @param[out] pErrOut ������Ϣ���ɿ�
	virtual fResult CreatePostEffect(f2dStream* pStream, f2dPostEffect** pOut, f2dStream** pErrOut)=0;

	// --- ��ͼ���� ---
	/// @brief     ���Z�������ȾĿ��
	/// @param[in] BackBufferColor ������ɫ
	/// @param[in] ZValue          Z���ֵ�����������Ӧȡ1.0f
	virtual fResult Clear(const fcyColor& BackBufferColor = 0, fFloat ZValue = 1.0f)=0;

	/// @brief     �����ȾĿ��
	/// @param[in] BackBufferColor ������ɫ
	virtual fResult ClearColor(const fcyColor& BackBufferColor = 0)=0;

	/// @brief     ���Z����
	/// @param[in] Value Z���ֵ�����������Ӧȡ1.0f
	virtual fResult ClearZBuffer(fFloat Value=1.0f)=0;

	/// @brief ����Ŀǰʹ���е���ȾĿ��
	/// @note  ���ΪĬ�Ϻ�̨������������NULL�����������ü���
	virtual f2dTexture* GetRenderTarget()=0;

	/// @brief ��һ����ȾĿ������ջ��������Ⱦ
	/// @note  һ����Ⱦ���ǰҪ��֤��ȾĿ��ջ�ÿ�
	virtual fResult PushRenderTarget(f2dTexture* pTarget)=0;

	/// @brief ��ջ����ȾĿ�굯��
	virtual fResult PopRenderTarget()=0;

	/// @brief ����Ŀǰ�Ĳü�����
	virtual fcyRect GetScissorRect()=0;

	/// @brief   ���òü�����
	/// @warning ����Ӧ��С��RenderTarget��С
	/// @note    �������û�������Сʱ��ֵ�ᱻ����
	virtual fResult SetScissorRect(const fcyRect& pRect)=0;

	// --- �豸���� ---
	/// @brief �����Կ�����
	virtual fcStrW GetDeviceName()=0;

	/// @brief ���ػ��������
	virtual fuInt GetBufferWidth()=0;

	/// @brief ���ػ������߶�
	virtual fuInt GetBufferHeight()=0;

	/// @brief �Ƿ񴰿ڻ�
	virtual fBool IsWindowed()=0;

	/// @brief ��ÿ���ݵȼ�
	virtual F2DAALEVEL GetAALevel()=0;

	/// @brief ��鿹����Ƿ�֧��
	/// @param[in] AALevel  Ҫ���Ŀ���ݵȼ�
	/// @param[in] Windowed �Ƿ񴰿�ģʽ
	virtual fBool CheckMultiSample(F2DAALEVEL AALevel, fBool Windowed)=0;

	/// @brief     ���軺����
	/// @param[in] Width    ���������
	/// @param[in] Height   �������߶�
	/// @param[in] Windowed ���ڻ�
	/// @param[in] VSync    ��ֱͬ��
	/// @param[in] AALevel  ����ݵȼ�
	virtual fResult SetBufferSize(fuInt Width, fuInt Height, fBool Windowed, fBool VSync, F2DAALEVEL AALevel)=0;

	/// @brief     ����
	/// @note      ��PNG��ʽ����
	/// @param[in] pStream �������
	virtual fResult SaveScreen(f2dStream* pStream)=0;

	/// @brief     ��������
	/// @note      ��PNG��ʽ����
	/// @warning   ��̬�������ڻᱻ������2���ݳ����ʱ��������澲̬�������岻��
	/// @param[in] pStream �������
	/// @param[in] pTex    Ҫ���������
	virtual fResult SaveTexture(f2dStream* pStream, f2dTexture* pTex)=0;

	/// @brief     ����UpdateLayeredWindow���·ֲ㴰��
	/// @note      Ҫ�������ڱ�����Ϊ�ֲ㴰��
	/// @param[in] KeyColor �ؼ�ɫ
	/// @param[in] Alpha    ͸����
	virtual fResult UpdateScreenToWindow(fcyColor KeyColor, fByte Alpha)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D���鷭תѡ��
////////////////////////////////////////////////////////////////////////////////
enum F2DSPRITEFLIP
{
	F2DSPRITEFLIP_NONE,  ///< @brief �޷�ת
	F2DSPRITEFLIP_H,     ///< @brief ˮƽ��ת
	F2DSPRITEFLIP_V,     ///< @brief ��ֱ��ת
	F2DSPRITEFLIP_HV     ///< @brief ˮƽ��ֱ��ת
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D����
////////////////////////////////////////////////////////////////////////////////
struct f2dSprite : public f2dInterface
{
	/// @brief ��þ���󶨵�����
	virtual f2dTexture* GetTexture()=0;

	/// @brief     ����һ���µ�����
	/// @param[in] pTex ����
	virtual fResult SetTexture(f2dTexture* pTex)=0;

	/// @brief ���ض�Ӧ����ľ���
	virtual fcyRect GetTexRect()=0;

	/// @brief ���ö�Ӧ����ľ���
	virtual fResult SetTexRect(fcyRect Rect)=0;

	/// @brief �����ȵ�
	virtual fcyVec2 GetHotSpot()=0;

	/// @brief     �����ȵ�
	/// @param[in] Point �ȵ�
	virtual fResult SetHotSpot(fcyVec2 Point)=0;

	/// @brief ���ط�ת��ʽ
	virtual F2DSPRITEFLIP GetFlipType()=0;
	
	/// @brief     ���÷�ת��ʽ
	/// @param[in] Type ��ת��ʽ
	virtual fResult SetFlipType(F2DSPRITEFLIP Type)=0;

	/// @brief ����Zֵ
	virtual fFloat GetZ()=0;

	/// @brief     ����Zֵ
	/// @param[in] Value �µ�Zֵ
	virtual fResult SetZ(fFloat Value)=0;

	/// @brief     ���ض������ɫ
	/// @param[in] Index ��������[0~3]������˳ʱ�뷽��λ
	virtual fcyColor GetColor(fuInt Index)=0;

	/// @brief     �������ж������ɫ
	/// @param[in] Color �����ɫ
	virtual fResult SetColor(fcyColor Color)=0;

	/// @brief ���ö�����ɫ
	/// @param[in] Index ��������[0~3]������˳ʱ�뷽��λ
	/// @param[in] Color �����ɫ
	virtual fResult SetColor(fuInt Index, fcyColor Color)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼ����ָ��
	/// @param[in] Dest   Ŀ�����
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyRect& Dest)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼ����ָ��
	/// @param[in] Dest   Ŀ�����
	/// @param[in] SubTex ����������[0~1, 0~1]
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyRect& Dest, const fcyRect& SubTex)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼ����ָ��
	/// @param[in] Center ������ʾ����
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼ����ָ��
	/// @param[in] Center ������ʾ����
	/// @param[in] Scale  ����
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼ����ָ��
	/// @param[in] Center ������ʾ����
	/// @param[in] Scale  ����
	/// @param[in] SubTex ����������[0~1, 0~1]
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, const fcyRect& SubTex)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph   ��ͼ����ָ��
	/// @param[in] Center   ������ʾ����
	/// @param[in] Scale    ����
	/// @param[in] Rotation ˳ʱ����ת�Ƕȣ������ơ�
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation)=0;
	
	/// @brief ���ƾ���
	/// @param[in] pGraph   ��ͼ����ָ��
	/// @param[in] Center   ������ʾ����
	/// @param[in] Scale    ����
	/// @param[in] Rotation ˳ʱ����ת�Ƕȣ������ơ�
	/// @param[in] SubTex   ����������[0~1, 0~1]
	virtual fResult Draw(f2dGraphics2D* pGraph, const fcyVec2& Center, const fcyVec2& Scale, fFloat Rotation, const fcyRect& SubTex)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D������Ⱦ��
////////////////////////////////////////////////////////////////////////////////
struct f2dFontRenderer : public f2dInterface
{
	/// @brief ����������
	virtual fuInt GetFaceCount()=0;

	/// @brief �����и�
	virtual fFloat GetLineHeight()=0;

	/// @brief �������û�������
	virtual f2dTexture* GetCache()=0;

	/// @brief ��������
	virtual void Cache(fcStrW Text)=0;

	/// @brief ���Zֵ
	virtual fFloat GetZ()=0;

	/// @brief     ����Zֵ
	/// @param[in] ZValue Zֵ
	virtual void SetZ(fFloat ZValue)=0;

	/// @brief     ��ö�����ɫ
	/// @param[in] Index ����[0~3]
	virtual fcyColor GetColor(fuInt Index)=0;

	/// @brief     ����������ɫ
	/// @param[in] Color ������ɫ
	virtual void SetColor(const fcyColor& Color)=0;

	/// @brief     ���ö�����ɫ
	/// @param[in] Index ����[0~3]
	/// @param[in] Color ��ɫ
	virtual void SetColor(fuInt Index, const fcyColor& Color)=0;

	/// @brief ��÷�ת��ʽ
	virtual F2DSPRITEFLIP GetFlipType()=0;

	/// @brief     ���÷�ת��ʽ
	/// @param[in] Type ��ת��ʽ
	virtual void SetFlipType(F2DSPRITEFLIP Type)=0;

	/// @brief ��������
	/// @param[in] pGraph   ��Ⱦ��
	/// @param[in] Text     ����
	/// @param[in] StartPos ������ʼ��׼
	virtual fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, const fcyVec2& StartPos)=0;

	/// @brief ��������
	/// @param[in]  pGraph   ��Ⱦ��
	/// @param[in]  Text     ����
	/// @param[in]  Count    ��������Ϊ-1��Ϊȫ������
	/// @param[in]  StartPos ������ʼ��׼
	/// @param[out] PosOut   ������ֹλ�ã��ɿ�
	virtual fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosOut)=0;

	/// @brief ��������
	/// @param[in]  pGraph   ��Ⱦ��
	/// @param[in]  Text     ����
	/// @param[in]  Count    ��������Ϊ-1��Ϊȫ������
	/// @param[in]  Bias     ��б�ǣ�0Ϊ����б
	/// @param[in]  StartPos ������ʼ��׼
	/// @param[out] PosOut   ������ֹλ�ã��ɿ�
	virtual fResult DrawTextW(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, fFloat Bias, const fcyVec2& StartPos, fcyVec2* PosOut)=0;

	/// @brief      �ھ����л�������
	/// @note       ����Ҫ�����ֻ����ھ��������У����ڳ����߽���Զ�����
	/// @warning    ����ֻ�ᱣ֤�ʴ�λ���ھ��������У�����֤����һ��ֻ��Ⱦ�ڷ�Χ��
	/// @param[in]  pGraph         ��Ⱦ��
	/// @param[in]  Text           ����
	/// @param[in]  DestRect       ���Ʒ�Χ
	/// @param[out] pCountRendered �ѻ��Ƶ�����������������ΪNULL
	virtual fResult DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, const fcyRect& DestRect, fuInt* pCountRendered)=0;

	/// @brief      �ھ����л�������
	/// @note       ����Ҫ�����ֻ����ھ��������У����ڳ����߽���Զ�����
	/// @warning    ����ֻ�ᱣ֤�ʴ�λ���ھ��������У�����֤����һ��ֻ��Ⱦ�ڷ�Χ��
	/// @param[in]  pGraph         ��Ⱦ��
	/// @param[in]  Text           ����
	/// @param[in]  Count          ��������Ϊ-1��Ϊȫ������
	/// @param[in]  DestRect       ���Ʒ�Χ
	/// @param[out] pCountRendered �ѻ��Ƶ�����������������ΪNULL
	virtual fResult DrawTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fuInt* pCountRendered)=0;

	/// @brief     ���Ƹ߼�����
	/// @note      ����ʹ��@��ǵĸ߼��������
	/// @param[in] pGraph        ��Ⱦ��
	/// @param[in] Text          ����
	/// @param[in] Count         ��������Ϊ-1��Ϊȫ������
	/// @param[in] StartPos      ������ʼ��׼
	/// @param[in] PosCache      λ�û��棬����ΪNULL
	/// @param[in] PosCacheCount λ�û�������
	virtual fResult DrawAdvancedText(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyVec2& StartPos, fcyVec2* PosCache, fuInt PosCacheCount)=0;

	/// @brief      �޶�������Ƹ߼�����
	/// @note       ����ʹ��@��ǵĸ߼��������
	/// @param[in]  pGraph         ��Ⱦ��
	/// @param[in]  Text           ����
	/// @param[in]  Count          ��������Ϊ-1��Ϊȫ������
	/// @param[in]  DestRect       Ŀ����Σ���֤�ʴ����������У�Խ��ʱ����
	/// @param[in]  PosCache       λ�û��棬����ΪNULL
	/// @param[in]  PosCacheCount  λ�û�������
	/// @param[out] pCountRendered ����Ⱦ��������������ΪNULL
	virtual fResult DrawAdvancedTextInRect(f2dGraphics2D* pGraph, fcStrW Text, fuInt Count, const fcyRect& DestRect, fcyVec2* PosCache, fuInt PosCacheCount, fuInt* pCountRendered)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�򵥼�������Ⱦ��
////////////////////////////////////////////////////////////////////////////////
struct f2dGeometryRenderer : public f2dInterface
{
	/// @brief ���Zֵ
	virtual fFloat GetZ()=0;

	/// @brief     ����Zֵ
	/// @param[in] ZValue Zֵ
	virtual void SetZ(fFloat ZValue)=0;

	/// @brief     ��û��ʵ���ɫ
	/// @param[in] Index ����[0~2]��0=�����ɫ��1=�м���ɫ��2=�ڲ���ɫ
	virtual fcyColor GetPenColor(fuInt Index)=0;

	/// @brief     ���û�����ɫ
	/// @param[in] Index ����[0~2]��0=�����ɫ��1=�м���ɫ��2=�ڲ���ɫ
	/// @param[in] Color ��ɫֵ
	virtual void SetPenColor(fuInt Index, const fcyColor& Color)=0;

	/// @brief ��û��ʴ�С
	virtual fFloat GetPenSize()=0;

	/// @brief     ���û��ʴ�С
	/// @param[in] Size ���ʴ�С
	virtual void SetPenSize(fFloat Size)=0;

	/// @brief     ����
	/// @param[in] pGraph ��ͼָ��
	/// @param[in] Begin  ���
	/// @param[in] End    �յ�
	virtual fResult DrawLine(f2dGraphics2D* pGraph, const fcyVec2& Begin, const fcyVec2& End)=0;

	/// @brief ���ƾ���
	/// @param[in] pGraph ��ͼָ��
	/// @param[in] Rect   ����
	virtual fResult DrawRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect)=0;

	/// @brief ����Բ
	/// @param[in] pGraph ��ͼָ��
	/// @param[in] Center ����
	/// @param[in] R      �뾶
	/// @param[in] Divide ϸ��
	virtual fResult DrawCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, fuInt Divide=50)=0;

	/// @brief ������
	/// @param[in] pGraph    ��ͼָ��
	/// @param[in] Rect      �������
	/// @param[in] pColorArr ��ɫ����[0~3]��˳ʱ���ĸ��ǵ���ɫ
	virtual fResult FillRectangle(f2dGraphics2D* pGraph, const fcyRect& Rect, const fcyColor* pColorArr)=0;

	/// @brief ���Բ
	/// @param[in] pGraph      ��ͼָ��
	/// @param[in] Center      ����
	/// @param[in] R           �뾶
	/// @param[in] CenterColor ������ɫ
	/// @param[in] BoundColor  �߽���ɫ
	/// @param[in] Divide      ϸ��
	virtual fResult FillCircle(f2dGraphics2D* pGraph, const fcyVec2& Center, float R, const fcyColor& CenterColor, const fcyColor& BoundColor, fuInt Divide=50)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ⱦ��
////////////////////////////////////////////////////////////////////////////////
struct f2dRenderer
{
	virtual f2dRenderDevice* GetDevice()=0;  ///< @brief �����Ⱦ�豸ָ��

	/// @brief      ����Sprite2D
	/// @param[in]  pTex �󶨵�����
	/// @param[out] pOut ������Sprite
	virtual fResult CreateSprite2D(f2dTexture* pTex, f2dSprite** pOut)=0;

	/// @brief      ����Sprite2D
	/// @param[in]  pTex �󶨵�����
	/// @param[in]  Org  ԭʼ�������
	/// @param[out] pOut ������Sprite
	virtual fResult CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, f2dSprite** pOut)=0;

	/// @brief      ����Sprite2D
	/// @param[in]  pTex    �󶨵�����
	/// @param[in]  Org     ԭʼ�������
	/// @param[in]  HotSopt �ȵ�
	/// @param[out] pOut    ������Sprite
	virtual fResult CreateSprite2D(f2dTexture* pTex, const fcyRect& Org, const fcyVec2& HotSopt, f2dSprite** pOut)=0;

	/// @brief      ����������Ⱦ��
	/// @param[in]  pStream    �����ļ���
	/// @param[in]  FontWidth  �����ȣ�����Ϊ0�����������߶�
	/// @param[in]  FontHeight ����߶ȣ�����Ϊ0�������������
	/// @param[in]  FaceIndex  ����������0����һ����Чֵ
	/// @param[out] pRenderer  �����������Ⱦ��ָ��
	virtual fResult CreateFontRenderer(f2dStream* pStream, fuInt FontWidth, fuInt FontHeight, fuInt FaceIndex, f2dFontRenderer** pRenderer)=0;

	/// @brief ������������Ⱦ��
	virtual fResult CreateGeometryRenderer(f2dGeometryRenderer** pOut)=0;
};

/// @}
