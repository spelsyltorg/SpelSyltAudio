#include "../SpelSyltAudio/FileFormats/Public/WavFile.h"
#include "../SpelSyltAudio/Engine/Public/AudioEngine.h"
#include "../SpelSyltAudio/Engine/Public/SoundSource.h"
#include "../SpelSyltAudio/Engine/Public/MusicSource.h"

#include <chrono>

#pragma comment(lib, "SpelSyltAudio_Debug")

int main()
{
	SSAL::CAudioEngine AE;
	AE.Initialize(200);
	SSAL::CMusicSource Source = AE.MakeMusicSource();
	Source.OpenOGGStream("Norrsken.ogg");

	//SSAL::SWavFile WavFile;
	//WavFile.LoadFromFile("Norrsken.wav");

	AE.SetListenerPosition(0.f, 0.f, 0.f);
	//Source.SetPosition(0.f, 0.f, 0.f);
	//
	//Source.SetVolume(1.f);
	//Source.PlaySound(WavFile, true);

	Source.Play();
	Source.SetVolume(0.25f);

	//auto CurrentTime = std::chrono::high_resolution_clock::now();
	//auto PreviousTime = CurrentTime;
	//float DT = 0.f;
	//float TotalTime = 0.f;

	while (true)
	{
		//CurrentTime = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<double> DT = std::chrono::duration_cast<std::chrono::duration<double>>(CurrentTime - PreviousTime);
		//TotalTime += (float)DT.count();

		Source.Tick();

		//Source.SetPosition(0.f, 0.f, sinf(TotalTime) * 10.f);
		//
		//PreviousTime = CurrentTime;
		//
		//if (TotalTime >= 5.f && TotalTime <= 10.f)
		//{
		//	Source.Stop();
		//}
		//else if (TotalTime >= 10.f)
		//{
		//	Source.Play();
		//}
	}

	return 0;
}