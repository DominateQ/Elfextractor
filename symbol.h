#ifndef	SYMBOL_H
#define	SYMBOL_H

#include "header.h"

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

#endif	//SYMBOL_H