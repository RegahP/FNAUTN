#ifndef DRAWCALL_H_INCLUDED
#define DRAWCALL_H_INCLUDED

int Draw(RenderWindow& window, Player player, Office office, Map mapa, Profe globalProfes[], Room globalRooms[], Vector2i screen, Clock* clock){

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

    Texture cameraTex;
    Sprite cameraSpr;

    Sprite renderSpr;
    RenderTexture renderTexture;
    renderTexture.create(screen.x, screen.y);
    renderTexture.setSmooth(true);
    //INITS INITS INITS INITS INITS INITS INITS INITS INITS

    //SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
    officeTex = SetTexture("equirectangulartest");
    officeSpr.setTexture(officeTex);

    cameraTex = SetTexture("00000");
    cameraSpr.setTexture(cameraTex);

    renderSpr.setScale(1.0, -1.0);
    renderSpr.setPosition(0.0, screen.y);
    renderSpr.setTexture(renderTexture.getTexture());
    //SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS

    //Sprite camHoverButtonSprite = player.DrawCamButton();
    //camHoverButtonSprite.setPosition(screen.x/2 - camHoverButtonSprite.getTextureRect().width/2 , screen.y - camHoverButtonSprite.getTextureRect().height);


    while (window.isOpen())
    {
        window.clear();
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
            player.Configure(event, &officeTex, officeSpr, &office, &mapa, mPos);
            office.Configure(&officeTex);
            mapa.Configure(&cameraTex, globalProfes, globalRooms);


        }

        if (!player.getLookingState()){

            Sprite *officeSprP = &officeSpr;
            HorizontalScroll (officeSprP, mPos, screen);

            window.draw(renderSpr, &shader);
            renderTexture.draw(officeSpr);
        }
        else{
            window.draw(cameraSpr);
            window.draw(mapa.getSprite());
            window.draw(mapa.getToggleButton());
        }

        //window.draw(camHoverButtonSprite);

        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }
    office.setGeneratorUsage(player.getLookingState());
    float usage = office.getGeneratorUsage();
    office.updateGeneratorTemp(usage, clock);
    cout<<office.getLightState()<<endl;
    }
}

#endif // DRAWCALL_H_INCLUDED
