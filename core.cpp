#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <limits>

int main() {
    using std::cout;
    using std::cin;
    using std::string;
    using std::ofstream;
    using std::ifstream;

    int health = 100;
    int level = 0;
    int exp = 0;
    int gold = 0;
    int maxHealth = 100;
    int healthPotion = 0;

    auto saveGame = [&]() {
        ofstream saveFile("save.txt");
        if (saveFile.is_open()) {
            saveFile << health << "\n"
                     << level << "\n"
                     << exp << "\n"
                     << gold << "\n"
                     << maxHealth << "\n"
                     << healthPotion << "\n";
            saveFile.close();
            cout << "Game saved successfully!\n";
        } else {
            cout << "Error saving the game.\n";
        }
    };

    auto loadGame = [&]() {
        ifstream loadFile("save.txt");
        if (loadFile.is_open()) {
            loadFile >> health >> level >> exp >> gold >> maxHealth >> healthPotion;
            loadFile.close();
            cout << "Game loaded successfully!\n";
        } else {
            cout << "No save file found. Starting a new game.\n";
        }
    };

    loadGame();

    string choice;

    while (true) {
        cout << "\n(hunt, shop, stats, heal, quit, reset)\n";
        cout << "> ";
        cin >> choice;

        if (choice == "hunt") {
            cout << "Choose your opponent:\n";
            cout << "[1] Goblin (Damage: 20, Gold: +15, EXP: +1)\n";
            cout << "[2] Orc (Damage: 85, Gold: +30, EXP: +3)\n";
            cout << "[3] Giant Bee (Damage: 140, Gold: +50, EXP: +6)\n";
            cout << "[4] Bandit (Damage: 250, Gold: +150, EXP: +8)\n";
            cout << "> ";
            int enemyChoice;
        
            if (!(cin >> enemyChoice)) {
                cin.clear(); 
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input. Returning to main menu.\n";
                continue; 
            }
        
            int enemyDamage = 0;
            int enemyGold = 0;
            int enemyExp = 0;
            string enemyName;
        
            switch (enemyChoice) {
                case 1:
                    enemyName = "Goblin";
                    enemyDamage = 20;
                    enemyGold = 15;
                    enemyExp = 1;
                    break;
                case 2:
                    enemyName = "Orc";
                    enemyDamage = 85;
                    enemyGold = 30;
                    enemyExp = 3;
                    break;
                case 3:
                    enemyName = "Giant Bee";
                    enemyDamage = 140;
                    enemyGold = 50;
                    enemyExp = 6;
                    break;
                case 4:
                    enemyName = "Bandit";
                    enemyDamage = 250;
                    enemyGold = 150;
                    enemyExp = 8;
                    break;
                default:
                    cout << "Invalid choice. Returning to main menu.\n";
                    continue;
            }
    
            cout << "You are fighting a " << enemyName << "!\n";
            health -= enemyDamage;
        
            if (health <= 0) {
                cout << "You took " << enemyDamage << " damage and have 0 health left.\n";
                cout << "You died. Game over.\n";
                health = 100;
                level = 0;
                exp = 0;
                gold = 0;
                break; 
            }
            system("cls");
            cout << "You took " << enemyDamage << " damage and have " << health << " health left.\n";
            gold += enemyGold;
            exp += enemyExp;
            cout << "You earned " << enemyGold << " gold and " << enemyExp << " EXP.\n";
            cout << "You now have " << gold << " gold and " << exp << " EXP.\n";
        
            int expThreshold = 10 + (level * 5);
            if (exp >= expThreshold) {
                level++;
                exp -= expThreshold; 
                cout << "Congratulations! You leveled up to level " << level << "!\n";
                maxHealth += 10; 
                health = maxHealth;
            }
        
        }
        else if (choice == "cls") {
            system("cls");
        }
        else if (choice == "stats") {
            cout << "Health: " << health << "\n";
            cout << "Level: " << level << "\n";
            cout << "Experience: " << exp << "\n";
            cout << "Gold: " << gold << "\n";
            cout << "Max Health: " << maxHealth << "\n";
            cout << "Health Potions: " << healthPotion << "\n\n";
        }
        else if (choice == "heal") {
            if (health == maxHealth) {
                cout << "You already have max health\n\n";
            }
            else if (healthPotion == 0) {
                cout << "You don't have any potions\n\n";
            }
            else {
                health += 30;
                if (health > maxHealth) health = maxHealth; // Cap health at maxHealth
                healthPotion -= 1;
                cout << "You have successfully healed\n\n";
            }
        } 
        else if (choice == "shop") {
            cout << "[0] exit\n";
            cout << "[1] health potion - 15 gold\n";
            cout << "[2] max health (+10) - 50 gold\n";
            cout << "> ";
            int bought;
            cin >> bought;
            if (bought == 1) {
                if (gold >= 15) {
                    gold -= 15;
                    healthPotion += 1;
                    cout << "You have bought a health potion\n\n";
                }
                else {
                    cout << "You don't have enough gold\n\n";
                }
            }
            else if (bought == 2) {
                if (gold >= 50) {
                    gold -= 50;
                    maxHealth += 10;
                    cout << "You have bought +10 max health\n\n";
                }
                else {
                    cout << "You don't have enough gold\n\n";
                }
            }
            else {
                cout << "Goodbye\n\n";
            }
        }
        else if (choice == "quit") {
            saveGame(); // Save the game before quitting
            break;
        }
        else if (choice == "color"){
            system("color a");
        }
        else if (choice == "reset") {
            health = 20;
            level = 0;
            exp = 0;
            gold = 100;
            maxHealth = 100;
            healthPotion = 0;
        }

    }


    return 0;
}