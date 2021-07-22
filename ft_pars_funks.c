/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_funks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:00:22 by wpersimm          #+#    #+#             */
/*   Updated: 2021/02/21 19:04:25 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_screen(char **str, int i)
{
	char	*buf;
	char	*buf2;

	if (!(buf = ft_substr(*str, 0, i)))
		exit(9);
	if (!(buf2 = ft_strdup(*str + i + 1)))
		exit(9);
	free(*str);
	if (!(*str = ft_strjoin(buf, buf2)))
		exit(9);
	free(buf);
	free(buf2);
}

int		ft_single(char **line, int i, int j)
{
	char	*buf;
	char	*buf2;

	while ((*line)[++i])
		if ((*line)[i] == 39)
		{
			buf = *line;
			if (!(*line = ft_substr(buf, 0, j)))
				exit(9);
			if (!(buf2 = ft_substr(buf, j + 1, i - j - 1)))
				exit(9);
			if (!(*line = ft_strjoiner(*line, buf2)))
				exit(9);
			free(buf2);
			if (!(buf2 = ft_substr(buf, i + 1, ft_strlen(buf) - i - 1)))
				exit(9);
			if (i != (int)ft_strlen(buf) - 1)
				if (!(*line = ft_strjoiner(*line, buf2)))
					exit(9);
			free(buf2);
			free(buf);
			return (i - 1);
		}
	return (i);
}

void	ft_double2(char **line, int i, int j)
{
	char	*buf;
	char	*buf2;

	buf = *line;
	(!(*line = ft_substr(buf, 0, j))) ? exit(9) : 0;
	(!(buf2 = ft_substr(buf, j + 1, i - j - 1))) ? exit(9) : 0;
	(!(*line = ft_strjoiner(*line, buf2))) ? exit(9) : 0;
	free(buf2);
	if (!(buf2 = ft_substr(buf, i + 1, ft_strlen(buf) - i - 1)))
		exit(9);
	if (i != (int)ft_strlen(buf) - 1)
		(!(*line = ft_strjoiner(*line, buf2))) ? exit(9) : 0;
	free(buf2);
	free(buf);
}

int		ft_double(t_line *lin, char **line, int i, int j)
{
	while ((*line)[++i])
	{
		if ((*line)[i] == 92 && ((*line)[i + 1] == 34
		|| (*line)[i + 1] == 92 || (*line)[i + 1] == 36))
		{
			ft_screen(line, i);
			continue ;
		}
		((*line)[i] == 36) ? i = ft_export2(lin, line, i, i) : 0;
		if ((*line)[i] == 34)
		{
			ft_double2(line, i, j);
			return (i - 1);
		}
	}
	return (i);
}

int		ft_tilda(t_line *line, char **arg, int i)
{
	char	*buf1;
	char	*buf2;
	char	*buf3;
	int		z;

	z = -1;
	while (line->env[++z])
		if (ft_strncmp(line->env[z], "HOME=", 5) == 0)
		{
			(!(buf1 = ft_strdup(line->env[z] + 5))) ? exit(9) : 0;
			break ;
		}
	if (!line->env[z])
		(!(buf1 = ft_strdup(line->home))) ? exit(9) : 0;
	(!(buf2 = ft_substr(*arg, 0, i))) ? exit(9) : 0;
	(!(buf3 = ft_substr(*arg, i + 1, ft_strlen(*arg) - i - 1))) ? exit(9) : 0;
	free(*arg);
	(!(*arg = ft_strjoin(buf2, buf1))) ? exit(9) : 0;
	(!(*arg = ft_strjoiner(*arg, buf3))) ? exit(9) : 0;
	z = ft_strlen(buf1);
	free(buf1);
	free(buf2);
	free(buf3);
	return (i + z - 1);
}
