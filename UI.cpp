#include "pch.h"
#include "UI.h"
#include "Texture.h"


UI::UI(const Window& window)
	: m_Window{window}
	, m_pStartButtonT{new Texture("Resources/Textures/Menu/StartButton.png")}
{

}

UI::~UI()
{
	delete m_pStartButtonT;
}

void UI::Draw() const
{
	m_pStartButtonT->Draw(Rectf(m_Window.width / 2 - m_pStartButtonT->GetWidth(), m_Window.height / 3 - m_pStartButtonT->GetHeight(), m_pStartButtonT->GetWidth() * 2, m_pStartButtonT->GetHeight() * 2));
}

void UI::Update()
{

}