#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <string>

#include "Server.hpp"
#include "Philosopher.hpp"

std::mutex chating;

void blockChating(std::string msg, Philosopher ph) {
    chating.lock();

    std::cout << std::this_thread::get_id() << " " << msg << " Ph = " << ph.id << std::endl;

    chating.unlock();
}

void doWork(Philosopher& ph, Server& server) {
    while (true) {
        blockChating("Think", ph);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        if (server.getForks(ph.id)) {
            ph.left->lock();

            blockChating("Take fork left", ph);

            ph.right->lock();

            blockChating("Take fork right", ph);

            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            blockChating("Have eaten", ph);

            ph.left->unlock();
            ph.right->unlock();

            server.setForks(ph.id);
        }
    }
}

int main() {
    std::vector<std::shared_ptr<std::mutex>> fork(5, nullptr);

    for (int i = 0; i < fork.size(); i++) {
        fork[i] = std::make_shared<std::mutex>();
        //std::cout << "Fork number " << i << "address " << fork[i] << std::endl;
    }
    
    std::vector<Philosopher> Ph(5);

    for (int i = 0; i < Ph.size(); i++) {
        Ph[i].id = i + 1;
        Ph[i].left = fork[i];
        if (i + 1 < Ph.size()) {
            Ph[i].right = fork[i + 1];
        }
        else {
            Ph[i].right = fork[0];
        }
        //std::cout << "Ph number " << Ph[i].id << "\naddress left fork " << Ph[i].left << "\naddress right fork " << Ph[i].right << std::endl;
    }

    std::shared_ptr<Server> server(std::make_shared<Server>());

    std::vector<std::thread> lifes;

    for (int i = 0; i < 5; i++) {
        lifes.push_back(std::thread{ doWork, std::ref(Ph[i]), std::ref(*server)});
    }

    for (int i = 0; i < 5; i++) {
        lifes[i].join();
    }

    std::cout <<  " END " << std::endl;
}