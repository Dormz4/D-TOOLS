#include "ElfAnalyze.h"

void ElfAnalyze::AnalyzeElf(unsigned char* elfFile)
{
	//1.show the file is 32bit or 64bit.
	if (elfFile[4]==0x1) {
		//32bit
		m_is32File = true;
	}
	else if(elfFile[4]==0x2)
	{
		//64bit
		m_is32File = false;
	}
	m_elf32Header = (Elf32_Ehdr*)elfFile;
	int a = 10;
}
