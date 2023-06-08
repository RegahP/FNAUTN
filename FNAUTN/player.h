#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{
public:
    bool lookingAtCams;
    int currentCam;

    bool leftDoorClosed;
    bool rightDoorClosed;
    bool lightOn;
    bool lightOnCheck;

    Texture tempTexture;

    int generatorTemp;
    int generatorUsage;

    Texture camHoverButton;
    Sprite camHoverButtonSprite;

public:
    void CheckCams(Vector2i mPos, Event event){
        lookingAtCams = CheckSpaceToggle(lookingAtCams, event);
    }

    void CheckLight(Event event){
        lightOn = CheckClickToggle(lightOn, event);

        if (lightOnCheck != lightOn){
            if (lightOn == true){
                tempTexture = SetTexture("equirectangulartest.png");
            }
            else{
                tempTexture = SetTexture("equirectangulartest1.png");
            }
        }
        lightOnCheck = lightOn;
    }

    Sprite DrawCamButton(){
    camHoverButton = SetTexture("camHoverButton.png");
    camHoverButtonSprite.setTexture(camHoverButton);
    return camHoverButtonSprite;
    }
};

#endif // PLAYER_H_INCLUDED
