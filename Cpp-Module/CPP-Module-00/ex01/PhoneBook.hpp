#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact _contact[8];
		int	_count;
		int	_next;
	public:
		PhoneBook();
	void	addContact(const Contact& c);
	void	printTable() const;
	bool	printContactByIndex(int index) const;
	int	count() const;
};
#endif
