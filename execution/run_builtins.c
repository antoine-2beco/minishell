/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:24:47 by hle-roi           #+#    #+#             */
/*   Updated: 2024/05/14 13:18:20 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilib.h"

int	is_builtin(char **cmd, char **env)
{
	if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0]) + 1))
		env = exportcmd(cmd, env);
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0]) + 1))
		return (echocmd(cmd));
	else
		return (0);
	return (1);
}
