# include<SFML/Graphics.hpp>
# include<functional>
# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace sf;
using namespace std;

# include "input.h"
# include "office.h"
# include "profe.h"
# include "room.h"
# include "map.h"
# include "player.h"
# include "drawcall.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "FNAUTN", Style::Fullscreen);
    Image icon;
    if (icon.loadFromFile("mrklostertransparent.png")){

    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setKeyRepeatEnabled(false);

    Vector2i screen(window.getSize().x, window.getSize().y);

    Player player;
    Office office;
    Clock clock;
    Time time;

    Profe globalProfes[4]; // i  r  s
    globalProfes[0].Configure(0, 40, 4, 5, 5); //4
    globalProfes[1].Configure(1, 90, 1, 5, 5); //9
    globalProfes[2].Configure(2, 40, 1, 5, 5); //4
    globalProfes[3].Configure(3, 60, 1, 5, 5); //6

    Room globalRooms[10];
    globalRooms[0].Configure(0, 11, 4);
    globalRooms[1].Configure(1, 5, 4);
    globalRooms[2].Configure(2, 2, 1);
    globalRooms[3].Configure(3, 3, 1);
    globalRooms[4].Configure(4, 5, 1);
    globalRooms[5].Configure(5, 2, 1);
    globalRooms[6].Configure(6, 3, 1);
    globalRooms[7].Configure(7, 3, 1);
    globalRooms[8].Configure(8, 2, 1);
    globalRooms[9].Configure(9, 3, 1);

    Map mapa(screen);

    office.startClock(&clock);
    office.startGeneratorTemp(190);

    Draw(window, player, office, mapa, globalProfes, globalRooms, screen, &clock);

    return 0;
}
