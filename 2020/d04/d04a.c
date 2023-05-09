#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_pass {
	int		byr;
	int		iyr;
	int		eyr;
	char		*hgt;
	char		*hcl;
	char		*ecl;
	char		*pid;
	char		*cid;
	int		valid;
	struct 	s_pass	*next;
}		t_pass;

int	count_valid(t_pass *cur)
{
	int	count = 0;

	while (cur != NULL)
	{
		if (cur->valid)
			count++;
		cur = cur->next;
	}
	return (count);
}

int	check_validity(t_pass *pass)
{
	if (pass->byr && pass->iyr && pass->eyr && pass->hgt && pass->hcl && pass->ecl && pass->pid)
		return (1);
	return (0);
}

t_pass	*init_pass(char *line)
{
	t_pass	*pass;
	char	*token;

	if (!(pass = (t_pass *)malloc(sizeof(t_pass))))
	{
		perror("malloc");
		exit(0);
	}
	pass->byr = 0;
	pass->iyr = 0;
	pass->eyr = 0;
	pass->hgt = NULL;
	pass->hcl = NULL;
	pass->ecl = NULL;
	pass->pid = NULL;
	pass->cid = NULL;
	token = strtok(line, " ");
	while (token)
	{
		if (strncmp(token, "byr:", 4) == 0)
			pass->byr = atoi(token + 4);
		if (strncmp(token, "iyr:", 4) == 0)
			pass->iyr = atoi(token + 4);
		if (strncmp(token, "eyr:", 4) == 0)
			pass->eyr = atoi(token + 4);
		if (strncmp(token, "hgt:", 4) == 0)
			pass->hgt = token + 4;
		if (strncmp(token, "hcl:", 4) == 0)
			pass->hcl = token + 4;
		if (strncmp(token, "ecl:", 4) == 0)
			pass->ecl = token + 4;
		if (strncmp(token, "pid:", 4) == 0)
			pass->pid = token + 4;
		if (strncmp(token, "cid:", 4) == 0)
			pass->cid = token + 4;
		token = strtok(NULL, " ");
	}
	pass->valid = check_validity(pass);
	pass->next = NULL;
	return (pass);
}

int	main(int argc, char **argv)
{
	ssize_t ret;
	char	*line = NULL;
	size_t	buf = 0;
	FILE	*fp;
	t_pass	*head = NULL;
	t_pass	*cur = NULL;
	char	*tmp1 = NULL;
	char	*tmp2;

	if (argc != 2)
	{
		printf("filename missing");
		exit(0);
	}
	fp = fopen(argv[1], "r");
	while (ret = getline(&line, &buf, fp) != -1)
	{
		if (tmp1)
		{
			tmp1[strlen(tmp1) - 1] = ' ';
			if (!(tmp2 = (char *)malloc(sizeof(char) * (strlen(tmp1) + strlen(line) + 1))))
			{
				perror("malloc");
				exit(0);
			}
			bzero(tmp2, strlen(tmp1) + strlen(line) + 1);
			strncat(tmp2, tmp1, strlen(tmp1));
			free(tmp1);
			strncat(tmp2, line, strlen(line));
			tmp1 = strdup(tmp2);
			free(tmp2);
		}
		else
			tmp1 = strdup(line);
		if (line[0] == '\n')
		{
			if (head == NULL)
			{
				head = init_pass(tmp1);
				cur = head;
			}
			else
			{
				cur->next = init_pass(tmp1);
				cur = cur->next;
			}
			free(tmp1);
			tmp1 = NULL;
		}
	}
	if (head == NULL)
		head = init_pass(tmp1);
	else
		cur->next = init_pass(tmp1);
	free(line);
	fclose(fp);
	free(tmp1);

	int	count;

	count = count_valid(head);
	printf("%d\n", count);
	while (head != NULL)
	{
		cur = head;
		head = head->next;
		free(cur);
	}
	return (0);
}
