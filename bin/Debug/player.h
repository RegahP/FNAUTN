#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{

private:
    bool isLookingAtCams = false;
    bool updateStatic = false;
    bool updatePlayer = false;
    bool inAnim = false;
    int currentCam = 0;

    SoundBuffer laptop1Buffer;
    Sound laptop1Sound;

    SoundBuffer laptop2Buffer;
    Sound laptop2Sound;

    SoundBuffer laptop3Buffer;
    Sound laptop3Sound;

    SoundBuffer laptop4Buffer;
    Sound laptop4Sound;

    SoundBuffer click2Buffer;
    Sound click2;

    SoundBuffer click3Buffer;
    Sound click3;

public:

    int getCurrentCam(){
        return currentCam;
    }
    bool getLookingState(){
        return isLookingAtCams;
    }
    bool getUpdatePlayer (){
        return updatePlayer;
    }
    void resetUpdatePlayer (){
        updatePlayer = false;
    }
    bool getUpdateStatic (){
        return updateStatic;
    }
    void resetUpdateStatic (){
        updateStatic = false;
    }
    void resetInAnim (){
        inAnim = false;
    }
    void setCurrentCam(int ID){
        currentCam = ID;
    }
    void toggleLookingState(){
        isLookingAtCams = !isLookingAtCams;

        if (isLookingAtCams){
            laptop1Sound.play();
        }
        else{
            laptop1Sound.stop();

            if (laptop3Sound.getStatus() == 2){
                laptop3Sound.stop();
                laptop4Sound.play();
            }
            laptop2Sound.play();
        }

        updatePlayer = true;
    }

    int getLaptop1SoundStatus(bool laptop3){
        if (laptop3 == false){
            return laptop1Sound.getStatus();
        }
        return laptop3Sound.getStatus();
    }

    void playLaptop3Sound(){
        laptop3Sound.play();
    }

    void CheckToggleLookingState(Event event, Clock* camTransitionClock){

        if (event.key.code == Keyboard::Space){
            if (event.type == Event::KeyPressed){
                if (!inAnim){
                    toggleLookingState();
                    camTransitionClock->restart();
                    inAnim = true;
                }
            }
        }
    }

    void PostAnimToggle (Office* office, Map* mapa){
        if (office->getLightState()){
            if (isLookingAtCams){
                office->setLightState(false);
            }
        }
        office->setGeneratorUsage(isLookingAtCams);
        mapa->setCameraSprite(currentCam, isLookingAtCams);
    }

    void CheckHoldLight(Event event, Sprite lDoorSpr, Office* office, Vector2i mPos){

        FloatRect tempHitbox = office->getHitbox(2);
        FloatRect movingHitbox = FloatRect(tempHitbox.left + lDoorSpr.getPosition().x, tempHitbox.top, tempHitbox.width, tempHitbox.height);

        if (CheckHover(movingHitbox, mPos)){
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    if (!inAnim){
                        office->setLightState(true);
                        office->setGeneratorUsage(isLookingAtCams);
                    }
                }
            }
        }
        if (office->getLightState()){
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonReleased){
                    office->setLightState(false);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }
    }

    void CheckToggleDoors(Event event, Sprite lDoorSpr, Office* office, Vector2i mPos){

        FloatRect lHitbox = office->getHitbox(0);
        FloatRect rHitbox = office->getHitbox(1);
        FloatRect movingLHitbox = FloatRect(lHitbox.left + lDoorSpr.getPosition().x, lHitbox.top, lHitbox.width, lHitbox.height);
        FloatRect movingRHitbox = FloatRect(rHitbox.left + lDoorSpr.getPosition().x, rHitbox.top, rHitbox.width, rHitbox.height);

        if (CheckHover(movingLHitbox, mPos)){
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonReleased){
                    office->toggleDoorState(0);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }

        if (CheckHover(movingRHitbox, mPos)){
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office->toggleDoorState(1);
                    office->setGeneratorUsage(isLookingAtCams);
                }
            }
        }
    }

    void CheckClickCams(Event event, Map* mapa, Vector2i mPos, Clock* camStaticClock, Animation* camStatic){
        for (int i = 0; i < 10; i++){
            if (CheckHover(mapa->getHitbox(i), mPos)){
                if (event.mouseButton.button == Mouse::Left){
                    if (event.type == Event::MouseButtonPressed){
                        if (mapa->getToggleButtonState() >= 2 && i >= 7){
                            mapa->setMapSprite(i);
                            mapa->setLastCam(1, i);
                            setCurrentCam(mapa->getLastCam(1));
                            click2.play();
                            camStaticClock->restart();
                            camStatic->ManualReset();
                            updateStatic = true;
                        }
                        else if (mapa->getToggleButtonState() < 2 && i < 7){
                            mapa->setMapSprite(i);
                            mapa->setLastCam(0, i);
                            setCurrentCam(mapa->getLastCam(0));
                            click2.play();
                            camStaticClock->restart();
                            camStatic->ManualReset();
                            updateStatic = true;
                        }
                        mapa->setCameraSprite(currentCam, isLookingAtCams);
                    }
                }
            }
        }

        if (CheckHover(mapa->getToggleButtonHitbox(), mPos)){
            if (event.mouseButton.button == Mouse::Left){
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
                    mapa->setCameraSprite(currentCam, isLookingAtCams);
                    click3.play();
                    camStaticClock->restart();
                    camStatic->ManualReset();
                    updateStatic = true;
                }
            }
        }
    }
    void CheckClickMira(Event event, Sprite lDoorSpr, Office* office, Vector2i mPos){

        FloatRect miraHitbox = office->getMiraHitbox();
        FloatRect movingMiraHitbox = FloatRect(miraHitbox.left + lDoorSpr.getPosition().x, miraHitbox.top, miraHitbox.width, miraHitbox.height);

        if (CheckHover(movingMiraHitbox, mPos)){
            if (event.mouseButton.button == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office->PlayMiraSound();
                }
            }
        }
    }

    void Configure(Event event, Sprite lDoorSpr, Office* office, Map* mapa, Vector2i mPos, Clock* camTransitionClock, Clock* camStaticClock, Animation* camStatic){

        if (!office->getDie()){
            CheckToggleLookingState(event, camTransitionClock);
            if (isLookingAtCams && !inAnim){
                CheckClickCams(event, mapa, mPos, camStaticClock, camStatic);
            }
            else{
                CheckHoldLight(event, lDoorSpr, office, mPos);
                CheckToggleDoors(event, lDoorSpr, office, mPos);
                CheckClickMira(event, lDoorSpr, office, mPos);
            }
        }
    }

    void InitConfigure(float volume){
        laptop1Buffer.loadFromFile("audio/FNAUTN_Laptop1.wav");
        laptop1Sound.setBuffer(laptop1Buffer);
        laptop1Sound.setVolume(80 * ((float)volume / 100));

        laptop2Buffer.loadFromFile("audio/FNAUTN_Laptop2.wav");
        laptop2Sound.setBuffer(laptop2Buffer);
        laptop2Sound.setVolume(80 * ((float)volume / 100));

        laptop3Buffer.loadFromFile("audio/FNAUTN_Laptop3.wav");
        laptop3Sound.setBuffer(laptop3Buffer);
        laptop3Sound.setLoop(true);
        laptop3Sound.setVolume(80 * ((float)volume / 100));

        laptop4Buffer.loadFromFile("audio/FNAUTN_Laptop4.wav");
        laptop4Sound.setBuffer(laptop4Buffer);
        laptop4Sound.setVolume(80 * ((float)volume / 100));

        click2Buffer.loadFromFile("audio/FNAUTN_Click2.wav");
        click2.setBuffer(click2Buffer);
        click2.setVolume(20 * ((float)volume / 100));

        click3Buffer.loadFromFile("audio/FNAUTN_Click3.wav");
        click3.setBuffer(click3Buffer);
        click3.setVolume(20 * ((float)volume / 100));
    }
};



#endif // PLAYER_H_INCLUDED
