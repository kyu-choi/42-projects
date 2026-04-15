#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
	private:
		std::string	_first;
		std::string	_last;
		std::string	_nick;
		std::string	_phone;
		std::string	_secret;
		bool	_filled;
	public:
		Contact();
	void	set(const std::string& first,
			const std::string& last,
			const std::string& nick,
			const std::string& phone,
			const std::string& secret);
	bool	isFilled() const;
	const	std::string& first() const;
	const	std::string& last() const;
	const	std::string& nick() const;
	const	std::string& phone() const;
	const	std::string& secret() const;
};

#endif
