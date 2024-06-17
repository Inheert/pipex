/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:10:19 by tclaereb          #+#    #+#             */
/*   Updated: 2024/06/17 19:03:07 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_strings(char const *s, char c)
{
	unsigned int	count;
	int				is_inside;

	count = 0;
	is_inside = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_inside)
			{
				count++;
				is_inside = 1;
			}
		}
		else
			is_inside = 0;
		s++;
	}
	return (count);
}

static char	*apply_string(const char *s, char c)
{
	char	*str;
	int		len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (len == 0)
		return (NULL);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}

static int	fill_result(char **result, char const *s, char c)
{
	int		i;
	int		is_inside;

	i = 0;
	is_inside = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_inside)
			{
				result[i++] = apply_string(s, c);
				if (!result[i - 1])
					return (0);
			}
			is_inside = 1;
		}
		else
			is_inside = 0;
		s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;
	char			**result;

	if (!s)
		return (NULL);
	count = count_strings(s, c);
	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, s, c))
	{
		i = 0;
		while (result[i])
			free(result[i++]);
		free(result);
		return (NULL);
	}
	result[count] = NULL;
	return (result);
}
