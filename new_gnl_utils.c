/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:29:48 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/19 20:40:50 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_revjoiner(char *s1, char *s2)
{
	char	*buf;

	buf = malloc((ft_strlen(s2) + 2) * sizeof(char));
	buf[0] = s1[ft_strlen(s1) - 4];
	ft_memcpy(buf + 1, s2, ft_strlen(s2));
	buf[ft_strlen(s2) + 1] = 0;
	free(s2);
	return (buf);
}

char		*ft_dop(char *s1, char c)
{
	char	*buf;
	int		i;

	if (s1)
	{
		buf = malloc((ft_strlen(s1) + 2) * sizeof(char));
		i = -1;
		while (s1[++i])
			buf[i] = s1[i];
		buf[i++] = c;
		buf[i] = 0;
	}
	else
	{
		buf = malloc(2 * sizeof(char));
		buf[0] = c;
		buf[1] = 0;
	}
	free(s1);
	return (buf);
}

static void	ft_prev1(char *tmp, char **buf)
{
	char	*tp;

	if (*buf)
	{
		tp = *buf;
		*buf = ft_strjoin(tmp, *buf);
		free(tp);
	}
	else
		*buf = ft_strdup(tmp);
}

void		ft_prev(char **line, char **buf)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tp;

	i = ft_strlen(*line);
	if (i == 0)
		return ;
	j = i;
	while (--i > 0)
		if (i > 0 && (*line)[i] != 32 && (*line)[i - 1] == 32)
			break ;
	tmp = ft_substr(*line, i, j - i);
	ft_prev1(tmp, buf);
	tp = *line;
	*line = ft_substr(*line, 0, i);
	free(tp);
	while (--j >= i)
		write(1, "\b", 1);
	free(tmp);
}

void		ft_next(char **line, char **buf)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tp;

	if (!*buf)
		return ;
	i = -1;
	j = ft_strlen(*buf);
	while (++i < j)
		if ((*buf)[i] != 32 && (*buf)[i - 1] == 32)
			break ;
	tmp = ft_substr(*buf, 0, i);
	tp = *buf;
	*buf = ft_substr(*buf, i, ft_strlen(*buf));
	free(tp);
	*line = ft_strjoiner(*line, tmp);
	j = -1;
	while (tmp[++j])
		write(1, &tmp[j], 1);
	free(tmp);
}
