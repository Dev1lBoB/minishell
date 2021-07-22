/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pogrujenie_entry.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:39:06 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:39:08 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_minishell1_2(t_line *line, char **mal)
{
	ft_err_comm1(mal[0], line);
	exit(0);
}

void	ft_add_minishell1_1(t_line *line, char **mal)
{
	write(1, "minishell: ", 11);
	write(2, mal[0], ft_strlen(mal[0]));
	write(1, ": command not found\n", 20);
	line->ero = 127;
}

void	ft_add_minishell(t_line *line, char **mal)
{
	int		status;
	char	*sline;
	char	*massi;
	int		r;
	pid_t	pid;

	if (!(ft_add_minishell1_3(line, mal, &massi, &sline)))
	{
		line->ero = 0;
		pid = fork();
		if (pid != 0)
			waitpid(-1, &status, 0);
		else
		{
			dup2(line->fd, 1);
			dup2(line->bfd, 0);
			r = execve(massi, mal, line->env);
			(r == -1) ? ft_add_minishell1_2(line, mal) : 0;
		}
		free(massi);
	}
	else
		ft_add_minishell1_1(line, mal);
	g_lobal = 0;
	free(sline);
}

int		ft_add_minishell1_3(t_line *line, char **mal,
		char **massi, char **sline)
{
	int			r;
	char		**sp;
	struct stat	buff;
	int			i;

	(ft_strncmp(mal[0], "/.minishell", 7) == 0) ? mal[0] += 2 : 0;
	g_lobal = 1;
	sp = ft_no_exe_path(line);
	((*sline = ft_strdup(mal[0])) == 0) ? ft_ero_exit_mal(line) : 0;
	i = -1;
	while (sp[++i])
	{
		r = 1;
		((sp[i] = ft_strjoiner(sp[i], "/")) == 0) ? ft_ero_exit_mal(line) : 0;
		((*massi = ft_strjoin(sp[i], *sline)) == 0) ? ft_ero_exit_mal(line) : 0;
		(stat(*massi, &buff) == 0) ? r = 0 : 0;
		if (r == 0)
		{
			ft_doublefree(sp);
			return (0);
		}
		free(*massi);
	}
	ft_doublefree(sp);
	return (1);
}
