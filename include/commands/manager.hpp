#ifndef HG_MANAGER_HEADER
#define HG_MANAGER_HEADER

#include<map>
#include<functional>
#include<string>
#include<vector>

#include "sleepy_discord/sleepy_discord.h"

#include "bot/token.hpp"
#include "bot/bot.hpp"

namespace Commands
{
    class Manager
    {
    private:
        std::map<std::string,std::function<void()>> mCommands;
    public:
        Manager(/* args */);
        ~Manager();

        void registerCommand(std::string command, std::function<void()> lambda);
        void runCommand(std::string command);
        std::vector<std::string> getCommands();
    };
    
    Manager::Manager(/* args */)
    {
    }
    
    Manager::~Manager()
    {
    }
    
    void Manager::registerCommand(std::string command, std::function<void()> lambda)
    {
        this->mCommands.insert(std::make_pair(command,lambda));
    }

    void Manager::runCommand(std::string command)
    {
        if(mCommands.count( command ))
        {
            this->mCommands[command]();
        }
        else
        {
            printf("attempt to run unknonw command: %s",command.c_str());
        }
    }

    std::vector<std::string> Manager::getCommands()
    {
        std::vector<std::string> r;

        for (auto const& x : this->mCommands)
        {
            r.push_back(x.first);
        }

        return r;
    }

    Manager gCommands;
    SleepyDiscord::Message gMsg;
    std::vector<std::string> gArgs;
} // namespace Commands

#endif