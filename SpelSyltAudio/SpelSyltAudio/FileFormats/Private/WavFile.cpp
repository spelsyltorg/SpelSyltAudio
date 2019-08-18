#pragma comment(lib, "SpelSyltCommonLibrary_Debug")

#include <SpelSyltAudio/FileFormats/Public/WavFile.h>

#include <SpelSyltCommonLibrary/System/Public/EndianHelpers.h>

#include <fstream>
#include <memory>

//Specs for the Wav format can be found here: https://web.archive.org/web/20141213140451/https://ccrma.stanford.edu/courses/422/projects/WaveFormat/

#define WAV_HEADER_SIZE 0x00000044
#define RIFF			0x46464952
#define WAVE			0x45564157
#define FMT				0x20746d66
#define DATA			0x61746164

//----------------------------------------------------------------------

void SSAL::SWavFile::LoadFromMemory(char* InDataStart, unsigned int InSize)
{
	char* CurrentData = InDataStart;
	
	if (ReadChunk(CurrentData) != EAudioFileError::None)
	{
		return;
	}
	
	if (ReadSubchunkOne(CurrentData) != EAudioFileError::None)
	{
		return;
	}
	
	if (ReadSubchunkTwo(CurrentData) != EAudioFileError::None)
	{
		return;
	}
}

//----------------------------------------------------------------------

void SSAL::SWavFile::LoadFromFile(const char* InPath)
{
	std::ifstream FileStream(InPath, std::ifstream::binary);
	FileStream.seekg(0, std::iostream::end);
	auto FileSize = FileStream.tellg();

	char* RawFileData = new char[FileSize];

	FileStream.seekg(0, std::iostream::beg);

	FileStream.read(RawFileData, FileSize);

	FileStream.close();

	LoadFromMemory(RawFileData, FileSize);
}

//----------------------------------------------------------------------

void SSAL::SWavFile::GetData(char*& OutData, int& OutDataSize)
{
	OutData = Data;
	OutDataSize = DataSize;
}

//----------------------------------------------------------------------

int SSAL::SWavFile::GetSampleRate() const
{
	return SampleRate;
}

//----------------------------------------------------------------------

SSAL::EAudioFormat SSAL::SWavFile::GetFormat() const
{
	return Format;
}

//----------------------------------------------------------------------

SSAL::EAudioFileError SSAL::SWavFile::ReadChunk(char*& InData)
{
	const CL::ESystemEndianType SystemEndianType = CL::GetSystemEndianType();

	//Expect to find RIFF at the beginning
	int RiffMem = 0;
	memcpy_s(&RiffMem, sizeof(RiffMem), InData, 4);
	if (RiffMem != RIFF)
	{
		return EAudioFileError::FalseFormat;
	}

	InData = &InData[4]; //Offset with the amount we just read

	//Read total file size with Riff and This part
	int ChunkSizeMem = 0;
	memcpy_s(&ChunkSizeMem, sizeof(ChunkSizeMem), InData, 4);
	
	//This is read as little endian, meaning that if we read this on a big endian structure we need to flip it to be able to use it
	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		ChunkSizeMem = CL::SwapEndian(ChunkSizeMem);
	}

	InData = &InData[4];

	//Expect to find WAVE in format
	int WaveMem = 0;
	memcpy_s(&WaveMem, sizeof(WaveMem), InData, 4);
	if (WaveMem != WAVE)
	{
		return EAudioFileError::FalseFormat;
	}

	InData = &InData[4];

	return EAudioFileError::None;
}

//----------------------------------------------------------------------

