#include "Render.h"
#include "GameObject.h"
#include "TransformComp.h"

void enf::RenderComp::Awake()
{
	m_TransformPtr = m_ParentPtr->GetComponent<TransformComp>();
}
