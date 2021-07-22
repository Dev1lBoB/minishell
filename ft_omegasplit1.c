/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_omegasplit1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:08:45 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:36:49 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_omegacount1_2(char ***arg, int i, int *j)
{
	while ((*arg)[i][*j] && (*arg)[i][*j] != 34)
	{
		if ((*arg)[i][*j] == 92)
			(*j)++;
		(*j)++;
	}
}

static int	ft_omegacount(char ***arg, int i, int j, char c)
{
	int		ct;

	ct = 0;
	while ((*arg)[++i] && (j = -1))
		while ((*arg)[i][++j])
			if ((*arg)[i][j] == 92 && j++)
				continue ;
			else if ((*arg)[i][j] == 34 && j++)
			{
				ft_omegacount1_2(arg, i, &j);
				continue ;
			}
			else if ((*arg)[i][j] == 39)
			{
				j++;
				while ((*arg)[i][j] != 39)
					j++;
				continue ;
			}
			else if ((*arg)[i][j] == c)
				ct++;
	if ((*arg)[i - 1][j - 1] == c && (ct-- != -10))
		(*arg)[i - 1][j - 1] = 0;
	return (ct);
}

static int	ft_omegacpy1(char **arg, int *j, int i)
{
	if (arg[i][*j] == 92)
	{
		(*j)++;
		return (1);
	}
	if (arg[i][*j] == 34)
	{
		(*j)++;
		while (arg[i][*j] != 34)
		{
			if (arg[i][*j] == 92)
				(*j)++;
			(*j)++;
		}
		return (1);
	}
	if (arg[i][*j] == 39)
	{
		(*j)++;
		while (arg[i][*j] != 39)
			(*j)++;
		return (1);
	}
	return (0);
}

char		***ft_omegacpy(char ****str, char **arg, char **tmp, char c)
{
	int		i;
	int		j;
	int		ct;

	i = -1;
	ct = 0;
	while (tmp[++i] && (j = -1))
		while (tmp[i][++j])
		{
			if (ft_omegacpy1(arg, &j, i))
				continue ;
			if (tmp[i][j] == c)
			{
				(*str)[ct++] = ft_omegado(tmp, i, j);
				tmp = ft_omegaposle(tmp, i, j);
				i = -1;
				break ;
			}
		}
	(*str)[ct] = tmp;
	(*str)[ct + 1] = NULL;
	return (*str);
}

char		***ft_omegasplit(char **arg, char c)
{
	int		ct;
	char	**tmp;
	char	***str;

	(!(tmp = ft_doublecpy(arg))) ? exit(9) : 0;
	ct = ft_omegacount(&arg, -1, -1, c);
	str = malloc((ct + 2) * sizeof(char **));
	!str ? exit(9) : 0;
	if (ct == 0)
	{
		if (!(str[ct] = ft_doublecpy(tmp)))
			exit(9);
		str[1] = 0;
		ft_doublefree(tmp);
		return (str);
	}
	return (ft_omegacpy(&str, arg, tmp, c));
}
