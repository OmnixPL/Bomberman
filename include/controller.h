#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <model.h>
#include <clientSender.h>

class Controller
{
private:
    std::ifstream inputFile;
    Model * model;
    ClientSender * sender;
    bool * isExitRequested;
public:
    Controller(std::string filepath, ClientSender * sender, Model * model, bool * exitPointer);
    ~Controller();
    void operator()();
};

#endif // CONTROLLER_H