#pragma once

namespace SSAL
{
	class CAudioEngine;
	struct SWavFile;

	class CSoundSource
	{
	public:
		friend CAudioEngine;

		CSoundSource() = delete;
		CSoundSource(unsigned int InSourceID, CAudioEngine& InAudioEngine);
		CSoundSource(const CSoundSource& InOther);
		void DestroySource();

		void PlaySound(SWavFile& InWavFile, bool InLoop = false);
		void SetVolume(float InVolume);

		void SetPosition(float InX, float InY, float InZ);
		void SetLooping(bool InLooping);

	private:
		CAudioEngine& AudioEngine;
		unsigned int SourceID;
	};
}