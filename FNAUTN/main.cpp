#include <SFML/Graphics.hpp>
# include<iostream>
# include<cstdlib>
# include<cstring>

using namespace sf;
using namespace std;

# include "input.h"
# include "player.h"
# include "drawcall.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "Holy Fuck Lois I'm Cumming", Style::Fullscreen);
    window.setKeyRepeatEnabled(false);

    Player player;

    DrawOffice(window, player);

    return 0;
}
