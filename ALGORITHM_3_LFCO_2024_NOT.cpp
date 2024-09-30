#include "ALGORITHM_1_LFCO_2024_NOT.cpp" 
#include "ALGORITHM_2_LFCO_2024_NOT.cpp" 

// Function to print the sentential form for a string from the CFG S -> aSb | ab
void sentential_form(string target_str) {
    char non_terminal = 'S';  // Start with non-terminal 'S'
    string str;
    str += non_terminal;
    
    cout << "Rule applied  | Sentential forms in a leftmost derivation" << endl;
    cout << "Initial       | " << str << endl;
    
    // Apply Rule S -> aSb until reaching the final form
    int rule_applied = 1;
    for (int i = 0; target_str[i] == 'a'; i++) {
        str = 'a' + str + 'b';  
        cout << "Rule  1       | " << str << endl;
    }
    
    // Apply Rule S -> ab to convert the middle 'S'
    str.erase(str.begin() + (str.length() / 2));
    cout << "Final Rule    | " << str << endl;
}

// Main function to generate strings, process them via PDA, and print their sentential forms
int main() {
    vector<string> strings = generate_strings();  // Generate random strings
    strings = process_strings(strings);  // Process them through the PDA to get the valid ones
    
    // Print the sentential forms of all valid strings
    for (string str : strings) {
        cout << "\nSentential form of the string '" << str << "'\n";
        sentential_form(str); 
    }

    return 0;
}
