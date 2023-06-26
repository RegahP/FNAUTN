# include<SFML/Graphics.hpp>
# include<functional>
# include<iostream>
# include<stdlib.h>
# include<cstdlib>
# include<cstring>
# include<time.h>

using namespace sf;
using namespace std;

# include "input.h"
# include "office.h"
# include "room.h"
# include "profe.h"
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

    Room globalRooms[10];
    globalRooms[0].Configure(0, 11, 3);
    globalRooms[1].Configure(1, 5, 4);
    globalRooms[2].Configure(2, 2, 1);
    globalRooms[3].Configure(3, 3, 1);
    globalRooms[4].Configure(4, 5, 1);
    globalRooms[5].Configure(5, 2, 1);
    globalRooms[6].Configure(6, 3, 1);
    globalRooms[7].Configure(7, 4, 1);
    globalRooms[8].Configure(8, 2, 1);
    globalRooms[9].Configure(9, 3, 1);

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

    int maxiFRooms[2] = {2, 6};

    int vastagFRooms[3] = {3, 4, 5};

    Vector2i maxiFSpots[4];
    maxiFSpots[0] = Vector2i(4, 4);
    maxiFSpots[1] = Vector2i(1, 5);
    maxiFSpots[2] = Vector2i(0, 9);
    maxiFSpots[3] = Vector2i(0, 8);

    Vector2i vastagFSpots[6];
    vastagFSpots[0] = Vector2i(0, 8);
    vastagFSpots[1] = Vector2i(0, 7);
    vastagFSpots[2] = Vector2i(1, 1);
    vastagFSpots[3] = Vector2i(1, 2);
    vastagFSpots[4] = Vector2i(1, 3);
    vastagFSpots[5] = Vector2i(1, 4);

    Profe globalProfes[4]; // i  r  s
    globalProfes[0].Configure(0, 0, 4, 20, 5.12, globalProfes, globalRooms, matrixMap, emptyFRooms, emptyFSpots, 1, 1); //4 4
    globalProfes[1].Configure(1, 9, 1, 20, 4.97, globalProfes, globalRooms, matrixMap, emptyFRooms, emptyFSpots, 1, 1); //9 1
    globalProfes[2].Configure(2, 4, 1, 20, 3.15, globalProfes, globalRooms, matrixMap, maxiFRooms, maxiFSpots, 2, 4); //4 1
    globalProfes[3].Configure(3, 6, 1, 20, 5.66, globalProfes, globalRooms, matrixMap, vastagFRooms, vastagFSpots, 3, 6); //6 1

    Map mapa(screen);

    Draw(window, player, office, mapa, globalProfes, globalRooms, screen);

    return 0;
}
