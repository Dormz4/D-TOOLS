#pragma once
#include "dzelf.h"
#include <QObject>
#define  TAG "ElfAnalyze"
#define ElfAnalyzeLogDbg(x,...) qDebug()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogWar(x,...) qWarning()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogCrt(x,...) qCritical()<<TAG<<x<<__VA_ARGS__;
#define ElfAnalyzeLogFat(x,...) qFatal()<<TAG<<x<<__VA_ARGS__;

#define NOT_VALID_ELF_FILE_BY_HEADER "not a valid elf file! cause by "

//#include "../../UI/FileAnalyze/fileanalyzewindow.h"

typedef unsigned char dump_type;
typedef struct filedata
{
	const char* file_name;
	FILE* handle;
	long        file_size;
	Elf_Ehdr    file_header;
	Elf_Shdr* section_headers;
	Elf_Phdr* program_headers;
	char* string_table;
	unsigned long        string_table_length;
	/* A dynamic array of flags indicating for which sections a dump of
	   some kind has been requested.  It is reset on a per-object file
	   basis and then initialised from the cmdline_dump_sects array,
	   the results of interpreting the -w switch, and the
	   dump_sects_byname list.  */
	dump_type* dump_sects;
	unsigned int         num_dump_sects;
} Filedata;

//¼ÇÂ¼ Çø¶Î
struct MySection
{
	QString sectionName;
	int idx;
};


class ElfAnalyze : public QObject
{
	Q_OBJECT

signals:
	void change_txt_status(QString txt);

public:
	//ElfAnalyze(Ui::FileAnalyzeWindow* parentUi);
	ElfAnalyze();
	ElfAnalyze(unsigned char* elfFile);
	/*ElfAnalyze(void* parentUi);
	ElfAnalyze(Ui::FileAnalyzeWindow&);*/
	void AnalyzeElf(unsigned char* elfFile);

private:
	//bool m_is32File;


private:
	Elf_Ehdr* m_elfHeader;
	Elf_Phdr* m_elfProgramHeader;
	Elf_Shdr* m_elfSectionHeader;
	Elf_Shdr* m_elfStringTableHeader;

	uint32_t m_phdrNum;
	Elf_Addr m_phdrSize;
	QVector<MySection> m_sectionList;


private:
	void SetElfFileBit(unsigned char* elfFile);
	bool VerifyElfHeader();
	bool ReadProgramHeader();
	bool getSections();
	bool getStringDataFromElf();
};


