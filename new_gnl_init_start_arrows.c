/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_gnl_init_start_arrows.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:32:25 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 06:40:20 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_gnl_init(struct termios *info, t_bonus *bon, char **line)
{
	tcgetattr(0, info);
	bon->fl = info->c_lflag;
	info->c_lflag &= ~ICANON;
	info->c_cc[VMIN] = 1;
	info->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, info);
	*line = NULL;
	bon->i = 0;
	bon->i1 = 0;
	bon->buf = 0;
}

int		ft_new_gnl_start(struct termios *info, t_bonus *bon, char **line)
{
	if (g_lobal2)
	{
		bon->i = ft_new_gnl_glob(info, line, &bon->buf, bon->c);
		bon->i1 = 0;
		return (1);
	}
	bon->flag = 0;
	read(0, &bon->c, 1);
	*line = ft_dop(*line, bon->c);
	bon->i = ft_newgnl_del(line, &bon->flag, bon->i);
	return (0);
}

int		ft_histeria(t_bonus *bon, char **line, char **history)
{
	if ((*line)[bon->i] == 65)
	{
		(*line)[bon->i + 1] = 0;
		if (!history || !history[bon->i1])
			ft_up1(bon, line);
		else
			bon->buf ? ft_up2(bon, line, history) :
			ft_up3(bon, line, history);
		bon->i = ft_strlen(*line) - 1;
		return (1);
	}
	else if ((*line)[bon->i] == 66)
	{
		(*line)[bon->i + 1] = 0;
		if (!history || bon->i1 == 0)
			ft_down1(bon, line);
		else
			bon->buf ? ft_down2(bon, line, history) :
			ft_down3(bon, line, history);
		bon->i = ft_strlen(*line) - 1;
		return (1);
	}
	return (0);
}

int		ft_arrows(t_bonus *bon, char **line)
{
	if ((*line)[bon->i] == 67)
	{
		(*line)[bon->i + 1] = 0;
		ft_right(bon, line);
		if (ft_strlen(bon->buf) == 0)
		{
			if (bon->buf)
				free(bon->buf);
			bon->buf = 0;
		}
		bon->i = ft_strlen(*line) - 1;
		return (1);
	}
	else if ((*line)[bon->i] == 68)
	{
		(*line)[bon->i + 1] = 0;
		ft_left(bon, line);
		return (1);
	}
	return (0);
}

int		ft_hfdel(t_bonus *bon, char **line)
{
	if ((*line)[bon->i] == 'H')
	{
		(*line)[bon->i - 2] = 0;
		ft_homa(bon, line);
		return (1);
	}
	else if ((*line)[bon->i] == 'F')
	{
		(*line)[bon->i - 2] = 0;
		ft_foma(bon, line);
		return (1);
	}
	else if ((*line)[bon->i] == 51)
	{
		bon->i++;
		read(0, &bon->c, 1);
		*line = ft_dop(*line, bon->c);
		(*line)[bon->i + 1] = 0;
		ft_del(bon, line);
		return (1);
	}
	return (0);
}
