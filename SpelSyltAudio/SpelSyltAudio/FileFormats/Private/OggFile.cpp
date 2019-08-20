#include <SpelSyltAudio/FileFormats/Public/OggFile.h>

//----------------------------------------------------------------------

void SSAL::SOGGFile::OpenStream(const char* InPath)
{
	VorbisReader.OpenStream(InPath, *this);
}

//----------------------------------------------------------------------

void SSAL::SOGGFile::CloseStream()
{
	VorbisReader.CloseStream();
}

//----------------------------------------------------------------------

void SSAL::SOGGFile::ReadNextChunk()
{
	Chunk.DataSize = VorbisReader.ReadStream(Chunk.Data, OGG_CHUNK_SIZE, *this);
}

//----------------------------------------------------------------------

bool SSAL::SOGGFile::ContainsMoreData()
{
	return !VorbisReader.IsEOF();
}

//----------------------------------------------------------------------

SSAL::SOGGChunk& SSAL::SOGGFile::GetCurrentChunk()
{
	Chunk.SampleRate = SampleRate;
	Chunk.Format = Format;
	return Chunk;
}

//----------------------------------------------------------------------