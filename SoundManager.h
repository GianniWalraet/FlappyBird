#pragma once
#include <iostream>
#include "SoundEffect.h"
#include "SoundStream.h"
#include <map>

enum class Sounds
{
	point = 0,
	hit = 1,
	swoosh = 2,
	wing = 3
};


class SoundManager
{
public:
	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) = delete;
	SoundManager& operator=(SoundManager&& other) = delete;
	~SoundManager()
	{
		for (std::pair<const Sounds, SoundEffect*>& element : m_pSoundsMap)
		{
			delete element.second;
		}
		m_pSoundsMap.clear();
	}

	static SoundManager* Get()
	{
		if (!m_Instance)
		{
			m_Instance = new SoundManager();
		}
		return m_Instance;
	}

	void AddSoundEffect(const std::string filePath, const Sounds& soundName)
	{
		m_pSoundsMap[soundName] = new SoundEffect(filePath);
	}

	void PlaySoundEffect(const Sounds& soundName)
	{
		m_pSoundsMap[soundName]->Play(0);
	}

	int GetVolume() const
	{
		int defaultVolume{ 50 };
		if (m_pSoundsMap.size() != 0)
		{
			return m_pSoundsMap.begin()->second->GetVolume();
		}
		return defaultVolume;
	}

	void SetVolume(int volume)
	{
		for (const std::pair<const Sounds, SoundEffect*>& element : m_pSoundsMap)
		{
			element.second->SetVolume(volume);
		}
	}
	void IncreaseVolume()
	{
		int add{ 5 };

		for (const std::pair<const Sounds, SoundEffect*>& element : m_pSoundsMap)
		{
			if (element.second->GetVolume() < 100)
			{
				element.second->SetVolume(element.second->GetVolume() + add);
			}
		}
	}
	void DecreaseVolume()
	{
		int subtr{ 5 };

		for (const std::pair<const Sounds, SoundEffect*>& element : m_pSoundsMap)
		{
			if (element.second->GetVolume() > 0)
			{
				element.second->SetVolume(element.second->GetVolume() - subtr);
			}
		}
	}
	
private:
	SoundManager()
	{

	}

	static SoundManager* m_Instance;

	std::map<Sounds, SoundEffect*> m_pSoundsMap;
};