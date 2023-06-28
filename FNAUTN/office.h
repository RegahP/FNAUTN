#ifndef OFFICE_H_INCLUDED
#define OFFICE_H_INCLUDED

class Office{

private:

    bool leftDoor = false;
    bool rightDoor = false;
    bool light = false;

    FloatRect leftDoorHitbox = FloatRect(844, 314, 222, 470);
    FloatRect rightDoorHitbox = FloatRect(2534, 314, 222, 470);
    FloatRect lightHitbox = FloatRect(1239, 154, 1122, 427);

    float generatorTemp;
    int generatorUsage;
    int generatorTimer;

    Clock generatorClock;

    Texture* ldTex;
    Texture* wnTex;
    Texture* rdTex;

    Profe* globalProfes;

    Font font;
    Text generatorUI;
    bool warning = false;

    Texture usageUI[5];
    Sprite usageSpr;

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
    Text getGeneratorTempUI(){
        return generatorUI;
    }
    Sprite getGeneratorUsageUI(){
        return usageSpr;
    }
    ///SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
    void toggleDoorState(bool ID){
        if (ID == 0){
            leftDoor = !leftDoor;
            if (leftDoor){
                *ldTex = SetTexture("office/L10");
            }
            else{
                *ldTex = SetTexture("office/L00");
            }
        }
        else{
            rightDoor = !rightDoor;
            if (rightDoor){
                *ldTex = SetTexture("office/R10");
            }
            else{
                *ldTex = SetTexture("office/R00");
            }
        }
    }
    void setLightState(bool ID){
        light = ID;
        if (light){
            *wnTex = SetTexture("office/0000");

            int profesReachedOffice[4];
            for(int i = 0; i < 4; i++){
                if (globalProfes[i].getOfficeState()){
                    profesReachedOffice[i] = 1;
                }
                else{
                    profesReachedOffice[i] = 0;
                }
            }
            *wnTex = SetTexture("office/" + getTextureID(profesReachedOffice));

            if (leftDoor){
                *ldTex = SetTexture("office/L11");
            }
            else{
                *ldTex = SetTexture("office/L01");
            }
            if (rightDoor){
                *rdTex = SetTexture("office/R11");
            }
            else{
                *rdTex = SetTexture("office/R01");
            }

        }
        else{
            *wnTex = SetTexture("office/FFFF");

            if (leftDoor){
                *ldTex = SetTexture("office/L10");
            }
            else{
                *ldTex = SetTexture("office/L00");
            }
            if (rightDoor){
                *rdTex = SetTexture("office/R10");
            }
            else{
                *rdTex = SetTexture("office/R00");
            }
        }
    }
    void startGenerator(float temp){
        generatorTemp = temp;
        generatorClock.restart();
        generatorTimer = 1;
    }
    void updateGeneratorTemp(float usage){

        if (generatorTemp > 190){
            generatorTemp -= 0.2;
        }
        else if (generatorTemp < 190){
                generatorTemp = 190;
        }
        if (generatorTemp <= 230){
            generatorTemp += usage/5;
        }
        if(generatorTemp >=220 && !warning){
            generatorUI.setColor(Color::Red);
            warning = true;
        }
        else if(generatorTemp <220){
            generatorUI.setColor(Color::White);
            warning = false;
        }
        generatorTimer += 1;
        generatorUI.setString(to_string((int)generatorTemp)+"°");
    }
    void setGeneratorUsage(bool lookingState){
        float usage = 0;
        if (leftDoor){
            usage += 1;
            cout<<"left door"<<endl;
        }
        if (rightDoor){
            usage += 1;
            cout<<"right door"<<endl;
        }
        if (lookingState != 0){
            usage += 2;
            cout<<"Cameras"<<endl;
        }
        else if (light){
            usage += 2;
            cout<<"lights"<<endl;
        }
        generatorUsage = usage;
        usageSpr.setTexture(usageUI[(int)usage]);
    }

    string getTextureID(int profesReachedOffice[]){

        string textureID = "";

        string bits[4];
        for (int i = 0; i <= 4; i++){
                bits[i] = to_string(profesReachedOffice[i]);
        }
        for (int i = 0; i < 4; i++){
            textureID += bits[i];
        }
        cout<<textureID<<endl;
        return textureID;
    }

    void setUI(Vector2i screen){

        if (!font.loadFromFile("Pixellari.ttf"))
        {
        cout<<"failed to load font"<<endl;
        }
        generatorUI.setFont(font);
        generatorUI.setString(to_string(190)+"°");
        generatorUI.setCharacterSize(48);
        generatorUI.setFillColor(sf::Color::White);
        generatorUI.setPosition(screen.x - generatorUI.getGlobalBounds().width - 30, 20);

        usageUI[0] = SetTexture("textures/usage0");
        usageUI[1] = SetTexture("textures/usage1");
        usageUI[2] = SetTexture("textures/usage2");
        usageUI[3] = SetTexture("textures/usage3");
        usageUI[4] = SetTexture("textures/usage4");

        usageSpr.setTexture(usageUI[0]);
        usageSpr.setScale(4, 4);
        usageSpr.setPosition(screen.x - generatorUI.getGlobalBounds().width * 2 - 20, screen.y - usageSpr.getGlobalBounds().height - 20);
    }

    void Configure(Texture* lDoorTex, Texture* windowTex, Texture* rDoorTex, Profe profes[]){
        ldTex = lDoorTex;
        wnTex = windowTex;
        rdTex = rDoorTex;
        globalProfes = profes;
    }
};

#endif // OFFICE_H_INCLUDED
