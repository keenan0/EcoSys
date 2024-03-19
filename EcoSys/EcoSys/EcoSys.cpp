#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using namespace sf;
using namespace std;

const enum TILE_TYPE {
    GRASS, WATER, SAND, MOUNTAIN, GRASS3
};

const enum MAP_CONFIG {
    RANDOM, PERLIN
};

const Vector2u TILE_SIZE = Vector2u(8, 8);
const float SCALING_FACTOR = 1.0f;

class Entity {
private:
    Vector2f _position;

    Texture _texture;
    Sprite _sprite;
public:
    Entity() = default;
    
    Entity(Vector2f position) : _position(position) {}

    Entity(const Entity &toCopy) {
        this->_position = toCopy._position;
        this->_texture = toCopy._texture;
        this->_sprite = toCopy._sprite;
    }

    bool LoadTexture(string textureFileName) {
        if (!this->_texture.loadFromFile("img/" + textureFileName)) {
            cout << "Eroare: Nu s-a putut incarca fisierul: " << textureFileName << '\n';

            return false;
        }

        this->_sprite.setTexture(this->_texture);
        this->_sprite.setPosition(this->_position);
        return true;
    }

    void DrawSprite(RenderWindow &currentWindow) {
        this->_sprite.setScale(Vector2f(SCALING_FACTOR, SCALING_FACTOR));
        
        currentWindow.draw(this->_sprite);
    }

    Vector2f getPosition() const { return this->_position; }

    ~Entity() {
        cout << "Avertisment: Entitate distrusa!\n";
    }

    Entity& operator=(const Entity& e) {
        this->_position = e._position;
        this->_sprite = e._sprite;
        this->_texture = e._texture;

        cout << "Avertizare: Entiate atribuita cu succes\n";

        return *this;
    }
};

class Animal : public Entity {
private:
    int _health;
public:
    Animal(Vector2f position, int health) : Entity(position), _health(health) {}
};

class Plant : public Entity {
private:
    float _lifeTime;
public:
    Plant() { this->_lifeTime = 0.0f; }
    Plant(float lifeTime) : _lifeTime(lifeTime) {}
    ~Plant() { cout << "Avertizare: Planta distrusa\n"; }

    void Update() {

    }
};

class TileMap : public Drawable, public Transformable {
private:
    Texture _texture;
    VertexArray _tileMapVertices;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = &this->_texture;

        target.draw(this->_tileMapVertices, states);
    }
public:
    bool LoadTileMap(const string tileMapTextureName, const int* tileConfig, unsigned int tileMapWidth, unsigned int tileMapHeight, Vector2u tileSize, float scalingFactor = 1.0f) {
        if (!_texture.loadFromFile("img/" + tileMapTextureName)) {
            cout << "Eroare: Nu s-a putut incarca tilemap-ul!\n";

            return false;
        }

        this->_tileMapVertices.setPrimitiveType(PrimitiveType::Quads);
        this->_tileMapVertices.resize(tileMapWidth * tileMapHeight * 4);

        for (int i = 0; i < tileMapWidth; ++i) {
            for (int j = 0; j < tileMapHeight; ++j) {
                int tileNumber = tileConfig[i + j * tileMapWidth];
                int nTilesInTextureRow = this->_texture.getSize().x / tileSize.x;

                int textureX = tileNumber % nTilesInTextureRow;
                int textureY = tileNumber / nTilesInTextureRow;

                Vertex* quad = &this->_tileMapVertices[(i + j * tileMapWidth) * 4];

                quad[0].position = Vector2f(i * tileSize.x, j * tileSize.y) * scalingFactor;
                quad[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y) * scalingFactor;
                quad[2].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;
                quad[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y) * scalingFactor;

                quad[0].texCoords = Vector2f(textureX * tileSize.x, textureY * tileSize.y);
                quad[1].texCoords = Vector2f((textureX + 1) * tileSize.x, textureY * tileSize.y);
                quad[2].texCoords = Vector2f((textureX + 1) * tileSize.x, (textureY + 1) * tileSize.y);
                quad[3].texCoords = Vector2f(textureX * tileSize.x, (textureY + 1) * tileSize.y);
            }
        }

        return true;
    }
};

class MapConfigurator {
private:
    int* _map;
    float* _noiseSeed;
    float* _perlinNoise;

    void GenerateSeed(unsigned int width, unsigned int height) const {
        for (int i = 0; i < width * height; ++i)
            this->_noiseSeed[i] = (float)rand() / (float)RAND_MAX;
    }

    void PerlinNoise(unsigned int width, unsigned int height, int maxOctaves, float bias) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                float noise = 0.0f;
                float scale = 1.0f;
                float totalScale = 0.0f;

                for (int octave = 0; octave < maxOctaves; ++octave) {
                    int pitch = width >> octave;

                    if (pitch == 0) pitch = 1;

                    Vector2i s1((i / pitch) * pitch, (j / pitch) * pitch);
                    Vector2i s2((s1.x + pitch) % width, (s1.y + pitch) % width);

                    Vector2f blend((float)(i - s1.x) / (float)pitch, (float)(j - s1.y) / (float)pitch);

                    Vector2f sample(
                        (1 - blend.x) * this->_noiseSeed[s1.y * width + s1.x] + blend.x * this->_noiseSeed[s1.y * width + s2.x],
                        (1 - blend.x) * this->_noiseSeed[s2.y * width + s1.x] + blend.x * this->_noiseSeed[s2.y * width + s2.x]
                    );

                    noise += (blend.y * (sample.y - sample.x) + sample.x) * scale;
                    totalScale += scale;

                    scale /= bias;
                }

