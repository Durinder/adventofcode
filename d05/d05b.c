#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	ssize_t	ret;
	char	*line = NULL;
	size_t	buf = 0;
	FILE	*fp;
	int	i;
	double	row;
	double	col;
	char	id_list[128 * 8 + 1];

	if (argc != 2)
	{
		printf("filename missing");
		return (0);
	}
	memset(id_list, '0', 128 * 8 + 1);
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
		id_list[(int)row * 8 + (int)col] = '1';
	}
	free(line);
	fclose(fp);
	i = -1;
	while (id_list[++i] == '0');
	while (id_list[i] == '1')
		i++;
	printf("%d\n", i);
	return (0);
}
