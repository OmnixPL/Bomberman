#include <controller.h>
#include <iostream>
#include <packets.h>
#include <thread>
#include <chrono>

void Controller::operator()()
{
    std::string command;
    while (isExitRequested && inputFile >> command)
    {
        if(command == "READY")
        {
            // PacketRdy * p = new PacketRdy(true, model->getUsername());
            // sender->addToQueue(p);
        }
        else if(command == "UNREADY")
        {
            // PacketRdy * p = new PacketRdy(false, model->getUsername());
            // sender->addToQueue(p);
        }
        else if(command == "LEAVE")
        {
            // PacketDisconnect * p = new PacketDisconnect(model->getUsername());
            // sender->addToQueue(p);
        }
        else if(command == "SHUTDOWN")
        {
            std::cout<<"Request exit";
            *isExitRequested = true;
        }
        else if(command == "UP")
        {
            ;
        }
        else if(command == "DOWN")
        {
            ;            
        }
        else if(command == "LEFT")
        {
            ;            
        }
        else if(command == "RIGHT")
        {
            ;
        }
        else if(command == "EXIT")
        {

        }
        else
        {
            std::cout<<"Ignoring invalid command " << command;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
}

Controller::Controller(std::string filepath, ClientSender * sender, Model * model, bool * exitPointer) : 
    inputFile(filepath, std::ifstream::in),
    sender(sender),
    model(model),
    isExitRequested(exitPointer)
{
}

Controller::~Controller()
{
}
