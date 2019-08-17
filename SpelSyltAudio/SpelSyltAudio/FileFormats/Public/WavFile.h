#pragma once
#include <SpelSyltAudio/FileFormats/Public/AudioFileErrors.h>
#include <SpelSyltAudio/FileFormats/Public/AudioFormats.h>

namespace SSAL
{
	struct SWavFile
	{
	public:
		void LoadFromMemory(char* InDataStart, unsigned int InSize);
		void LoadFromFile(const char* InPath);

		void GetData(char*& OutData, int& OutDataSize);
		int GetSampleRate() const;
		EAudioFormat GetFormat() const;

	private:
		EAudioFileError ReadChunk(char*& InData);
		EAudioFileError ReadSubchunkOne(char*& InData);
		EAudioFileError ReadSubchunkTwo(char*& InData);

		void SetFormat(short InBitsPerSample, short InChannelCount);
		
		char* Data;
		int DataSize;
		int SampleRate;
		EAudioFormat Format;

	};
}