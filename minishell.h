/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpersimm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:47:23 by wpersimm          #+#    #+#             */
/*   Updated: 2021/03/02 08:28:08 by wpersimm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <term.h>

typedef struct	s_line
{
	char		**history;
	char		**env;
	int			ero;
	char		**expo;
	char		**temp;
	char		*line;
	char		*home;
	char		*command;
	char		**arg;
	char		***dc;
	int			pip;
	int			pipa;
	t_list		**glist;
	t_list		*list;
	t_list		*list_h;
	int			fd;
	int			bfd;
	int			**fad;
	int			fd_flag;
	int			red_flag;
	int			bred_flag;
	int			env_size;
	int			exp_size;
	int			plag;
	int			pid;
}				t_line;

typedef	struct	s_bonus
{
	int			i;
	int			i1;
	int			fl;
	int			a;
	char		c;
	int			flag;
	char		*buf;
}				t_bonus;

int				g_lobal;
int				g_lobal1;
int				g_lobal2;

char			**g_envps;

int				new_gnl(char **line, char **history);
char			*ft_revjoiner(char *s1, char *s2);
char			*ft_dop(char *s1, char c);
void			ft_prev(char **line, char **buf);
void			ft_next(char **line, char **buf);
int				ft_new_gnl_glob(struct termios *info,\
				char **line, char **buf, char c);
int				ft_newgnl_del(char **line, int *flag, int i);
void			ft_up1(t_bonus *bon, char **line);
void			ft_up2(t_bonus *bon, char **line, char **history);
void			ft_up3(t_bonus *bon, char **line, char **history);
void			ft_down1(t_bonus *bon, char **line);
void			ft_down2(t_bonus *bon, char **line, char **history);
void			ft_down3(t_bonus *bon, char **line, char **history);
void			ft_right(t_bonus *bon, char **line);
void			ft_left(t_bonus *bon, char **line);
void			ft_homa(t_bonus *bon, char **line);
void			ft_foma(t_bonus *bon, char **line);
void			ft_del(t_bonus *bon, char **line);
int				ft_break(t_bonus *bon, char **line);
void			ft_buf_write(t_bonus *bon);
void			ft_new_gnl_init(struct termios *info,\
				t_bonus *bon, char **line);
int				ft_new_gnl_start(struct termios *info,\
				t_bonus *bon, char **line);
int				ft_histeria(t_bonus *bon, char **line, char **history);
int				ft_arrows(t_bonus *bon, char **line);
int				ft_hfdel(t_bonus *bon, char **line);

char			*ft_pipspace(char *line);
int				ft_preparser(t_line *lin, char **line);
int				ft_export3(t_line *lin, char **line);

void			ft_brackets(t_line *line, int i, int j);
char			**ft_brackets2(t_line *line, char **arg, int i, int j);

int				ft_double(t_line *lin, char **line, int i, int j);
int				ft_redb(t_line *lin, char **line, int i);
int				ft_tilda(t_line *line, char **arg, int i);
int				ft_reder(char **line, char *buf, int j, int i);
int				ft_red(t_line *lin, char **line, int i, int j);
int				ft_red2(t_line *lin, char **line, int i, int j);
int				ft_bred(t_line *lin, char **line, int i, int j);
int				ft_bred2(t_line *lin, char **line, int i, int j);
int				ft_export2(t_line *line, char **str, int i, int j);
int				ft_single(char **line, int i, int j);
void			ft_screen(char **line, int i);
void			ft_delone(t_line *line, int z);
void			ft_cleaner(t_line *line);
void			ft_dotcomma(t_line *line, char c);
char			**ft_cleaner3(char **line);
char			**ft_doublecpy(char **line);

char			**ft_omegado(char **arg, int i, int j);
char			**ft_omegaposle(char **arg, int i, int j);
char			***ft_omegasplit(char **arg, char c);
char			***ft_omegasplit2(char **arg, char c);
char			*ft_whynot(char *str);

int				ft_pipcount(char **str);
void			ft_pipinit(t_line *line);

void			ft_export_show(t_line *line);
void			ft_sort_expo(t_line *line);
void			ft_export_add(t_line *line, char **mal);
void			ft_export_create(t_line *line);
int				ft_chek_exp_add(t_line *line, char *str, char *s, int fl);
char			*ft_export_declare(t_line *line, char *s);

void			ft_free_exp(t_line *line, int kol);
void			ft_free_env(t_line *line, int kol);
void			ft_env_create(char **env, t_line *line);

void			ft_unset(t_line *line, char **mal);

void			ft_env_show(t_line *line);
void			ft_env_add(t_line *line, char *s);

void			ft_echo(t_line *line, char **mal);
void			ft_echo_add1(char **mal, t_line *line, int i, int fl);
void			ft_pwd(t_line *line);
void			ft_cd(char **mal, t_line *line);
void			ft_exc(t_line *line, char **mal);
void			ft_doublefree(void *str);
void			ft_doublefree2(void *str);
void			ft_triplefree(void *str);
char			**ft_splinter(char const *s1, char c);
void			ft_exit(t_line line);
void			ft_ctrl_break(int val);
void			ft_ctrl_d(int val);
void			ft_pars_dv(void *ar, t_line *line);
void			ft_pars_dv_pipe(void *ar, t_line *line);
int				ft_spaceskip(char *line);
int				ft_preerror(char *line);
int				ft_doperror(char c);

void			ft_exc_command(t_line *line, char **mal);
void			ft_exc_command1(t_line *line, char **mal, int pp[3][2], int i);

void			sig_quit1(int sig);
void			sig_quit2(int sig);
void			sig_clear1(int sig);
void			sig_clear2(int sig);
void			ft_env_up(t_line *line);
int				ft_env_levl(char **env);
void			ft_cd_error(char **mal, t_line *line);
void			ft_err_comm1(char *m, t_line *line);
void			ft_ero_exit_mal(t_line *line);
int				ft_path_chek(t_line *line, char *mal);

void			ft_add_minishell(t_line *line, char **mal);
void			ft_exit_dv(t_line *line, char **mal);
int				ft_chek_exp_add1(t_line *line, char *s);
void			ft_chek_exp_add0(t_line *line, char *s);

char			**ft_no_exe_path(t_line *line);
char			**ft_exe_path(t_line *line);
void			ft_pars_dv_pipe1(t_line *line,\
				char ***tmal, int i, int pp[100][2]);
void			ft_lit_exit(char *mal, t_line *line);
void			ft_exc_command1_3(t_line *line, char **mal);
void			ft_exc_command1_2(t_line *line, int pp[100][2], int m);
int				ft_exc_command1_1(t_line *line, char **mal, char **massi);
void			ft_add_minishell1_1(t_line *line, char **mal);
void			ft_add_minishell1_2(t_line *line, char **mal);
int				ft_add_minishell1_3(t_line *line,\
				char **mal, char **ma, char **sl);
void			ft_exc1_1(t_line *line, char **mal);
int				ft_exc1_2(t_line *line, char **mal, char **sline, char **massi);
void			ft_exc1_3(t_line *line, char **mal);
int				ft_pars_dv_pipe1_1(t_line *line, char **mal);
void			ft_ero_exit_mal(t_line *line);
int				ft_export_add_new_2(t_line *line, char **str);
int				ft_export_add_new(t_line *line, char *mal, char **stat);
void			ft_export_add_07(t_line *line, char *stat, char *mal, int m);
int				fs_chek_valid(t_line *line, char *mal);
void			ft_export_add_009(t_line *line, int m, char *stat);
int				ft_chek_ascii(char *tmp);
void			ft_for_wpersimm(char *m, t_line *line);
void			ft_dupsss(t_line *line);
void			ft_destroy(char **mal, int fd, pid_t pid, char **env);
void			ft_creat(char **mal, int fd, pid_t pid, char **env);
int				ft_checkline(char *line);
char			*ft_home(char **env);
void			ft_garb(char ***ar);
int				ft_getpid(char **env, char *str);
void			ft_init_cicle1(t_line *line, int i);
void			ft_init(t_line *line, char **argv, char **env);
void			ft_inits(t_line *line);
void			ft_last_main(t_line *line);
void			ft_global_cik(t_line *line);

#endif
