#include "TransformComp.h"
#include "Renderer.h"

void enf::TransformComp::SetPosition(const glm::vec3& pos)
{
	if (m_position.z != pos.z)
	{
		Renderer::GetInstance().SetDirty();
	}

	m_position = pos;
}
