#include "Brain.hpp"

Brain::Brain()
{
	int	i;

	std::cout << "Brain default constructor called" << std::endl;
	i = 0;
	while (i < 100)
	{
		ideas[i] = "";
		i++;
	}
}

Brain::Brain(const Brain& other)
{
	std::cout <<"Brain copy constructor called" << std::endl;
	*this = other;
}

Brain& Brain::operator=(const Brain& other)
{
	int	i;

	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &other)
	{
		i = 0;
		while (i < 100)
		{
			ideas[i] = other.ideas[i];
			i++;
		}
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

void	Brain::setIdea(int index, const std::string& idea)
{
	if (index >= 0 && index < 100)
		ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
	if (index >= 0 && index < 100)
		return (ideas[index]);
	return ("");
}
