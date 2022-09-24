#include "pch.h"
#include "ChunkManager.h"
#include <iostream>
#include "utils.h"
#include "Chunk.h"


ChunkManager::ChunkManager(const Point2f& cameraPosStart, const Window& window)
	: m_Idx{}
	, m_pChunks{}
{
	GenerateChunks(cameraPosStart, window);
}
ChunkManager::~ChunkManager()
{
	for (size_t i = 0; i < m_pChunks.size(); i++)
	{
		delete m_pChunks[i];
		m_pChunks[i] = nullptr;
	}
	m_pChunks.clear();
}

void ChunkManager::Draw() const
{
	for (const Chunk* chunk : m_pChunks)
	{
		chunk->Draw();
	}
}

void ChunkManager::Update(const Point2f& cameraPos, const Window& window)
{
	AddChunks(cameraPos, window);
	DeleteChunks(cameraPos);
}

void ChunkManager::Reset(const Point2f& cameraPos, const Window& window)
{
	size_t size = m_pChunks.size();

	for (size_t i = 0; i < size; i++)
	{
		delete m_pChunks[0];
		m_pChunks[0] = nullptr;
		m_pChunks.pop_front();
	}
	m_pChunks.clear();

	GenerateChunks(cameraPos, window);
}

Obstacle* ChunkManager::GetObstacleInRange(const float playerPosX) const
{
	for (size_t i = 0; i < m_pChunks.size(); i++)
	{
		if (playerPosX >= m_pChunks[i]->GetPosX() && playerPosX <= (m_pChunks[i]->GetPosX() + Chunk::GetWidth()))
		{
			return m_pChunks[i]->GetObstacleInRange(playerPosX);
		}
	}

	return nullptr;
}

void ChunkManager::GenerateChunks(const Point2f& cameraPos, const Window& window)
{
	int i = 0;
	do
	{
		m_pChunks.push_back(new Chunk(i, window));

		++i;

	} while (m_pChunks.back()->GetPosX() + Chunk::GetWidth() < cameraPos.x + window.width);
}
void ChunkManager::AddChunks(const Point2f& cameraPos, const Window& window)
{
	if (cameraPos.x + window.width >= m_pChunks.back()->GetPosX())
	{
		m_pChunks.push_back(new Chunk((m_pChunks.back()->GetIdx() + 1), window));
	}
}
void ChunkManager::DeleteChunks(const Point2f& cameraPos)
{
	if (cameraPos.x > (m_pChunks.front()->GetPosX() + Chunk::GetWidth()))
	{
		delete m_pChunks.front();
		m_pChunks.front() = nullptr;
		m_pChunks.pop_front();
	}
}