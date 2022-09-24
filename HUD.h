#pragma once
#include "structs.h"

class Texture;

class HUD
{
public:
	HUD(const Window& window);
	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& rhs) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& rhs) = delete;
	~HUD();

	void Draw() const;
	void Update(float elapsedSec, int score);
private:
	const Window m_Window;
	int m_Score;

	bool m_DrawVolume;
	float m_MaxTime;
	float m_ElapsedTime;

	Texture* m_pScoreT;
	Texture* m_pScoreBGT;
	Texture* m_pVolumeT;

	void HandleVolume();
};
