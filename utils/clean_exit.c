/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cleanstruct(t_a *a)
{
	int		i;

	i = -1;
	while (a->raw[++i].str)
		free(a->raw[i].str);
	free (a->raw);
	if (a->line)
		free(a->line);
	a->line = NULL;
	a->sep = SEPARATORS;
}

void	ft_exit_clean(t_a *a, char *str)
{
	(void)a;
	ft_putstr_fd(str, 2);
	ft_cleanstruct(a);
	//free everything
	exit (0);
}

void	set_backup_and_exit(t_a *a, char *str, int k)
{
	int i;

	i = 0;
	while (i < k) //on free tout ce qui a ete malloc dans la struct
	{
		free(a->raw[i].str);
		i++;
	}
	a->line = a->backup;
	ft_putstr_fd(str, 2);
	exit (1); // clean le reste de la structure a la suite
}
