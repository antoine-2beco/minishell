/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:34:08 by hle-roi           #+#    #+#             */
/*   Updated: 2024/03/06 11:52:16 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[i] && s[i] != c)
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

static char	**test_pointeur(const char *s, char **tab, char c, int *i)
{
	*i = 0;
	if (!s)
		return (NULL);
	tab = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = NULL;
	tab = test_pointeur(s, tab, c, &i);
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			tab[i] = malloc((ft_word_len(s, c) + 1) * sizeof(char));
			if (!tab[i])
				return (ft_free(tab, i));
			j = 0;
			while (*s && *s != c)
				tab[i][j++] = *s++;
			tab[i++][j] = '\0';
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
