#pragma once

#include <mutex>

struct Philosopher
{
    int id;
    std::shared_ptr<std::mutex> left;
    std::shared_ptr<std::mutex> right;
};