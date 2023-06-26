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

    Texture* ldTex;
    Texture* wnTex;
    Texture* rdTex;

    Font font;
    Text generatorUI;

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
            *wnTex = SetTexture("office/00000");
            //CALCULAR EL TEXTURE ID PARA LA VENTANA
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
            *wnTex = SetTexture("office/FFFFF");

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
            generatorTemp -= 0.1;
        }
        else if (generatorTemp < 190){
                generatorTemp = 190;
        }
        //cout<<generatorTemp<<endl;
        //cout<<generatorClock.getElapsedTime().asSeconds()<<endl;
        //cout<<usage<<endl<<endl;
        generatorTemp += usage/5;
        generatorTimer += 1;
        generatorUI.setString(to_string((int)generatorTemp)+"°");
    }
    void setGeneratorUsage(bool lookingState){
        float usage = 0;
        if (leftDoor){
            usage += 1;
        }
        if (rightDoor){
            usage += 1;
        }
        if (lookingState != 0){
            usage += 2;
        }
        else if (light){
            usage += 2;
        }
        generatorUsage = usage;
        usageSpr.setTexture(usageUI[(int)usage]);
    }
    void setUI(Vector2i screen){

        if (!font.loadFromFile("Pixellari.ttf"))
        {
        cout<<"failed to load font"<<endl;
        }
        generatorUI.setFont(font); // font is a sf::Font
        generatorUI.setString(to_string(190)+"°");
        generatorUI.setCharacterSize(48); // in pixels, not points!
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

    void Configure(Texture* lDoorTex, Texture* windowTex, Texture* rDoorTex){
        ldTex = lDoorTex;
        wnTex = windowTex;
        rdTex = rDoorTex;
    }
};

#endif // OFFICE_H_INCLUDED
