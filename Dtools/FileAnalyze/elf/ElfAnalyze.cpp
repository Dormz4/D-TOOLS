#include "ElfAnalyze.h"
#include <QDebug>

//参考:https://github.com/bminor/binutils-gdb/blob/master/binutils/readelf.c


ElfAnalyze::ElfAnalyze()
{
}

ElfAnalyze::ElfAnalyze(unsigned char* elfFile)
{
	//记录一些文件头
	QString status;
	//记录elf文件头
	m_elfHeader = (Elf_Ehdr*)elfFile;
	//记录程序头
	m_elfProgramHeader = (Elf_Phdr*)(int(m_elfHeader) + m_elfHeader->e_phoff);
	if (m_elfHeader->e_shstrndx != SHN_UNDEF && m_elfHeader->e_shstrndx < m_elfHeader->e_shnum) {
		//记录节段头
		m_elfSectionHeader = (Elf_Shdr*)(int(m_elfHeader) + m_elfHeader->e_shoff);

	}
	else
	{
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf header is not valied!");
		status = QString::fromLocal8Bit("异常ELF:初始化elf section header失败");
		change_txt_status(status);
	}

	//记录字符串节段，用于索引字符串滴
	m_elfStringTableHeader = (Elf_Shdr*)((int)m_elfHeader + m_elfHeader->e_shstrndx);



}

void ElfAnalyze::AnalyzeElf(unsigned char* elfFile)
{
	QString status;
	//bool isCorrectElfFile = true;

	//SetElfFileBit(elfFile);
	if (!VerifyElfHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf header is not valied!");
		status = QString::fromLocal8Bit("异常ELF:文件头不正确");
		change_txt_status(status);
		return;
	}

	/*if (!ReadProgramHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf program header is not valied!");
		status = QString::fromLocal8Bit("异常ELF:程序头不正确");
		change_txt_status(status);
		return;
	}*/
	if (!getStringDataFromElf()) {

	}


	//进行一系列文件信息的读取
	//1.显示程序头的信息
	//2.显示区段头的信息
	if (!getSections()) {
		ElfAnalyzeLogWar(NOT_VALID_ELF_FILE_BY_HEADER, QString::fromLocal8Bit("获取区段信息失败"));
	}
	//3.显示动态符号表
	//4.导出表
	//5.导入表



	status = QString::fromLocal8Bit("正常ELF文件");
	change_txt_status(status);

	int a = 10;
}

void ElfAnalyze::SetElfFileBit(unsigned char* elfFile)
{

}


//确定是否为有效ELF文件
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
		return false;
	}

	if (m_elfHeader->e_type != ET_DYN) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_type: %d", m_elfHeader->e_type);
		return false;
	}

	if (m_elfHeader->e_version != EV_CURRENT) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_version: %d", m_elfHeader->e_version);

		return false;
	}

	return true;

}




//读取程序头
bool ElfAnalyze::ReadProgramHeader()
{
	// Like the kernel, we only accept program header tables that
	// are smaller than 64KiB.
	m_phdrNum = m_elfHeader->e_phnum;
	// Like the kernel, we only accept program header tables that
	// are smaller than 64KiB.
	if (m_phdrNum < 1 || m_phdrNum > 65536 / sizeof(Elf_Phdr)) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "has unexpected e_phnum: %zu", m_phdrNum);

		return false;
	}

	m_phdrSize = m_phdrNum * sizeof(Elf_Phdr);
	void* mmapResult = new uint8_t[m_phdrSize];
	//if()


	return true;
}

bool ElfAnalyze::getSections()
{
	//m_elfSectionHeader
	for (int i = 0; i < m_elfHeader->e_shnum; i++) {
		MySection section = {};
		
		if (m_elfSectionHeader[i].sh_type == SHT_STRTAB) {
			int a = 10;
		}
		section.idx = i;
		section.sectionName = m_elfSectionHeader[i].sh_name;
		m_sectionList.append(section);
	}

	return true;
}

bool ElfAnalyze::getStringDataFromElf()
{
	Elf_Shdr* m_elfStringTableHeader = (Elf_Shdr*)((int)m_elfHeader + m_elfHeader->e_shstrndx);

	return false;
}
