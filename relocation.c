#include "header.h"
#include "relocation.h"
#include "symbol.h"

static void print_instruction_applied_relocation(char *instructionp)
{
	//call -> 0xe8 xx xx xx xx
	//jmp -> 0xeb xx
	if (*instructionp == 0xe8) {
		printf("CALL applied: 0xe8 0x%2.2x 0x%2.2x 0x%2.2x 0x%2.2x\n", instructionp[1],
			instructionp[2], instructionp[3], instructionp[4]);
	}
	else if (*instructionp == 0xeb) {
		printf("JMP applied: 0xeb 0x%2.2x\n", instructionp[1]);
	}
}

static void process_rela(char* elfp, Elf64_Off off)
{
	Elf64_Ehdr* ehdrp = (Elf64_Ehdr*)elfp;
	Elf64_Shdr* reloshdrp = (Elf64_Shdr*)(elfp + off);
	Elf64_Shdr* symtabshdrp = (Elf64_Shdr*)(elfp + SECTION_TABEL_ENTRY_OFFSET(ehdrp, reloshdrp->sh_link));
	Elf64_Shdr* appliedrelashdrp = (Elf64_Shdr*)(elfp + SECTION_TABEL_ENTRY_OFFSET(ehdrp, reloshdrp->sh_info));;
	int i;
	Elf64_Sym* symentryp;
	Elf64_Rela* relaentryp = (Elf64_Rela*)(elfp + reloshdrp->sh_offset);
	char* appliedrelap = elfp + appliedrelashdrp->sh_offset;

	for (i = 0; i < reloshdrp->sh_size / reloshdrp->sh_entsize; i++) {
		//r_offset This member gives the location at which to apply the relocation action. For a relocatable
		//			file, the value is the byte offset from the beginning of the section to the storage unit affected
		//			by the relocation. For an executable file or a shared object, the value is the virtual address of
		//			the storage unit affected by the relocation
		print_instruction_applied_relocation(appliedrelap + (int)((relaentryp + i)->r_offset));
		//print_symbol_name
		//print_addend
	}
}

void process_relocation(char* elfp)
{
	Elf64_Ehdr* ehdrp = (Elf64_Ehdr*)elfp;
	int ridx = 0;

	while (1) {
		ridx = find_section_header_index(elfp, ehdrp, SHT_RELA, ridx);
		if (ridx == -1)
			break;
		process_rela(elfp, SECTION_TABEL_ENTRY_OFFSET(ehdrp, ridx));
	}

	while (1) {
		ridx = find_section_header_index(elfp, ehdrp, SHT_REL, ridx);
		if (ridx == -1)
			break;
	}
}