#include <iostream>
#include <string>
#include <memory>

class Entity
{
public:
    Entity()
    {
        std::cout << "Created Entity\n";
    }

    Entity(std::string name)
    {
        std::cout << name << "\n";
    }

    ~Entity()
    {
        std::cout << "Destroyed Entity\n";
    }
};

int main()
{

    // std::unique_ptr<Entity> ent = std::make_unique<Entity>();
    std::unique_ptr<Entity> ent = std::make_unique<Entity>("Hello");

    return 0;
}