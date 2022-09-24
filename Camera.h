#pragma once
#include "structs.h"

class Camera
{
public:
	Camera(float width, float height);

	void SetLevelBoundaries(const Rectf& levelBoundaries);
	void Transform(const Rectf& target) const;

	Point2f GetPos(const Rectf& target) const;
private:
	float m_Width;
	float m_Height;
	Rectf m_LevelBoundaries;

	Point2f Track(const Rectf& target) const;

	void ClampX(Point2f& bottomLeftPos) const;
	void ClampY(Point2f& bottomLeftPos) const;
};