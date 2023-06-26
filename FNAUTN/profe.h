#ifndef PROFE_H_INCLUDED
#define PROFE_H_INCLUDED

class Profe{

private:

    int profeID;
    Vector2i currentPos;
    int lastRoom;
    int difficulty;
    float opportunityRate;
    bool attackMode;
    bool reachedOffice;

    Profe* globalProfes;
    Room* globalRooms;
    int matrixMap[7][7];
    int validMap[3][3] = {0};

    Clock profeClock;
    float currentTime;

    int* filterRooms;
    int filterRoomsSize;
    Vector2i* filterSpots;
    int filterSpotsSize;

public:
    Vector2i getPos(){
        return currentPos;
    }
    int getID(){
        return profeID;
    }
    int getLastRoom(){
        return lastRoom;
    }

    void MovementOpportunity(bool* updateCameras){
        if (profeClock.getElapsedTime().asSeconds() >= currentTime){
            int randNum = randomNumber(20);
            cout<<"tried to move "<<randNum<<endl;
            if (randNum <= difficulty){
                Move();
                *updateCameras = true;
            }
            else{
                cout<<"lol"<<endl<<endl;
            }
            currentTime += opportunityRate;
        }
    }

    void Move(){
        Vector2i posInMatrix = getPositionInMatrix();
        setValidMap(posInMatrix);
        for (int x = 0; x < 3; x++){
            for (int y = 0; y < 3; y++){
                cout<<to_string(validMap[x][y])+" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<currentPos.x<<", ";
        cout<<currentPos.y<<endl<<endl;

        int chooseMoveType = randomNumber(2);
        cout<<"chose move type "<<chooseMoveType<<endl;
        if (chooseMoveType == 1){
            lastRoom = currentPos.x;
            //currentPos = MoveToRoom();
            currentPos = MoveToSpot();
        }
        else{
            currentPos = MoveToSpot();
        }
    }

    Vector2i MoveToRoom(){
        resetValidMap();
        Vector2i posInMatrix = getPositionInMatrix();
        setValidMap(posInMatrix);

        int adyacentAmount = globalRooms[currentPos.x].getAdyacentAmount();
        bool roomCheck = false;
        int roomFound = 0;
        while (!roomCheck){

            int randNumRoom = randomNumber(adyacentAmount);
            cout<<"checking rand num room "<<randNumRoom<<endl;
            int searchNumRoom = 0;

            for (int x = 0; x < 3; x++){
                for (int y = 0; y < 3; y++){
                    if (validMap[x][y] != 0){
                        searchNumRoom++;
                        if (searchNumRoom == randNumRoom){
                            roomCheck = filterRoomsCheck(validMap[x][y]);
                            if (roomCheck){
                                roomFound = validMap[x][y] - 1;
                            }
                        }
                    }
                }
            }
        }
        int spotAmount = globalRooms[roomFound].getSpotAmount();
        bool spotCheck = false;
        int spotFound = 0;
        while (!spotCheck){

            int randNumSpot = randomNumber(spotAmount);
            cout<<"checking rand num spot "<<randNumSpot<<endl;
            spotCheck = filterSpotsCheck(Vector2i(roomFound, randNumSpot));
            if (spotCheck){
                spotFound = randNumSpot;
            }
        }
        return Vector2i(roomFound, spotFound);
    }

    Vector2i MoveToSpot(){
        int spotAmount = globalRooms[currentPos.x].getSpotAmount();
        bool spotCheck = false;
        int spotFound = 0;
        while (!spotCheck){

            int randNumSpot = randomNumber(spotAmount);
            cout<<"checking rand num spot "<<randNumSpot<<endl;
            spotCheck = filterSpotsCheck(Vector2i(currentPos.x, randNumSpot));
            if (spotCheck){
                spotFound = randNumSpot;
            }
        }
        return Vector2i(currentPos.x, spotFound);
    }

    bool filterRoomsCheck(int roomID){
        bool check = false;
        for (int i = 0; i < filterRoomsSize; i++){
            if (roomID != filterRooms[i]){
                check = true;
            }
            else{
                check = false;
            }
        }
        return check;
    }

    bool filterSpotsCheck(Vector2i pos){
        bool check = true;
        for (int i = 0; i < filterSpotsSize; i++){
            if (pos.x == filterSpots[i].x){
                if (pos.y == filterSpots[i].y){
                    check = false;
                    return check;
                }
            }
        }
        return check;
    }

    Vector2i getPositionInMatrix (){
        int num = currentPos.x + 1;
        for (int x = 0; x < 7; x++){
            for (int y = 0; y < 7; y++){
                if (matrixMap[x][y] == num){
                    Vector2i posInMatrix(x, y);
                    return posInMatrix;
                }
            }
        }
    }

    void setValidMap(Vector2i posInMatrix){
        int xOffset = posInMatrix.x - 1;
        int xEnd = posInMatrix.x + 1;
        int yOffset = posInMatrix.y - 1;
        int yEnd = posInMatrix.y + 1;
        for (int x = xOffset; x <= xEnd; x++){
            for (int y = yOffset; y <= yEnd; y++){
                if (x != posInMatrix.x || y != posInMatrix.y){


                    if (matrixMap[x][y] == -1){
                        if(posInMatrix.x == x){
                            if( y > posInMatrix.y){
                                validMap[x - xOffset][y - yOffset] = matrixMap[x][y+1];
                            }
                            else{
                                validMap[x - xOffset][y - yOffset] = matrixMap[x][y-1];
                            }
                        }
                        if(posInMatrix.y == y){
                            if( x > posInMatrix.x){
                                validMap[x - xOffset][y - yOffset] = matrixMap[x+1][y];
                            }
                            else{
                                validMap[x - xOffset][y - yOffset] = matrixMap[x-1][y];
                            }
                        }
                    }
                    else if (matrixMap[x][y] == -2){
                        if (currentPos.x + 1 == 2){
                            validMap[x - xOffset][y - yOffset] = 5;
                        }
                        else if(currentPos.x + 1 == 5){
                            validMap[x - xOffset][y - yOffset] = 2;
                        }

                    }
                    else{
                        validMap[x - xOffset][y - yOffset] = matrixMap[x][y];
                    }
                }
            }
        }
    }

    void resetValidMap(){
        for(int x = 0; x < 3; x++){
            for (int y = 0; y < 3; y++){
                validMap[x][y] = 0;
            }
        }
    }

    void Configure(int ID, int initRoom, int initSpot, int diff, float oppRate, Profe profes[], Room rooms[], int mMap[][7], int fRooms[], Vector2i fSpots[], int fRoomsSize, int fSpotsSize){
        currentPos.x = initRoom;
        currentPos.y = initSpot;
        lastRoom = currentPos.x;
        difficulty = diff;
        opportunityRate = oppRate;
        profeClock.restart();
        currentTime = opportunityRate;

        globalProfes = profes;
        globalRooms = rooms;

        filterRooms = fRooms;
        filterRoomsSize = fRoomsSize;
        filterSpots = fSpots;
        filterSpotsSize = fSpotsSize;

        for (int x = 0; x < 7; x++){
            for (int y = 0; y < 7; y++){
                matrixMap[x][y] = mMap[x][y];
                cout<<matrixMap[x][y]<<" ";
                if (y == 6){
                    cout<<endl;
                }
            }
        }
        cout<<endl;
    }
};

#endif // PROFE_H_INCLUDED
