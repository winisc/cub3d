/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsilveir <wsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:35:51 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/21 17:19:58 by wsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (i < len && big[i])
	{
		if (little[0] == big[i])
		{
			j = 1;
			while ((little[j] == big[i + j]) && little[j] && (i + j) < len)
				j++;
			if (little[j] == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
