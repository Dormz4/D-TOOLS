#pragma once
#include "elf.h"
class ElfAnalyze
{
public:
	void AnalyzeElf(unsigned char* elfFile);
private:
	Elf32_Ehdr* m_elf32Header;
};


