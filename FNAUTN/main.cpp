#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    Vector2i screen(0, 0);
    screen.x = VideoMode::getDesktopMode().width;
    screen.y = VideoMode::getDesktopMode().height;



    if (!Shader::isAvailable())
    {

    }

    Shader shader;
    // load only the fragment shader
    if (!shader.loadFromFile("fragment_shader.frag", Shader::Fragment))
    {
        //return 0;
        system("pause");
    }
    shader.setUniform("texture", Shader::CurrentTexture);
    shader.setUniform("screen", Vector2f(screen.x, screen.y));




    //CircleShape shape(100.f);
    //shape.setFillColor(Color::Green);
    Texture texture;
    texture.setSmooth(true);
    if (!texture.loadFromFile("equirectangulartest.png", IntRect(0, 0, 3600, 900)))
    {
        // error...
    }

    Sprite sprite;
    sprite.setTexture(texture);

    Vector2i mPos(0, 0);

    //sprite.setOrigin(-1600/2, -3704/2);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);

        mPos.x = Mouse::getPosition(window).x;
        mPos.y = Mouse::getPosition(window).y;
        if (mPos.x > 1600 * 0.8 && sprite.getPosition().x > -(3600-1600)){
            sprite.move(-0.5, 0);
        }
        if (mPos.x < 1600 * 0.2 && sprite.getPosition().x < 0){
            sprite.move(0.5, 0);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)){///detecta cuando Escape está siendo presionado
            return 0;
        }

        window.draw(sprite, &shader);
        window.display();
    }

    return 0;
}
