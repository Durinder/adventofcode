#include <stdio.h>
#include <inttypes.h>
#include "libft.h"

void	bit_twiddling(char mask[], uint64_t *value)
{
	for (int i = 35; i >= 0; i--)
	{
		if (mask[i] == '1')
			*value |= 1UL << 35 - i;
		if (mask[i] == '0')
			*value &= ~(1UL << 35 - i); 
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(EXIT_FAILURE);
	char	*data = reader(argv[1]);
	char	**input = ft_strsplit(data, '\n');
	free(data);

	char		mask[36];
	uint64_t	mem[65535];
	char		*p;
	int		slot;
	int		max_slot = 0;

	for (int i = 0; i < 65535; i++)
		mem[i] = 0;
	for (int i = 0; input[i]; i++)
	{
		if (strstr(input[i], "mask"))
			strncpy(mask, input[i] + 7, 36);
		else
		{
			slot = strtol(input[i] + 4, &p, 10);
			if (slot > max_slot)
				max_slot = slot;
			mem[slot] = strtoul(p + 4, NULL, 10);
			bit_twiddling(mask, &mem[slot]);
		}
		free(input[i]);
	}
	free(input);
	uint64_t	ret = 0;
	
	for (int i = 0; i <= max_slot; i++)
	{
		ret += mem[i];
	}
	printf("%lu\n", ret);
	return (0);
}
