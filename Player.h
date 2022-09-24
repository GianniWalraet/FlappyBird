#pragma once
#include "structs.h"
#include "Vector2f.h"

class Texture;
class SoundEffect;
class Sprite;

class Player
{
public:
	Player(const Point2f& startPos, const Vector2f& startVelocity);
	Player(const Player& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player(Player&& other) = delete;
	Player& operator=(Player&& rhs) = delete;
	~Player();

	void Draw() const;
	void Update(float elapsedSec, bool gamePaused);

	void DoJump();
	void Reset();

	void IncrementScore();

	Point2f GetPos() const;
	float GetWidth() const;
	float GetHeight() const;
	int GetScore() const;

	void SetPos(const Point2f& newPos);
	void SetVelocity(const Vector2f& newVelocity);
private:
	Rectf m_Shape;
	float m_Scale;
	Point2f m_StartPos;
	Vector2f m_StartVelocity;
	Vector2f m_Velocity;
	Vector2f m_Acceleration;
	float m_JumpSpeed;

	int m_Score;

	bool m_IsDead;

	Sprite* m_pSprite;

	void ApplyGravity(float elapsedSec);
};