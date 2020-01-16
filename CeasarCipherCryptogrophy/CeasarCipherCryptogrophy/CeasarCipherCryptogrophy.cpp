#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iterator>
#include <fstream>

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

std::string Decryption(std::string string, int key)
{
	key = (26 - key) % 26;
	return Encrypt(string, key);
}

std::vector<std::string> BruteDecrypt(std::string string)
{
	std::vector<std::string> poss;
	for (size_t i = 0; i < 26; i++)
	{
		poss.push_back(Decryption(string, i));
	}
	return poss;
}

std::vector<std::string> SplitString(std::string input, char split)
{
	if (input[0] != split)
	{
		input += split;
	}

	std::vector<std::string> words;

	std::string temp = "";
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] != split)
		{
			temp += input[i];
		}
		else
		{
			words.push_back(temp);
			temp = "";
		}
	}

	return words;
}


std::string SmartCracker(std::string string)
{
	auto words = SplitString(string, ' ');
	std::string word;
	int key = -1;
	for (size_t i = 0; i < words.size(); i++)
	{
		std::string temp = words[i];
		if (temp.size() < key)
		{
			key = temp.size();
			word = temp;
		}
	}

	std::string dict = DictionaryCheck(word);
	return word;
}

std::string DictionaryCheck(std::string word)
{
	auto perms = BruteDecrypt(word);
	std::string line;
	std::ifstream myfile("Dictionary.txt");
	if (myfile.is_open())
	{
		for (size_t i = 0; i < perms.size(); i++)
		{
			for (size_t j = 0; std::getline(myfile, line); j++)
			{
				if (perms[i] == line)
				{
					return line;
				}
			}

		}
	}
}

void LowerCase(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(),
		[](unsigned char c) { return std::tolower(c); });
}

int main()
{
	/*std::cout << "Put in a string to encrypt:";
	std::string text;
	std::getline(std::cin, text);
	LowerCase(text);
	std::cout << "Type in a key:";
	int key;
	std::cin >> key;
	std::cout << Encrypt(text, key) << "\n";

	std::cin.ignore();*/

	//std::cout << "Put in a string to decrypt:";
	//std::string decrypt;
	//std::getline(std::cin, decrypt);
	//LowerCase(decrypt);
	//std::cout << "Type in a key:";
	//int key2;
	//std::cin >> key2;
	//std::cout << Decryption(decrypt, key) << "\n";

	/*std::cout << "Put in a string to decrypt:";
	std::string decrypt2;
	std::getline(std::cin, decrypt2);
	LowerCase(decrypt2);
	auto poss = BruteDecrypt(decrypt2);
	for (size_t i = 0; i < 26; i++)
	{
		std::cout << poss[i] << "\n";
	}*/

	std::string text;
	std::getline(std::cin, text);
	std::cout << SmartCracker(text);
}