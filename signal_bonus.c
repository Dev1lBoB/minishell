/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:39:18 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 08:32:16 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_quit2(int sig)
{
	(void)sig;
	if (g_lobal1 == 1 && g_lobal != 1)
		write(1, "Quit :3\n", 8);
	else
		write(1, "\b\b  \b\b", 6);
}

void	sig_clear2(int sig)
{
	(void)sig;
	g_lobal2 = 1;
	if (g_lobal1 == 0 && g_lobal != 1)
	{
		write(1, "\b\b  \b\b", 6);
		write(2, "\nminishell-3.2$ ", 16);
	}
	if (g_lobal != 1 && g_lobal1 != 0)
	{
		write(1, "\n", 1);
		g_lobal2 = 2;
	}
}

int		ft_checkline(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == 32)
		i++;
	if (line[i])
		return (0);
	return (1);
}

void	ft_creat(char **mal, int fd, pid_t pid, char **env)
{
	int		i;

	mal[0] = "ps";
	mal[1] = 0;
	fd = open("pid.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	pid = fork();
	if (pid != 0)
		waitpid(-1, &i, 0);
	else
	{
		dup2(fd, 1);
		execve("/bin/ps", mal, env);
		exit(0);
	}
	close(fd);
}

void	ft_destroy(char **mal, int fd, pid_t pid, char **env)
{
	if (!(mal[0] = ft_strdup("rm")))
		exit(9);
	if (!(mal[1] = ft_strdup("pid.txt")))
		exit(9);
	mal[2] = 0;
	close(fd);
	pid = fork();
	if (pid != 0)
		waitpid(-1, &fd, 0);
	else
	{
		execve("/bin/rm", mal, env);
		exit(0);
	}
	ft_doublefree(mal);
}
