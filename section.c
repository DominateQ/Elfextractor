/*
 * section.c
 * Written by Liao Yuyi<liaoyuyi0302@outlook.com>
 * (C)Copyright 2024 
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "section.h"

#define BUFF_SIZE 8196
#define SYM_BUFF_SIZE 64
#define ELF64_ST_VISIBILITY(o) ((o)&0x3)

int find_name_with_offset_in_string_table(char* strp, int len, int offset, char** retstrp);

int string_table(int fd, Elf64_Ehdr* ehp)
{
    off_t ret;
    ssize_t bytes_read;
    char buff[BUFF_SIZE];
    char* section_bufferp;
    Elf64_Shdr* shp;
    int offset, str_num, strtab_index;
    int i;

    //String_table
    printf("Size: %d\n", ehp->e_shentsize);
    printf("Number of entries: %d\n", ehp->e_shnum);
    printf("Offset: %ld\n", ehp->e_shoff);

    ret = lseek(fd, ehp->e_shoff, SEEK_SET);
    if (ret == -1)
    {
        //perror("abc");
        printf("Error occur when setting offset.\n");
        return -1;
    }
    
    memset(buff, 0, BUFF_SIZE);
    bytes_read = read(fd, buff, ((ehp->e_shentsize) * (ehp->e_shnum)));
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    }
    shp = (Elf64_Shdr*)buff;
   
    shp += ehp->e_shstrndx;
    printf("Section name string table index: %d\n", ehp->e_shstrndx);
    lseek(fd, shp->sh_offset, SEEK_SET);
    section_bufferp = malloc(shp->sh_size);
    if (section_bufferp == NULL)
    {
        printf("Failure of allocating memory.\n");
        return -1;
    }
    bytes_read = read(fd, section_bufferp, shp->sh_size);
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    }

    offset = 0;
    while (offset < shp->sh_size)
    {
        printf("%s: %d\n", section_bufferp + offset, offset);
        offset += strlen(section_bufferp + offset) + 1;
    }
    free(section_bufferp);

    shp = (Elf64_Shdr*)buff;
    str_num = 0;
    for (i = 0; i < ehp->e_shnum; i++)
    {
        if ((shp + i)->sh_type != SHT_STRTAB)
            continue;

        lseek(fd, (shp + i)->sh_offset, SEEK_SET);
        section_bufferp = malloc((shp + i)->sh_size);  
        if (section_bufferp == NULL)
        {
            printf("Failure of allocating memory.\n");
            return -1;
        }
        bytes_read = read(fd, section_bufferp, (shp + i)->sh_size);
        if (bytes_read == -1)
        {
            printf("Error occur when reading this file.\n");
            return -1;
        }

        offset = 0;
        strtab_index = 0;
        while (offset < (shp + i)->sh_size)
        {
            printf("%d: %s - %ld\n", strtab_index, section_bufferp + offset, (shp + i)->sh_size);
            offset += strlen(section_bufferp + offset) + 1;
            strtab_index++;
        }
        free(section_bufferp);
        printf("\n\n");
        str_num += 1;
    }

    printf("String table number: %d\n", str_num);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
    return 0;      
}

/**
 * find_name_with_index_in_string_table - find name with index in string table
 *  @strp: pointer to string table
 *  @len: length of string table
 *  @index: which index in string table
 *  @retstrp: pointer to string by '@index'
 * return value: 0 - success
 *              -1 - failure
 */
static int find_name_with_index_in_string_table(char* strp, int len, int index, char** retstrp)
{
    int counter, offset;
    char *p = strp;

    counter = offset = 0;
    while (offset < len)
    {
        counter += 1;
        if (counter > index) {
            *retstrp = p;
            return 0;
        }
        offset += strlen(p) + 1;
        p += strlen(p) + 1;
    }

    return -1;
}

void symbol_type(unsigned char info, char* strtype)
{
    switch (info & 0xf)
    {
    case STT_NOTYPE:
        strncpy(strtype, "NoType", sizeof("NoType") - 1);
        break;
    case STT_OBJECT:
        strncpy(strtype, "Object", sizeof("Object") - 1);
        break;
    case STT_FUNC:
        strncpy(strtype, "Func", sizeof("Func") - 1);
        break;
    case STT_SECTION:
        strncpy(strtype, "Section", sizeof("Section") - 1);
        break;
    case STT_FILE:
        strncpy(strtype, "File", sizeof("File") - 1);
        break;
    case STT_LOOS:
        strncpy(strtype, "LOOS", sizeof("LOOS") - 1);
        break;
    case STT_HIOS:
        strncpy(strtype, "HIOS", sizeof("HIOS") - 1);
        break;
    case STT_LOPROC:
        strncpy(strtype, "LOPROC", sizeof("LOPROC") - 1);
        break;
    case STT_HIPROC:
        strncpy(strtype, "HIPROC", sizeof("HIPROC") - 1);
        break;
    default:
        strncpy(strtype, "Unsupported", sizeof("Unsupported") - 1);
        break;
    }
}

