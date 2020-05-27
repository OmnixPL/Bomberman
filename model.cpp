// Szymon Malolepszy
// Kacper Kula
#include <model.h>

Model::Model(std::string username) : username(username)
{
}

std::string Model::getUsername()
{
    return username;
}
Model::~Model()
{
}