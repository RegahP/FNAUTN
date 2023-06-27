# include<SFML/Graphics.hpp>
# include<functional>
# include<iostream>
# include<stdlib.h>
# include<cstdlib>
# include<cstring>
# include<time.h>
# include<random>

using namespace sf;
using namespace std;

# include "input.h"
# include "room.h"
# include "profe.h"
# include "office.h"
# include "map.h"
# include "player.h"
# include "drawcall.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "FNAUTN", Style::Default);
    Image icon;
    if (icon.loadFromFile("mrklostertransparent.png")){

    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setKeyRepeatEnabled(false);

    Vector2i screen(window.getSize().x, window.getSize().y);

    Player player;
    Office office;
    office.startGenerator(190);
    office.setUI(screen);

    ///ROOMS CONFIG

    Room globalRooms[10];
    globalRooms[0].Configure(0, 7, 3);
    globalRooms[1].Configure(1, 5, 4);
    globalRooms[2].Configure(2, 2, 1);
    globalRooms[3].Configure(3, 3, 1);
    globalRooms[4].Configure(4, 5, 1);
    globalRooms[5].Configure(5, 2, 1);
    globalRooms[6].Configure(6, 3, 1);
    globalRooms[7].Configure(7, 4, 1);
    globalRooms[8].Configure(8, 3, 1);
    globalRooms[9].Configure(9, 3, 1);

    ///ADYACENCY MAP

    int matrixMap[7][7] = {
    {0, 0,  0,  0,  0,  0, 0},
    {0, 0,  0,  3,  0,  7, 0},
    {0, 0,  0, -1,  0, -1, 0},
    {0, 4, -1,  2, -1,  1, 0},
    {0, 0, -2, -1,  0, -1, 0},
    {0, 5,  0,  6,  0,  8, 0},
    {0, 0,  0,  0,  0,  0, 0}};

    int emptyFRooms[1] = {-1};
    Vector2i emptyFSpots[1];

    ///MAXI FILTER
    int maxiFRooms[3] = {2, 6, 7};
    Vector2i maxiFSpots[3];
    maxiFSpots[0] = Vector2i(4, 4);
    maxiFSpots[1] = Vector2i(0, 5);
    maxiFSpots[2] = Vector2i(0, 7);

    ///VASTAG FILTER
    int vastagFRooms[4] = {3, 4, 5, 7};
    Vector2i vastagFSpots[6];
    vastagFSpots[0] = Vector2i(0, 6);
    vastagFSpots[1] = Vector2i(0, 7);
    vastagFSpots[2] = Vector2i(1, 1);
    vastagFSpots[3] = Vector2i(1, 2);
    vastagFSpots[4] = Vector2i(1, 3);
    vastagFSpots[5] = Vector2i(1, 4);

    Vector2i emptySequence[1];

    ///KLOSTER SEQUENCE
    int klosterSequenceSize = 13;
    Vector2i klosterSequence[13];
    klosterSequence[0] = Vector2i(4, 4);
    klosterSequence[1] = Vector2i(4, 5);
    klosterSequence[2] = Vector2i(4, 3);
    klosterSequence[3] = Vector2i(1, 1);
    klosterSequence[4] = Vector2i(5, 2);
    klosterSequence[5] = Vector2i(1, 2);
    klosterSequence[6] = Vector2i(3, 3);
    klosterSequence[7] = Vector2i(1, 3);
    klosterSequence[8] = Vector2i(1, 4);
    klosterSequence[9] = Vector2i(1, 5);
    klosterSequence[10] = Vector2i(0, 3);
    klosterSequence[11] = Vector2i(0, 7);
    klosterSequence[12] = Vector2i(7, 2);

    ///MATI SEQUENCE

    int matiSequenceSize = 5;
    Vector2i matiSequence[5];
    matiSequence[0] = Vector2i(9, 1);
    matiSequence[1] = Vector2i(9, 2);
    matiSequence[2] = Vector2i(9, 3);
    matiSequence[3] = Vector2i(8, 1);
    matiSequence[4] = Vector2i(8, 2);

    ///MAXI SEQUENCE

    int maxiSequenceSize = 3;
    Vector2i maxiSequence[3];
    maxiSequence[0] = Vector2i(0, 6);
    maxiSequence[1] = Vector2i(7, 1);
    maxiSequence[2] = Vector2i(7, 3);

    ///VASTAG SEQUENCE

    int vastagSequenceSize = 3;
    Vector2i vastagSequence[3];
    vastagSequence[0] = Vector2i(0, 5);
    vastagSequence[1] = Vector2i(8, 3);
    vastagSequence[2] = Vector2i(7, 4);

    ///PROFES CONFIG

    Profe globalProfes[4]; // i  r  s
    globalProfes[0].Configure(0, 4, 4, 20, 5.12, globalProfes, globalRooms, matrixMap, emptyFRooms, emptyFSpots, 1, 1, klosterSequence, klosterSequenceSize); //4 4
    globalProfes[1].Configure(1, 9, 1, 20, 4.97, globalProfes, globalRooms, matrixMap, emptyFRooms, emptyFSpots, 1, 1, matiSequence, matiSequenceSize); //9 1
    globalProfes[2].Configure(2, 4, 1, 20, 3.15, globalProfes, globalRooms, matrixMap, maxiFRooms, maxiFSpots, 3, 3, maxiSequence, maxiSequenceSize); //4 1
    globalProfes[3].Configure(3, 6, 2, 20, 2, globalProfes, globalRooms, matrixMap, vastagFRooms, vastagFSpots, 4, 6, vastagSequence, vastagSequenceSize); //6 2

    Map mapa(screen);

    Draw(window, player, office, mapa, globalProfes, globalRooms, screen);

    return 0;
}
