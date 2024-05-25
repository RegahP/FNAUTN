# include<SFML/Graphics.hpp>
# include<SFML/Audio.hpp>
# include<functional>
# include<iostream>
# include<stdlib.h>
# include<cstdlib>
# include<cstring>
# include<time.h>
# include<random>

using namespace sf;
using namespace std;

# include "tools.h"
# include "anim.h"
# include "room.h"
# include "profe.h"
# include "office.h"
# include "map.h"
# include "player.h"
# include "progress.h"
# include "progressFunctions.h"
# include "drawcall.h"
# include "night.h"
# include "menu.h"

int main()
{
    RenderWindow window(VideoMode(1600, 900), "FNAUTN", Style::Fullscreen);
    Image icon;
    if (icon.loadFromFile("mrklostertransparent.png")){

    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setKeyRepeatEnabled(false);

    Menu(window);

    return 0;
}
