#pragma once
#include <deque>
#include "structs.h"
#include "Obstacle.h"

class Chunk;

class ChunkManager
{
public:
	ChunkManager(const Point2f& cameraPosStart, const Window& window);
	ChunkManager(const ChunkManager& other) = delete;
	ChunkManager& operator=(const ChunkManager& rhs) = delete;
	ChunkManager(ChunkManager&& other) = delete;
	ChunkManager& operator=(ChunkManager&& rhs) = delete;
	~ChunkManager();

	void Draw() const;
	void Update(const Point2f& cameraPos, const Window& window);

	void Reset(const Point2f& cameraPos, const Window& window);

	Obstacle* GetObstacleInRange(const float playerPosX) const;
private:
	int m_Idx;
	std::deque<Chunk*> m_pChunks;

	void GenerateChunks(const Point2f& cameraPos, const Window& window);
	void AddChunks(const Point2f& cameraPos, const Window& window);
	void DeleteChunks(const Point2f& cameraPos);
};