/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:13:29 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:14:29 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_spaceskip(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int		ft_preerror(char *line)
{
	char *str;

	str = "minishell-🐌: syntax error near unexpected token `";
	write(2, str, ft_strlen(str));
	write(2, line, ft_strlen(line));
	write(2, "\'\n", 2);
	return (-1);
}

int		ft_doperror(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_preerror(str));
}

void	ft_sort_env(char **env)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	while (env[i + 1])
	{
		len = ft_strlen(env[i]) > ft_strlen(env[i + 1]) ?
		ft_strlen(env[i]) : ft_strlen(env[i + 1]);
		if (ft_strncmp(env[i], env[i + 1], len) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

char	**ft_doublecpy(char **line)
{
	int		i;
	char	**str;

	i = 0;
	while (line[i])
		i++;
	if (!(str = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (line[++i])
		if (!(str[i] = ft_strdup(line[i])))
			return (NULL);
	str[i] = 0;
	return (str);
}
