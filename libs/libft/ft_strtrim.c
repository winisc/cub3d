/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:30:25 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/21 17:20:09 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	size_t		i;
	size_t		j;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > i && ft_strchr(set, s1[j - 1]))
		j--;
	len = j - i + 1;
	str = (char *) malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, len);
	return (str);
}
