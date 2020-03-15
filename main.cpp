// -------------------------------------------------------------------------------
// Filename:            main.cpp
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   03
// Due Date:            March 27, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Description: Encodes/Decodes Morse Code Messages Using A Binary Tree
// -------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "morse.h"

int main()
{
    // Create A Telegraph Object
    Telegraph station;
    
    // Init Morse Code Vars
    string text, morse;

    // Build Morse Code Encoding List/Decoding Tree
    Telegraph::Open();
    
    // Read In The Telegram
    cout << "[Reading Telegram...]\n\n";
    text = Telegraph::Read();
    cout << "\n\n";
    system("pause");

    // Encode Telegram Into Morse Code
    cout << "\n\n[Encoding Telegram...]\n\n";
    station.Encode(text, morse);

    // Display Encoded Telegram
    cout << morse << "\n\n";
    system("pause");
    
    // Decode Telegram Into Text
    cout << "\n\n[Decoding Telegram...]\n\n";
    station.Decode(morse, text);
    
    // Display Decoded Telegram
    cout << text << "\n\n";
    system("pause");

    // Clean Up By Deleting Tree And List
    Telegraph::Close();
}