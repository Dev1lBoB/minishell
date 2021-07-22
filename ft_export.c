/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:12:21 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 06:37:26 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_export3(t_line *line, char **str)
{
	int		i;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == 92)
		{
			i++;
			continue ;
		}
		if ((*str)[i] == 39)
		{
			i++;
			while ((*str)[i] != 39)
				i++;
			continue ;
		}
		if ((*str)[i] == 36 && (*str)[i + 1] && (*str)[i + 1] != 32)
		{
			i = ft_export2(line, str, i, i);
			continue ;
		}
	}
	return (1);
}

static char	*ft_export2_1(t_line *line, char **str, int *i, int j)
{
	char	*buf;
	char	*buf2;
	int		z;

	z = -1;
	buf2 = NULL;
	(!(buf = ft_substr(*str, j + 1, *i - j - 1))) ? exit(9) : 0;
	if ((*str)[j + 1] == '?' && (*i)++)
		(!(buf2 = ft_itoa(line->ero))) ? exit(9) : 0;
	else if ((*str)[j + 1] == '$' && (*i)++)
		(!(buf2 = ft_itoa(line->pid))) ? exit(9) : 0;
	else if ((*str)[j + 1] == '0')
		(!(buf2 = ft_strdup("minishell"))) ? exit(9) : 0;
	else
		while (line->env[++z])
			if (ft_strncmp(buf, line->env[z], ft_strlen(buf)) == 0 &&
			line->env[z][ft_strlen(buf)] == 61)
			{
				(!(buf2 = ft_substr(line->env[z], ft_strlen(buf) + 1,
				ft_strlen(line->env[z]) - ft_strlen(buf) - 1))) ? exit(9) : 0;
				break ;
			}
	free(buf);
	return (buf2);
}

static int	ft_export2_2(char **str, char *buf2, int i, int j)
{
	int		z;
	char	*buf;
	char	*buf3;

	(*str)[j] = 0;
	(!(buf = ft_strdup(*str))) ? exit(9) : 0;
	(!(buf3 = ft_strdup((*str) + i))) ? exit(9) : 0;
	free(*str);
	if (buf2)
	{
		(!(*str = ft_strjoin(buf, buf2))) ? exit(9) : 0;
		(!(*str = ft_strjoiner(*str, buf3))) ? exit(9) : 0;
		z = ft_strlen(buf2);
	}
	else
		(!(*str = ft_strjoin(buf, buf3))) ? exit(9) : 0;
	free(buf);
	free(buf3);
	if (buf2)
		free(buf2);
	else
		z = 0;
	return (z);
}

int			ft_export2(t_line *line, char **str, int i, int j)
{
	char	*buf2;
	int		z;

	z = -1;
	buf2 = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == 92)
			ft_screen(str, i);
		i++;
		if ((!(ft_isalnum((*str)[i])) && (*str)[i] != '_') ||
		(*str)[j + 1] == '?' || (ft_isdigit((*str)[j + 1])))
		{
			if (ft_isdigit((*str)[j + 1]))
				i++;
			buf2 = ft_export2_1(line, str, &i, j);
			z = ft_export2_2(str, buf2, i, j);
			return (j + z - 1);
		}
	}
	return (i);
}
