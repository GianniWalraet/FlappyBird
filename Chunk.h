#pragma once
#include <vector>
#include "structs.h"
#include "Obstacle.h"

class Background;

class Chunk
{
public:
	Chunk(int index, const Window& window);
	Chunk(const Chunk& other) = delete;
	Chunk& operator=(const Chunk& rhs) = delete;
	Chunk(Chunk&& other) = delete;
	Chunk& operator=(Chunk&& rhs) = delete;
	~Chunk();

	void Draw() const;

	void GenerateObstacles(const Window& window);

	int GetPosX() const;
	int GetIdx() const;
	Obstacle* GetObstacleInRange(const float playerPosX);

	static int GetWidth()
	{
		return m_ObstaclesPerChunk * (Obstacle::GetWidth() + m_Gap);
	}
private:
	int m_Idx;
	int m_ChunkPosX;

	static const int m_Gap = 200;

	static const int m_ObstaclesPerChunk = 10;
	std::vector<Obstacle*> m_pObstacles;

	Background* m_pBackground;

	int FindPos(int index, const float windowWidth);
};
