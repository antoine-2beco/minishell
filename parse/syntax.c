/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:27:34 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/20 12:12:12 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

char	**s_get_args(char **ps, char *es, t_cmd **ret, t_data *data)
{
	char	*token;
	int		type;
	t_list	*tmp;
	t_list	*current;
	t_list	*list;

	list = NULL;
	current = NULL;
	tmp = NULL;
	while (!peek(ps, es, "|);"))
	{
		type = get_token(ps, es, &token, 0);
		if (type == 0)
			break ;
		if (type != 'a')
			return (ft_printf("Synthax error\n", 2), NULL);
		get_args_norm(&list, &current, &tmp, token);
		*ret = s_parseredirs(*ret, ps, es, data);
	}
	tmp = ft_lstnew(0);
	if (current)
		current->next = tmp;
	else
		list = tmp;
	return (convert_list(list));
}

int	check_syntax(char **ps, char *es, t_data *data)
{
	int		pid;
	int		status;
	int		ret;

	pid = create_fork();
	ret = 1;
	if (!pid)
	{
		free_cmd(s_parseline(ps, es, data));
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (ret)
		data->exitcode = ret;
	return (ret);
}
