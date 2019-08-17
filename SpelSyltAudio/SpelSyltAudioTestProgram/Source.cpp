#include "../SpelSyltAudio/FileFormats/Public/WavFile.h"
#include "../SpelSyltAudio/Engine/Public/AudioEngine.h"
#include "../SpelSyltAudio/Engine/Public/SoundSource.h"

#include <chrono>

#pragma comment(lib, "SpelSyltAudio_Debug")

int main()
{
	SSAL::CAudioEngine AE;
	AE.Initialize(1);
	SSAL::CSoundSource Source = AE.MakeSource();

	SSAL::SWavFile WavFile;
	WavFile.LoadFromFile("eagle.wav");

	AE.SetListenerPosition(0.f, 0.f, 0.f);
	Source.SetPosition(0.f, 0.f, 0.f);

	Source.PlaySound(WavFile, true);

	auto CurrentTime = std::chrono::high_resolution_clock::now();
	auto PreviousTime = CurrentTime;
	float DT = 0.f;
	float TotalTime = 0.f;

	while (true)
	{
		CurrentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> DT = std::chrono::duration_cast<std::chrono::duration<double>>(CurrentTime - PreviousTime);
		TotalTime += (float)DT.count();
		
		Source.SetPosition(0.f, 0.f, sinf(TotalTime) * 10.f);

		PreviousTime = CurrentTime;
	}

	return 0;
}