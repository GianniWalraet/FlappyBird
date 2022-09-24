#include "pch.h"
#include "Chunk.h"
#include <iostream>
#include "Background.h"

Chunk::Chunk(int index, const Window& window)
	: m_Idx{index}
	, m_ChunkPosX{}
	, m_pObstacles{}
	, m_pBackground{new Background(window)}
{
	GenerateObstacles(window);
}
Chunk::~Chunk()
{
	for (size_t i = 0; i < m_pObstacles.size(); ++i)
	{
		delete m_pObstacles[i];
		m_pObstacles[i] = nullptr;
	}
	m_pObstacles.clear();

	delete m_pBackground;
}

void Chunk::Draw() const
{
	m_pBackground->Draw(this->GetPosX(), this->GetWidth());
	for (const Obstacle* element : m_pObstacles)
	{
		element->Draw();
	}
}

void Chunk::GenerateObstacles(const Window& window)
{
	int obstacleIdx = m_Idx * m_ObstaclesPerChunk;

	for (int i = obstacleIdx; i < (obstacleIdx + m_ObstaclesPerChunk); i++)
	{
		m_pObstacles.push_back(new Obstacle(float(FindPos(i, window.width)), window.height));

		if (i == obstacleIdx)
		{
			m_ChunkPosX = FindPos(i, window.width) - m_Gap;
		}
	}
}

int Chunk::GetPosX() const
{
	return m_ChunkPosX;
}
int Chunk::GetIdx() const
{
	return m_Idx;
}
Obstacle* Chunk::GetObstacleInRange(const float playerPosX)
{
	return m_pObstacles[(int(playerPosX) - m_ChunkPosX) / (m_Gap + Obstacle::GetWidth())];
}


int Chunk::FindPos(int index, const float windowWidth)
{
	int gap{ 100 };
	return (int(windowWidth) + gap) + m_Gap + (m_Gap + Obstacle::GetWidth()) * index;
}