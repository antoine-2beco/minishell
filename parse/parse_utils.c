/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:11:17 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/17 12:55:06 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	**convert_list(t_list *list)
{
	char	**args;
	t_list	*current;
	t_list	*tmp;
	int		argc;

	argc = 0;
	args = malloc(sizeof(char *) * ft_lstsize(list));
	current = list;
	while (current)
	{
		args[argc++] = current->content;
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(current);
	return (args);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ps = s;
	return ((*s && ft_strchr(toks, *s)));
}

t_execcmd	*init_cmd(t_cmd *ret)
{
	t_execcmd	*cmd;

	cmd = (t_execcmd *)ret;
	cmd->args = malloc(sizeof(char *) * (MAXARGS));
	if (!cmd->args)
		crash_handler("Malloc error\n");
	return (cmd);
}

void	get_args_norm(t_list **list, t_list **current,
	t_list **tmp, char *token)
{
	if (!*list)
	{
		*list = ft_lstnew(token);
		*current = *list;
	}
	else
	{
		*tmp = ft_lstnew(token);
		(*current)->next = *tmp;
		*current = *tmp;
	}
}

char	**get_args(char **ps, char *es, t_cmd **ret, t_data *data)
{
	char	*token;
	int		type;
	t_list	*tmp;
	t_list	*current;
	t_list	*list;

	list = NULL;
	current = NULL;
	tmp = NULL;
	token = NULL;
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token);
		if (type == 0)
			break ;
		if (type != 'a')
			return (ft_printf("Synthax error\n", 2), NULL);
		get_args_norm(&list, &current, &tmp, token);
		*ret = parseredirs(*ret, ps, es, data);
	}
	tmp = ft_lstnew(0);
	if (current)
		current->next = tmp;
	else
		list = tmp;
	return (convert_list(list));
}
