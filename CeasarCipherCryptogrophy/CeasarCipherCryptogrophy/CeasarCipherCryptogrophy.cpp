#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iterator>
#include <fstream>
#include <filesystem>
#include <array>
#include <unordered_set>

enum class Languages {
	English,
	Spanish,
	French
};

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

std::string DictionaryCheck(std::string text, Languages language)
{
	/*auto currDir = std::filesystem::current_path();
	std::cout << currDir << std::endl;*/

	std::ifstream myfile;
	if (language == Languages::English)
	{
		myfile = std::ifstream("Dictionary.txt");
	}
	else if (language == Languages::French)
	{
		myfile = std::ifstream("francais.txt");
	}
	else
	{
		myfile = std::ifstream("espanol.txt");
	}
	std::string line;
	std::unordered_set<std::string> wordsDictionary;

	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			wordsDictionary.insert(line);
		}
	}

	auto perms = BruteDecrypt(text);
	for (size_t i = 0; i < perms.size(); i++)
	{
		auto words = SplitString(perms[i], ' ');
		for (size_t j = 0; j < words.size(); j++)
		{
			if (words[j].size() >= 4)
			{
				if (wordsDictionary.find(words[j]) != wordsDictionary.end())
				{
					return perms[i];
				}
			}
		}
	}

	return "";
	//auto textWord = SplitString(text, ' ');


	//for (size_t n = 0; n < textWord.size(); n++)
	//{
	//	auto perms = BruteDecrypt(textWord[n]);
	//	for (size_t i = 0; i < perms.size(); i++)
	//	{
	//		for (size_t j = 0; j < words.size(); j++)
	//		{
	//			if (words.find(perms[i]) != words.end())
	//				//if (std::find(words.begin(), words.end(), word) != words.end())
	//			{
	//				return perms[i];
	//			}
	//		}
	//		/*int z = {};
	//		while (std::getline(myfile, line))
	//		{
	//			if (perms[i] == line)
	//			{
	//				return line;
	//			}
	//			z++;
	//		}*/
	//	}
	//}
}

std::string DictionaryLanguageCheck(std::string text)
{
	std::string eng = DictionaryCheck(text, Languages::English);
	std::string sp = DictionaryCheck(text, Languages::Spanish);
	std::string fr = DictionaryCheck(text, Languages::French);
	if (eng != "")
	{
		std::cout << "English \n";
		return eng;
	}
	else if (sp != "")
	{
		std::cout << "Spanish \n";
		return sp;
	}

	else if (fr != "")
	{
		std::cout << "French \n";
		return fr;
	}
	return "";
}

void LowerCase(std::string& string)
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
	LowerCase(text);
	std::cout << DictionaryLanguageCheck(text);
}