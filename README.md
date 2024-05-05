# **Robots🤖 and walls🧱, what more could you want?**

*Authors*: **Matyáš Oujezdský** (xoujez04), **Milan Vrbas** (xvrbas01)

---

## **☰ Menu**
By clicking on the menu icon, you can perform following actions:

- **🤖 Add Robot to scene**: Drag and drop a robot into the scene.
  
- **🧱 Add Wall to scene**: Drag and drop a wall into the scene.

- **💾 Save Scene**: Save your current scene as a .json file.

- **📂 Load Scene**: Load a previously saved scene with all objects.

- **▶️ Start Simulation**: Begin the simulation after adding objects and setting parameters.

- **❓ Help**: Open this help window.

---

## **🛠 Setting Object Parameters**
### **🤖 Robot**
By right-clicking on specific robot, you are able to adjust it's parameters. The list of all options is following:
- **🔄 Rotate**: Use this option to manually rotate the robot to a desired direction.
.
- **🤖/🕹 Set robot player status**: Toggle between `Autonomous` and `Player controlled` modes.
    - **🤖 Autonomous**: The robot will automatically move forward until it detects a wall, then it will turn.
    - **🕹 Player controlled**: You can choose between two players for manual control:
      - **🎮 Player 1**: Use arrow keys (Up, Down, Left, Right) for movement.
      - **🎮 Player 2**: Use W, S, A, D keys for movement.

- **🚀 Set movement speed**: Adjust the speed parameter to set the robot's movement speed.

- **📏 Set detection range**: Define the range within which the robot can detect obstacles or walls.

- **📐 Set detection angle**: Defines the angle by which the robot turns when it detects an obstacle.

- **🔀 Set turning direction**: Choose the direction in which the robot will turn when encountering an obstacle (clockwise or cunter clockwise).

- **🎨 Change icon**: Customize the appearance of the robot by selecting a different icon or image.

### **🧱 Wall**
If you hover over the edge of the wall, you can drag the mouse pointer to either enlarge or shrink the wall size.

---

## **🎮 Robot Control:**
| Control     | Player 1 | Player 2  |
|-------------|----------|-----------|
| **Up**      | ↑        | W         |
| **Down**    | ↓        | S         |
| **Left**    | ←        | A         |
| **Right**   | →        | D         |

---

## 🖱 **Multi-Object Selection**
Drag your mouse over multiple objects to select them, then relocate them together by dragging.

---------------------------------------------------------------------------------------------------------------

Disclaimer:
- One file in this project was taken from a public GitHub repository and thus not written by the authors of this project
    - file: `json.hpp` the repository: `https://github.com/nlohmann/json`

- Features not implemented, although planned:
    - Fully fledged out collision detection with all edge cases
        - Walls can be resized through other objects
        - When walls are resized outside of the scene, they behave unexpectedly
        - Items stay "frozen" when dragged on top of other items (plan was to stay closest to mouse as possible without colliding)

- Extra features planned above the scope of this assignment:
    - Robots being able to shoot and destroy other robots
    - Two player robots having a race through a track built with walls
    - Walls "snapping" to each other when placed close enough
