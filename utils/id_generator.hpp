#pragma once

class IdGenerator
{
public:
    static IdGenerator shared;
    long generateId();

private:
    long lastId;
    IdGenerator();
};