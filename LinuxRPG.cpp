#include <iostream> // For input/output operations
#include <string> // For string manipulation
#include <vector> // For dynamic arrays
#include <map> // For key-value pair storage
#include <algorithm> // for various algorithms like sorting
#include <sstream> // for string stream processing

//Defining the FileSystem class that will become our main game world
class FileSystem {
public:
    // Defining a Structure. The Structure will create nodes (files or directories) that populate inside the FileSystems our Constructor makes
    struct FSNode{
        std::string type;        // Can be a "file" or "directory"
        std::string description; // A brief description of the node
        std::string content;    // Content of the file (currently empty for directories)
        bool hidden = false;    // Whether the node is hidden from the user or not
    };


};

//The main function and entry point of my program 
int main(){
    //Prints a greeting to the user
    std::cout << "Welcome to the LinuxRPG!" << std::endl;
    // Return a 0 to indicate successful program execution
    return 0;
}