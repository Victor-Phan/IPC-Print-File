#pragma once
#include "service.hpp"
#include <pthread.h>
class Client : public Service{
public:
    Client() = default;
    virtual ~Client() = default;
    bool connectClient(char * filename, int priority);
};