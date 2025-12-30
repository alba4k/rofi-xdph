#include <hyprutils/os/Process.hpp>
#include <iostream>
#include <QApplication>
#include <QScreen>
#include <string>
#include <vector>

#include "locale.h"
#include "windows.h"

int main(int argc, char **argv) {
    bool allowTokenByDefault = false;
    for(int i = 1; i < argc; ++i)
        if(std::string_view(argv[i]) == "--allow-token")
            allowTokenByDefault = true;

    std::string for_rofi = "";

    QApplication picker(argc, argv);
    const auto SCREENS = picker.screens();
    for(const auto& screen : SCREENS) {
        const auto GEOMETRY = screen->geometry();
        for_rofi += localize("Screen") + ": " + screen->name().toStdString() + " " + localize("at") + " " 
                     + std::to_string(GEOMETRY.x()) + ", " + std::to_string(GEOMETRY.y()) + " (" 
                     + std::to_string(GEOMETRY.width()) + "x" + std::to_string(GEOMETRY.height()) + ")\n";
    }

    const auto WINDOWS = getWindows(getenv("XDPH_WINDOW_SHARING_LIST"));
    for(const auto& window : WINDOWS)
        for_rofi += window.clazz + ": " + window.name + "\n";

    for_rofi += localize("Select Region") + "\n";

    Hyprutils::OS::CProcess proc("/bin/sh", {"-c", "rofi -format i -dmenu -p 'Seleziona' <<EOF\n" + for_rofi + "EOF"});
    if (!proc.runSync()) {
        std::cout << "error1\n";
        return 0; // this is what hyprland-share-picker does
    }

    int selection;
    try {
        selection = std::stoi(proc.stdOut());
    } catch (...) {
        std::cout << "error1\n";
        return 0;
    }

    std::cout << "[SELECTION]" << (allowTokenByDefault ? "r" : "") << "/";

    const int screen_count = SCREENS.size();
    const int window_count = WINDOWS.size();

    if(selection < screen_count) {
        std::cout << "screen:" << SCREENS[selection]->name().toStdString() << std::endl;
    } else if(selection < screen_count + window_count) {
        std::cout << "window:" << WINDOWS[selection - screen_count].id << std::endl;
    } else { 
        Hyprutils::OS::CProcess slurpProc("/bin/sh", {"-c", "slurp -f '%o@%x,%y,%w,%h' 2>&1"});
        if (!slurpProc.runSync()) {
            std::cout << "error1\n";
            return 0; 
        }
        std::cout << "region:" << slurpProc.stdOut() << std::endl;
    }

    return 0;
}