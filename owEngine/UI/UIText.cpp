#include "stdafx.h"

// General
#include "UIText.h"

namespace
{
	const char* cDefaultText = "<empty>";
	const vec2  cDefaultOffset = vec2(0.0f, 0.0f);
	const vec4  cDefaultColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

CUITextNode::CUITextNode()
{
	m_Font = GetManager<IFontsManager>()->GetMainFont();
	m_Text = cDefaultText;
	m_Offset = cDefaultOffset;

	m_Material = std::make_shared<UI_Font_Material>();
	m_Material->SetWrapper(m_Material);
	m_Material->SetTexture(0, m_Font->GetTexture());
	m_Material->SetColor(cDefaultColor);
}

CUITextNode::~CUITextNode()
{}



//
// CUITextNode
//
void CUITextNode::SetFont(std::shared_ptr<CFontMesh> _font)
{
	_ASSERT(_font != nullptr);

	m_Font = _font;
	m_Material->SetTexture(0, m_Font->GetTexture());
}

void CUITextNode::SetText(const std::string& _text)
{
	m_Text = _text;
}

void CUITextNode::SetColor(cvec4 _color)
{
	m_Material->SetColor(_color);
}



//
// CUIBaseNode
//
bool CUITextNode::AcceptMesh(IVisitor& visitor)
{
	m_Font->SetMaterial(m_Material);

	vec2 _offset = m_Offset;

	for (uint32 i = 0; i < m_Text.length(); i++)
	{
		uint8 ch = m_Text.c_str()[i];
		m_Material->SetOffset(_offset);
		_offset.x += static_cast<float>(m_Font->GetCharWidth(ch)) + 0.01f;

		m_Font->Accept(visitor, 0, 0, (ch) * 6, 6);
	}

	return true;
}
