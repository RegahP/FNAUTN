#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

void CustomNightMenu(RenderWindow& window, Vector2i mPos, float scaleX, float scaleY, int customDifs[], bool* customNightPlay, bool* play, Sound click1, Sprite* customNightSpr, Text txtDifs[]);
Text UpdateDif(Text txtDif, int dif, Vector2f txtPos, bool first);
Text UpdateDif(Text txtDif, float dif, Vector2f txtPos);

void Menu(RenderWindow& window){

    Vector2i mPos(0, 0);
    Texture menuTextTex = SetTexture("textures/MenuArtText");
    Sprite menuTextSpr;
    Texture menuContTex = SetTexture("textures/MenuArtCont");
    Sprite menuContSpr;
    Texture menuNight6Tex = SetTexture("textures/MenuArtNoche6");
    Sprite menuNight6Spr;
    Texture menuCustomNightTex = SetTexture("textures/MenuArtNocheCustom");
    Sprite menuCustomNightSpr;
    Texture customNightTex = SetTexture("textures/NocheCustom");
    Sprite customNightSpr;
    Texture menuBGTex = SetTexture("textures/MenuArtBG");
    Sprite menuBGSpr;
    Texture menuSmokeTex = SetTexture("textures/MenuArtSmoke");
    Sprite menuSmokeSpr;
    Texture menuStarsTex = SetTexture("textures/Star");
    Sprite menuStarsSpr[3];

    Font font;
    Text continueNight;

    if (!font.loadFromFile("Pixellari.ttf")){
        cout<<"failed to load font"<<endl;
    }

    Vector2f menuBGParallax;
    Vector2f menuSmokeParallax;
    int parallaxBG = 100;
    int parallaxSmoke = 50;

    Texture creditsTex = SetTexture("textures/CreditsArt");
    Sprite creditsSpr;
    Texture settingsTex = SetTexture("textures/SettingsArt");
    Sprite settingsSpr;
    RectangleShape creditsBG;

    RectangleShape fadeInOut;
    float fadeValue;
    float fadeSpeed;
    float fadeVolume;
    bool fadeIn = false;
    bool fadeOut = false;

    bool play = false;

    bool newGame = false;
    bool continueButtonFlag = false;
    bool night6ButtonFlag = false;
    bool customNightFlag = false;
    bool night420Flag = false;

    bool night6Play = false;
    bool customNightPlay = false;

    int customDifs[4] = {0, 0, 0, 0};
    Text txtDifs[4];

    for (int i = 0; i < 4; i++){
        txtDifs[i].setFont(font);
    }

    int nightNum = 1;

    Progress progress;

    Music menuMusic;
    SoundBuffer clickBuffer;
    Sound click1;

    clickBuffer.loadFromFile("audio/FNAUTN_Click1.wav");
    click1.setBuffer(clickBuffer);
    click1.setVolume(15);

    bool showCredits = false;
    bool showSettings = false;

    menuTextSpr.setTexture(menuTextTex);
    menuBGSpr.setTexture(menuBGTex);
    menuSmokeSpr.setTexture(menuSmokeTex);

    creditsSpr.setTexture(creditsTex);
    settingsSpr.setTexture(settingsTex);
    menuContSpr.setTexture(menuContTex);
    menuNight6Spr.setTexture(menuNight6Tex);
    menuCustomNightSpr.setTexture(menuCustomNightTex);
    customNightSpr.setTexture(customNightTex);

    menuStarsSpr[0].setTexture(menuStarsTex);
    menuStarsSpr[1].setTexture(menuStarsTex);
    menuStarsSpr[2].setTexture(menuStarsTex);

    creditsBG.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    creditsBG.setFillColor(Color(0, 0, 0, 128));
    fadeInOut.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    fadeInOut.setFillColor(Color(0, 0, 0, 255));

    float scaleX = VideoMode::getDesktopMode().width / menuTextSpr.getGlobalBounds().width;
    float scaleY = VideoMode::getDesktopMode().height / menuTextSpr.getGlobalBounds().height;

    menuTextSpr.setScale(scaleX, scaleY);
    menuBGSpr.setOrigin(menuBGSpr.getTextureRect().width / 2, menuBGSpr.getTextureRect().height / 2);
    menuBGSpr.setPosition(menuBGSpr.getTextureRect().width / 2, menuBGSpr.getTextureRect().height / 2);
    menuSmokeSpr.setOrigin(menuBGSpr.getTextureRect().width / 2, menuSmokeSpr.getTextureRect().height / 2);
    menuSmokeSpr.setPosition(menuBGSpr.getTextureRect().width / 2, menuSmokeSpr.getTextureRect().height / 2);
    menuBGSpr.setScale(scaleX * 1.05, scaleY * 1.05);
    menuSmokeSpr.setScale(scaleX *  1.05, scaleY *  1.05);
    creditsSpr.setScale(scaleX, scaleY);
    settingsSpr.setScale(scaleX, scaleY);
    menuContSpr.setScale(scaleX, scaleY);
    menuNight6Spr.setScale(scaleX, scaleY);
    menuCustomNightSpr.setScale(scaleX, scaleY);
    customNightSpr.setScale(scaleX, scaleY);

    menuStarsSpr[0].setPosition(1496*scaleX, 796*scaleY);
    menuStarsSpr[0].setScale(4*scaleX, 4*scaleY);
    menuStarsSpr[1].setPosition(1418*scaleX, 796*scaleY);
    menuStarsSpr[1].setScale(4*scaleX, 4*scaleY);
    menuStarsSpr[2].setPosition(1340*scaleX, 796*scaleY);
    menuStarsSpr[2].setScale(4*scaleX, 4*scaleY);

    continueNight.setFont(font);
    continueNight.setPosition(101*scaleX, 464*scaleY);
    continueNight.setCharacterSize(24);
    continueNight.setFillColor(sf::Color::White);

    FloatRect newGameButton = FloatRect(0*scaleX, 278*scaleY, 464*scaleX, 112*scaleY);
    FloatRect continueButton = FloatRect(0*scaleX, 390*scaleY, 464*scaleX, 112*scaleY);
    FloatRect night6Button = FloatRect(0*scaleX, 502*scaleY, 412*scaleX, 90*scaleY);
    FloatRect customNightButton = FloatRect(0*scaleX, 592*scaleY, 464*scaleX, 108*scaleY);
    FloatRect exitButton = FloatRect(0*scaleX, 746*scaleY, 292*scaleX, 116*scaleY);
    FloatRect settingsButton = FloatRect(292*scaleX, 746*scaleY, 412*scaleX, 116*scaleY);
    FloatRect creditsButton = FloatRect(1395*scaleX, 118*scaleY, 183*scaleX, 52*scaleY);
    FloatRect backButton = FloatRect(0, 790*scaleY, 206*scaleX, 100*scaleY);

    FloatRect volumeMinus = FloatRect (867*scaleX, 460*scaleY, 42*scaleX, 64*scaleY);
    FloatRect volumePlus = FloatRect (1073*scaleX, 460*scaleY, 45*scaleX, 64*scaleY);
    FloatRect gammaMinus = FloatRect (867*scaleX, 565*scaleY, 42*scaleX, 64*scaleY);
    FloatRect gammaPlus = FloatRect (1073*scaleX, 565*scaleY, 45*scaleX, 64*scaleY);

    int volume = ReadProgress().getVolume();
    float gamma = ReadProgress().getGamma();

    Text txtVolume;
    Text txtGamma;

    Vector2f txtVolumePos = Vector2f(1053*scaleX, 450*scaleY);
    Vector2f txtGammaPos = Vector2f(1053*scaleX, 555*scaleY);

    txtVolume.setFont(font);
    txtVolume = UpdateDif(txtVolume, volume, txtVolumePos, true);
    txtVolume.setCharacterSize(64);
    txtVolume.setFillColor(sf::Color::White);
    txtGamma.setFont(font);
    txtGamma = UpdateDif(txtGamma, gamma, Vector2f(txtGammaPos.x - 40, txtGammaPos.y));
    txtGamma.setCharacterSize(64);
    txtGamma.setFillColor(sf::Color::White);

    fadeValue = 255;
    fadeSpeed = 0.3;
    fadeVolume = 0;

    progress = ReadProgress();
    progress.setNight(1);
    progress.setNight(5);
    progress.setNight5();
    progress.setNight6();
    progress.setCustomNight();

    click1.setVolume(15 * ((float)progress.getVolume() / 100));

    continueNight.setString("Noche " + to_string(progress.getNight()));

    if(progress.getNight() != 1){
        continueButtonFlag = true;
    }
    if(progress.getNight5()){
        night6ButtonFlag = true;
    }
    if (progress.getNight6()){
        customNightFlag = true;
    }
    if (progress.getCustomNight()){
        night420Flag = true;
    }

    if (!menuMusic.openFromFile("audio/FNAUTN_MenuMusic.wav")){
        cout<<"failed to load music"<<endl;
    }
    menuMusic.setLoop(true);
    menuMusic.setVolume(0);
    menuMusic.play();

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
            if (fadeIn){
                if (event.mouseButton.button == Mouse::Left && !play){
                    if (event.type == Event::MouseButtonPressed){

                        if (!showCredits && !showSettings){
                            if (CheckHover(newGameButton, mPos)){
                                NewGame();
                                newGame = true;
                                play = true;
                                click1.play();
                            }
                            else if (CheckHover(continueButton, mPos) && continueButtonFlag){
                                nightNum = ContinueGame();
                                play = true;
                                cout<<nightNum;
                                click1.play();
                            }
                            else if (CheckHover(night6Button, mPos) && night6ButtonFlag){
                                night6Play = true;
                                play = true;
                                click1.play();
                            }
                            else if (CheckHover(customNightButton, mPos) && customNightFlag){
                                click1.play();
                                CustomNightMenu(window, mPos, scaleX, scaleY, customDifs, &customNightPlay, &play, click1, &customNightSpr, txtDifs);
                            }
                            else if (CheckHover(exitButton, mPos)){
                                return;
                                click1.play();
                            }
                            else if (CheckHover(creditsButton, mPos)){
                                showCredits = !showCredits;
                                click1.play();
                            }
                            else if (CheckHover(settingsButton, mPos)){
                                showSettings = !showSettings;
                                click1.play();
                            }
                        }
                        else if (showCredits){
                            if (CheckHover(backButton, mPos)){
                                showCredits = !showCredits;
                                click1.play();
                            }
                        }
                        else if (showSettings){
                            if (CheckHover(backButton, mPos)){
                                showSettings = !showSettings;
                                fadeVolume = menuMusic.getVolume();
                                click1.play();

                                progress.setGamma(gamma);
                                SaveSettings(progress);
                            }
                            if (CheckHover(volumeMinus, mPos)){
                                if (volume >= 5){
                                    volume -= 5;
                                    txtVolume = UpdateDif(txtVolume, volume, txtVolumePos, false);
                                    click1.play();

                                    menuMusic.setVolume(50 * ((float)volume / 100));
                                    click1.setVolume(15 * ((float)volume / 100));
                                    progress.setVolume(volume);
                                }
                            }
                            if (CheckHover(volumePlus, mPos)){
                                if (volume <= 95){
                                    volume += 5;
                                    txtVolume = UpdateDif(txtVolume, volume, txtVolumePos, false);
                                    click1.play();

                                    menuMusic.setVolume(50 * ((float)volume / 100));
                                    click1.setVolume(15 * ((float)volume / 100));
                                    progress.setVolume(volume);
                                }
                            }
                            if (CheckHover(gammaMinus, mPos)){
                                if (gamma >= 0.5){
                                    gamma -= 0.1;
                                    txtGamma = UpdateDif(txtGamma, gamma, txtGammaPos);
                                    click1.play();
                                }
                            }
                            if (CheckHover(gammaPlus, mPos)){
                                if (gamma <= 1.45){
                                    gamma += 0.1;
                                    gamma *= 1;
                                    txtGamma = UpdateDif(txtGamma, gamma, txtGammaPos);
                                    click1.play();
                                }
                            }
                        }
                    }
                }
            }
        }

        menuBGParallax = Vector2f((-(float)mPos.x / parallaxBG) + menuBGSpr.getLocalBounds().width / 2 * scaleX + menuBGSpr.getLocalBounds().width / (parallaxBG * 4 * scaleX), (-(float)mPos.y / parallaxBG) + menuBGSpr.getLocalBounds().height / 2 * scaleY + menuBGSpr.getLocalBounds().height / (parallaxBG * 4) * scaleY);
        menuSmokeParallax = Vector2f((-(float)mPos.x / parallaxSmoke) + menuSmokeSpr.getLocalBounds().width / 2  * scaleX + menuSmokeSpr.getLocalBounds().width / (parallaxSmoke * 4 * scaleX), (-(float)mPos.y / parallaxSmoke) + menuSmokeSpr.getLocalBounds().height / 2  * scaleY + menuSmokeSpr.getLocalBounds().height / (parallaxSmoke * 4) * scaleY);
        menuBGSpr.setPosition(menuBGParallax);
        menuSmokeSpr.setPosition(menuSmokeParallax);
        window.draw(menuBGSpr);
        window.draw(menuSmokeSpr);

        if (!showCredits && !showSettings){
            window.draw(menuTextSpr);
            if(continueButtonFlag){
                window.draw(menuContSpr);
                window.draw(continueNight);
            }
            if(night6ButtonFlag){
                window.draw(menuNight6Spr);
                window.draw(menuStarsSpr[0]);
            }
            if(customNightFlag){
                window.draw(menuCustomNightSpr);
                window.draw(menuStarsSpr[1]);
            }
            if (night420Flag){
                window.draw(menuStarsSpr[2]);
            }
        }
        else if (showCredits){
            window.draw(creditsBG);
            window.draw(creditsSpr);
        }
        else if (showSettings){
            window.draw(creditsBG);
            window.draw(settingsSpr);
            window.draw(txtVolume);
            window.draw(txtGamma);
        }
        if (customNightPlay){
            window.draw(customNightSpr);
            window.draw(txtDifs[0]);
            window.draw(txtDifs[1]);
            window.draw(txtDifs[2]);
            window.draw(txtDifs[3]);
        }
        if (!fadeIn){
            fadeInOut.setFillColor(Color(0, 0, 0, fadeValue));
            menuMusic.setVolume(fadeVolume);

            fadeValue -= fadeSpeed;
            fadeVolume += (fadeSpeed / 5.1) * ((float)volume / 100);
            cout<<fadeVolume<<endl;
            if (fadeValue <= 0){
                fadeIn = true;
            }
            window.draw(fadeInOut);
        }
        if (play){
            if (!fadeOut){
                fadeInOut.setFillColor(Color(0, 0, 0, fadeValue));
                menuMusic.setVolume(fadeVolume);
                fadeValue += fadeSpeed;
                fadeVolume -= (fadeSpeed / 5.1) * ((float)volume / 100);
                cout<<fadeVolume<<endl;
                if (fadeValue >= 255){
                    fadeOut = true;
                }
                window.draw(fadeInOut);
            }
            else{
                play = false;
                menuMusic.stop();
                if(newGame){
                    night(window, 1, volume);
                    newGame = false;
                }
                else if(night6Play){
                    night(window, 6, volume);
                    night6Play = false;
                }
                else if (customNightPlay){
                    customNight(window, 7, customDifs, volume);
                    customNightPlay = false;
                }
                else{
                    night(window, nightNum, volume);
                }
                progress = ReadProgress();

                if(progress.getNight() != 1){
                    continueButtonFlag = true;
                }
                if(progress.getNight5()){
                    night6ButtonFlag = true;
                }
                fadeIn = false;
                fadeOut = false;
                menuMusic.play();

                fadeValue = 255;
                fadeSpeed = 0.3;
                fadeVolume = 0;
            }
        }

        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return;
        }

    }
}

