/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_source.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avivien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 06:35:39 by avivien           #+#    #+#             */
/*   Updated: 2021/03/02 07:11:30 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_declare(t_line *line, char *s)
{
	char	*str;
	char	*tmp;
	char	*stat;

	str = ft_strdup("declare -x ");
	if (ft_strchr(s, 61))
	{
		stat = ft_strchr(s, 61);
		((tmp = ft_substr(s, 0, stat - s)) == 0) ? ft_ero_exit_mal(line) : 0;
		((tmp = ft_strjoiner(tmp, "=\"")) == 0) ? ft_ero_exit_mal(line) : 0;
		((tmp = ft_strjoiner(tmp, stat + 1)) == 0) ? ft_ero_exit_mal(line) : 0;
		((tmp = ft_strjoiner(tmp, "\"")) == 0) ? ft_ero_exit_mal(line) : 0;
		((str = ft_strjoiner(str, tmp)) == 0) ? ft_ero_exit_mal(line) : 0;
		free(tmp);
	}
	else
		((str = ft_strjoiner(str, s)) == 0) ? ft_ero_exit_mal(line) : 0;
	return (str);
}

int		ft_export_add_new(t_line *line, char *mal, char **stat)
{
	char	*tmp;
	char	*str;

	*stat = ft_strchr(mal, 61);
	if (*stat != NULL)
		((tmp = ft_substr(mal, 0, *stat - mal)) == 0) ?
		ft_ero_exit_mal(line) : 0;
	else
	{
		((*stat = ft_strjoin("declare -x ", mal)) == 0) ?
		ft_ero_exit_mal(line) : 0;
		((str = ft_strjoin("declare -x ", mal)) == 0) ?
		ft_ero_exit_mal(line) : 0;
		return (ft_export_add_new_2(line, &str));
	}
	ft_env_add(line, mal);
	((str = ft_strjoin("declare -x ", tmp)) == 0) ? ft_ero_exit_mal(line) : 0;
	((*stat = ft_strjoin(*stat, "\"")) == 0) ? ft_ero_exit_mal(line) : 0;
	free(tmp);
	((tmp = ft_strjoin("=\"", *stat + 1)) == 0) ? ft_ero_exit_mal(line) : 0;
	free(*stat);
	((*stat = ft_strjoin(str, tmp)) == 0) ? ft_ero_exit_mal(line) : 0;
	free(tmp);
	return (ft_export_add_new_2(line, &str));
}

int		ft_chek_ascii(char *tmp)
{
	while (*tmp)
	{
		if (!(ft_isalnum(*tmp)) && *tmp != '_')
			return (1);
		tmp++;
	}
	return (0);
}

void	ft_for_wpersimm(char *m, t_line *line)
{
	char *er;

	er = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, m, ft_strlen(m));
	write(2, ": ", 2);
	write(2, er, ft_strlen(er));
	write(2, "\n", 1);
	line->ero = 1;
}

void	ft_dupsss(t_line *line)
{
	dup2(line->fd, 1);
	dup2(line->bfd, 0);
}
