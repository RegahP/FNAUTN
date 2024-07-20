#ifndef PROFE_H_INCLUDED
#define PROFE_H_INCLUDED

class Profe{

private:

    string profeName;
    int profeID;
    Vector2i currentPos;
    int lastRoom;
    int difficulty;
    float opportunityRate;
    bool attackMode;
    bool reachedOffice;
    bool enteredOffice;

    Profe* globalProfes;
    Room* globalRooms;
    int matrixMap[7][7];
    int validMap[3][3] = {0};

    Clock movementClock;
    float currentTime;

    Clock patienceClock;
    float patienceTimer;
    float leaveTimer;

    bool pickSides;
    int side;
    bool updateDoors;

    bool klosterMode;
    bool dirubeMode;

    SoundBuffer jumpscareBuffer;
    Sound jumpscareSound;

    SoundBuffer matiLeaveBuffer;
    Sound matiLeaveSound;

    SoundBuffer enterOfficeBuffer;
    Sound enterOfficeSound;

    SoundBuffer vastagBuffer;
    Sound vastagSound;

    SoundBuffer matiEnterBuffer;
    Sound matiEnterSound;

    bool playedVastagSound;

    int* filterRooms;
    int filterRoomsSize;
    Vector2i* filterSpots;
    int filterSpotsSize;

    Vector2i* sequence;
    int sequenceSize;

    int posInSeq;

    bool jumpscare;
    int jumpscareID;

    int waitToJumpscare;

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
    bool getKlosterMode(){
        return klosterMode;
    }
    bool getDirubeMode(){
        return dirubeMode;
    }
    bool getEnteredOffice(){
        return enteredOffice;
    }
    int getSide(){
        return side;
    }
    bool getJumpscareState(){
        return jumpscare;
    }
    int getJumpscareID(){
        return jumpscareID;
    }
    bool getUpdateDoors(){
        return updateDoors;
    }
    void resetUpdateDoors(){
        updateDoors = true;
    }
    void setVastagVolume(float vol){
        vastagSound.setVolume(vol);
    }
    void setMatiVolume(float vol){
        matiEnterSound.setVolume(vol);
    }

