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
	AudioEngine.SetSourceLooping(*this, InLoop);
	AudioEngine.PlaySource(*this);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::Play(bool InLoop)
{
	AudioEngine.SetSourceLooping(*this, InLoop);

	if (!AudioEngine.IsSourcePlaying(*this))
	{
		AudioEngine.PlaySource(*this);
	}
}

//----------------------------------------------------------------------

bool SSAL::CSoundSource::IsPlaying() const
{
	return AudioEngine.IsSourcePlaying(*this);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::Pause()
{
	AudioEngine.PauseSource(*this);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::Stop()
{
	AudioEngine.StopSource(*this);
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

float SSAL::CSoundSource::GetVolume() const
{
	return AudioEngine.GetSourceGain(*this);
}

//----------------------------------------------------------------------
