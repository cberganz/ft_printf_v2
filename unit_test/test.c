#include <stdio.h>

int	ft_printf(const char *s, ...) __attribute__ ((format (printf, 1, 2)));

int	main(void)
{
	char			c = 'c';
	char*			s = "Anystring";
	char*			p = "";
	int				d = -4242;
	int				i = 4242;
	unsigned int	u = 424242;
	int				x = 42424242;
	int				X = 42424242;

	int size = 0;
	while (size < 1)
	{
		ft_printf("1---------------------------------------------------------------------------------------------------100-------------------------------------------------------------------------------------------------200-------------------------------------------------------------------------------------------------300-------------------------------------------------------------------------------------------------400-------------------------------------------------------------------------------------------------500-------------------------------------------------------------------------------------------------600-------------------------------------------------------------------------------------------------700-------------------------------------------------------------------------------------------------800-------------------------------------------------------------------------------------------------900-------------------------------------------------------------------------------------------------1000------------------------------------------------------------------------------------------------1100------------------------------------------------------------------------------------------------");
		//ft_printf("s :%s#\n", s);
		//ft_printf("p :%p#\n", p);
		//ft_printf("d :%d#\n", -2147483648);
		//ft_printf("i :%i#\n", i);
		//ft_printf("u :%u#\n", u);
		//ft_printf("x :%x#\n", x);
		//ft_printf("X :%X#\n", X);
		//ft_printf("%% :%%#\n");
		//ft_printf("X :%X#\n", X);
		//ft_printf("X :#\n");
		size++;
	}
	//while(1);
	return 0;
}