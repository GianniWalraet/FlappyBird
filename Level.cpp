#include "pch.h"
#include "Level.h"
#include <iostream>
#include "Texture.h"
#include "utils.h"
#include "Obstacle.h"
#include "Player.h"
#include "ChunkManager.h"
#include "Background.h"


Level::Level(const Window& window, const Point2f& cameraPos)
	: m_Window(window)
	, m_Boundaries(0, 0, window.width, window.height)
	, m_pChunkManager{ new ChunkManager(cameraPos, window) }
	, m_pNearestObstacle{}
	, m_pBackground{ new Background(window) }
{
}

Level::~Level()
{
	delete m_pChunkManager;
}

void Level::Draw(const Point2f& cameraPos) const
{
	m_pChunkManager->Draw();
	m_pBackground->Draw(0.f, 200.f);
	m_pBackground->Draw(200.f, 200.f);
}
bool Level::Update(const Point2f& cameraPos, const Window& window, Player* player)
{
	m_pChunkManager->Update(cameraPos, window);
	bool c1 = HandleCollision(player, cameraPos);
	bool c2 = HandleObstacleCollision(player, cameraPos);

	return c1 || c2;
}

bool Level::HandleCollision(Player* player, const Point2f& cameraPos)
{
	Rectf playerShape{ player->GetPos().x, player->GetPos().y, player->GetWidth(), player->GetHeight() };

	if (playerShape.bottom + playerShape.height > m_Boundaries.height || playerShape.bottom < m_Boundaries.bottom)
	{
		ResetLevel(player, cameraPos);
		return true;
	}

	return false;
}

bool Level::HandleObstacleCollision(Player* player, const Point2f& cameraPos)
{
	Obstacle* temp = m_pChunkManager->GetObstacleInRange(player->GetPos().x);
	Rectf playerShape{ player->GetPos().x, player->GetPos().y, player->GetWidth(), player->GetHeight() };
	
	if (temp != nullptr)
	{
		if ((utils::IsOverlapping(playerShape, temp->GetCollisionRectTop()) || utils::IsOverlapping(playerShape, temp->GetCollisionRectBottom())))
		{
			ResetLevel(player, cameraPos);
			return true;
		}
		else
		{
			if (m_pNearestObstacle != temp)
			{
				if (m_pNearestObstacle != nullptr)
				{
					player->IncrementScore();
				}
				m_pNearestObstacle = temp;
			}
		}
	}
	
	return false;
}


void Level::ResetLevel(Player* player, const Point2f& cameraPos)
{
	player->Reset();
	m_pChunkManager->Reset(cameraPos, m_Window);
	m_pNearestObstacle = nullptr;
}