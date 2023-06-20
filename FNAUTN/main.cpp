# include<SFML/Graphics.hpp>
# include<functional>
# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace sf;
using namespace std;

# include "input.h"
# include "render.h"
# include "office.h"
# include "map.h"
# include "player.h"
# include "room.h"
# include "drawcall.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    window.setKeyRepeatEnabled(false);

    Vector2i screen(window.getSize().x, window.getSize().y);

    Player player;
    Map mapa;
    Office office;

    Draw(window, player, office, mapa, screen);

    return 0;
}
