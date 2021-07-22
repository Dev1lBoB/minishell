/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl_globdelup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 16:38:00 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 06:39:55 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_new_gnl_glob(struct termios *info, char **line, char **buf, char c)
{
	int		i;

	i = 0;
	info->c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, info);
	if (*buf)
		free(*buf);
	*buf = 0;
	free(*line);
	*line = NULL;
	if (g_lobal2 == 1)
	{
		i = 1;
		*line = ft_dop(*line, c);
	}
	else
		i = 0;
	g_lobal2 = 0;
	return (i);
}

int		ft_newgnl_del(char **line, int *flag, int i)
{
	char *tmp;

	if ((*line)[i] == 127)
	{
		if (i != 0)
		{
			write(1, "\b\b\b   \b\b\b", 9);
			tmp = *line;
			*line = ft_substr(*line, 0, ft_strlen(*line) - 2);
			free(tmp);
			i = ft_strlen(*line) - 1;
			*flag = 1;
		}
		else
		{
			write(1, "\b\b  \b\b", 6);
			(*line)[i] = 0;
			i = ft_strlen(*line) - 1;
		}
	}
	return (i);
}

void	ft_up1(t_bonus *bon, char **line)
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

void	ft_up2(t_bonus *bon, char **line, char **history)
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
	*line = ft_strdup(history[bon->i1++]);
	write(1, *line, ft_strlen(*line));
}

void	ft_up3(t_bonus *bon, char **line, char **history)
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
	*line = ft_strdup(history[bon->i1++]);
	write(1, *line, ft_strlen(*line));
}
