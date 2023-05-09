#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct	s_child {
	int	n;
	char	*name;
}		t_child;


typedef struct	s_bag {
	char	*name;
	int	amount;
	int	visited;
	t_child	**children;
}		t_bag;

void	free_all(t_bag **bags, int j)
{
	int	i = 0;

	while (i < j)
	{
		while(bags[i]->amount)
		{
			bags[i]->amount--;
			free(bags[i]->children[bags[i]->amount]->name);
			free(bags[i]->children[bags[i]->amount]);
		}
		free(bags[i]->children);
		free(bags[i]->name);
		free(bags[i]);
		i++;
	}
}

int	count_children(char *s, t_bag **bags)
{
	int	i = 0;

	while (strcmp(s, bags[i]->name) != 0)
		i++;
	if (bags[i]->amount == 0)
		return (1);
	int	ret = 1;
	int	j = 0;
	while (j < bags[i]->amount)
	{
		ret += count_children(bags[i]->children[j]->name, bags) * bags[i]->children[j]->n;
		j++;
	}
	return (ret);
}

int	count_parents(char *s, t_bag **bag, int total)
{
	int	i = 0;
	int	j;
	int	ret = 0;

	while (i < total)
	{
		j = 0;
		while (j < bag[i]->amount)
		{
			if (strcmp(s, bag[i]->children[j]->name) == 0 && bag[i]->visited == 0)
			{
				bag[i]->visited = 1;
				ret++;
				ret += count_parents(bag[i]->name, bag, total);
			}
			j++;
		}
		i++;
	}
	return (ret);
}

char	*ft_strnew(size_t size)
{
	char	*s;

	s = (char *)malloc(size + 1);
	if (s == NULL)
		return (NULL);
	while (size + 1 > 0)
	{
		s[size] = '\0';
		size--;
	}
	return (s);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (s)
	{
		substring = (char *)malloc(len + 1);
		if (substring == NULL)
			return (NULL);
		i = 0;
		while (i < len)
		{
			substring[i] = s[start + i];
			i++;
		}
		substring[i] = '\0';
		return (substring);
	}
	return (NULL);
}

static size_t	check_double_delimiter(char const *s, size_t i, char c)
{
	if (s[i] == c)
		i++;
	return (i);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			counter++;
			while (s[i] == c)
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (counter + 1);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new_array;
	size_t	i;
	size_t	delimiter;
	size_t	start;

	if (s)
	{
		delimiter = count_words(s, c);
		if (!(new_array = (char **)malloc(sizeof(char *) * (delimiter + 1))))
			return (NULL);
		i = 0;
		delimiter = 0;
		while (s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (i - start > 0)
				new_array[delimiter++] = ft_strsub(s, start, i - start);
			i = check_double_delimiter(s, i, c);
		}
		new_array[delimiter] = NULL;
		return (new_array);
	}
	return (NULL);
}

t_child	*init_child(char *s)
{
	t_child	*child;

	if (!(child = (t_child *)malloc(sizeof(t_child))))
	{
		perror("malloc");
		exit(0);
	}
	child->n = atoi(s);
	child->name = ft_strsub(s, 2, strstr(s, " bag") - s - 2);
	return (child);
}

t_child	*empty()
{
	t_child	*child;

	if (!(child = (t_child *)malloc(sizeof(t_child))))
	{
		perror("malloc");
		exit(0);
	}
	child->n = 0;
	child->name = strdup("");
	return(child);
}

t_child	**init_children(char *s, int *amount)
{
	int	i = 0;

	while (s[i])
	{
		if (isdigit(s[i]))
			(*amount)++;
		i++;
	}
	if (*amount == 0)
		return (NULL);
	t_child	**children;

	if (!(children = (t_child **)malloc(sizeof(t_child *) * *amount)))
	{
		perror("malloc");
		exit(0);
	}
	*amount = 0;
	i = 0;
	while (s[i])
	{
		if (isdigit(s[i]))
		{
			children[(*amount)++] = init_child(&s[i]);
		}
		i++;
	}
	return (children);
}

t_bag	*map_bags(char *s)
{
	t_bag	*bag;
	int	i = 0;

	if (!(bag = (t_bag *)malloc(sizeof(t_bag))))
	{
		perror("malloc");
		exit(0);
	}
	bag->name = ft_strsub(s, 0, strstr(s, " bags") - s);
	bag->visited = 0;
	bag->children = init_children(&s[i], &i);
	bag->amount = i;
	return (bag);
}

void	main(int argc, char **argv)
{
	FILE	*f;
	long	len;
	char	*data;


	if (argc != 4)
	{
		perror("./a.out input amount '[color]'");
		exit(0);
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
			exit(0);
		}
		if (data)
			fread(data, 1, len, f);
		data[len] = '\0';
		fclose(f);
	}
	if (data)
	{
		char	**array;
		t_bag	**bags;
		int	i = 0;

		array = ft_strsplit(data, '\n');
		while(array[i])
		{
			i++;
		}
		if (!(bags = (t_bag **)malloc(sizeof(t_bag *) * i)))
		{
			perror("malloc");
			exit(0);
		}
		i = 0;
		while (array[i])
		{
			bags[i] = map_bags(array[i]);
			free(array[i++]);
		}
		free(array);
		printf("%d\n", count_parents(argv[3], bags, i));
		printf("%d\n", count_children(argv[3], bags) - 1);
		free_all(bags, i);
		free(bags);
		free(data);
	}
}
