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

// A class to store label data
class label
{
	private:
		string name;			// A name to identify the label
		unsigned short address;		// The memory address associated
						// with the label name
	public:
		label(string paramName, unsigned short paramAddress);
		label();
		bool isValid();
		string getName();
		unsigned short getAddress();
		~label();
};

// Label constructor
label::label(string paramName, unsigned short paramAddress)
{
	name	= paramName;
	address	= paramAddress;
}

// Label constructor
label::label()
{
}

// Returns true if the label has a valid identifying name
// Labels cannot be numbers of any form, including binary, hexadecimal, and decimal.
// This would interfere with the jump command ("JMP") and prevent
// jumping to specific addresses.
bool label::isValid()
{
	return !isNumeric(name);
}

// Return the label name
string label::getName()
{
	return name;
}

// Return the label address
unsigned short label::getAddress()
{
	return address;
}

// Label destructor
label::~label(){ }
