#pragma once
#include <SpelSyltAudio/Engine/Public/SSALTypes.h>
#include <SpelSyltAudio/FileFormats/Public/OggFile.h>

#define MUSIC_BUFFER_COUNT 3

namespace SSAL
{
	class CAudioEngine;

	class CMusicSource
	{
	public:
		CMusicSource() = delete;
		CMusicSource(FSourceID InSourceID, FBufferID InBuffers[MUSIC_BUFFER_COUNT], CAudioEngine& InAudioEngine);
		CMusicSource(const CMusicSource& InOther);

		void OpenOGGStream(const char* PathToFile);
		void CloseOGGStream();

		void Play();
		void SetVolume(float InVolume);

		void Tick();
	private:
		void FillAndEnqueueBuffer(FBufferID InBufferID);

		SOGGFile OggFile;
		CAudioEngine& AudioEngine;
		FSourceID SourceID;
		FBufferID Buffers[MUSIC_BUFFER_COUNT];
		FBufferID WriteBuffer;
	};
}