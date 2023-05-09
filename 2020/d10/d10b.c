#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*reader(const char *input);

unsigned long	count_valid_combinations(char **array, int elems)
{
	char	branches[elems + 2];
	int	i0 = 0;
	int	i1 = (elems >= 1) ? atoi(array[0]) : 0;
	int	i2 = (elems >= 2) ? atoi(array[1]) : 0;
	int	i3 = (elems >= 3) ? atoi(array[2]) : 0;
	int	j = 0;
	int	split;
	unsigned long	amount[elems + 1];

	branches[elems + 1] = '\0';
	while (elems + 1)
	{
		split = 0;
		if (i1 && i1 - i0 < 4)
		{
			split++;
			if (i2 && i2 - i0 < 4)
			{
				split++;
				if (i3 && i3 - i0 < 4)
					split++;
			}
		}
		amount[j] = 0;
		branches[j++] = split + 48;
		if (i0)
			array++;
		elems--;
		i0 = i1;
		i1 = i2;
		i2 = i3;
		i3 = (elems > 2) ? atoi(array[3]) : i3 + 3;
		i3 = (elems < 2) ? 0 : i3;
	}
	j = 0;
	amount[j] = 1;
	while (branches[j])
	{
		if (branches[j] == '3')
		{
			amount[j + 2] += amount[j];
			amount[j + 3] += amount[j];
		}
		else if (branches[j] == '2')
			amount[j + 2] += amount[j];
		amount[j + 1] += amount[j];
		j++;
	}
	return (amount[--j]);
}

int	count_chain(char **array)
{
	int	i = 0;
	int	dif1 = (array[0][0] == '1') ? 1 : 0;
	int	dif3 = 1;

	while (array[i + 1])
	{
		if (atoi(array[i]) - atoi(array[i + 1]) == -1)
			dif1++;
		else if (atoi(array[i]) - atoi(array[i + 1]) == -3)
			dif3++;
		i++;
	}
	printf("dif1:%d dif3:%d\n", dif1, dif3);
	return (dif1 * dif3);
}

int	compare(const void *p1, const void *p2)
{
	return (atoi(*(const char **)p1) - atoi(*(const char **)p2));
}

void	main(int argc, char **argv)
{
	char	*data = reader(argv[1]);
	if (data)
	{
		char	**array = ft_strsplit(data, '\n');
		int	i = 0;
		while (array[i])
			i++;
		qsort(array, i, sizeof(char *), compare);
		printf("%d\n", count_chain(array));
		printf("%ld\n", count_valid_combinations(array, i));
		i = 0;
		while (array[i])
			free(array[i++]);
		free(array);
		free(data);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
