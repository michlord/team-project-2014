#include <string>
#include <cstdlib>
std::string randomString() {
    const static std::string WORDS[] = {"oga", "             boga"};
    return WORDS[std::rand() % 2];
}