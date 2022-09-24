#include "pch.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	: m_Width(width)
	, m_Height(height)
	, m_LevelBoundaries{0,0,width,height}
{

}

void Camera::SetLevelBoundaries(const Rectf& levelBoundaries)
{
	m_LevelBoundaries = levelBoundaries;
}

void Camera::Transform(const Rectf& target) const
{
	Point2f bottomLeft{ Track(target) };

	ClampX(bottomLeft);
	ClampY(bottomLeft);

	Rectf camera{ bottomLeft.x, bottomLeft.y, m_Width, m_Height };

	glTranslatef(-camera.left, -camera.bottom, 0);
}


Point2f Camera::Track(const Rectf& target) const
{
	Point2f newPos{ (target.left + target.width/2) - m_Width/2, (target.bottom + target.height/2) - m_Height/2 };
	return newPos;
}
void Camera::ClampX(Point2f& bottomLeftPos) const
{
	if(m_LevelBoundaries.width > 0)
	{
		if (bottomLeftPos.x < m_LevelBoundaries.left)
		{
			bottomLeftPos.x = m_LevelBoundaries.left;
		}
		else if (bottomLeftPos.x + m_Width > m_LevelBoundaries.left + m_LevelBoundaries.width)
		{
			bottomLeftPos.x = m_LevelBoundaries.left + m_LevelBoundaries.width - m_Width;
		}
	}
}
void Camera::ClampY(Point2f& bottomLeftPos) const
{
	if (m_LevelBoundaries.height > 0)
	{
		if (bottomLeftPos.y < m_LevelBoundaries.bottom)
		{
			bottomLeftPos.y = m_LevelBoundaries.bottom;
		}
		else if (bottomLeftPos.y + m_Height > m_LevelBoundaries.bottom + m_LevelBoundaries.height)
		{
			bottomLeftPos.y = m_LevelBoundaries.bottom + m_LevelBoundaries.height - m_Height;
		}
	}
}

Point2f Camera::GetPos(const Rectf& target) const
{
	return Track(target);
}