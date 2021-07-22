/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brackets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:06:07 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 05:35:52 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_uslovie(char ***arg, int *i, int j)
{
	if ((*arg)[j][*i] == 36 && (ft_isalnum((*arg)[j][*i + 1])
	|| (*arg)[j][*i + 1] == '_' || (*arg)[j][*i + 1] == '$'
	|| (*arg)[j][*i + 1] == '?'))
		return (1);
	if ((*arg)[j][*i] == 36 && ((*arg)[j][*i + 1] == 34
	|| (*arg)[j][*i + 1] == 39))
	{
		ft_screen(&((*arg)[j]), *i);
		(*i)--;
		return (0);
	}
	return (0);
}

static int	ft_brackets2_1(t_line *line, char ***arg, int *i, int j)
{
	if (line->red_flag)
	{
		*i = ft_red2(line, &((*arg)[j]), *i - 1, *i);
		line->red_flag = 0;
		(*arg)[j][0] = 0;
		return (1);
	}
	if (line->bred_flag)
	{
		*i = ft_bred2(line, &((*arg)[j]), *i - 1, *i);
		line->bred_flag = 0;
		(*arg)[j][0] = 0;
		return (1);
	}
	if ((*arg)[j][*i] == 39)
	{
		*i = ft_single(&((*arg)[j]), *i, *i) - 1;
		return (1);
	}
	if ((*arg)[j][*i] == 34)
	{
		*i = ft_double(line, &((*arg)[j]), *i, *i) - 1;
		return (1);
	}
	return (0);
}

static int	ft_brackets2_2(t_line *line, char ***arg, int *i, int j)
{
	if (ft_brackets2_1(line, arg, i, j))
		return (1);
	if ((*arg)[j][*i] == 126 && (*i == 0 || (*arg)[j][*i - 1] == 61) &&
	(!(*arg)[j][*i + 1] || (*arg)[j][*i + 1] == '/'))
	{
		*i = ft_tilda(line, &((*arg)[j]), *i);
		return (1);
	}
	if ((*arg)[j][*i] == 92)
	{
		ft_screen(&((*arg)[j]), *i);
		return (1);
	}
	if (ft_uslovie(arg, i, j))
	{
		*i = ft_export2(line, &((*arg)[j]), *i, *i);
		return (1);
	}
	if ((*arg)[j][*i] == 124)
	{
		(*arg)[j][*i] = -1;
		line->pipa++;
	}
	return (0);
}

char		**ft_brackets2(t_line *line, char **arg1, int i, int j)
{
	char	**arg;

	arg = ft_doublecpy(arg1);
	while (arg[++j] && (i = -1))
		while (arg[j][++i])
		{
			if (ft_brackets2_2(line, &arg, &i, j))
				continue ;
			if (arg[j][i] == 62)
			{
				i = ft_red(line, &(arg[j]), i + 1, i + 1);
				if (line->red_flag)
					break ;
				continue ;
			}
			if (arg[j][i] == 60)
			{
				i = ft_bred(line, &(arg[j]), i + 1, i + 1);
				if (line->bred_flag)
					break ;
				continue ;
			}
		}
	ft_doublefree(arg1);
	return (arg);
}
