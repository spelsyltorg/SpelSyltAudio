#include <SpelSyltAudio/Engine/Public/AudioSource.h>

#include <SpelSyltAudio/Engine/Public/AudioEngine.h>

//----------------------------------------------------------------------

SSAL::CAudioSource::CAudioSource(CAudioEngine& InAudioEngine, FSourceID InSourceID)
	: AudioEngine(InAudioEngine)
	, SourceID(InSourceID)
{
}

//----------------------------------------------------------------------

SSAL::CAudioSource::CAudioSource(const CAudioSource& InOther)
	: AudioEngine(InOther.AudioEngine)
	, SourceID(InOther.SourceID)
{
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::DestroySource()
{
	AudioEngine.DestroySource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::Play(bool InLoop)
{
	AudioEngine.SetSourceLooping(SourceID, InLoop);
	
	//GUARD THIS!!!!
	AudioEngine.PlaySource(SourceID);
}

//----------------------------------------------------------------------

bool SSAL::CAudioSource::IsPlaying() const
{
	return false;
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::Pause()
{
	AudioEngine.PauseSource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::Stop()
{
	AudioEngine.StopSource(SourceID);
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::SetVolume(float InVolume)
{
	AudioEngine.SetSourceGain(SourceID, InVolume);
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::SetPosition(float InX, float InY, float InZ)
{
	AudioEngine.SetSourcePosition(SourceID, InX, InY, InZ);
}

//----------------------------------------------------------------------

void SSAL::CAudioSource::SetLooping(bool InLooping)
{
	AudioEngine.SetSourceLooping(SourceID, InLooping);
}

//----------------------------------------------------------------------

float SSAL::CAudioSource::GetVolume() const
{
	return AudioEngine.GetSourceGain(SourceID);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------