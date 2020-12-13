#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*reader(const char *input);

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
		i = 0;
		while (array[i])
			free(array[i++]);
		free(array);
		free(data);
	}
	exit(EXIT_FAILURE);
}
