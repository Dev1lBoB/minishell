/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:36:18 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:36:21 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_add_07(t_line *line, char *stat, char *mal, int m)
{
	free(line->expo[m]);
	ft_chek_exp_add0(line, mal);
	((line->expo[m] = ft_strdup(stat)) == 0) ? ft_ero_exit_mal(line) : 0;
}

int		fs_chek_valid(t_line *line, char *mal)
{
	char *st;
	char *tmp;

	st = ft_strchr(mal, 61);
	if (st != NULL)
		((tmp = ft_substr(mal, 0, st - mal)) == 0) ? ft_ero_exit_mal(line) : 0;
	else
		((tmp = ft_strdup(mal)) == 0) ? ft_ero_exit_mal(line) : 0;
	if ((*tmp >= '0' && *tmp <= '9') || ft_chek_ascii(tmp)
	|| (ft_strlen(tmp) == 1 && *tmp == '_'))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	ft_export_add_009(t_line *line, int m, char *stat)
{
	((line->temp = malloc(sizeof(char *) *
	(++line->exp_size + 1))) == NULL) ? ft_ero_exit_mal(line) : 0;
	while (line->expo[++m])
		((line->temp[m] = ft_strdup(line->expo[m])) == 0) ? exit(9) : 0;
	((line->temp[m++] = ft_strdup(stat)) == 0) ?
	ft_ero_exit_mal(line) : 0;
	line->temp[m] = 0;
	ft_doublefree(line->expo);
	line->expo = line->temp;
	ft_sort_expo(line);
}

void	ft_export_add(t_line *line, char **mal)
{
	int		i;
	int		m;
	char	*stat;

	i = -1;
	while (mal[++i])
	{
		if (fs_chek_valid(line, mal[i]))
		{
			write(2, "minishell-3.2$ '", 16);
			write(2, mal[i], ft_strlen(mal[i]));
			write(2, "': not a valid identifier\n", 26);
			continue;
		}
		m = ft_export_add_new(line, mal[i], &stat);
		if (m < 0)
			ft_export_add_009(line, m, stat);
		else
			ft_export_add_07(line, stat, mal[i], m);
		free(stat);
	}
}

void	ft_chek_exp_add0(t_line *liness, char *s)
{
	int		j;
	char	*s1;
	char	*tmp;

	j = -1;
	while (liness->env[++j])
	{
		if ((tmp = ft_strchr(s, 61)) == NULL)
			break ;
		if (!(s1 = ft_substr(s, 0, (tmp - s))))
			ft_ero_exit_mal(liness);
		if (ft_strncmp(liness->env[j], s1, ft_strlen(s1)) == 0)
		{
			free(s1);
			free(liness->env[j]);
			((liness->env[j] = ft_strdup(s)) == NULL) ?
			ft_ero_exit_mal(liness) : 0;
			break ;
		}
		free(s1);
	}
}
