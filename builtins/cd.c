/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/06/12 13:51:18 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	*change_cwd(char *folder)
{
	char	*new_path;
	char	*temp;
	char	path[100];

	getcwd(path, sizeof(path));
	ft_printf("%s\n", 1, path);
	if (path[0])
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, folder);
		free(temp);
	}
	else
		new_path = ft_strdup(folder);
	ft_printf("%s\n", 1, new_path);
	chdir(new_path);
	return (new_path);
}
