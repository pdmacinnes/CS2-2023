#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    // Open the text file for reading.
    ifstream textFile("sample.txt", ios::ate);

    if (textFile.is_open())
    {
        // Determine the file size.
        streampos fileSize = textFile.tellg();
        textFile.seekg(0, ios::beg);

        // Allocate a C-style character array to store the file contents.
        char* fileContent = new char[fileSize];

        // Read the entire file content into the array.
        textFile.read(fileContent, fileSize);
        cout << "The file contained:\n" << fileContent << endl << endl
             << "Enter words to search for (separated by spaces): ";
        
        string searchWords;
        cin >> searchWords;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Tokenize the content using strtok.
        char* token = strtok(fileContent, " \n");

        // Create a count for each search word.
        int wordCount = 0;

        // Display individual tokens and search for specific words.
        while (token != nullptr)
        {
            cout << "Token: " << token << endl;
            
            // Check if the token matches any of the search words.
            if (searchWords.find(token) != string::npos) {
                wordCount++;
            }

            // Get the next token.
            token = strtok(nullptr, " \n");
        }

        // Display the count of specific words found.
        cout << "Words found: " << wordCount << endl;

        // Don't forget to release the allocated memory.
        delete[] fileContent;
    }
    else
    {
        cerr << "Failed to open the text file." << endl;
        return 1;
    }

    return 0;
}
