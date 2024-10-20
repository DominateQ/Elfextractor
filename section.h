#ifndef SECTION_H
#define SECTION_H

#include "global.h"
#include "elfheader.h"

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

//Symbol Table Entry
typedef struct __attribute__((packed))
{
    Elf64_Word      st_name;
    unsigned char   st_info;
    unsigned char   st_other;
    Elf64_Half      st_shndx;
    Elf64_Addr      st_value;
    Elf64_Xword     st_size;
} Elf64_Sym;

//Symbol Types
#define STT_NOTYPE      0
#define STT_OBJECT      1
#define STT_FUNC        2
#define STT_SECTION     3
#define STT_FILE        4
#define STT_LOOS        10
#define STT_HIOS        12
#define STT_LOPROC      13
#define STT_HIPROC      15

//Symbol Bindings
#define STB_LOCAL       0
#define STB_GLOBAL      1
#define STB_WEAK        2
#define STB_LOOS        10
#define STB_HIOS        12
#define STB_LOPROC      13
#define STB_HIPROC      15

//Special Section Indexes
#define SHN_UNDEF       0
#define SHN_LORESERVE   0xFF00
#define SHN_LOPROC      0XFF00
#define SHN_HIPROC      0XFF1F
#define SHN_LOOS        0XFF20
#define SHN_HIOS        0XFF3F
#define SHN_ABS         0XFFF1
#define SHN_COMMON      0XFFF2
#define SHN_XINDEX      0XFFFF
#define SHN_HIRESERVE   0XFFFF

//Symbol Visibility
#define STV_DEFAULT     0
#define STV_INTERNAL    1
#define STV_HIDDEN      2
#define STV_PROTECTED   3

int string_table(int fd, Elf64_Ehdr* ehp);
int symbol_table(int fd, Elf64_Ehdr* ehp);
int print_symbol_table(int fd, Elf64_Shdr* shp, int i);
int find_name_with_offset_in_string_table(char* strp, int len, int offset, char** retstrp);

#endif //SECTION_H