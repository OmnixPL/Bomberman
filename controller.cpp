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
            std::shared_ptr<PacketRdy> p = std::make_shared<PacketRdy>(true, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "UNREADY")
        {
            std::shared_ptr<PacketRdy> p = std::make_shared<PacketRdy>(false, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "AUTH")
        {
            std::string password;
            inputFile>>password;
            std::shared_ptr<PacketAuth> p = std::make_shared<PacketAuth>(password, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "LEAVE")
        {
            std::shared_ptr<PacketDisconnect> p = std::make_shared<PacketDisconnect>(model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "SHUTDOWN")
        {
            std::shared_ptr<PacketDisconnect> p = std::make_shared<PacketDisconnect>(model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
            std::cout<<"Request exit\n";
            *isExitRequested = true;
        }
        else if(command == "UP")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::UP, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "DOWN")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::DOWN, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "LEFT")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::LEFT, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else if(command == "RIGHT")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::RIGHT, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else if(command == "BOMB")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::NONE, true);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else
        {
            std::cout<<"Ignoring invalid command " << command;
        }
        std::this_thread::sleep_for(std::chrono::seconds(noSeconds));
    }
}

void Controller::runOnce()
{
    std::string command;
    if(inputFile >> command && !(*isExitRequested))
    {
        if(command == "READY")
        {
            std::shared_ptr<PacketRdy> p = std::make_shared<PacketRdy>(true, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "UNREADY")
        {
            std::shared_ptr<PacketRdy> p = std::make_shared<PacketRdy>(false, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "AUTH")
        {
            std::string password;
            inputFile>>password;
            std::shared_ptr<PacketAuth> p = std::make_shared<PacketAuth>(password, model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "LEAVE")
        {
            std::shared_ptr<PacketDisconnect> p = std::make_shared<PacketDisconnect>(model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "SHUTDOWN")
        {
            std::shared_ptr<PacketDisconnect> p = std::make_shared<PacketDisconnect>(model->getUsername());
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
            std::cout<<"Request exit\n";
            *isExitRequested = true;
        }
        else if(command == "UP")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::UP, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "DOWN")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::DOWN, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p));
        }
        else if(command == "LEFT")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::LEFT, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else if(command == "RIGHT")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::RIGHT, false);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else if(command == "BOMB")
        {
            std::shared_ptr<PacketAction> p = std::make_shared<PacketAction>(model->getUsername(), action_t::NONE, true);
            sender->addToQueue(std::dynamic_pointer_cast<Packet>(p)); 
        }
        else
        {
            std::cout<<"Ignoring invalid command " << command;
        }
        std::this_thread::sleep_for(std::chrono::seconds(noSeconds));
    }
}

Controller::Controller(
    std::string filepath, 
    ClientSender * sender, 
    Model * model, 
    bool * exitPointer,
    int noSeconds) : 
        inputFile(filepath, std::ifstream::in),
        sender(sender),
        model(model),
        isExitRequested(exitPointer),
        noSeconds(noSeconds)
{
}

Controller::~Controller()
{
}
