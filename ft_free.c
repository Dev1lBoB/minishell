/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:19:16 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 18:19:28 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_doublefree(void *star)
{
	int		i;
	char	**str;

	str = (char **)star;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = 0;
}

void	ft_doublefree2(void *star)
{
	int		i;
	int		**str;

	str = (int **)star;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = 0;
}

void	ft_triplefree(void *star)
{
	int		i;
	char	***str;

	str = (char ***)star;
	i = -1;
	while ((str)[++i])
		ft_doublefree((str)[i]);
	free(str);
	str = 0;
}
