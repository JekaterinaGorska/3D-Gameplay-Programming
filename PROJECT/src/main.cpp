//Jekaterina Gorska
#include <./include/Game.h>
int main(void)
{
    // Setup SFML Context Settings
    // For more information, refer to:
    // - https://www.sfml-dev.org/documentation/2.6.1/structsf_1_1ContextSettings.php
    // - https://www.sfml-dev.org/documentation/2.6.1/ContextSettings_8hpp_source.php
    ContextSettings settings;
    settings.depthBits = 24u; // for depth buffer Z-Buffer
    settings.antialiasingLevel = 4u;

    try
    {
        // Create a reference to the game and run
        Game game(settings);
        game.run();
    }
    catch (const exception &e)
    {
        // Exception occurred, print error message
        cerr << "Exception: " << e.what() << endl;
        // Return -1 indicating program exited with errors
        return -1;
    }

    // Return 0 indicating program exited successfully
    return 0;
}
