#include "VOLE.cpp"
using namespace std;


int main() {
    // Create a machine instance named FCB, loading instructions from the "INPUT" file
    machine FCB("INPUT");

    // Call the Menu function to interact with and control the machine
    Menu(FCB);

    return 0;
}

