#pragma once
#include "structs.h"

class Texture;

class Obstacle
{
public:
	Obstacle(const float xPos, const float windowHeight);
	Obstacle(const Obstacle& other) = delete;
	Obstacle& operator=(const Obstacle& rhs) = delete;
	Obstacle(Obstacle&& other) = delete;
	Obstacle& operator=(Obstacle&& rhs) = delete;
	~Obstacle();

	void Draw() const;

	Point2f GetPos() const;
	Rectf GetCollisionRectTop() const;
	Rectf GetCollisionRectBottom() const;

	static int GetWidth()
	{
		return m_Width;
	}
	static int GetHeight()
	{
		return m_Height;
	}
private:
	Point2f m_Pos;
	Rectf m_RectTop;
	Rectf m_RectBottom;

	static const int m_Width = 50;
	static const int m_Height = 100;

	/*Texture* m_pTubeUpT;
	Texture* m_pTubeDownT;*/
};