#include <err.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <sys/stat.h>

int main(void) {
        for (;;) {
		char func_name[4096];
                int value;

		printf("enter func_name and value: ");
		scanf("%s %d", func_name, &value);

                int fd = open(func_name, O_RDWR);
                if (fd < 0) {
                        printf("failed to open %s.\n", func_name);
                        continue;
                }

                struct stat stat_buf;
                fstat(fd, &stat_buf);

                size_t size = stat_buf.st_size;

                void *p = mmap(NULL, size, PROT_EXEC | PROT_READ, MAP_PRIVATE, fd, 0);

                if (MAP_FAILED == p)
                        err(1, "mmap");

                int (*function)(int) = p;
                int result = function(value);

                printf("%d = %s(%d)\n", result, func_name, value);
                munmap(function, size);
                close(fd);
        }
}