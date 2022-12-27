#include "id_generator.hpp"

IdGenerator IdGenerator::shared = IdGenerator();

long IdGenerator::generateId()
{
    lastId++;
    return lastId;
}

IdGenerator::IdGenerator()
{
    lastId = 0;
}