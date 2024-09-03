/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:27 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/03 14:12:41 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIB_H
# define MINILIB_H

// INCLUDES
# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define HEREDOC 5

# define MAXARGS 10

// STRUCTURES
typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**args;
}	t_execcmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		mode;
	int		fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_listcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

typedef struct s_data
{
	int		exitcode;
	int		exit;
	char	**env;
}	t_data;

// FUNCTIONS
/*----------- Construct token ------------*/
t_cmd		*execcmd(void);
t_cmd		*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*listcmd(t_cmd *left, t_cmd *right);

/*--------------- Parser -----------------*/
t_cmd		*parseline(char **ps, char *es, t_data *data);
t_cmd		*parseblock(char **ps, char *es, t_data *data);
t_cmd		*parseexec(char **ps, char *es, t_data *data);
t_cmd		*parsepipe(char **ps, char *es, t_data *data);
t_cmd		*parseredirs(t_cmd *cmd, char **ps, char *es, t_data *data);
char		**convert_list(t_list *list);

/*------------- Parse utils ---------------*/
int			peek(char **ps, char *es, char *toks);
t_execcmd	*init_cmd(t_cmd *ret);
t_cmd		*create_heredoc(t_cmd *cmd, char *file, t_data *data);
char		**get_args(char **ps, char *es, t_cmd **ret, t_data *data);

/*-------------- Get token ----------------*/
int			get_token(char **ps, char *es, char **token);

/*----------------- Main ------------------*/
void		crash_handler(char *str);
int			create_fork(void);

/*--------------- Expander ----------------*/
t_cmd		*expand(t_cmd *cmd, t_data *data);
char		*handle_quotes(char *s, t_data *data);
int			prompt_len(char *s, t_data *data, int i, int len);
char		*get_var(char *s);

/*------------ Expander utils -------------*/
char		*get_env_var(char **env, char *var);
void		switch_inquote(char *ps, int *inquote);

/*-------------- Builtins -----------------*/
int			exportcmd(char **args, t_data *data);
int			echocmd(char **args, t_data *data);
int			envcmd(char **args, t_data *data);
int			pwdcmd(char **args, t_data *data);
int			unsetcmd(char **args, t_data *data);
int			change_cwd(char *folder, t_data *data);
int			exitcmd(char **args, t_data *data);

void		runcmd(t_cmd *cmd, t_data *data);
int			is_builtin(char **cmd, t_data *data);

/*-------------- Free -----------------*/
void		free_cmd(t_cmd *cmd);
void		free_array(char **array);
void		free_list(t_list *list);

/*-------------- Signal -----------------*/
void		sig_interrupt(int num);
void		sig_interrupt_exec(int num);
void		disable_signal_print(void);
void		enable_signal_print(void);
void		rl_clear_history(void);
void		rl_replace_line(const char *str, int undo);

/*-------------- Exec -----------------*/
void		execution(char **cmd, t_data *data);
#endif