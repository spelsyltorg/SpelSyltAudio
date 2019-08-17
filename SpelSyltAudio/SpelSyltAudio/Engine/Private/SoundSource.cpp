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

void SSAL::CSoundSource::PlaySound(SWavFormat& InWavFile)
{
	AudioEngine.BindBufferToSource(*this, InWavFile);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------