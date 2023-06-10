#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player{
private:
    bool isLookingAtCams;
    int currentCam;

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
    }

};

class Office{
private:
    bool leftDoor;
    bool rightDoor;
    bool light;

    int generatorTemp;
    int generatorUsage;

public:
    /*
    bool getDoorState(bool ID);
    bool getLightState();
    int getGeneratorTemp();
    int getGeneratorUsage();

    void toggleDoorState(bool ID);
    void setLightState();
    void startGeneratorTemp(int temp);
    void updateGeneratorTemp(int usage);
    void setGeneratorUsage(int currentCam);
    */
    bool getDoorState(bool ID){
        if (ID == 0){
            return leftDoor;
        }
        return rightDoor;
    }
    bool getLightState(){
        return light;
    }
    int getGeneratorTemp(){
        return generatorTemp;
    }
    int getGeneratorUsage(){
        return generatorUsage;
    }

    void toggleDoorState(bool ID){
        if (ID == 0){
            leftDoor = !leftDoor;
        }
        else{
            rightDoor = !rightDoor;
        }
    }
    void setLightState(bool ID){
        light = ID;
    }
    void startGeneratorTemp(int temp){
        generatorTemp = temp;
    }
    void updateGeneratorTemp(int usage){
        generatorTemp -= 0.1;
        generatorTemp += usage;
        //something to do with time
        //usage and temp should be floats?
    }
    void setGeneratorUsage(int currentCam){
        int usage = 0;
        if (leftDoor){
            usage += 1;
        }
        if (rightDoor){
            usage += 1;
        }
        if (light){
            usage += 2;
        }
        if (currentCam != 0){
            usage += 1;
        }
        generatorUsage = usage;
    }
};

#endif // PLAYER_H_INCLUDED
