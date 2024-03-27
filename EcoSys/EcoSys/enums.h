#pragma once

const enum TILE_TYPE {
    GRASS, WATER, SAND, MOUNTAIN, GRASS3, UNDEFINED, TILE_TYPE_SIZE
};
//
//const enum TILE_TYPE {
//    WATER, GRASS1, GRASS2, GRASS3, GRASS4,
//    MUD1, MUD2, MUD3,
//    MOUNTAIN1, MOUNTAIN2, MOUNTAIN3,
//    SAND1, SAND2, SAND3,
//    N_TILE_TYPES
//};

//TILE_TYPE selectedTile = N_TILE_TYPES;
//
//if (value < 0.3f) {
//    selectedTile = TILE_TYPE::WATER;
//}
//else if (value < 0.5f) {
//    selectedTile = (enum TILE_TYPE)(rand() % 3 + 11);
//}
//else if (value < 0.8f) {
//    //Texturile de la iarba random
//    selectedTile = (enum TILE_TYPE)(rand() % 4 + 1);
//}
//else if (value < 0.9f) {
//    //Texturile de la noroi
//    selectedTile = (enum TILE_TYPE)(rand() % 3 + 5);
//}
//else {
//    //Texturile la munte
//    selectedTile = (enum TILE_TYPE)(rand() % 3 + 8);
//}

const enum MAP_CONFIG {
    RANDOM, PERLIN
};