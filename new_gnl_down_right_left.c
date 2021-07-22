/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl_down_right_left.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:11:16 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/19 20:12:48 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_down1(t_bonus *bon, char **line)
{
	write(1, "\b\b\b\b", 4);
	bon->a = ft_strlen(bon->buf);
	if (bon->a > 4)
		bon->a = 4;
	write(1, bon->buf, bon->a);
	while (bon->a++ < 4)
		write(1, " ", 1);
	write(1, "\b\b\b\b", 4);
	(*line)[bon->i - 2] = 0;
}

void	ft_down2(t_bonus *bon, char **line, char **history)
{
	bon->a = ft_strlen(*line);
	while (bon->a-- > -1)
		write(1, "\b", 1);
	bon->a = ft_strlen(*line) + ft_strlen(bon->buf);
	while (bon->a-- > -1)
		write(1, " ", 1);
	bon->a = ft_strlen(*line) + ft_strlen(bon->buf);
	while (bon->a-- > -1)
		write(1, "\b", 1);
	free(*line);
	free(bon->buf);
	bon->buf = 0;
	*line = ft_strdup(history[--bon->i1]);
	write(1, *line, ft_strlen(*line));
}

void	ft_down3(t_bonus *bon, char **line, char **history)
{
	bon->a = ft_strlen(*line);
	while (bon->a-- > -1)
		write(1, "\b", 1);
	bon->a = ft_strlen(*line);
	while (bon->a-- > -1)
		write(1, " ", 1);
	bon->a = ft_strlen(*line);
	while (bon->a-- > -1)
		write(1, "\b", 1);
	free(*line);
	*line = ft_strdup(history[--bon->i1]);
	write(1, *line, ft_strlen(*line));
}

void	ft_right(t_bonus *bon, char **line)
{
	char	*tmp;

	if (!bon->buf)
	{
		write(1, "\b\b\b\b    \b\b\b\b", 12);
		(*line)[bon->i - 2] = 0;
	}
	else
	{
		write(1, "\b\b\b\b", 4);
		bon->a = ft_strlen(bon->buf);
		if (bon->a > 4)
			bon->a = 4;
		write(1, bon->buf, bon->a);
		while (bon->a++ < 4)
			write(1, " ", 1);
		write(1, "\b\b\b", 3);
		(*line)[bon->i - 2] = 0;
		*line = ft_dop(*line, bon->buf[0]);
		tmp = bon->buf;
		bon->buf = ft_strdup(bon->buf + 1);
		free(tmp);
	}
}

void	ft_left(t_bonus *bon, char **line)
{
	char	*buf2;

	if (bon->i - 2 > 0)
	{
		write(1, "\b\b\b\b    \b\b\b\b\b", 13);
		buf2 = ft_substr(*line, 0, bon->i - 3);
		bon->buf = ft_revjoiner(*line, bon->buf);
		free(*line);
		*line = buf2;
		bon->i = ft_strlen(*line) - 1;
	}
	else
	{
		write(1, "\b\b\b\b    \b\b\b\b", 12);
		(*line)[bon->i - 2] = 0;
		bon->i = -1;
	}
}
