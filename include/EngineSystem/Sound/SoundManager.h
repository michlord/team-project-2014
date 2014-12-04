#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>

class SoundManager {
	public:
		SoundManager();
		~SoundManager();

		void clear();

		void setSoundsVolume(float);
		void setMusicsVolume(float);

		void scaleSoundsVolume(float);
		void scaleMusicsVolume(float);

		std::size_t createBuffer(const std::string &);
		std::size_t createSound(std::size_t);
		std::size_t createMusic(const std::string &);

		void deleteSound(std::size_t);
		void deleteMusic(std::size_t);

		// TODO: find out if these should be static?
		sf::Sound& getSound(std::size_t);
		sf::Music& getMusic(std::size_t);

		void stopSounds();
		void stopMusics();

	private:
		int id_gen_base;
		float sounds_volume;
		float musics_volume;

// TODO: find out if this will cause problems, because sf::Sound uses const SoundBuffer...
		std::unordered_map<std::size_t, sf::SoundBuffer> sound_buffers;
		std::unordered_map<std::size_t, sf::Sound> sounds;
		std::unordered_map<std::size_t, sf::Music> musics;
};

#endif // !SOUNDMANAGER_H_INCLUDED