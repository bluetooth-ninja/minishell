/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlucilla <vlucilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:23:46 by wgaunt            #+#    #+#             */
/*   Updated: 2021/10/26 16:24:09 by vlucilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_digits(char *str)
{
	if (str[0] == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	do_exit(char **arr)
{
	int	nb;

	nb = 1;
	while (arr[nb])
		nb++;
	if (nb == 1)
		exit(sh_exit);
	if (nb == 2 && is_digits(arr[1]))
		exit(ft_atoi(arr[1]));
	if (nb >= 2 && !is_digits(arr[1]))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		sh_exit = 255;
		exit(sh_exit);
	}
	if (nb > 2)
	{
		if (is_digits(arr[1]))
		{
			printf("%s", "exit: too many arguments\n");
			sh_exit = 1;
			return (1);
		}
		else
			exit(0);
	}
	return (0);
}
