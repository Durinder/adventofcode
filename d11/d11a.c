#include <stdio.h>
#include "libft.h"
#define BUFF_SIZE 256

int	max_h = 0;
int	max_w = 0;

char	*reader(const char *input);

void	free_map_data(char ***states)
{
	int	i = 0;
	int	j;

	while (states[i])
	{
		j = 0;
		while (states[i][j])
			free(states[i][j++]);
		free(states[i++]);
	}
	free(states);
}

int	count_occupied_seats(char **stabilized)
{
	int	ret = 0;
	int	i = 0;
	int	j;

	while (i < max_h)
	{
		j = 0;
		while (j <= max_w)
		{
			if (stabilized[i][j] == '#')
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
}

int	count_adjacent(char **input, int h, int w, char arg)
{
	char	area[3][3];
	int	ret = 0;

	area[0][0] = (h && w)			? input[h-1][w-1] : '\0';
	area[0][1] = (h)			? input[h-1][w] : '\0';
	area[0][2] = (h && w < max_w)		? input[h-1][w+1]: '\0';
	area[1][0] = (w)			? input[h][w-1] : '\0';
	area[1][1] = 				input[h][w];
	area[1][2] = (w < max_w)		? input[h][w+1] : '\0';
	area[2][0] = (h+1 < max_h && w)		? input[h+1][w-1] : '\0';
	area[2][1] = (h+1 < max_h)		? input[h+1][w]: '\0';
	area[2][2] = (h+1 < max_h && w < max_w)	? input[h+1][w+1] : '\0';
	
	int	i = 0;
	int	j;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i == 1 && j == 1)
				j++;
			if (area[i][j] == arg)
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
}

int	stabilizer(char **input, char *next)
{
	int	i = 0;
	int	j;
	int	k = 0;
	int	changes = 0;

	while (i < max_h)
	{
		j = 0;
		while (j < max_w)
		{
			if (input[i][j] == 'L')
			{
				if (count_adjacent(input, i, j, '#') == 0)
				{
					*(next + k) = '#';
					changes++;
				}
			}
			else if (input[i][j] == '#')
			{
			       if (count_adjacent(input, i, j, '#') >= 4)
			       {
					*(next + k) = 'L';
					changes++;
			       }
			}
			else
				*(next + k) = input[i][j];
			k++;
			j++;
		}
		*(next + k) = '\n';
		k++;
		i++;
	}
	k--;
	*(next + k) = '\0';
	if (changes != 0)
		return (1);
	return (0);
}

void	main(int argc, char **argv)
{
	char	*data = reader(argv[1]);
	if (data)
	{
		char	**array = ft_strsplit(data, '\n');
		max_w = strlen(array[0]);
		while (array[max_h])
			max_h++;
		char	***states = (char ***)malloc(sizeof(char **) * BUFF_SIZE);
		if (states)
		{
			states[0] = array;
			char	*next = (char *)malloc((sizeof(char) * (max_w + 1) * max_h + 1));
			if (next)
			{
				int	ret = 0;
				char	*tmp;
				while (stabilizer(states[ret], next) == 1)
				{
					ret++;
					if (ret + 1 >= BUFF_SIZE)
					{
						perror("BUFF_SIZE exceeded");
						exit(EXIT_FAILURE);
					}
					tmp = strdup(next);
					states[ret] = ft_strsplit(tmp, '\n');
					free(tmp);
				}
				printf("occupied seats:%d\n", count_occupied_seats(states[ret]));
				free(next);
				states[ret+1] = NULL;
			}
			free_map_data(states);
		}
		free(data);
	}
}
