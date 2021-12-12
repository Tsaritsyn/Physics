#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>

#include "include.hpp"

#define NUM_CHANNELS 4

int main()
{
    App app({1080, 720}, "Physics");
    app.run();

    return 0;
}
