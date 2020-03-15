// -------------------------------------------------------------------------------
// Filename:            morse.cpp
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   03
// Due Date:            March 27, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Description: Encodes/Decodes Morse Code Messages Using A Binary Tree
// -------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>

#include "morse.h"

static const char DOT = '.';
static const char DASH = '-';

TNODE *Telegraph::mRoot = 0;
LNODE *Telegraph::mHead = 0;

Telegraph test;

// -------------------------------------------------------------------------------
// Reads A File Into A Telegram Object
// -------------------------------------------------------------------------------
string Telegraph::Read()
{
    string buffer;
    string line;

    // Create A File Object
    ifstream file;
    
    // Clear File Object
    file.clear();

    // Open Morse Code File
    file.open("telegram.txt");

    // If File Does Not Exist
    if (!file) 
    { 
        // Print Error And Exit!
        cerr << "\n\nERROR: File Does Not Exist! Exiting!\n"; 
        system("pause"); 
        exit(0); 
    } 

    while(getline(file,line))
    {
        buffer += line;
    }
    cout << buffer;
    return buffer;
}

// -------------------------------------------------------------------------------
// Builds Encoding List And Decoding Tree For The Telegraph
// -------------------------------------------------------------------------------
void Telegraph::Open()
{
    // Create Temporary Morse Code Variables
    char m_temp_char;
    string m_temp_code;
    
    // Create The mHead Node. A Space Is Encoded As The Empty String
    mHead = new LNODE(' ', "");

    // Create The mRoot Node
    mRoot = new TNODE;
    
    // If Root Doesn't Exist, Exit
    if (!mRoot) 
    {
        return;
    }

    // Set Symbol
    mRoot->symbol = ' ';

    // Create A File Object
    ifstream file;
    
    // Clear File Object
    file.clear();

    // Open Morse Code File
    file.open("morse.txt");

    // If File Does Not Exist
    if (!file) 
    { 
        // Print Error And Exit!
        cerr << "\n\nERROR: File Does Not Exist! Exiting!\n"; 
        system("pause"); 
        exit(0); 
    } 
    
    // If File Exists, Read Morse Code Data Into Tree Until End Of File Is Reached
    while (!file.eof())
    {
        // Read In Character and Associated Code
        file >> m_temp_char >> m_temp_code;
        
        // Remove Delimiter
        m_temp_code.erase(0,1);
        
        // Insert Data Into Tree
        Insert (m_temp_char, m_temp_code);
    }
}

// -------------------------------------------------------------------------------
// Destroys The Encoding List And Decoding Tree By Way Of Recursive Helper Func.
// -------------------------------------------------------------------------------
void Telegraph::Close()
{
    // Create Temp Note That Starts At Head For Traversing List
    LNODE *node = mHead;
    LNODE *next = 0;	

    // Remove Node As Long As The List Is Not Empty (head != NULL)
    while(node)
    { 
        // Set Next Node
        next = node->next;
        
        // Remove Node
        delete node;
        
        // Set Node To Next
        node = next;
    
    } 
    
    // Set Head Of List To NULL
    mHead = NULL;	
    
    // Destroy Decoding Tree
    RecursiveDestroy(mRoot);
    
    // Set Root Of Tree To NULL
    mRoot = 0;
}

// -------------------------------------------------------------------------------
// Destroys The Encoding List And Decoding Tree By Way Of Recursive Helper Func.
// -------------------------------------------------------------------------------
void Telegraph::RecursiveDestroy(TNODE *root)
{
    // Since The Root Is Passed By Value, There's No Need To Create A Copy For Traversal
    
    // If There's No Tree Root Exit
    if (!root)
    {	
        return;
    }
    
    // Otherwise... If Right SubTree Exists, Destroy It
    else if (root->right)
    {
        RecursiveDestroy(root->right);
        delete root;
    }
    
    // Otherwise... If Left SubTree Exists, Destroy It
    else if(root->left)
    {
        RecursiveDestroy(root->left);
        delete root;
    }
}

