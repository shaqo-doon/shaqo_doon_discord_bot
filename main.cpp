#include "bot/token.hpp"
#include "bot/bot.hpp"

#include "commands/manager.hpp"
#include "commands/executor.hpp"

#include "sleepy_discord/sleepy_discord.h"

#include "commands/test_commands.hpp"

int main() {
    DoonBot client(BOT_TOKEN, SleepyDiscord::USER_CONTROLED_THREADS);
    
    client.registerTestCommands();
    client.endInit();
    
	client.run();
}