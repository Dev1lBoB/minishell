/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:37:46 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 06:37:48 by avivien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_line *line, int kol)
{
	int		i;
	int		j;
	char	**temp;

	i = -1;
	j = 0;
	if ((temp = malloc(sizeof(char *) * (line->env_size))) == NULL)
		ft_ero_exit_mal(line);
	while (line->env[++i])
		if (i != kol)
			if ((temp[j++] = ft_strdup(line->env[i])) == NULL)
				ft_ero_exit_mal(line);
	temp[j] = 0;
	ft_doublefree(line->env);
	line->env = temp;
	line->env_size--;
}

void	ft_env_create(char **env, t_line *line)
{
	int	i;

	i = -1;
	while (env[++i])
		if ((line->env[i] = ft_strdup(env[i])) == NULL)
			ft_ero_exit_mal(line);
	line->env[i] = 0;
}

void	ft_env_up(t_line *line)
{
	int		i;
	char	*s;
	char	*ll;
	char	s1[150];

	i = -1;
	while (line->env[++i])
	{
		if (ft_strncmp(line->env[i], "SHLVL=", 6) == 0)
		{
			((s = ft_strdup(line->env[i])) == NULL) ? ft_ero_exit_mal(line) : 0;
			free(line->env[i]);
			ft_strlcpy(s1, s, 7);
			ll = ft_itoa(ft_atoi(s + 6) + 1);
			if ((line->env[i] = ft_strjoin(s1, ll)) == NULL)
				ft_ero_exit_mal(line);
			free(s);
			free(ll);
		}
		if (ft_strncmp(line->env[i], "OLDPWD=", 7) == 0)
		{
			free(line->env[i]);
			line->env[i] = ft_strdup("OLDPWD=");
		}
	}
}

void	ft_env_show(t_line *line)
{
	int i;

	i = -1;
	line->ero = 0;
	while (line->env[++i])
	{
		if (ft_strncmp(line->env[i], "OLDPWD=", 7) ==
		0 && ft_strlen(line->env[i]) == 7)
			continue ;
		write(line->fad[0][1], line->env[i], ft_strlen(line->env[i]));
		write(line->fad[0][1], "\n", 1);
	}
}

void	ft_env_add(t_line *line, char *s)
{
	char	**env1;
	int		i;
	char	*s1;

	i = -1;
	s1 = ft_substr(s, 0, (ft_strchr(s, 61)) - s);
	while (line->env[++i])
		if (ft_strncmp(line->env[i], s1, ft_strlen(s1)) == 0)
		{
			free(s1);
			return ;
		}
	free(s1);
	line->env_size++;
	env1 = malloc(sizeof(char *) * (line->env_size + 1));
	i = -1;
	while (line->env[++i])
		env1[i] = ft_strdup(line->env[i]);
	env1[i++] = ft_strdup(s);
	env1[i] = 0;
	ft_doublefree(line->env);
	line->env = env1;
}
