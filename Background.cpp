#include "pch.h"
#include "Background.h"
#include <iostream>
#include "Texture.h"

Background::Background( const Window& window)
	: m_Window{window}
	, m_Box{}
	, m_pTexture{new Texture("Resources/Textures/Background/Background_0.png")}
{
	m_Box.width = m_pTexture->GetWidth() * 2;
	m_Box.height = m_pTexture->GetHeight() * 2;
}
Background::~Background()
{
	delete m_pTexture;
}

void Background::Draw(const float xPos, const float chunkWidth) const
{
	float increment{m_pTexture->GetWidth() * 2};
	float x{};
	float i{};

	while (x < xPos + chunkWidth)
	{
		m_pTexture->Draw((Rectf(xPos + x, m_Box.bottom, m_Box.width, m_Box.height)));
		x += increment;
	}
}
