/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exit_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:39:18 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 07:22:44 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_dv(t_line *line, char **mal)
{
	size_t j;

	if (mal[1] != 0 && mal[2] != 0)
		write(2, "too many arguments\n", 19);
	else
	{
		write(2, "exit\n", 5);
		if (!mal[1])
			exit(line->ero);
		j = 0;
		if (mal[1][j] == '-')
			j++;
		while (ft_isdigit(mal[1][j]))
			j++;
		if (ft_strlen(mal[1]) != j)
		{
			write(2, "numeric argument required\n", 26);
			exit(255);
		}
		exit((unsigned char)ft_atoi(mal[1]));
	}
}

void	ft_echo(t_line *line, char **mal)
{
	int i;
	int fl;
	int j;

	i = 1;
	fl = 0;
	line->ero = 0;
	while (mal[i])
	{
		j = 1;
		if (mal[i][0] == '-' && mal[i][1] && mal[i][1] == 'n')
			while (mal[i][j] && mal[i][j] == 'n')
				j++;
		else
			j--;
		if (mal[i][j] != 0)
		{
			i--;
			break ;
		}
		fl = 1;
		i++;
	}
	ft_echo_add1(mal, line, i, fl);
}

void	ft_pwd(t_line *line)
{
	char *path;

	line->ero = 0;
	path = getcwd(NULL, 0);
	write(line->fd, path, ft_strlen(path));
	free(path);
	write(line->fd, "\n", 1);
}

void	ft_err_comm1(char *m, t_line *line)
{
	char *er;

	er = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, m, ft_strlen(m));
	write(2, ": ", 2);
	write(2, er, ft_strlen(er));
	write(2, "\n", 1);
	line->ero = errno;
}

void	ft_cd_error(char **mal, t_line *line)
{
	char *er;

	er = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, mal[0], ft_strlen(mal[0]));
	write(2, ": ", 2);
	write(2, mal[1], ft_strlen(mal[1]));
	write(2, ": ", 2);
	write(2, er, ft_strlen(er));
	write(2, "\n", 1);
	line->ero = 1;
}
