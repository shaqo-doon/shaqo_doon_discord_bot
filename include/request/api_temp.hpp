#ifndef HG_TEMP_API
#define HG_TEMP_API

#include <string>
#include <vector>
#include <random>

#include <map>

#include "http.hpp"
#include "../json/json.hpp"

using json = nlohmann::json;

#define RESULT_LIMIT 7

namespace BancaBian
{

    template<typename ... Args>
    std::string string_format( const std::string& format, Args ... args )
    {
        int size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; 
        if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        std::unique_ptr<char[]> buf( new char[ size ] ); 
        snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); 
    }

    std::string to_lower(std::string s)
    {
        auto d = s;
        std::transform(d.begin(), d.end(), d.begin(),
            [](unsigned char c){ return std::tolower(c); });
        return d;
    }

    http::Response request(std::string type, std::string url)
    {
        http::Request request(url);
        return request.send(type);
    }
    
    std::string getTotalCompanies()
    {
        auto response = request("GET","http://zimbor.go.ro/api/bot/total/");
        auto recv = json::parse(std::string(response.body.begin(), response.body.end()));
        std::string ret = recv["total"]["jobs"];
        return ret;
    }

    json listOfCompaniesJSON()
    {
        
        auto response = request("GET","http://zimbor.go.ro/api/bot/companies/");
        auto recv = json::parse(std::string(response.body.begin(), response.body.end()));
        
        return recv;
    }

    std::string listOfCompaniesFormatted()
    {
        
        auto recv = listOfCompaniesJSON();
        
        std::string fmtList;
        json::iterator lim;

        if( recv["companies"].size() < 10 )
        { 
            lim = recv["companies"].end(); 
        }
        else
        { 
            lim = recv["companies"].begin() + 10;
        }

        for(json::iterator it = recv["companies"].begin();it != lim; ++it)
        {
            fmtList.append((*it)["company"]);
            fmtList.append(" - ");
            fmtList.append((*it)["link"]);
            fmtList.push_back('\n');            
        }

        return fmtList;
    }

    std::vector<std::string> listOfCompaniesVec()
    {
        auto recv = listOfCompaniesJSON();
        
        std::vector<std::string> vecComp;
        json::iterator lim;
        if( recv["companies"].size() < 10 )
        { 
            lim = recv["companies"].end(); 
        }
        else
        { 
            lim = recv["companies"].begin() + 10;
        }
        for(json::iterator it = recv["companies"].begin();it != lim; ++it)
        { 
            vecComp.push_back((*it)["company"]);      
        }
        return vecComp;
    }

    json jobsOfJSON(std::string company)
    {
        std::string query = "http://zimbor.go.ro/api/bot/jobs/?company=";

        auto response = request("GET",query.append(company));
        auto recv = json::parse(std::string(response.body.begin(), response.body.end()));
        return recv;
    }

    std::string jobsOfFormatted(std::string company)
    {
        auto recv = jobsOfJSON(company);
        
        std::string fmtList;

        for(json::iterator job = recv["jobs"].begin();job != recv["jobs"].begin() + 10 && job != recv["jobs"].end(); ++job)
        {
            fmtList.append("[");
            fmtList.append((*job)["country"]);
            fmtList.append("]");
            fmtList.append("[");
            fmtList.append((*job)["city"]);
            fmtList.append("]");
            fmtList.append((*job)["title"]);
            fmtList.append("\n");
            fmtList.append((*job)["link"]);
            fmtList.append("\n");
        }
        fmtList.append("\n For more jobs, visit: [PLACEHOLDER CAND IMPLEMENTAM ENDAVA LIST]");

        return fmtList;
    }

    std::string makeString(std::vector<std::string> v ,int p, int n)
    {
        std::string ret = "";
        for(int i = p; i < p+n; ++i)
        {
            ret.append(v[i]);
            ret.append(" ");
        }
        ret = ret.substr(0, ret.size()-1);
        
        return ret;
    }

    std::vector<std::string> tokenizeQuery( std::vector<std::string> tokens )
    {
        std::vector<std::string> ret;


        printf("t: %ld\n",tokens.size());
        for(auto & i : tokens)
        {
            printf("t: %s\n",i.c_str());
        }
        
        for(long unsigned int tkSize = 1; tkSize < tokens.size(); ++tkSize)
        {
            for(long unsigned int tk = 0; tk < tokens.size() - tkSize + 1; ++tk)
            {
                ret.push_back(to_lower(makeString(tokens,tk,tkSize)));
            }
        }
        ret.push_back(to_lower(makeString(tokens,0,tokens.size())));
        return ret;
    }

    json getAllJobsJSON()
    {
        std::string query = "http://zimbor.go.ro/api/bot/jobs/";

        auto response = request("GET",query);
        auto recv = json::parse(std::string(response.body.begin(), response.body.end()));

        return recv;
    }

    int countChar(char c,std::string s) {
        int count = 0;

        for (std::size_t i = 0; i < s.size(); i++)
            if (s[i] == c) count++;

        return count;
    }

    std::string searchByJobTitleFmt( std::vector<std::string> query )
    {
        std::string ret = "";
        json recv = getAllJobsJSON();
        std::vector<std::string> tokens = tokenizeQuery(query);
        std::map<int, std::string> results;
        std::size_t resCount = 0;
        for(json::iterator job = recv["jobs"].begin(); job != recv["jobs"].end(); ++job)
        {
            std::string entry = "";
            for(auto &tk : tokens)
            {
                printf("q: %s|%s \n",to_lower(tk).c_str(),to_lower((*job)["title"]).c_str());
                int tkTier = countChar(' ',tk);
                if (to_lower((*job)["title"]).find(to_lower(tk)) != std::string::npos) {
                    entry.append("[");
                    entry.append((*job)["company"]);
                    entry.append("]");
                    entry.append("[");
                    entry.append((*job)["country"]);
                    entry.append("]");
                    entry.append("[");
                    entry.append((*job)["city"]);
                    entry.append("]");
                    entry.append((*job)["title"]);
                    entry.append("\n");
                    entry.append((*job)["link"]);
                    entry.append("\n");
                    if(resCount<RESULT_LIMIT)
                    {
                        results[tkTier].append(entry); 
                        ++resCount;
                    }
                }
            }
        }


        int maxr = -1;
        for(auto & r : results)
        {
            maxr = r.first > maxr ? r.first : maxr;
        }

        for(int r = maxr; r >= 0; --r)
        {
            ret.append(results[r]);
        }

        return ret;
    }
} // namespace API


#endif