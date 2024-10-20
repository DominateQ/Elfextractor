#ifndef RELOCATION_H
#define RELOCATION_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"
//#include "section.h"

#define ELF64_R_SYM(i)        ((i) >> 32)
#define ELF64_R_TYPE(i)       ((i) & 0xffffffffL)
#define ELF64_R_INFO(s, t)    (((s) << 32)) + (((t) & 0xffffffffL))  

typedef struct 
{
    Elf64_Addr      r_offset;
    Elf64_Xword     r_info;
} Elf64_Rel;

typedef struct 
{
    Elf64_Addr      r_offset;
    Elf64_Xword     r_info;
    Elf64_Sxword    r_addend;
} Elf64_Rela;

//Relocation types
typedef enum {
    R_X86_64_NONE,
    R_X86_64_64,
    R_X86_64_PC32,
    R_X86_64_GOT32,
    R_X86_64_PLT32,
    R_X86_64_COPY,
    R_X86_64_GLOB_DAT,
    R_X86_64_JUMP_SLOT,
    R_X86_64_RELATIVE,
    R_X86_64_GOTPCREL,
    R_X86_64_32,
    R_X86_64_32S,
    R_X86_64_16,
    R_X86_64_PC16,
    R_X86_64_8,
    R_X86_64_PC8,
    R_X86_64_PC64 = 24,
    R_X86_64_GOTOFF64,
    R_X86_64_GOTPC32,
    R_X86_64_SIZE32 = 32,
    R_X86_64_SIZE64
} relocation_types;

void process_relocation(char* elfp);

#endif //RELOCATION_H