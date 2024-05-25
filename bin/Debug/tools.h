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

    int number = rand()%maxNumber + 1;
    return number;
}

Texture SetTexture(string textureName){

    Texture texture;
    string extension = ".png";
    if (!texture.loadFromFile(textureName+extension))
    {
        cout<<"failed to load "<<textureName<<endl;
    }
    return texture;
}

void HorizontalScroll (Sprite* lDoor, Sprite* window, Sprite* rDoor, Sprite* mrKloster, Sprite* achievements, Vector2i mPos, Vector2i screen){

    float speed = 1.6;
    if (mPos.x > screen.x * 0.85 && rDoor->getPosition().x > -(rDoor->getTextureRect().width-screen.x)){
        lDoor->move(-speed, 0);
        window->move(-speed, 0);
        rDoor->move(-speed, 0);
        mrKloster->move(-speed, 0);
        achievements->move(-speed, 0);
    }

    if (mPos.x < screen.x * 0.15 && lDoor->getPosition().x < 0){

        lDoor->move(speed, 0);
        window->move(speed, 0);
        rDoor->move(speed, 0);
        mrKloster->move(speed, 0);
        achievements->move(speed, 0);
    }
}

#endif // INPUT_H_INCLUDED
