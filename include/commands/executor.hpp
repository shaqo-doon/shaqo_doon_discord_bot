#ifndef HG_EXECUTOR_HEADER
#define HG_EXECUTOR_HEADER

#include<map>
#include<functional>
#include<string>
#include<vector> // for vector 
#include<algorithm> // for copy() and assign() 
#include<iterator> // for back_inserter 
#include "manager.hpp"

namespace Commands
{
    class Executor
    {
    private:
    
    public:
        Executor();
        ~Executor();

        void handle(std::string command,std::vector<std::string> v);
    };
    
    Executor::Executor()
    {
    }
     
    Executor::~Executor()
    {
    }
    
    void Executor::handle(std::string command,std::vector<std::string> v)
    {
        copy(v.begin(), v.end(),Commands::gArgs.begin());//nu sterge
        Commands::gCommands.runCommand(command);
    }

    Executor exec;
} // namespace Commands

#endif