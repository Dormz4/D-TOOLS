#pragma once
#include "elf.h"
class ElfAnalyze
{
public:
	void AnalyzeElf(unsigned char* elfFile);

private:
	bool m_is32File;

	//32bit
private:
	Elf32_Ehdr* m_elf32Header;
	
	//64bit
private:
	Elf64_Ehdr* m_elf64Header;
};


