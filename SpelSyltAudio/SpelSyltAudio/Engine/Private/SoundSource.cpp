#include <SpelSyltAudio/Engine/Public/SoundSource.h>

#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

//----------------------------------------------------------------------

SSAL::CSoundSource::CSoundSource(CAudioEngine& InAudioEngine, FSourceID InSourceID)
	: CAudioSource(InAudioEngine, InSourceID)
{
}

//----------------------------------------------------------------------

SSAL::CSoundSource::CSoundSource(const CSoundSource& InOther)
	: CAudioSource(InOther)
{
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::BindWavFile(SWavFile& InWavFile)
{
	AudioEngine.BindBufferToSource(SourceID, InWavFile);
}

//----------------------------------------------------------------------