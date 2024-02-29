#include "RenderComp.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TransformComp.h"

enf::RenderComp::~RenderComp()
{
	m_RendererPtr->RemoveOutRenderList(this);
}

void enf::RenderComp::Awake()
{
	m_TransformPtr = GetParent()->GetComponent<TransformComp>();

	m_RendererPtr = &Renderer::GetInstance();
	m_RendererPtr->AddToRenderList(this);
}