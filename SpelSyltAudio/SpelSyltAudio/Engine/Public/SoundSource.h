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

		void PlaySound(SWavFile& InWavFile);

		void SetVolume(float InVolume);

	private:
		CAudioEngine& AudioEngine;
		unsigned int SourceID;
	};
}