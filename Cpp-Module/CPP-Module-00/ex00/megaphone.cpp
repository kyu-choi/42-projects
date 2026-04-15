#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int	i;
	int	j;
	unsigned char c;

	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			c = static_cast<unsigned char>(argv[i][j]);
			std::cout << static_cast<char>(std::toupper(c));
			j++;
		}
		i++;
	}
	std::cout << std::endl;
	return (0);
}
