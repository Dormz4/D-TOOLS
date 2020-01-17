#include "ElfAnalyze.h"
#include <QDebug>

//�ο�:https://github.com/bminor/binutils-gdb/blob/master/binutils/readelf.c


ElfAnalyze::ElfAnalyze()
{
}

ElfAnalyze::ElfAnalyze(unsigned char* elfFile)
{
	//��¼һЩ�ļ�ͷ
	QString status;
	//��¼elf�ļ�ͷ
	m_elfHeader = (Elf_Ehdr*)elfFile;
	//��¼����ͷ
	m_elfProgramHeader = (Elf_Phdr*)(int(m_elfHeader) + m_elfHeader->e_phoff);
	if (m_elfHeader->e_shstrndx != SHN_UNDEF && m_elfHeader->e_shstrndx < m_elfHeader->e_shnum) {
		//��¼�ڶ�ͷ
		m_elfSectionHeader = (Elf_Shdr*)(int(m_elfHeader) + m_elfHeader->e_shoff);

	}
	else
	{
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf header is not valied!");
		status = QString::fromLocal8Bit("�쳣ELF:��ʼ��elf section headerʧ��");
		change_txt_status(status);
	}

	//��¼�ַ����ڶΣ����������ַ�����
	m_elfStringTableHeader = (Elf_Shdr*)((int)m_elfHeader + m_elfHeader->e_shstrndx);



}

void ElfAnalyze::AnalyzeElf(unsigned char* elfFile)
{
	QString status;
	//bool isCorrectElfFile = true;

	//SetElfFileBit(elfFile);
	if (!VerifyElfHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf header is not valied!");
		status = QString::fromLocal8Bit("�쳣ELF:�ļ�ͷ����ȷ");
		change_txt_status(status);
		return;
	}

	/*if (!ReadProgramHeader()) {
		ElfAnalyzeLogDbg(NOT_VALID_ELF_FILE_BY_HEADER, "elf program header is not valied!");
		status = QString::fromLocal8Bit("�쳣ELF:����ͷ����ȷ");
		change_txt_status(status);
		return;
	}*/
	if (!getStringDataFromElf()) {

	}


	//����һϵ���ļ���Ϣ�Ķ�ȡ
	//1.��ʾ����ͷ����Ϣ
	//2.��ʾ����ͷ����Ϣ
	if (!getSections()) {
		ElfAnalyzeLogWar(NOT_VALID_ELF_FILE_BY_HEADER, QString::fromLocal8Bit("��ȡ������Ϣʧ��"));
	}
	//3.��ʾ��̬���ű�
	//4.������
	//5.�����



	status = QString::fromLocal8Bit("����ELF�ļ�");
	change_txt_status(status);

	int a = 10;
}

void ElfAnalyze::SetElfFileBit(unsigned char* elfFile)
{

}


//ȷ���Ƿ�Ϊ��ЧELF�ļ�
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




//��ȡ����ͷ
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
