// -------------------------------------------------------------------------------
// Filename:            morse.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   03
// Due Date:            March 27, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Description: Encodes/Decodes Morse Code Messages Using A Binary Tree
// -------------------------------------------------------------------------------

#ifndef _MORSE_H_
#define _MORSE_H_

#include <string>
#include <vector>

// Documenation Located In morsedocs.h
#include "morsedocs.h";

using namespace std;

// Node Of The Morse Code Encoding List 
struct LNODE 
{              
    char symbol;
    string code;
    LNODE *next;

    // Constructor
    LNODE(char c, const string &str) : symbol(c), code(str), next(0) {}       
};

// Node Of The Morse Code Decoding Tree
struct TNODE 
{              
    char symbol;
    TNODE *left;
    TNODE *right;
    
    // Constructor
    TNODE() : symbol('*'), left(0), right(0) {}
};

// Telegraph Class That Handles Encoding/Decoding Of Telegrams
class Telegraph 
{
    public:

        static string Read();	// Read Telegram File
        static void Open();		// Open The Encode List/Decode Tree
        static void Close();	// Delete The Encode List/Decode Tree

        void Encode(const string &text, string &morse);	// Encode The Telegram
        void Decode(const string &morse, string &text); // Decode The Telegram

    private:

        static void RecursiveDestroy(TNODE *root);
        static void Insert(char symbol, const string &morsecode);

        static LNODE *mHead;        // The Head Of The Encoding List.
        static TNODE *mRoot;        // The Root Of The Decoding Tree.
};
#endif
