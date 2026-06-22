/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 12:16:23 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/21 17:19:20 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	max_len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	max_len = len_1 + len_2;
	str = (char *)malloc((max_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len_1 + 1);
	ft_strlcat(str, s2, max_len + 1);
	return (str);
}
