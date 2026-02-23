#include "vbc.h"

char	*g_ptr;

void	error_exit(char c)
{
	if (c == '\0')
		printf("Unexpected end of input\n");
	else
		printf("Unexpected token '%c'\n", c);
	exit (1);
}

int	use_terms(void)
{
	if (*g_ptr == '(')
	{
		g_ptr++;
		int	res = add_up();
		if (*g_ptr != ')')
			error_exit(*g_ptr);
		g_ptr++;
		return (res);
	}
	else if (isdigit(*g_ptr))
	{
		int	res = *g_ptr - '0';
		g_ptr++;
		return (res);
	}
	error_exit(*g_ptr);
	return (0);
}

int	make_multi(void)
{
	int	res = use_terms();

	while (*g_ptr == '*')
	{
		g_ptr++;
		res *= use_terms();
	}
	return (res);
}

int	add_up(void)
{
	int	res = make_multi();

	while (*g_ptr == '+')
	{
		g_ptr++;
		res += make_multi();
	}
	return (res);
}

int	main(int ac, char **av)
{
	if (!av || !av[1] || av[1][0] == '\0')
		return (1);
	g_ptr = av[1];

	int	res = add_up();
	if (*g_ptr != '\0')
		error_exit(*g_ptr);
	printf("%d\n", res);
}