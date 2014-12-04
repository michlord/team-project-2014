#include <EngineSystem/Sound/SoundManager.h>

SoundManager::SoundManager() {
	id_gen_base = 1;
	sounds_volume = 100.0f;
	musics_volume = 100.0f;
}

SoundManager::~SoundManager() {
	clear();
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::clear() {
	stopSounds();
	sounds.clear();

	sound_buffers.clear();

	stopMusics();
	musics.clear();

	id_gen_base = 1;
	sounds_volume = 100.0f;
	musics_volume = 100.0f;
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::setSoundsVolume(float sound_volume) {
	sounds_volume = sound_volume;
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::setMusicsVolume(float music_volume) {
	musics_volume = music_volume;
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::scaleSoundsVolume(float sound_volume) {
	float old_volume = sounds_volume;
	sounds_volume = std::max(sound_volume, 0.0f);
	for ( std::pair<std::size_t, sf::Sound> snd : sounds ) {
		snd.second.setVolume(std::min(snd.second.getVolume() / old_volume * sound_volume, 100.0f));
	}
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::scaleMusicsVolume(float music_volume) {
	float old_volume = music_volume;
	musics_volume = std::max(music_volume, 0.0f);
	for ( std::pair<std::size_t, sf::Sound> snd : sounds ) {
		snd.second.setVolume(std::min(snd.second.getVolume() / old_volume * music_volume, 100.0f));
	}
}

///////////////////////////////////////////////////////////////////////////////

std::size_t SoundManager::createBuffer(const std::string &filename) {
	sf::SoundBuffer buffer;
	if( buffer.loadFromFile(filename) ) {
		std::pair<std::size_t, sf::SoundBuffer> new_elem;
		new_elem.first = id_gen_base;

		new_elem.second = buffer;
		sound_buffers.insert( new_elem );
		return id_gen_base++;
	}
	else {
		throw std::runtime_error("File missing or could not open: " + filename);
		return 0;
	}
}

std::size_t SoundManager::createSound(std::size_t buff_id) {
	std::unordered_map<std::size_t, sf::SoundBuffer>::iterator got = sound_buffers.find(buff_id);
	if( got != sound_buffers.end() ) {
		std::pair<std::size_t, sf::Sound> new_elem;
		new_elem.first = id_gen_base;
		sf::Sound sound((*got).second);
		sound.setVolume(sounds_volume);

		for ( std::pair<std::size_t, sf::Sound> snd : sounds ) {
			if( snd.second.getStatus() == sf::Sound::Status::Stopped )
			{
				sounds.erase(snd.first);
				break;
			}
		}
		new_elem.second = sound;
		sounds.insert( new_elem );
		return id_gen_base++;
	}
	else if( musics.size() + sound_buffers.size() < 250 ) {
		throw std::runtime_error("Buffer not found: " + buff_id);
		return 0;
	}
	else {
		throw std::runtime_error("Too many sounds created.");
		return 0;
	}
}

std::size_t SoundManager::createMusic(const std::string &filename) {
	sf::Music music;
	if( music.openFromFile(filename) ) {
		std::pair<std::size_t, sf::Music> new_elem;
		new_elem.first = id_gen_base;
		music.setVolume(musics_volume);
		music.setLoop(true);

		for ( std::pair<std::size_t, sf::Music> msc : musics ) {
			if( msc.second.getStatus() == sf::Sound::Status::Stopped )
			{
				musics.erase(msc.first);
				break;
			}
		}
		new_elem.second = music;
		musics.insert( new_elem );
		return id_gen_base++;
	}
	else if( musics.size() + sound_buffers.size() < 250 ) {
		throw std::runtime_error("File missing or could not open: " + filename);
		return 0;
	}
	else {
		throw std::runtime_error("Too many sounds created.");
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::deleteSound(std::size_t sound_id) {
	std::unordered_map<std::size_t, sf::Sound>::iterator got = sounds.find(sound_id);
	if( got != sounds.end() ) {
		(*got).second.stop();
		sounds.erase((*got).first);
		return;
	}
	else {
		throw std::runtime_error("Sound does not exist.");
		return;
	}
}

void SoundManager::deleteMusic(std::size_t music_id) {
	std::unordered_map<std::size_t, sf::Music>::iterator got = musics.find(music_id);
	if( got != musics.end() ) {
		(*got).second.stop();
		musics.erase((*got).first);
		return;
	}
	else {
		throw std::runtime_error("Music does not exist.");
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////

sf::Sound& SoundManager::getSound(std::size_t sound_id) {
	std::unordered_map<std::size_t, sf::Sound>::iterator got = sounds.find(sound_id);
	if( got != sounds.end() ) {
		return (*got).second;
	}
	else {
		throw std::runtime_error("Could not get sound: " + sound_id);
	}
}

sf::Music& SoundManager::getMusic(std::size_t music_id) {
	std::unordered_map<std::size_t, sf::Music>::iterator got = musics.find(music_id);
	if( got != musics.end() ) {
		return (*got).second;
	}
	else {
		throw std::runtime_error("Could not get music: " + music_id);
	}
}

///////////////////////////////////////////////////////////////////////////////

void SoundManager::stopSounds() {
	for ( std::pair<std::size_t, sf::Sound> snd : sounds ) {
		snd.second.stop();
	}
}

void SoundManager::stopMusics() {
	for ( std::pair<std::size_t, sf::Music> msc : musics ) {
		msc.second.stop();
	}
}


/*

/////////// DEMANDS ENCAPSULATION
//	functionality on sounds and musics should return references for cascade. - Maybe.
//	delete sound on stop - when making new sound, find all sounds with this id which are stopped, and delete.

	allow deletion of music, sounds

	make getSound private, use it in functions such as PLAY(id)


NOW:	szczur na pocz¹tek Enemies as entities. AI stateMachine... przechodzenie do innych stanów.
	hierarchie przeciwników.
	Entity "cos co chodzi po ziemi" stany (chodze w lewo, w prawo), AI (maszyna ktora wysyla wiadomosci "idz w lewo")
	napisac na google groups mniej wiecej "co planuje zrobic" - do niedzieli.

*/
