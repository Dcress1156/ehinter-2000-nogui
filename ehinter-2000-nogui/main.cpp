#include <iostream>
#include <string>
#include <iterator>

std::string hideEmail(std::string email)
{
	// uses the size of the email as the initializer for emailLength
	const int emailLength{ static_cast<int>(std::size(email)) };
	const char hintChar{ '*' };

	// some variables for iterating through the email string
	const int domainIndex{ static_cast<int>(email.find("@")) };
	constexpr int id1{ 1 };
	constexpr int id2{ 2 };

	// going to generate the email hint
	for (int index{ id2 }; index < domainIndex - id1; ++index)
	{
		email[index] = hintChar;
	}

	return email;
}

std::string getEmail()
{
	std::cout << "Please enter an Email: ";
	std::string email{};
	std::cin >> email;
	return email;
}

int main()
{
	std::string email_hint{ hideEmail(getEmail()) };

	std::cout << email_hint;
}