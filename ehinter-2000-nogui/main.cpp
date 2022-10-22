#include <iostream>
#include <string>
#include <iterator>
#include <Windows.h>

// if you couldn't tell, this program is a little widows dependent
// that is because I am 99% that anyone who needs this program is-
// -only working with windows but I may be wrong. If that is the case -
// -then make a fork. I will never use this on linux or mac, so I am not -
// -porting it :p (Sorry Linus)

// this program is quite niche and situational so error handling is not needed
// however, for sh*ts and giggles, it may be something to add for a more stable program

// If you are worried about emails being saved, or this being a malicous program,
// then please take a moment to look at the source code.
// This is a local program that saves a generated string to the clipboard.

// some busted binbows code for clipboard stuff
// tbh I don't get most of it myself
void setClipboard(const char* str)
{
	HGLOBAL hText;
	char* pText;
	hText = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, 100);
	pText = (char*)GlobalLock(hText);
	strcpy(pText, str);
	GlobalUnlock(hText); OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hText);
	CloseClipboard();
}

// more busted windows stuff
// this will basically return what has been saved to clipboard
char* getClipboard()
{
	OpenClipboard(NULL);
	HANDLE hint = GetClipboardData(CF_TEXT);
	CloseClipboard();
	LPVOID lptstr = GlobalLock(hint);
	return (char*)hint;
}


// this
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

// function for returning a user inputed email as a cpp string
std::string getEmail()
{
	std::cout << "Please enter an Email: ";
	std::string email{};
	std::cin >> email;
	return email;
}


// entry point :o
int main()
{
	std::string email_hint{ hideEmail(getEmail()) };
	setClipboard(email_hint.c_str());
	std::cout << getClipboard() << " Has been copied to the clipboard!" << '\n';
}
