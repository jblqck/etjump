#ifndef CUSTOM_MAP_VOTES_HH
#define CUSTOM_MAP_VOTES_HH

#include <vector>
#include <string>

class CustomMapVotes
{
public:
    struct MapType
    {
        std::string type;
        std::string callvoteText;
        std::vector<std::string> maps;
    };

    struct TypeInfo
    {
        TypeInfo(bool typeExists, const std::string& callvoteText):
        typeExists(typeExists), callvoteText(callvoteText)
        {
            
        }
        TypeInfo() : typeExists(false) {}
        bool typeExists;
        std::string callvoteText;
    };

    CustomMapVotes();
    ~CustomMapVotes();
    bool Load();
    TypeInfo GetTypeInfo(const std::string& type) const;
    const std::string RandomMap(const std::string& type);
    std::string ListTypes() const;
    const std::vector<std::string> *ListInfo(const std::string& name);
    void GenerateVotesFile();
private:
    std::vector<MapType> customMapVotes_;
};

#endif