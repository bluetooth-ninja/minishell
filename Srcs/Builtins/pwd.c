/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wgaunt <wgaunt@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:51 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/24 16:50:21 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(void)
{
	char	*path;

	path = getcwd(0, 0);
	printf("%s\n", path);
	free(path);
	return (0);
}
