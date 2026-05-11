#include <string>
#include <string_view>
#include <cstdlib>

#include "locale.h"

std::string localize(std::string_view input) {
    const char* lang = std::getenv("LANG");
    if (!lang) return std::string(input);

    const std::string_view LANG(lang);

    if (LANG.substr(0, 2) == "it") {
        if (input == "at") return "a";
        if (input == "Screen") return "Schermo";
        if (input == "Select Region") return "Seleziona Regione";
        if (input == "Select") return "Seleziona";
    }

    return std::string(input);
}
