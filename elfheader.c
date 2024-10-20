#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "elfheader.h"
#include "section.h"

#define BUFF_SIZE 256

void machine_type(Elf64_Half mach)
{
    printf("Machine type: ");
    switch (mach)
    {
    case EM_NONE:
        printf("No machine\n");
        break;
    case EM_M32:
        printf("AT&T WE 32100\n");
        break;
    case EM_SPARC:
        printf("SPARC\n");
        break;
    case EM_386:
        printf("Intel 80386\n");
        break;
    case EM_68K:
        printf("Motorola 68000\n");
        break;
    case EM_88K:
        printf("Motorola 88000\n");
        break;
    case EM_860:
        printf("Intel 80860\n");
        break;
    case EM_MIPS:
        printf("MIPS RS3000\n");
        break;
    case EM_ARM:
        printf("Arm\n");
        break;
    case EM_X64_INTEL:
        printf("Intel Itanium\n");
        break;
    default:
        printf("Unsupported machine type.\n");
        break;
    }
}

int elfheader(int fd, Elf64_Ehdr* ehp)
{
    ssize_t bytes_read;
 //   char buff[BUFF_SIZE];

    memset((char*)ehp, 0, sizeof(Elf64_Ehdr));
    bytes_read = read(fd, (char*)ehp, sizeof(Elf64_Ehdr));
    if (bytes_read == -1)
    {
        printf("Error occur when reading this file.\n");
        return -1;
    }
    
    //File format
//    ehp = (Elf64_Ehdr*)buff;
    if (ehp->e_ident[El_MAG0] != '\x7f' || ehp->e_ident[El_MAG1] != 'E' || ehp->e_ident[El_MAG2] != 'L' 
        || ehp->e_ident[El_MAG3] != 'F')
    {
        printf("It is not an ELF file.\n");
        return -2;
    }
    printf("File format: ELF\n");

    //File class
    printf("File class: ");
    if (ehp->e_ident[El_CLASS] == ELFCLASS32)
    {
        printf("32-bit object\n");
    }
    else if (ehp->e_ident[El_CLASS] == ELFCLASS64)
    {
        printf("64-bit object\n");
    }

    //Data encoding
    printf("Data encoding: ");
    if (ehp->e_ident[El_DATA] == ELFDATA2LSB)
    {
        printf("LSB(little_endian)\n");
    }
    else if (ehp->e_ident[El_DATA] == ELFDATA2MSB)
    {
        printf("MSB(big_endian)\n");
    }

    //Operating System and ABI Identifiers
    printf("Operating System and ABI Identifiers: ");
    switch (ehp->e_ident[El_OSABI])
    {
    case ELFOSABI_SYSV:
        printf("System V ABI\n");
        break;
    case ELFOSABI_HPUX:
        printf("HP-UX operating system\n");
        break;
    case ELFOSABI_STANDALONE:
        printf("Standalone (embedded) application\n");
    default:
        printf("Unsupported system.\n");
        break;
    }

    //Object File Types
    printf("Object File Types: ");
    switch (ehp->e_type)
    {
    case ET_NONE:
        printf("No file type\n");
        break;
    case ET_REL:
        printf("Relocatable object file\n");
        break;
    case ET_EXEC:
        printf("Executable file\n");
        break;
    case ET_DYN:
        printf("Shared object file\n");
        break;
    case ET_CORE:
        printf("Core file\n");
        break;
    case ET_LOOS:
    case ET_HIOS:
        printf("Environment-specific use\n");
        break;

    case ET_LOPROC:
    case ET_HIPROC:
        printf("Processor-specific use\n");
        break;
    default:
        printf("Unsupported file types.\n");
        break;
    }

    //Machine type
    machine_type(ehp->e_machine);

    return 0;
}