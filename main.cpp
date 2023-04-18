#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

// fucntion that encrypts a message
string encrypt(string key, string plain_text)
{
    string encrypted_message;
    int k = 0;
    for(int i = 0; i < plain_text.size(); i++)
    {
        if(k == key.size()) {k = 0;}

        if(plain_text[i] == ' ') {encrypted_message += ' ';}
        else if((plain_text[i] > 0 && plain_text[i] < 65) || (plain_text[i] < 97 && plain_text[i] > 122) || plain_text[i] > 122)
        {
            encrypted_message += plain_text[i];
        }
        else
        {
            if(plain_text[i] >= 97 && plain_text[i] <= 122)
            {
                transform(alphabet.begin(), alphabet.end(), alphabet.begin(), ::tolower);
                transform(key.begin(), key.end(), key.begin(), ::tolower);
            }
            else
            {
                transform(alphabet.begin(), alphabet.end(), alphabet.begin(), ::toupper);
                transform(key.begin(), key.end(), key.begin(), ::toupper);
            }

            int alphabet_index = alphabet.find(key[k]) + alphabet.find(plain_text[i]);
            if(alphabet_index >= alphabet.size())
            {
               alphabet_index -= alphabet.size();
            }



            encrypted_message += alphabet[alphabet_index];

            k++;
        }
    }
    return encrypted_message;
}

// fucntion that decrypts a message
string decrypt(string key, string plain_text)
{
    string decrypted_message;
    int k = 0;
    for(int i = 0; i < plain_text.size(); i++)
    {
        if(k == key.size()) {k = 0;}

        if(plain_text[i] == ' ') {decrypted_message += ' ';}
        else if((plain_text[i] > 0 && plain_text[i] < 65) || (plain_text[i] < 97 && plain_text[i] > 122) || plain_text[i] > 122)
        {
            decrypted_message += plain_text[i];
        }
        else
        {
            if(plain_text[i] >= 97 && plain_text[i] <= 122)
            {
                transform(alphabet.begin(), alphabet.end(), alphabet.begin(), ::tolower);
                transform(key.begin(), key.end(), key.begin(), ::tolower);
            }
            else
            {
                transform(alphabet.begin(), alphabet.end(), alphabet.begin(), ::toupper);
                transform(key.begin(), key.end(), key.begin(), ::toupper);
            }

            int alphabet_index = alphabet.find(plain_text[i]) - alphabet.find(key[k]);
            if(alphabet_index < 0)
            {
               alphabet_index += alphabet.size();
            }
            decrypted_message += alphabet[alphabet_index];

            k++;
        }
    }
    return decrypted_message;
}

void logo()
{
    cout << R"(
     _    _ _                                             _       _
    | |  | (_)                                           (_)     | |
    | |  | |_  ____  ____ ____   ____  ____ ____     ____ _ ____ | | _   ____  ____
     \ \/ /| |/ _  |/ _  )  _ \ / _  )/ ___) _  )   / ___) |  _ \| || \ / _  )/ ___)
      \  / | ( ( | ( (/ /| | | ( (/ /| |  ( (/ /   ( (___| | | | | | | ( (/ /| |
       \/  |_|\_|| |\____)_| |_|\____)_|   \____)   \____)_| ||_/|_| |_|\____)_|
             (_____|                                       |_|
    )" << endl;
}

int main()
{
    string key, plain_text, coded_message, cipher_choice, read_choice, save_in_file;
    fstream cipher_param("cipher_param.txt");

    logo();

    cout << "Welcome to Vigenere Cipher! Here, you will be able to encrypt or decrypt your message!\n" << endl;
    cout << "Type 'e' to encrypt or 'd' to decrypt your message: ";

    getline(cin, cipher_choice);

    if(cipher_choice == "d")
    {
        cipher_choice = "decrypted message";

        cout << "Type 'f' to get your parameters from file named 'cipher_param.txt' or 'c' to put them into console: ";
        getline(cin, read_choice);

        if(read_choice == "c")
        {
            cout << "Type in a text that you want decrypt: ";
            getline(cin, plain_text);
            cout << "Type in a key: ";
            getline(cin, key);
        }
        else if(read_choice == "f")
        {
            getline(cipher_param, plain_text);
            getline(cipher_param, key);
        }
        else
        {
            cout << "Wrong input!";
            return -1;
        }
        coded_message = decrypt(key, plain_text);

        cout << "Your " << cipher_choice << " is \"" << coded_message << "\"" << endl;
    }
    else if(cipher_choice == "e")
    {
        cipher_choice = "encrypted message";

        cout << "Type 'f' to get your parameters from file named 'cipher_param.txt' or 'c' to put them into console: ";
        getline(cin, read_choice);

        transform(save_in_file.begin(), save_in_file.end(), save_in_file.begin(), ::tolower);

        if(read_choice == "c")
        {
            cout << "Type in a text that you want to encrypt: ";
            getline(cin, plain_text);
            cout << "Type in a key: ";
            getline(cin, key);
        }
        else if(read_choice == "f")
        {
            getline(cipher_param, plain_text);
            getline(cipher_param, key);
        }
        else
        {
            cout << "Wrong input!";
            return -1;
        }

        coded_message = encrypt(key, plain_text);
        cout << "Your " << cipher_choice << " is \"" << coded_message << "\"" << endl;
    }
    else
    {
        cout << "Wrong input! Exiting... " << endl;
        return -1;
    }

    cout << "Do you want to save your " << cipher_choice << " into a file named 'saved_message.txt'? ('yes' or 'no'): ";
    getline(cin, save_in_file);
    transform(save_in_file.begin(), save_in_file.end(), save_in_file.begin(), ::tolower);

    cout << "\n";

    if(save_in_file == "yes")
    {
        ofstream outfile("saved_message.txt");
        if(!outfile)
        {
            cout << "Cannot save \"saved_message.txt\". Exiting... " << endl;
            return -1;
        }

        outfile << "Your " << cipher_choice << " is \"" << coded_message << "\"";
        cout << "Your message was saved into \"saved_message.txt\" file. Exiting...";
    }
    else if(save_in_file == "no") {cout << "Exiting...";}
    else {cout << "Wrong input! Exiting...";}

    return 0;
}
