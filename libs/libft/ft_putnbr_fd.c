/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:45:25 by wsilveir          #+#    #+#             */
/*   Updated: 2025/08/10 05:29:49 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	last_d;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	last_d = num % 10 + '0';
	num = num / 10;
	if (num != 0)
		ft_putnbr_fd (num, fd);
	write (fd, &last_d, 1);
}
