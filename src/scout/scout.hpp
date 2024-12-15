#pragma once

#include <string>
#include <vector>
#include "../common/socket.hpp"

class Scout {
public:

    Scout(){};
    Scout(const std::vector<std::string>& targets, const std::vector<std::string>& exchanges);

    std::vector<int> calculate_discrepancies();

private:

    std::vector<Socket> connections;

    












};
