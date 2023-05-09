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

int	count_to_direction(char **input, int i, int j, char arg, int dir1, int dir2)
{
	if (dir1 == 0 && dir2 == 0)
		return (0);
	while (1)
	{
		i += dir1;
		j += dir2;
		if (i < 0 || i == max_h || j < 0 || j == max_w)
			return (0);
		if (input[i][j] == arg)
			return (1);
		if (input[i][j] == 'L')
			return (0);
	}
}

int	count_visible(char **input, int h, int w, char arg)
{
	int	ret = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			ret += count_to_direction(input, h, w, arg, i, j);
		}
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
				if (count_visible(input, i, j, '#') == 0)
				{
					*(next + k) = '#';
					changes++;
				}
			}
			else if (input[i][j] == '#')
			{
			       if (count_visible(input, i, j, '#') >= 5)
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
			char	*next = (char *)malloc(sizeof(char) * (max_w + 1) * max_h);
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
