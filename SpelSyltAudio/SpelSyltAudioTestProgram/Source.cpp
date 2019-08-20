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
	
	SSAL::CSoundSource SoundSource = AE.MakeSoundSource();

	SSAL::CMusicSource MusicSource = AE.MakeMusicSource();
	MusicSource.OpenOGGStream("Norrsken2.ogg");

	SSAL::SWavFile WavFile;
	WavFile.LoadFromFile("eagle.wav");
	SoundSource.BindWavFile(WavFile);

	AE.SetListenerPosition(0.f, 0.f, 0.f);

	MusicSource.Play();
	MusicSource.SetVolume(0.25f);
	
	SoundSource.Play(true);

	auto CurrentTime = std::chrono::high_resolution_clock::now();
	auto PreviousTime = CurrentTime;
	float DT = 0.f;
	float TotalTime = 0.f;

	while (true)
	{
		CurrentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> DT = std::chrono::duration_cast<std::chrono::duration<double>>(CurrentTime - PreviousTime);
		TotalTime += (float)DT.count();

		MusicSource.Tick();

		SoundSource.SetPosition(0.f, 0.f, sinf(TotalTime) * 10.f);
		
		PreviousTime = CurrentTime;
	}

	return 0;
}