/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:49:22 by tclaereb          #+#    #+#             */
/*   Updated: 2023/10/30 13:04:51 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*new_s;

	len = ft_strlen(s) + 1;
	new_s = ((char *)ft_calloc(len, sizeof(char)));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s, len);
	return (new_s);
}
