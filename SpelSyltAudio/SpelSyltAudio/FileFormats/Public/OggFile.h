#pragma once
#include <SpelSyltAudio/FileFormats/Public/AudioFormats.h>
#include <SpelSyltAudio/FileFormats/Public/VorbisWrapper.h>

#define OGG_CHUNK_SIZE 131072u 

namespace SSAL
{
	struct SOGGChunk
	{
		SOGGChunk()
			: Data(new char[OGG_CHUNK_SIZE])
			, SampleRate(-1)
			, Format(EAudioFormat::Mono8)
		{
		}

		~SOGGChunk()
		{
			delete[OGG_CHUNK_SIZE] Data;
		}
		
		char* Data;
		unsigned int DataSize = OGG_CHUNK_SIZE;
		int SampleRate;
		EAudioFormat Format;
	};

	struct SOGGFile
	{
	public:
		friend class CVorbisWrapper;

		void OpenStream(const char* InPath);
		void CloseStream();

		void ReadNextChunk();
		bool ContainsMoreData();

		SOGGChunk& GetCurrentChunk();
	private:
		CVorbisWrapper VorbisReader;
		SOGGChunk Chunk;
		int SampleRate;
		EAudioFormat Format;

	};
}