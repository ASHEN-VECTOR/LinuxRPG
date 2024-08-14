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
public:
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

//Define the Quest class to represent player objectives

class Quest{
public: std::string name;           //Name of the quest
        std::string description;    //Description of the quest
        std::string status;         //Current status of the quest (e.g., "active", "completed")

        //Constructor to initialize a Quest with name, description, and status
        Quest(std::string n, std::string d, std::string s)
        : name(n), description(d), status(s) {}
};

// Define the main Game class to manage game state and logic
class Game {
private:
    FileSystem fileSystem;      //  Our game world
    std::string currentPath;    //  Player's current location
    std::vector<std::string> inventory;      //  Player's inventory
    std::vector<Quest> quests;         //  Active Quests
    std::map<std::string, std::vector<NPC>> npcs;             //  NPCs organized by location
    std::map<std::string, std::vector<Monster>> monsters;         //  Monsters by location

public:
    // Constructor to initialize the game state
    Game() : currentPath("/home/user")  {
        // Initialize player's inventory
        inventory = {"rusty_key", "digital_compass", "encrypted scroll"};

        // Initialize quests
        quests = {
            Quest("Debug the Kernel", "Find and fix the bug in the heart of the system", "active"),
            Quest("Recover Lost Data","Retrieve the imporant files from a corrupted drive.", "active"),
            Quest("The Fourth Wall", "Investigate the strange girl who seems to know more than she should.", "active")
        };

        //Initialize NPCs
        npcs["/home/user"] = {
            NPC("Sudo", "A wise old wizard with root privileges", "Greetings, young sysadmin. Remember with great power comes great responsibility." ),
            NPC("Grep", "A keen-eyed scout, always searching for patterns", "Hail, traveler Need help finding something in the vast data streams?" ),
            NPC ("Monika", "A mysterious girl with emerald eyes and a white bow in her hair", "Hello, player! Welcome to this little game within a game. Remember, the choices you make here matter.. perhaps more than you realize. Ahaha~")
        };

        // Initalize monsters
        monsters["/"] = {
            Monster("Kernel Panic", "A chaotic force threatening system stability", 100),
            Monster("Stack Overflow", "A data beast consuming memory", 75)
        };
    }

    // Method to handle commands from the player
    void handleCommand(const std::string& command) {
        if (command == "inventory") {
            std::cout << "Inventory: ";
            for (const auto& item : inventory) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
        //Add more command handling logic here
    }

    // Main game loop
    void run() {
        std::string command;
        while(true) {
            std::cout << "user@linuxrpg:~$ ";
            std::getline(std::cin, command);
            if (command == "exit") break;
            handleCommand (command);
        }
    }
};

// Main game loop



//The main function and entry point of my program 
int main(){
    //Prints a greeting to the user
    std::cout << "Welcome to the LinuxRPG!" << std::endl;
    // Return a 0 to indicate successful program execution
    return 0;
}