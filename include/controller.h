// Szymon Malolepszy
// Kacper Kula
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <fstream>
#include <model.h>
#include <clientSender.h>

class Controller
{
private:
    std::ifstream inputFile;
    ClientSender * sender;
    Model * model;
    bool * isExitRequested;
    int noSeconds;
public:
    Controller(
        std::string filepath, 
        ClientSender * sender, 
        Model * model, 
        bool * exitPointer,
        int noSeconds
    );
    ~Controller();
    void runOnce();
    int getNoSeconds();
};

#endif // CONTROLLER_H