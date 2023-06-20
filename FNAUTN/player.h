#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{

private:
    bool isLookingAtCams;
    int currentCam;

    Render render;
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

        ///pTex->update(render.getImage());
    }

    void CheckToggleLookingState(Event event){

    switch(event.type){
        case Event::MouseButtonPressed:{
            switch(event.key.code){
                case Mouse::Left:
                    toggleLookingState();
                break;
                }
            break;
            }
        break;
        }
    }

    void CheckHoldLight(Event event, Office office, Vector2i mPos){

        if (CheckHover(FloatRect(1239, 154, 1122, 427), mPos)){
            if (event.key.code == Mouse::Left){
                if (event.type == Event::MouseButtonPressed){
                    office.setLightState(true);
                }
                if (event.type == Event::MouseButtonReleased){
                    office.setLightState(false);
                }
            }
        }
    }

    void Configure(Event event, Texture* tex, Office office, Vector2i mPos){
        pTex = tex;
        //CheckToggleLookingState(event);
        CheckHoldLight(event, office, mPos);
    }

};



#endif // PLAYER_H_INCLUDED
