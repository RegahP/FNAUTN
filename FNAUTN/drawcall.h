#ifndef DRAWCALL_H_INCLUDED
#define DRAWCALL_H_INCLUDED

int DrawOffice(RenderWindow& window, Player player){

    Vector2i screen(0, 0);
    screen.x = VideoMode::getDesktopMode().width;
    screen.y = VideoMode::getDesktopMode().height;

    Texture texture;
    texture = SetTexture("equirectangulartest.png");

    if (!Shader::isAvailable())
    {
        cout<<"shaders not available"<<endl;
    }
    Shader shader;
    Sprite sprite;
    Sprite renderSprite;
    RenderTexture renderTexture;

    if (!shader.loadFromFile("perspective.frag", Shader::Fragment))
    {
        cout<<"failed to load "<<"perspective.frag"<<endl;
    }

    renderTexture.create(screen.x, screen.y);
    renderTexture.setSmooth(true);
    shader.setUniform("texture", Shader::CurrentTexture);

    sprite.setTexture(texture);
    renderSprite.setScale(1.0, -1.0);
    renderSprite.setPosition(0.0, 900.0);
    renderSprite.setTexture(renderTexture.getTexture());

    Vector2i mPos(0, 0);

    //Sprite camHoverButtonSprite = player.DrawCamButton();
    //camHoverButtonSprite.setPosition(screen.x/2 - camHoverButtonSprite.getTextureRect().width/2 , screen.y - camHoverButtonSprite.getTextureRect().height);


    while (window.isOpen())
    {
        mPos.x = Mouse::getPosition(window).x;
        mPos.y = Mouse::getPosition(window).y;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            //player.CheckCams(mPos, event);
            //player.CheckLight(event);
            //texture = player.tempTexture;
        }

        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }

        if (!player.lookingAtCams){

            if (mPos.x > 1600 * 0.8 && sprite.getPosition().x > -(3600-1600)){
                sprite.move(-0.8, 0);
            }
            if (mPos.x < 1600 * 0.2 && sprite.getPosition().x < 0){
                sprite.move(0.8, 0);
            }

            window.draw(renderSprite, &shader);
            renderTexture.draw(sprite);
        }
        //window.draw(camHoverButtonSprite);

        window.display();
    }
}

#endif // DRAWCALL_H_INCLUDED
