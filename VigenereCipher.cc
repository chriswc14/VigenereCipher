/*	Notes:
	Decode causes a segmentation fault
	Needs to be able to use lowercase letters
	
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int search (char ch);
void encode (string key);
void decode (string key);

char caesar [26][26] = {{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'},
			{'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A'},
			{'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B'},
			{'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C'},
			{'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D'},
			{'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E'},
			{'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F'},
			{'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G'},
			{'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H'},
			{'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I'},
			{'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J'},
			{'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K'},
			{'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L'},
			{'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M'},
			{'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N'},
			{'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'},
			{'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P'},
			{'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q'},
			{'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R'},
			{'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'},
			{'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T'},
			{'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'},
			{'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V'},
			{'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W'},
			{'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X'},
			{'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y'}};

int main (int argc, char *argv[]) {
	string key = "";

	// Check the number of parameters
    	if (argc < 2) {
        	// Tell the user how to run the program
        	std::cerr << "Usage: " << argv[0] << " <option(s)> KEY\n"
              		  << "Options:\n"
              		  << "\t-d, --Decode\tDecode a ciphertext to plaintext.\n"
              		  << "\t-e, --Encode\tEncode plaintext to ciphertext.\n"
              		  << std::endl;
    	}
    	
	// Determine option
    	for (int i = 1; i < argc; i++) {
		// Decode option for program
		if (!strcmp (argv[i], "-d")) {
			for (i = i + 1; i < argc; i++) {
				key = key + argv[i];
			}
			decode(key);
		}

		// Encode option for program
		if (!strcmp (argv[i], "-e")) {
			for (i = i + 1; i < argc; i++) {
				key = key + argv[i];
			}
			encode(key);
		}
    	}
}


// Searches array for specified character
int search (char ch) {
	char search [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	int size = strlen(search);

	for(int i = 0; i < size; i++) {	
		if (search[i] == ch){
			return i;
		}
	}

	return -1;
}

// Encode text with specified key
void encode (string key) {
	int textValue;
	int keyValue;
	string text;
	
	cin >> text;
	cout << key << endl;

	int textSize = text.size();
	int keySize = key.size();

	// Searches for the values to input for 2D array
	for(int i = 0; i < textSize; i++) {
		textValue = search(text[i]);
		
		if (i >= keySize) {
			keyValue = search(key[(i-keySize)]);
		} else {
			keyValue = search(key[i]);
		}
		
		cout << caesar[textValue][keyValue];
	}
	
	cout << endl;	
}

// Decodes text with specified key
void decode (string key) {
	char text [26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int cipherValue;
	int keyValue;
	string cipher;
	
	cin >> cipher;
	cout << key << endl;

	int cipherSize = cipher.size();
	int keySize = key.size();

	// Searches for the values to be used to crack cipher
	for(int i = 0; i < cipherSize; i++) {		
		if (i >= keySize) {
			keyValue = search(key[(i-keySize)]);
		} else {
			keyValue = search(key[i]);
		}		
	
		for(int j = 0; j < 26; j++) {	
			if (caesar[keyValue][j] == cipher[i]){
				cipherValue = j;
				break;			
			}	
		}
		
		cout << text[cipherValue];
	}
	
	cout << endl;	
}

