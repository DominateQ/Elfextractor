#ifndef ELFHEADER_H
#define ELFHEADER_H

typedef void*           Elf64_Addr;
typedef unsigned long   Elf64_Off;
typedef unsigned short  Elf64_Half;
typedef unsigned int    Elf64_Word;
typedef int             Elf64_Sword;
typedef unsigned long   Elf64_Xword;
typedef long            Elf64_Sxword;
typedef unsigned char   Elf64_Byte;

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

#define	SECTION_TABLE(elfp, ehdr)		((elfp) + (ehdr)->e_shoff)
#define	SECTION_TABEL_ENTRY_OFFSET(ehdr, idx)	((ehdr)->e_shoff + (ehdr)->e_shentsize * (idx))

int find_section_header_index(char* elfp, Elf64_Ehdr* ehdrp, Elf64_Word type, int sidx);
//int find_section_header_index(char* elfp, Elf64_Ehdr* ehdrp, Elf64_Word type);

//Section Types
#define SHT_NULL        0
#define SHT_PROGBITS    1
#define SHT_SYMTAB      2
#define SHT_STRTAB      3
#define SHT_RELA        4
#define SHT_HASH        5
#define SHT_DYNAMIC     6
#define SHT_NOTE        7
#define SHT_NOBITS      8
#define SHT_REL         9
#define SHT_SHLIB       10
#define SHT_DYNSYM      11
#define SHT_LOOS        0x60000000
#define SHT_HIOS        0x6FFFFFFF
#define SHT_LOPROC      0x70000000
#define SHT_HIPROC      0X7FFFFFFF

//Section header
typedef struct __attribute__((packed))
{   
    Elf64_Word      sh_name;
    Elf64_Word      sh_type;
    Elf64_Xword     sh_flags;
    Elf64_Addr      sh_addr;
    Elf64_Off       sh_offset;
    Elf64_Xword     sh_size;
    Elf64_Word      sh_link;
    Elf64_Word      sh_info;
    Elf64_Xword     sh_addralign;
    Elf64_Xword     sh_entsize;
} Elf64_Shdr;

#endif  //ELFHEADER_H
