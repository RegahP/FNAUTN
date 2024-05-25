#ifndef PROGRESS_H_INCLUDED
#define PROGRESS_H_INCLUDED

class Progress{
private:

    int night;
    bool night5;
    bool night6;
    bool customNight;

    float gamma;
    int volume;

public:

    int getNight(){
        return night;
    }
    bool getNight5(){
        return night5;
    }
    bool getNight6(){
        return night6;
    }
    bool getCustomNight(){
        return customNight;
    }
    void setNight(int num){
        night = num;
    }
    void setNight5(){
        night5 = true;
    }
    void setNight6(){
        night6 = true;
    }
    void setCustomNight(){
        customNight = true;
    }

    void setVolume(int x){
        volume = x;
    }
    void setGamma(float x){
        gamma = x;
    }

    int getVolume(){
        return volume;
    }
    float getGamma(){
        return gamma;
    }

    Progress(){
        night = 1;
        night5 = false;
        night6 = false;
        customNight = false;
        volume = 100;
        gamma = 1.0f;
    }
};

#endif // PROGRESS_H_INCLUDED
