#ifndef ELFHEADER_H
#define ELFHEADER_H

#include "global.h"

#define El_MAG0         0
#define El_MAG1         1
#define El_MAG2         2
#define El_MAG3         3
#define El_CLASS        4
#define El_DATA         5
#define El_VERSION      6
#define El_OSABI        7
#define El_ABIVERSION   8
#define El_PAD          9
#define El_NIDENT       16   

#define ELFCLASS32      1
#define ELFCLASS64      2

#define ELFDATA2LSB     1
#define ELFDATA2MSB     2

#define ELFOSABI_SYSV       0
#define ELFOSABI_HPUX       1
#define ELFOSABI_STANDALONE 255

#define ET_NONE         0
#define ET_REL          1
#define ET_EXEC         2
#define ET_DYN          3
#define ET_CORE         4
#define ET_LOOS         0xFE00
#define ET_HIOS         0xFEFF
#define ET_LOPROC       0XFF00
#define ET_HIPROC       0XFFFF

#define EM_NONE         0
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3
#define EM_68K          4
#define EM_88K          5
#define EM_860          7
#define EM_MIPS         8
#define EM_ARM          40
#define EM_X64_INTEL    62  

#define EV_NONE         0
#define EV_CURRENT      1

typedef struct __attribute__((packed))
{
    Elf64_Byte e_ident[16];
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;
    Elf64_Off e_phoff;
    Elf64_Off e_shoff;
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf64_Ehdr;


int header_finder(unsigned char* buff, int size);
void machine_type(Elf64_Half);
int elfheader(int fd, Elf64_Ehdr* ehp);

#endif  //ELFHEADER_H
