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
            *pTex = SetTexture("1600x900demo.png");
        }
        else{
            *pTex = SetTexture("equirectangulartest.png");
        }
        ///pTex->update(render.getImage());
    }

    void CheckClickToggle(Event event){

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

    Configure(Event event, Texture* tex){
        pTex = tex;
        CheckClickToggle(event);
    }

};



#endif // PLAYER_H_INCLUDED
