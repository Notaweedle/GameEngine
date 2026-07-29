#pragma once
#include <string>
#include <map>

namespace FMOD { class System; class Sound; }

namespace nu
{
	class Audio
	{
	public:
		bool Initialize();
		void ShutDown();
		void LoadSound(const std::string& name, const std::string& path);
		void Update();
		void PlaySound(const std::string& name);
		void PlayMusic(const std::string& name);

	private:
		FMOD::System* m_system = nullptr;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}
