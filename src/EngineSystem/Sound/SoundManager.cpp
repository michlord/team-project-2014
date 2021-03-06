#include <EngineSystem/Sound/SoundManager.h>
#include <algorithm>
#include <stdexcept>

namespace Sound {

    SoundManager &soundManager = SoundManager::getInstance();

    SoundManager &SoundManager::getInstance() {
        static SoundManager instance;
        return instance;
    }

    SoundManager::SoundManager() {
        id_gen_base = 1;
        sounds_volume = 100.0f;
        musics_volume = 100.0f;
    }

    SoundManager::~SoundManager() {
        clear();
    }

    void SoundManager::clear() {
        stopSounds();
        sounds.clear();

        sound_buffers.clear();

        stopMusics();
        musics.clear();

        setIdGenBase(1);
        setSoundsVolume(100.0f);
        setMusicsVolume(100.0f);
    }

    void SoundManager::setIdGenBase(int id) {
        id_gen_base = std::max(1, id);
    }

    void SoundManager::setSoundsVolume(float sound_volume) {
        sounds_volume = sound_volume;
    }

    void SoundManager::setMusicsVolume(float music_volume) {
        musics_volume = music_volume;
    }

    void SoundManager::scaleSoundsVolume(float sound_volume) {
        float old_volume = sounds_volume;
        setSoundsVolume(std::max(sound_volume, 0.0f));
        for (std::pair<std::size_t, sf::Sound> sound : sounds) {
            sound.second.setVolume(std::min(sound.second.getVolume() / old_volume * sound_volume, 100.0f));
        }
    }

    void SoundManager::scaleMusicsVolume(float music_volume) {
        float old_volume = music_volume;
        setMusicsVolume(std::max(music_volume, 0.0f));
        for (std::pair<std::size_t, sf::Music*> music : musics) {
            (*music.second).setVolume(std::min((*music.second).getVolume() / old_volume * music_volume, 100.0f));
        }
    }

    std::size_t SoundManager::createBuffer(const std::string &filename) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(filename)) {
            std::pair<std::size_t, sf::SoundBuffer> new_elem(id_gen_base, buffer);

            sound_buffers.insert(new_elem);
            return id_gen_base++;
        }
        else {
            throw std::runtime_error("File missing or could not open: " + filename);
        }
    }

    std::size_t SoundManager::createSound(std::size_t buff_id) {
        for (std::pair<std::size_t, sf::Sound> sound : sounds) {
            if (sound.second.getStatus() == sf::Sound::Status::Stopped)
            {
                sounds.erase(sound.first);
                break;
            }
        }
        std::unordered_map<std::size_t, sf::SoundBuffer>::iterator got = sound_buffers.find(buff_id);
        if (got != sound_buffers.end()) {
            sf::Sound sound((*got).second);
            sound.setVolume(sounds_volume);
            std::pair<std::size_t, sf::Sound> new_elem(id_gen_base, sound);

            sounds.insert(new_elem);
            return id_gen_base++;
        }
        else if (musics.size() + sound_buffers.size() < 250) {
            throw std::runtime_error("Buffer not found: " + buff_id);
        }
        else {
            throw std::runtime_error("Too many sounds created.");
        }
    }

    std::size_t SoundManager::createMusic(const std::string &filename) {
        for (std::pair<std::size_t, sf::Music*> music : musics) {
            if ((*music.second).getStatus() == sf::Sound::Status::Stopped)
            {
                musics.erase(music.first);
                break;
            }
        }
        sf::Music *music = new sf::Music();
        if ((*music).openFromFile(filename)) {
            (*music).setVolume(musics_volume);
            (*music).setLoop(true);
            std::pair<std::size_t, sf::Music*> new_elem(id_gen_base, music);

            musics.insert(new_elem);
            return id_gen_base++;
        }
        else if (musics.size() + sound_buffers.size() < 250) {
            throw std::runtime_error("File missing or could not open: " + filename);
        }
        else {
            throw std::runtime_error("Too many sounds created.");
        }
    }

    void SoundManager::deleteSound(std::size_t sound_id) {
        std::unordered_map<std::size_t, sf::Sound>::iterator got = sounds.find(sound_id);
        if (got != sounds.end()) {
            (*got).second.stop();
            sounds.erase((*got).first);
            return;
        }
        else {
            throw std::runtime_error("Sound does not exist.");
        }
    }


    void SoundManager::deleteMusic(std::size_t music_id) {
        std::unordered_map<std::size_t, sf::Music*>::iterator got = musics.find(music_id);
        if (got != musics.end()) {
            (*(*got).second).stop();
            musics.erase((*got).first);
            return;
        }
        else {
            throw std::runtime_error("Music does not exist.");
        }
    }

    void SoundManager::stopSounds() {
        for (std::pair<std::size_t, sf::Sound> sound : sounds) {
            sound.second.stop();
        }
    }

    void SoundManager::stopMusics() {
        for (std::pair<std::size_t, sf::Music*> music : musics) {
            (*music.second).stop();
        }
    }

    sf::Sound& SoundManager::getSound(std::size_t sound_id) {
        std::unordered_map<std::size_t, sf::Sound>::iterator got = sounds.find(sound_id);
        if (got != sounds.end()) {
            return (*got).second;
        }
        else {
            throw std::runtime_error("Could not get sound: " + sound_id);
        }
    }

    sf::Music& SoundManager::getMusic(std::size_t music_id) {
        std::unordered_map<std::size_t, sf::Music*>::iterator got = musics.find(music_id);
        if (got != musics.end()) {
            return (*(*got).second);
        }
        else {
            throw std::runtime_error("Could not get music: " + music_id);
        }
    }

}