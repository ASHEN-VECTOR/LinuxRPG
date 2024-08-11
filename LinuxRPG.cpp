#include <iostream> // For input/output operations
#include <string> // For string manipulation
#include <vector> // For dynamic arrays
#include <map> // For kgey-value pair storage
#include <algorithm> // for various algorithms like sorting
#include <sstream> // for string stream processing

//Defining the FileSystem class that will become our main game world
class FileSystem {
public:
    // Defining a Structure. The Structure will create nodes (files or directories) that populate inside the FileSystems our Constructor makes
    struct FSNode {
        std::string type;        // Can be a "file" or "directory"
        std::string description; // A brief description of the node
        std::string content;    // Content of the file (currently empty for directories)
        bool hidden = false;    // Whether the node is hidden from the user or not, allows for secret files and directories
    };

    //Use a nested map to represent out file system structure
    std::map<std::string, std::map<std::string, FSNode>> nodes;

    //Constructor to initialize our file system with some basic structure
    FileSystem() {

            // Create a root directory
            nodes["/"] = {
                {"home", {"directory", "The realm of user domains"}},
                {"etc", {"directory", "A labyrinth of system configurations"}}

            };
            // Create a home directory with a user subdirectory
            nodes["/home"] = {
                {"user", {"directory", "Your personal sanctuary in this digital realm"}}
            };
    }

};

// Notes on nested 'nodes' map:
// - Outer map: Keys are full paths (such as "/home/user")
// - Inner map: Keys are node names, values are FSNode structs
// - The constructor initializes the actual file system structure:
// - The constructor creates a root directory ("/") with "home" and "etc" subdirectories
// - The constructor creates a "/home" directory with a "user" subdirectory
// - This is just our starting point and can be expanded later. 

//----- Define the NPC (Non-Player Character) class
class NPC {
    std::string name; // Name of the NPC
    std::string description; // Description of the NPC
    std:: string dialogue; // What the NPC says when talked to

    // Constructor to initialize an NPC with name, description, and dialogue
    NPC(std::string n, std::string d, std::string di)
        : name(n), description(d), dialogue(di) {}
};

//Define the Monster class for potential enemies in our game
class Monster {
public:
    std::string name;           // Name of the monster
    std::string description;    // Description of the monster
    int health;                 // Health points of the monster

    // Constructor to initialize a Monster with name, description, and health
    Monster(std::string n, std:: string d, int h)
        : name(n), description(d), health(h) {}
};


//The main function and entry point of my program 
int main(){
    //Prints a greeting to the user
    std::cout << "Welcome to the LinuxRPG!" << std::endl;
    // Return a 0 to indicate successful program execution
    return 0;
}