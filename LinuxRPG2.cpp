#include <iostream>     // Required for input/output operations(e.g, std::cout, std::cin)
#include <string>       // Required for using the std::string class for string manipulation
#include <vector>       // Required for using the std::vector class for dynamic arrays
#include <map>          // Required for using the std::map class for key-value pair storage
#include <algorith>     // Required for using algorithms like std::unique
#include <sstream>      // Required for string stream processing (e.g, std::istringstream)

// Define a structure to represent a quest in the game

struct Quest {
    std::string name;        //The name of the quest
    std::string description; // A brief description of what the quest involves
    std::string status;     // The current status of the quest (e.g, "active", "completed")
};

// Define a structure to represent a file or directory in the virtual file system
struct FileSystemObject {
    std::string type;       // The type of object ("file" or "directory")
    std::string description; // A brief description of the object
    std::string content;    // The content of the file (empty for directories)
    bool hidden = false;    //Whether the object is hidden (default is set to false)
};

// Define a structure to represent an NPC (Non-Player Character) in the game
struct NPC {
    std::string name;           // The name of the NPC
    std::string description;   // A brief description of the NPC
    std::string dialogue;       // The dialogue the NPC will speak when interacted with
};

// Define a structure to represent a Monster in the game
struct Monster {
    std::string name;        // The name of the monster
    std::string description; // A brief description of the monster
    int health;              // The health points of the monster
};

// Define the main game class that will manage the state and logic of the game
class LinuxRPG{
private:
    // Member variables to hold the game's state
    std::string current_path;           // Rhe current location of the player in the file system
    std::vector<std::string> inventory; // The player's inventory, a dynamic array of items
    std::vector<Quest> quests;          // The list of active quests the player has
    std::map<std::string, std::map<std::string, FileSystemObject>> file_system; // The virtual file system structure
    std::map<std::string, std::vector<NPC>> npcs; // The NPCs available in each location
    std::map<std::string, std::vector<Monster>> monsters; // The monsters present in each location

public:
    // Constructor to initialize the game state when an instance of LinuxRPG is created
    LinuxRPG() {
        // Set the initial current path to the home directory
        current_path = "/home/user";

        // Populate the player's invenory with some initial items
        inventory = {"rusty_key", "digital_compass", "encrypted_scroll"}

        
    }
}