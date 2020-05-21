#include <controller.h>
#include <iostream>
#include <packets.h>

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
            // PacketDisconnect * p = new PacketDisconnect(model->getUsername());
            // sender->addToQueue(p);
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
        else
        {
            std::cout<<"Ignoring invalid command " << command;
        }
        
    }
    
}

Controller::Controller(std::string filepath, ClientSender * sender, Model * model) : 
    inputFile(filepath, std::ifstream::in),
    sender(sender),
    model(model)
{
}

Controller::~Controller()
{
}
