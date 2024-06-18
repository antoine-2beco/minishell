/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beco <ade-beco@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:12:01 by ade-beco          #+#    #+#             */
/*   Updated: 2024/06/12 14:07:53 by ade-beco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minilib.h"

int	exitcmd(char **args)
{
	if (!args[1])
		exit(1);
	else
		exit(ft_atoi(args[1]));
}