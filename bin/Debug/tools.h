#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

bool updateNightClock(int* hourCounter, Text* nightClockText, Clock* nightClock, float* hourTimer){

    if(nightClock->getElapsedTime().asSeconds() > *hourTimer){
        *hourCounter += 1;
        *hourTimer += 90;
        nightClockText->setString(to_string(*hourCounter)+" AM");
        return true;
    }
    return false;
}

bool CheckHover(FloatRect obj, Vector2i mPos){

    if(obj.contains(mPos.x, mPos.y)){
        return true;
    }
    else{
        return false;
    }
}

int randomNumber(int maxNumber){

    int number = rand() % maxNumber + 1;
    return number;
}

Texture SetTexture(string textureName){

    Texture texture;
    string extension = ".png";
    if (!texture.loadFromFile(textureName + extension))
    {
        cout<<"failed to load "<<textureName<<endl;
    }
    return texture;
}

void HorizontalScroll (Sprite* lDoor, Sprite* window, Sprite* rDoor, Sprite* mrKloster, Sprite* miraPlushie, Sprite* monke, Sprite* dndDice, Vector2i mPos, Vector2i screen){

    float speed = 1.6;
    if (mPos.x > screen.x * 0.85 && rDoor->getPosition().x > -(rDoor->getTextureRect().width-screen.x)){
        lDoor->move(-speed, 0);
        window->move(-speed, 0);
        rDoor->move(-speed, 0);
        mrKloster->move(-speed, 0);
        miraPlushie->move(-speed, 0);
        monke->move(-speed, 0);
        dndDice->move(-speed, 0);
    }

    if (mPos.x < screen.x * 0.15 && lDoor->getPosition().x < 0){
        lDoor->move(speed, 0);
        window->move(speed, 0);
        rDoor->move(speed, 0);
        mrKloster->move(speed, 0);
        miraPlushie->move(speed, 0);
        monke->move(speed, 0);
        dndDice->move(speed, 0);
    }
}

void DrawIntroCard (RenderWindow& window){

    RectangleShape fadeInOut;
    float fadeValue;
    float fadeSpeed;
    bool fadeIn = false;
    bool fadeOut = false;

    Texture introCardTex;
    Sprite introCardSpr;

    fadeInOut.setSize(Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
    fadeInOut.setFillColor(Color(0, 0, 0, 255));
    fadeValue = 255;
    fadeSpeed = 0.15f;

    introCardTex = SetTexture("textures/introcard");
    introCardTex.setSmooth(true);
    introCardSpr.setTexture(introCardTex);


    introCardSpr.setOrigin(introCardSpr.getTextureRect().width / 2, introCardSpr.getTextureRect().height / 2);
    introCardSpr.setPosition(introCardSpr.getTextureRect().width / 2, introCardSpr.getTextureRect().height / 2);

    Clock waitClock;

    while(window.isOpen()){
        window.clear();
        introCardSpr.scale(1.000002f, 1.000002f);
        if (!fadeIn){
            fadeInOut.setFillColor(Color(0, 0, 0, fadeValue));
            fadeValue -= fadeSpeed;

            cout<<"lol "<<fadeValue<<endl;

            if (fadeValue <= 0){
                fadeIn = true;
                fadeOut = true;
                waitClock.restart();
            }
        }


        if (fadeOut && waitClock.getElapsedTime().asSeconds() >= 6){
                if(fadeValue <= 255){
                    fadeValue += fadeSpeed;
                    fadeInOut.setFillColor(Color(0, 0, 0, fadeValue));
                }
                cout<<"lol 2 "<<fadeValue<<" tiempo: "<<waitClock.getElapsedTime().asSeconds()<<endl;

        }
        if (fadeOut && fadeValue >= 255){
            return;
        }
        window.draw(introCardSpr);
        window.draw(fadeInOut);
        window.display();
    }

}

void DisplayNightCard(RenderWindow& window, int night, float volume){

    Texture nightCardTex;
    Sprite nightCardSpr;

    nightCardTex = SetTexture("textures/nightcard_" + to_string(night - 1));
    nightCardSpr.setTexture(nightCardTex);

    SoundBuffer click2Buffer;
    Sound click2;

    click2Buffer.loadFromFile("audio/FNAUTN_Click2.wav");
    click2.setBuffer(click2Buffer);
    click2.setVolume(20 * ((float)volume / 100));

    click2.play();

    Clock waitClock;

    while(window.isOpen()){
        window.clear();

        if(waitClock.getElapsedTime().asSeconds() >= 3){
            return;
        }

        window.draw(nightCardSpr);
        window.display();
    }
}

#endif // INPUT_H_INCLUDED
