/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:09 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/15 11:38:38 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void	crash_handler(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	exit(1);
}

int	create_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		crash_handler("Fork");
	return (pid);
}

t_cmd	*parsecmd(char *s, char **env)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es, env);
	peek(&s, es, " ");
	if (s != es)
	{
		ft_printf("leftovers: %s\n", s);
		crash_handler("synthax\n");
	}
	return (cmd);
}

char	**cpy_env(char **pre_env)
{
	char	**env;
	int		i;

	i = 0;
	while (pre_env[i++])
		;
	env = malloc(i * sizeof(char *));
	if (!env)
		exit(EXIT_FAILURE);
	i = 0;
	while (pre_env[i])
	{
		env[i] = malloc(sizeof(pre_env[i]));
		if (!env[i])
			exit(EXIT_FAILURE);
		env[i] = pre_env[i];
		i++;
	}
	return (env);
}

void	print_cmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_listcmd	*lcmd;
	int			i;
	char		line[300];

	i = 0;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->args[0] == 0)
			crash_handler("Empty node \n");
		ft_printf("Exec node : ");
		while (ecmd->args[i])
			ft_printf("%s.", ecmd->args[i++]);
		ft_printf("\n");
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		ft_printf("Pipe \n");
		print_cmd(pcmd->left);
		print_cmd(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		ft_printf("Redir : %s, %d, %d\n", rcmd->file, rcmd->mode, rcmd->fd);
		print_cmd(rcmd->cmd);
	}
	else if (cmd->type == LIST)
	{
		lcmd = (t_listcmd *)cmd;
		ft_printf("List \n");
		print_cmd(lcmd->left);
		print_cmd(lcmd->right);
	}
	else if (cmd->type == HEREDOC)
	{
		rcmd = (t_redircmd *)cmd;
		ft_printf("Heredoc : %s, %d, %d\n", rcmd->file, rcmd->mode, rcmd->fd);
		dup2(rcmd->fd, STDIN_FILENO);
		close(rcmd->fd);
		scanf("%s", line);
		ft_printf("%s\n", line);
		print_cmd(rcmd->cmd);
	}
}

int	main(int argc, char **argv, char **pre_env)
{
	char	*line;
	char	**env;
	int		pid;
	int		stdout_cpy;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	stdout_cpy = dup(1);
	line = readline("\e[1m\x1b[36mMinishell ➤ \x1b[36m\e[m");
	env = cpy_env(pre_env);
	while (line > 0)
	{
		add_history(line);
		pid = create_fork();
		if (!pid)
			print_cmd(expand(parsecmd(line, env), env));
		wait(0);
		free(line);
		line = readline("\e[1m\x1b[36mMinishell ➤ \x1b[36m\e[m");
	}
}
