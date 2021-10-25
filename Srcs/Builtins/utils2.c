/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:26:11 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 16:49:33 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minishell.h>

int	name_strncmp(const char *name, const char *var, int len)
{
	int	res;

	res = ft_strncmp(name, var, len);
	if (!res)
	{
		if (var[len] == '=')
			return (0);
		res = var[len] - '=';
	}
	return (res);
}
