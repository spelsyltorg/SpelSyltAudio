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

		//BEGIN SOURCE FUNCTIONS
		CSoundSource MakeSource();
		void DestroySource(CSoundSource& InSource);
		void BindBufferToSource(CSoundSource& InSource, SWavFile& InWav);
		void PlaySource(CSoundSource& InSource);
		void PauseSource(CSoundSource& InSource);
		void StopSource(CSoundSource& InSource);
		void SetSourceGain(CSoundSource& InSource, float InGain);
		void SetSourcePosition(CSoundSource& InSource, float InX, float InY, float InZ);
		void SetSourceLooping(CSoundSource& InSource, bool InLooping);

		bool IsSourcePlaying(CSoundSource& InSource);
		//END SOURCE FUNCTIONS

		//BEGIN LISTENER FUNCTIONS
		void SetListenerPosition(float InX, float InY, float InZ);
		//END LISTENER FUNCTIONS
	private:
		void ShutDown();

		int BufferCount;
		int NextFreeBuffer;
		unsigned int* Buffers;
	};
}