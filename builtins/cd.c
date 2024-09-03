/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/09/03 14:55:06 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	change_cwd(char *folder, t_data *data)
{
	char	*new_path;
	char	*temp;
	char	path[100];

	getcwd(path, sizeof(path));
	if (path[0])
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, folder);
		free(temp);
	}
	else
		new_path = ft_strdup(folder);
	if (chdir(new_path) == -1)
	{
		data->exitcode = 1;
		perror("minishell");
		return (1);
	}
	free(new_path);
	data->exitcode = 0;
	return (1);
}
