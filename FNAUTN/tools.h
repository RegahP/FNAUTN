#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

void updateNightClock(int* hourCounter, Text* nightClockText, Clock* nightClock, float* hourTimer){

    if(nightClock->getElapsedTime().asSeconds() > *hourTimer){
            *hourCounter += 1;
            *hourTimer += 90;
            nightClockText->setString(to_string(*hourCounter)+" AM");
        }
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

void HorizontalScroll (Sprite* lDoor, Sprite* window, Sprite* rDoor, Vector2i mPos, Vector2i screen){

    float mult = 0.003;
    if (mPos.x > screen.x * 0.85 && rDoor->getPosition().x > -(rDoor->getTextureRect().width-screen.x)){
        lDoor->move(screen.x * -mult, 0);
        window->move(screen.x * -mult, 0);
        rDoor->move(screen.x * -mult, 0);
    }

    if (mPos.x < screen.x * 0.15 && lDoor->getPosition().x < 0){

        lDoor->move(screen.x * mult, 0);
        window->move(screen.x * mult, 0);
        rDoor->move(screen.x * mult, 0);
    }
}

#endif // INPUT_H_INCLUDED
