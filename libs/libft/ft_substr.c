/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:52:22 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/23 00:43:45 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			max_len;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	max_len = ft_strlen(s) - start;
	if (len < max_len)
		max_len = len;
	str = (char *) malloc((max_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, max_len + 1);
	return (str);
}
