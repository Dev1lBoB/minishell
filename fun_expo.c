/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_expo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:37:52 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:37:54 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_show(t_line *line)
{
	int i;

	i = -1;
	line->ero = 0;
	while (line->expo[++i])
	{
		write(line->fd, line->expo[i], ft_strlen(line->expo[i]));
		write(line->fd, "\n", 1);
	}
}

void	ft_sort_expo(t_line *line)
{
	int			i;
	char		*tmp;
	size_t		len;

	i = 0;
	while (line->expo[i + 1])
	{
		len = ft_strlen(line->expo[i]) > ft_strlen(line->expo[i + 1]) ?
		ft_strlen(line->expo[i]) : ft_strlen(line->expo[i + 1]);
		if (ft_strncmp(line->expo[i], line->expo[i + 1], len) > 0)
		{
			tmp = line->expo[i];
			line->expo[i] = line->expo[i + 1];
			line->expo[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	ft_free_exp(t_line *line, int kol)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	j = 0;
	if ((temp = malloc(sizeof(char *) * (line->exp_size))) == NULL)
		ft_ero_exit_mal(line);
	while (line->expo[++i])
		if (i != kol)
			((temp[j++] = ft_strdup(line->expo[i]))
			== NULL) ? ft_ero_exit_mal(line) : 0;
	temp[j] = 0;
	ft_doublefree(line->expo);
	line->expo = temp;
	line->exp_size--;
}

void	ft_export_create(t_line *line)
{
	int	i;

	i = -1;
	while (line->env[++i])
		line->expo[i] = ft_export_declare(line, line->env[i]);
	line->expo[i] = 0;
	ft_sort_expo(line);
}
