#include "main.h"
void cant_write(char *s);
void cant_read(char *s);
/**
 * main - entry point!
 * @s: string to read/writey
 *
 * Description: cp file_from file_to
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *buff[1024];
	int fd1, fd2;
	ssize_t rd, wr;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	if (argv[1] == NULL)
	{
		cant_read(argv[1]);
		exit(98);
	}
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		cant_read(argv[1]);

	fd2 = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd2 == -1)
		cant_write(argv[2]);

	rd = read(fd1, buff, 1024);
	if (rd == -1)
		cant_read(argv[1]);

	wr = write(fd2, buff, rd);
	if (wr == -1)
		cant_write(argv[2]);
	while (rd == 1024)
	{
		rd = read(fd1, buff, 1024);
		if (rd == -1)
			cant_read(argv[1]);
		wr = write(fd2, buff, rd);
		if (wr == 1)
			cant_write(argv[2]);
	}
	if (close(fd1) < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd1);
		exit(100);
	}
	if (close(fd2) < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd2);
		exit(100);
	}
	return (0);
}
/**
 * cant_read - function
 * @s: string to read
 *
 * Description: error function if unable to read
 * Return: 0
 */
void cant_read(char *s)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", s);
	exit(98);
}
/**
 * cant_write - function
 * @s: string to write
 *
 * Description: error func if unable to write
 * Return: 0
 */
void cant_write(char *s)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", s);
	exit(99);
}
