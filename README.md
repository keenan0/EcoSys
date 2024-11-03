
# ECOSYS

## Overview
**ECOSYS** is a top-down, 2D simulation game where players can construct and observe their own ecosystems. Players select various species of animals and plants, along with their respective populations, to create a customized ecosystem. Once the ecosystem is set, the simulation runs autonomously, allowing players to witness the interactions and natural developments within their environment.

## Development Details

### Tile-Based Map
The map in **ECOSYS** is built on a tile-based system, represented as a 2D matrix. This matrix is generated using a custom Perlin Noise algorithm, inspired by the work of [**javidx9**](https://www.youtube.com/watch?v=6-0UaeJBumA&t=1323s). The Perlin noise algorithm enables the map to be rendered with natural-looking terrain. 
> Pressing the Left/Right Arrow Keys or Spacebar, the player will adjust the uniformity of the noise, leading to different map layouts.

#### Initial Map Layout 
>This is the default map appearance when the game first runs.
><img src="https://github.com/user-attachments/assets/f528c476-1b2d-45b3-a57d-e79c94388425" alt="Description" width="300">

#### Modifying Noise Bias 
>Pressing the left and right arrow keys will adjust the bias of the noise.
><img src="https://github.com/user-attachments/assets/4b40eb3a-ed09-45cf-8e8c-7449b251a7fa" alt="Description" width="300">


#### Adjusting Noise Octaves 
>Pressing the spacebar changes the number of octaves used in the noise, creating variations in terrain.
<img src="https://github.com/user-attachments/assets/36afe7dc-9088-441a-bc2e-5e3276cbc508" alt="Description" width="300">

## Basic controls
The game has basic camera controls such as moving the camera around using WASD and zooming in and out.
<img src="https://github.com/user-attachments/assets/53cac81d-8164-4f77-8de4-9fca7896a0c4" alt="Description" width="300">

## Spawning Animals
Currently there are two types of animals: **Rabbits** and **Foxes**;
To spawn them you just change the nRabbits and nFoxes variable in the Game.cpp file.

> #### RABBIT
><img src="https://github.com/user-attachments/assets/da401cb0-a762-4ff1-bf3a-8d2786fef70d" alt="Description" width="300">

> #### FOX
><img src="https://github.com/user-attachments/assets/73e0f00f-5b60-4ab3-91f0-ba4dec99fa4b" alt="Description" width="300">

## Vision and Movement
Each animal has its own way of moving around the map.
An animal will first analyse all the tiles that are visible to it and then make a choice.
The choice will be based on a simple algorithm that gives tiles a value based on what is inside them.
><img src="https://github.com/user-attachments/assets/aba30976-4551-43a0-83a1-f936eb3446e1" alt="Description" width="300">
>
>*-- This is what a bunny with vision_range = 4 sees* 

Everything the bunny sees is marked in the game as **green tiles**.

The algorithm for making a move will analyse all those tiles and pick one of the 8 tiles in the yellow highlighted area to move towards based on a danger level.
<img src="https://github.com/user-attachments/assets/c78e3116-35f6-4dfe-81f2-9c5bc102f7ca" alt="Description" width="300">

Also, each Animal has it's own move_speed, meaning that a rabbit could outrun the fox's vision or the opposite.

## Cursor Selector
Each Animal can be clicked. Clicking it will show its vision range represented as low opacity green tiles.
<img src="https://github.com/user-attachments/assets/d9d41003-6bd5-4d04-843f-218f94459859" alt="Description" width="300">

## Plants
There is just a carrot, a plant that will affect only the rabbits. Once eaten by a rabbit, it's vision_range will increase by one.
<img src="https://github.com/user-attachments/assets/7baffdd2-6a15-4525-8f21-72ca1e0d0620" alt="Description" width="300">

# Plant Implementation
Using the Decorator Design Pattern, each plant can have multiple properties, similar to how swords can be enchanted in Minecraft.
Knowing this, the carrot can be either a simple or a special plant:
```cpp
Plant* myPlant = new Carrot();

// Adding a decorator
myPlant = new HealDecorator(myPlant);
myPlant = new SpeedDecorator(myPlant);
myPlant = new VisionDecorator(myPlant);
```
# CARROT
<img src="https://github.com/user-attachments/assets/4b0a2d88-e265-4fff-ac15-9037f24865ff" alt="Description" width="300">






## Resources
- [SFML](https://github.com/SFML/SFML/tree/2.6.1)
