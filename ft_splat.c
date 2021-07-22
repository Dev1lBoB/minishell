/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:19:06 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 18:21:34 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_splinter1(char **s, char c, size_t i)
{
	size_t	j;

	while (--i != 0)
		if ((*s)[i - 1] == 92 && (*s)[i] == c)
			(*s)[i] = -1;
	i = ft_strlen(*s);
	while (--i != 0)
		if ((*s)[i - 1] == 92 && (*s)[i] == 34)
			(*s)[i] = -2;
	i = ft_strlen(*s);
	while (--i != 0)
		if ((*s)[i - 1] == 92 && (*s)[i] == 39)
			(*s)[i] = -3;
	i = 0;
	while ((*s)[++i])
		if ((*s)[i] == -1 && (*s)[i - 1] == c)
		{
			j = i - 1;
			while ((*s)[i] == -1)
				i++;
			if ((*s)[i] == c)
				while (++j < i)
					(*s)[j] = 32;
		}
}

static void	ft_splinter2(char **s, char c, char z)
{
	size_t	y;
	size_t	j;
	size_t	i;

	y = 0;
	i = -1;
	while ((*s)[++i])
		if ((*s)[i] == z && y == 0)
		{
			j = i + 1;
			while ((*s)[j] != z && (*s)[j])
			{
				if ((*s)[j] == 92 && z == 34)
					j++;
				j++;
			}
			if (!(*s)[j])
				break ;
			y = 1;
		}
		else if ((*s)[i] == c && y == 1)
			(*s)[i] = -1;
		else if ((*s)[i] == z && y == 1)
			y = 0;
}

static char	**ft_splinter3(char **s, char c, size_t i, size_t y)
{
	char	**ar;

	while ((*s)[++i])
		if ((*s)[i] == -2)
			(*s)[i] = 34;
	i = -1;
	while ((*s)[++i])
		if ((*s)[i] == -3)
			(*s)[i] = 39;
	i = -1;
	y = 0;
	while ((*s)[++i])
		if (((*s)[i] == c && ((*s)[i + 1] != c || (*s)[i + 1] != 0))
		|| ((*s)[i] != c && (*s)[i + 1] == 0))
			y++;
	if ((*s)[0] == c)
		y--;
	if (!(ar = malloc((y + 1) * sizeof(char *))))
		return (NULL);
	return (ar);
}

static int	ft_splinter4(char *s, char **ar, char c)
{
	size_t	i;
	size_t	j;
	size_t	y;

	y = -1;
	i = 0;
	j = 0;
	while (s[++y])
		if ((s[y] == c && (s[y + 1] != c || s[y + 1] != 0)))
			j = y + 1;
		else if (s[y] != c && (s[y + 1] == 0 || s[y + 1] == c))
			if (!(ar[i++] = ft_substr(s, j, y - j + 1)))
				return (1);
	ar[i] = NULL;
	i = 0;
	j = -1;
	while (ar[++j])
	{
		i = -1;
		while (ar[j][++i])
			if (ar[j][i] == -1)
				ar[j][i] = c;
	}
	return (0);
}

char		**ft_splinter(char const *s1, char c)
{
	char	**ar;
	char	*s;

	if (!(s = ft_strdup(s1)))
		exit(9);
	ft_splinter1(&s, c, ft_strlen(s));
	ft_splinter2(&s, c, 34);
	ft_splinter2(&s, c, 39);
	if (!(ar = ft_splinter3(&s, c, -1, 0)))
		exit(9);
	if (ft_splinter4(s, ar, c))
		exit(9);
	free(s);
	return (ar);
}
