//
// Created by ericthomas on 07/11/2019.
//

#include <algorithm>
#include <iostream>
#include "utils.h"

bool utils::is_alpha(string &totest) {

    std::all_of(std::begin(totest), std::end(totest),
                [](char c){ return std::isalpha(c); });
}
