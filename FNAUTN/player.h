#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{

private:
    bool isLookingAtCams = false;
    int currentCam;

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

    void CheckToggleLookingState(Event event, Office* office, Map* mapa){

        if (event.key.code == Keyboard::Space){
            if (event.type == Event::KeyPressed){
                toggleLookingState();
                office->setLightState(false);
                office->setGeneratorUsage(isLookingAtCams);
                if (isLookingAtCams){
                    mapa->setCameraSprite(currentCam);
                }
            }
        }
    }

    void CheckHoldLight(Event event, Sprite lDoorSpr, Office* office, Vector2i mPos){

        FloatRect tempHitbox = office->getHitbox(2);
        FloatRect movingHitbox = FloatRect(tempHitbox.left + lDoorSpr.getPosition().x, tempHitbox.top, tempHitbox.width, tempHitbox.height);

        if (CheckHover(movingHitbox, mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office->setLightState(true);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }
        if (event.key.code == Mouse::Left){
            if (event.type == Event::MouseButtonReleased){
                office->setLightState(false);
                office->setGeneratorUsage(isLookingAtCams);
                ///AGREGAR SET GENERATOR USAGE A LAS PUERTAS
            }
        }
    }

    void CheckToggleDoors(Event event, Sprite lDoorSpr, Office* office, Vector2i mPos){

        FloatRect lHitbox = office->getHitbox(0);
        FloatRect rHitbox = office->getHitbox(1);
        FloatRect movingLHitbox = FloatRect(lHitbox.left + lDoorSpr.getPosition().x, lHitbox.top, lHitbox.width, lHitbox.height);
        FloatRect movingRHitbox = FloatRect(rHitbox.left + lDoorSpr.getPosition().x, rHitbox.top, rHitbox.width, rHitbox.height);

        if (CheckHover(movingLHitbox, mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonReleased){
                    office->toggleDoorState(0);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }

        if (CheckHover(movingRHitbox, mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office->toggleDoorState(1);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }
    }

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

    void Configure(Event event, Sprite lDoorSpr, Office* office, Map* mapa, Vector2i mPos){
        CheckToggleLookingState(event, office, mapa);
        if (isLookingAtCams){
            CheckClickCams(event, mapa, mPos);
        }
        else{
            CheckHoldLight(event, lDoorSpr, office, mPos);
            CheckToggleDoors(event, lDoorSpr, office, mPos);
        }
    }
};



#endif // PLAYER_H_INCLUDED
