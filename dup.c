#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open a file
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Duplicate the file descriptor
    int fd_dup = dup2(fd, 3);
    if (fd_dup < 0) {
        perror("dup");
        return 1;
    }

    // Write to the original file descriptor
    write(fd, "Hello from fd\n", 14);

    // Write to the duplicated file descriptor
    write(fd_dup, "Hello from fd_dup\n", 18);

    // Close file descriptors
    close(fd);
    close(fd_dup);
	// printf("%d");`
    return 0;
}
