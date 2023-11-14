#include <bits/stdc++.h>
using namespace std;

#ifndef TASK3_VOLE_H
#define TASK3_VOLE_H

// Function to convert an integer to a two-character hexadecimal string
string counter(int i) {
    // Calculate the tens and ones places in the hexadecimal representation
    int tens = i / 16;
    int ones = i % 16;

    // Convert the tens place to the corresponding character
    char tensDigit = (tens < 10) ? '0' + tens : 'A' + (tens - 10);

    // Convert the ones place to the corresponding character
    char onesDigit = (ones < 10) ? '0' + ones : 'A' + (ones - 10);

    // Initialize an empty string to store the result
    string Ans = "";

    // Append the character representing the tens place to the result string
    Ans += tensDigit;

    // Append the character representing the ones place to the result string
    Ans += onesDigit;

    // Return the final two-character string representing the hexadecimal representation
    return Ans;
}

// Class representing a simple CPU with registers
class CPU {
private:
    // Private member variable tao store the CPU registers
    vector<string> Registers;

public:
    // Constructor initializes the Registers vector with 16 elements, each set to "00"
    CPU() ;

    // Set the value of a specific register (indexed by 'n') to the provided hexadecimal string 'Hex'
    void setRegister(int n, string Hex) ;

    // Clear the value of a specific register (indexed by 'n') by setting it to "00"
    void Clear(int n) ;

    // Retrieve and return the hexadecimal value of a specific register (indexed by 'n')
    string DisplayRegister(int n) ;
};

// Class representing a basic memory with read functionality from a file
class Memory {
protected:
public:
    // Public member variable to store memory contents as key-value pairs (address-value)
    map<string, string> memory;

    // Function to read memory contents from a file and populate the memory map
    void ReadFile(string FileName) ;

    // Function to clear all elements from the memory map
    void Clear() ;

    // Function to retrieve a constant reference to the memory map
    const map<string, string>& getMemoryMap() const ;
};

// Class representing the main machine, inheriting from the Memory class
class machine : public Memory {
private:
    Memory Storage;  // Instance of Memory for additional storage
    CPU Registers;   // Instance of CPU for managing registers
    int PC = 0;       // Program Counter to track the execution of instructions

    // Load the value from memory into a register
    void LoadRegisterFromMemory(int registerIndex, string memoryAddress) {
        Registers.setRegister(registerIndex, memory[memoryAddress]);
    }

    // Load a specific pattern into a register
    void LoadRegisterWithPattern(int registerIndex, string pattern) {
        Registers.setRegister(registerIndex, pattern);
    }

    // Store the value from a register into memory
    void StoreRegisterToMemory(int registerIndex, string memoryAddress) {
        if (memoryAddress == "00") {
            cout << "Value of register " << registerIndex << " : " << Registers.DisplayRegister(registerIndex) << "\n\n";
        } else {
            memory[memoryAddress] = Registers.DisplayRegister(registerIndex);
        }
    }

    // Move the value from one register to another
    void MoveRegisterToRegister(int sourceIndex, int destinationIndex) {
        Registers.setRegister(destinationIndex, Registers.DisplayRegister(sourceIndex));
    }

    // Add two registers using two's complement representation
    void AddRegistersTwoComplement(int resultIndex, char operandIndex1, char operandIndex2) {
        // Get the two operands from registers
        string C1 = "";
        C1 += operandIndex1;
        string C2 = "";
        C2 += operandIndex2;
        string operand1 = Registers.DisplayRegister(hexToDec(C1));
        string operand2 = Registers.DisplayRegister(hexToDec(C2));

        // Perform addition of two's complement
        int result = hexToDec(operand1) + hexToDec(operand2);

        // Handle overflow (if the result is larger than 255 or smaller than 0)
        if (result > 255 || result < 0) {
            // Handle overflow as needed for your application
            cerr << "Overflow occurred during addition." << endl;
            // You might want to set flags or take other actions based on your application's requirements
            // For simplicity, let's set the result to 0
            result = 0;
        }

        // Store the result in the specified register
        Registers.setRegister(resultIndex, decToHex(result));
    }

    // Jump to a specific memory address if the contents of a register are equal to zero
    void JumpIfEqual(int registerIndex, string memoryAddress) {
        if (Registers.DisplayRegister(registerIndex) == Registers.DisplayRegister(0)) {
            PC = hexToDec(memoryAddress);
        }
    }

    // Set the Program Counter to -1 to halt execution
    void HaltExecution() {
        PC = -1;
    }

    // Convert hexadecimal string to decimal integer
    int hexToDec(const string& hexStr) {
        int decimalValue;
        stringstream ss;
        ss << hex << hexStr;  // Set the stringstream to interpret the input as hexadecimal
        ss >> decimalValue;   // Read the hexadecimal string as an integer in decimal
        return decimalValue;
    }

    // Convert decimal integer to a two-digit hexadecimal string
    string decToHex(int decimalValue) {
        stringstream ss;
        ss << hex << uppercase << setw(2) << setfill('0') << decimalValue;
        return ss.str();
    }

    // Friend function declaration for the Menu function
    friend void Menu(machine& M);

    // Display the contents of memory (address: instruction)
    void DisplayMemory() {
        cout << "\nAddress : Instruction\n";
        for (const auto& entry : memory) {
            cout << entry.first << ": " << entry.second << "\n";
        }
        cout << endl;
    }

public:
    friend void Menu();  // Friend function declaration for the Menu function

    // Constructor to initialize the machine by reading instructions from a file
    machine(string FileName) ;

    // Run the machine until termination, executing instructions
    void RunFull() ;
    // Run the machine step by step, executing instructions
    void RunSBS() ;

    // Display the current machine state, program counter, instruction register, and registers
    void Display() ;

    // Display the contents of all registers
    void DisplayRegisters() ;

    // Reset all registers to '00'
    void ResetRegister() ;

};


#endif //TASK3_VOLE_H
