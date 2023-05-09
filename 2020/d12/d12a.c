#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct	position {
	int	dir[4]; // 0 == N, 1 == E, 2 == S, 3 == W
	int	cur; // tracks, what index *facing is pointing on dir[], starts at east so 1
	int	*facing;
	int	deg;
};

void	turn(struct position *head, int units)
{
	if (units % 90 != 0)
	{
		perror("revise code");
		exit(EXIT_FAILURE);
	}
	int	tmp = head->cur;

	head->cur += units / 90;
	while (head->cur < 0)
		head->cur += 4;
	while (head->cur > 3)
		head->cur -= 4;
	head->facing += head->cur - tmp;
}

void	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage\n");
		exit(EXIT_FAILURE);
	}
	FILE	*f = fopen(argv[1], "r");
	if (!f)
		exit(EXIT_FAILURE);

	int		units;
	struct position	head;

	head.cur = 1;
	for (int i = 0; i <4; i++)
		head.dir[i] = 0;
	head.facing = &head.dir[1];

	char	*line = (char *)malloc(sizeof(char) * 6);
	if (!line)
		exit(EXIT_FAILURE);
	while (fgets(line, 6, f))
	{
		units = strtol(line + 1, NULL, 10);
		switch (line[0])
		{
			case ('F'):
				*head.facing += units;
				break ;
			case ('N'):
				head.dir[0] += units;
				break ;
			case ('E'):
				head.dir[1] += units;
				break ;
			case ('S'):
				head.dir[2] += units;
				break ;
			case ('W'):
				head.dir[3] += units;
				break ;
			case ('L'):
			       turn(&head, units * -1);
				       break ;
			case ('R'):
			       turn(&head, units);
		}
	}
	fclose(f);
	free(line);
	int	manhattan[2];
	manhattan[0] = abs(head.dir[1] - head.dir[3]);
	manhattan[1] = abs(head.dir[0] - head.dir[2]);
	printf("current position is:%d + %d = %d\n", manhattan[0], manhattan[1], manhattan[0] + manhattan[1]);
	exit(EXIT_SUCCESS);
}
