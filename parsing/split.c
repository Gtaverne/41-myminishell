/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_sep(char c, t_a *a)
{
	int i;

	i = 0;
	while (a->sep[i])
	{
		if (c == a->sep[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_split_sh(t_a *a)
{
	int		i;
	int		k;
	int		counter;

	i = 0;
	k = 0;
	a->raw = malloc(sizeof(*a->raw) * (1 + 1000)); //revenir dessus;
	if (!a->raw)
		return ;
	a->backup = a->line;
	while (a->line[i])
	{
		a->sep = a->backup_sep;
		if (a->line[i] == ' ')
		{
			while (is_sep(a->line[i + 1], a) && a->line[i] == ' ') //on avance sur ' ' et on stop au sep diff de ' ' ou au dernier ' '
				(a->line)++;
		} 
		//ici on se retrouve donc systematiquement sur le premier element
		if (a->line[i] == ' ' || !is_sep(a->line[i], a)) // si c'est pas un sep, le sep est un espace;
		{
			a->raw[k].type = ' ';
			if (a->line[0] == ' ')
				(a->line)++;
			counter = 0;
			while (!is_sep(a->line[counter], a) && a->line[counter] != '\0')
				counter++;
			a->raw[k].str = malloc(sizeof(char) * (counter + 1));
			if (!a->raw[k].str)
			{
				ft_putstr_fd("Error\nMalloc Failed\n", 2);
				a->line = a->backup;
				exit (1); // fonction d'exit a coder
			}
			while (counter > 0)
			{
				a->raw[k].str[i] = a->line[0];
				i++;
				counter--;
				(a->line)++;
			}
			a->raw[k].str[i] = 0;
			i = 0;
		}
		else if (ft_strlen(a->line) > 1 && a->line[0] == '>' && a->line[1] == '>')
		{
			a->raw[k].type = '#';
			a->raw[k].str = malloc(sizeof(char) * 3);
			a->raw[k].str[0] = '>';
			a->raw[k].str[1] = '>';
			a->raw[k].str[2] = 0;
			(a->line)++;
			(a->line)++;
		}
		else if (a->line[i] == '|' || a->line[i] == ';' || a->line[i] == '<' || a->line[i] == '>')
		{
			a->raw[k].type = a->line[i];
			a->raw[k].str = malloc(sizeof(char) * 2);
			a->raw[k].str[0] = a->line[i];
			a->raw[k].str[1] = 0;
			(a->line)++;
		}
		else if (a->line[i] == '"' || a->line[i] == '\'')
		{
			a->raw[k].type = a->line[i];
			if (a->line[i] == '"')
			{
				(a->line)++;
				counter = 0;
				while (a->line[counter] != '"' && a->line[counter] != '\0')
					counter++;
				if (a->line[counter] == '\0')
				{
					ft_putstr_fd("Error\nYour you are missing an ending quote\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
				{
					ft_putstr_fd("Error\nMalloc Failed\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				while (counter > 0)
				{
					a->raw[k].str[i] = a->line[0];
					i++;
					counter--;
					(a->line)++;
				}
				a->raw[k].str[i] = 0;
				i = 0;
			}
			else //a->line[i] == '\''
			{
				(a->line)++;
				counter = 0;
				while (a->line[counter] != '\'' && a->line[counter] != '\0')
					counter++;
				if (a->line[counter] == '\0')
				{
					ft_putstr_fd("Error\nYour you are missing an ending quote\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
				{
					ft_putstr_fd("Error\nMalloc Failed\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				while (counter > 0)
				{
					a->raw[k].str[i] = a->line[0];
					i++;
					counter--;
					(a->line)++;
				}
				a->raw[k].str[i] = 0;
				i = 0;
			}
			(a->line)++; //on depasse la deuxieme quote
		}
		else
		{
			write(1, "@@@@@@@@@@", 10);
		}
		k++;
	}
	a->raw[k].str = 0;
	a->sep = a->backup_sep;
	a->line = a->backup;
}