/*
// -------------------------------------------------------------------------------
// Filename:            MorseDocs.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   03
// Due Date:            March 27, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// Description: Encodes/Decodes Morse Code Messages Using A Binary Tree
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// DESCRIPTION
// -------------------------------------------------------------------------------
    This program encodes and decodes morse code messages using a binary tree to
    store the values. A telegram is read in from a file, encoded into morse code,
    then decoded back into text.

// -------------------------------------------------------------------------------
// CONTENTS
// -------------------------------------------------------------------------------

   /-------------------------------------------------------------------------------\
     Program Files
   \-------------------------------------------------------------------------------/

    morsedocs.h
    Documentation for the Morse Code program. You're Reading It!
    
    main.cpp
    This is the main program. There are no functions defined in this file.

    morse.h
    This includes the main program classes, member function prototypes, and member 
    variables.

    morse.cpp
    This contains most of the functions defined in morse.h.
    
    morse.txt
    Contains the actual Morse Code language. The file is comma delimited separating
    the character with its associated morse code translation.

    telegram.txt
    This contains a sample telegram the program encodes and decodes. It is a copy
    of the famous "Zimmerman Telegram".
    
        "At the end of January 1917, the German government�desperate to break 
        the stalemated trench warfare�announced that it would resume unrestricted 
        submarine attacks. The United States broke diplomatic relations with Germany 
        and further events pushed the nation even closer to war. On March 1, newspapers 
        published a telegram from German foreign minister Arthur Zimmermann to the 
        Mexican government, proposing a German-Mexican alliance against the United 
        States. (For attacking the United States, the Mexicans would recoup lost 
        territory in Texas, New Mexico, and Arizona.) Intercepted by the British, the 
        telegram was published widely in American newspapers and inflamed popular 
        opinion against the Germans."

   /-------------------------------------------------------------------------------\
     CLASSES AND FUNCTIONS
   \-------------------------------------------------------------------------------/

   /---------------------\
    Struct: LNODE
   \---------------------/
    This represents the node of the encoding list. This node is used to store
    the character its associated morse code.

    Constructor: LNODE
    The constructor takes a character and a string which represents the symbol
    and associated morse code.
    

   /---------------------\
    Struct: TNODE
   \---------------------/
    This represents the node of the decoding tree. This node is used to store
    the code for each character.

    Constructor: TNODE
    The constructor does not take any values. It is composed of two TNODEs
    which act as left and right nodes of the tree and a symbol for the 
    character located in each node.

   /---------------------\
    Class: Telegraph
   \---------------------/
    This is the main class. It contains the following:

    Constructor: Telegraph
        This class contains static data members for the head of the encoding
        list and the root of the decoding tree.
        
    Function: Read
        This function reads in a text file called "telegram.txt" and returns
        it to main as a string to encode.

        PreCondition: There must be a file named "telegram.txt" in the working
        folder.

        PostCondition: The contents of "telegram.txt" is read into a string and
        passed to main for encoding/decoding.
    
    Function: Open
        Builds the encoding list and decoding tree for the Telegraph object.

        PreCondition: There must be a file called "morse.txt" in the working
        folder. This file must be comma delimited and formatted like this:

        Ex: character, morse code

        PostCondition: An encoding list and decoding tree is constructed based
        on the information found in morse.txt.

    Function: Close
        Destroys the encoding list and decoding tree by way of a recursive
        helper function RecursiveDestroy. This cleans up after we're done
        encoding and decoding a telegram.

        PreCondition: There must be an encoding list and decoding tree.
        PostCondition: The memory used by the encoding list and decoding tree
        is cleaned up.

    Function: RecursiveDestroy
        This function is passed the root node, and recursively deletes each
        node of the branch that it encounters. If no root exists it exits.

        PreConditions: None

        PostCondition: If an encoding list and decoding tree are found, nodes
        are deleted recursively cleaning up memory.

    Function: Insert
        Inserts a symbol and its Morse code into the encoding list and decoding tree.
        Each Morse code character will correspond to a path in the tree from the root 
        to a node: at a "dot" go left, at a "dash" go right.  The node at the end of 
        the path holds the symbol for that character.

        PreCondition: There must be a filename called morse.text in the working folder
        and it must be in the proper format.

        PostCondition: A node for each character and associated morse code is created
        in the encoding list and decoding tree.

    Function: Encode
        This function encodes the text found in telegram.txt into its morse code
        equivalent.

        PreConditions: A valid text string comprised of the character set located
        in morse.txt must be passed.

        PostConditions: The text string is encoded into morse code.

    Function: Decode
        This function decodes the morse encoded text string passed back into text.

        PreConditions: The function must be passed a morse encoded string.

        PostConditions: The morse encoded string is decoded back into text.

// -------------------------------------------------------------------------------
*/