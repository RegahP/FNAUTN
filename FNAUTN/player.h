#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{

private:
    bool isLookingAtCams = false;
    int currentCam;

    Texture* pTex;

public:
    /*
    int getCurrentCam();
    bool getLookingState();

    void setCurrentCam(int ID);
    void toggleLookingState();
    */
    int getCurrentCam(){
        return currentCam;
    }
    bool getLookingState(){
        return isLookingAtCams;
    }

    void setCurrentCam(int ID){
        currentCam = ID;
    }
    void toggleLookingState(){
        isLookingAtCams = !isLookingAtCams;

    }

    void CheckToggleLookingState(Event event){

        if (event.key.code == Keyboard::Space){
            if (event.type == Event::KeyPressed){
                toggleLookingState();
            }
        }
    }

    void CheckHoldLight(Event event, Sprite officeSpr, Office office, Vector2i mPos){

        FloatRect tempHitbox = office.getHitbox(2);
        FloatRect movingHitbox = FloatRect(tempHitbox.left + officeSpr.getPosition().x, tempHitbox.top, tempHitbox.width, tempHitbox.height);

        if (CheckHover(movingHitbox, mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office.setLightState(true);
                }
            }
        }
        if (event.key.code == Mouse::Left){
            if (event.type == Event::MouseButtonReleased){
                office.setLightState(false);
            }
        }
    }

    /*void CheckToggleDoor(Event event){

    switch(event.type){
        case Event::MouseButtonPressed:{
            switch(event.key.code){
                case Mouse::Left:
                    //toggleLookingState();
                break;
                }
            break;
            }
        break;
        }
    }*/

    void CheckClickCams(Event event, Map* mapa, Vector2i mPos){
        for (int i = 0; i < 10; i++){
            if (CheckHover(mapa->getHitbox(i), mPos)){
                if (event.key.code == Mouse::Left){
                    if (event.type == Event::MouseButtonPressed){
                        if (mapa->getToggleButtonState() >= 2 && i >= 7){
                            mapa->setMapSprite(i);
                            mapa->setLastCam(1, i);
                            setCurrentCam(mapa->getLastCam(1));
                        }
                        else if (mapa->getToggleButtonState() < 2 && i < 7){
                            mapa->setMapSprite(i);
                            mapa->setLastCam(0, i);
                            setCurrentCam(mapa->getLastCam(0));
                        }
                        mapa->setCameraSprite(currentCam);
                    }
                }
            }
        }

        if (CheckHover(mapa->getToggleButtonHitbox(), mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    mapa->HightlightButton();

                    if (mapa->getToggleButtonState() == 1){
                        setCurrentCam(mapa->getLastCam(1));
                    }
                    else if (mapa->getToggleButtonState() == 3){
                        setCurrentCam(mapa->getLastCam(0));
                    }
                }
                else if (event.type == Event::MouseButtonReleased){
                    mapa->ToggleButton();
                    mapa->setCameraSprite(currentCam);
                }
            }
        }
    }

    void Configure(Event event, Texture* tex, Sprite officeSpr, Office office, Map* mapa, Vector2i mPos){
        pTex = tex;
        CheckToggleLookingState(event);
        CheckHoldLight(event, officeSpr, office, mPos);
        CheckClickCams(event, mapa, mPos);
    }

};



#endif // PLAYER_H_INCLUDED