                this->_perlinNoise[j * width + i] = noise / totalScale;
            }
        }
    }
public:
    MapConfigurator() = default;

    MapConfigurator(unsigned int width, unsigned int height, MAP_CONFIG mode = MAP_CONFIG::RANDOM) {
        this->_map = new int[width * height];
        this->_noiseSeed = new float[width * height];
        this->_perlinNoise = new float[width * height];

        switch (mode) {
        case MAP_CONFIG::RANDOM:
            this->GenerateRandom(width, height);
            break;
        case MAP_CONFIG::PERLIN:
            this->GeneratePerlin(width, height, 4);
            break;
        }
    }

    void GenerateRandom(unsigned int width, unsigned int height) {
        for (int i = 0; i < width; ++i)
            for (int j = 0; j < height; ++j)
                this->_map[i + j * width] = rand() % 5;
    }

    void GeneratePerlin(unsigned int width, unsigned int height, unsigned int maxOctaves = 4, float bias = 2.0f) {
        this->GenerateSeed(width, height);
        this->PerlinNoise(width, height, maxOctaves, bias);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                float value = this->_perlinNoise[i + j * width];

                if (value < 0.3f) {
                    this->_map[i + j * width] = TILE_TYPE::MOUNTAIN;
                }
                else if (value < 0.5f) {
                    this->_map[i + j * width] = TILE_TYPE::GRASS;
                }
                else if(value < 0.8f) {
                    this->_map[i + j * width] = TILE_TYPE::SAND;
                }
                else {
                    this->_map[i + j * width] = TILE_TYPE::WATER;
                }
            }
        }
    }

    const int* getMap() const {
        return this->_map;
    }

    ~MapConfigurator() = default;
};

RenderWindow window(VideoMode(1080, 720), "Ecosys");

vector<Entity> plants;

TileMap worldTileMap;

Event event;

void LoadTextures() {
    for (int i = 0; i < plants.size(); ++i)
        plants[i].LoadTexture("carrot.png");
}

void DrawSprites() {
    for (int i = 0; i < plants.size(); ++i)
        plants[i].DrawSprite(window);
}

void SetIcon(RenderWindow &window) {
    Image icon;
    icon.loadFromFile("img/carrot.png");
     
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int main() {
    srand(time(NULL));
    window.setVerticalSyncEnabled(true);

    SetIcon(window);

    LoadTextures();

    Vector2u windowSize = window.getSize();

    unsigned int mapWidth = windowSize.x / TILE_SIZE.x + 1;
    unsigned int mapHeight = windowSize.y / TILE_SIZE.y + 1;
    
    unsigned int octaves = 4;
    float bias = 3.0f;

    MapConfigurator config(mapWidth, mapHeight, MAP_CONFIG::PERLIN);

    worldTileMap.LoadTileMap("tileSet.png", config.getMap(), mapWidth, mapHeight, TILE_SIZE, SCALING_FACTOR);

    while (window.isOpen()) { 
        while (window.pollEvent(event)) {
            switch (event.type) {
            case Event::Closed:
                window.close();
            case Event::MouseButtonPressed:
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2i mouse(event.mouseButton.x, event.mouseButton.y);
                    Vector2i mapped(floor(mouse.x / TILE_SIZE.x / SCALING_FACTOR), floor(mouse.y / TILE_SIZE.y / SCALING_FACTOR));

                    plants.emplace_back(Entity(Vector2f(mapped.x * TILE_SIZE.x * SCALING_FACTOR, mapped.y * TILE_SIZE.y * SCALING_FACTOR)));

                    LoadTextures();
                }
            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::R)) {
                    //config.GenerateRandom(mapWidth, mapHeight);
                    config.GeneratePerlin(mapWidth, mapHeight, octaves, bias);
                    worldTileMap.LoadTileMap("tileSet.png", config.getMap(), mapWidth, mapHeight, TILE_SIZE, SCALING_FACTOR);
                    plants.clear();
                }

                if (Keyboard::isKeyPressed(Keyboard::Space)) {
                    octaves = (octaves + 1) % 8;
                    cout << "octaves: " << octaves << '\n';
                }

                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    bias -= 0.1f;
                    cout << "bias: " << bias << '\n';
                }

                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    bias += 0.1f;
                    cout << "bias: " << bias << '\n';
                }
            }
        }
        
        window.clear(Color::Black);
        window.draw(worldTileMap);

        DrawSprites();

        window.display();
    }
}

/*
bool operator==(const Echipa& e) const {
        return nume == e.nume && codEchipa == e.codEchipa;
    }

    Echipa &operator=(const Echipa& ec) {
        this->codEchipa = ec.codEchipa;
        this->nume = ec.nume;

        return *this;
    }
    //const Echipa &e ca sa nu se mai faca o copie in cadrul functiei

    //Intuitiv
    Echipa &operator<<(const Echipa &e) {
        cout << e.nume << ' ' << e.codEchipa << '\n';
    }

    friend ostream& operator<<(ostream &out, const Echipa &e) {
        cout << e.nume << ' ' << e.codEchipa;

        return out;
    }

    friend istream& operator>>(istream& in, Echipa& e) {
        in >> e.nume >> e.codEchipa;
        return in;
    }*/