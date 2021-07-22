/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:14:35 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 18:45:55 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_reda(t_line *lin, char **line, int i)
{
	if ((*line)[i] == 0)
	{
		lin->red_flag = 1;
		if (lin->fd_flag)
			(*line)[i - 2] = -5;
		else
			(*line)[i - 1] = -5;
		return (1);
	}
	return (0);
}

int		ft_redb(t_line *lin, char **line, int i)
{
	while ((*line)[++i])
		if ((*line)[i] == 34)
		{
			i = ft_double(lin, line, i, i) - 1;
			continue;
		}
		else if ((*line)[i] == 39)
		{
			i = ft_single(line, i, i) - 1;
			continue;
		}
		else if ((*line)[i] == 92)
		{
			ft_screen(line, i);
			continue;
		}
		else if ((*line)[i] == 36)
		{
			i = ft_export2(lin, line, i, i);
			continue;
		}
		else if ((*line)[i] == 62 || (*line)[i] == 60 || (*line)[i] == 124)
			break ;
	return (i);
}

int		ft_reder(char **line, char *buf, int j, int i)
{
	(j != 0 && (*line)[j - 1] == 62) ? j-- : 0;
	(j != 0 && (*line)[j - 1] == 62) ? j-- : 0;
	(*line)[j] = -5;
	free(buf);
	return (i - 1);
}

int		ft_red(t_line *lin, char **line, int i, int j)
{
	char	*buf;

	((*line)[i] == 62) ? ++j : 0;
	((*line)[i] == 62) ? lin->fd_flag = 1 : 0;
	((*line)[i] == 62) ? i++ : 0;
	if (ft_reda(lin, line, i))
		return (i - 1);
	i = ft_redb(lin, line, i - 1);
	if (!(buf = ft_substr(*line, j, i - j)))
		exit(9);
	if (lin->fad[lin->pipa][1] == -1 || lin->fad[lin->pipa][0] == -1)
		return (ft_reder(line, buf, j, i));
	if (lin->fad[lin->pipa][1] != 1 && lin->fad[lin->pipa][1])
		close(lin->fad[lin->pipa][1]);
	if (!lin->fd_flag)
		lin->fad[lin->pipa][1] = open(buf, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		lin->fad[lin->pipa][1] = open(buf, O_RDWR | O_CREAT | O_APPEND, 0644);
	(lin->fad[lin->pipa][1] == -1) ? ft_for_wpersimm(buf, lin) : 0;
	lin->fd = lin->fad[lin->pipa][1];
	free(buf);
	(j != 0 && (*line)[j - 1] == 62) ? j-- : 0;
	(j != 0 && (*line)[j - 1] == 62) ? j-- : 0;
	(*line)[j] = -5;
	return (i - 1);
}

int		ft_red2(t_line *lin, char **line, int i, int j)
{
	char	*buf;

	i = ft_redb(lin, line, i);
	if (!(buf = ft_substr(*line, j, i - j)))
		exit(9);
	if (lin->fad[lin->pipa][1] == -1 || lin->fad[lin->pipa][0] == -1)
	{
		free(buf);
		return (i - 1);
	}
	if (lin->fad[lin->pipa][1] != 1 && lin->fad[lin->pipa][1])
		close(lin->fad[lin->pipa][1]);
	if (!lin->fd_flag)
		lin->fad[lin->pipa][1] = open(buf, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		lin->fad[lin->pipa][1] = open(buf, O_RDWR | O_CREAT | O_APPEND, 0644);
	(lin->fad[lin->pipa][1] == -1) ? ft_for_wpersimm(buf, lin) : 0;
	lin->fd = lin->fad[lin->pipa][1];
	free(buf);
	return (i - 1);
}
