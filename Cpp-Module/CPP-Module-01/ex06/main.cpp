#include "Harl.hpp"

static	int	getLevelIndex(std::string level)
{
	std::string levels[4];
	int	i;

	levels[0] = "DEBUG";
	levels[1] = "INFO";
	levels[2] = "WARNING";
	levels[3] = "ERROR";
	i = 0;
	while (i < 4)
	{
		if (levels[i] == level)
			return (i);
		i++;
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	Harl harl;
	int	level;

	if (argc != 2)
	{
		std::cout << "Usage: ./harlFilter <level>" << std::endl;
		return (1);
	}
	level = getLevelIndex(argv[1]);
	switch (level)
	{
		case 0:
		{
			harl.complain("DEBUG");
			harl.complain("INFO");
			harl.complain("WARNING");
			harl.complain("ERROR");
			break ;
		}
		case 1:
		{
			harl.complain("INFO");
			harl.complain("WARNING");
			harl.complain("ERROR");
			break ;
		}
		case 2:
		{
			harl.complain("WARNING");
			harl.complain("ERROR");
			break ;
		}	
		case 3:
			harl.complain("ERROR");
			break;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]"
				  << std::endl;
	}
	return (0);
}
