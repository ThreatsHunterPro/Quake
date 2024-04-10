#pragma once
#include "../../CoreMinimal.h"
#include "Source/Runtime/Core/Containers/TMap.h"
#include <SFML/Audio.hpp>

class SoundManager
{
    TMap<string, sf::SoundBuffer*> dataSound;
    TMap<string, sf::Sound*> sounds;

public:
    FORCEINLINE static SoundManager& GetInstance()
    {
        static SoundManager _instance;
        return _instance;
    }

public:
    SoundManager();
    ~SoundManager();
    void LoadAllSounds();
    void PlaySoundFromName(const FString& _nameSound, const float& _pitch = 1.f, const float& _volume = 1.f, const bool& _loop = false);
    void StopSound(const FString& _nameSound);
    void StopAllSounds();
};