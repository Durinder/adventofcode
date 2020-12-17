#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct	position {
	int	pos[2]; // as X, Y coordinates
	int	waypoint[2]; // as X, Y coordinates
};

void	turn(struct position *head, int units)
{
	if (units % 90 != 0)
	{
		perror("revise code");
		exit(EXIT_FAILURE);
	}
	int	tmp;

	units /= 90;
	while (units)
	{
		tmp = head->waypoint[0];
		head->waypoint[1] = 0 - head->waypoint[0];
		head->waypoint[0] = tmp;
		units += (units > 0) ? -1 : 1;
	}
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

	head.waypoint[0] = 10;
	head.waypoint[1] = 1;
	head.pos[0] = 0;
	head.pos[1] = 0;

	char	*line = (char *)malloc(sizeof(char) * 6);
	if (!line)
		exit(EXIT_FAILURE);
	while (fgets(line, 6, f))
	{
		units = strtol(line + 1, NULL, 10);
		switch (line[0])
		{
			case ('F'):
				head.pos[0] += head.pos[0] > 0 ? units * head.waypoint[0] : -1 * (units * head.waypoint[0]);
				head.pos[1] += head.pos[1] > 0 ? units * head.waypoint[1] : -1 * (units * head.waypoint[1]);
				break ;
			case ('N'):
				head.waypoint[1] += units;
				break ;
			case ('E'):
				head.waypoint[0] += units;
				break ;
			case ('S'):
				head.waypoint[1] -= units;
				break ;
			case ('W'):
				head.waypoint[0] -= units;
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
	printf("current position is:%d + %d = %d\n", abs(head.pos[0]), abs(head.pos[1]), abs(head.pos[0]) + abs(head.pos[1]));
	exit(EXIT_SUCCESS);
}
