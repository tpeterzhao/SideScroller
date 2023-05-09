#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 960), "SFML works!");
    bool textureLoaded = false;
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture rollTexture;
    sf::Sprite sprite;
    sf::IntRect idleTextureReact(0,0,48,48);
    sf::IntRect runTextureReact(0,0,48,48);
    sf::IntRect rollTextureReact(0,0,48,48);
    sf::Clock clock;
    float rollTimer = 0.6;

    enum CharacterStates {idle, run, roll};
    enum CharacterDirection {left, right};
    CharacterStates state = idle;
    CharacterDirection direction = right;
    float characterSpeed = 200;
    if(!idleTexture.loadFromFile("assets/AssetPack-V1/Sprite Sheets/Character Idle 48x48.png"))
    {
        printf("Error loading idle texture!");
    } else if(!runTexture.loadFromFile("assets/AssetPack-V1/Sprite Sheets/run cycle 48x48.png")){
        printf("Error loading run texture!");
    } else if(!rollTexture.loadFromFile("assets/AssetPack-V1/Sprite Sheets/Player Roll 48x48.png")){
        printf("Error loading roll right texture!");
    } else {
        textureLoaded = true;
        // texture.setSmooth(true);
        sprite.setTexture(idleTexture);
        sprite.setTextureRect(idleTextureReact);
        sprite.setScale(2.f, 2.f);
        sprite.setOrigin(24.f, 24.f);
        sprite.setPosition(sf::Vector2f(200.f, 400.f));
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (state != roll)){
            state = roll;
            sprite.setTexture(rollTexture);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (state != roll)){
            state = run;
            direction = right;
            sprite.setTexture(runTexture);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (state != roll)){
            state = run;
            direction = left;
            sprite.setTexture(runTexture);
        }else if(state != roll){
            state = idle;
            sprite.setTexture(idleTexture);
        }

        if(clock.getElapsedTime().asSeconds() > 0.1f){
            if(state == idle){
                if(idleTextureReact.left == 480-48){
                    idleTextureReact.left = 0;
                }
                else{
                    idleTextureReact.left += 48;
                }
                sprite.setTextureRect(idleTextureReact);

            }
            if(state == run){
                if(runTextureReact.left == 384-48){
                    runTextureReact.left = 0;
                } else{
                    runTextureReact.left += 48;
                }
                sprite.setTextureRect(runTextureReact);

                float velocity = characterSpeed * clock.getElapsedTime().asSeconds();
                if(direction == left){
                    sprite.move(-velocity, 0.f);
                } 
                if(direction == right){
                    sprite.move(velocity, 0.f);
                }
            }
            if(state == roll){
                if(rollTextureReact.left == 336-48){
                    rollTextureReact.left = 0;
                } else{
                    rollTextureReact.left += 48;
                }
                sprite.setTextureRect(rollTextureReact);
                rollTimer -= clock.getElapsedTime().asSeconds();
                float velocity = 2.5* characterSpeed * clock.getElapsedTime().asSeconds();
                if(direction==right){
                    sprite.move(velocity, 0.f);
                } 
                if(direction==left){
                    sprite.move(-velocity, 0.f);
                }
                if(rollTimer <= 0){
                    state = idle;
                    rollTimer = 0.6;
                }
            }

            clock.restart();
        }
        window.clear();
        if(direction==left){
            sprite.setScale(-2,2);
        } else {
            sprite.setScale(2, 2);
        }
        window.draw(sprite);
        window.display();
    }

    return 0;
}