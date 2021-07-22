/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:52:32 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:16:29 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_omegado(char **arg, int i, int j)
{
	int		ii;
	char	**str;

	if (!(str = malloc(sizeof(char *) * (i + 2))))
		exit(9);
	ii = -1;
	while (++ii < i)
		if (!(str[ii] = ft_strdup(arg[ii])))
			exit(9);
	if (!(str[ii++] = ft_substr(arg[i], 0, j)))
		exit(9);
	str[ii] = 0;
	ii = -1;
	return (str);
}

char	**ft_omegaposle(char **arg, int i, int j)
{
	int		ii;
	int		iii;
	int		ct;
	char	**str;

	ct = 0;
	while (arg[ct])
		ct++;
	if (!(str = malloc(sizeof(char *) * (ct - i + 1))))
		exit(9);
	ii = i;
	iii = 0;
	if (!(str[0] = ft_substr(arg[i], j + 1, ft_strlen(arg[i]) - j)))
		exit(9);
	while (++ii < ct)
		if (!(str[++iii] = ft_strdup(arg[ii])))
			exit(9);
	str[++iii] = 0;
	ft_doublefree(arg);
	ii = -1;
	return (str);
}

int		ft_omegacount2(char ***arg, int i, int j, char c)
{
	int		ct;

	ct = 0;
	while ((*arg)[++i])
	{
		j = -1;
		while ((*arg)[i][++j])
		{
			if ((*arg)[i][j] == c)
				ct++;
		}
	}
	if ((*arg)[i - 1][j - 1] == c)
	{
		(*arg)[i - 1][j - 1] = 0;
		ct--;
	}
	return (ct);
}

char	***ft_omegacpy2(char ****str, char **tmp, char c)
{
	int		i;
	int		j;
	int		ct;

	i = -1;
	ct = 0;
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (tmp[i][j] == c)
			{
				(*str)[ct++] = ft_omegado(tmp, i, j);
				tmp = ft_omegaposle(tmp, i, j);
				i = -1;
				break ;
			}
		}
	}
	(*str)[ct] = tmp;
	(*str)[ct + 1] = NULL;
	return (*str);
}

char	***ft_omegasplit2(char **arg, char c)
{
	int		i;
	int		ct;
	char	**tmp;
	char	***str;

	if (!(tmp = ft_doublecpy(arg)))
		exit(9);
	ct = 0;
	i = -1;
	if (arg[0][0] == c)
		arg[0] = ft_whynot(arg[0]);
	ct = ft_omegacount2(&arg, -1, -1, c);
	if (!(str = malloc((ct + 2) * sizeof(char **))))
		exit(9);
	if (ct == 0)
	{
		if (!(str[ct] = ft_doublecpy(tmp)))
			exit(9);
		str[1] = 0;
		ft_doublefree(tmp);
		return (str);
	}
	return (ft_omegacpy2(&str, tmp, c));
}
