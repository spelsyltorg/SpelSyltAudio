#pragma once

namespace SSAL
{
	class CAudioEngine;
	struct SWavFormat;

	class CSoundSource
	{
	public:
		friend CAudioEngine;

		CSoundSource() = delete;
		CSoundSource(unsigned int InSourceID, CAudioEngine& InAudioEngine);
		CSoundSource(const CSoundSource& InOther);
		void DestroySource();

		void PlaySound(SWavFormat& InWavFile);

	private:
		CAudioEngine& AudioEngine;
		unsigned int SourceID;
	};
}