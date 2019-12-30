#include "ElfAnalyze.h"

void ElfAnalyze::AnalyzeElf(unsigned char* elfFile)
{
	m_elf32Header = (Elf32_Ehdr*)elfFile;
	int a = 10;
}
