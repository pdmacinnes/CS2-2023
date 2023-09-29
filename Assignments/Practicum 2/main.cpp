#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Struct to store ID3 tag information
struct ID3v1Tag {
    char header[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char trackNumber;
    int genre;
};

// Function to print a string without relying on null-termination
void printString(const char* str, int size) {
    for (int i = 0; i < size; ++i) {
        if (str[i] != '\0') {
            cout << str[i];
        }
    }
}

// Function to update the comment field in the ID3v1.1 tag
void updateCommentField(ID3v1Tag& tag) {
    cout << "Do you wish to update the comment field (Y/N)? ";
    char choice;
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        cout << "Comment: ";
        cin.ignore(); // Clear newline from previous input
        cin.getline(tag.comment, sizeof(tag.comment));
        tag.comment[sizeof(tag.comment) - 1] = '\0'; // Ensure null-termination
    }
}

const char genre[148][32] =  {"Blues", "Classic Rock", "Country", "Dance",
    "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz", "Metal", "New Age",
    "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno",
    "Industrial", "Alternative", "Ska", "Death Metal", "Pranks",
    "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", "Vocal",
    "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental", "Acid",
    "House", "Game", "Sound Clip", "Gospel", "Noise", "Alternative Rock",
    "Bass", "Soul", "Punk", "Space", "Meditative", "Instrumental Pop",
    "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
    "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream",
    "Southern Rock", "Comedy", "Cult", "Gangsta", "Top 40", "Christian Rap",
    "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave",
    "Psychadelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal",
    "Acid Punk", "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll",
    "Hard Rock", "Folk", "Folk-Rock", "National Folk", "Swing",
    "Fast Fusion", "Bebob", "Latin", "Revival", "Celtic", "Bluegrass",
    "Avantgarde", "Gothic Rock", "Progressive Rock", "Psychedelic Rock",
    "Symphonic Rock", "Slow Rock", "Big Band", "Chorus", "Easy Listening",
    "Acoustic", "Humour", "Speech", "Chanson", "Opera", "Chamber Music",
    "Sonata", "Symphony", "Booty Bass", "Primus", "Porn Groove", "Satire",
    "Slow Jam", "Club", "Tango", "Samba", "Folklore", "Ballad",
    "Power Ballad", "Rhythmic Soul", "Freestyle", "Duet", "Punk Rock",
    "Drum Solo", "Acapella", "Euro-House", "Dance Hall", "Goa",
    "Drum & Bass", "Club-House", "Hardcore", "Terror", "Indie", "BritPop",
    "Negerpunk", "Polsk Pumk", "Beat", "Christian Gangsta Rap",
    "Heavy Metal", "Black Metal", "Crossover", "Contemporary Christian",
    "Christian Rock", "Merengue", "Salsa", "Thrash Metal", "Anime", "JPop",
    "Synthpop"};


int main() {
    char filename[256];
    cout << "Enter filename: ";
    cin.getline(filename, sizeof(filename));

    // Check if the file has a .mp3 extension
    if (strlen(filename) < 4 || strncmp(filename + strlen(filename) - 4, ".mp3", 4) != 0) {
        cerr << "Error: File must have a .mp3 extension." << endl;
        return 1;
    }

    ifstream mp3file(filename, ios::binary);

    if (!mp3file) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    mp3file.seekg(-128, ios::end); // Position the file 128 bytes from the end
    ID3v1Tag tag;

    mp3file.read(reinterpret_cast<char*>(&tag), sizeof(tag));
    tag.genre = static_cast<int>(tag.genre); // Convert genre to int


    // Check if the tag is valid
    if (strncmp(tag.header, "TAG", 3) != 0) {
        cerr << "Error: Invalid ID3v1.1 tag." << endl;
        return 1;
    }

    cout << "File is OK and has valid ID3v1.1 tag" << endl;
    cout << "Title: ";
    printString(tag.title, sizeof(tag.title));
    cout << endl;
    cout << "Artist: ";
    printString(tag.artist, sizeof(tag.artist));
    cout << endl;
    cout << "Album: ";
    printString(tag.album, sizeof(tag.album));
    cout << endl;
    cout << "Year: ";
    printString(tag.year, sizeof(tag.year));
    cout << endl;
    cout << "Comment: ";
    printString(tag.comment, sizeof(tag.comment));
    cout << endl;
    cout << "Track Number: " << static_cast<int>(tag.trackNumber) << endl;

    // Validate and print the genre
    if (tag.genre >= 0 && tag.genre < 148) {
        cout << "Genre: " << genre[tag.genre] << endl;
    } else {
        cout << "Genre: Unknown" << endl;
    }


    updateCommentField(tag);

    mp3file.close();

    // Reopen the file for writing and update the comment
    ofstream mp3fileOut(filename, ios::binary | ios::in | ios::out);

    if (!mp3fileOut) {
        cerr << "Error: Unable to open file for writing." << endl;
        return 1;
    }

    // Reposition the file to the location of the comment
    mp3fileOut.seekp(-30, ios::end);
    mp3fileOut.write(tag.comment, sizeof(tag.comment));

    cout << "Updated ID3 tag:" << endl;
    cout << "Title: ";
    printString(tag.title, sizeof(tag.title));
    cout << endl;
    cout << "Artist: ";
    printString(tag.artist, sizeof(tag.artist));
    cout << endl;
    cout << "Album: ";
    printString(tag.album, sizeof(tag.album));
    cout << endl;
    cout << "Year: ";
    printString(tag.year, sizeof(tag.year));
    cout << endl;
    cout << "Comment: ";
    printString(tag.comment, sizeof(tag.comment));
    cout << endl;
    cout << "Track Number: " << static_cast<int>(tag.trackNumber) << endl;

    // Validate and print the genre again
    if (tag.genre >= 0 && tag.genre < 148) {
        cout << "Genre: " << genre[tag.genre] << endl;
    } else {
        cout << "Genre: Unknown" << endl;
    }

    mp3fileOut.close();

    return 0;
}
