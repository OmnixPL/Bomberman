#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>

class Controller
{
private:
    bool isExitRequested;
    std::ifstream inputFile;
public:
    Controller(std::string filepath);
    ~Controller();
    void operator()();
};

Controller::Controller(std::string filepath) : inputFile(filepath, std::ifstream::in)
{
}

Controller::~Controller()
{
}


#endif // CONTROLLER_H