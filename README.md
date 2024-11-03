### ECOSYS
A top-down 2D game that lets you build your own ecosystem and let it simulate what would happen. You just select the types of animals you want and how many of them and how many plants you would like and then let the simulation begin. 

### What was used in the making of the game?
## Tile-based map
The map is basically a 2D matrix of tiles that is rendered randomly using a "homemade" version of perlin noise inspired from javidx9. Pressing the left, right arrow buttons or space will change the uniformity of the perlin noise algorithm and will allow you to generate a new outcome.  

This is an example of how the map looks like when you first run the game.
![image](https://github.com/user-attachments/assets/f528c476-1b2d-45b3-a57d-e79c94388425)

Pressing the left and right arrow buttons will change the bias of the noise.
![11-03-2024 (19-10-51)](https://github.com/user-attachments/assets/4b40eb3a-ed09-45cf-8e8c-7449b251a7fa)

Pressing the space button will change the number of octaves of the noise.
![11-03-2024 (19-12-54)](https://github.com/user-attachments/assets/36afe7dc-9088-441a-bc2e-5e3276cbc508)

## Basic controls
The game has basic camera controls such as moving the camera around using WASD and zooming in and out.
![11-03-2024 (19-36-27)](https://github.com/user-attachments/assets/53cac81d-8164-4f77-8de4-9fca7896a0c4)

## Spawning Animals
Currently there are two types of animals: Rabbits and Foxes;
To spawn them you just change the nRabbits and nFoxes variable in the Game.cpp file.

# RABBIT
![image](https://github.com/user-attachments/assets/da401cb0-a762-4ff1-bf3a-8d2786fef70d)

# FOX
![image](https://github.com/user-attachments/assets/73e0f00f-5b60-4ab3-91f0-ba4dec99fa4b)

## Vision and Movement
Each animal has its own way of moving around the map.
An animal will first analyse all the tiles that are visible to it and then make a choice.
The choice will be based on a simple algorithm that gives tiles a value based on what is inside them.
![image](https://github.com/user-attachments/assets/aba30976-4551-43a0-83a1-f936eb3446e1)
-- This is what this bunny sees (it has a vision_range = 4)

All the bunny sees is marked in the game as green tiles.
The algorithm for making a move will analyse all those tiles and pick one of the 8 tiles in the yellow highlighted area to move towards based on a danger level.
![image](https://github.com/user-attachments/assets/c78e3116-35f6-4dfe-81f2-9c5bc102f7ca)

Also, each Animal has it's own move_speed, meaning that a rabbit could outrun the fox's vision or the opposite.

## Cursor Selector
Each Animal can be clicked. Clicking it will show its vision range represented as low opacity green tiles.
![11-03-2024 (19-38-34)](https://github.com/user-attachments/assets/d9d41003-6bd5-4d04-843f-218f94459859)

## Plants
There is just a carrot, a plant that will affect only the rabbits. Once eaten by a rabbit, it's vision_range will increase by one.
https://github.com/user-attachments/assets/748e37a8-cf2d-406c-a3cc-48143043483e

# Plant Implementation
Using the Decorator Design Pattern, each plant can have multiple properties, similar to how swords can be enchanted in Minecraft.
Knowing this, the carrot can be either a simple plant or a special one:
```cpp
Plant* myPlant = new Carrot();

// Adding a decorator
myPlant = new HealDecorator(myPlant);
myPlant = new SpeedDecorator(myPlant);
myPlant = new VisionDecorator(myPlant);
```
# CARROT
![image](https://github.com/user-attachments/assets/4b0a2d88-e265-4fff-ac15-9037f24865ff)





## Resources
- [SFML](https://github.com/SFML/SFML/tree/2.6.1)
