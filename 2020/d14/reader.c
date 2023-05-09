#include <stdio.h>
#include <stdlib.h>

char	*reader(const char *input)
{
	FILE	*f;
	ssize_t	buf = 0;
	char	*data;
	size_t	len;

	if (input)
	{
		f = fopen(input, "r");
		if (f)
		{
			fseek(f, 0, SEEK_END);
			len = ftell(f);
			rewind(f);
			data = (char *)malloc(sizeof(char) * len + 1);
			if (data)
			{
				fread(data, 1, len, f);
				data[len] = '\0';
			}
			fclose(f);
			return (data);
		}
	}
	return (NULL);
}
