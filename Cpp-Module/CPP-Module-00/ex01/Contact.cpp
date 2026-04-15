#include "Contact.hpp"

Contact::Contact() : _filled(false) {}

void	Contact::set(const std::string& first,
			const std::string& last,
			const std::string& nick,
			const std::string& phone,
			const std::string& secret)
			{
				_first = first;
				_last = last;
				_nick = nick;
				_phone = phone;
				_secret = secret;
				_filled = true;
			}
bool	Contact::isFilled() const 
{
	return (_filled);
}

const	std::string& Contact::first() const
{
	return (_first);
}

const	std::string& Contact::last() const
{
	return (_last);
}

const	std::string& Contact::nick() const
{
	return (_nick);
}

const	std::string& Contact::phone() const
{
	return (_phone);
}

const	std::string& Contact::secret() const
{
	return (_secret);
}
