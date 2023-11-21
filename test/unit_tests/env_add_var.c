#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char **n;

	n = init_env(env);
	n = add_var(n, "test", "salut");
	if (!n)
		ft_printf("Error: can't remove test\n");
	n = add_var(n, "test2", "");
	if (!n)
		ft_printf("Error: can't remove test\n");
	int i = 0;
	while (n[i])
		i++;
	if (ft_strcmp(n[i - 2], "test=salut") != 0)
		ft_printf("Error: %s should be %s\n", n[i - 1], "test=salut");
	if (ft_strcmp(n[i - 1], "test2=") != 0)
		ft_printf("Error: %s should be %s\n", n[i - 1], "test2=");
}
