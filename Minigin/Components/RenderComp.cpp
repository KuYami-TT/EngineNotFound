#include "RenderComp.h"
#include "Renderer.h"

enf::RenderComp::~RenderComp()
{
	m_RendererPtr->RemoveOutRenderList(this);
}

void enf::RenderComp::Awake()
{
	m_RendererPtr = &Renderer::Get();
	m_RendererPtr->AddToRenderList(this);
}