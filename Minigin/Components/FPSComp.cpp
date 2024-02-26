#include "FPSComp.h"
#include "GameObject.h"
#include "TextRenderComp.h"

enf::FPSComp::FPSComp(const std::shared_ptr<Font>& pFont)
{
	m_pTextRenderComp = GetParent()->AddComponent<TextRenderComp>(pFont);
}
