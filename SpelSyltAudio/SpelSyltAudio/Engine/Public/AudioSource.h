#pragma once
#include <SpelSyltAudio/Engine/Public/SSALTypes.h>

namespace SSAL
{
	class CAudioEngine;

	class CAudioSource
	{
	public:
		CAudioSource() = delete;
		CAudioSource(CAudioEngine& InAudioEngine, FSourceID InSourceID);
		CAudioSource(const CAudioSource& InOther);

		void DestroySource();

		void Play(bool InLoop = false);
		bool IsPlaying() const;

		void Pause();
		void Stop();
		void SetVolume(float InVolume);

		void SetPosition(float InX, float InY, float InZ);

		void SetLooping(bool InLooping);
		float GetVolume() const;
	protected:
		CAudioEngine& AudioEngine;
		FSourceID SourceID;
	};
}