#include "PhoneBook.hpp"
#include "Contact.hpp"

#include <iostream>
#include <string>

static	bool readNonEmptyLine(const std::string& prompt, std::string& out)
{
	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, out))
			return (false);
		if (!out.empty())
			return (true);
		std::cout << "Field cannot be empty.\n";
	}
}

static	bool readContact(Contact& c)
{
	std::string first, last, nick, phone, secret;

	if (!readNonEmptyLine("First name: ", first))
		return (false);
	if (!readNonEmptyLine("Last name: ", last))
		return (false);
	if (!readNonEmptyLine("Nickname: ", nick))
		return (false);
	if (!readNonEmptyLine("Phone number: ", phone))
		return (false);
	if (!readNonEmptyLine("Darkest secret: ", secret))
		return (false);
	c.set(first, last, nick, phone, secret);
	return (true);
}

static	bool parseIndex(const std::string& s, int& outIndex)
{
	int	i;
	int	size;

	if (s.empty())
		return (false);
	i = 0;
	size = s.size();
	while (i < size)
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	outIndex = 0;
	i = 0;
	while (i < size)
	{
		outIndex = outIndex * 10 + (s[i] - '0');
		i++;
	}
	return (true);
}

int	main(void)
{
	PhoneBook	pb;
	std::string	cmd, idxStr;
	Contact	c;
	int	idx;

	std::cout << "Commands: ADD, SEARCH, EXIT\n";
	while (true)
	{
		std::cout << ">";
		if (!std::getline(std::cin, cmd))
		{
			std::cout << "\nEOF received. Exiting.\n";
			break;
		}
		if (cmd == "ADD")
		{
			if (!readContact(c))
			{
				std::cout << "\nEOF received. Exiting.\n";
				break;
			}
			pb.addContact(c);
			std::cout << "Contact added.\n";
		}
		else if (cmd == "SEARCH")
		{
			if (pb.count() == 0)
			{
				std::cout << "PhoneBook is empty.\n";
				continue;
			}
			pb.printTable();
			std::cout << "Enter index: ";
			if (!std::getline(std::cin, idxStr))
			{
				std::cout << "\nEOF received. Exiting.\n";
				break;
			}
			if (!parseIndex(idxStr, idx) || !pb.printContactByIndex(idx))
				std::cout << "Invalid index.\n";
		}
		else if (cmd == "EXIT")
			break;
		else if (cmd.empty())
			continue;
		else
			std::cout << "Unknown command. Use: ADD, SEARCH, EXIT\n";
	}
	return (0);
}
