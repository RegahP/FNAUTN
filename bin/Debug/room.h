#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED
//room =      {1a, 2a, 3, 4, 5, 6, 7, 1b, 2b, 8}

//roomID =    {0,  1,  2, 3, 4, 5, 6,  7,  8, 9}
//roomspots = {7,  5,  2, 3, 5, 2, 3,  4,  3, 3}
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
        return textureID;
    }

    void Configure(int ID, int spotAmt, int adyacentAmt){
        roomID = ID;
        spotAmount = spotAmt;
        adyacentAmount = adyacentAmt;
    }
};

#endif // ROOM_H_INCLUDED
