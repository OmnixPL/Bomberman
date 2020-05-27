// Szymon Malolepszy
// Kacper Kula
#ifndef MODEL_H
#define MODEL_H

#include <string>

class Model
{
private:
    std::string username;
public:
    Model(std::string username);
    ~Model();
    std::string getUsername();
};







#endif // MODEL_H