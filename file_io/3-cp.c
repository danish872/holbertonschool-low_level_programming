#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void cant_write(char *s);
void cant_read(char *s);

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Description: cp file_from file_to
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char buff[1024];
	int fd1, fd2;
	ssize_t rd, wr;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		cant_read(argv[1]);

	fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd2 == -1)
	{
		close(fd1);
		cant_write(argv[2]);
	}

	while ((rd = read(fd1, buff, 1024)) > 0)
	{
		wr = write(fd2, buff, rd);
		if (wr == -1)
		{
			close(fd1);
			close(fd2);
			cant_write(argv[2]);
		}
	}
	if (rd == -1)
	{
		close(fd1);
		close(fd2);
		cant_read(argv[1]);
	}

	if (close(fd1) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd1);
		exit(100);
	}
	if (close(fd2) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd2);
		exit(100);
	}

	return (0);
}

/**
 * cant_read - prints read error and exits
 * @s: file name
 */
void cant_read(char *s)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", s);
	exit(98);
}

/**
 * cant_write - prints write error and exits
 * @s: file name
 */
void cant_write(char *s)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", s);
	exit(99);
}

