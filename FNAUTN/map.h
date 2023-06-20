#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class Map{

private:

    Texture cams[10];
    Sprite mapSprite;
    FloatRect hitboxes[10];

    int lastCamOnPB = 0;
    int lastCamOnP1 = 7;

    Texture toggleButtonTextures[4];
    Sprite toggleButtonSprite;
    FloatRect toggleButtonHitbox;
    int toggleButtonState = 0;

public:
    FloatRect getHitbox(int ID){
        return hitboxes[ID];
    }
    int getLastCam(bool floor){
        if (floor == 0){
            return lastCamOnPB;
        }
        return lastCamOnP1;
    }
    FloatRect getToggleButtonHitbox(){
        return toggleButtonHitbox;
    }
    Sprite getSprite(){
        return mapSprite;
    }
    Sprite getToggleButton(){
        return toggleButtonSprite;
    }
    int getToggleButtonState(){
        return toggleButtonState;
    }
    void setMapSprite(int ID){
        mapSprite.setTexture(cams[ID]);
    }
    void setLastCam(bool floor, int ID){
        if (floor == 0){
            lastCamOnPB = ID;
        }
        else{
            lastCamOnP1 = ID;
        }
    }
    void ToggleButton(){
        if (toggleButtonState == 1){
            toggleButtonSprite.setTexture(toggleButtonTextures[2]);
            toggleButtonState = 2;
            setMapSprite(lastCamOnP1);
        }
        else if (toggleButtonState == 3){
            toggleButtonSprite.setTexture(toggleButtonTextures[0]);
            toggleButtonState = 0;
            setMapSprite(lastCamOnPB);
        }
    }
    void HightlightButton(){
        if (toggleButtonState == 0){
            toggleButtonSprite.setTexture(toggleButtonTextures[3]);
            toggleButtonState = 1;
        }
        else if (toggleButtonState == 2){
            toggleButtonSprite.setTexture(toggleButtonTextures[1]);
            toggleButtonState = 3;
        }
    }
    void setScale(int scale){
        mapSprite.setScale(scale, scale);
        toggleButtonSprite.setScale(scale, scale);
        for (int i = 0; i < 10; i++){
            hitboxes[i].left *= scale;
            hitboxes[i].top *= scale;
            hitboxes[i].width *= scale;
            hitboxes[i].height *= scale;
        }
        toggleButtonHitbox.left *= scale;
        toggleButtonHitbox.top *= scale;
        toggleButtonHitbox.width *= scale;
        toggleButtonHitbox.height *= scale;
    }
    void setPosition(Vector2i pos){

        mapSprite.setPosition(pos.x, pos.y);
        toggleButtonSprite.setPosition(pos.x, pos.y);
        for (int i = 0; i < 10; i++){
            hitboxes[i].left += pos.x;
            hitboxes[i].top += pos.y;
        }
        toggleButtonHitbox.left += pos.x;
        toggleButtonHitbox.top += pos.y;
    }

    Map(){
        cams[0] = SetTexture("textures/1a.png");
        cams[1] = SetTexture("textures/2a.png");
        cams[2] = SetTexture("textures/3.png");
        cams[3] = SetTexture("textures/4.png");
        cams[4] = SetTexture("textures/5.png");
        cams[5] = SetTexture("textures/6.png");
        cams[6] = SetTexture("textures/7.png");
        cams[7] = SetTexture("textures/1b.png");
        cams[8] = SetTexture("textures/2b.png");
        cams[9] = SetTexture("textures/8.png");

        toggleButtonTextures[0] = SetTexture("textures/baja.png");
        toggleButtonTextures[1] = SetTexture("textures/bajaHold.png");
        toggleButtonTextures[2] = SetTexture("textures/alta.png");
        toggleButtonTextures[3] = SetTexture("textures/altaHold.png");

        hitboxes[0] = FloatRect(323, 120, 23, 17);
        hitboxes[1] = FloatRect(129, 66, 23, 17);
        hitboxes[2] = FloatRect(123, 46, 23, 17);
        hitboxes[3] = FloatRect(28, 116, 23, 17);
        hitboxes[4] = FloatRect(2, 146, 23, 17);
        hitboxes[5] = FloatRect(77, 165, 23, 17);
        hitboxes[6] = FloatRect(222, 6, 23, 17);
        hitboxes[7] = FloatRect(221, 71, 23, 17);
        hitboxes[8] = FloatRect(337, 57, 23, 17);
        hitboxes[9] = FloatRect(358, 90, 23, 17);

        toggleButtonHitbox = FloatRect(129, 111, 78, 34);

        setMapSprite(0);
        toggleButtonSprite.setTexture(toggleButtonTextures[0]);
        setScale(2);
        setPosition(Vector2i(50, 50));
    }
};

#endif // MAP_H_INCLUDED
