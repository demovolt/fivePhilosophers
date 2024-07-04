#include "Server.hpp"

Server::Server() : isFree(5, true) {}


bool Server::getForks(int id) {
    bool result = isFree[id - 1];
    if (id == 5) {
        result = result && isFree[0];
    }
    else {
        result = result && isFree[id];
    }
    if (result) {
        if (id == 5) {
            isFree[0] = false;
        }
        else {
            isFree[id] = false;
        }
        isFree[id - 1] = false;
    }
    return result;
}

void Server::setForks(int id) {
    if (id == 5) {
        isFree[0] = true;
    }
    else {
        isFree[id] = true;
    }
    isFree[id - 1] = true;
}