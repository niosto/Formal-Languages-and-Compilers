#include <bits/stdc++.h>

using namespace std;

// Class definition for the Pushdown Automaton (PDA)
class PDA {
public:
    // Constructor to initialize the PDA with states, alphabet, transition function, initial stack symbol, initial state, and final states
    PDA(const set<int>& states, 
        const set<char>& alphabet,
        // Transition function is a map that returns a pair<int, char> (the next state and the stack operation)
        const map<int, map<char, map <char, pair<int, char>>>>& f_transicion, 
        const char& initial_symbol,  
        const int& initial_state,    
        const set<int>& final_state) 
        : states(states), alphabet(alphabet), f_transicion(f_transicion), initial_symbol(initial_symbol), initial_state(initial_state), final_state(final_state) {}

    // Function to handle transitions based on the input symbol
    void transicion(char symbol) {
        // Check if the symbol is part of the defined alphabet
        if (alphabet.find(symbol) != alphabet.end()) {
            // Retrieve the orders from the transition function for the current state, symbol, and top of the stack
            pair<int, char> orders = f_transicion.at(state).at(symbol).at(Stack.top());

            // If the second part of the orders is not empty, push it to the stack; otherwise, pop the stack
            if (orders.second != ' ') Stack.push(orders.second);
            else Stack.pop();

            // Update the state to the new state specified in the orders
            state = orders.first;

        } else {
            throw symbol; // If the symbol isn't in the alphabet, throw an exception
        }
    }

    // Function to check if a given string is accepted by the PDA
    bool acceptance(const string& str) {
        Stack = stack<char>(); // Clear and initialize the stack
        state = initial_state; // Reset the PDA state to the initial state
        Stack.push(initial_symbol); // Push the initial stack symbol onto the stack
        
        // Loop through each symbol in the input string
        for (char symbol : str) {
            try {
                // Try to transition based on the current symbol
                transicion(symbol);
            }
            catch (const char* e) { // Catch an error if the symbol isn't part of the alphabet
                cout << "The Symbol " << e << " does not belong to the alphabet" << endl; 
                return false; // Return false as the string is rejected
            }
            catch (const out_of_range& e) { // Catch an out_of_range error when no valid transition exists
                return false; // Return false as the string is rejected
            }
        }

        // If the stack's top is the initial symbol, pop it
        if (Stack.top() == initial_symbol)
            Stack.pop();

        // Check if the PDA is in a final state and the stack is empty
        return final_state.find(state) != final_state.end() && Stack.size() == 0;
    }

private:
    int state;                          
    char initial_symbol;                
    stack<char> Stack;                  
    set<int> states;                    
    set<char> alphabet;                 
    const map<int, map<char, map <char, pair<int, char>>>> f_transicion; 
    int initial_state;                 
    set<int> final_state;               
};

// Function to create and configure a PDA according to the grammar S -> aSb | ab
PDA pda_creation() {
    set<int> states{0, 1};
    set<char> alphabet = {'a', 'b'};
    char initial_symbol = 'S';  
    int initial_state = 0; 
    // Set of final states (PDA is considered accepting if it reaches state 1)
    set<int> final_state = {1};
    // Transition function that defines how the PDA behaves
    map<int, map<char, map <char, pair<int, char>>>> f_transicion;
    // Transitions:
    // - In state 0, reading 'a' with 'S' at the top of the stack, go to state 0 and push 'b' onto the stack
    f_transicion[0]['a'][initial_symbol] = make_pair(0, 'b');
    // - In state 0, reading 'a' with 'b' at the top of the stack, go to state 0 and push another 'b' onto the stack
    f_transicion[0]['a']['b'] = make_pair(0, 'b'); 
    // - In state 0, reading 'b' with 'b' at the top of the stack, go to state 1 and pop 'b' from the stack
    f_transicion[0]['b']['b'] = make_pair(1, ' ');
    // - In state 1, reading 'b' with 'b' at the top of the stack, stay in state 1 and pop 'b' from the stack
    f_transicion[1]['b']['b'] = make_pair(1, ' '); 
    
    // Create and return the PDA
    PDA pda(states, alphabet, f_transicion, initial_symbol, initial_state, final_state);
    return pda;
}

// Function to process a list of strings and determine which ones are accepted by the PDA
vector<string> process_strings(vector<string>& strings) {
    PDA pda = pda_creation(); 
    cout << "\nThe second algorithm proces the strings:";
    // Loop through each string in the vector
    for (auto i = strings.begin(); i != strings.end(); ) {
        // Check if the current string is accepted by the PDA
        
        if (pda.acceptance(*i)) {
            cout << "The string '" << *i << "' is accepted by the PDA" << endl;
            ++i;
        } else {
            cout << "The string '" << *i << "' is rejected by the PDA" << endl;
            // Erase the rejected string and update the iterator
            i = strings.erase(i);
        }
    }

    return strings;
}
