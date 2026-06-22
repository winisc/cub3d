/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:30 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/22 23:54:59 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t		m_size;
	void		*ptr;

	if (!nmemb || !size)
		return ((void *) ft_strdup(""));
	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	m_size = nmemb * size;
	ptr = (char *)malloc(m_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, m_size);
	return (ptr);
}
