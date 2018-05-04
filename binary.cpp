/*****************Convert string to binary code****************/

/*Me no known how to divide by zero, but me know how to divide cookies into crumbs*/
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <bitset>
#include <conio.h>
#include <Windows.h>

#define UTIL_PRINT(st) do { std::cout << st; } while(false)

template <class T> void anykey(const T& msg) 
{ UTIL_PRINT(msg); std::cin.get(); }

void Print_char(const short begin, const short end)
{
	size_t k = 0;
	for (short i = begin; i <= end; ++i) 
	{
		std::cout << std::setw(4) << i << '#' << static_cast<char>(i);
		++k;
		if (k % 10 == 0) 
			std::cout << std::endl;
	}
}
int Text_to_Binary()
{
	std::string binary, str;
	std::cout << "Enter string: "; 
	getline(std::cin, str);
	for (size_t i = 0; i < str.length();++i)
	{
		int x = static_cast<int>(str[i]);
		binary += std::bitset<8>(x).to_string()+ ' ';
	}
	std::cout << std::endl << "converted string is: " <<'\"' << binary.c_str() << '\"' << std::endl;

	/****************writing to clipboard************************************/
	if(!OpenClipboard(0)) {
		std::cout << "Failed to write text to clipboard\n";		return -1;
	}
	else {
		size_t len;
		HGLOBAL hMem;
		len = binary.length();
		hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hMem),binary.c_str(), len);
		GlobalUnlock(hMem);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
		std::cout<<"\n************converted string has written to clipboard************\n";
	}
	anykey("\nPress Enter to continue...\n");
	return 1;
}

int Binary_to_Text()
{
	/*****************reading from clipboard*****************************/
	std::cout << "\n************reading from clipboard************\n";
	std::string fromClipboard, binary;
	if (!OpenClipboard(0)) {
		std::cout << "Failed to read text from clipboard\n";	return 1;
	}
	HANDLE hData = GetClipboardData(CF_TEXT);
	char* chBuffer = static_cast<char*>(GlobalLock(hData));
	fromClipboard = chBuffer;
	GlobalUnlock(hData);
	CloseClipboard();
	fromClipboard.erase(std::remove(fromClipboard.begin(), fromClipboard.end(), ' '),fromClipboard.end());
	bool isDigit = true;
	for (size_t i = 0; i < fromClipboard.length(); ++i)
		if (!isdigit(fromClipboard[i])) {
			isDigit = false;	break;
		}
	if (!isDigit) 
	{
		std::cout << "Failed to read text from clipboard\n";
		std::cout << "text in buffer !-- "<< fromClipboard << " --!" << std::endl;
	} 
	else 
	{
		binary = fromClipboard;
		unsigned long decimal;
		std::cout << "encoded string is: ";
		while (binary[0] != '\0')
		{
			decimal = std::bitset<8>(binary).to_ulong();
			std::cout << char(decimal);
			//подсчитать кол-во символов для удаления
			binary = binary.erase(0,8);
		}
	}
	anykey("\nPress Enter to continue...\n");
	return 1;
}

inline void Show_symbol_table()
{
	Print_char(24, 255);
	anykey("\nPress Enter to continue...\n");
}

void Griting()
{
	std::cout << "*******************Main menu*******************\n";
	std::cout <<" 1. Text to binary\n 2. Binary to text(from clipboard only)\n 3. Show current symbol table\n 4. Exit\n";
}

int main(int argc, char *argv[])
{
	system("color 09");		
	while(true)
	{
		system("cls");
		Griting();
		char ans;
		ans = _getch();
		switch (ans)
		{
			case '1': Text_to_Binary();	break;
			case '2': Binary_to_Text();	break;
			case '3': Show_symbol_table();	break;
			case '4': exit(0);
		}
	}
	anykey("\nPress Enter to exit...\n");;
	return 0;
}

