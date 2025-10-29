#include "BorjaLib.h"

namespace snd {

	AudioData defaultAudio;
	AudioData audioDataList[audioDataMaxAmount] = {};

	void StartAudioDevice()
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			InitAudioDevice();
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
			break;
		}
		default:
			break;
		}
	}

	void EndAudioDevice()
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			CloseAudioDevice();
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
			break;
		}
		default:
			break;
		}
	}

	int InitAudioData(AudioData& audioData)
	{
		int availableID = 0;
		int currentID = -1;

		bool isAvailable = false;
		while (!isAvailable) {
			currentID++;

			isAvailable = !audioDataList[currentID].active;

			if (isAvailable) {
				availableID = currentID;
			}
			if (currentID == audioDataMaxAmount - 1) {
				isAvailable = true;
			}
		}
		audioData.active = true;

		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			audioData.sound = LoadSound(audioData.file.c_str());
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			audioData.id = slLoadWAV(audioData.file.c_str());
#endif
			break;
		}
		default:
			break;
		}

		audioDataList[availableID] = audioData;
		return availableID;
	}

	void DeInit(AudioData& audioData)
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			UnloadSound(audioData.sound);
			audioData.id = 0;
			audioData.active = false;
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			audioData.id = 0;
			audioData.active = false;
#endif
			break;
		}
		default:
			break;
		}
	}

	void Play(int id)
	{

		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			PlaySound(audioDataList[id].sound);
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			slSoundPlay(audioDataList[id].id);
#endif
			break;
		}
		default:
			break;
		}
	}

	void Pause(int id, bool pause)
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			if (pause) {
				PauseSound(audioDataList[id].sound);
			}
			else {
				ResumeSound(audioDataList[id].sound);
			}
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			if (pause) {
				slSoundPause(audioDataList[id].id);
			}
			else {
				slSoundPlay(audioDataList[id].id);
			}
#endif
			break;
		}
		default:
			break;
		}
	}

	void Stop(int id)
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			StopSound(audioDataList[id].sound);
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
#endif
			break;
		}
		default:
			break;
		}
	}

	bool IsPlaying(int id)
	{
		switch ((rend::GraphicsLib)rend::activeGraphics)
		{
		case rend::GraphicsLib::NONE: {

			break;
		}
		case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
			IsSoundPlaying(audioDataList[id].sound);
#endif
			break;
		}
		case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
			return slSoundPlaying(audioDataList[id].id);
#endif
			break;
		}
		default:
			break;
		}
		return false;
	}

}