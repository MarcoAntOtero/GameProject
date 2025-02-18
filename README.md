Space Shooter Game
A 2D space shooter game built using SFML (Simple and Fast Multimedia Library). The player controls a spaceship, fights enemies, and survives as long as possible. The game features dynamic background tiling, a zoomed-in view, and a health bar that reflects the player's current health.

Features
Player Controls:

Move the spaceship using W, A, S, D.

Shoot bullets using Space or Left Mouse Button.

Enemies:

Enemies spawn randomly and follow the player.

Destroy enemies to earn points and restore health.

Health Bar:

A dynamic health bar reflects the player's current health.

Background:

The background tiles dynamically as the player moves, creating an infinite scrolling effect.

Zoomed View:

The camera zooms in on the player, providing a focused view of the action.

How to Play
Movement:

Use W, A, S, D to move the spaceship.

Shooting:

Press Space or Left Mouse Button to shoot bullets.

Survive:

Avoid enemy bullets and destroy enemies to stay alive.

Health:

Keep an eye on the health bar. Destroy enemies to restore health.

Installation
Dependencies:

Ensure you have SFML installed on your system.

Download SFML from https://www.sfml-dev.org/.

Build the Game:

Clone the repository:

bash
Copy
git clone https://github.com/your-username/space-shooter.git
Navigate to the project directory:

bash
Copy
cd space-shooter
Compile the game using your preferred build system (e.g., CMake, Makefile, or IDE).

Run the Game:

Execute the compiled binary:

bash
Copy
./space-shooter
File Structure
Copy
space-shooter/
├── Resources/              # Game assets (textures, fonts, etc.)
├── src/                    # Source code
│   ├── Game.cpp            # Main game logic
│   ├── Game.h              # Game class definition
│   ├── Player.cpp          # Player logic
│   ├── Player.h            # Player class definition
│   ├── Enemy.cpp           # Enemy logic
│   ├── Enemy.h             # Enemy class definition
│   ├── Bullet.cpp          # Bullet logic
│   ├── Bullet.h            # Bullet class definition
│   └── main.cpp            # Entry point
├── CMakeLists.txt          # CMake build configuration
└── README.md               # This file


Controls
Key	Action
W	Move Up
A	Move Left
S	Move Down
D	Move Right
Space	Shoot
Left Mouse Button	Shoot
Escape	Quit Game
Credits
Developer: Marco Otero

SFML: https://www.sfml-dev.org/

Assets: Game textures from Itch.io and one of my own creation.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Contributing
Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.
