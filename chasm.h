#include <string>		// For the string class
#include <sstream>		// For conversions from string to number
using namespace std;

/*
Copyright (c) 2010-2016 Matthew Mikolay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

// Returns true if a given character is whitespace
bool isWhitespace(char letter)
{
	return (letter == ' ' || letter == '\t');
}

// Converts a given character to uppercase if the input is in lowercase
char toUpper(char letter)
{
	if(letter >= 0x61 && letter <= 0x7A)
		return (letter - 0x20);
	return letter;
}

// Writes to the screen that an error occured
bool error(string filename, unsigned int lineNumber, string message)
{
	cout << filename << ":" << lineNumber << ":" << message << endl;
	return true;
}

// Try to add an argument to the array of arguments, making sure no overflow occurs
bool addArg(string &input, string (&args)[4], unsigned char &number)
{
	// Make sure the maximum number of arguments is not already in the array
	if(number >= 4)
		return false;

	// Store the word, increment the counter, and clear the contents of word
	args[number] = input;
	number++;
	input = "";
	return true;
}

// Returns true if the given string is a number
bool isNumeric(string input)
{
	if(input.at(0) == '#' || input.at(0) == '$')
		return true;

	// Loop through the contents of the string, looking for non-numeric characters
	for(unsigned int i = 0; i < input.length(); i++)
	{
		if(input.at(i) < '0' || input.at(i) > '9')
			return false;
	}
	
	return true;
}

// Convert a given string to a register number
bool strToRegister(string input, unsigned char &output)
{
	if(input.length() == 2 && input.at(0) == 'V')
	{
		// Is the register a number register?
		if(input.at(1) >= 'A' && input.at(1) <= 'F')
		{
			output = input.at(1) - 55;
			return true;
		}
		// Is the register a letter register?
		if(input.at(1) >= '0' && input.at(1) <= '9')
		{
			output = input.at(1) - '0';
			return true;
		}
	}
	return false;
}

// Convert a given string to a 4-bit number (nibble)
bool strToNibble(string input, unsigned char &output)
{
	if(input.length() > 0)
	{
		// Process the input as hexadecimal
		if(input.at(0) == '#')
		{
			unsigned int result = 0;
			// Remove the hash
			input = input.substr(1, input.length());
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 4-bit number
			if((iss >> hex >> result).fail() || result >= 16)
				return false;

			output = result;
			return true;
		}

		// Process the input as binary
		if(input.at(0) == '$')
		{
			unsigned int result = 0;
			// Loop through the string computing the binary number
			for(unsigned char i = input.length() - 1; i > 0; i--)
			{
				if(input.at(i) == '1')
					result += 1 << (input.length() - 1 - i);
				else if(input.at(i) != '0' && input.at(i) != '.')
					return false;
			}

			// Make sure the result is a 4-bit number
			if(result >= 16)
				return false;

			output = result;
			return true;
		}

		// Try to process the input as decimal
		else
		{
			unsigned int result = 0;
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 4-bit number
			if((iss >> dec >> result).fail() || result >= 16)
				return false;

			output = result;
			return true;
		}
	}
	return false;
}

// Convert a given string to an 8-bit number (byte)
bool strToByte(string input, unsigned char &output)
{
	if(input.length() > 0)
	{
		// Process the input as hexadecimal
		if(input.at(0) == '#')
		{
			unsigned int result = 0;
			// Remove the hash
			input = input.substr(1, input.length());
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is an 8-bit number
			if((iss >> hex >> result).fail() || result >= 256)
				return false;

			output = result;
			return true;
		}

		// Process the input as binary
		if(input.at(0) == '$')
		{
			unsigned int result = 0;
			// Loop through the string computing the binary number
			for(unsigned char i = input.length() - 1; i > 0; i--)
			{
				if(input.at(i) == '1')
					result += 1 << (input.length() - 1 - i);
				else if(input.at(i) != '0' && input.at(i) != '.')
					return false;
			}

			// Make sure the result is an 8-bit number
			if(result >= 256)
				return false;

			output = result;
			return true;
		}

		// Try to process the input as decimal
		else
		{
			unsigned int result = 0;
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is an 8-bit number
			if((iss >> dec >> result).fail() || result >= 256)
				return false;

			output = result;
			return true;
		}
	}
	return false;
}

// Convert a given string to a 12-bit number
bool strTo12Bit(string input, unsigned short &output)
{
	if(input.length() > 0)
	{
		// Process the input as hexadecimal
		if(input.at(0) == '#')
		{
			unsigned int result = 0;
			// Remove the hash
			input = input.substr(1, input.length());
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 12-bit number
			if((iss >> hex >> result).fail() || result >= 4096)
				return false;

			output = result;
			return true;
		}

		// Process the input as binary
		if(input.at(0) == '$')
		{
			unsigned int result = 0;
			// Loop through the string computing the binary number
			for(unsigned char i = input.length() - 1; i > 0; i--)
			{
				if(input.at(i) == '1')
					result += 1 << (input.length() - 1 - i);
				else if(input.at(i) != '0' && input.at(i) != '.')
					return false;
			}

			// Make sure the result is a 12-bit number
			if(result >= 4096)
				return false;

			output = result;
			return true;
		}

		// Try to process the input as decimal
		else
		{
			unsigned int result = 0;
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 12-bit number
			if((iss >> dec >> result).fail() || result >= 4096)
				return false;

			output = result;
			return true;
		}
	}
	return false;
}

// Convert a given string to a 16-bit number
bool strToWord(string input, unsigned short &output)
{
	if(input.length() > 0)
	{
		// Process the input as hexadecimal
		if(input.at(0) == '#')
		{
			unsigned int result = 0;
			// Remove the hash
			input = input.substr(1, input.length());
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 16-bit number
			if((iss >> hex >> result).fail() || result >= 65536)
				return false;

			output = result;
			return true;
		}

		// Process the input as binary
		if(input.at(0) == '$')
		{
			unsigned int result = 0;
			// Loop through the string computing the binary number
			for(unsigned char i = input.length() - 1; i > 0; i--)
			{
				if(input.at(i) == '1')
					result += 1 << (input.length() - 1 - i);
				else if(input.at(i) != '0' && input.at(i) != '.')
					return false;
			}

			// Make sure the result is a 16-bit number
			if(result >= 65536)
				return false;

			output = result;
			return true;
		}

		// Try to process the input as decimal
		else
		{
			unsigned int result = 0;
			// Attempt to convert the string to a number
			istringstream iss(input);

			// Make sure the conversion did not fail and the result is a 16-bit number
			if((iss >> dec >> result).fail() || result >= 65536)
				return false;

			output = result;
			return true;
		}
	}
	return false;
}
