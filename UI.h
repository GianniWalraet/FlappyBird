#pragma once

class Texture;

class UI
{
public:
	UI(const Window& window);
	UI(const UI& other) = delete;
	UI& operator=(const UI& other) = delete;
	UI(UI&& other) = delete;
	UI& operator=(UI&& other) = delete;
	~UI();

	void Draw() const;
	void Update();
private:
	const Window m_Window;

	Texture* m_pStartButtonT;
};
