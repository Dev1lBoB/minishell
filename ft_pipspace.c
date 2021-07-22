/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipspace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:13:32 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 18:15:23 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_addspace(char *s1, int i)
{
	char	*buf1;
	char	*buf2;

	if (!(buf1 = ft_substr(s1, 0, i + 1)))
		exit(9);
	buf1[i] = 32;
	if (!(buf2 = ft_substr(s1, i, ft_strlen(s1) - i)))
		exit(9);
	if (!(buf1 = ft_strjoiner(buf1, buf2)))
		exit(9);
	free(buf2);
	free(s1);
	return (buf1);
}

static int	ft_pipspace1(char *str, int *i)
{
	if (str[i[0]] == 34)
	{
		i[0]++;
		while (str[i[0]] && str[i[0]] != 34)
		{
			if (str[i[0]] == 92)
				i[0]++;
			i[0]++;
		}
		return (1);
	}
	if (str[i[0]] == 39)
	{
		i[0]++;
		while (str[i[0]] && str[i[0]] != 39)
			i[0]++;
		return (1);
	}
	if (str[i[0]] == 92)
	{
		i[0]++;
		return (1);
	}
	return (0);
}

static int	ft_pipspace2(char *str, int *i)
{
	if (str[i[0]] == 34)
	{
		i[0]++;
		while (str[i[0]] && str[i[0]] != 34)
		{
			if (str[i[0]] == 92)
				i[0]++;
			i[0]++;
		}
		return (1);
	}
	if (str[i[0]] == 39)
	{
		i[0]++;
		while (str[i[0]] != 39)
			i[0]++;
		return (1);
	}
	if (str[i[0]] == 92)
	{
		i[0]++;
		return (1);
	}
	return (0);
}

static void	ft_pipspace3(char **str, int *i)
{
	while ((*str)[++i[0]])
	{
		if (ft_pipspace1(*str, i))
			continue ;
		if ((*str)[i[0]] == 62 || (*str)[i[0]] == 60)
		{
			while ((*str)[i[0]] == 32)
				i[0]++;
			while ((*str)[i[0]] && (*str)[i[0] + 1] &&
			(*str)[i[0]] != 124 &&
			(*str)[i[0]] != 59 && (*str)[i[0]] != 32)
			{
				if (ft_pipspace2(*str, i))
					continue ;
				i[0]++;
			}
			if ((*str)[i[0]] == 124)
				*str = ft_addspace(*str, i[0]);
		}
	}
}

char		*ft_pipspace(char *line)
{
	char	*str;
	int		i[1];

	if (!(str = ft_strdup(line)))
		exit(9);
	i[0] = -1;
	ft_pipspace3(&str, i);
	i[0]--;
	while (str[i[0]] == 32 && i[0] >= 0)
		i[0]--;
	if (str[i[0]] == ';')
		str[i[0]] = ' ';
	free(line);
	return (str);
}
