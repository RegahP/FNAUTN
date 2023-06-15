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
    if (!texture.loadFromFile(textureName))
    {
        cout<<"failed to load "<<textureName<<endl;
    }
    return texture;
}

void HorizontalScroll (Sprite* sprite, Vector2i mPos, Vector2i screen){
    if (mPos.x > screen.x * 0.85 && sprite->getPosition().x > -(sprite->getTextureRect().width-screen.x)){
        sprite->move(-1.5, 0);
    }
    if (mPos.x < screen.x * 0.15 && sprite->getPosition().x < 0){
        sprite->move(1.5, 0);
    }
}

#endif // INPUT_H_INCLUDED
