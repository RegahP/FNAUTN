#include <SFML/Graphics.hpp>
# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace sf;
using namespace std;

# include "input.h"
# include "office.h"
# include "render.h"
# include "player.h"
# include "room.h"
# include "drawcall.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    window.setKeyRepeatEnabled(false);

    Vector2i screen(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);

    Player player;

    Draw(window, player, screen);

    return 0;
}
