#include "pch.h"
#include "Player.h"
#include <iostream>
#include "Texture.h"
#include "utils.h"
#include "SoundEffect.h"
#include "Sprite.h"
#include "SoundManager.h"

Player::Player(const Point2f& startPos, const Vector2f& startVelocity)
	: m_Shape{ startPos.x, startPos.y, 0, 0 }
	, m_Scale{ 2.f }
	, m_StartPos{ startPos }
	, m_StartVelocity{ startVelocity }
	, m_Velocity{ startVelocity }
	, m_Acceleration{ 2.f, -981.f }
	, m_JumpSpeed{ 300.f }
	, m_Score{}
	, m_pSprite{}
{
	int cols{ 3 };
	int rows{ 1 };
	float frameSec{ 1 / 5.f };
	m_pSprite = new Sprite("Resources/Textures/Player/FlappyBirdSprite.png", cols, rows, frameSec);

	Texture birdTexture{ "Resources/Textures/Player/FlappyBirdSprite.png" };
	m_Shape.width = birdTexture.GetWidth() / cols * m_Scale;
	m_Shape.height = birdTexture.GetHeight() / rows * m_Scale;

	SoundManager::Get()->AddSoundEffect("Resources/Audio/SoundEffects/point.mp3", Sounds::point);
	SoundManager::Get()->AddSoundEffect("Resources/Audio/SoundEffects/wing.mp3", Sounds::wing);
	SoundManager::Get()->AddSoundEffect("Resources/Audio/SoundEffects/hit.mp3", Sounds::hit);

}

Player::~Player()
{
	delete m_pSprite;
}

void Player::Draw() const
{
	utils::SetColor(Color4f(1, 1, 0, 1));
	utils::DrawRect(m_Shape.left, m_Shape.bottom, m_Shape.width, m_Shape.height);
	m_pSprite->Draw(Point2f(m_Shape.left, m_Shape.bottom), m_Scale);
	//m_pTexture->Draw(m_Shape);
}

void Player::Update(float elapsedSec, bool gamePaused)
{
	if (!gamePaused)
	{
		ApplyGravity(elapsedSec);
		m_Shape.left += m_Velocity.x * elapsedSec;
		m_Shape.bottom += m_Velocity.y * elapsedSec;
	}

	m_pSprite->Update(elapsedSec);
}

void Player::DoJump()
{
	SoundManager::Get()->PlaySoundEffect(Sounds::wing);
	m_Velocity.y = m_JumpSpeed;
}
void Player::Reset()
{
	SoundManager::Get()->PlaySoundEffect(Sounds::hit);
	m_Shape.left = m_StartPos.x;
	m_Shape.bottom = m_StartPos.y;
	m_Velocity = m_StartVelocity;
	m_Score = 0;
}

void Player::IncrementScore()
{
	std::cout << "Score Incremented\n";
	SoundManager::Get()->PlaySoundEffect(Sounds::point);
	++m_Score;
}

void Player::ApplyGravity(float elapsedSec)
{
	m_Velocity.y += m_Acceleration.y * elapsedSec;

	if (m_Velocity.x < 200.f)
	{
		m_Velocity.x += m_Acceleration.x * elapsedSec;
	}
}


Point2f Player::GetPos() const
{
	return Point2f(m_Shape.left, m_Shape.bottom);
}
float Player::GetWidth() const
{
	return m_Shape.width;
}
float Player::GetHeight() const
{
	return m_Shape.height;
}
int Player::GetScore() const
{
	return m_Score;
}

void Player::SetPos(const Point2f& newPos)
{
	m_Shape.left = newPos.x;
	m_Shape.bottom = newPos.y;
}
void Player::SetVelocity(const Vector2f& newVelocity)
{
	m_Velocity = newVelocity;
}