// -------------------------------------------------------------------------------
// Inserts A Symbol And Morse Code Into The Encoding List And Decoding Tree
// -------------------------------------------------------------------------------
void Telegraph::Insert(char symbol, const string &morsecode)
{
    // Each Morse Code Character Will Correspond To A Path In The Tree
    // From The Root To A Node: At A "DOT" Go Left, At A "DASH" Go
    // Right.  The Node At The End Of The Path Holds The Symbol
    // For That Character.    

    // Append A New Node At The End Of The Encoding List
    LNODE *lnode;
    lnode = mHead;

    while (lnode->next)
    {
        lnode = lnode->next;
    }
    lnode->next = new LNODE(symbol, morsecode);

    // TNODE Is A Pointer To A Node And Traverses Tree Initialized To mRoot
    TNODE *tnode = mRoot;


    for (int i = 0; i < (signed)morsecode.length(); i++) 
    {
        // DOT < DASH, So For Every DOT Found In The List Travel Left Of tnode,
        // Which Starts At Root And Goes Back After Loop Exits.
        //				.-
        //
        //				mRoot		
        //				/   \		DOT Found. Go Left Of tnode, Starting At mRoot
        //			   .
        //				\			DASH Found. Go Right Of tnode, Starting At mRoot
        //				 -
        
        // If DOT Found
        if (morsecode[i] == DOT) 
        {
           
            // Go Left In Tree
            if(!tnode->left)
            {   
                // Allocate Memory
                tnode->left = new TNODE();
            }
        
            // Move TNODE To Left Of New Node
            tnode=tnode->left;
        }

        // If DASH Found
        else 
        { 
            // Go Right In Tree
            if(!tnode->right)
            {
                // Allocate Memory
                tnode->right = new TNODE();
            }
            
            // Move TNODE To Right Of New Node
            tnode=tnode->right;
        }
    }
    
    // Set Symbol
    tnode->symbol = symbol;
}

// -------------------------------------------------------------------------------
// Encode The Telegram Into Morse Code
// -------------------------------------------------------------------------------
void Telegraph::Encode(const string &text, string &morse)
{
    LNODE *lnode;
    char ch;

    // Make Morse Code String Empty
    morse = "";

    for (int i = 0; i < (signed)text.length(); i++) 
    {
        // Converts Text To Uppercase To Correspond With Capitalized Letters
        // In The Tree
        ch = toupper(text[i]);

        // Find This Symbol In The Encoding List, Skip If Not Found
        for (lnode = mHead; lnode; lnode = lnode->next)
        {
            if (lnode->symbol == ch)
            {
                break;
            }
        }

        // Append The Code To The Morse Strin (Add One Space To Separate Letters):
        if (lnode)
        {
            // Not The Most Efficient Approach
            morse += lnode->code + ' ';
        }
        
        /*
        The above statement looks neat, but it may be atrociously
        inefficient.  We start with an empty string and may end up
        with a string of considerable length.  Each time += is executed,
        the string buffer may be reallocated and the whole string will
        be copied into the new buffer.  This is repeated for every
        character in the text string.  To avoid such situations we
        could add a constructor to the apstring class that would
        build an empty string but allocate a large buffer for future
        expansion.  We could also add the space character to
        the codes that we place into the encoding list in the Insert()
        function instead of executing + every time here:

        (e.g. lnode->next = new LNODE(symbol, morsecode + ' ');)

        Alternatively, we could use null-terminated strings to handle
        concatenation more efficiently.
        */
    }
}

// -------------------------------------------------------------------------------
// Decodes Telegram Into Text
// -------------------------------------------------------------------------------
void Telegraph::Decode(const string &morse, string &text)
{
    TNODE *tnode;
    
    // Make The Text String Empty
    text = "";                        

    tnode = mRoot;

    // For Each Character In The Encoded Message (DOT, DASH, Or SPACE)
    for (int i = 0; i < (signed)morse.length(); i++) 
    {	
        // Traverse Tree As Long As There Are Dots Or Dashes.
        // When You Encounter A Space, Take The Symbol From The
        // Node, Add It To The Text String, And Return To The mRoot.

        // DOT Is Encountered, So Go Left In Tree Since DOT < DASH
        if(morse[i] == '.')	
        {
            tnode = tnode->left;
        }

        // DASH Is Encountered, So Go Right In Tree Since DASH > DOT 
        if(morse[i] == '-')	
        {
            tnode = tnode->right;
        }		
        
        // SPACE Is Encountered, So Take The Symbol Of The Location Of tnode
        // Since The Tree Traversal Is Finished		
        if(morse[i] == ' ')	
        {
            // Add Decoded Letter To String text
            text += tnode->symbol;	

            // Brings tnode Back To mRoot For Decoding Of Next Symbol
            tnode = mRoot;
        }
    }
}