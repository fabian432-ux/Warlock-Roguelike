# Warlock Console Roguelike

## Description
A turn-based, text-adventure roguelike written in C++. You play as a Warlock battling through a gauntlet of increasingly difficult enemies in a single run. Survive 10 consecutive fights by managing your health, utilizing black magic, summoning demons, and buying permanent upgrades at the shop between rounds. If your HP hits zero, your run is over.

## Features
* **Turn-Based Combat:** Engage in tactical battles managing your HP, Attack, and Black Magic resources.
* **Warlock Abilities:** * *Make Them Suffer:* Deal direct magic damage to your enemy.
    * *Summoning Portal:* Expend Black Magic to summon up to 3 demons to fight alongside you.
    * *Magic Circle:* Gain immunity from enemy attacks for a turn (has a cooldown).
* **Run Progression & Shop System:** Earn gold after victorious battles to spend in the shop.
    * Increase maximum HP and Attack damage.
    * Permanently buff your summoned demons' stats for the rest of the run.
    * Reduce the cooldown of your Magic Circle ability.
* **Scaling Difficulty:** Enemies gain +5 HP and +5 Attack after every successful encounter.

## How to Compile and Run

### Prerequisites
You need a C++ compiler installed on your system (such as GCC/G++ for Linux/Windows or Clang for macOS).

### Compilation
1. Open your terminal or command prompt.
2. Navigate to the directory where you saved `main.cpp`.
3. Run the following command to compile the game:
   ```bash
   g++ main.cpp -o warlock
