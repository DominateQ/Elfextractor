#include "header.h"

/**
 * find_section_header_index - find the index of section header with type @type from @sidx
 *  @elfp: pointer to the beginning of ELF file
 *  @ehdrp: pointer to elf header
 *  @type: which section to find
 *  @sidx: start index
 * return: the index found when less than 0; -1 when failure
 */
int find_section_header_index(char* elfp, Elf64_Ehdr* ehdrp, Elf64_Word type, int sidx)
{
	int i = -1;
	Elf64_Shdr* shdrp = (Elf64_Shdr*)SECTION_TABLE(elfp, ehdrp);

	for (i = sidx; i < ehdrp->e_shnum; i++) {
		if ((shdrp + i)->sh_type == type)
			break ;
	}

	return i;
}