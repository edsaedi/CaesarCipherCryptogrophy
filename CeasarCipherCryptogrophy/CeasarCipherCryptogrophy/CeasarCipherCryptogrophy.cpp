#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

std::string Encrypt(std::string string, int key)
{
	std::string final = "";
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	key = key % 26;
	for (size_t i = 0; i < string.size(); i++)
	{
		int position = -1;
		for (size_t j = 0; j < alphabet.size(); j++)
		{
			if (string[i] == alphabet[j])
			{
				position = j;
				break;
			}
		}
		if (position == -1)
		{
			final += string[i];
		}
		else
		{
			final += alphabet[(key + position) % 26];
		}
	}
	return final;
}

int main()
{
	std::cout << "Put in a string to encrypt:";
	std::string text;
	std::getline(std::cin, text);
	std::transform(text.begin(), text.end(), text.begin(),
		[](unsigned char c) { return std::tolower(c); });
	std::cout << "Type in a key:";
	int key;
	std::cin >> key;
	std::cout << Encrypt(text, key);
	return 0;
}