/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:27 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/22 10:31:49 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIB_H
# define MINILIB_H

// INCLUDES
# include "ft_printf/includes/ft_printf.h"
# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

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

// FUNCTIONS
/*----------- Construct token ------------*/
t_cmd		*execcmd(void);
t_cmd		*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*listcmd(t_cmd *left, t_cmd *right);

/*--------------- Parser -----------------*/
t_cmd		*parseline(char **ps, char *es, char **env);
t_cmd		*parseblock(char **ps, char *es, char **env);
t_cmd		*parseexec(char **ps, char *es, char **env, int argc);
t_cmd		*parsepipe(char **ps, char *es, char **env);
t_cmd		*parseredirs(t_cmd *cmd, char **ps, char *es, char **env);

/*------------- Parse utils ---------------*/
int			peek(char **ps, char *es, char *toks);
void		parseexec_error(t_execcmd *cmd, int argc);
t_execcmd	*init_cmd(t_cmd *ret);
t_cmd		*create_heredoc(t_cmd *cmd, char *file, char **env);

/*-------------- Get token ----------------*/
int			get_token(char **ps, char *es, char **token);

/*----------------- Main ------------------*/
void		crash_handler(char *str);
int			create_fork(void);

/*--------------- Expander ----------------*/
t_cmd		*expand(t_cmd *cmd, char **env);
char		*handle_env_var(char *s, char *es, char **env, int tok);
char		*handle_quotes(char *s, int i, int y, char **env);

/*------------ Expander utils -------------*/
char		*get_env_var(char *var, char **env);
void		switch_inquote(char *ps, int *inquote);

/*-------------- Builtins -----------------*/
char		**exportcmd(char **args, char **env);
char		*change_cwd(char *path, char *folder);

void		runcmd(t_cmd *cmd, char **env, int stdout_cpy);

void		pipex(t_cmd *cmd, int stdout_cpy, char **env);

void		free_cmd(t_cmd *cmd);

void		free_array(char **array);
#endif