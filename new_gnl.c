/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 01:39:56 by wpersimm          #+#    #+#             */
/*   Updated: 2021/07/22 10:40:35 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_jump1(t_bonus *bon, char **line)
{
	if ((*line)[bon->i] == 53)
	{
		bon->i++;
		read(0, &bon->c, 1);
		*line = ft_dop(*line, bon->c);
		(*line)[bon->i + 1] = 0;
		if ((*line)[bon->i] == 126)
		{
			write(1, "\b\b\b\b\b     \b\b\b\b\b", 15);
			(*line)[bon->i - 3] = 0;
			ft_prev(line, &bon->buf);
			bon->i = ft_strlen(*line) - 1;
		}
		bon->i = ft_strlen(*line) - 1;
		return (1);
	}
	return (0);
}

int		ft_jump2(t_bonus *bon, char **line)
{
	if ((*line)[bon->i] == 54)
	{
		bon->i++;
		read(0, &bon->c, 1);
		*line = ft_dop(*line, bon->c);
		(*line)[bon->i + 1] = 0;
		if ((*line)[bon->i] == 126)
		{
			write(1, "\b\b\b\b\b     \b\b\b\b\b", 15);
			(*line)[bon->i - 3] = 0;
			ft_next(line, &bon->buf);
			bon->i = ft_strlen(*line) - 1;
		}
		bon->i = ft_strlen(*line) - 1;
		return (1);
	}
	return (0);
}

void	ft_new_gnl1(t_bonus *bon, char **line, char **history)
{
	if ((*line)[bon->i] == 27)
	{
		bon->i++;
		read(0, &bon->c, 1);
		*line = ft_dop(*line, bon->c);
		bon->i++;
		read(0, &bon->c, 1);
		*line = ft_dop(*line, bon->c);
		if (ft_histeria(bon, line, history))
		{
		}
		else if (ft_arrows(bon, line))
		{
		}
		else if (ft_hfdel(bon, line))
		{
		}
		else if (ft_jump1(bon, line))
		{
		}
		else if (ft_jump2(bon, line))
		{
		}
	}
}

void	n_gnl2(struct termios *info, t_bonus *bon, char **line, char **history)
{
	while (1)
	{
		if (ft_new_gnl_start(info, bon, line))
			continue ;
		ft_new_gnl1(bon, line, history);
		if (g_lobal2)
		{
			if ((*line)[bon->i] == '\n')
				write(2, "minishell-3.2$ ", 15);
			continue ;
		}
		if (bon->i != -1 && ((*line)[bon->i] == 4 || (*line)[bon->i] == '\n'))
		{
			if (ft_break(bon, line))
				break ;
		}
		if (bon->buf)
			ft_buf_write(bon);
		bon->i++;
	}
}

int		new_gnl(char **line, char **history)
{
	char			*tmp;
	struct termios	info;
	t_bonus			bon;

	tmp = NULL;
	ft_new_gnl_init(&info, &bon, line);
	n_gnl2(&info, &bon, line, history);
	if ((*line)[0] == '\n')
	{
		tmp = *line;
		*line = ft_strdup(*line + 1);
		free(tmp);
	}
	if (bon.buf)
	{
		*line = ft_strjoiner(*line, bon.buf);
		free(bon.buf);
	}
	info.c_lflag = bon.fl;
	tcsetattr(0, TCSANOW, &info);
	return (bon.flag);
}
