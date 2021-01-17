#include "bot/bot.hpp"

#define COLOUR(r,g,b) ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)

#include <string>
#include <vector>
#include <random>

#include "request/http.hpp"
#include "json/json.hpp"

#include "request/api_temp.hpp"

using json = nlohmann::json;

void DoonBot::registerTestCommands()
{
	this->mCommands.registerCommand("help",[this](){
    
        std::string sentMsg = "These are the availible commands:\n\n"; 
        for (auto const& x : Commands::gCommands.getCommands())
        {
            sentMsg.push_back('+');
            sentMsg.append(x);
            sentMsg.push_back('\n');
        }

        SleepyDiscord::Embed embed;
        embed.title = "Commands";
        embed.description = sentMsg;
        embed.color = COLOUR(255,120,0);
        sendMessage(Commands::gMsg.channelID,"",embed);
    });

    this->mCommands.registerCommand("bere",[this](){
        sendMessage(Commands::gMsg.channelID,"https://shanghai-paper.com/wp-content/uploads/2020/06/Beer-in-China.jpg");
    });

    this->mCommands.registerCommand("ping",[this](){
        sendMessage(Commands::gMsg.channelID,"pog");
    });
	
    this->mCommands.registerCommand("donate",[this](){
        SleepyDiscord::Embed embed;
            embed.title = "Make a donation here";
            embed.url = "http://zimbor.go.ro/donate";
            embed.color = COLOUR(255,120,0);
        sendMessage(Commands::gMsg.channelID,"",embed);
    });

    this->mCommands.registerCommand("team",[this](){
        SleepyDiscord::Embed embed;
            embed.title = "More info about our team here";
            embed.url = "http://zimbor.go.ro/team";
            embed.color = COLOUR(255,120,0);
        sendMessage(Commands::gMsg.channelID,"",embed);
    });

    this->mCommands.registerCommand("roll",[this](){
        srand (time(NULL));
        std::stringstream msg(Commands::gArgs[1]); 
        int lim; msg >> lim; 
        sendMessage(Commands::gMsg.channelID,std::to_string(rand()%lim));
    });

    this->mCommands.registerCommand("companies",[this](){
        SleepyDiscord::Embed embed;
            embed.title = "Our first ten companies: ";
            embed.description = BancaBian::listOfCompaniesFormatted();
            embed.color = COLOUR(255,120,0);
        sendMessage(Commands::gMsg.channelID,"",embed);
    });

    this->mCommands.registerCommand("find",[this](){
        auto query = std::vector<std::string>(this->mArgs.begin() + 1,this->mArgs.end());

        std::string title = "While searching through ";
        title.append(BancaBian::getTotalCompanies());
        title.append(" jobs, we have found: ");

        std::string res = BancaBian::searchByJobTitleFmt(query);
        printf("%ld\n",res.size());
        try
        {
            if(res.size() < 6000)
            {
                SleepyDiscord::Embed embed;
                    embed.title = title;
                    embed.description = res;
                    embed.color = COLOUR(255,120,0);
                sendMessage(Commands::gMsg.channelID,"",embed);
            }
            else
            {
                sendMessage(Commands::gMsg.channelID,"Result is too large (>6000).");
            }
        }
        catch(const std::exception& e)
        {
            sendMessage(Commands::gMsg.channelID,e.what());
        }
        
    });


    this->mCommands.registerCommand("jobs",[this](){
        if(this->mArgs.size() > 1)
        {            
            auto companyList = BancaBian::listOfCompaniesVec();
            for(auto & compName : companyList)
            {
               if(this->mArgs[1] == compName)
               {
                    SleepyDiscord::Embed embed;
                    embed.title = BancaBian::string_format("First ten jobs from %s: ",this->mArgs[1].c_str());
                    embed.description = BancaBian::jobsOfFormatted(this->mArgs[1]);
                    embed.color = COLOUR(255,120,0);
                    sendMessage(Commands::gMsg.channelID,"",embed);
                    return;
               }
            }
            sendMessage(Commands::gMsg.channelID,"Invalid command");
        }
        else
        {
            sendMessage(Commands::gMsg.channelID,"invalid format, see +help for more info");
        }
    });

    this->mCommands.registerCommand("job",[this](){
        json recv;
        std::stringstream ss;
        
        if(Commands::gArgs.size() > 1)
        {
            if(Commands::gArgs[1] == "count")
            {
                try
                {
                    http::Request request("http://zimbor.go.ro/api/bot/total/");
                    const http::Response response = request.send("GET");
                    recv = json::parse(std::string(response.body.begin(), response.body.end()));
                    ss << recv["total"]["jobs"] << " jobs from" << "\n" << recv["total"]["companies"] << "companies";
                    SleepyDiscord::Embed embed;
                    embed.title = "We have counted: ";
                    embed.description = ss.str();
                    embed.color = COLOUR(255,120,0);
                    sendMessage(Commands::gMsg.channelID,"",embed);
                }
                catch (const std::exception& e)
                {
                    sendMessage(Commands::gMsg.channelID,"Error reaching server, contact balex#6304");
                }
            }
            else if(Commands::gArgs[1] == "find")
            {
                if(Commands::gArgs.size() > 2)
                {

                }
                else
                {
                    sendMessage(Commands::gMsg.channelID,"Invalid command");
                }
            }    
        }
        else
        {
            SleepyDiscord::Embed embed;
            embed.title = "See all jobs here";
            embed.url = "http://zimbor.go.ro/";
            embed.color = COLOUR(255,120,0);
            sendMessage(Commands::gMsg.channelID,"",embed);
        }
        
    });
    
    this->mCommands.registerCommand("zimbor",[this](){
        std::vector<std::string> zimbor = {
            "https://cdn.discordapp.com/attachments/784814224449863690/796503592289828864/enlarge.png",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505177623363584/TERMINATOR.png",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505191129415731/Screenshot_20210105-224053_Instagram.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505193709568040/ce_faceti_ba.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505216991494214/bombardier.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505249635500052/smecherii.mp4",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505567195430953/20201212_210258.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505841418371072/chinese.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505861362810900/hand.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505875086573608/ballsyu.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505918762254336/arnie.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505955411034163/cristian.png",
            "https://cdn.discordapp.com/attachments/796502530753298495/796505990269763594/c.png",
            "https://cdn.discordapp.com/attachments/796502530753298495/796506097358864414/ruman.mp4",
            "https://cdn.discordapp.com/attachments/796502530753298495/796506409994420258/chel_prost.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796506497696661514/wide_putin.jpg",
            "https://images-ext-2.discordapp.net/external/VBkTLwd1gE1WSSW3ak5KQv9xpRk20GflEIrVOoAwZRM/https/media.discordapp.net/attachments/296056831514509312/764709266967101511/image0.gif",
            "https://cdn.discordapp.com/attachments/796502530753298495/796507244569165855/Screenshot_20210105_182943_com.dazz.hoop.jpg",
            "https://cdn.discordapp.com/attachments/796502530753298495/796507244837077052/IMG_20201231_214841.jpg",

        };

        sendMessage(Commands::gMsg.channelID,zimbor.at(rand()%zimbor.size()));
    });
    
}