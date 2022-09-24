#pragma once
#include "Texture.h"
#include "structs.h"

class Sprite
{
public:
	Sprite();
	Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec);
	~Sprite();
	Sprite(const Sprite& rhs) = delete;
	Sprite(Sprite&& other) noexcept;
	Sprite& operator=(const Sprite& rhs) = delete;
	Sprite& operator=(Sprite&& rhs) noexcept;

	void Update(float elapsedSec);
	void Draw(const Point2f& pos, float scale) const;

	float GetFrameWidth() const;
	float GetFrameHeight() const;

	void SetFramesPerSec(float& frames);
private:
	Texture* m_pTexture;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int m_ActFrame;
};
