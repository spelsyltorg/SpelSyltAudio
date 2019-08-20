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
		int GetBufferQueueCount(FSourceID InSourceID);

		void DestroySource(FSourceID InSourceID);
		void BindBufferToSource(FSourceID InSourceID, SWavFile& InWav);
		void PlaySource(FSourceID InSourceID);
		void PauseSource(FSourceID InSourceID);
		void StopSource(FSourceID InSourceID);
		void SetSourceGain(FSourceID InSourceID, float InGain);
		void SetSourcePosition(FSourceID InSourceID, float InX, float InY, float InZ);
		void SetSourceLooping(FSourceID InSourceID, bool InLooping);

		bool IsSourcePlaying(FSourceID InSourceID);
		float GetSourceGain(FSourceID InSourceID) const;
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