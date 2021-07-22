/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl_homa_foma_write.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:14:53 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/19 20:19:07 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_homa(t_bonus *bon, char **line)
{
	char	*tmp;

	bon->i -= 2;
	write(1, "\b\b\b\b", 4);
	bon->a = ft_strlen(bon->buf);
	if (bon->a > 4)
		bon->a = 4;
	write(1, bon->buf, bon->a);
	while (bon->a++ < 4)
		write(1, " ", 1);
	write(1, "\b\b\b\b", 4);
	while (--bon->i >= 0)
		write(1, "\b", 1);
	bon->i = -1;
	if (bon->buf)
	{
		tmp = bon->buf;
		bon->buf = ft_strjoin(*line, bon->buf);
		free(tmp);
	}
	else
		bon->buf = ft_strdup(*line);
	tmp = *line;
	*line = ft_strdup("");
	free(tmp);
}

void	ft_foma(t_bonus *bon, char **line)
{
	bon->i -= 2;
	write(1, "\b\b\b\b", 4);
	bon->a = ft_strlen(bon->buf);
	if (bon->a > 4)
		bon->a = 4;
	write(1, bon->buf, bon->a);
	while (bon->a++ < 4)
		write(1, " ", 1);
	write(1, "\b\b\b\b", 4);
	if (bon->buf)
	{
		write(1, bon->buf, ft_strlen(bon->buf));
		*line = ft_strjoiner(*line, bon->buf);
	}
	if (bon->buf)
		free(bon->buf);
	bon->buf = 0;
	bon->i = ft_strlen(*line) - 1;
}

void	ft_del(t_bonus *bon, char **line)
{
	char	*tmp;

	if ((*line)[bon->i] == 126)
	{
		if (bon->buf)
		{
			write(1, "\b\b\b\b\b      \b\b\b\b\b\b", 17);
			tmp = bon->buf;
			bon->buf = ft_strdup(bon->buf + 1);
			free(tmp);
			bon->flag = 2;
			if (ft_strlen(bon->buf) == 0)
			{
				if (bon->buf)
					free(bon->buf);
				bon->buf = 0;
			}
		}
		else
		{
			write(1, "\b\b\b\b\b     \b\b\b\b\b", 15);
		}
	}
	(*line)[bon->i - 3] = 0;
	bon->i = ft_strlen(*line) - 1;
}

int		ft_break(t_bonus *bon, char **line)
{
	if ((*line)[bon->i] == 4)
	{
		(*line)[bon->i] = 0;
		bon->a = ft_strlen(bon->buf);
		if (bon->a > 2)
			bon->a = 2;
		write(1, "\b\b", 2);
		write(1, bon->buf, bon->a);
		while (bon->a++ < 2)
			write(1, " ", 1);
		write(1, "\b\b", 2);
		(!(*line)[0] && !bon->buf) ? write(1, "\n", 1) : 0;
		(!(*line)[0] && !bon->buf) ? bon->flag = 0 : 0;
		if ((!(*line)[0] && !bon->buf))
			return (1);
		bon->i = ft_strlen(*line) - 1;
	}
	else
	{
		write(1, "\b\b", 2);
		bon->flag = 1;
		(*line)[bon->i] = 0;
		return (1);
	}
	return (0);
}

void	ft_buf_write(t_bonus *bon)
{
	if (bon->flag == 2)
		write(1, " \b", 2);
	bon->a = ft_strlen(bon->buf);
	write(1, bon->buf, bon->a);
	if (bon->flag)
		write(1, " \b", 2);
	while (bon->a--)
		write(1, "\b", 1);
}
