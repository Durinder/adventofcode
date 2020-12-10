#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "libft.h"

long long	find_weakness(long long *table, long long culprit, size_t stop)
{
	size_t		i = 0;
	long long	smallest = LLONG_MAX;
	long long	largest = LLONG_MIN;
	long long	sum = 0;

	while (stop)
	{
		sum += table[i];
		smallest = (table[i] < smallest) ? table[i] : smallest;
		largest = (table[i] > largest) ? table[i] : largest;
		if (sum == culprit)
			return (smallest + largest);
		else if (sum > culprit)
			return (find_weakness(table + 1, culprit, --stop));
		else
			i++;
	}
	return (0);
}

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
		long long	culprit;

		printf("%lld\n", culprit = find_culprit(table, atoi(argv[2]), --i));
		printf("%lld\n", find_weakness(table, culprit, ++i));
		free(table);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
