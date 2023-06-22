#ifndef OFFICE_H_INCLUDED
#define OFFICE_H_INCLUDED

class Office{

private:

    bool roomSpots[5];

    bool leftDoor;
    bool rightDoor;
    bool light;

    FloatRect leftDoorHitbox = FloatRect(844, 314, 222, 470);
    FloatRect rightDoorHitbox = FloatRect(2534, 314, 222, 470);
    FloatRect lightHitbox = FloatRect(1239, 154, 1122, 427);

    int generatorTemp;
    int generatorUsage;

    Texture* oTex;

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

    void Configure(Texture* tex){
        oTex = tex;
    }
};

/*
    bool profesOffice[4];
    for(int i = 0; i < 4; i++){
        profesOffice[i] = profes[i].getOfficeState();
    }

    char textureID[5];
    strcpy(textureID, Office.getTextureID(profesOffice));

    string texID;
    for (int i = 0; i < textureID.size(); i++){
        textID.insert(i, 1, textureID[i]);
    }
    Texture tex = SetTexture(texID);
    Sprite sprite.setTexture(tex);
*/

#endif // OFFICE_H_INCLUDED
