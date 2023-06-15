#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
//room = 1a, 2a, 3, 4, 5, 6, 7, 1b, 2b, 8

class Room{

private:

    int ID;
    int spotAmount;
    int adyacentAmount;

public:

    int getID(){
        return ID;
    }
    int getSpotAmount(){
        return spotAmount;
    }
    int getAdyacentAmount(){
        return adyacentAmount;
    }

    const char* getTextureID(Vector2i profesPos[4]){
        char textureID[6];
        textureID[0] = ID;
        for (int i = 0; i < 4; i++){
            if (ID == profesPos[i].x){
                textureID[i+1] = profesPos[i].y;
            }
            else{
                textureID[i+1] = 'f';
            }
        }
        return textureID;

    }
};
/*
    Vector2i profesPos[4];
    for(int i = 0; i < 4; i++){
        profesPos[i] = profes[i].getPos();
    }

    char textureID[6]; //the camID we clicked on (camID)
    strcpy(textureID, Rooms[camID].getTextureID(profesPos));

    string texID;
    for (int i = 0; i < textureID.size(); i++){
        textID.insert(i, 1, textureID[i]);
    }
    Texture tex = SetTexture(texID);
    Sprite sprite.setTexture(tex);
*/

#endif // ROOM_H_INCLUDED
