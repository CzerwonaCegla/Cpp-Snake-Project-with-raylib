# Repo for a clone of snake made in c++ with raylib

# **🐍 Snake Game (C++ / raylib)**

A classic **Snake game** written in **C++** using the **raylib** graphics library.  
The player controls a snake on a grid, eats apples to grow longer, and must avoid colliding with itself.

---

## **🎮 Gameplay**

- Move the snake using the **arrow keys**
- Eat apples to grow
- The game ends when the snake collides with itself
- The snake wraps around the window edges

---

## **🧱 Project Structure**

├── Main.cpp # Game loop, rendering, input handling
├── Snake.cpp # Snake logic (movement, growth, collision)
├── Apple.cpp # Apple spawning and rendering
├── Snake.h
├── Apple.h
├── RenderableObject.h
├── GlobalGameParameters.h

### **Key Components**

- **Snake**
  - Handles movement, direction changes, growth, and self-collision
  - Implemented using a vector of grid-aligned segments

- **Apple**
  - Spawns at random grid-aligned positions
  - Relocates after being eaten

- **GlobalGameParameters**
  - Stores window size, grid size, colors, and timing constants

- **RenderableObject**
  - Base class for drawable game objects

---

## **🛠️ Requirements**

- **C++17** or newer
- **raylib** (https://www.raylib.com/)
- A compiler such as:
  - `g++`
  - `clang`
  - MSVC

---

## **⌨️ Controls**
### **Key	Action**
- ↑ Arrow	Move Up
- ↓ Arrow	Move Down
- ← Arrow	Move Left
- → Arrow	Move Right

Opposite-direction turns are automatically prevented.

## **⚙️ Game Logic Notes**

- The game updates every globalGameTickSpeed seconds

- Movement is grid-based using globalGridWidth

- Snake collision is checked by comparing segment positions

- Apple positions are randomly generated but always grid-aligned

## **🚀 Possible Improvements**

- Score counter

- Game over screen & restart option

- Sound effects

- Increasing speed as the snake grows

- Wall collision instead of wrapping

- High-score saving

## **📄 License**

This project is provided for educational purposes.
Feel free to modify, extend, and experiment with it.