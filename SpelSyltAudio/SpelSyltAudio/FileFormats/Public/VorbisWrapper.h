#pragma once

struct OggVorbis_File;

namespace SSAL
{
	struct SOGGFile;

	class CVorbisWrapper
	{
	public:
		CVorbisWrapper();

		void OpenStream(const char* InPath, SOGGFile& InOggFile);
		void CloseStream();

		unsigned int ReadStream(char*& OutData, unsigned int InMaxSize, const SOGGFile& InOGGFile);
		bool IsEOF() const;
	private:
		OggVorbis_File* OggFile;
		int CurrentSection;
		bool EndOfFile;
	};
}