SSAL::EAudioFileError SSAL::SWavFile::ReadSubchunkOne(char*& InData)
{
	const CL::ESystemEndianType SystemEndianType = CL::GetSystemEndianType();

	//Expect to find "fmt "
	int FmtMem = 0;
	memcpy_s(&FmtMem, sizeof(FmtMem), InData, 4);

	if (FmtMem != FMT)
	{
		return EAudioFileError::PossibleCorruption;
	}

	InData = &InData[4];

	//Get the size of this subchunk, for non compressed wav files this should be 16
	int SubchunkSizeMem = 0;
	memcpy_s(&SubchunkSizeMem, sizeof(SubchunkSizeMem), InData, 4);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		SubchunkSizeMem = CL::SwapEndian(SubchunkSizeMem);
	}

	if (SubchunkSizeMem != 16)
	{
		return EAudioFileError::UnexpectedEncryption;
	}

	InData = &InData[4];

	//Get the audio format. Expecting PCM (non compressed) which is 1
	short FormatMem = 0;
	memcpy_s(&FormatMem, sizeof(FormatMem), InData, 2);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		FormatMem = CL::SwapEndian(FormatMem);
	}

	if (FormatMem != 1)
	{
		return EAudioFileError::UnexpectedEncryption;
	}

	InData = &InData[2];

	//Get the channel count (1 = Mono, 2 = Stereo...)
	short ChannelCountMem = 0;
	memcpy_s(&ChannelCountMem, sizeof(ChannelCountMem), InData, 2);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		ChannelCountMem = CL::SwapEndian(ChannelCountMem);
	}

	InData = &InData[2];

	//Read the sample rate
	int SampleRateMem = 0;
	memcpy_s(&SampleRateMem, sizeof(SampleRateMem), InData, 4);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		SampleRateMem = CL::SwapEndian(SampleRateMem);
	}

	SampleRate = SampleRateMem;
	InData = &InData[4];

	//Read the byte rate
	int ByteRateMem = 0;
	memcpy_s(&ByteRateMem, sizeof(ByteRateMem), InData, 4);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		ByteRateMem = CL::SwapEndian(ByteRateMem);
	}

	InData = &InData[4];

	//Read the block align, this is the size of a sample
	short BlockAlignMem = 0;
	memcpy_s(&BlockAlignMem, sizeof(BlockAlignMem), InData, 2);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		BlockAlignMem = CL::SwapEndian(BlockAlignMem);
	}

	InData = &InData[2];

	//Read the bits per sample (8 bit, 16 bits, 32 bits ...)
	short BPSMem = 0;
	memcpy_s(&BPSMem, sizeof(BPSMem), InData, 2);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		BPSMem = CL::SwapEndian(BPSMem);
	}

	SetFormat(BPSMem, ChannelCountMem);

	InData = &InData[2];

	//Down here is where we would potentially read if we allowed encrypted WAV files

	return EAudioFileError::None;
}

SSAL::EAudioFileError SSAL::SWavFile::ReadSubchunkTwo(char*& InData)
{
	const CL::ESystemEndianType SystemEndianType = CL::GetSystemEndianType();

	//Expect to find "data"
	int DataMem = 0;
	memcpy_s(&DataMem, sizeof(DataMem), InData, 4);

	if (DataMem != DATA)
	{
		return EAudioFileError::PossibleCorruption;
	}

	InData = &InData[4];

	//Read the size of the data
	int DataSizeMem = 0;
	memcpy_s(&DataSizeMem, sizeof(DataSizeMem), InData, 4);

	if (SystemEndianType == CL::ESystemEndianType::Big)
	{
		DataSizeMem = CL::SwapEndian(DataSizeMem);
	}

	InData = &InData[4];

	DataSize = DataSizeMem;

	//Read the actual data
	Data = new char[DataSizeMem];
	memcpy_s(Data, DataSizeMem, InData, DataSizeMem);

	return EAudioFileError::None;
}

//----------------------------------------------------------------------

void SSAL::SWavFile::SetFormat(short InBitsPerSample, short InChannelCount)
{
	if (InBitsPerSample == 8 && InChannelCount == 1)
	{
		Format = EAudioFormat::Mono8;
	}

	if (InBitsPerSample == 16 && InChannelCount == 1)
	{
		Format = EAudioFormat::Mono16;
	}

	if (InBitsPerSample == 8 && InChannelCount == 2)
	{
		Format = EAudioFormat::Stereo8;
	}

	if (InBitsPerSample == 16 && InChannelCount == 2)
	{
		Format = EAudioFormat::Stereo16;
	}
}

//----------------------------------------------------------------------