void symbol_bindings(unsigned char info, char* bind)
{
    switch (info >> 4)
    {
    case STB_LOCAL:
        strncpy(bind, "LOCAL", sizeof("LOCAL") - 1);
        break;
    case STB_GLOBAL:
        strncpy(bind, "GLOBAL", sizeof("GLOBAL") - 1);
        break;
    case STB_WEAK:
        strncpy(bind, "WEAK", sizeof("WEAK") - 1);
        break;
    case STB_LOOS:
        strncpy(bind, "LOOS", sizeof("LOOS") - 1);
        break;
    case STB_HIOS:
        strncpy(bind, "HIOS", sizeof("HIOS") - 1);
        break;
    case STB_LOPROC:
        strncpy(bind, "LOPROC", sizeof("LOPROC") - 1);
        break;
    case STB_HIPROC:
        strncpy(bind, "HIPROC", sizeof("HIPROC") - 1);
        break;
    default:
        strncpy(bind, "Unsupported", sizeof("Unsupported") - 1);
        break;
    }
}

/** 
 * symbol_visibility: judge a symbol's visibility
 * @other: st_other from targeted symbol
 * @vis: return the symbol's visibility to buff_return
*/
void symbol_visibility(unsigned char other, char* vis)
{
    switch (ELF64_ST_VISIBILITY(other))
    {
    case STV_DEFAULT:
        strncpy(vis, "DEFAULT", sizeof("DEFAULT") - 1);
        break;
    case STV_INTERNAL:
        strncpy(vis, "INTERNAL", sizeof("INTERNAL") - 1);
        break;
    case STV_HIDDEN:
        strncpy(vis, "HIDDEN", sizeof("HIDDEN") - 1);
        break;
    case STV_PROTECTED:
        strncpy(vis, "PROTECTED", sizeof("PROTECTED") - 1);
        break;
    }
}

/** 
 * symbol_section_index: extract the section index of relevant section
 * @shndx: section index of the section
 * @index: return the symbol's section index to buff_return
*/
int symbol_section_index(Elf64_Half shndx, char* index)
{
    char* section_index;
    section_index = malloc(sizeof(shndx));
    if (section_index == NULL) {
        printf("Failure of allocating memory.\n");
        return -1;
    }
    memset(section_index, 0, sizeof(shndx));
    snprintf(section_index, sizeof(shndx), "%d", shndx);

    switch (shndx)
    {
    case SHN_UNDEF:
        strncpy(index, "UNDEF", sizeof("UNDEF") - 1);
        break;
    case SHN_LOPROC:
        strncpy(index, "LOPROC", sizeof("LOPROC") - 1);
        break;
    case SHN_HIPROC:
        strncpy(index, "HIPROC", sizeof("HIPROC") - 1);
        break;
    case SHN_LOOS:
        strncpy(index, "LOOS", sizeof("LOOS") - 1);
        break;
    case SHN_HIOS:
        strncpy(index, "HIOS", sizeof("HIOS") - 1);
        break;
    case SHN_ABS:
        strncpy(index, "ABS", sizeof("ABS") - 1);
        break;
    case SHN_COMMON:
        strncpy(index, "COMMON", sizeof("COMMON") - 1);
        break;
    case SHN_XINDEX:
        strncpy(index, "XINDEX", sizeof("XINDEX") - 1);
        break;
    default:
        strncpy(index, section_index, sizeof(shndx));
        break;
    }

    free(section_index);
    return 0;
}

/**
 * print_symbol_table: print symobl table
 * @fd: file descriptor of elf file
 * @shp: pointer to section header table of elf file
 * @i: index of section header(symbol table)
 * 
 * return value: -1: Failure
 *                0: Success
 */
