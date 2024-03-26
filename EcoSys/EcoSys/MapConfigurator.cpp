#include "MapConfigurator.h"

void MapConfigurator::GenerateSeed() const {
    /*
        @return void 

        - functia returneaza genereaza un seed random pentru a fi ulterior prelucrat de PerlinNoise()
    */

    for (int i = 0; i < this->_width * this->_height; ++i)
        this->_noiseSeed[i] = (float)rand() / (float)RAND_MAX;
}

void MapConfigurator::PerlinNoise(uint maxOctaves, float bias) {
    /*
        @return void

        - functia specifica perlin noise
        - are 2 parametri: octave si bias

        - octavele determina nivelul de dispersie a hartii
        - bias-ul determina uniformitatea dispersiei
    */

    for (int i = 0; i < this->_width; ++i) {
        for (int j = 0; j < this->_height; ++j) {
            float noise = 0.0f;
            float scale = 1.0f;
            float totalScale = 0.0f;

            for (int octave = 0; octave < maxOctaves; ++octave) {
                int pitch = this->_width >> octave;

                if (pitch == 0) pitch = 1;

                Vector2i s1((i / pitch) * pitch, (j / pitch) * pitch);
                Vector2i s2((s1.x + pitch) % this->_width, (s1.y + pitch) % this->_height);

                Vector2f blend((float)(i - s1.x) / (float)pitch, (float)(j - s1.y) / (float)pitch);

                Vector2f sample(
                    (1 - blend.x) * this->_noiseSeed[s1.y * this->_width + s1.x] + blend.x * this->_noiseSeed[s1.y * this->_width + s2.x],
                    (1 - blend.x) * this->_noiseSeed[s2.y * this->_width + s1.x] + blend.x * this->_noiseSeed[s2.y * this->_width + s2.x]
                );

                noise += (blend.y * (sample.y - sample.x) + sample.x) * scale;
                totalScale += scale;

                scale /= bias;
            }

            this->_perlinNoise[j * this->_width + i] = noise / totalScale;
        }
    }
}

MapConfigurator::MapConfigurator() {
    this->_map = nullptr;
    this->_noiseSeed = nullptr;
    this->_perlinNoise = nullptr;

    this->_width = 0;
    this->_height = 0;
    this->_maxTextures = 1;
    this->_mode = MAP_CONFIG::RANDOM;
}

MapConfigurator::MapConfigurator(uint width, uint height, uint maxTextures, MAP_CONFIG mode) {
    this->_width = width;
    this->_height = height;
    this->_maxTextures = maxTextures;
    this->_mode = mode;

    this->_map = new int[width * height];
    this->_noiseSeed = new float[width * height];
    this->_perlinNoise = new float[width * height];

    switch (mode) {
    case MAP_CONFIG::RANDOM:
        this->GenerateRandom();
        break;
    case MAP_CONFIG::PERLIN:
        this->GeneratePerlin();
        break;
    }

    //this->Debug();
}

void MapConfigurator::GenerateRandom() {
    /*
        @return void

        - una din functiile de generare a hartii
        - foloseste doar numere random, fara uniformizare
    */

    for (int i = 0; i < this->_width; ++i)
        for (int j = 0; j < this->_height; ++j)
            this->_map[i + j * this->_width] = rand() % this->_maxTextures;
}

void MapConfigurator::GeneratePerlin(uint maxOctaves, float bias) {
    /*
        @return void

        - una din functiile de generare a hartii
        - foloseste perlin noise pentru a genera peisaje uniforme

        - genereaza un seed random initial intr-un vector
        - aplica perlin noise pe vectorul generat
        - randeaza tile-urile in functie de valorile generate
    */

    this->GenerateSeed();
    this->PerlinNoise(maxOctaves, bias);

    for (int i = 0; i < this->_width; ++i) {
        for (int j = 0; j < this->_height; ++j) {
            float value = this->_perlinNoise[i + j * this->_width];

            TILE_TYPE selectedTile = TILE_TYPE::GRASS;

            if (value < 0.2f) {
                selectedTile = TILE_TYPE::MOUNTAIN;
            }
            else if (value < 0.5f) {
                selectedTile = TILE_TYPE::GRASS;
            }
            else if (value < 0.7f) {
                selectedTile = TILE_TYPE::SAND;
            }
            else {
                selectedTile = TILE_TYPE::WATER;
            }

            this->_map[i + j * this->_width] = selectedTile;
        }
    }
}

void MapConfigurator::Update(uint octaves, float bias) {
    switch (this->_mode) {
    case MAP_CONFIG::RANDOM:
        this->GenerateRandom();
        break;
    case MAP_CONFIG::PERLIN:
        this->GeneratePerlin(octaves, bias);
        break;
    }
}

void MapConfigurator::Debug() const {
    /*
        @return void

        - functie de debug
    */
    
    for (int i = 0; i < this->_width; ++i) {
        for (int j = 0; j < this->_height; ++j)
            cout << this->_map[i + j * this->_width] << ' ';
        cout << '\n';
    }
}
