// LibTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <chrono>
#include <thread>
#include <fstream>
#include "Hitomezashi.h"
#include "Morse.h"
#include "TypeConversions.h"
#include "FractionatedMorse.h"
#include "Playfair.h"
#include "RailFence.h"
#include "XORCipher.h"
#include "VigenereCipher.h"

using namespace std;
using namespace kadenLib;

int main()
{
    
    Playfair pf;
    RailFence rf;
    XORCipher Alice;
    XORCipher Bob;
    VigenereCipher vc;

    //QUESTION 1
    Alice.genKey();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Bob.genKey();
    string plainttext = "This is the plain text message";
    string step1 = Alice.encode("This is the plain text message");
    string step2 = Bob.encode(step1);
    string step3 = Alice.encode(step2);
    string step4 = Bob.encode(step3);

    cout << "Question 1: \nPlain Text:\t\t\t" << plainttext << "\nStep 1 Alice encodes message:\t" << step1 << "\nStep 2 Bob encodes message:\t" << step2 << "\nStep 3 Alice decodes message:\t" << step3 << "\nStep 4 Bob decodes meeage:\t" << step4 << endl;

    string s1XORs2 = Alice.xorStrings(step1, step2);
    string s3XORkey = Alice.xorStrings(s1XORs2, step3);

    cout << "\nSolution:\nXOR step 1 and 2 to get Bobs key: \t" << s1XORs2 << "\nXOR Bobs key with step 3: \t\t" << s3XORkey << endl;

    cout << "\n\n\n\n\n";

    //QUESTION 2 SUBSTITUTION CIPHER

    cout << "Question 2 A Playfair Cipher (modified for 5x6 grid)\n\n";

    string fullKey = pf.genFull65Key("KADEN");
    for (int i = 0; i < 30; i++)
    {
        cout << fullKey[i];
        if (((i+1) % 5) == 0 && i != 0) cout << "\n";
    }
    cout << endl;

    cout << pf.encode65("Go Chargers", fullKey, 1);


    cout << "\n\n\n\n\n";
    //QUESTION 2 TRANPOSITION CIPHER
    cout << "Question 2 B  Rail Fence Cipher:\n";
    cout << rf.showFence("GO CHARGERS", 4) << endl;
    cout << rf.encode("GO CHARGERS", 4) << endl << endl << endl;

    cout << "\n\n\n\n\n";
    //QUESTION 3
    
    ifstream inFP;
    inFP.open("ciphertext.txt");
    if (inFP.is_open() != true) cout << "FILE ERROR\n";
    string ciphertext = "";
    string line = "";
    while (getline(inFP, line))
    {
        ciphertext.append(line);
    }
    inFP.close();

    vc.aOffset = 0;

    cout << "Question 3 break a Vigenere cipher\n\n";
    cout << "Use a index of coincidence test to find the key length\nThe key length for this text was fount to be: " << vc.iocKeyLengthTest(ciphertext) << endl << endl;

    cout << "Use a chi squared goodness of fit test to compare the letter frequency distribution \nof standard english to the nth letters of the cipher text\nshift the letters by one and retest until the off set is found.  repeat for all chars of key.\n";
    cout << "Key: " << vc.breakKey(ciphertext) << endl << endl;

    cout << "Use the key to decode the text\n";
    cout << vc.decode(ciphertext, vc.breakKey(ciphertext)) << endl;

}

