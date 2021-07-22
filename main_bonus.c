/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:30:45 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 08:33:46 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>

char	**ft_history(char *line, char **history)
{
	char	**buf2;
	int		i;
	int		i2;

	i = 0;
	if (!history)
	{
		buf2 = malloc(2 * sizeof(char *));
		(!(buf2[0] = ft_strdup(line))) ? exit(9) : 0;
		buf2[1] = 0;
		return (buf2);
	}
	while (history[i])
		i++;
	(!(buf2 = malloc((i + 2) * sizeof(char *)))) ? exit(9) : 0;
	!(buf2[0] = ft_strdup(line)) ? exit(9) : 0;
	i = -1;
	i2 = 1;
	while (history[++i])
		(!(buf2[i2++] = ft_strdup(history[i]))) ? exit(9) : 0;
	buf2[i2] = 0;
	ft_doublefree(history);
	return (buf2);
}

void	ft_ampersents(char **line)
{
	int		i;

	i = -1;
	while ((*line)[++i])
		if ((*line)[i] == 39)
		{
			while ((*line)[i] && (*line)[i] != 39)
				i++;
			continue ;
		}
		else if ((*line)[i] == 34)
		{
			while ((*line)[i] && (*line)[++i] != 34)
				if ((*line)[i] == 92)
					i++;
			continue ;
		}
		else if ((*line)[i] == 92 && i++)
			continue ;
		else if ((*line)[i] == 38 && (*line)[i + 1] && (*line)[i + 1] == 38)
		{
			(*line)[i + 1] = 59;
			ft_screen(line, i);
			continue ;
		}
}

void	ft_costyl(t_line *line)
{
	free(line->line);
	write(2, "minishell-3.2$ ", 15);
}

void	ft_main_bonus(t_line *line)
{
	while (new_gnl(&line->line, line->history))
	{
		ft_inits(line);
		if (ft_checkline(line->line))
		{
			ft_costyl(line);
			continue;
		}
		line->history = ft_history(line->line, line->history);
		ft_ampersents(&line->line);
		if (ft_preparser(line, &line->line) == -1)
		{
			line->ero = 258;
			ft_costyl(line);
			continue;
		}
		if (!line->line[0])
		{
			ft_costyl(line);
			continue;
		}
		ft_last_main(line);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_line	line;

	(void)(argc);
	(void)(argv);
	ft_init(&line, argv, env);
	ft_main_bonus(&line);
	write(1, "exit\n", 5);
}
