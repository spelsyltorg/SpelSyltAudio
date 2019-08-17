#include <SpelSyltAudio/Engine/Public/SoundSource.h>

#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

//----------------------------------------------------------------------

SSAL::CSoundSource::CSoundSource(unsigned int InSourceID, CAudioEngine& InAudioEngine)
	: SourceID(InSourceID)
	, AudioEngine(InAudioEngine)
{
}

//----------------------------------------------------------------------

SSAL::CSoundSource::CSoundSource(const CSoundSource& InOther)
	: SourceID(InOther.SourceID)
	, AudioEngine(InOther.AudioEngine)
{
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::DestroySource()
{
	AudioEngine.DestroySource(*this);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::PlaySound(SWavFile& InWavFile, bool InLoop)
{
	AudioEngine.BindBufferToSource(*this, InWavFile);

	if (InLoop)
	{
		AudioEngine.SetSourceLooping(*this, InLoop);
	}
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetVolume(float InVolume)
{
	AudioEngine.SetSourceGain(*this, InVolume);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetPosition(float InX, float InY, float InZ)
{
	AudioEngine.SetSourcePosition(*this, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetLooping(bool InLooping)
{
	AudioEngine.SetSourceLooping(*this, InLooping);
}

//----------------------------------------------------------------------
