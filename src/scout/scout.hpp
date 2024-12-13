#pragma once

#include "listener.hpp"
#include <string>
#include <vector>

class Scout {
public:

    Scout() = delete;
    explicit Scout(const std::vector<std::string>& targets);

private:

    std::vector<Listener> listeners;











};
