#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

static void filtrerType(std::string& type) {
    type.erase(std::remove_if(std::begin(type), std::end(type),
                        [](auto ch) { return std::isdigit(ch); }),
        type.end());
}

#endif