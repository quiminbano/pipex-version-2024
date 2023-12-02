#include <stdio.h>
#include "parser.h"

int	main(void)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_parser("   Hola Ossi  \\\"   \"Como   \\\"  te    va?\" \"\" Espero que super");
	while (str[i])
	{
		printf("%s\n", str[i]);
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}