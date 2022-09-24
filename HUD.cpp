#include "pch.h"
#include "HUD.h"
#include <iostream>
#include "Texture.h"
#include "SoundManager.h"

HUD::HUD(const Window& window)
	: m_Window{ window }
	, m_Score{}
	, m_DrawVolume{false}
	, m_MaxTime{ 8.f }
	, m_ElapsedTime{}
	, m_pScoreT{new Texture("0", "Resources/Textures/TextFont/FlappyBirdy.ttf", 100, Color4f(1,1,1,1)) }
	, m_pScoreBGT{ new Texture("0", "Resources/Textures/TextFont/FlappyBirdy.ttf", 110, Color4f(0,0,0,1)) }
	, m_pVolumeT{new Texture(std::to_string(SoundManager::Get()->GetVolume()), "Resources/Textures/TextFont/Andy_Bold.ttf", 30, Color4f(1,1,0,1)) }
	
{

}
HUD::~HUD()
{
	delete m_pScoreT;
	delete m_pScoreBGT;
}

void HUD::Draw() const
{
	Point2f scorePos{};
	Point2f scorePosBG{};
	float gap{ 10 };
	scorePos.x = m_Window.width / 2 - m_pScoreT->GetWidth() / 2;
	scorePos.y = m_Window.height - m_pScoreT->GetHeight() - gap;
	scorePosBG.x = m_Window.width / 2 - m_pScoreBGT->GetWidth() / 2;
	scorePosBG.y = m_Window.height - m_pScoreBGT->GetHeight() - gap;

	m_pScoreBGT->Draw(scorePosBG);
	m_pScoreT->Draw(scorePos);

	if (m_DrawVolume)
	{
		m_pVolumeT->Draw(Point2f(0, 0));
	}
}

void HUD::Update(float elapsedSec, int score)
{
	if (score == (m_Score + 1) || score == 0)
	{
		delete m_pScoreT;
		m_pScoreT = new Texture(std::to_string(score), "Resources/Textures/TextFont/FlappyBirdy.ttf", 100, Color4f(1, 1, 1, 1));

		delete m_pScoreBGT;
		m_pScoreBGT = new Texture(std::to_string(score), "Resources/Textures/TextFont/FlappyBirdy.ttf", 110, Color4f(0, 0, 0, 1));
	}
	m_Score = score;

	m_ElapsedTime += elapsedSec;
	if (m_ElapsedTime > m_MaxTime)
	{
		m_DrawVolume = false;
		m_ElapsedTime = 0.f;
	}

	HandleVolume();
}


void HUD::HandleVolume()
{
	const Uint8* pKeysStates = SDL_GetKeyboardState(nullptr);

	if (pKeysStates[SDL_SCANCODE_UP])
	{
		m_DrawVolume = true;
		delete m_pVolumeT;
		m_pVolumeT = new Texture("Volume:" + std::to_string(SoundManager::Get()->GetVolume()), "Resources/Textures/TextFont/Andy_Bold.ttf", 30, Color4f(1, 1, 0, 1));
	}
	else if (pKeysStates[SDL_SCANCODE_DOWN])
	{
		m_DrawVolume = true;
		delete m_pVolumeT;
		m_pVolumeT = new Texture("Volume:" + std::to_string(SoundManager::Get()->GetVolume()), "Resources/Textures/TextFont/Andy_Bold.ttf", 30, Color4f(1, 1, 0, 1));
	}
}
