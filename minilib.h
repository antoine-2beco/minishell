/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:27 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/05 13:18:17 by hle-roi          ###   ########.fr       */
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

t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);

t_cmd	*parseline(char **ps, char *es, char **env);
t_cmd	*parseblock(char **ps, char *es, char **env);
t_cmd	*parseexec(char **ps, char *es, char **env);
t_cmd	*parsepipe(char **ps, char *es, char **env);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char **env);

int		get_token(char **ps, char *es, char **token);
int		peek(char **ps, char *es, char *toks);

void	crash_handler(char *str);
int		create_fork(void);

t_cmd	*expand(t_cmd *cmd, char **env);
char	*handle_env_var(char *s, char *es, char **env);
char	*handle_quotes(char *s, int i, int y);

char	*get_env_var(char *var, char **env);
t_cmd	*create_heredoc(t_cmd *cmd, char *file, char **env);
#endif