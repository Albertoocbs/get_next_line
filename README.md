get_next_line
-------
![image](https://github.com/user-attachments/assets/ec85dab8-bb71-405b-9f51-da7fb633399c)


Status
-------
Finished: 2025-01-19. Grade: 105/100.


Usage
-------
This function is not a stand-alone program, its files must be included and compiled within another project.

Example main.c:

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}

Compilation:

gcc main.c get_next_line.c get_next_line_utils.c

BUFFER_SIZE can be specified at compilation to override the default BUFFER_SIZE:

gcc -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c

Execution:

./a.out [file]

------
Here is a useful guide to understand this project: https://42-cursus.gitbook.io/guide/rank-01/get_next_line
