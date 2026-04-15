#include "Zombie.hpp"

int	main(void)
{
	int	N;
	Zombie* horde;
	int	i;

	N = 5;
	horde = zombieHorde(N, "Horde");
	i = 0;
	while (i < N)
	{
		horde[i].announce();
		i++;
	}
	delete[] horde;
}
