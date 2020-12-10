#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

long long	find_culprit(long long *table, int n, size_t stop)
{
	size_t		start = 0;
	size_t		end;
	size_t		max = n - 1;
	long long	sum;

	if (n > stop)
		return(0);
	while (start < max)
	{
		end = start + 1;
		while (end <= max)
		{
			if (table[n] == table[start] + table[end])
				return (find_culprit(table + 1, n, --stop));
			end++;
		}
		start++;
	}
	return (table[n]);
}

void	main(int argc, char **argv)
{
	FILE		*f;
	ssize_t		buf = 0;
	char		*data;
	size_t		len;

	if (argc != 3)
	{
		perror("filename, preamble length");
		exit(EXIT_FAILURE);
	}
	f = fopen(argv[1], "r");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		len = ftell(f);
		rewind(f);
		data = (char *)malloc(sizeof(char) * len + 1);
		if (data)
		{
			fread(data, 1, len, f);
			data[len] = '\0';
		}
		fclose(f);
	}
	if (data)
	{
		char		**array = ft_strsplit(data, '\n');
		size_t	i = 0;

		free(data);
		while (array[i])
			i++;
		long long	*table = (long long *)malloc(sizeof(long long) *i);
		i = 0;
		while (table && array[i])
		{
			table[i] = atoll(array[i]);
			free(array[i++]);
		}
		free(array);
		printf("%lld\n", find_culprit(table, atoi(argv[2]), --i));
		free(table);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
