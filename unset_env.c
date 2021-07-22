/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:39:26 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:39:28 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset1(t_line *line, char *mal)
{
	int		m;
	int		j;
	char	*str;

	m = -1;
	while (ft_strlen(line->expo[++m]))
	{
		(!(str = malloc(ft_strlen(mal) + 14))) ? ft_ero_exit_mal(line) : 0;
		ft_strlcpy(str, "declare -x ", 13);
		ft_strlcat(str, mal, ft_strchr(mal, 61) - mal + 13);
		j = -1;
		if (ft_strncmp(line->expo[m], str, ft_strlen(str)) == 0)
		{
			while (line->env[++j])
				if (ft_strncmp(line->env[j], mal, ft_strlen(mal)) == 0)
				{
					free(str);
					ft_free_env(line, j);
					break ;
				}
			ft_free_exp(line, m);
			break ;
		}
		free(str);
	}
}

void	ft_unset(t_line *line, char **mal)
{
	int i;

	i = -1;
	line->ero = 0;
	while (mal[++i])
		ft_unset1(line, mal[i]);
}

int		ft_pars_dv1_1(t_line *line, char **mal)
{
	if (ft_strncmp(mal[0], "exit ", ft_strlen(mal[0])) == 0
	&& ft_strlen(mal[0]) == 4)
		ft_exit_dv(line, mal);
	else if (ft_strncmp(mal[0], "cd ", ft_strlen(mal[0])) == 0
	&& ft_strlen(mal[0]) == 2)
		ft_cd(mal, line);
	else if (ft_strncmp(mal[0], "echo ", ft_strlen(mal[0])) == 0
	&& ft_strlen(mal[0]) == 4)
		ft_echo(line, mal);
	else if (ft_strncmp(mal[0], "pwd ", ft_strlen(mal[0])) == 0
	&& ft_strlen(mal[0]) == 3)
		ft_pwd(line);
	else if (ft_strncmp(mal[0], "unset ", ft_strlen(mal[0])) == 0)
		ft_unset(line, mal + 1);
	else
		return (1);
	return (0);
}

void	ft_pars_dv(void *ar, t_line *line)
{
	char **mal;

	mal = (char **)ar;
	if (!mal[0][0])
		return ;
	if (ft_pars_dv1_1(line, mal))
	{
		if (((ft_strncmp(mal[0], "/.minishell", 7) == 0 &&
		ft_strlen(mal[0]) == 7) && ft_path_chek(line, mal[0])))
			ft_add_minishell(line, mal);
		else if (ft_strncmp(mal[0], "env", 3) == 0)
			ft_env_show(line);
		else if (ft_strncmp(mal[0], "export ", 6) == 0)
			(ft_strlen(mal[1]) == 0) ? ft_export_show(line)
			: ft_export_add(line, mal + 1);
		else
			ft_exc(line, mal);
	}
}

void	ft_lit_exit(char *mal, t_line *line)
{
	ft_err_comm1(mal, line);
	exit(1);
}
