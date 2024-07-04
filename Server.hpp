#pragma once

#include <vector>

class Server {
public:
    Server();

    bool getForks(int id);

    void setForks(int id);

private:
    std::vector<bool> isFree;
};