#ifndef DRAWCALL_H_INCLUDED
#define DRAWCALL_H_INCLUDED

Render officeRender;

int Draw(RenderWindow& window, Player player, Vector2i screen){

    //SHADER SHADER SHADER SHADER SHADER SHADER SHADER SHADER
    if (!Shader::isAvailable())
    {
        cout<<"shaders not available"<<endl;
    }
    Shader shader;

    if (!shader.loadFromFile("perspective.frag", Shader::Fragment))
    {
        cout<<"failed to load "<<"perspective.frag"<<endl;
    }
    shader.setUniform("texture", Shader::CurrentTexture);
    //SHADER SHADER SHADER SHADER SHADER SHADER SHADER SHADER

    //INITS INITS INITS INITS INITS INITS INITS INITS INITS
    Vector2i mPos(0, 0);
    Texture officeTex;
    Sprite officeSpr;
    Sprite renderSprite;
    RenderTexture renderTexture;
    renderTexture.create(screen.x, screen.y);
    renderTexture.setSmooth(true);
    //INITS INITS INITS INITS INITS INITS INITS INITS INITS

    //SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
    officeTex = SetTexture("equirectangulartest.png");
    officeSpr.setTexture(officeTex);
    renderSprite.setScale(1.0, -1.0);
    renderSprite.setPosition(0.0, screen.y);
    renderSprite.setTexture(renderTexture.getTexture());
    //SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS

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
            player.Configure(event, &officeTex);

        }

        officeTex.update(officeRender.getImage());


        Sprite *officeSprP = &officeSpr;
        HorizontalScroll (officeSprP, mPos, screen);

        window.clear();
        window.draw(renderSprite, &shader);
        renderTexture.draw(officeSpr);

        //window.draw(camHoverButtonSprite);

        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }
    }
}

#endif // DRAWCALL_H_INCLUDED
