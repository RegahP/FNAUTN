#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

Texture SetTexture(string textureName);

bool CheckClickToggle( bool flag, Event event){

    switch(event.type){
        case Event::MouseButtonPressed:{
            switch(event.key.code){
                case Mouse::Left:

                    if(!flag){
                    return true;

                    } else if(flag){
                    return false;
                    }
                break;
                }
            break;
            }
        break;
        }
    return flag;
}

bool CheckHover(FloatRect obj, Vector2i mPos){

    if(obj.contains(mPos.x, mPos.y)){
        return true;
    }
    else{
        return false;
    }
}

bool CheckSpaceToggle( bool flag, Event event){

    switch(event.type){
        case Event::KeyPressed:{
            switch(event.key.code){
                case Keyboard::Space:

                    if(!flag){
                    return true;

                    } else if(flag){
                    return false;
                    }
                break;
                }
            break;
            }
        break;
        }
    return flag;
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

    float mult = 0.001;
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
