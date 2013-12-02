// HexBinDataConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <limits> // For char size
#include <cctype> // For isxdigit
#include <vector>
#include <iostream>
#include <type_traits>

void bytes_to_hex(const unsigned char* data, size_t length,	std::string& str)
{
	// Sanity check
	//static_assert<8 == CHAR_BIT>::valid_expression();

	// Clear output
	str.clear();

	// No data? Then we're done
	if (0 == length)
		return;

	// Output is twice the length of input length
	str.resize(length * 2, ' ');

	// Working with 4-bit nybbles, we can use the value as
	// index to character
	static const std::string hex_char = "0123456789abcdef";

	for (size_t i = 0; i < length; ++i)
	{
		// High nybble
		str[i<<1] = hex_char[(data[i] >> 4) & 0x0f];
		// Low nybble
		str[(i<<1) + 1] = hex_char[data[i] & 0x0f];
	}
}

// Encode data buffer to string of hexadecimal values
void bytes_to_hex(const std::vector<unsigned char>& data,	std::string& str)
{
	// Just wrapping the more "raw" function
	bytes_to_hex(&data[0], data.size(), str);
}



void hex_to_bytes(const std::string& str, 	std::vector<unsigned char>& data)
{
	// Sanity check
	//static_assert<8 == CHAR_BIT>::valid_expression();

	// Clear output
	data.clear();

	// No data? Then we're done
	if (str.empty())
		return;

	// Must be prepared that string can have odd number of
	// nybbles, in which case the first is treated like the low
	// nybble of the first byte
	size_t lengthOverflow = str.length() % 2;

	// This also affects the length of the data buffer we
	// allocate (need full  byte for nybble)
	const size_t length = lengthOverflow + str.length() / 2;
	data.resize(length);

	// Buffer for byte conversion
	static char buf[3];
	buf[2] = 0;
	// End of input
	char* pend = &buf[2];

	// Iterators for input and output
	size_t i = 0;
	size_t c = 0;

	// If the first nybble is a low, we'll do it separately
	if (1 == lengthOverflow)
	{
		buf[0] = '0';
		buf[1] = str[c++];
		unsigned char x = static_cast<unsigned char>
			(strtoul(buf, &pend, 16));

		// Parsing should stop at terminating zero
		if (pend != &buf[2])
		{
			std::string e = "Invalid character in hex string: \'";
			e += *(pend);
			e += "'";
			throw std::invalid_argument(e);
		}
		data[i++] = x;
	}

	// For each output byte, we use two input characters for
	// high and low nybble, respectively
	for (; i < length; ++i)
	{
		buf[0] = str[c++];
		// strtoul accepts initial whitespace or sign, we can't
		if (!isxdigit(buf[0]))
		{
			std::string e = "Invalid character in hex string: \'";
			e += buf[0];
			e += "'";
			throw std::invalid_argument(e);
		}

		buf[1] = str[c++];
		unsigned char x = static_cast<unsigned char>
			(strtoul(buf, &pend, 16));

		// Parsing should stop at terminating zero
		if (pend != &buf[2])
		{
			std::string e = "Invalid character in hex string: \'";
			e += *(pend);
			e += "'";
			throw std::invalid_argument(e);
		}

		data[i] = x;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//std::string s = "abcv";
	//printf("%c", s[1<<1]);


	const unsigned char vv[] = {1,23,108,20,25,32, 61};
	const	std::vector<unsigned char>  data (std::begin(vv), std::end(vv));  
	std::string str;

	bytes_to_hex(data, str);

	//std::cout << "hex: " << str;
	printf("hex: %s", str.c_str());

	return 0;
}

