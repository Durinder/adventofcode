#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
	if (!(pass->byr && pass->iyr && pass->eyr && pass->hgt && pass->hcl && pass->ecl && pass->pid))
		return (0);
	if (!(pass->byr >= 1920 && pass->byr <= 2002))
		return (0);
	if (!(pass->iyr >= 2010 && pass->iyr <= 2020))
		return (0);
	if (!(pass->eyr >= 2020 && pass->eyr <= 2030))
		return (0);
	if (isdigit(pass->hgt[0] == 0))
		return (0);
	if (atoi(pass->hgt) >= 150 && atoi(pass->hgt) <= 193)
	{
		if (strstr(pass->hgt, "cm") == NULL)
			return (0);
	}
	else if (atoi(pass->hgt) >= 59 && atoi(pass->hgt) <= 76)
	{
		if (strstr(pass->hgt, "in") == NULL)
			return (0);
	}
	else
		return (0);
	if (!(pass->hcl[0] == '#'))
		return(0);
	int	i = 1;
	
	while (i <= 6)
	{
		if (!(isdigit(pass->hcl[i]) || (pass->hcl[i] >= 'a' && pass->hcl[i] <= 'f')))
			return (0);
		i++;
	}
	i = 0;
	if (strcmp(pass->ecl, "amb") == 0)
		i++;
	if (strcmp(pass->ecl, "blu") == 0)
		i++;
	if (strcmp(pass->ecl, "brn") == 0)
		i++;
	if (strcmp(pass->ecl, "gry") == 0)
		i++;
	if (strcmp(pass->ecl, "grn") == 0)
		i++;
	if (strcmp(pass->ecl, "hzl") == 0)
		i++;
	if (strcmp(pass->ecl, "oth") == 0)
		i++;
	if (i != 1)
		return (0);
	if (strlen(pass->pid) != 9)
		return (0);
	return (1);
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
	if (tmp1 && head == NULL)
	{
		head = init_pass(tmp1);
		free(tmp1);
	}
	else if (tmp1)
	{
		cur->next = init_pass(tmp1);
		free(tmp1);
	}
	free(line);
	fclose(fp);

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
