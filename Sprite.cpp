#include "pch.h"
#include "Sprite.h"
#include <iostream>

Sprite::Sprite()
	: m_pTexture{}
	, m_Cols{ }
	, m_Rows{ }
	, m_FrameSec{ }
	, m_AccuSec{}
	, m_ActFrame{}
{

}

Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec)
	: m_pTexture{ new Texture{ filename } }
	, m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_FrameSec{ frameSec }
	, m_AccuSec{}
	, m_ActFrame{}
{
	m_pTexture->IsCreationOk();
}

//Sprite::Sprite(const Sprite& rhs)
//	: m_pTexture{ rhs.m_pTexture }
//	, m_Cols{ rhs.m_Cols }
//	, m_Rows{ rhs.m_Rows }
//	, m_FrameSec{ rhs.m_FrameSec }
//	, m_AccuSec{ rhs. m_AccuSec }
//	, m_ActFrame{ rhs.m_ActFrame }
//{
//	std::cout << "Copy constructor\n";
//}
Sprite::Sprite(Sprite&& other) noexcept
	: m_pTexture{other.m_pTexture }
	, m_Cols{ other.m_Cols }
	, m_Rows{ other.m_Rows }
	, m_FrameSec{ other.m_FrameSec }
	, m_AccuSec{ other.m_AccuSec }
	, m_ActFrame{ other.m_ActFrame }
{
	std::cout << "Move constructor\n";

	other.m_pTexture = nullptr;
	other.m_Cols = 0;
	other.m_Rows = 0;
	other.m_FrameSec = 0;
	other.m_AccuSec = 0;
	other.m_ActFrame = 0;
}
//Sprite& Sprite::operator=(const Sprite& rhs) 
//{
//	if (this != &rhs)
//	{
//		std::cout << "Assignment operator\n";
//
//		delete m_pTexture;
//		m_pTexture = rhs.m_pTexture;
//		m_Cols = rhs.m_Cols;
//		m_Rows = rhs.m_Rows;
//		m_FrameSec = rhs.m_FrameSec;
//		m_AccuSec = rhs.m_AccuSec;
//		m_ActFrame = rhs.m_ActFrame;
//	}
//	return *this;
//}
Sprite& Sprite::operator=(Sprite&& rhs) noexcept
{
	if (this != &rhs)
	{
		std::cout << "Assignment operator\n";

		delete m_pTexture;
		m_pTexture = rhs.m_pTexture;
		m_Cols = rhs.m_Cols;
		m_Rows = rhs.m_Rows;
		m_FrameSec = rhs.m_FrameSec;
		m_AccuSec = rhs.m_AccuSec;
		m_ActFrame = rhs.m_ActFrame;
		rhs.m_pTexture = nullptr;
		rhs.m_Cols = 0;
		rhs.m_Rows = 0;
		rhs.m_FrameSec = 0;
		rhs.m_AccuSec = 0;
		rhs.m_ActFrame = 0;
	}
	return *this;
}

Sprite::~Sprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;

	if (m_AccuSec > m_FrameSec)
	{
		++m_ActFrame %= (m_Cols * m_Rows);
		m_AccuSec -= m_FrameSec;
	}
}
void Sprite::Draw(const Point2f& pos, float scale) const
{
	Rectf srcRect{ }; // welk deeltje uit de image knippen
	srcRect.width = GetFrameWidth();
	srcRect.height = GetFrameHeight();
	int col{ m_ActFrame % m_Cols }; // col van het frame
	int row{ m_ActFrame / m_Cols }; // row van het current frame
	srcRect.left = srcRect.width * col;
	srcRect.bottom = srcRect.height * (row + 1);

	Rectf dstRect{};
	dstRect.left = pos.x;
	dstRect.bottom = pos.y;
	dstRect.width = srcRect.width * scale;
	dstRect.height = srcRect.height * scale;

	m_pTexture->Draw(dstRect, srcRect);
}

float Sprite::GetFrameWidth() const
{
	return (m_pTexture->GetWidth() / m_Cols);
}
float Sprite::GetFrameHeight() const
{
	return (m_pTexture->GetHeight() / m_Rows);
}

void Sprite::SetFramesPerSec(float& frames)
{
	m_FrameSec = (1.f / frames);
}