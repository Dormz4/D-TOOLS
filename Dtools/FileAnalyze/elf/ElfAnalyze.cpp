#include "ElfAnalyze.h"
#include <QDebug>


void ElfAnalyze::AnalyzeElf(unsigned char* elfFile)
{
	m_elfHeader = (Elf32_Ehdr*)elfFile;

	//SetElfFileBit(elfFile);
	if (!VerifyElfHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf header is not valied!");
		return;
	}

	if (!ReadProgramHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf program header is not valied!");
	}

	////1.show the file is 32bit or 64bit.
	//if (elfFile[4]==0x1) {
	//	//32bit
	//	m_is32File = true;
	//}
	//else if(elfFile[4]==0x2)
	//{
	//	//64bit
	//	m_is32File = false;
	//}



	int a = 10;
}

void ElfAnalyze::SetElfFileBit(unsigned char* elfFile)
{

}

bool ElfAnalyze::VerifyElfHeader()
{
	if ((m_elfHeader->e_ident[EI_MAG0] != ELFMAG0) ||
		(m_elfHeader->e_ident[EI_MAG1] != ELFMAG1) ||
		(m_elfHeader->e_ident[EI_MAG2] != ELFMAG2) ||
		(m_elfHeader->e_ident[EI_MAG3] != ELFMAG3)) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "cause by elfHeader.e_ident[] ");
		return false;
	}
#ifdef __ELF64__
	if (m_elfHeader->e_ident[EI_CLASS] != ELFCLASS64) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "e_ident[EI_CLASS]!= ELFCLASS64");
		return false;
	}
#else
	if (m_elfHeader->e_ident[EI_CLASS] != ELFCLASS32) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "e_ident[EI_CLASS]!= ELFCLASS32");
		return false;
	}
#endif 
	if (m_elfHeader->e_ident[EI_DATA] != ELFDATA2LSB) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "not little-endian: %d", m_elfHeader->e_ident[EI_DATA]);
		//FLOGE("\"%s\" not little-endian: %d", name_, m_elfHeader->_ident[EI_DATA]);
		return false;
	}

	if (m_elfHeader->e_type != ET_DYN) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_type: %d", m_elfHeader->e_type);
		//FLOGE("\"%s\" has unexpected e_type: %d", name_, m_elfHeader->_type);
		return false;
	}

	if (m_elfHeader->e_version != EV_CURRENT) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_version: %d", m_elfHeader->e_version);

		//FLOGE("\"%s\" has unexpected e_version: %d", name_, m_elfHeader->_version);
		return false;
	}

	return true;

}

bool ElfAnalyze::ReadProgramHeader()
{
	// Like the kernel, we only accept program header tables that
	// are smaller than 64KiB.
	m_phdrNum = m_elfHeader->e_phnum;
	// Like the kernel, we only accept program header tables that
	// are smaller than 64KiB.
	if (m_phdrNum < 1 || m_phdrNum > 65536 / sizeof(Elf_Phdr)) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_phnum: %zu", m_phdrNum);

		//FLOGE("\"%s\" has invalid e_phnum: %zu", name_, phdr_num_);
		return false;
	}

	m_phdrSize = m_phdrNum * sizeof(Elf_Phdr);
	void* mmapResult = new uint8_t[m_phdrSize];
	//if()


	return true;
}
