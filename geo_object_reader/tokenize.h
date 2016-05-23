#ifndef TOKENIZE_H_
#define TOKENIZE_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace geom {

std::string seps(std::string &s);
void tokenize(std::string &str, std::vector<std::string> &tokens, const std::string &delimiters);

} // namespace geom
#endif