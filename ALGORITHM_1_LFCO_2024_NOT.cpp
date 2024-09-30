#include <bits/stdc++.h>

using namespace std;

// Function to generate a valid string based on the grammar
string valid_string_generator(){
    int n = rand() % 21; // Randomly generate the length of the string
    string valid_str = "ab"; // Initialize the string with "ab" as a base case

    // Loop to insert "ab" in the middle of the string n times
    for (int i = 0; i < n; i++)
        valid_str.insert(valid_str.length() / 2, "ab"); // Insert "ab" in the middle of the string
    return valid_str; 
}

// Function to generate a random string (could be invalid)
string invalid_string_generator(){
    string random_str;
    int n = rand() % 21; // Randomly generate the length of the string

    // Loop to randomly append 'a' or 'b' to the string n times
    for(int i = 0; i < n; i++){
        int r = rand() % 2; // Generate a random number (0 or 1)
        // Depending on the value of r, add either 'a' or 'b' to the string
        if(r == 0) random_str += 'a'; 
        else random_str += 'b';
    }
    return random_str;
}

// Function to generate a collection of strings (both valid and invalid)
vector <string> generate_strings(){
    srand(time(0)); // Set the random seed to the current time for random number generation

    int n = rand() % 20;  // Randomly generate the number of strings to process
    vector <string> strings; 

    cout << "The first algorithm produced the strings:" << endl;

    // Loop to generate n strings
    for (int i = 0; i < n; i++){
        int r = rand() % 2; // Randomly decide whether to generate a valid or invalid string
        // If r == 0, generate a valid string, otherwise generate an invalid string
        if(r == 0) strings.push_back(valid_string_generator()); 
        else strings.push_back(invalid_string_generator());
        cout << "String: '" << strings[i] << "'" << endl;
    }        

    return strings;
}
  
