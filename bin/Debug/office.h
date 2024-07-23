#ifndef OFFICE_H_INCLUDED
#define OFFICE_H_INCLUDED

class Office{

private:

    bool leftDoor = false;
    bool rightDoor = false;
    bool light = false;

    FloatRect leftDoorHitbox;
    FloatRect rightDoorHitbox;
    FloatRect lightHitbox;

    FloatRect miraHitbox;

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
    bool warning;
    bool stoppedAlarm;

    Texture usageUI[5];
    Sprite usageSpr;

    SoundBuffer alarmBuffer;
    Sound alarmSound;

    SoundBuffer generatorBuffer;
    Sound generatorSound;

    SoundBuffer miraBuffer;
    Sound miraSound;

    SoundBuffer door1Buffer;
    Sound door1Sound;

    SoundBuffer door2Buffer;
    Sound door2Sound;

    SoundBuffer light1Buffer;
    Sound light1Sound;

    SoundBuffer light2Buffer;
    Sound light2Sound;

    SoundBuffer light3Buffer;
    Sound light3Sound;

    bool die;
    bool shutOff;

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
    FloatRect getMiraHitbox(){
        return miraHitbox;
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
    bool getDie(){
        return die;
    }
    ///SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS SETS
    void toggleDoorState(bool ID){
        if (ID == 0){
            leftDoor = !leftDoor;
            if (leftDoor){
                *ldTex = SetTexture("office/L10");
                door2Sound.play();
            }
            else{
                door1Sound.play();
                if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                    if (!globalProfes[1].getSide()){
                        *ldTex = SetTexture("office/L00M");
                    }
                    else{
                        *ldTex = SetTexture("office/L00");
                    }
                }
                else{
                    *ldTex = SetTexture("office/L00");
                }
            }
        }
        else{
            rightDoor = !rightDoor;
            if (rightDoor){
                *rdTex = SetTexture("office/R10");
                door2Sound.play();
            }
            else{
                door1Sound.play();
                if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                    if (globalProfes[1].getSide()){
                        *rdTex = SetTexture("office/R00M");
                    }
                    else{
                    *rdTex = SetTexture("office/R00");
                    }
                }
                else{
                    *rdTex = SetTexture("office/R00");
                }
            }
        }
    }
    void updateLeftDoor(){
        if (leftDoor){
            *ldTex = SetTexture("office/L10");
        }
        else{
            if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                if (!globalProfes[1].getSide()){
                    *ldTex = SetTexture("office/L00M");
                }
                else{
                    *ldTex = SetTexture("office/L00");
                }
            }
            else{
                *ldTex = SetTexture("office/L00");
            }
        }
    }
    void updateRightDoor(){
        if (rightDoor){
            *rdTex = SetTexture("office/R10");
        }
        else{
            if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                if (globalProfes[1].getSide()){
                    *rdTex = SetTexture("office/R00M");
                }
                else{
                    *rdTex = SetTexture("office/R00");
                }
            }
            else{
                *rdTex = SetTexture("office/R00");
            }
        }
    }
    void setLightState(bool ID, bool playSound = true){
        light = ID;
        if (light){
            if (playSound){
                light1Sound.play();
                light3Sound.play();
            }
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
            if (playSound){
                light2Sound.play();
                light3Sound.stop();
            }
            *wnTex = SetTexture("office/FFFF");

            if (leftDoor){
                *ldTex = SetTexture("office/L10");
            }
            else{
                if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                    if (!globalProfes[1].getSide()){
                        *ldTex = SetTexture("office/L00M");
                    }
                    else{
                        *ldTex = SetTexture("office/L00");
                    }
                }
                else{
                  *ldTex = SetTexture("office/L00");
                }
            }
            if (rightDoor){
                *rdTex = SetTexture("office/R10");
            }
            else{
                if (globalProfes[1].getDirubeMode() && !globalProfes[1].getEnteredOffice()){
                    if (globalProfes[1].getSide()){
                        *rdTex = SetTexture("office/R00M");
                    }
                    else{
                        *rdTex = SetTexture("office/R00");
                    }
                }
                else{
                    *rdTex = SetTexture("office/R00");
                }
            }
        }
    }
    void updateWindow(){
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
    void ShutOff(){
        if (!shutOff){
            setLightState(false);
            *ldTex = SetTexture("office/LDIE");
            *wnTex = SetTexture("office/WDIE");
            *rdTex = SetTexture("office/RDIE");
            shutOff = true;
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
            generatorUI.setColor(Color(172, 50, 50));
            alarmSound.setLoop(true);
            alarmSound.play();
            warning = true;
        }
        else if(generatorTemp <220){
            generatorUI.setColor(Color::White);
            alarmSound.stop();
            warning = false;
        }
        if (generatorTemp >= 230 && !die){
            generatorClock.restart();
            alarmSound.stop();
            generatorSound.play();
            die = true;
        }
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
    void StopAlarm(){
        if (!stoppedAlarm){
            alarmSound.stop();
            stoppedAlarm = true;
        }
    }
    void PlayMiraSound(){
        miraSound.play();
    }

    void Configure(Texture* lDoorTex, Texture* windowTex, Texture* rDoorTex, Profe profes[], Font ft, Vector2f scale, float volume){
        ldTex = lDoorTex;
        wnTex = windowTex;
        rdTex = rDoorTex;
        globalProfes = profes;

        rightDoorHitbox = FloatRect(2534 * scale.x, 314 * scale.y, 222 * scale.x, 470 * scale.y);
        leftDoorHitbox = FloatRect(844 * scale.x, 314 * scale.y, 222 * scale.x, 470 * scale.y);
        lightHitbox = FloatRect(1239 * scale.x, 154 * scale.y, 1122 * scale.x, 427 * scale.y);

        miraHitbox = FloatRect(2260 * scale.x, 637 * scale.y, 20 * scale.x, 15 * scale.y);

        font = ft;

        alarmBuffer.loadFromFile("audio/FNAUTN_Alarm.wav");
        alarmSound.setBuffer(alarmBuffer);
        alarmSound.setVolume(75 * ((float)volume / 100));

        generatorBuffer.loadFromFile("audio/FNAUTN_Generator.wav");
        generatorSound.setBuffer(generatorBuffer);
        generatorSound.setVolume(75 * ((float)volume / 100));

        miraBuffer.loadFromFile("audio/FNAUTN_Mira.wav");
        miraSound.setBuffer(miraBuffer);
        miraSound.setVolume(15 * ((float)volume / 100));

        door1Buffer.loadFromFile("audio/FNAUTN_Door1.wav");
        door1Sound.setBuffer(door1Buffer);
        door1Sound.setVolume(75 * ((float)volume / 100));

        door2Buffer.loadFromFile("audio/FNAUTN_Door2.wav");
        door2Sound.setBuffer(door2Buffer);
        door2Sound.setVolume(75 * ((float)volume / 100));

        light1Buffer.loadFromFile("audio/FNAUTN_Light1.wav");
        light1Sound.setBuffer(light1Buffer);
        light1Sound.setVolume(60 * ((float)volume / 100));

        light2Buffer.loadFromFile("audio/FNAUTN_Light2.wav");
        light2Sound.setBuffer(light2Buffer);
        light2Sound.setVolume(60 * ((float)volume / 100));

        light3Buffer.loadFromFile("audio/FNAUTN_Light3.wav");
        light3Sound.setBuffer(light3Buffer);
        light3Sound.setVolume(60 * ((float)volume / 100));
        light3Sound.setLoop(true);

        warning = false;
        stoppedAlarm = false;
        die = false;
        shutOff = false;
    }
};

#endif // OFFICE_H_INCLUDED
