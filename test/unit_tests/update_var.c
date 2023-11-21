#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char **n;

	n = init_env(env);
	n = add_var(n, "test", "salut");
	n = update_var(n, "test", "truc");
	char *test = ms_getenv(n, "test");
	if (ft_strcmp(test, "truc") != 0)
		ft_printf("Error: %s should be %s\n", test, "trucc");
}
