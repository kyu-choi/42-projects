#include "Character.hpp"

Character::Character()
: name("default")
{
	int	i;

	i = 0;
	while (i < 4)
	{
		inventory[i] = 0;
		i++;
	}
}

Character::Character(std::string const& name)
: name(name)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		inventory[i] = 0;
		i++;
	}
}

Character::Character(const Character& other)
: name(other.name)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		inventory[i] = 0;
		i++;
	}
	*this = other;
}

Character& Character::operator=(const Character& other)
{
	int	i;

	i = 0;
	if (this != &other)
	{
		name = other.name;
		while (i < 4)
		{
			if (inventory[i])
			{
				delete	inventory[i];
				inventory[i] = 0;
			}
			if (other.inventory[i])
				inventory[i] = other.inventory[i]->clone();
			i++;
		}
	}
	return (*this);
}

Character::~Character()
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (inventory[i])
			delete	inventory[i];
		i++;
	}
}

std::string const& Character::getName() const
{
	return (name);
}

void	Character::equip(AMateria* m)
{
	int	i;

	if (!m)
		return ;
	i = 0;
	while (i < 4)
	{
		if(!inventory[i])
		{
			inventory[i] = m;
			return ;
		}
		i++;
	}	
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4)
		return ;
	inventory[idx] = 0;
}

void	Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= 4)
		return ;
	if (inventory[idx])
		inventory[idx]->use(target);
}
