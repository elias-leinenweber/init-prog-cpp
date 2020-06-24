#include <iostream>
#include <string>

char		code(char, int);
char		decale(char, char, int);
std::string	code(std::string, int);
std::string	decode(std::string, int);

int
main()
{
	std::string s = code("Fuyez manants", 4);

	std::cout << s << std::endl;
	std::cout << decode(s, 4) << std::endl;
}

char
decale(char c, char debut, int decalage)
{
	while (decalage < 0)
		decalage += 26;
	return debut + (((c - debut) + decalage) % 26);
}

char
code(char c, int d)
{
	if (c >= 'a' && c <= 'z')
		c = decale(c, 'a', d);
	else if (c >= 'A' && c <= 'Z')
		c = decale(c, 'A', d);
	return c;
}

std::string
code(std::string s, int d)
{
	for (char &c : s)
		c = code(c, d);
	return s;
}

std::string
decode(std::string s, int d)
{
	return code(s, -d);
}
