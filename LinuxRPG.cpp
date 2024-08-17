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
    
        // Declarations for the functions
    void handleCommand(const std::string& cmd);
    void showHelp();
    void showCurrentPath() const;
    void listDirectory(const std::vector<std::string>& args, const std::string& currentPath, const FileSystem& fileSystem) const;
    void changeDirectory(const std::vector<std::string>& args, std::string& currentPath, const FileSystem& fileSystem);
    void catFile(const std::vector<std::string>& args, const std::string& currentPath, const FileSystem& fileSystem) const;
    void showInventory() const;  // No additional arguments needed
    void showQuests() const;  // No additional arguments needed
    void talkToNPC(const std::vector<std::string>& args, const std::string& currentPath, const std::map<std::string, std::vector<NPC>>& npcs);
};

// Process and execute player commands
void Game::handleCommand(const std::string&cmd) {
    //Split the command into words
    std::vector<std::string> words;
    std::istringstream iss(cmd);
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

// If no command was entered, return
if (words.empty()) return;

// Extract the main command and it's arguements
std::string command = words[0];
std::vector<std::string> args(words.begin() + 1, words.end());

// Execute the appropriate action based on the command
if (command == "help") {
        showHelp();
}   else if (command == "pwd") {
        showCurrentPath();
}   else if (command == "ls") {
        listDirectory(args, currentPath, fileSystem);
}   else if (command == "cd") {
        changeDirectory(args, currentPath, fileSystem);
}   else if (command == "cat") {
        catFile(args, currentPath, fileSystem);
}   else if (command == "inventory") {
        showInventory();
}   else if (command == "quests") {
        showQuests();
}   else if (command == "talk") {
        talkToNPC(args, currentPath, npcs);
    } else {
        std::cout << "Command not recognized. Try 'help' for a list of commands." << std::endl;
    }
}

// Display available commands
void Game::showHelp() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  help         - Show this help message" << std::endl;
    std::cout << "  pwd          - Print current directory" << std::endl;
    std::cout << "  ls           - List directory contents" << std::endl;
    std::cout << "  cd [dir]     - Change directory" << std::endl;
    std::cout << "  cat [file]   - View file contents" << std::endl;
    std::cout << "  inventory    - Show inventory" << std::endl;
    std::cout << "  quests       - Show active quests" << std::endl;
    std::cout << "  talk [npc]   - Talk to an NPC" << std::endl;
    std::cout << "  exit         - Exit the game" << std::endl;
}

// Display current path
void Game::showCurrentPath() const {
    std::cout << currentPath << std::endl;
}

// List contents of a directory
void Game::listDirectory(const std::vector<std::string>& args, const std::string& currentPath, const FileSystem& fileSystem) const {
    std::string path = currentPath;
    if (!args.empty()) path = args[0];

    auto nodeIterator = fileSystem.nodes.find(path);
    if (nodeIterator == fileSystem.nodes.end()) {
        std::cout << "Directory not found: " << path << std::endl;
        return;
    }

    for (const auto& entry : nodeIterator->second) {
        if (!entry.second.hidden) {
            std::cout << entry.first << "\t" << entry.second.type << "\t" << entry.second.description << std::endl;
        }
    }
}

// Change current directory
void Game::changeDirectory(const std::vector<std::string>& args, std::string& currentPath, const FileSystem& fileSystem) {
    if (args.empty()) {
        std::cout << "Usage: cd [directory]" << std::endl;
        return;
    }

    std:: string newPath = args[0];
    if (newPath[0] != '/') {
        newPath = currentPath + "/" + newPath;

    }

    if ( fileSystem.nodes.find(newPath) != fileSystem.nodes.end()) {
        currentPath = newPath;
    } else {
        std::cout << "Directory not found: " << newPath << std::endl;
    
    }
}

// Display contents of a file
void Game::catFile(const std::vector<std::string>& args, const std::string& currentPath, const FileSystem& fileSystem) const {
    if (args.empty()) {
        std::cout << "Usage: cat [file]" << std::endl;
        return;
    }

    std::string filePath = currentPath + "/" + args[0];

    if (fileSystem.nodes.find(filePath) == fileSystem.nodes.end()) {
        std::cout << "File not found: " << filePath << std::endl;
        return;
    }

    const auto& node = fileSystem.nodes.at(filePath).at(args[0]);
    if (node.type == "file") {
        std::cout << node.content << std::endl;
    } else {
        std::cout << args[0] << " is not a file." << std::endl;
    }
} 

// Function to handle talking to an NPC
void Game::talkToNPC(const std::vector<std::string>& args, const std::string& currentPath, const std::map<std::string, std::vector<NPC>>& npcs) {
    if (args.empty()) {
        std::cout << "Usage: talk [npc]" << std::endl;
        return;
    }

    const std::string& npcName = args[0];
    if (npcs.find(currentPath) != npcs.end()) {
        for (const NPC& npc : npcs.at(currentPath)) {
            if (npc.name == npcName) {
                std::cout << npc.dialogue << std::endl;
                return;
            }
        }
        std::cout << "No NPC named " << npcName << " found here." << std::endl;
    } else {
        std::cout << "No NPCs found in this location." << std::endl;
    }
}

//The main function and entry point of my program 
int main(){
    // Create an instance of the Game class
    Game game;

    // Prints a greeting to the user
    std::cout << "Welcome to the LinuxRPG!" << std::endl;

    // Start the main game loop
    game.run();

    // Return a 0 to indicate successful program execution
    return 0;
}

// Function to display the player's inventory
void Game::showInventory() const {
    // Assuming you want to print the contents of the player's inventory
    std::cout << "Inventory:" << std::endl;
    for (const std::string& item : inventory) {
        std::cout << "- " << item << std::endl;
    }
}

// Function to display the active quests
void Game::showQuests() const {
    // Assuming you want to print the list of active quests
    std::cout << "Active Quests:" << std::endl;
    for (const Quest& quest : quests) {
        std::cout << "- " << quest.name << ": " << quest.description << " [" << quest.status << "]" << std::endl;
    }
}