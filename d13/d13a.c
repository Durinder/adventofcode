#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#define BUFF_SIZE 1024

char	*reader(const char *input);

int	earliest_mult_by_wait(int target, int *buses, int last_bus)
{
	int	i = 0;
	int	contender;
	int	earliest = target * 2;
	int	wait = target * 2;

	while (i <= last_bus)
	{
		printf("target:%d, buses[i]:%d, last_bus:%d\n", target, buses[i], last_bus);
		contender = buses[i];
		while (contender < target)
		{
			contender += contender;
		}
		if (contender - target < earliest)
		{
			earliest = buses[i];
			wait = contender - target;
		}
		i++;
	}
	if (i > last_bus)
		exit(EXIT_FAILURE);
	return (earliest * wait);
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
		int	target = strtol(input[0], NULL, 10);
		char	**bus_data = ft_strsplit(input[1], ',');
		free(input[0]);
		free(input[1]);
		free(input);
		int	i = 0;
		while (bus_data[i])
			i++;
		int	*bus_list = (int *)malloc(sizeof(int) * i);
		i = 0;
		for (int j = 0; bus_data[j]; j++)
		{
			if (bus_data[j][0] == 'x')
				continue ;
			bus_list[i++] = strtol(bus_data[j], NULL, 10);
			free(bus_data[j]);
		}
		free(bus_data);
		printf("%d\n", earliest_mult_by_wait(target, bus_list, i - 1));
		free(bus_list);
	}
	exit(EXIT_SUCCESS);
}
