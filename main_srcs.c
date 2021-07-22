/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_srcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 08:26:45 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 08:27:09 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_main_cicle_1(t_line *line, int i)
{
	while (line->dc[++i])
	{
		ft_init_cicle1(line, i);
		ft_pipinit(line);
		line->dc[i] = ft_brackets2(line, line->dc[i], -1, -1);
		ft_garb(&line->dc[i]);
		line->dc[i] = ft_cleaner3(line->dc[i]);
		if (!line->dc[i])
		{
			ft_doublefree2(line->fad);
			break ;
		}
		if (line->pip == 0)
			ft_pars_dv(line->dc[i], line);
		else
		{
			g_lobal1 = 1;
			g_lobal = 1;
			ft_pars_dv_pipe(line->dc[i], line);
			g_lobal1 = 0;
			g_lobal = 0;
		}
		ft_doublefree2(line->fad);
	}
}

void	ft_last_main(t_line *line)
{
	int i;

	line->line = ft_pipspace(line->line);
	line->arg = ft_splinter(line->line, 32);
	line->dc = ft_omegasplit(line->arg, ';');
	ft_lstadd_back(&line->list, ft_lstnew(line->arg));
	line->list_h = line->list;
	i = -1;
	ft_main_cicle_1(line, i);
	free(line->line);
	ft_triplefree(line->dc);
	ft_lstclear(&line->list, &ft_doublefree);
	write(2, "minishell-3.2$ ", 15);
}

void	ft_inits(t_line *line)
{
	line->fd_flag = 0;
	line->red_flag = 0;
	line->bred_flag = 0;
	line->pip = 0;
	line->fd = 1;
	line->bfd = 0;
}

void	ft_global_cik(t_line *line)
{
	while (get_next_line(0, &line->line))
	{
		ft_inits(line);
		if (ft_checkline(line->line))
		{
			free(line->line);
			write(2, "minishell-3.2$ ", 15);
			continue;
		}
		if (ft_preparser(line, &line->line) == -1)
		{
			free(line->line);
			write(2, "minishell-3.2$ ", 15);
			continue;
		}
		if (!line->line[0])
		{
			free(line->line);
			write(2, "minishell-3.2$ ", 15);
			continue;
		}
		ft_last_main(line);
	}
}
