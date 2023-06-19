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

        if (isLookingAtCams){
            *pTex = SetTexture("equirectangulartest1.png");
        }
        else{
            *pTex = SetTexture("equirectangulartest.png");
        }
        ///pTex->update(render.getImage());
    }

    void CheckToggleLookingState(Event event, void(Player::*func)(), Player player){

    switch(event.type){
        case Event::MouseButtonPressed:{
            switch(event.key.code){
                case Mouse::Left:
                    //toggleLookingState();
                    player->*func();
                break;
                }
            break;
            }
        break;
        }
    }

    void Configure(Event event, Texture* tex, Player player){
        pTex = tex;
        CheckToggleLookingState(event, &Player::toggleLookingState, player);
    }

};



#endif // PLAYER_H_INCLUDED
