#pragma once

namespace SSAL
{
	enum class EAudioFileError
	{
		None = 0,
		FalseFormat = 1,
		PossibleCorruption = 2,
		UnexpectedEncryption = 3,
	};
}