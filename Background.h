#pragma once
#include <vector>

class Texture;

class Background
{
public:
	Background( const Window& window);
	Background(const Background& other) = delete;
	Background& operator=(const Background& rhs) = delete;
	Background(Background&& other) = delete;
	Background& operator=(Background&& rhs) = delete;
	~Background();

	void Draw(const float xPos, const float chunkWidth) const;
private:
	const Window m_Window;
	Rectf m_Box;
	static const int m_DrawCount = 4;
	Texture* m_pTexture;
};

