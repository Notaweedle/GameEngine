#include "pch.h"
#include "Audio.h"
#include <fmod.hpp>
#include <iostream>

namespace nu
{
	bool Audio::Initialize()
	{
		FMOD::System_Create(&m_system);
		FMOD_RESULT result = m_system->init(512, FMOD_INIT_NORMAL, nullptr);
		if (result != FMOD_OK)
		{
			std::cerr << "FMOD init failed" << std::endl;
			return false;
		}
		return true;
	}

	void Audio::ShutDown()
	{
		for (auto& [name, sound] : m_sounds)
		{
			sound->release();
		}
		m_sounds.clear();

		if (m_system)
		{
			m_system->close();
			m_system->release();
			m_system = nullptr;
		}
	}

	void Audio::LoadSound(const std::string& name, const std::string& path)
	{
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_system->createSound(path.c_str(), FMOD_DEFAULT, nullptr, &sound);
		if (result != FMOD_OK)
		{
			std::cerr << "Failed to load sound: " << path << std::endl;
			return;
		}
		m_sounds[name] = sound;
	}

	void Audio::Update()
	{
		if (m_system) m_system->update();
	}

	void Audio::PlaySound(const std::string& name)
	{
		auto it = m_sounds.find(name);
		if (it == m_sounds.end()) return;

		m_system->playSound(it->second, nullptr, false, nullptr);
	}

	void Audio::PlayMusic(const std::string& name)
	{
		auto it = m_sounds.find(name);
		if (it == m_sounds.end()) return;

		it->second->setMode(FMOD_LOOP_NORMAL);
		m_system->playSound(it->second, nullptr, false, nullptr);
	}
}
