#pragma once
#include "dzelf.h"
#define  TAG "ElfAnalyze"
#define ElfAnalyzeLogDbg(x,...) qDebug()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogWar(x,...) qWarning()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogCrt(x,...) qCritical()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogFat(x,...) qFatal()<<TAG<<x<<__VA_ARGS__;

#define NOT_VALID_ELF_FILE_BY_HEADER "not a valid elf file! cause by "


class ElfAnalyze
{
public:
	void AnalyzeElf(unsigned char* elfFile);

private:
	//bool m_is32File;


private:
	Elf_Ehdr* m_elfHeader;
	uint32_t m_phdrNum;
	Elf_Addr m_phdrSize;

private:
	void SetElfFileBit(unsigned char* elfFile);
	bool VerifyElfHeader();
	bool ReadProgramHeader();
};


