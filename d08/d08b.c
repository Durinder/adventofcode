#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	**ft_strsplit(char const *s, char c);

int	execute_input(char **input, int *acc)
{
	int	debug = 1;
	int	i = 0;
	while (input[i])
		i++;
	int	visited[i];
	memset(visited, 0, sizeof(int) * i);
	i = 0;
	while(input[i])
	{
		if (visited[i] != 0)
			return(0);
		else
			(visited[i] = debug);
		if (*input[i] == 'a')
		{
			*acc += atoi(input[i] + 4);
			i++;
		}
		else if (*input[i] == 'n')
			i++;
		else if (*input[i] == 'j')
			i += atoi(input[i] + 4);
		else
		{
			perror("fatal error");
			exit(EXIT_FAILURE);
		}
		debug++;
	}
	return(1);
}

void	main(int argc, char **argv)
{
	FILE	*f;
	long	len;
	char	*data;

	if (argc != 2)
	{
		perror("filename");
		exit(EXIT_FAILURE);
	}
	f = fopen(argv[1], "r");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		len = ftell(f);
		rewind(f);
		if (!(data = (char *)malloc(sizeof(char) * (len + 1))))
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		fread(data, 1, len, f);
		data[len] = '\0';
		fclose(f);
	}
	if (data)
	{
		char	**input;
		int	ret = 0;
		int	i = 0;

		input = ft_strsplit(data, '\n');
		free(data);
		if (execute_input(input, &ret) == 0)
			printf("inf loop, acc value:%d\n", ret);
		else
		{
			printf("program terminated, acc value:%d\n", ret);
			while (input[i])
				free(input[i++]);
			free(input);
			exit(EXIT_SUCCESS);
		}
		while (input[i])
			i++;
		int	lines[i];
		i = 0;
		while (input[i])
		{
			if (strncmp(input[i], "jmp", 3) == 0)
				lines[i] = 1;
			else if (strncmp(input[i], "nop", 3) == 0)
				lines[i] = 2;
			else
				lines[i] = 0;
			i++;
		}
		int	max = i;
		i = 0;
		while (i < max)
		{
			ret = 0;
			if (lines[i] == 1)
			{
				memcpy(input[i], "nop", 3);
				if (execute_input(input, &ret))
					break ;
				memcpy(input[i], "jmp", 3);
			}
			if (lines[i] == 2)
			{
				memcpy(input[i], "jmp", 3);
				if (execute_input(input, &ret))
					break ;
				memcpy(input[i], "nop", 3);
			}
			i++;
		}
		if (i < max)
			printf("program halted by fixing line %i, acc is:%d\n", i, ret);
		else
			printf("all hope is lost.\n");
		i = 0;
		while (input[i])
			free(input[i++]);
		free(input);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
