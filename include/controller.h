#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <model.h>
#include <clientSender.h>

class Controller
{
private:
    bool isExitRequested;
    std::ifstream inputFile;
    Model * model;
    ClientSender * sender;
public:
    Controller(std::string filepath, ClientSender * sender);
    ~Controller();
    void operator()();
};

#endif // CONTROLLER_H