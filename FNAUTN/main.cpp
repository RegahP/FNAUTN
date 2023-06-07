#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void perspectiveImage(int ID, string textureName, Sprite sprite, Sprite renderSprite, Shader& shader, RenderTexture& renderTexture, Vector2i screen, RenderWindow& window);

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    Vector2i screen(0, 0);
    screen.x = VideoMode::getDesktopMode().width;
    screen.y = VideoMode::getDesktopMode().height;

    Sprite sprite;
    Sprite renderSprite;
    Shader shader;
    RenderTexture renderTexture;


    perspectiveImage(0, "equirectangulartest.png", sprite, renderSprite, shader, renderTexture, screen, window);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }

        perspectiveImage(1, "equirectangulartest.png", sprite, renderSprite, shader, renderTexture, screen, window);

        window.display();
    }

    return 0;
}

void perspectiveImage(int ID, string textureName, Sprite sprite, Sprite renderSprite, string shaderName, Shader& shader, RenderTexture& renderTexture, Vector2f screen, RenderWindow& window){

    Vector2i mPos(0, 0);
    switch(ID){
    case 0:{
    Texture texture;
    if (!texture.loadFromFile(textureName))
    {

    }
    if (!Shader::isAvailable())
    {

    }
    if (!shader.loadFromFile("perspective.frag", Shader::Fragment))
    {

    }

    sprite.setTexture(texture);
    renderTexture.create(screen.x, screen.y);
    renderSprite.setTexture(renderTexture.getTexture());
    renderSprite.setScale(1.0, -1.0);
    renderSprite.setPosition(0.0, 900.0);

    shader.setUniform("texture", Shader::CurrentTexture);
    }
        break;
    case 1:
        mPos.x = Mouse::getPosition(window).x;
        mPos.y = Mouse::getPosition(window).y;
        if (mPos.x > 1600 * 0.8 && sprite.getPosition().x > -(3600-1600)){
            sprite.move(-0.8, 0);
        }
        if (mPos.x < 1600 * 0.2 && sprite.getPosition().x < 0){
            sprite.move(0.8, 0);
        }

        window.draw(renderSprite, &shader);
        renderTexture.draw(sprite);
        break;
    }


}
