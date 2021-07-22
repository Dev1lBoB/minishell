/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:38:27 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:38:30 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_path_chek(t_line *line, char *mal)
{
	int		i;
	char	*spwd;
	char	*spwd1;

	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "_=/", 3) == 0)
			if ((spwd = ft_substr(line->env[i], 2,
				ft_strlen(line->env[i]) - ft_strlen(mal) + 2)) == NULL)
				ft_ero_exit_mal(line);
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PWD=/", 5) == 0)
			if ((spwd1 = ft_substr(line->env[i], 4,
				ft_strlen(line->env[i]))) == NULL)
				ft_ero_exit_mal(line);
	if (ft_strncmp(spwd, spwd1, ft_strlen(spwd)) == 0)
		return (1);
	return (0);
}

char	**ft_no_exe_path(t_line *line)
{
	char	*sline;
	char	**sp;
	int		i;
	char	*spwd;

	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "_=/", 3) == 0)
			if ((spwd = ft_substr(line->env[i], 2,
				ft_strlen(line->env[i]) - 9)) == NULL)
				ft_ero_exit_mal(line);
	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PATH=", 5) == 0)
			if ((sline = ft_strdup(line->env[i] + 5)) == NULL)
				ft_ero_exit_mal(line);
	if ((sline = ft_strjoiner(sline, ":")) == NULL)
		ft_ero_exit_mal(line);
	if ((sline = ft_strjoiner(sline, spwd)) == NULL)
		ft_ero_exit_mal(line);
	if ((sp = ft_split(sline, ':')) == NULL)
		ft_ero_exit_mal(line);
	free(sline);
	free(spwd);
	return (sp);
}

char	**ft_exe_path(t_line *line)
{
	char	*sline;
	char	**sp;
	int		i;
	char	*spwd;

	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PWD=", 4) == 0)
			if ((spwd = ft_strdup(line->env[i] + 4)) == NULL)
				ft_ero_exit_mal(line);
	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PATH=", 5) == 0)
			if ((sline = ft_strdup(line->env[i] + 5)) == NULL)
				ft_ero_exit_mal(line);
	if ((sline = ft_strjoiner(sline, ":")) == NULL)
		ft_ero_exit_mal(line);
	if ((sline = ft_strjoiner(sline, spwd)) == NULL)
		ft_ero_exit_mal(line);
	if ((sp = ft_split(sline, ':')) == NULL)
		ft_ero_exit_mal(line);
	free(sline);
	free(spwd);
	return (sp);
}
