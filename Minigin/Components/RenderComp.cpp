#include "Render.h"
#include "GameObject.h"
#include "TransformComp.h"

void enf::RenderComp::Awake()
{
	m_pTransform = m_pParent->GetComponent<TransformComp>();
}
