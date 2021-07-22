/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 13:58:26 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/20 14:03:51 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_preparser1(char *line, int *i)
{
	if (line[i[0]] == 92)
	{
		i[0]++;
		if (!line[i[0]])
			return (ft_preerror("newline"));
		return (1);
	}
	if (line[i[0]] == 34)
	{
		i[0]++;
		while (line[i[0]] && line[i[0]] != 34)
		{
			if (line[i[0]] == 92)
			{
				i[0]++;
			}
			i[0]++;
		}
		if (!line[i[0]])
			return (ft_preerror("newline"));
	}
	return (0);
}

static int	ft_preparser2(char *line, int *i)
{
	if (line[i[0]] == 39)
	{
		i[0]++;
		while (line[i[0]] && line[i[0]] != 39)
			i[0]++;
		if (!line[i[0]])
			return (ft_preerror("newline"));
	}
	if (line[i[0]] == 124 || line[i[0]] == 59)
	{
		i[0]++;
		i[0] += ft_spaceskip(line + i[0]);
		if (line[i[0]] == 124)
			return (ft_preerror("|"));
		if (line[i[0]] == 59)
			return (ft_preerror(";"));
	}
	return (0);
}

static int	ft_preparser4(char **line, int *i)
{
	if ((*line)[i[0]] == 62)
	{
		i[0]++;
		if ((*line)[i[0]] == 124)
		{
			ft_screen(line, i[0]);
			if ((*line)[i[0]] == 62 || (*line)[i[0]] == 60 ||
			(*line)[i[0]] == 124 || (*line)[i[0]] == 59)
				return (ft_doperror((*line)[i[0]]));
			if ((*line)[i[0]] == 0)
				return (ft_preerror("newline"));
		}
		if ((*line)[i[0]] == 62)
			i[0]++;
		i[0] += ft_spaceskip(*line + i[0]);
		if ((*line)[i[0]] == 62 || (*line)[i[0]] == 60 ||
		(*line)[i[0]] == 124 || (*line)[i[0]] == 59)
			return (ft_doperror((*line)[i[0]]));
		if ((*line)[i[0]] == 0)
			return (ft_preerror("newline"));
		i[0]--;
	}
	return (0);
}

static int	ft_preparser3(char **line, int *i)
{
	int		j;

	j = ft_strlen(*line) - 1;
	while ((*line)[j] == 32)
		j--;
	if ((*line)[j] == 124)
		return (ft_preerror("newline"));
	if (ft_preparser4(line, i))
		return (-1);
	if ((*line)[i[0]] == 60)
	{
		i[0]++;
		i[0] += ft_spaceskip(*line + i[0]);
		if ((*line)[i[0]] == 62 || (*line)[i[0]] == 60 ||
		(*line)[i[0]] == 124 || (*line)[i[0]] == 59)
			return (ft_doperror((*line)[i[0]]));
		if ((*line)[i[0]] == 0)
			return (ft_preerror("newline"));
	}
	return (0);
}

int			ft_preparser(t_line *lin, char **line)
{
	int		i[1];
	int		z;
	int		ar;

	ar = lin->ero;
	lin->ero = 1;
	i[0] = ft_spaceskip(*line) - 1;
	if ((*line)[i[0] + 1] == 124 || (*line)[i[0] + 1] == 59)
		return (ft_doperror((*line)[i[0] + 1]));
	while ((*line)[++i[0]])
	{
		if ((z = ft_preparser1(*line, i)))
		{
			if (z == -1)
				return (-1);
			continue;
		}
		if (ft_preparser2(*line, i))
			return (-1);
		if (ft_preparser3(line, i))
			return (-1);
	}
	lin->ero = ar;
	return (0);
}
