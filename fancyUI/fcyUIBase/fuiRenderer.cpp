#include "fuiRenderer.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

fuiRenderer::fuiRenderer(f2dRenderer* pRenderer, f2dGraphics2D* pGraph)
	: m_pRenderer(pRenderer), m_pGraph(pGraph)
{
	m_pRenderer->CreateGeometryRenderer(&m_pGeometryRenderer);
}

fuiRenderer::~fuiRenderer(void)
{
	FCYSAFEKILL(m_pGeometryRenderer);
}

void fuiRenderer::Begin()
{
	m_pGraph->GetWorldTransform(&m_OrgMat);
}

void fuiRenderer::End()
{
	m_pGraph->SetWorldTransform(m_OrgMat);

	m_TransMat = fcyMatrix4();
	while(!m_ClipRect.empty())
		PopClip();
}

f2dGraphics2D* fuiRenderer::GetGraph()
{
	return m_pGraph;
}

f2dGeometryRenderer* fuiRenderer::GetGeometryRenderer()
{
	return m_pGeometryRenderer;
}

fcyVec2* fuiRenderer::GetOffset()
{
	return (fcyVec2*)&m_TransMat._41;
}

void fuiRenderer::ApplyOffset(const fcyVec2& Offset)
{
	(*GetOffset()) += Offset;

	m_pGraph->SetWorldTransform(m_TransMat * m_OrgMat);
}

fBool fuiRenderer::PushClip(const fcyRect& Rect)
{
	fcyRect tCur(Rect.a + *GetOffset(), Rect.b + *GetOffset());
	fcyRect tIns;

	if(m_ClipRect.empty())
	{
		m_OrgClip = m_pRenderer->GetDevice()->GetScissorRect();
		
		// ��
		if(!m_OrgClip.Intersect(tCur, &tIns))
			return false;
	}
	else
	{
		// ��ö��˾���
		if(!m_ClipRect.top().Intersect(tCur, &tIns))
			return false;
	}

	// �ཻ�������ջ������
	m_ClipRect.push(tIns);

	// ��ϻ���
	m_pGraph->End();

	// ���òü�����
	m_pRenderer->GetDevice()->SetScissorRect(tIns);

	m_pGraph->Begin();

	return true;
}

void fuiRenderer::PopClip()
{
	fcyRect* tRect = NULL;

	m_ClipRect.pop();

	if(m_ClipRect.empty())
		tRect = &m_OrgClip;
	else
		tRect = &m_ClipRect.top();

	// ��ϻ���
	m_pGraph->End();

	// ���òü�����
	m_pRenderer->GetDevice()->SetScissorRect(*tRect);

	m_pGraph->Begin();
}
