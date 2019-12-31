#ifndef DZELF_H
#define DZELF_H
#include "elf.h"
#include <QtGlobal>


//#define TOSTR(fmt) #fmt
//#define FLFMT TOSTR([%s:%d])
//#define FNLINE TOSTR(\n)
//
//#define FLOGE(fmt, ...) printf(FLFMT fmt FNLINE, __FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define FLOGD(fmt, ...) printf(FLFMT fmt FNLINE, __FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define FLOGW(fmt, ...) printf(FLFMT fmt FNLINE, __FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define FLOGI(fmt, ...) printf(FLFMT fmt FNLINE, __FUNCTION__, __LINE__, ##__VA_ARGS__)
//#define FLOGV(fmt, ...) printf(FLFMT fmt FNLINE, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#ifdef Q_OS_WIN32
typedef Elf32_Ehdr Elf_Ehdr;
typedef Elf32_Phdr Elf_Phdr;
typedef Elf32_Shdr Elf_Shdr;
typedef Elf32_Sym Elf_Sym;
typedef Elf32_Dyn Elf_Dym;
typedef Elf32_Rel Elf_Rel;
typedef Elf32_Rela Elf_Rela;
typedef Elf32_Addr Elf_Addr;
typedef Elf32_Dyn Elf_Dyn;
typedef Elf32_Word Elf_Word;
#elif Q_OS_WIN64
#define __ELF64__
typedef Elf64_Ehdr Elf_Ehdr;
typedef Elf64_Phdr Elf_Phdr;
typedef Elf64_Shdr Elf_Shdr;
typedef Elf64_Sym Elf_Sym;
typedef Elf64_Dyn Elf_Dym;
typedef Elf64_Rel Elf_Rel;
typedef Elf64_Rela Elf_Rela;
typedef Elf64_Addr Elf_Addr;
typedef Elf64_Dyn Elf_Dyn;
typedef Elf64_Word Elf_Word;
#endif

#ifndef PAGE_SIZE
#define PAGE_SIZE 0x1000

#define PAGE_MASK (~(PAGE_SIZE-1))
// Returns the address of the page containing address 'x'.
#define PAGE_START(x)  ((x) & PAGE_MASK)

// Returns the offset of address 'x' in its page.
#define PAGE_OFFSET(x) ((x) & ~PAGE_MASK)

#define PAGE_END(x)    PAGE_START((x) + (PAGE_SIZE-1))

#endif	//PAGE_SIZE

#endif  //DZELF_H
