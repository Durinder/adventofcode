#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*reader(const char *input);

unsigned long long	valid_timestamp(unsigned long long *bus, int elems)
{
	unsigned long long	candidate;
	int			i = 0;
	unsigned long long	mult;

	while (bus[i] == 0)
		i++;
	candidate = bus[i];
	mult = bus[i];
	i++;
	while (i < elems)
	{
		while (bus[i] == 0)
			i++;
		if ((candidate + i) % bus[i] == 0)
		{
			mult *= bus[i];
			i++;
			continue ;
		}
		candidate += mult;
	}
	return (candidate);
}

void	main(int argc, char **argv)
{
	if (argc!= 2)
		perror("usage");
	char	*data = reader(argv[1]);
	if (data)
	{
		char	**input = ft_strsplit(data, '\n');
		free(data);
		char	**bus_data = ft_strsplit(input[1], ',');
		free(input[0]);
		free(input[1]);
		free(input);
		int	i = 0;
		while (bus_data[i])
			i++;
		unsigned long long	*bus_list = (unsigned long long *)malloc(sizeof(unsigned long long) * i);
		i = 0;
		for (int j = 0; bus_data[j]; j++)
		{
			bus_list[i++] = strtoll(bus_data[j], NULL, 10);
			free(bus_data[j]);
		}
		free(bus_data);
		printf("%lld\n", valid_timestamp(bus_list, i));
		free(bus_list);
	}
	exit(EXIT_SUCCESS);
}
