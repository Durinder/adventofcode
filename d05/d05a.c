#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	ssize_t	ret;
	char	*line = NULL;
	size_t	buf = 0;
	FILE	*fp;
	int	i;
	double	row;
	double	col;
	double	highest = 0;

	if (argc != 2)
	{
		printf("filename missing");
		return (0);
	}
	fp = fopen(argv[1], "r");
	while (ret = getline(&line, &buf, fp) != -1)
	{
		if (line[0] == '\n')
			break ;
		i = 0;
		row = 0;
		col = 0;
		while (i < 7)
		{
			if (line[i] == 'B')
				row += pow(2, (6 - i));
			i++;
		}
		while (i < 10)
		{
			if (line[i] == 'R')
				col += pow(2, (9 - i));
			i++;
		}
		if (row * 8 + col > highest)
			highest = row * 8 + col;
	}
	free(line);
	fclose(fp);
	printf("%.f\n", highest);
	return (0);
}
