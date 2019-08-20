#include <SpelSyltAudio/Engine/Public/SoundSource.h>

#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

//----------------------------------------------------------------------

SSAL::CSoundSource::CSoundSource(FSourceID InSourceID, CAudioEngine& InAudioEngine)
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
	AudioEngine.DestroySource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::PlaySound(SWavFile& InWavFile, bool InLoop)
{
	AudioEngine.BindBufferToSource(SourceID, InWavFile);
	AudioEngine.SetSourceLooping(SourceID, InLoop);
	AudioEngine.PlaySource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::Play(bool InLoop)
{
	AudioEngine.SetSourceLooping(SourceID, InLoop);

	if (!AudioEngine.IsSourcePlaying(*this))
	{
		AudioEngine.PlaySource(SourceID);
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
	AudioEngine.PauseSource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::Stop()
{
	AudioEngine.StopSource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetVolume(float InVolume)
{
	AudioEngine.SetSourceGain(SourceID, InVolume);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetPosition(float InX, float InY, float InZ)
{
	AudioEngine.SetSourcePosition(SourceID, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CSoundSource::SetLooping(bool InLooping)
{
	AudioEngine.SetSourceLooping(SourceID, InLooping);
}

//----------------------------------------------------------------------

float SSAL::CSoundSource::GetVolume() const
{
	return AudioEngine.GetSourceGain(*this);
}

//----------------------------------------------------------------------
