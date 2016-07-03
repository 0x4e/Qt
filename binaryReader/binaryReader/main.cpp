#include <QCoreApplication>
#include <iostream>
#include <stdio.h>
using namespace std;


// An unsigned char can store 1 Bytes (8bits) of data (0-255)
typedef unsigned char BYTE;

// Get the size of a file
long getFileSize(FILE *file)
{
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "POOOOO"<<endl;

    const char *filePath = "/home/nick/console5.txt";
    BYTE *fileBuf;			// Pointer to our buffered data
    FILE *file = NULL;		// File pointer

    // Open the file in binary mode using the "rb" format string
    // This also checks if the file exists and/or can be opened for reading correctly
    if ((file = fopen(filePath, "rb")) == NULL)
        cout << "Could not open specified file" << endl;
    else
        cout << "File opened successfully" << endl;

    // Get the size of the file in bytes
    long fileSize = getFileSize(file);

    // Allocate space in the buffer for the whole file
    fileBuf = new BYTE[fileSize];

    // Read the file in to the buffer
    fread(fileBuf, fileSize, 1, file);

    // Now that we have the entire file buffered, we can take a look at some binary infomation
    // Lets take a look in hexadecimal
    for (int i = 0; i < fileSize; i++)
        printf("%X ", fileBuf[i]);

    cin.get();
    delete[]fileBuf;
    fclose(file);   // Almost forgot this



    return a.exec();
}
