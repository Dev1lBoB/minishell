/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:30:45 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 08:27:47 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	t_line line;

	(void)(argc);
	ft_init(&line, argv, env);
	ft_global_cik(&line);
	write(1, "exit\n", 5);
}