void CustomNightMenu(RenderWindow& window, Vector2i mPos, float scaleX, float scaleY, int customDifs[], bool* customNightPlay, bool* play, Sound click1, Sprite* customNightSpr, Text txtDifs[]){

    int difs[4] = {0, 0, 0, 0};

    Vector2f txtPositions[4];
    txtPositions[0] = Vector2f(332*scaleX, 578*scaleY); //k
    txtPositions[2] = Vector2f(686*scaleX, 578*scaleY); //x
    txtPositions[3] = Vector2f(1038*scaleX, 578*scaleY); //v
    txtPositions[1] = Vector2f(1388*scaleX, 578*scaleY);//t

    for (int i = 0; i < 4; i++){
        txtDifs[i] = UpdateDif(txtDifs[i], customDifs[i], Vector2f(txtPositions[i].x - 10, txtPositions[i].y), true);
        txtDifs[i].setCharacterSize(64);
        txtDifs[i].setFillColor(sf::Color::White);
    }

    FloatRect customKlosterMinus = FloatRect (147*scaleX, 588*scaleY, 42*scaleX, 64*scaleY);
    FloatRect customKlosterPlus = FloatRect (353*scaleX, 588*scaleY, 45*scaleX, 64*scaleY);
    FloatRect customMaxiMinus = FloatRect (503*scaleX, 588*scaleY, 42*scaleX, 64*scaleY);
    FloatRect customMaxiPlus = FloatRect (706*scaleX, 588*scaleY, 45*scaleX, 64*scaleY);
    FloatRect customVastagMinus = FloatRect (856*scaleX, 588*scaleY, 42*scaleX, 64*scaleY);
    FloatRect customVastagPlus = FloatRect (1059*scaleX, 588*scaleY, 45*scaleX, 64*scaleY);
    FloatRect customMatiMinus = FloatRect (1205*scaleX, 588*scaleY, 42*scaleX, 64*scaleY);
    FloatRect customMatiPlus = FloatRect (1406*scaleX, 588*scaleY, 45*scaleX, 64*scaleY);
    FloatRect customPlayButton = FloatRect (1312*scaleX, 785*scaleY, 226*scaleX, 74*scaleY);

    while (window.isOpen()){
        window.clear();
        mPos.x = Mouse::getPosition(window).x;
        mPos.y = Mouse::getPosition(window).y;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    if (CheckHover(customKlosterMinus, mPos)){
                        if (customDifs[0] > 0){
                            customDifs[0]--;
                            txtDifs[0] = UpdateDif(txtDifs[0], customDifs[0], txtPositions[0], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customKlosterPlus, mPos)){
                        if (customDifs[0] < 20){
                            customDifs[0]++;
                            txtDifs[0] = UpdateDif(txtDifs[0], customDifs[0], txtPositions[0], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customMaxiMinus, mPos)){
                        if (customDifs[2] > 0){
                            customDifs[2]--;
                            txtDifs[2] = UpdateDif(txtDifs[2], customDifs[2], txtPositions[2], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customMaxiPlus, mPos)){
                        if (customDifs[2] < 20){
                            customDifs[2]++;
                            txtDifs[2] = UpdateDif(txtDifs[2], customDifs[2], txtPositions[2], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customVastagMinus, mPos)){
                        if (customDifs[3] > 0){
                            customDifs[3]--;
                            txtDifs[3] = UpdateDif(txtDifs[3], customDifs[3], txtPositions[3], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customVastagPlus, mPos)){
                        if (customDifs[3] < 20){
                            customDifs[3]++;
                            txtDifs[3] = UpdateDif(txtDifs[3], customDifs[3], txtPositions[3], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customMatiMinus, mPos)){
                        if (customDifs[1] > 0){
                            customDifs[1]--;
                            txtDifs[1] = UpdateDif(txtDifs[1], customDifs[1], txtPositions[1], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customMatiPlus, mPos)){
                        if (customDifs[1] < 20){
                            customDifs[1]++;
                            txtDifs[1] = UpdateDif(txtDifs[1], customDifs[1], txtPositions[1], false);
                            click1.play();
                        }
                    }
                    else if (CheckHover(customPlayButton, mPos)){

                        *customNightPlay = true;
                        *play = true;
                        click1.play();
                        return;
                    }
                }
            }
        }
        window.draw(*customNightSpr);
        window.draw(txtDifs[0]);
        window.draw(txtDifs[1]);
        window.draw(txtDifs[2]);
        window.draw(txtDifs[3]);
        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return;
        }
    }
}

Text UpdateDif(Text txtDif, int dif, Vector2f txtPos, bool first){
    Text txt = txtDif;
    txt.setString(to_string(dif));
    FloatRect bounds = txt.getLocalBounds();
    int offset = 0;
    if (dif < 10){
        offset = 10;
    }
    else if (dif < 100){
        offset = 30;
    }
    else{
        offset = 50;
    }
    if (first){
       txt.setPosition(txtPos.x - bounds.width - offset, txtPos.y);
       return txt;
    }
    txt.setPosition(txtPos.x - bounds.width, txtPos.y);
    return txt;
}
Text UpdateDif(Text txtDif, float dif, Vector2f txtPos){
    Text txt = txtDif;
    txt.setString(to_string(dif).erase(3));
    FloatRect bounds = txt.getLocalBounds();
    txt.setPosition(txtPos.x - bounds.width, txtPos.y);
    return txt;
}

#endif // MENU_H_INCLUDED
