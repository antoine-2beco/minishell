/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:40 by hle-roi           #+#    #+#             */
/*   Updated: 2024/04/09 15:22:24 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

char	*change_cwd(char *path, char *folder)
{
	char	*new_path;
	char	*temp;

	if (path)
	{
		temp = ft_strjoin(path, "/");
		new_path = ft_strjoin(temp, folder);
		free(path);
		free(temp);
	}
	else
		new_path = ft_strdup(folder);
	chdir(new_path);
	return (new_path);
}
