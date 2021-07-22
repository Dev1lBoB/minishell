/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bred.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:45:28 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 18:45:46 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_bred(t_line *lin, char **line, int i, int j)
{
	char	*buf;

	if ((*line)[i] == 0)
	{
		lin->bred_flag = 1;
		(*line)[i - 1] = -5;
		return (i - 1);
	}
	i = ft_redb(lin, line, i - 1);
	if (!(buf = ft_substr(*line, j, i - j)))
		exit(9);
	if (lin->fad[lin->pipa][1] == -1 || lin->fad[lin->pipa][0] == -1)
		return (ft_reder(line, buf, j, i));
	if (lin->fad[lin->pipa][0] != 1 && lin->fad[lin->pipa][0])
		close(lin->fad[lin->pipa][0]);
	lin->fad[lin->pipa][0] = open(buf, O_RDONLY);
	lin->bfd = lin->fad[lin->pipa][0];
	free(buf);
	if ((*line)[j - 1] == 62)
		j--;
	if ((*line)[j - 1] == 62)
		j--;
	(*line)[j - 1] = -5;
	return (i - 1);
}

int		ft_bred2(t_line *lin, char **line, int i, int j)
{
	char	*buf;

	i = ft_redb(lin, line, i);
	if (!(buf = ft_substr(*line, j, i - j)))
		exit(9);
	if (lin->fad[lin->pipa][0] != 1 && lin->fad[lin->pipa][0])
		close(lin->fad[lin->pipa][0]);
	lin->fad[lin->pipa][0] = open(buf, O_RDONLY);
	(lin->fad[lin->pipa][0] == -1) ? ft_for_wpersimm(buf, lin) : 0;
	lin->bfd = lin->fad[lin->pipa][0];
	free(buf);
	return (i - 1);
}
