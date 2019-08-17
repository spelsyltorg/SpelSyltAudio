#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

#include <SpelSyltAudio/FileFormats/Public/WavFile.h>

#pragma comment(lib, "OpenAL32")

#include <al.h>
#include <alc.h>

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

	Buffers = new unsigned int[BufferCount];
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

SSAL::CSoundSource SSAL::CAudioEngine::MakeSource()
{
	unsigned int SourceID = 0;
	alGenSources(1, &SourceID);

	int ErrorCode = alGetError();

	CSoundSource CreatedSource(SourceID, *this);
	return CreatedSource;
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::DestroySource(CSoundSource& InSource)
{
	alDeleteSources(1, &InSource.SourceID);
	InSource.SourceID = 0;
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::BindBufferToSource(CSoundSource& InSource, SWavFile& InWav)
{
	ALenum Format = 0;

	switch (InWav.GetFormat())
	{
	case EAudioFormat::Mono8:
		Format = AL_FORMAT_MONO8;
		break;
	case EAudioFormat::Mono16:
		Format = AL_FORMAT_MONO16;
		break;
	case EAudioFormat::Stereo8:
		Format = AL_FORMAT_STEREO8;
		break;
	case EAudioFormat::Stereo16:
		Format = AL_FORMAT_STEREO16;
		break;
	default:
		break;
	}

	char* SoundData = nullptr;
	int SoundDataSize = 0;
	InWav.GetData(SoundData, SoundDataSize);

	alBufferData(Buffers[NextFreeBuffer], Format, SoundData, SoundDataSize, InWav.GetSampleRate());
	alSourcei(InSource.SourceID, AL_BUFFER, Buffers[NextFreeBuffer++]);
	alSourcePlay(InSource.SourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourceGain(CSoundSource& InSource, float InGain)
{
	alSourcef(InSource.SourceID, AL_GAIN, InGain);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourcePosition(CSoundSource& InSource, float InX, float InY, float InZ)
{
	alSource3f(InSource.SourceID, AL_POSITION, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CAudioEngine::SetSourceLooping(CSoundSource& InSource, bool InLooping)
{
	int Looping = InLooping ? 1 : 0;
	alSourcei(InSource.SourceID, AL_LOOPING, Looping);
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

	if (Buffers)
	{
		alDeleteBuffers(BufferCount, Buffers);
		delete[] Buffers;
	}

	if (Context)
	{
		alcDestroyContext(Context);
	}

	if (Device)
	{
		alcCloseDevice(Device);
	}
}

//----------------------------------------------------------------------