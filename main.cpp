#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    bool textureLoaded = false;
    sf::Texture idleTexture;
    sf::Texture walkTexture;
    sf::Texture slashTexture;
    sf::Texture blockTexture;
    sf::Texture deathTexture;
    sf::Sprite sprite;
    sf::IntRect spriteTextureReact(0,0,48,48);
    sf::Clock clock;

    enum CharacterStates {idle, walk, slash, block, death};
    CharacterStates state = idle;
    if(!idleTexture.loadFromFile("assets/AssetPack-V1/Sprite Sheets/Character Idle 48x48.png"))
    {
        printf("Error loading idle texture!");
    } else if(!walkTexture.loadFromFile("assets/AssetPack-V1/Sprite Sheets/run cycle 48x48.png")){
        printf("Error loading walk texture!");
    } else if(!slashTexture.loadFromFile("assets/knight/slash.png")){
        printf("Error loading slash texture!");
    } else if(!blockTexture.loadFromFile("assets/knight/block.png")){
        printf("Error loading block texture!");
    } else if(!deathTexture.loadFromFile("assets/knight/death.png")){
        printf("Error loading death texture!");
    } else {
        textureLoaded = true;
        // texture.setSmooth(true);
        sprite.setTexture(idleTexture);
        sprite.setTextureRect(spriteTextureReact);
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(24.f, 24.f);
        sprite.setPosition(sf::Vector2f(200.f, 200.f));
    }
    while (window.isOpen())
    {
        sf::Event event;
        bool moveLeft = false;
        bool moveRight = false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code)
                {
                case sf::Keyboard::D:
                    moveLeft = true;
                    break;
                case sf::Keyboard::A:
                    moveRight = true;
                    break;
                default:
                    break;
                }
            }
            if (event.type == sf::Event::KeyReleased){
                state = idle;
                moveLeft = false;
                moveRight = false;
                sprite.setTexture(idleTexture);
            }
        }

        if(moveLeft){
            state = walk;
            sprite.setTexture(walkTexture);
            sprite.setScale(2.f, 2.f);
            sprite.move(10.f, 0.f);
        }
        if(moveRight){
            state = walk;
            sprite.setTexture(walkTexture);
            sprite.setScale(-2.f, 2.f);
            sprite.move(-10.f, 0.f);
        }

        if(clock.getElapsedTime().asSeconds() > 0.1f){
            if(state == idle && spriteTextureReact.left == 480-48){
                spriteTextureReact.left = 0;
            } else if(state == walk && spriteTextureReact.left == 384-48){
                spriteTextureReact.left = 0;
            }
            else{
                spriteTextureReact.left += 48;
            }

            sprite.setTextureRect(spriteTextureReact);
            clock.restart();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}