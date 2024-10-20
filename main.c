#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#include "relocation.h"

int main(int argc, char* argv[])
{
	struct stat st;
	int fd;
	char* elfp;

	if (argc != 2) {
		printf("Usage: %s <elf_file>\n", argv[0]);
		return 1;
	}

	if (stat(argv[1], &st) == -1) {
		perror("Cannot stat");
		exit(1);
	}

	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		perror("Cannot open the elf_file");
		exit(1);
	}

	elfp = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (elfp == MAP_FAILED) {
		perror("Cannot mmap");
		exit(1);
	}
	close(fd);

	process_relocation(elfp);

	return 0;
}
