#ifndef DRAWCALL_H_INCLUDED
#define DRAWCALL_H_INCLUDED

bool Draw(RenderWindow& window, Player player, Office office, Map mapa, Profe globalProfes[], Room globalRooms[], Vector2i screen, Clock nightClock, float gamma, int volume){

    ///SHADER SHADER SHADER SHADER SHADER SHADER SHADER SHADER
    if (!Shader::isAvailable())
    {
        cout<<"shaders not available"<<endl;
    }
    Shader perspectiveShader;
    Shader gammaShader;

    if (!perspectiveShader.loadFromFile("perspective.frag", Shader::Fragment))
    {
        cout<<"failed to load "<<"perspective.frag"<<endl;
    }
    perspectiveShader.setUniform("texture", Shader::CurrentTexture);

    if (!gammaShader.loadFromFile("gamma.frag", Shader::Fragment))
    {
        cout<<"failed to load "<<"gamma.frag"<<endl;
    }
    gammaShader.setUniform("gamma", gamma);

    ///INITS INITS INITS INITS INITS INITS INITS INITS INITS
    Vector2i mPos(0, 0);

    srand((unsigned)time(NULL));

    Texture windowTex;
    Sprite windowSpr;
    Texture lDoorTex;
    Sprite lDoorSpr;
    Texture rDoorTex;
    Sprite rDoorSpr;
    Texture miraPlushieTex;
    Sprite miraPlushieSpr;
    Texture monkeTex;
    Sprite monkeSpr;
    Texture dndDiceTex;
    Sprite dndDiceSpr;

    Texture cameraTex;
    Sprite cameraSpr;

    Texture jumpscareTex;
    Sprite jumpscareSpr;

    Animator jumpscares(&jumpscareSpr, 24);

    RectangleShape deathCard;///replace with texture vector of deathcards to place at the end per profe

    Texture mrKlosterTex;
    Sprite mrKlosterSpr;

    Sprite renderSpr;
    RenderTexture renderTexture;
    renderTexture.create(screen.x, screen.y);
    renderTexture.setSmooth(true);

    Sprite gammaSpr;
    RenderTexture gammaTexture;
    gammaTexture.create(screen.x, screen.y);
    gammaTexture.setSmooth(true);

    Text nightClockText;
    Font font;
    int hourCounter;
    float hourTimer;

    Clock drawClock;
    nightClock.restart();
    bool calculateTimers;
    bool playAudio;
    int waitToAudio;
    int waitToKloster;

    RectangleShape fadeInOut;
    float fadeValue;
    float fadeSpeed;
    float fadeVolume;
    bool fadeIn;

    float klosterFadeValue;
    float klosterFadeSpeed;
    bool klosterFadeIn;
    bool mrKlosterIsHere;
    bool mrKlosterJumpscare;

    SoundBuffer klosterBuffer;
    Sound klosterSound;
    Music ambience;

    bool updateCameras;
    bool updateWindow;

    Texture camTransitionTex;
    Sprite camTransitionSpr;
    Texture camTransitionFrames[12];

    Animation camTransition;
    Clock camTransitionClock;

    ///SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS

    lDoorTex = SetTexture("office/L00");
    lDoorSpr.setTexture(lDoorTex);
    windowTex = SetTexture("office/FFFF");
    windowSpr.setTexture(windowTex);
    rDoorTex = SetTexture("office/R00");
    rDoorSpr.setTexture(rDoorTex);

    miraPlushieTex = SetTexture("office/miraplushie");
    miraPlushieSpr.setTexture(miraPlushieTex);
    monkeTex = SetTexture("office/monkevsbana");
    monkeSpr.setTexture(monkeTex);
    dndDiceTex = SetTexture("office/dnddice");
    dndDiceSpr.setTexture(dndDiceTex);


    cameraTex = SetTexture("cameras/00000");
    cameraSpr.setTexture(cameraTex);

    jumpscareTex = SetTexture("animations/kloster0");
    jumpscareSpr.setTexture(jumpscareTex);

    camTransitionTex = SetTexture("animations/cam0");
    camTransitionSpr.setTexture(camTransitionTex);
    camTransition.LoadAnimation(&camTransitionSpr, camTransitionFrames, 12, "cam");

    deathCard.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    deathCard.setFillColor(Color(0, 0, 0, 255));

    Vector2f cameraScale(VideoMode::getDesktopMode().width / cameraSpr.getGlobalBounds().width, VideoMode::getDesktopMode().height / cameraSpr.getGlobalBounds().height);
    cameraSpr.setScale(cameraScale.x, cameraScale.y);

    Vector2f jumpscareScale(VideoMode::getDesktopMode().width / jumpscareSpr.getGlobalBounds().width, VideoMode::getDesktopMode().height / jumpscareSpr.getGlobalBounds().height);
    jumpscareSpr.setScale(jumpscareScale.x, jumpscareScale.y);

    Vector2f camTransitionScale(VideoMode::getDesktopMode().width / camTransitionSpr.getGlobalBounds().width, VideoMode::getDesktopMode().height / camTransitionSpr.getGlobalBounds().height);
    camTransitionSpr.setScale(camTransitionScale.x, camTransitionScale.y);

    mrKlosterTex = SetTexture("office/DIE");
    mrKlosterSpr.setTexture(mrKlosterTex);
    mrKlosterSpr.setColor(Color(255, 255, 255, 0));

    lDoorSpr.setPosition(-1000, 0);
    windowSpr.setPosition(130, 0);
    rDoorSpr.setPosition(1470, 0);
    miraPlushieSpr.setPosition(-1000, 0);
    monkeSpr.setPosition(-1000, 0);
    dndDiceSpr.setPosition(-1000, 0);
    mrKlosterSpr.setPosition(-1000, 0);

    renderSpr.setScale(1.0, -1.0);
    renderSpr.setPosition(0.0, screen.y);
    renderSpr.setTexture(renderTexture.getTexture());
    gammaSpr.setScale(1.0, -1.0);
    gammaSpr.setPosition(0.0, screen.y);
    gammaSpr.setTexture(gammaTexture.getTexture());

    nightClockText.setFont(font);
    nightClockText.setString(to_string(12)+" AM");
    nightClockText.setCharacterSize(48);
    nightClockText.setFillColor(sf::Color::White);
    nightClockText.setPosition(30, 20);
    hourCounter = 0;
    hourTimer = 90;

    if (!font.loadFromFile("Pixellari.ttf")){
        cout<<"failed to load font"<<endl;
    }

    calculateTimers = false;
    playAudio = false;
    waitToAudio = 0;
    waitToKloster = 0;

    klosterBuffer.loadFromFile("audio/FNAUTN_MrKloster.wav");
    klosterSound.setBuffer(klosterBuffer);
    klosterSound.setVolume(100 * ((float)volume / 100));

    if (!ambience.openFromFile("audio/FNAUTN_Ambience1.wav")){
        cout<<"failed to load music"<<endl;
    }

    fadeInOut.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    fadeInOut.setFillColor(Color(0, 0, 0, 255));
    fadeValue = 255;
    fadeSpeed = 0.3;
    fadeVolume = 0;
    fadeIn = false;

    klosterFadeValue = 0;
    klosterFadeSpeed = 0.01;
    klosterFadeIn = false;
    mrKlosterIsHere = false;
    mrKlosterJumpscare = false;

    ambience.setLoop(true);
    ambience.setVolume(5 * ((float)volume / 100));
    ambience.play();

    ///INIT CONFIGURES INIT CONFIGURES INIT CONFIGURES
    office.Configure(&lDoorTex, &windowTex, &rDoorTex, globalProfes, font, Vector2f(1, 1), volume);
    office.setUI(screen);
    mapa.Configure(&cameraTex, globalProfes, globalRooms);

    updateCameras = false;
    updateWindow = false;

    Progress progress = ReadProgress();


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
            player.Configure(event, lDoorSpr, &office, &mapa, mPos, &camTransitionClock);
        }
        ///EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME EVERY FRAME
        if (!office.getDie()){

            for (int i = 0; i < 4; i++){
                globalProfes[i].MovementOpportunity(&updateCameras, &updateWindow, player.getLookingState(), player.getCurrentCam(), office.getDoorState(0), office.getDoorState(1), &drawClock);
            }

            if (office.getGeneratorClock()->getElapsedTime().asSeconds() >= office.getGeneratorTimer()){
                office.setGeneratorUsage(player.getLookingState());
                float usage = office.getGeneratorUsage();
                office.updateGeneratorTemp(usage);
            }
            if (globalProfes[0].getKlosterMode()){
                globalProfes[0].ReachedOfficeKloster(&updateWindow, office.getLightState(), &drawClock);
            }
            if (globalProfes[1].getDirubeMode()){
                globalProfes[1].ReachedOfficeMati(office.getDoorState(0), office.getDoorState(1), office.getLightState(), &drawClock);
                if (!globalProfes[1].getUpdateDoors()){
                    if (globalProfes[1].getSide() == 0){
                        office.updateLeftDoor();
                    }
                    else if (globalProfes[1].getSide() == 1){
                        office.updateRightDoor();
                    }
                    globalProfes[1].resetUpdateDoors();
                }
            }
            else if (globalProfes[1].getOfficeState()){
                globalProfes[1].WaitToDirubeMode();
            }
        }
        else{
            if (player.getLookingState()){
                player.toggleLookingState();
            }
            office.ShutOff();
            if (!calculateTimers){
                drawClock.restart();
                waitToAudio = randomNumber(4) + 4 + 8;
                waitToKloster = randomNumber(6) + 6 + 24;
                calculateTimers = true;
            }
            if (drawClock.getElapsedTime().asSeconds() >= waitToAudio){
                if (!playAudio){
                    klosterSound.play();
                    playAudio = true;
                    mrKlosterIsHere = true;
                }
                if (!klosterFadeIn){
                    mrKlosterSpr.setColor(Color(255, 255, 255, klosterFadeValue));
                    klosterFadeValue += klosterFadeSpeed;
                    if (klosterFadeValue >= 255){
                        klosterFadeIn = true;
                    }
                }
                if (drawClock.getElapsedTime().asSeconds() >= waitToAudio + waitToKloster){
                    mrKlosterJumpscare = true;
                    globalProfes[0].KlosterJumpscare(&drawClock);
                }
            }

        }
        if (!player.getLookingState()){

            HorizontalScroll (&lDoorSpr, &windowSpr, &rDoorSpr, &mrKlosterSpr, &miraPlushieSpr, &monkeSpr, &dndDiceSpr, mPos, screen);
            if (updateWindow){
                if (office.getLightState()){
                   office.updateWindow();
                }
                updateWindow = false;
            }
            if (!mrKlosterJumpscare){
                renderTexture.draw(lDoorSpr);
                renderTexture.draw(windowSpr);
                renderTexture.draw(rDoorSpr);
                if (mrKlosterIsHere){
                    renderTexture.draw(mrKlosterSpr);
                }

                if(progress.getNight5()){
                    renderTexture.draw(miraPlushieSpr);
                }
                if(progress.getNight6()){
                    renderTexture.draw(monkeSpr);
                }
                if(progress.getCustomNight()){
                    renderTexture.draw(dndDiceSpr);
                }
                gammaTexture.draw(renderSpr, &perspectiveShader);
                window.draw(gammaSpr, &gammaShader);
            }

            if (player.getUpdatePlayer()){

                if (camTransitionClock.getElapsedTime().asSeconds() < camTransition.getDuration(24)){
                    camTransition.PlayAnimationReverse(24);
                    window.draw(camTransitionSpr);
                }
                else{
                    player.PostAnimToggle(&office, &mapa);
                    player.resetUpdatePlayer();
                    player.resetInAnim();
                }
            }
        }
        else{

            if (camTransitionClock.getElapsedTime().asSeconds() < camTransition.getDuration(24)){
                camTransition.PlayAnimation(24);
                window.draw(gammaSpr, &gammaShader);
                window.draw(camTransitionSpr);
            }
            else{

                if (player.getUpdatePlayer()){
                    player.PostAnimToggle(&office, &mapa);
                    player.resetUpdatePlayer();
                    player.resetInAnim();
                }

                if (updateCameras){
                    for (int i = 0; i < 4; i++){
                        if (globalProfes[i].getPos().x == player.getCurrentCam() || globalProfes[i].getLastRoom() == player.getCurrentCam()){
                            updateCameras = false;
                        }
                    }
                    if (!updateCameras){
                        mapa.setCameraSprite(player.getCurrentCam(), player.getLookingState());
                    }
                }
                gammaTexture.draw(cameraSpr);
                window.draw(gammaSpr, &gammaShader);
                window.draw(mapa.getSprite());
                window.draw(mapa.getToggleButton());
            }
        }
        if (!office.getDie()){
            window.draw(office.getGeneratorTempUI());
            window.draw(office.getGeneratorUsageUI());
            window.draw(nightClockText);
        }
        for(int i = 0; i < 4; i++){
            if (globalProfes[i].getJumpscareState()){
                office.StopAlarm();
                ambience.stop();
                if (player.getLookingState()){
                    player.toggleLookingState();
                }
                if (drawClock.getElapsedTime().asSeconds() < 10){
                    if (drawClock.getElapsedTime().asSeconds() < jumpscares.getDuration(globalProfes[i].getJumpscareID())){
                        jumpscares.PlayAnimation(globalProfes[i].getJumpscareID());
                        window.draw(jumpscareSpr);
                    }
                    else{
                        window.draw(deathCard);
                        if (event.mouseButton.button == Mouse::Left){
                            if (event.type == Event::MouseButtonPressed){
                                return false;
                            }
                        }
                    }
                }
                else{
                    return false;
                }
            }
        }
        if (!fadeIn){
            fadeInOut.setFillColor(Color(0, 0, 0, fadeValue));
            ambience.setVolume(fadeVolume);

            fadeValue -= fadeSpeed;
            fadeVolume += (fadeSpeed / 51) * ((float)volume / 100);
            if (fadeValue <= 0){
                fadeIn = true;
                ambience.setVolume(5);
            }
            window.draw(fadeInOut);
        }
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return false;
        }

        if (nightClock.getElapsedTime().asSeconds() <= 540){ //night duration
            if (updateNightClock(&hourCounter, &nightClockText, &nightClock, &hourTimer)){
                for (int i = 0; i < 4; i++){
                    switch(i){
                    case 2://maxi
                        if (hourCounter >= 2 && hourCounter <= 4){
                            globalProfes[i].IncreaseProfeDif();
                        }
                        break;
                    case 1://mati
                    case 3://vastag
                        if (hourCounter >= 3 && hourCounter <= 4){
                            globalProfes[i].IncreaseProfeDif();
                        }
                        break;
                    default:
                        break;
                    }
                }
                ambience.setVolume(ambience.getVolume() + (3) * ((float)volume / 100));
            }
        }
        else{

            return true;
        }
    }
}

#endif // DRAWCALL_H_INCLUDED
