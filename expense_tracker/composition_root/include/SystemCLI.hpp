#pragma once
#include "System.hpp"

namespace et {

class SystemCLI : public System {
public:
    SystemCLI();
    ~SystemCLI();
    int run(int argc, char* argv[]) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};

} // namespace et
