#include "PhoneBook.hpp"

#include <iostream>
#include <iomanip>

PhoneBook::PhoneBook() : _count(0), _next(0) {}

void	PhoneBook::addContact(const Contact& c)
{
	_contact[_next] = c;
	_next = (_next + 1) % 8;
	if (_count < 8)
		_count++;
}

int	PhoneBook::count() const
{
	return (_count);
}

static	std::string formatCell(const std::string& s)
{
	if (s.length() <= 10)
		return (s);
	return (s.substr(0,9) + ".");
}

void	PhoneBook::printTable() const
{
	int	i;

	std::cout << std::setw(10) << "index" << "|"
		  << std::setw(10) << "first name" << "|"
		  << std::setw(10) << "last name" << "|"
		  << std::setw(10) << "nickname" << "\n";
	i = 0;
	while (i < _count)
	{
		std::cout << std::setw(10) << (i + 1) << "|"
			  << std::setw(10) << formatCell(_contact[i].first()) << "|"
			  << std::setw(10) << formatCell(_contact[i].last()) << "|"
			  << std::setw(10) << formatCell(_contact[i].nick()) << "\n";
		i++;
	}
}

bool	PhoneBook::printContactByIndex(int index) const
{
	Contact c;

	if (index < 1 || index > _count)
		return (false);
	c = _contact[index - 1];
	std::cout << "First name: " << c.first() << "\n";
	std::cout << "Last name: " << c.last() << "\n";
	std::cout << "Nickname: " << c.nick() << "\n";
	std::cout << "Phone number: " << c.phone() << "\n";
	std::cout << "Darkest secret: " << c.secret() << "\n";
	return (true);
}
