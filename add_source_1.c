/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_source_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:39:18 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 08:06:37 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_getpid(char **env, char *str)
{
	int		i;
	int		z;
	int		fd;
	char	**mal;
	pid_t	pid;

	pid = 0;
	fd = 0;
	if (!(mal = malloc(sizeof(char *) * 3)))
		exit(9);
	ft_creat(mal, fd, pid, env);
	fd = open("pid.txt", O_RDONLY, 0666);
	while ((z = get_next_line(fd, &mal[0])))
	{
		if (z == -1)
			exit(9);
		if (ft_strnstr(mal[0], str + 2, ft_strlen(mal[0])))
			i = ft_atoi(mal[0]);
		free(mal[0]);
	}
	free(mal[0]);
	ft_destroy(mal, fd, pid, env);
	return (i);
}

void	ft_garb(char ***ar)
{
	int		i;
	int		j;

	i = -1;
	while ((*ar)[++i])
	{
		j = -1;
		while ((*ar)[i][++j])
			if ((*ar)[i][j] == -5)
				(*ar)[i][j] = 0;
	}
}

char	*ft_home(char **env)
{
	int		i;
	char	*home;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			if (!(home = ft_strdup(env[i] + 5)))
				return (NULL);
			return (home);
		}
	return (NULL);
}

void	ft_init(t_line *line, char **argv, char **env)
{
	dup2(0, 1);
	g_lobal1 = 0;
	g_lobal = 0;
	line->ero = 0;
	line->env_size = 0;
	while (env[line->env_size])
		line->env_size++;
	line->list = NULL;
	line->history = NULL;
	line->exp_size = line->env_size;
	!(line->env = malloc(sizeof(char *) * (line->env_size + 1))) ? exit(9) : 0;
	ft_env_create(env, line);
	ft_env_up(line);
	!(line->expo = malloc(sizeof(char *) * (line->env_size + 1))) ? exit(9) : 0;
	ft_export_create(line);
	line->pid = ft_getpid(env, argv[0]);
	line->home = ft_home(env);
	write(2, "minishell-3.2$ ", 15);
	signal(SIGQUIT, sig_quit2);
	signal(SIGINT, sig_clear2);
}

void	ft_init_cicle1(t_line *line, int i)
{
	line->fd_flag = 0;
	line->red_flag = 0;
	line->bred_flag = 0;
	line->pip = 0;
	line->pipa = 0;
	line->fd = 1;
	line->bfd = 0;
	line->pip = ft_pipcount(line->dc[i]);
}
