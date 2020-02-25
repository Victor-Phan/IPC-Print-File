#pragma once
#include "service.hpp"
class Client : public Service{
  private:

  public:
    Client() = default;
    virtual ~Client() = default;
    bool connectClient(char * filename, int priority);
};