#include <SpelSyltAudio/FileFormats/Public/VorbisWrapper.h>

#include <SpelSyltAudio/FileFormats/Public/OggFile.h>

#include <SpelSyltCommonLibrary/System/Public/EndianHelpers.h>

#include <vorbisfile.h>

#include <cassert>

//----------------------------------------------------------------------

namespace
{
	SSAL::EAudioFormat TranslateBitrateAndChannelCountToSSALFormat(unsigned int InBitrate, unsigned int InChannelCount)
	{
		if (InBitrate == 8 && InChannelCount == 1)
		{
			return SSAL::EAudioFormat::Mono8;
		}
		if (InBitrate == 8 && InChannelCount == 2)
		{
			return SSAL::EAudioFormat::Stereo8;
		}
		if (InBitrate == 16 && InChannelCount == 1)
		{
			return SSAL::EAudioFormat::Mono16;
		}
		if (InBitrate == 16 && InChannelCount == 2)
		{
			return SSAL::EAudioFormat::Stereo16;
		}

		return SSAL::EAudioFormat::Mono8;
	}
}


//----------------------------------------------------------------------

SSAL::CVorbisWrapper::CVorbisWrapper()
	: OggFile()
	, CurrentSection(0)
	, EndOfFile(false)
{
}

//----------------------------------------------------------------------

void SSAL::CVorbisWrapper::OpenStream(const char* InPath, SOGGFile& InOggFile)
{
	OggFile = new OggVorbis_File();
	const int OpenErrorCode = ov_fopen(InPath, OggFile);
	assert(OpenErrorCode == 0 && "Failed to open ogg file");

	vorbis_info * Info = ov_info(OggFile, -1);
	InOggFile.SampleRate = static_cast<unsigned int>(Info->rate);
	InOggFile.Format = ::TranslateBitrateAndChannelCountToSSALFormat(16, Info->channels);
}

//----------------------------------------------------------------------

void SSAL::CVorbisWrapper::CloseStream()
{
	ov_clear(OggFile);
	delete OggFile;
}

//----------------------------------------------------------------------

unsigned int SSAL::CVorbisWrapper::ReadStream(char*& OutData, unsigned int InMaxSize, const SOGGFile & InOGGFile)
{
	int EndianDefinition = 0;
	if (CL::ESystemEndianType::Big == CL::GetSystemEndianType())
	{
		EndianDefinition = 1;
	}

	int ReadWord = 1;
	if (InOGGFile.Format == EAudioFormat::Mono16 || InOGGFile.Format == EAudioFormat::Stereo16)
	{
		ReadWord = 2;
	}

	long TotalBytesRead = 0;

	//Fill the chunk
	while (TotalBytesRead != InMaxSize && !EndOfFile)
	{
		long BytesRead = ov_read(OggFile, &OutData[TotalBytesRead], InMaxSize - TotalBytesRead, EndianDefinition, ReadWord, 1, &CurrentSection);
		TotalBytesRead += BytesRead;
		
		if (BytesRead == 0)
		{
			EndOfFile = true;
		}
	}

	return static_cast<unsigned int>(TotalBytesRead);
}

//----------------------------------------------------------------------

bool SSAL::CVorbisWrapper::IsEOF() const
{
	return EndOfFile;
}

//----------------------------------------------------------------------