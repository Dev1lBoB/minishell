/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exet.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:38:53 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:38:55 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exc_command1(t_line *line, char **mal, int pp[100][2], int m)
{
	char	*massi;
	int		r;
	pid_t	pid;

	r = ft_exc_command1_1(line, mal, &massi);
	if (r == 0)
	{
		pid = fork();
		if (pid != 0)
			(m != line->pip) ? close(pp[m][1]) : 0;
		else
		{
			ft_exc_command1_2(line, pp, m);
			r = execve(massi, mal, line->env);
			dup2(1, 1);
			dup2(0, 0);
			(r == -1) ? ft_lit_exit(mal[0], line) : 0;
		}
		free(massi);
	}
	else
		ft_exc_command1_3(line, mal);
	g_lobal = 0;
}

void	ft_exc_command1_3(t_line *line, char **mal)
{
	if (mal[0][0] != -1)
	{
		write(1, "minishell: ", 11);
		write(2, mal[0], ft_strlen(mal[0]));
		write(1, ": command not found\n", 20);
		line->ero = errno;
	}
}

void	ft_exc_command1_2(t_line *line, int pp[100][2], int m)
{
	if (m == 0)
	{
		close(pp[m][0]);
		dup2(pp[m][1], 1);
		close(pp[m][1]);
	}
	else if (m < line->pip)
	{
		close(pp[m - 1][1]);
		dup2(pp[m - 1][0], 0);
		close(pp[m][0]);
		dup2(pp[m][1], 1);
	}
	else
	{
		close(pp[m - 1][1]);
		dup2(pp[m - 1][0], 0);
		close(pp[m - 1][0]);
	}
	(line->fad[m][1] != 1) ? dup2(line->fad[m][1], 1) : 0;
	(line->fad[m][0] != 0) ? dup2(line->fad[m][0], 0) : 0;
}

char	*ft_exc_command_007(t_line *line)
{
	int		i;
	char	*sline;

	i = -1;
	while (line->env[++i])
		if (ft_strncmp(line->env[i], "PATH=", 5) == 0)
			((sline = ft_strdup(line->env[i] +
			5)) == 0) ? exit(9) : 0;
	return (sline);
}

int		ft_exc_command1_1(t_line *line, char **mal, char **massi)
{
	int			i;
	char		*sline;
	int			r;
	char		**sp;
	struct stat	buff;

	sline = ft_exc_command_007(line);
	((sp = ft_split(sline, ':')) == NULL) ? exit(9) : 0;
	free(sline);
	i = -1;
	while (sp[++i])
	{
		r = 1;
		((sp[i] = ft_strjoiner(sp[i], "/")) == 0) ? ft_ero_exit_mal(line) : 0;
		((*massi = ft_strjoin(sp[i], mal[0])) == 0) ? ft_ero_exit_mal(line) : 0;
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
