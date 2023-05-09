/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhallama <jhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 16:20:07 by jhallama          #+#    #+#             */
/*   Updated: 2019/10/30 13:34:31 by jhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
