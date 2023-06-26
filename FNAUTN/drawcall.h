#ifndef DRAWCALL_H_INCLUDED
#define DRAWCALL_H_INCLUDED

int Draw(RenderWindow& window, Player player, Office office, Map mapa, Profe globalProfes[], Room globalRooms[], Vector2i screen){

    ///SHADER SHADER SHADER SHADER SHADER SHADER SHADER SHADER
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

    ///INITS INITS INITS INITS INITS INITS INITS INITS INITS
    Vector2i mPos(0, 0);

    Texture windowTex;
    Sprite windowSpr;
    Texture lDoorTex;
    Sprite lDoorSpr;
    Texture rDoorTex;
    Sprite rDoorSpr;

    Texture cameraTex;
    Sprite cameraSpr;

    Sprite renderSpr;
    RenderTexture renderTexture;
    renderTexture.create(screen.x, screen.y);
    renderTexture.setSmooth(true);

    ///SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
    lDoorTex = SetTexture("office/L00");
    lDoorSpr.setTexture(lDoorTex);
    windowTex = SetTexture("office/FFFFF");
    windowSpr.setTexture(windowTex);
    rDoorTex = SetTexture("office/R00");
    rDoorSpr.setTexture(rDoorTex);

    cameraTex = SetTexture("cameras/00000");
    cameraSpr.setTexture(cameraTex);

    windowSpr.setPosition(1130, 0);
    rDoorSpr.setPosition(2470, 0);

    renderSpr.setScale(1.0, -1.0);
    renderSpr.setPosition(0.0, screen.y);
    renderSpr.setTexture(renderTexture.getTexture());

    ///INIT CONFIGURES INIT CONFIGURES INIT CONFIGURES
    office.Configure(&lDoorTex, &windowTex, &rDoorTex);
    mapa.Configure(&cameraTex, globalProfes, globalRooms);
    bool updateCameras = false;

    while (window.isOpen())
    {
        window.clear();
        mPos.x = Mouse::getPosition(window).x;
        mPos.y = Mouse::getPosition(window).y;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
            ///UPDATE CONFIGURES UPDATE CONFIGURES UPDATE CONFIGURES
            player.Configure(event, lDoorSpr, &office, &mapa, mPos);
        }
        ///EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME

        globalProfes[0].MovementOpportunity(&updateCameras);
        //globalProfes[1].MovementOpportunity(&updateCameras);
        //globalProfes[2].MovementOpportunity(&updateCameras);
        //globalProfes[3].MovementOpportunity(&updateCameras);

        if (office.getGeneratorClock()->getElapsedTime().asSeconds() >= office.getGeneratorTimer()){
            office.setGeneratorUsage(player.getLookingState());
            float usage = office.getGeneratorUsage();
            office.updateGeneratorTemp(usage);
        }
        if (!player.getLookingState()){

            HorizontalScroll (&lDoorSpr, &windowSpr, &rDoorSpr, mPos, screen);

            renderTexture.draw(lDoorSpr);
            renderTexture.draw(windowSpr);
            renderTexture.draw(rDoorSpr);
            window.draw(renderSpr, &shader);

        }
        else{
            if (updateCameras){
                if (globalProfes[0].getPos().x == player.getCurrentCam() || globalProfes[0].getLastRoom() == player.getCurrentCam()){
                    mapa.setCameraSprite(player.getCurrentCam());
                    updateCameras = false;
                }
                /*if (globalProfes[1].getPos().x == player.getCurrentCam() || globalProfes[1].getLastRoom() == player.getCurrentCam()){
                    mapa.setCameraSprite(player.getCurrentCam());
                    updateCameras = false;
                }
                if (globalProfes[2].getPos().x == player.getCurrentCam() || globalProfes[2].getLastRoom() == player.getCurrentCam()){
                    mapa.setCameraSprite(player.getCurrentCam());
                    updateCameras = false;
                }
                if (globalProfes[3].getPos().x == player.getCurrentCam() || globalProfes[3].getLastRoom() == player.getCurrentCam()){
                    mapa.setCameraSprite(player.getCurrentCam());
                    updateCameras = false;
                }*/
            }

            window.draw(cameraSpr);
            window.draw(mapa.getSprite());
            window.draw(mapa.getToggleButton());

        }
        window.draw(office.getGeneratorTempUI());
        window.draw(office.getGeneratorUsageUI());
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }
    }
}

#endif // DRAWCALL_H_INCLUDED
