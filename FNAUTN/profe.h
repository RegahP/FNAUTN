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

    Clock movementClock;
    float currentTime;

    Clock patienceClock;
    Clock exposureClock;


    int* filterRooms;
    int filterRoomsSize;
    Vector2i* filterSpots;
    int filterSpotsSize;

    Vector2i* sequence;
    int sequenceSize;

    int posInSeq;

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
    bool getOfficeState(){
        return reachedOffice;
    }

    void MovementOpportunity(bool* updateCameras, bool playerLookingState, int playerCurrentCam){
        if (movementClock.getElapsedTime().asSeconds() >= currentTime){
            int randNum = randomNumber(20);
            if (randNum <= difficulty){
                if (profeID == 2){
                    if (!attackMode){
                        MoveRandomAdyacent();
                        if (currentPos == sequence[0]){
                            attackMode = true;
                            posInSeq++;
                        }
                    }
                    else{
                        if (!reachedOffice){
                            MoveSequenceMaxi();
                        }
                        else{
                            ReachedOffice();
                            reachedOffice = false;
                            attackMode = false;
                            currentPos = Vector2i(4, 1);
                        }
                    }
                    *updateCameras = true;

                }
                else if (profeID == 3){

                    if (!attackMode){

                        MoveRandomAdyacent();
                        if (currentPos == sequence[0]){
                            if (randomNumber(2) == 2){
                            }
                            attackMode = true;
                            posInSeq++;
                        }
                    }
                    else{
                        if (!reachedOffice){
                            MoveSequenceVastag();
                        }
                        else{
                            ReachedOffice();
                            reachedOffice = false;
                            attackMode = false;
                            currentPos = Vector2i(6, 2);
                        }
                    }
                    *updateCameras = true;
                }
                else if (!playerLookingState || playerCurrentCam != currentPos.x){
                    if (profeID == 0){
                        if (!reachedOffice){
                            MoveSequenceKloster();
                            if (currentPos == sequence[sequenceSize-1]){
                                reachedOffice = true;
                            }
                        }
                        else{
                            ReachedOffice();
                        }
                        *updateCameras = true;

                    }
                    else if (profeID == 1){
                        if (!reachedOffice){
                            MoveSequenceMati();
                        }
                        else{
                            ReachedOffice();
                            reachedOffice = false;
                        }
                        *updateCameras = true;
                    }
                }
            }
            currentTime += opportunityRate;
        }
    }

    void MoveRandomAdyacent(){
        Vector2i posInMatrix = getPositionInMatrix();
        setValidMap(posInMatrix);

        int chooseMoveType = randomNumber(2);
        if (chooseMoveType == 1){
            lastRoom = currentPos.x;
            currentPos = MoveToRoom();
            if (lastRoom == currentPos.x){
               currentPos = MoveToSpot();
            }
        }
        else{
            currentPos = MoveToSpot();
        }
    }

    void MoveSequenceKloster(){
        bool check = false;
        if (posInSeq < sequenceSize){
            check = occupiedCheck(sequence[posInSeq]);
            if (check){
                currentPos = sequence[posInSeq];
                posInSeq++;
            }
        }
    }

    void MoveSequenceMati(){

        if (posInSeq < sequenceSize){
            currentPos = sequence[posInSeq];
            posInSeq++;
        }
        if (posInSeq == sequenceSize){
            posInSeq = -1;
            reachedOffice = true;
        }
        if (posInSeq == -1){
            posInSeq = 0;
        }
    }

    void MoveSequenceMaxi(){

        if (posInSeq < sequenceSize){
            currentPos = sequence[posInSeq];
            posInSeq++;
        }
        if (posInSeq == sequenceSize){
            posInSeq = 0;
            reachedOffice = true;
        }
    }

    void MoveSequenceVastag(){

        if (posInSeq < sequenceSize){
            currentPos = sequence[posInSeq];
            posInSeq++;
        }
        if (posInSeq == sequenceSize){
            posInSeq = 0;
            reachedOffice = true;
        }
    }


    void ReachedOffice(){

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
            int searchNumRoom = 0;

            for (int x = 0; x < 3; x++){
                for (int y = 0; y < 3; y++){
                    if (validMap[x][y] != 0){
                        searchNumRoom++;
                        if (searchNumRoom == randNumRoom){
                            roomCheck = filterRoomsCheck(validMap[x][y] - 1);
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
        bool ocupCheck = false;
        int spotFound = 0;
        int nonAvailableSpots = 0;
        while (!spotCheck && !ocupCheck){

            int randNumSpot = randomNumber(spotAmount);
            spotCheck = filterSpotsCheck(Vector2i(roomFound, randNumSpot));
            if (spotCheck){
                ocupCheck = occupiedCheck(Vector2i(roomFound, randNumSpot));
                if (ocupCheck){
                   spotFound = randNumSpot;
                }
                else{
                    spotCheck = false;
                    nonAvailableSpots++;
                    if (nonAvailableSpots == spotAmount){
                        roomFound = currentPos.x;
                        spotFound = currentPos.y;
                        spotCheck = true;
                        ocupCheck = true;
                    }
                }
            }
        }
        return Vector2i(roomFound, spotFound);
    }

    Vector2i MoveToSpot(){
        int spotAmount = globalRooms[currentPos.x].getSpotAmount();
        bool spotCheck = false;
        bool ocupCheck = false;
        int spotFound = 0;
        while (!spotCheck && !ocupCheck){

            int randNumSpot = randomNumber(spotAmount);
            spotCheck = filterSpotsCheck(Vector2i(currentPos.x, randNumSpot));
            if (spotCheck){
                ocupCheck = occupiedCheck(Vector2i(currentPos.x, randNumSpot));
                if (ocupCheck){
                   spotFound = randNumSpot;
                }
                else{
                    spotCheck = false;
                }
            }
        }
        return Vector2i(currentPos.x, spotFound);
    }

    bool occupiedCheck(Vector2i pos){
        bool check = true;
        for (int i = 0; i < 4; i++){
            if (globalProfes[i].getID() != profeID){
                if (globalProfes[i].getPos() == pos){
                    check = false;
                    return check;
                }
            }
        }
        return check;
    }

    bool filterRoomsCheck(int roomID){
        bool check = true;
        for (int i = 0; i < filterRoomsSize; i++){
            if (roomID == filterRooms[i]){
                check = false;
                return check;
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
                        //validMap[x - xOffset][y - yOffset] = 0;
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

    void Configure(int ID, int initRoom, int initSpot, int diff, float oppRate, Profe profes[], Room rooms[], int mMap[][7], int fRooms[], Vector2i fSpots[], int fRoomsSize, int fSpotsSize, Vector2i seq[], int seqSize){
        profeID = ID;
        currentPos.x = initRoom;
        currentPos.y = initSpot;
        lastRoom = currentPos.x;
        difficulty = diff;
        opportunityRate = oppRate;
        attackMode = false;
        reachedOffice = false;
        movementClock.restart();
        currentTime = opportunityRate;

        globalProfes = profes;
        globalRooms = rooms;

        for (int x = 0; x < 7; x++){
            for (int y = 0; y < 7; y++){
                matrixMap[x][y] = mMap[x][y];
            }
        }

        filterRooms = fRooms;
        filterRoomsSize = fRoomsSize;
        filterSpots = fSpots;
        filterSpotsSize = fSpotsSize;

        sequence = seq;
        sequenceSize = seqSize;

        posInSeq = 0;

        cout<<"profe "<<profeID<<": ";
        cout<<currentPos.x<<", ";
        cout<<currentPos.y<<endl;
    }
};

#endif // PROFE_H_INCLUDED
