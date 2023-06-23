#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
//room =      {1a, 2a, 3, 4, 5, 6, 7, 1b, 2b, 8}

//roomID =    {0,  1,  2, 3, 4, 5, 6,  7,  8, 9}
//roomspots = {11, 5,  2, 3, 5, 2, 3,  3,  2, 3}
//adycrooms = {4,  4,  1, 1, 1, 1, 1,  1,  1, 1}

class Room{

private:

    int roomID;
    int spotAmount;
    int adyacentAmount;

public:

    int getID(){
        return roomID;
    }
    int getSpotAmount(){
        return spotAmount;
    }
    int getAdyacentAmount(){
        return adyacentAmount;
    }

    string getTextureID(Vector2i profesPos[]){

        string textureID = "";

        string bits[5];
        bits[0] = to_string(roomID);

        for (int i = 1; i <= 4; i++){
            if (roomID == profesPos[i-1].x){
                bits[i] = to_string(profesPos[i-1].y);
            }
            else{
                bits[i] = "0";
            }
        }
        for (int i = 0; i < 5; i++){
            textureID += bits[i];
        }

        cout<<textureID<<endl;
        return textureID;

    }

    void Configure(int ID, int spotAmt, int adyacentAmt){
        roomID = ID;
        spotAmount = spotAmt;
        adyacentAmount = adyacentAmt;
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
