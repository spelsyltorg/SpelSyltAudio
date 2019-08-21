#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

#include <SpelSyltAudio/FileFormats/Public/WavFile.h>
#include <SpelSyltAudio/FileFormats/Public/OggFile.h>

#pragma comment(lib, "OpenAL32")

#include <al.h>
#include <alc.h>

//----------------------------------------------------------------------

namespace
{
	ALenum SSALFormatToOALFormat(SSAL::EAudioFormat InSSALFormat)
	{
		switch (InSSALFormat)
		{
		case SSAL::EAudioFormat::Mono8:
			return AL_FORMAT_MONO8;
			break;
		case SSAL::EAudioFormat::Mono16:
			return AL_FORMAT_MONO16;
			break;
		case SSAL::EAudioFormat::Stereo8:
			return AL_FORMAT_STEREO8;
			break;
		case SSAL::EAudioFormat::Stereo16:
			return AL_FORMAT_STEREO16;
			break;
		default:
			return -1;
			break;
		}

		return -1;
	}
}

//----------------------------------------------------------------------

SSAL::CAudioEngine::CAudioEngine()
	: BufferCount(0)
	, NextFreeBuffer(0)
	, Buffers(nullptr)
{

}

//----------------------------------------------------------------------

SSAL::CAudioEngine::~CAudioEngine()
{
	ShutDown();
}

//----------------------------------------------------------------------

bool SSAL::CAudioEngine::Initialize(int InBufferCount)
{
	ALenum ErrorCode = 0;

	ALCdevice* Device = alcOpenDevice(nullptr);
	ALCcontext* Context = nullptr;
	ErrorCode = alGetError();

	if (ErrorCode != AL_NO_ERROR)
	{
		alcCloseDevice(Device);
		return false;
	}

	Context = alcCreateContext(Device, nullptr);
	alcMakeContextCurrent(Context);

	ErrorCode = alGetError();
	if (ErrorCode != AL_NO_ERROR)
	{
		alcDestroyContext(Context);
		alcCloseDevice(Device);
		return false;
	}

	ALboolean SupportEAX2 = alIsExtensionPresent("EAX 2.0");

	Buffers = new unsigned int[InBufferCount];
	alGenBuffers(InBufferCount, Buffers);

	ErrorCode = alGetError();
	if (ErrorCode != AL_NO_ERROR)
	{
		alDeleteBuffers(InBufferCount, Buffers);
		alcDestroyContext(Context);
		alcCloseDevice(Device);
		return false;
	}

	BufferCount = InBufferCount;
	return true;
}

//----------------------------------------------------------------------

SSAL::CSoundSource SSAL::CAudioEngine::MakeSoundSource()
{
	unsigned int SourceID = 0;
	alGenSources(1, &SourceID);

	int ErrorCode = alGetError();

	CSoundSource CreatedSource(*this, SourceID);
	return CreatedSource;
}

//----------------------------------------------------------------------

SSAL::CMusicSource SSAL::CAudioEngine::MakeMusicSource()
{
	unsigned int SourceID = 0;
	alGenSources(1, &SourceID);

	FBufferID BuffersForSource[MUSIC_BUFFER_COUNT];
	for (short i = 0; i < MUSIC_BUFFER_COUNT; ++i)
	{
		BuffersForSource[i] = Buffers[NextFreeBuffer++];
	}

	CMusicSource CreatedSource(SourceID, BuffersForSource, *this);
	return CreatedSource;
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::DestroySource(FSourceID InSourceID)
{
	alDeleteSources(1, &InSourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::AddBufferToSourceQueue(FSourceID InSourceID, FBufferID InBufferID, SOGGChunk& InDataChunk)
{
	ALenum Format = ::SSALFormatToOALFormat(InDataChunk.Format);
	alBufferData(InBufferID, Format, InDataChunk.Data, InDataChunk.DataSize, InDataChunk.SampleRate);

	int ErrorCode = alGetError();
	volatile const int OOM = AL_OUT_OF_MEMORY;
	volatile const int IV = AL_INVALID_VALUE;
	volatile const int IE = AL_INVALID_ENUM;


	alSourceQueueBuffers(InSourceID, 1, &InBufferID);

	ErrorCode = alGetError();
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::DequeueBuffersFromSource(FSourceID InSourceID, int FreeBufferCount, FBufferID*& OutFreedBuffers)
{
	alSourceUnqueueBuffers(InSourceID, FreeBufferCount, OutFreedBuffers);
}

//----------------------------------------------------------------------

bool SSAL::CAudioEngine::HaveProcessedBuffers(FSourceID InSourceID, int& OutProcessedCount)
{
	alGetSourcei(InSourceID, AL_BUFFERS_PROCESSED, &OutProcessedCount);
	return OutProcessedCount > 0;
}

//----------------------------------------------------------------------

int SSAL::CAudioEngine::GetBufferQueueCount(FSourceID InSourceID)
{
	int NumBuffers = 0;
	alGetSourcei(InSourceID, AL_BUFFERS_QUEUED, &NumBuffers);
	return NumBuffers;
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::BindBufferToSource(FSourceID InSourceID, SWavFile& InWav)
{
	ALenum Format = ::SSALFormatToOALFormat(InWav.GetFormat());

	char* SoundData = nullptr;
	int SoundDataSize = 0;
	InWav.GetData(SoundData, SoundDataSize);

	alBufferData(Buffers[NextFreeBuffer], Format, SoundData, SoundDataSize, InWav.GetSampleRate());
	alSourcei(InSourceID, AL_BUFFER, Buffers[NextFreeBuffer++]);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::PlaySource(FSourceID InSourceID)
{
	alSourcePlay(InSourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::PauseSource(FSourceID InSourceID)
{
	alSourcePause(InSourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::StopSource(FSourceID InSourceID)
{
	alSourceStop(InSourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourceGain(FSourceID InSourceID, float InGain)
{
	alSourcef(InSourceID, AL_GAIN, InGain);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourcePosition(FSourceID InSourceID, float InX, float InY, float InZ)
{
	alSource3f(InSourceID, AL_POSITION, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourceLooping(FSourceID InSourceID, bool InLooping)
{
	int Looping = InLooping ? 1 : 0;
	alSourcei(InSourceID, AL_LOOPING, Looping);
}

//----------------------------------------------------------------------

bool SSAL::CAudioEngine::IsSourcePlaying(FSourceID InSourceID)
{
	int State = 0;
	alGetSourcei(InSourceID, AL_SOURCE_STATE, &State);

	return State == AL_PLAYING;
}

//----------------------------------------------------------------------

float SSAL::CAudioEngine::GetSourceGain(FSourceID InSourceID) const
{
	float Gain = 0.f;
	alGetSourcef(InSourceID, AL_GAIN, &Gain);
	return Gain;
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetListenerPosition(float InX, float InY, float InZ)
{
	alListener3f(AL_POSITION, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::ShutDown()
{
	ALCcontext* Context = alcGetCurrentContext();
	ALCdevice* Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(Context);
	alcCloseDevice(Device);

	delete[] Buffers;
}

//----------------------------------------------------------------------