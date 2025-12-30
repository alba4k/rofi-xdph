#include <vector>
#include <string>

struct SWindowEntry {
    std::string name;
    std::string clazz;
    unsigned long long id = 0;
};

std::vector<SWindowEntry> getWindows(const char* env);
