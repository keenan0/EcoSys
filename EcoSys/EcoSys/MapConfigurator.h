#pragma once
#include "includes.h"

class MapConfigurator {
private:
    int* _map;
    float* _noiseSeed;
    float* _perlinNoise;

    MAP_CONFIG _mode;

    uint _width;
    uint _height;

    uint _maxTextures;

    void GenerateSeed() const;
    void PerlinNoise(uint maxOctaves, float bias);
public:
    MapConfigurator();
    ~MapConfigurator() = default;

    MapConfigurator(uint width, uint height, uint maxTextures = 1, MAP_CONFIG mode = MAP_CONFIG::RANDOM);

    void GenerateRandom();
    void GeneratePerlin(uint maxOctaves = 4, float bias = 2.0f);

    void Update(uint octaves, float bias);
    void Debug() const;

    const int* GetMap() const { return this->_map; }
    void SetWidth(const uint width) { this->_width = width; }
    void SetHeight(const uint height) { this->_height = height; }
};


