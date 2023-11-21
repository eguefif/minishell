#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;

	char **new_env;

	new_env = init_env(env);
	int	j = 0;
	while (env[j])
		j++;

	int	z = 0;
	while (env[z])
		z++;
	if (z != j)
	{
		ft_printf("Error: size different\n");
		return (0);
	}
	int	i = 0;
	while (i < j)
	{
		if (ft_strcmp(new_env[i], env[i]) != 0)
			ft_printf("Error at index = %d\n", i);
		i++;
	}
}
