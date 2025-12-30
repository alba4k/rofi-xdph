#include <hyprutils/os/Process.hpp>
#include <iostream>
#include <QApplication>
#include <QScreen>
#include <string>
#include <vector>

#include "locale.h"
#include "windows.h"

// Formats:
// Screen:
// [SELECTION]r/screen:eDP-1
// Window:
// [SELECTION]r/window:-1584294736
// Region:
// [SELECTION]r/region:eDP-1@0,0,1920,1200

int main(int argc, char **argv) {
    bool allowTokenByDefault = false;
    for(int i = 1; i < argc; ++i) {
        if(argv[i] == std::string{"--allow-token"}) {
            allowTokenByDefault = true;
        }
    }

    std::string for_rofi = "";

    // add screens to for_rofi
    QApplication picker(argc, argv);
    const auto SCREENS = picker.screens();
    for(auto screen : SCREENS) {
        const auto GEOMETRY = screen->geometry();
        for_rofi += localize("Screen") + ": " + screen->name().toStdString() + " " + localize("at") + " " + std::to_string(GEOMETRY.x()) 
                     + ", " + std::to_string(GEOMETRY.y()) + " (" + std::to_string(GEOMETRY.width())
                     + "x" + std::to_string(GEOMETRY.height()) + ")\n";
    }

    const auto WINDOWS = getWindows(getenv("XDPH_WINDOW_SHARING_LIST"));
    for(auto window : WINDOWS)
        for_rofi += window.clazz + ": " + window.name + "\n";

    // add this option to for_rofi
    for_rofi += localize("Select Region") + "\n";

    Hyprutils::OS::CProcess proc("/bin/sh", {"-c", "rofi -format i -dmenu -p 'Seleziona' <<EOF\n" + for_rofi + "EOF"});
    if (!proc.runSync()) {
        std::cout << "error1\n";
        return 0; // this is what hyprland-share-picker does
    }
    std::string output = proc.stdOut();
    if(output == "") {
        std::cout << "error1\n";
        return 0; // this is what hyprland-share-picker does
    }
    int selection = std::stoi(output);

    std::cout << "[SELECTION]" << (allowTokenByDefault ? "r" : "") << "/";

    if(selection < (int)SCREENS.length()) // selected a screen
        std::cout << "screen:" << SCREENS[selection]->name().toStdString() << std::endl;
    else if(selection - (int)SCREENS.length() < (int)std::size(WINDOWS)) // selected a window
        std::cout << "window:" << (int)WINDOWS[selection - (int)SCREENS.length()].id << std::endl;
    else { // selected a region
        Hyprutils::OS::CProcess proc("/bin/sh", {"-c", "slurp -f '%o@%x,%y,%w,%h' 2>&1"});
        if (!proc.runSync()) {
            std::cout << "error1\n";
            return 0; // this is what hyprland-share-picker does
        }
        std::cout << "region:" << proc.stdOut() << std::endl;
    }

    return 0;
}
