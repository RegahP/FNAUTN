#ifndef PROFE_H_INCLUDED
#define PROFE_H_INCLUDED

class Profe{

private:

    int profeID;
    Vector2i currentPos;
    int difficulty;
    float opportunityRate;
    bool attackMode;
    bool reachedOffice;

public:
    Vector2i getPos(){
        return currentPos;
    }
    int getID(){
        return profeID;
    }

    void Configure(int ID, int initRoom, int initSpot, int diff, float oppRate){
        currentPos.x = initRoom;
        currentPos.y = initSpot;
        difficulty = diff;
        opportunityRate = oppRate;
    }
};

#endif // PROFE_H_INCLUDED
