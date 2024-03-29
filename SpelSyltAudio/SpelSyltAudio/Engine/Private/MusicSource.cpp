#include <SpelSyltAudio/Engine/Public/MusicSource.h>

#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

#pragma comment(lib, "libvorbis_static")
#pragma comment(lib, "libogg_static")
#pragma comment(lib, "libvorbisfile_static")

//----------------------------------------------------------------------

SSAL::CMusicSource::CMusicSource(FSourceID InSourceID, FBufferID InBuffers[MUSIC_BUFFER_COUNT], CAudioEngine& InAudioEngine)
	: CAudioSource(InAudioEngine, InSourceID)
	, Buffers()
{
	for (unsigned int i = 0; i < MUSIC_BUFFER_COUNT; ++i)
	{
		Buffers[i] = InBuffers[i];
	}
}

//----------------------------------------------------------------------

SSAL::CMusicSource::CMusicSource(const CMusicSource& InOther)
	: CAudioSource(InOther)
	, Buffers()
{
	for (unsigned int i = 0; i < MUSIC_BUFFER_COUNT; ++i)
	{
		Buffers[i] = InOther.Buffers[i];
	}

}

//----------------------------------------------------------------------

void SSAL::CMusicSource::OpenOGGStream(const char* PathToFile)
{
	OggFile.OpenStream(PathToFile);

	//We enqueue all our buffers at the start to give us some room for streaming
	for (int i = 0; i < MUSIC_BUFFER_COUNT; ++i)
	{
		OggFile.ReadNextChunk();
		AudioEngine.AddBufferToSourceQueue(SourceID, Buffers[i], OggFile.GetCurrentChunk());
	}
}

//----------------------------------------------------------------------

void SSAL::CMusicSource::CloseOGGStream()
{
	OggFile.CloseStream();
}

//----------------------------------------------------------------------

void SSAL::CMusicSource::Tick()
{
	int FreeBufferCount = 0;
	if (AudioEngine.HaveProcessedBuffers(SourceID, FreeBufferCount))
	{
		FBufferID FreeBuffers[MUSIC_BUFFER_COUNT] = {};
		FBufferID* FreeBuffersPtr = FreeBuffers;
		AudioEngine.DequeueBuffersFromSource(SourceID, FreeBufferCount, FreeBuffersPtr);

		for (int i = 0; i < FreeBufferCount; ++i)
		{
			if (OggFile.ContainsMoreData())
			{
				FillAndEnqueueBuffer(FreeBuffers[i]);
			}
		}
	}
}

//----------------------------------------------------------------------

void SSAL::CMusicSource::FillAndEnqueueBuffer(FBufferID InBufferID)
{
	OggFile.ReadNextChunk();
	AudioEngine.AddBufferToSourceQueue(SourceID, InBufferID, OggFile.GetCurrentChunk());
}

//----------------------------------------------------------------------