    void MovementOpportunity(bool* updateCameras, bool* updateWindow, bool playerLookingState, int playerCurrentCam, bool leftDoorState, bool rightDoorState, Clock* drawClock){
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
                        if (posInSeq == sequenceSize){
                            currentPos = Vector2i(7, 0);
                            *updateCameras = true;
                        }
                        if (!reachedOffice){
                            MoveSequenceMaxi(updateWindow);
                        }
                        else{
                            ReachedOffice(updateWindow, rightDoorState, drawClock, Vector2i(4, 1));
                        }
                    }
                    *updateCameras = true;

                }
                else if (profeID == 3){

                    if (!attackMode){
                        MoveRandomAdyacent();
                        if (currentPos == sequence[0]){
                            if (randomNumber(2) == 2){
                                attackMode = true;
                                posInSeq++;
                            }
                        }
                    }
                    else{
                        if (posInSeq == sequenceSize){
                            currentPos = Vector2i(7, 0);
                            *updateCameras = true;
                        }
                        if (!reachedOffice){
                            MoveSequenceVastag(updateWindow);
                        }
                        else{
                            ReachedOffice(updateWindow, leftDoorState, drawClock, Vector2i(6, 2));
                        }
                    }
                    *updateCameras = true;
                }
                else if (!playerLookingState || playerCurrentCam != currentPos.x){
                    if (profeID == 0){
                        if (!reachedOffice){
                            if (currentPos == sequence[sequenceSize-1]){
                                reachedOffice = true;
                                patienceClock.restart();
                                currentPos = Vector2i(7, 0);
                                *updateWindow = true;
                                *updateCameras = true;
                            }
                            MoveSequenceKloster();
                        }
                        else{
                            waitToJumpscare = randomNumber(3) + 4;
                            klosterMode = true;
                        }
                        *updateCameras = true;

                    }
                    else if (profeID == 1){
                        if (!reachedOffice){
                            MoveSequenceMati();
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
            //currentPos = MoveToSpot();
            if (lastRoom == currentPos.x){
               currentPos = MoveToSpot();
            }
        }
        else{
            currentPos = MoveToSpot();
        }
        if (currentPos == Vector2i(6, 3) && !playedVastagSound){
            vastagSound.setVolume(0);
            vastagSound.play();
            playedVastagSound = true;
        }
        else{
            if (playedVastagSound){
                vastagSound.stop();
                playedVastagSound = false;
            }
        }
        cout<<currentPos.x<<", "<<currentPos.y<<endl;
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
            patienceClock.restart();
            reachedOffice = true;
        }
    }

    void MoveSequenceMaxi(bool* updateWindow){

        if (posInSeq == sequenceSize){
            posInSeq = 0;
            reachedOffice = true;
            *updateWindow = true;
        }
        else if (posInSeq < sequenceSize){
            currentPos = sequence[posInSeq];
            posInSeq++;
        }
    }

    void MoveSequenceVastag(bool* updateWindow){

        if (posInSeq == sequenceSize){
            posInSeq = 0;
            reachedOffice = true;
            *updateWindow = true;
        }
        else if (posInSeq < sequenceSize){
            currentPos = sequence[posInSeq];
            posInSeq++;
        }

        cout<<currentPos.x<<", "<<currentPos.y<<endl;
    }
    void TriggerDirubeMode(){
        dirubeMode = true;
        updateDoors = false;
        waitToJumpscare = randomNumber(3) + 4;
        matiEnterSound.play();
        patienceClock.restart();
    }
    void WaitToDirubeMode(){
        if (patienceClock.getElapsedTime().asSeconds() >= 25 - (difficulty / 2) && !dirubeMode){
            TriggerDirubeMode();
        }
    }

    void ReachedOffice(bool* updateWindow, bool doorState, Clock* drawClock, Vector2i resetPos){
        if (!doorState){
          if (profeID == 2){
            Jumpscare(drawClock, 4);
          }
          else{
            Jumpscare(drawClock, 5);
          }
        }
        else{
            reachedOffice = false;
            *updateWindow = true;
            attackMode = false;
            currentPos = resetPos;
        }
    }

    void ReachedOfficeKloster(bool* updateWindow, bool lightState, Clock* drawClock){
        if (patienceTimer < 12 && patienceClock.getElapsedTime().asSeconds() >= 1){
            if (!lightState){
                patienceTimer += 1;
            }
            else{
                if (patienceTimer > 0){
                    patienceTimer -= 1;
                }
            }
            patienceClock.restart();
        }
        if (patienceTimer >= 12){
            reachedOffice = false;

            if (!enteredOffice){
                enterOfficeSound.play();
                *updateWindow = true;
                enteredOffice = true;
            }
            if (patienceClock.getElapsedTime().asSeconds() >= waitToJumpscare){
                    Jumpscare(drawClock, 0);
                    klosterMode = false;

            }
        }
    }

    void ReachedOfficeMati (bool leftDoor, bool rightDoor, bool light, Clock* drawClock){
        if (light && !enteredOffice){
            Jumpscare(drawClock, 3);
            dirubeMode = false;
        }
        if (!pickSides){
            if ((leftDoor && rightDoor) || (!leftDoor && !rightDoor)){
                side = randomNumber(2)-1;
            }
            else{
                if (!leftDoor){
                    side = 0;
                }
                else{
                    side = 1;
                }
            }
            pickSides = true;
        }
        if (patienceClock.getElapsedTime().asSeconds() >= 0.1 && !enteredOffice){
            if (side == 0){
                if (!leftDoor){
                    patienceTimer += 0.1;
                    leaveTimer = 0;
                }
                else{
                    leaveTimer += 0.1;
                }
            }
            else if (side == 1){
                if (!rightDoor){
                    patienceTimer += 0.1;
                    leaveTimer = 0;
                }
                else{
                    leaveTimer += 0.1;
                }
            }
            patienceClock.restart();
        }
        if (patienceTimer >= 4 && !enteredOffice){
            enteredOffice = true;
            updateDoors = false;
            enterOfficeSound.play();
        }
        else if (leaveTimer >= 4){
            patienceTimer = 0;
            leaveTimer = 0;
            reachedOffice = false;
            dirubeMode = false;
            pickSides = false;
            posInSeq = 0;
            currentPos = sequence[posInSeq];
            matiLeaveSound.play();
        }
        if (patienceClock.getElapsedTime().asSeconds() >= waitToJumpscare){
            Jumpscare(drawClock, 2);
            dirubeMode = false;
        }
    }

    void Jumpscare(Clock* drawClock, int jmpscrID){
        movementClock.restart();
        jumpscare = true;
        jumpscareID = jmpscrID;
        jumpscareSound.play();
        drawClock->restart();
    }
    void KlosterJumpscare(Clock* drawClock){
        movementClock.restart();
        jumpscare = true;
        jumpscareID = 1;
        jumpscareBuffer.loadFromFile("audio/FNAUTN_Jumpscare3.wav");
        jumpscareSound.play();
        drawClock->restart();
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
            if (!globalProfes[i].getID() == profeID){
                if (globalProfes[i].getPos() == pos){
                    check = false;
                    return check;
                }
            }
            else{
                if (currentPos == pos){
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

    void Configure(string name, int ID, int initRoom, int initSpot, int diff, float oppRate, Profe profes[], Room rooms[], int mMap[][7], int fRooms[], Vector2i fSpots[], int fRoomsSize, int fSpotsSize, Vector2i seq[], int seqSize, int volume){
        profeName = name;
        profeID = ID;
        currentPos.x = initRoom;
        currentPos.y = initSpot;
        lastRoom = currentPos.x;
        difficulty = diff;
        opportunityRate = oppRate;
        attackMode = false;
        reachedOffice = false;
        enteredOffice = false;
        movementClock.restart();
        currentTime = opportunityRate;

        patienceTimer = 0;
        leaveTimer = 0;
        pickSides = false;
        side = 0;
        updateDoors = true;

        klosterMode = false;
        dirubeMode = false;

        if (profeID == 0 || profeID == 1){
            jumpscareBuffer.loadFromFile("audio/FNAUTN_Jumpscare1.wav");
        }
        else{
           jumpscareBuffer.loadFromFile("audio/FNAUTN_Jumpscare2.wav");
        }
        jumpscareSound.setBuffer(jumpscareBuffer);
        jumpscareSound.setVolume(100 * ((float)volume / 100));

        matiLeaveBuffer.loadFromFile("audio/FNAUTN_Mati2.wav");
        matiLeaveSound.setBuffer(matiLeaveBuffer);
        matiLeaveSound.setVolume(50 * ((float)volume / 100));

        enterOfficeBuffer.loadFromFile("audio/FNAUTN_TriggerEnter.wav");
        enterOfficeSound.setBuffer(enterOfficeBuffer);
        enterOfficeSound.setVolume(20 * ((float)volume / 100));

        vastagBuffer.loadFromFile("audio/FNAUTN_TriggerVastag.wav");
        vastagSound.setBuffer(vastagBuffer);
        vastagSound.setVolume(0);
        vastagSound.setLoop(true);
        playedVastagSound = false;

        matiEnterBuffer.loadFromFile("audio/FNAUTN_Mati1.wav");
        matiEnterSound.setBuffer(matiEnterBuffer);
        matiEnterSound.setVolume(0);

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

        if (profeID == 0){
            posInSeq++;
        }

        jumpscare = false;
        jumpscareID = 0;

        waitToJumpscare = 0;

        cout<<"profe "<<profeID<<": ";
        cout<<currentPos.x<<", ";
        cout<<currentPos.y<<endl;
    }

    void IncreaseProfeDif(){
        difficulty += 1;
    }
};

#endif // PROFE_H_INCLUDED
