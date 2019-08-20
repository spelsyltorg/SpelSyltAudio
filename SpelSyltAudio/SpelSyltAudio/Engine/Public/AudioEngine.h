#pragma once
#include <SpelSyltAudio/Engine/Public/SSALTypes.h>
#include <SpelSyltAudio/Engine/Public/SoundSource.h>
#include <SpelSyltAudio/Engine/Public/MusicSource.h>

namespace SSAL
{
	struct SWavFile;
	struct SOGGChunk;

	class CAudioEngine
	{
	public:
		CAudioEngine();
		~CAudioEngine();
		bool Initialize(int InBufferCount);

		//BEGIN SOURCE FUNCTIONS
		CSoundSource MakeSoundSource();
		CMusicSource MakeMusicSource();

		void AddBufferToSourceQueue(FSourceID InSourceID, FBufferID InBuffer, SOGGChunk& InDataChunk);
		void DequeueBuffersFromSource(FSourceID InSourceID, int FreeBufferCount, FBufferID*& OutFreedBuffers);
		bool HaveProcessedBuffers(FSourceID InSourceID, int& OutProcessedCount);
		int GetBufferQueueCount(FSourceID InSurceID);

		void DestroySource(FSourceID InSource);
		void BindBufferToSource(FSourceID InSource, SWavFile& InWav);
		void PlaySource(FSourceID InSource);
		void PauseSource(FSourceID InSource);
		void StopSource(FSourceID InSource);
		void SetSourceGain(FSourceID InSource, float InGain);
		void SetSourcePosition(FSourceID InSource, float InX, float InY, float InZ);
		void SetSourceLooping(FSourceID InSource, bool InLooping);

		bool IsSourcePlaying(const CSoundSource& InSource);
		float GetSourceGain(const CSoundSource& InSource) const;
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