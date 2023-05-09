/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhallama <jhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 12:54:25 by jhallama          #+#    #+#             */
/*   Updated: 2020/12/09 15:27:38 by jhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		if (s[i] == '\0')
			break ;
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
