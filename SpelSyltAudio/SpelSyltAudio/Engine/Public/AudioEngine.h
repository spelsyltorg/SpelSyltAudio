#pragma once

#include <SpelSyltAudio/Engine/Public/SoundSource.h>

namespace SSAL
{
	struct SWavFile;

	class CAudioEngine
	{
	public:
		CAudioEngine();
		~CAudioEngine();
		bool Initialize(int InBufferCount);

		CSoundSource MakeSource();
		void DestroySource(CSoundSource& InSource);

		void BindBufferToSource(CSoundSource& InSource, SWavFile& InWav);
		void SetSourceGain(CSoundSource& InSource, float InGain);

	private:
		void ShutDown();

		int BufferCount;
		int NextFreeBuffer;
		unsigned int* Buffers;
	};
}