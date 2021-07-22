# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 05:43:01 by wpersimm          #+#    #+#              #
#    Updated: 2021/03/02 08:32:23 by wpersimm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

HEAD	= minishell.h

SRCS	= add_source.c\
		cd_export.c\
		exect_r.c\
		ft_brackets.c\
		ft_bred.c\
		ft_cd.c\
		ft_export.c\
		ft_free.c\
		ft_omegasplit1.c\
		ft_pars_funks.c\
		ft_pipcount.c\
		ft_pipspace.c\
		ft_preparser.c\
		ft_redirects.c\
		ft_splat.c\
		ft_utils.c\
		ft_utils2.c\
		fun_env.c\
		fun_expo.c\
		main.c\
		parser.c\
		path.c\
		pipe_exet.c\
		pipe_pars.c\
		pogrujenie_entry.c\
		pwd_exit_echo.c\
		unset_env.c\
		add_source_1.c\
		signal.c\
		main_srcs.c

SRCS_B	= add_source.c\
		cd_export.c\
		exect_r.c\
		ft_brackets.c\
		ft_bred.c\
		ft_cd.c\
		ft_export.c\
		ft_free.c\
		ft_omegasplit1.c\
		ft_pars_funks.c\
		ft_pipcount.c\
		ft_pipspace.c\
		ft_preparser.c\
		ft_redirects.c\
		ft_splat.c\
		ft_utils.c\
		ft_utils2.c\
		fun_env.c\
		fun_expo.c\
		main_bonus.c\
		new_gnl.c\
		new_gnl_down_right_left.c\
		new_gnl_globdelup.c\
		new_gnl_homa_foma_write.c\
		new_gnl_init_start_arrows.c\
		new_gnl_utils.c\
		parser.c\
		path.c\
		pipe_exet.c\
		pipe_pars.c\
		pogrujenie_entry.c\
		pwd_exit_echo.c\
		unset_env.c\
		add_source_1.c\
		signal_bonus.c\
		main_srcs.c

LIBA	= libft/libft.a

LIBH	= libft/libft.h

LIBS	= libft/ft_atoi.c\
		libft/ft_bzero.c\
		libft/ft_calloc.c\
		libft/ft_isalnum.c\
		libft/ft_isalpha.c\
		libft/ft_isascii.c\
		libft/ft_isdigit.c\
		libft/ft_isprint.c\
		libft/ft_itoa.c\
		libft/ft_lstadd_back.c\
		libft/ft_lstadd_front.c\
		libft/ft_lstclear.c\
		libft/ft_lstdelone.c\
		libft/ft_lstiter.c\
		libft/ft_lstlast.c\
		libft/ft_lstmap.c\
		libft/ft_lstnew.c\
		libft/ft_lstsize.c\
		libft/ft_memccpy.c\
		libft/ft_memchr.c\
		libft/ft_memcmp.c\
		libft/ft_memcpy.c\
		libft/ft_memmove.c\
		libft/ft_memset.c\
		libft/ft_putchar_fd.c\
		libft/ft_putendl_fd.c\
		libft/ft_putnbr_fd.c\
		libft/ft_putstr_fd.c\
		libft/ft_split.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		libft/ft_strjoin.c\
		libft/ft_strlcat.c\
		libft/ft_strlcpy.c\
		libft/ft_strlen.c\
		libft/ft_strmapi.c\
		libft/ft_strncmp.c\
		libft/ft_strnstr.c\
		libft/ft_strrchr.c\
		libft/ft_strtrim.c\
		libft/ft_substr.c\
		libft/ft_tolower.c\
		libft/ft_toupper.c\
		libft/get_next_line.c\
		libft/get_next_line_utils.c

LIBO	= ${LIBS:.c=.o}

all:	${NAME}

${NAME}:  ${HEAD} ${SRCS} ${LIBA}
		  gcc -Wall -Wextra -Werror ${SRCS} -lft -Llibft -o ${NAME}

${LIBA}: ${LIBH} ${LIBO}
		 make -C libft

bonus: ${LIBA} ${HEAD} ${SRCS_B}
		  gcc -Wall -Wextra -Werror ${SRCS_B} -lft -Llibft -o ${NAME}

clean:
		make fclean -C libft

fclean: clean
		rm -rf ${NAME}

re:		fclean all
