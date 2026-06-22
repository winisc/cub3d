/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:43:59 by wsilveir          #+#    #+#             */
/*   Updated: 2025/08/10 05:17:16 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	length(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		is_neg;
	int		len;
	long	num;
	char	*str;

	num = n;
	len = length(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	is_neg = (num < 0);
	if (is_neg)
		num = -num;
	while (len > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (is_neg)
		str[0] = '-';
	return (str);
}
