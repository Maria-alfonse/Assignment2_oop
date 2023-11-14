#include "VOLE.h"
using namespace std;


// Constructor initializes the Registers vector with 16 elements, each set to "00"
CPU :: CPU() : Registers(16, "00") {}

// Set the value of a specific register (indexed by 'n') to the provided hexadecimal string 'Hex'
void CPU :: setRegister(int n, string Hex) {
    Registers[n] = Hex;
}

// Clear the value of a specific register (indexed by 'n') by setting it to "00"
void CPU :: Clear(int n) {
    Registers[n] = "00";
}

// Retrieve and return the hexadecimal value of a specific register (indexed by 'n')
string CPU :: DisplayRegister(int n) {
    return Registers[n];
}




// Function to read memory contents from a file and populate the memory map
void Memory :: ReadFile(string FileName) {
    // Open the file for reading
    fstream MyFile;
    int PC = 0;  // Program Counter for tracking memory addresses

    // Attempt to open the file
    MyFile.open(FileName + ".txt", ios::in);

    if (MyFile.is_open()) {
        string line;

        // Read each line from the file
        while (getline(MyFile, line)) {
            // Generate the hexadecimal address using the counter function
            string Address = counter(PC);

            // Insert the first two characters of the line into memory at the generated address
            memory.insert({Address, line.substr(0, 2)});

            // Move to the next address
            PC++;

            // Generate the next hexadecimal address
            Address = counter(PC);

            // Insert the next two characters of the line into memory at the generated address
            memory.insert({Address, line.substr(2, 2)});

            // Move to the next address
            PC++;
        }
    } else {
        // Display an error message if the file cannot be opened
        cout << "Error opening file: " << FileName << ".txt" << '\n';
    }

    // Close the file after reading
    MyFile.close();
}

// Function to clear all elements from the memory map
void Memory :: Clear() {
    memory.clear(); // Clears all elements from the map
}

// Function to retrieve a constant reference to the memory map
const map<string, string>&  Memory :: getMemoryMap() const {
    return memory;
}





void Menu(machine& M) {
    int x;

    // Display menu options
    cout << "1-Run step by step\n";
    cout << "2-Run full code\n";
    cout << "3-Reset\n";

    // Get user input for menu choice
    cin >> x;

    // Execute corresponding action based on user input
    if (x == 1) {
        // Run the machine step by step
        M.RunSBS();

        // Check if the machine has terminated
        if (M.PC == -1) {
            return;
        }

        // Recursively call Menu for additional user input
        Menu(M);
    } else if (x == 2) {
        // Run the machine with full execution
        M.RunFull();
        return;  // Exit the function after full execution
    } else if (x == 3) {
        // Reset all registers and call Menu for additional user input
        M.ResetRegister();
        Menu(M);
    }
}

// Constructor to initialize the machine by reading instructions from a file
machine :: machine(string FileName) {
    ReadFile(FileName);
}

// Run the machine until termination, executing instructions
void machine :: RunFull() {
    while (PC != -1) {
        string hxPC = counter(PC);
        if (memory[hxPC][0] == '1') {
            string pattern = memory[counter(PC + 1)];
            LoadRegisterFromMemory(memory[hxPC][1] - '0', pattern);
        } else if (memory[hxPC][0] == '2') {
            string pattern = memory[counter(PC + 1)];
            LoadRegisterWithPattern(memory[hxPC][1] - '0', pattern);
        } else if (memory[hxPC][0] == '3') {
            string pattern = memory[counter(PC + 1)];
            StoreRegisterToMemory(memory[hxPC][1] - '0', pattern);
        } else if (memory[hxPC][0] == '4') {
            string C = "";
            C += memory[counter(PC + 1)][1];
            MoveRegisterToRegister(memory[counter(PC + 1)][0] - '0', hexToDec(C));
        } else if (memory[hxPC][0] == '5') {
            AddRegistersTwoComplement(memory[hxPC][1] - '0', memory[counter(PC + 1)][0], memory[counter(PC + 1)][1]);
        } else if (memory[hxPC][0] == 'B' || memory[hxPC][0] == 'b') {
            int check = PC;
            string pattern = memory[counter(PC + 1)];
            JumpIfEqual(memory[hxPC][1] - '0', pattern);
            if (check != PC) {
                PC -= 2;
            }
        } else if (memory[hxPC][0] == 'C' || memory[hxPC][0] == 'c') {
            Display();
            PC = -1;
            return;  // Set PC to -1 to indicate termination
        }
        PC += 2;
    }
    Display();
}

// Run the machine step by step, executing instructions
void machine :: RunSBS() {
    if (PC == -1) {
        return;
    }
    string hxPC = counter(PC);
    if (memory[hxPC][0] == '1') {
        string pattern = memory[counter(PC + 1)];
        LoadRegisterFromMemory(memory[hxPC][1] - '0', pattern);
    } else if (memory[hxPC][0] == '2') {
        string pattern = memory[counter(PC + 1)];
        LoadRegisterWithPattern(memory[hxPC][1] - '0', pattern);
    } else if (memory[hxPC][0] == '3') {
        string pattern = memory[counter(PC + 1)];
        StoreRegisterToMemory(memory[hxPC][1] - '0', pattern);
    } else if (memory[hxPC][0] == '4') {
        string C = "";
        C += memory[counter(PC + 1)][1];
        MoveRegisterToRegister(memory[counter(PC + 1)][0] - '0', hexToDec(C));
    } else if (memory[hxPC][0] == '5') {
        AddRegistersTwoComplement(memory[hxPC][1] - '0', memory[counter(PC + 1)][0], memory[counter(PC + 1)][1]);
    } else if (memory[hxPC][0] == 'B' || memory[hxPC][0] == 'b') {
        int check = PC;
        string pattern = memory[counter(PC + 1)];
        JumpIfEqual(memory[hxPC][1] - '0', pattern);
        if (check != PC) {
            PC -= 2;
        }
    } else if (memory[hxPC][0] == 'C' || memory[hxPC][0] == 'c') {
        Display();
        PC = -1;
        return;  // Set PC to -1 to indicate termination
    }
    PC += 2;
    Display();
    DisplayMemory();
}

// Display the current machine state, program counter, instruction register, and registers
void machine :: Display() {
    string hxPC = counter(PC);
    cout << "Machine State:" << endl;
    cout << "hxPC: " << hxPC << endl;
    cout << "IR: " << memory[hxPC] << memory[counter(PC + 1)] << endl;
    cout << "Registers: \n";
    DisplayRegisters();
}

// Display the contents of all registers
void machine :: DisplayRegisters() {
    for (int i = 0; i < 16; ++i) {
        cout << "R" << i << " : " << Registers.DisplayRegister(i) << endl;
    }
}

// Reset all registers to '00'
void machine :: ResetRegister() {
    for (int i = 0; i < 16; ++i) {
        Registers.Clear(i);
    }
}
