#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	count_group(char *group, int i)
{
	int	ret = 0;
	int	c = 'a';

	while (c <= 'z')
	{
		if (memchr(group, c, i))
			ret++;
		c++;
	}
	return (ret);
}

int	main(int argc, char **argv)
{
	char	*data;
	long	len;
	FILE	*f;
	       
	if (argc != 2)
		exit(0);
	f = fopen(argv[1], "r");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		len =  ftell(f);
		rewind(f);
		data = (char *)malloc(len + 1);
		data[len] = '\0';
		if (data)
			fread(data, 1, len, f);
		fclose(f);
	}
	if (data)
	{
		int	ans = 0;
		char	*p = data;
		long	i = 0;

		while (*data)
		{
			if (data[i] == '\0')
				break ;
			if (data[i] == '\n' && data[i + 1] == '\n')
			{
				ans += count_group(data, i);
				data += i;
				i = 0;
			}
			i++;
		}
		free(p);
		printf("%d\n", ans);
	}
	return (0);
}
