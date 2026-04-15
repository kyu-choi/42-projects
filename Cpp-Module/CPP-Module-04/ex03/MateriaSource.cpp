#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	int	i;

	i = 0;
	while (i < 4)
	{
		storage[i] = 0;
		i++;
	}
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		storage[i] = 0;
		i++;
	}
	*this = other;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	int	i;

	if (this != &other)
	{
		i = 0;
		while (i < 4)
		{
			if (storage[i])
			{
				delete	storage[i];
				storage[i] = 0;
			}
			if (other.storage[i])
				storage[i] = other.storage[i]->clone();
			i++;
		}
		
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (storage[i])
			delete	storage[i];
		i++;
	}
}

void	MateriaSource::learnMateria(AMateria* m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < 4)
	{
		if (!storage[i])
		{
			storage[i] = m->clone();
			delete	m;
			return ;
		}
		i++;
	}
	delete	m;
}

AMateria*	MateriaSource::createMateria(std::string const& type)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (storage[i] && storage[i]->getType() == type)
			return (storage[i]->clone());
		i++;
	}
	return (0);
}
