#ifndef OFFICE_H_INCLUDED
#define OFFICE_H_INCLUDED

class Office{

private:

    bool roomSpots[5];

    bool leftDoor = false;
    bool rightDoor = false;
    bool light;

    FloatRect leftDoorHitbox = FloatRect(844, 314, 222, 470);
    FloatRect rightDoorHitbox = FloatRect(2534, 314, 222, 470);
    FloatRect lightHitbox = FloatRect(1239, 154, 1122, 427);

    float generatorTemp;
    int generatorUsage;
    int generatorTimer;

    Clock generatorClock;

    Texture* oTex;

public:
    ///GETS GETS GETS GETS GETS GETS GETS GETS GETS GETS GETS GETS
    bool getDoorState(bool ID){
        if (ID == 0){
            return leftDoor;
        }
        return rightDoor;
    }
    bool getLightState(){
        return light;
    }
    FloatRect getHitbox(int ID){
        if (ID == 0){
            return leftDoorHitbox;
        }
        if (ID == 1){
            return rightDoorHitbox;
        }
        if (ID == 2){
            return lightHitbox;
        }
    }
    int getGeneratorTemp(){
        return generatorTemp;
    }
    int getGeneratorUsage(){
        return generatorUsage;
    }
    Clock* getGeneratorClock(){
        return &generatorClock;
    }
    int getGeneratorTimer(){
        return generatorTimer;
    }
    const char* getTextureID(bool profesOffice[4]){
        char textureID[5];
        for (int i = 0; i < 4; i++){
            if (profesOffice[i]){
                textureID[i] = 1;
            }
            else{
                textureID[i] = 0;
            }
        }
        return textureID;
    }
    ///SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
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
        if (light){
            *oTex = SetTexture("equirectangulartest1");
        }
        else{
            *oTex = SetTexture("equirectangulartest");
        }
    }
    void startGenerator(float temp){
        generatorTemp = temp;
        generatorClock.restart();
        generatorTimer = 1;
    }
    void updateGeneratorTemp(float usage){

        if (generatorTemp > 190){
            generatorTemp -= 0.1;
        }
        cout<<generatorTemp<<endl;
        cout<<generatorClock.getElapsedTime().asSeconds()<<endl;
        cout<<usage<<endl<<endl;
        generatorTemp += usage/5;
        generatorTimer += 1;

        //something to do with time
        //usage and temp should be floats?
    }
    void setGeneratorUsage(bool lookingState){
        float usage = 0;
        if (leftDoor){
            usage += 1;
        }
        if (rightDoor){
            usage += 1;
        }
        if (light){
            usage += 2;
        }
        if (lookingState != 0){
            usage += 2;
        }
        generatorUsage = usage;
    }

    void Configure(Texture* tex){
        oTex = tex;
    }
};

#endif // OFFICE_H_INCLUDED
