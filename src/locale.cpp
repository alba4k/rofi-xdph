#include <string>

#include "locale.h"

std::string localize(std::string input) {
    const std::string LANG = std::string{getenv("LANG")}.substr(0, 2);

    // could also use switches but whatever
    if(input == "at") {
        if(LANG == "it") return "a";
    }
    else if(input == "Select Region") {
        if(LANG == "it") return "Seleziona Regione";
    }
    else if(input == "Screen") {
        if(LANG == "it") return "Schermo";
    }

    return input;
}