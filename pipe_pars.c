/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:38:41 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:38:42 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pars_dv_pipe1(t_line *line, char ***tmal, int i, int pp[100][2])
{
	char **mal;

	mal = ft_cleaner3(tmal[i]);
	ft_exc_command1(line, mal, pp, i);
	ft_doublefree(mal);
}

void	ft_pars_dv_pipe(void *ar, t_line *line)
{
	char	***tmal;
	int		status;
	int		i;
	pid_t	pid;
	int		pp[100][2];

	if ((tmal = ft_omegasplit2((char **)ar, -1)) == NULL)
		ft_ero_exit_mal(line);
	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (i <= line->pip)
			pipe(pp[i++]);
		i = -1;
		while (tmal[++i])
			ft_pars_dv_pipe1(line, tmal, i, pp);
		while (i-- > 0)
			wait(0);
		exit(0);
	}
	waitpid(pid, &status, 0);
	ft_triplefree(tmal);
}

void	ft_ero_exit_mal(t_line *line)
{
	line->ero = 9;
	exit(9);
}

int		ft_export_add_new_2(t_line *line, char **str)
{
	int	j;

	j = -1;
	while (line->expo[++j])
		if (ft_strncmp(line->expo[j], *str, ft_strlen(*str)) == 0)
		{
			free(*str);
			return (j);
		}
	free(*str);
	return (-1);
}
