#pragma once
#include "structs.h"
#include "Vector2f.h"
#include <vector>

class Texture;
class ChunkManager;
class Player;
class Obstacle;
class Background;

class Level
{
public:
	Level(const Window& window, const Point2f& cameraPos);
	Level(const Level& other) = delete;
	Level& operator=(const Level& rhs) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& rhs) = delete;
	~Level();

	void Draw(const Point2f& cameraPos) const;
	bool Update(const Point2f& cameraPos, const Window& window, Player* player);
private:
	const Window m_Window;
	Rectf m_Boundaries;
	
	ChunkManager* m_pChunkManager;
	Obstacle* m_pNearestObstacle;

	Background* m_pBackground;
	
	bool HandleCollision(Player* player, const Point2f& cameraPos);
	bool HandleObstacleCollision(Player* player, const Point2f& cameraPos);

	void ResetLevel(Player* player, const Point2f& cameraPos);
};
