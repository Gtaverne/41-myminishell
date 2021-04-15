#include "../includes/minishell.h"

void	ft_initstruct(t_a *a)
{
	a->sep = " '\"|;><";
<<<<<<< HEAD
	a->nav = 0;
	a->nline = 0;
	a->h = malloc(sizeof(char *) * 1000);
=======
	a->backup_sep = a->sep;
>>>>>>> 672537cdf16ac1caaa2f86948fa64df768166daa
}

void	ft_cleanstruct(t_a *a)
{
	int		i;

	i = -1;
	while (a->raw[++i].str)
		free(a->raw[i].str);
	free (a->raw);
	a->sep = " '\"|;><";
}

void	ft_putnbr_fd(int n, int fd)
{
	long nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}