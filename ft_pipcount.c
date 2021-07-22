/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 03:40:52 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:36:00 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pipinit(t_line *line)
{
	int		i;

	i = -1;
	if (!(line->fad = malloc((line->pip + 2) * sizeof(int *))))
		exit(9);
	while (++i < line->pip + 1)
	{
		if (!(line->fad[i] = malloc(2 * sizeof(int))))
			exit(9);
		line->fad[i][0] = 0;
		line->fad[i][1] = 1;
	}
	line->fad[i] = 0;
}

static char	*ft_dtoa(char **str)
{
	int		i;
	int		j;
	int		ct;
	char	*line;

	i = -1;
	ct = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			ct++;
	}
	if (!(line = malloc((ct + 1) * sizeof(char))))
		exit(9);
	i = -1;
	ct = 0;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			line[ct++] = str[i][j];
	}
	line[ct] = 0;
	return (line);
}

static void	ft_pipcounter2(char *line, int *i)
{
	while (line[*i] != 34)
	{
		if (line[*i] == 92)
			(*i)++;
		(*i)++;
	}
}

static int	ft_pipcounter(char *line, int i, int count)
{
	while (line[++i])
	{
		if (line[i] == 92)
		{
			++i;
			continue;
		}
		if (line[i] == 34)
		{
			++i;
			ft_pipcounter2(line, &i);
			continue;
		}
		if (line[i] == 39)
		{
			++i;
			while (line[i] != 39)
				++i;
			continue;
		}
		if (line[i] == 124)
			count++;
	}
	return (count);
}

int			ft_pipcount(char **str)
{
	int		count;
	char	*line;

	line = ft_dtoa(str);
	count = ft_pipcounter(line, -1, 0);
	free(line);
	return (count);
}
