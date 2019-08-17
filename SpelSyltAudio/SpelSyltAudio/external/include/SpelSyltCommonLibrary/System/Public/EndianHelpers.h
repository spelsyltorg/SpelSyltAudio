#pragma once

namespace CL
{
	enum class ESystemEndianType
	{
		Little,
		Big
		//Planet
	};

	ESystemEndianType GetSystemEndianType();

	short SwapEndian(const short InSwapSrc);
	unsigned short SwapEndian(const unsigned short InSwapSrc);

	int SwapEndian(const int InSwapSrc);
	unsigned int SwapEndian(const unsigned int InSwapSrc);

	long SwapEndian(const long InSwapSrc);
	unsigned long SwapEndian(const unsigned long InSwapSrc);

	long long SwapEndian(const long long InSwapSrc);
	unsigned long long SwapEndian(const unsigned long long InSwapSrc);
}