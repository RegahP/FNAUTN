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

#endif // INPUT_H_INCLUDED
