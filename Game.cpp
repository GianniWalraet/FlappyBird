#include "pch.h"
#include "Game.h"
#include "structs.h"
#include "Player.h"
#include "Level.h"
#include "SoundManager.h"

Game::Game(const Window& window)
	:m_Window{ window }
	, m_pPlayer{}
	, m_pLevel{}
	, m_HUD{ window }
	, m_UI{ window }
	, m_IsPaused{ true }
	, m_HasJumped{ false }
	, m_Camera{ window.width, window.height }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	Point2f startPos{ m_Window.width / 2, m_Window.height / 2 };
	Vector2f startVelocity{ 100.f, 0.f };

	m_pPlayer = new Player(startPos, startVelocity);
	m_pLevel = new Level(m_Window, m_Camera.GetPos(Rectf(m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetWidth(), m_pPlayer->GetHeight())));

	m_Camera.SetLevelBoundaries(Rectf(0, 0, 0, m_Window.height));

	SoundManager::Get()->SetVolume(20);
}

void Game::Cleanup()
{
	delete m_pPlayer;
	delete m_pLevel;
	delete SoundManager::Get();
}

void Game::Update(float elapsedSec)
{
	if (!m_IsPaused)
	{
		m_IsPaused = m_pLevel->Update(m_Camera.GetPos(Rectf(m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetWidth(), m_pPlayer->GetHeight())), m_Window, m_pPlayer);
	}

	m_pPlayer->Update(elapsedSec, m_IsPaused);
	m_HUD.Update(elapsedSec, m_pPlayer->GetScore());
	m_UI.Update();
}

void Game::Draw() const
{
	ClearBackground();

	Rectf cameraTarget{ m_pPlayer->GetPos().x, m_pPlayer->GetPos().y, m_pPlayer->GetWidth(), m_pPlayer->GetHeight() };

	glPushMatrix();
	m_Camera.Transform(cameraTarget);
	m_pLevel->Draw(m_Camera.GetPos(cameraTarget));
	m_pPlayer->Draw();
	glPopMatrix();

	m_HUD.Draw();

	if (m_IsPaused)
		m_UI.Draw();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;

	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	case SDLK_SPACE:
		break;
	case SDLK_ESCAPE:
		m_IsPaused = !m_IsPaused;
		break;
	}
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_UP:
		SoundManager::Get()->IncreaseVolume();
		break;
	case SDLK_DOWN:
		SoundManager::Get()->DecreaseVolume();
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	case SDLK_SPACE:
		break;
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		m_pPlayer->DoJump();
		m_IsPaused = false;
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	switch (e.button)
	{
	case SDL_BUTTON_LEFT:
		if (!m_IsPaused)
		{
			m_HasJumped = false;
		}
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		break;
	}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
