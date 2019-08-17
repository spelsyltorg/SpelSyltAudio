#pragma once

#include <SpelSyltAudio/Engine/Public/SoundSource.h>

namespace SSAL
{
	struct SWavFormat;

	class CAudioEngine
	{
	public:
		CAudioEngine();
		~CAudioEngine();
		bool Initialize(int InBufferCount);

		CSoundSource MakeSource();
		void DestroySource(CSoundSource& InSource);

		void BindBufferToSource(CSoundSource& InSource, SWavFormat& InWav);

	private:
		void ShutDown();

		int BufferCount;
		int NextFreeBuffer;
		unsigned int* Buffers;
	};
}