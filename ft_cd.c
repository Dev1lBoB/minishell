/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:36:48 by avivien           #+#    #+#             */
/*   Updated: 2021/07/22 10:37:33 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd1_1(t_line *line)
{
	int		i;
	char	*path;
	char	*path_temp;

	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PWD=", 4) == 0)
		{
			if ((path = ft_strdup(line->env[i] + 4)) == NULL)
				ft_ero_exit_mal(line);
			free(line->env[i]);
			path_temp = getcwd(NULL, 0);
			if ((line->env[i] = ft_strjoin("PWD=", path_temp)) == 0)
				ft_ero_exit_mal(line);
			free(path_temp);
		}
	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "OLDPWD=", 7) == 0)
		{
			free(line->env[i]);
			line->env[i] = ft_strjoin("OLDPWD=", path);
		}
	free(path);
}

void	ft_cd1_2(t_line *line)
{
	char	*path;
	char	*path_temp;
	int		i;

	i = -1;
	while (line->expo[++i])
		if (ft_strncmp(line->expo[i] + 11, "PWD=", 4) == 0)
		{
			if ((path = ft_strdup(line->expo[i] + 15)) == NULL)
				ft_ero_exit_mal(line);
			free(line->expo[i]);
			path_temp = getcwd(NULL, 0);
			if ((line->expo[i] = ft_strjoin("declare -x PWD=", path_temp)) == 0)
				ft_ero_exit_mal(line);
			free(path_temp);
		}
	i = -1;
	while (line->expo[++i])
		if (ft_strncmp(line->expo[i] + 11, "OLDPWD=", 7) == 0)
		{
			free(line->expo[i]);
			line->expo[i] = ft_strjoin("declare -x OLDPWD=", path);
		}
	free(path);
}

void	ft_cd(char **mal, t_line *line)
{
	int		i;
	char	*s;

	if (mal[1] == NULL)
	{
		i = 0;
		while (line->env[++i])
			if (ft_strncmp(line->env[i], "HOME=", 5) == 0)
				s = ft_strdup(line->env[i] + 5);
		if (chdir(s) == -1)
			write(1, "minishell: cd: HOME not set\n", 28);
		else
			free(s);
	}
	else
	{
		if (chdir(mal[1]) == -1)
			ft_cd_error(mal, line);
		else
		{
			line->ero = 0;
			ft_cd1_1(line);
			ft_cd1_2(line);
		}
	}
}

void	ft_echo_add1(char **mal, t_line *line, int i, int fl)
{
	if (!mal[i])
	{
		if (!fl)
			write(1, "\n", 1);
		return ;
	}
	if (i == 1)
		fl = 1;
	while (mal[++i])
	{
		write(line->fd, mal[i], ft_strlen(mal[i]));
		if (mal[i + 1])
			write(line->fd, " ", 1);
	}
	if (fl != 1)
		write(line->fd, "\n", 1);
}
