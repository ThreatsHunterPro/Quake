#include "SoundManager.h"
#include <windows.h>

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
    for (sf::SoundBuffer* _buffer : dataSound.GetAllValues())
    {
        delete _buffer;
        _buffer = nullptr;
    }
    for (sf::Sound* _sound : sounds.GetAllValues())
    {
        delete _sound;
        _sound = nullptr;
    }
}

void SoundManager::LoadAllSounds()
{
	string path = "../Content/Sound";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(FString::Format("{}/*", path).GetText().c_str(), &findFileData);
    
    FString _file;
    FString _name;
    FString _pathCombine;


    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (findFileData.dwFileAttributes != 16)
            {
                _file = findFileData.cFileName;
                _name = _file.SubString(0, _file.Find("."));               

                _pathCombine = FString::Format("{}/{}", path, _file.GetText());

                sf::SoundBuffer* _buffer = new sf::SoundBuffer();
                if (!_buffer->loadFromFile(_pathCombine.GetText())) {
                    std::cout << FString::Format("[SoundManager] Cannot be load \"{}\"", _file.GetText()).GetText() << std::endl;
                    delete _buffer;
                    _buffer = nullptr;
                }
                else
                    dataSound.Add(_name.GetText(), _buffer);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }

}

void SoundManager::PlaySoundFromName(const FString& _nameSound, const float& _pitch, const float& _volume, const bool& _loop)
{
    sf::Sound* _sound = new sf::Sound();
    _sound->setBuffer(**dataSound.Find(_nameSound.GetText()));
    _sound->setPitch(_pitch);
    _sound->setVolume(_volume);
    _sound->setLoop(_loop);
    _sound->play();
    sounds.Add(_nameSound.GetText(), _sound);
}

void SoundManager::StopSound(const FString& _nameSound)
{
    sf::Sound* _sound = *sounds.Find(_nameSound.GetText());
    _sound->stop();
    sounds.RemoveAt(_nameSound.GetText());
}

void SoundManager::StopAllSounds()
{
    for (sf::Sound* _sound : sounds.GetAllValues())
    {
        _sound->stop();
        delete _sound;
        _sound = nullptr;
    }
}

