/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:57:47 by wsilveir          #+#    #+#             */
/*   Updated: 2025/07/23 23:47:07 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*n_node;

	while (*lst)
	{
		n_node = (*lst)->next;
		ft_lstdelone((*lst), (*del));
		*lst = n_node;
	}
	*lst = NULL;
}
