#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char **n;

	n = init_env(env);
	n = add_var(n, "test", "salut");
	n = add_var(n, "test2", "fasfa");
	n = remove_var(n, "test");
	if (!n)
		ft_printf("Error: can't remove test\n");
	n = remove_var(n, "test2");
	if (!n)
		ft_printf("Error: can't remove test\n");
	int i = 0;
	while (n[i])
		i++;
	if (ft_strcmp(n[i - 2], env[i - 2]) != 0)
		ft_printf("Error: %s should be %s\n", n[i - 1], env[i - 2]);
	if (ft_strcmp(n[i - 1], env[i - 1]) != 0)
		ft_printf("Error: %s should be %s\n", n[i - 1], env[i - 1]);
}
