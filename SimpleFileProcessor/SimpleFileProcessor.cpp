// SimpleFileProcessor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    long long number_of_lines;

    // Make sure that argument was passed
	if (argc < 2)
    {
        return 1; // Argument wasn't passed, kill with non-zero return code
    }
    else
    {
        char *filename = argv[1];
        ifstream file_stream(filename);

        number_of_lines = count(istreambuf_iterator<char>(file_stream),
            istreambuf_iterator<char>(), '\n');   

        file_stream.close();
    }

    cout << number_of_lines + 1 << endl;

    return 0;
}

