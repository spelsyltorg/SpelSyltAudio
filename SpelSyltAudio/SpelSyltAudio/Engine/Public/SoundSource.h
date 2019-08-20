#pragma once
#include <SpelSyltAudio/Engine/Public/AudioSource.h>
#include <SpelSyltAudio/Engine/Public/SSALTypes.h>

namespace SSAL
{
	class CAudioEngine;
	struct SWavFile;

	class CSoundSource final
		: public CAudioSource
	{
	public:
		friend CAudioEngine;
		CSoundSource() = delete;
		CSoundSource(CAudioEngine& InAudioEngine, FSourceID InSourceID);
		CSoundSource(const CSoundSource& InOther);

		void BindWavFile(SWavFile& InWavFile);
	};
}