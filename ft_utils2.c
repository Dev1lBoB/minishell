/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:15:17 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:15:57 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cleaner3(char **line)
{
	int		i;
	int		j;
	char	**str;

	i = -1;
	j = 0;
	while (line[++i])
		if (line[i][0] && line[i][0] != -5)
			j++;
	(!(str = malloc(sizeof(char *) * (j + 1)))) ? exit(9) : 0;
	i = -1;
	while (i < j)
		str[++i] = 0;
	i = -1;
	j = -1;
	while (line[++i])
		if (line[i][0] && line[i][0] != -5)
			(!(str[++j] = ft_strdup(line[i]))) ? exit(9) : 0;
	ft_doublefree(line);
	if (str[0] == NULL)
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*ft_whynot(char *str)
{
	char	*line;

	if (!(line = ft_strdup(str + 1)))
		exit(9);
	free(str);
	return (line);
}
