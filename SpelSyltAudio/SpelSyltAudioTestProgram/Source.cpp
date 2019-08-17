#include "../SpelSyltAudio/FileFormats/Public/WavFile.h"
#include "../SpelSyltAudio/Engine/Public/AudioEngine.h"
#include "../SpelSyltAudio/Engine/Public/SoundSource.h"

#pragma comment(lib, "SpelSyltAudio_Debug")

int main()
{
	SSAL::CAudioEngine AE;
	AE.Initialize(1);
	SSAL::CSoundSource Source = AE.MakeSource();

	SSAL::SWavFormat WavFile;
	WavFile.LoadFromFile("Norrsken.wav");

	Source.PlaySound(WavFile);

	while (true)
	{

	}

	return 0;
}