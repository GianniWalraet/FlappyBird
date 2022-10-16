#include "pch.h"
#include "Obstacle.h"
#include <iostream>
#include "utils.h"
#include "Texture.h"

Obstacle::Obstacle(const float xPos, const float windowHeight)
	: m_Pos{xPos, 0}
	, m_RectTop{}
	, m_RectBottom{}
	/*, m_pTubeUpT{}
	, m_pTubeDownT{}*/
{
	float yPos = float(rand() % ((int(windowHeight) / 4 * 3) + 1 - (int(windowHeight) / 4)) + (int(windowHeight) / 4));
	m_Pos.y = yPos;

	m_RectBottom = Rectf(m_Pos.x, 0, m_Width, m_Pos.y);
	m_RectTop = Rectf(m_Pos.x, m_Pos.y + m_Height, m_Width, windowHeight - m_Height);
}
Obstacle::~Obstacle()
{
	/*delete m_pTubeUpT;
	delete m_pTubeDownT;*/
}

void Obstacle::Draw() const
{
	utils::SetColor(Color4f(0, 0, 1, 1));
	utils::FillRect(m_RectBottom);
	utils::FillRect(m_RectTop);
}


Point2f Obstacle::GetPos() const
{
	return m_Pos;
}
Rectf Obstacle::GetCollisionRectTop() const
{
	return m_RectTop;
}
Rectf Obstacle::GetCollisionRectBottom() const
{
	return m_RectBottom;
}

//int Obstacle::GetWidth()
//{
//	return m_Width;
//}
//int Obstacle::GetHeight()
//{
//	return m_Height;
//}
