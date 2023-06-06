#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    Vector2i screen(0, 0);
    screen.x = VideoMode::getDesktopMode().width;
    screen.y = VideoMode::getDesktopMode().height;
    //CircleShape shape(100.f);
    //shape.setFillColor(Color::Green);
    Texture texture;
    texture.setSmooth(true);
    if (!texture.loadFromFile("equirectangulartest.png", IntRect(0, 0, 2083, 900)))
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
        if (mPos.x > 1600 * 0.8 && sprite.getPosition().x > -(2083-1600)){
            sprite.move(-1, 0);
        }
        if (mPos.x < 1600 * 0.2 && sprite.getPosition().x < 0){
            sprite.move(1, 0);
        }

        window.draw(sprite);
        window.display();
    }

    return 0;
}
