/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wini <wini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:46:36 by wsilveir          #+#    #+#             */
/*   Updated: 2025/08/10 05:31:46 by wini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_spl(char **spl)
{
	size_t	i;

	i = 0;
	if (!spl)
		return (NULL);
	while (spl[i])
		free (spl[i++]);
	free (spl);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**spl;
	size_t	i;
	size_t	start;
	size_t	word;

	spl = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!spl)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (i > start)
		{
			spl[word] = ft_substr(s, start, i - start);
			if (!spl[word++])
				return (free_spl(spl));
		}
	}
	return (spl);
}
