#ifndef HG_BOT_HEADER
#define HG_BOT_HEADER

#include "sleepy_discord/sleepy_discord.h"

#include "commands/manager.hpp"
#include "commands/executor.hpp"

#include<string>
#include<vector>

class DoonBot : public SleepyDiscord::DiscordClient {
private:
    Commands::Manager mCommands;
    Commands::Executor mExec;
    std::vector<std::string> mArgs;

public:
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onMessage(SleepyDiscord::Message message) override;
    void registerTestCommands();

    void endInit();
};

void DoonBot::onMessage(SleepyDiscord::Message message)
{
	if (message.startsWith("+") && !message.author.bot)
    {   
        Commands::gMsg = message;
        std::istringstream iss(message.content);
        std::vector<std::string> tokens
        {
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };
        tokens[0] = tokens[0].substr(1);
        Commands::gArgs = tokens;
        this->mArgs = tokens;
        this->mExec.handle(Commands::gArgs[0],tokens);
    }
		
}

void DoonBot::endInit()
{
    Commands::gCommands = this->mCommands;
}

#endif


