/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/23 11:44:04 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	*change_cwd(char *folder)
{
	char	*new_path;
	char	*temp;
	char	path[100];

	getcwd(path, sizeof(path));
	ft_printf("%s\n", path);
	if (path[0])
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, folder);
		free(temp);
	}
	else
		new_path = ft_strdup(folder);
	ft_printf("%s\n", new_path);
	chdir(new_path);
	return (new_path);
}
