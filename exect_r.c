/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exect_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:36:32 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:36:34 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exc1_1(t_line *line, char **mal)
{
	write(1, "minishell: ", 11);
	write(2, mal[0], ft_strlen(mal[0]));
	write(1, ": command not found\n", 20);
	line->ero = 127;
}

int		ft_exc1_2_1(t_line *line, char **sline, char **massi, char *sp)
{
	struct stat buff;

	if (*(*sline) != '/')
		((*massi = ft_strjoin(sp, *sline)) == 0) ? ft_ero_exit_mal(line) : 0;
	else
		*massi = ft_strdup(*sline);
	if (stat(*massi, &buff) == 0)
		return (0);
	return (1);
}

int		ft_exc1_2(t_line *line, char **mal, char **sline, char **massi)
{
	char		**sp;
	int			i;
	int			r;

	g_lobal1 = 1;
	sp = ft_exe_path(line);
	((*sline = ft_strdup(mal[0])) == NULL) ? ft_ero_exit_mal(line) : 0;
	i = -1;
	while (sp[++i])
	{
		((sp[i] = ft_strjoiner(sp[i], "/")) == 0) ? ft_ero_exit_mal(line) : 0;
		r = ft_exc1_2_1(line, sline, massi, sp[i]);
		if (r == 0)
		{
			ft_doublefree(sp);
			return (0);
		}
		else
			free(*massi);
	}
	ft_doublefree(sp);
	return (1);
}

void	ft_exc1_3(t_line *line, char **mal)
{
	ft_err_comm1(mal[0], line);
	exit(1);
}

void	ft_exc(t_line *line, char **mal)
{
	int		status;
	char	*sline;
	char	*massi;
	int		r;
	pid_t	pid;

	status = 0;
	if (!(ft_exc1_2(line, mal, &sline, &massi)))
	{
		pid = fork();
		if (pid != 0)
			waitpid(-1, &status, 0);
		else
		{
			ft_dupsss(line);
			r = execve(massi, mal, line->env);
			(r == -1) ? ft_exc1_3(line, mal) : 0;
		}
		free(massi);
		line->ero = (status == 256) ? 1 : 0;
	}
	else
		ft_exc1_1(line, mal);
	g_lobal1 = 0;
	free(sline);
}
