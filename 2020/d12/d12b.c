#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct	position {
	int	pos[2]; // as X, Y coordinates
	int	waypoint[2]; // E/W == +X/-X, N/S == +Y/-Y
};

void	turn(int *wp, int units)
{
	if (units % 90 != 0)
	{
		perror("revise code");
		exit(EXIT_FAILURE);
	}
	units /= 90;
	if (units > 3)
	{
		perror("revise code");
		exit(EXIT_FAILURE);
	}
	if (units < 0) // change all L rotations to R for simplicity as
		units += 4; // 3 to L results in the same as 1 to R, 2 L == 2 R and 1 L == 3 R
	int	tmp;
	while (units) // as rot to right N -> E -> S -> W -> N
	{		// same as +Y -> +X -> -Y -> -X -> +Y
		tmp = wp[0];
		wp[0] = wp[1]; // +Y/-Y -> +X/-X
		wp[1] = tmp * -1; // +X/-X -> -Y/+X
		units--;
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
				head.pos[0] += head.waypoint[0] * units;
				head.pos[1] += head.waypoint[1] * units;
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
				turn(head.waypoint, units * -1);
				break ;
			case ('R'):
				turn(head.waypoint, units);
		}
	}
	fclose(f);
	free(line);
	printf("current position:%d,%d, Manhattan distance:%d\n", head.pos[0], head.pos[1], abs(head.pos[0]) + abs(head.pos[1]));
	exit(EXIT_SUCCESS);
}