int print_symbol_table(int fd, Elf64_Shdr* shp, int i)
{
    Elf64_Sym *symp, *symp_save;
    char* strtabp;
    ssize_t bytes_read;
    int offset, num, ret;
    Elf64_Shdr*  shdr_symtabp = shp + i;
    int error_value = 0;
    char buff_type[SYM_BUFF_SIZE];
    char buff_bindings[SYM_BUFF_SIZE];
    char buff_index[SYM_BUFF_SIZE];
    char buff_vis[SYM_BUFF_SIZE];

    lseek(fd, shdr_symtabp->sh_offset, SEEK_SET);
    symp = malloc(shdr_symtabp->sh_size);
    if (symp == NULL)
    {
        printf("Failure of allocating memory.\n");
        return -1;
    }
    symp_save = symp;
    bytes_read = read(fd, symp, shdr_symtabp->sh_size);
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    }
    printf("Symbol table entries:%ld\n", shdr_symtabp->sh_size / sizeof(Elf64_Sym));

    shp += shdr_symtabp->sh_link;
    printf("Section(StringTable) Type = %d, Size = %ld\n", shp->sh_type, shp->sh_size);
    lseek(fd, shp->sh_offset, SEEK_SET);
    strtabp = malloc(shp->sh_size);
    if (strtabp == NULL)
    {
        printf("Failure of allocating memory.\n");
        return -1;
    }
    bytes_read = read(fd, strtabp, shp->sh_size);
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    }

    offset = 0;
    num = 0;
    printf("Num\tValue\t\t\tSize\tType\tBind\tVis\tNdx\tName\n");
    while (offset < shdr_symtabp->sh_size)
    {
        char* p;

        if (find_name_with_offset_in_string_table(strtabp, shp->sh_size, symp->st_name, &p) == -1)
        {
            printf("Can't find name of symbol in string table: %d.\n", symp->st_name);
            error_value = -1;
            goto error_out;
        }
        
        memset(buff_type, 0, SYM_BUFF_SIZE);
        memset(buff_bindings, 0, SYM_BUFF_SIZE);
        memset(buff_vis, 0, SYM_BUFF_SIZE);
        memset(buff_index, 0, SYM_BUFF_SIZE);

        symbol_type(symp->st_info, buff_type);
        symbol_bindings(symp->st_info, buff_bindings);
        symbol_visibility(symp->st_other, buff_vis);
        if (symbol_section_index(symp->st_shndx, buff_index) == -1) {
            return -1;
        }
        printf("%d:\t%016p\t%ld\t%s\t%s\t%s\t%s\t%s\n", num, symp->st_value, symp->st_size, buff_type,
            buff_bindings, buff_vis, buff_index, p);
        /*%016d: st_value contains the value of the symbol.This may be an absolute value or a relocatable address.*/
        /*However, the type of st_value is Elf64_Addr(aka void*), so it can occur a warning.*/
        offset += sizeof(Elf64_Sym);
        symp++;
        num++;
    }
    printf("Symbol table entries-> %d\n", num);

error_out:
    free(symp_save);
    free(strtabp);

    return error_value;
}

int symbol_table(int fd, Elf64_Ehdr* ehp)
{
    char buff[BUFF_SIZE];
    ssize_t bytes_read;
    Elf64_Shdr* shp;
    int i, ret;

    memset(buff, 0, BUFF_SIZE);
    lseek(fd, ehp->e_shoff, SEEK_SET);
    bytes_read = read(fd, buff, ((ehp->e_shentsize) * (ehp->e_shnum)));
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    } 
    shp = (Elf64_Shdr*)buff;
   
   //Linking editing & dynamic linker
   for (i = 0; i < ehp->e_shnum; i++)
    {
        if ((shp + i)->sh_type != SHT_SYMTAB)
            continue;
        
        printf("Linking editing & dynamic linker:\n");

        ret = print_symbol_table(fd, shp, i);
        if (ret < 0)
        {
            exit(1);
        }
    }
    
    //Dynamic linking symbols
    
    shp = (Elf64_Shdr*)buff;
    for (i = 0; i < ehp->e_shnum; i++)
    {
        if ((shp + i)->sh_type != SHT_DYNSYM)
            continue;
        
        printf("\nDynamic linking symbols:\n");
        ret = print_symbol_table(fd, shp, i);
        if (ret < 0)
        {
            exit(1);
        }
    }
}

int find_name_with_offset_in_string_table(char* strp, int len, int offset, char** retstrp)
{
    *retstrp = strp + offset;
    return  0;
}
