#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
#include <map>

#include "server.h"

using json = nlohmann::json;

size_t write_callback(char *ptr, size_t size, size_t nmemb, std::string* userdata){
    json j1 = json::parse(ptr);
    userdata->append(j1["link"].get<std::string>());
    return size * nmemb;
}

size_t writeScores(char *ptr, size_t size, size_t nmemb, std::string *userdata){
    json j1 = json::parse(ptr);
    userdata->append("[");
    for (auto it = j1["highscores"].begin(); it != j1["highscores"].end(); ++it)
    {
        json j2 = json::parse(it.value().dump());
        userdata->append(j2.dump());
        if(it+1!=j1["highscores"].end()){
            userdata->append(", ");
        }
    }
    userdata->append("]");
    return size * nmemb;
}

std::string Url(){
    std::string link = "";
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl1 = curl_easy_init();

    curl_easy_setopt(curl1, CURLOPT_URL, "https://matiusulung.com/se.json");
    curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl1, CURLOPT_WRITEDATA, &link);
    curl_easy_perform(curl1);

    curl_easy_cleanup(curl1);
    return link;
}

 bool Server::uploadScore(int totalnumberofPencil){
    json j1 ={
                {"jacobs-id", std::getenv("JACOBS_ID")},
                {"se-token", std::getenv("SE_TOKEN")},
                {"game-username", std::getenv("GAME_USERNAME")},
                {"score", totalnumberofPencil}
             };
    std::string s = j1.dump();

    std::string uploadLink = Url();
    uploadLink.append("/uploadscore");

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charsets: utf-8");
    headers = curl_slist_append(headers, "Expect:");

    curl_easy_setopt(curl, CURLOPT_URL, uploadLink.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, s.c_str());

    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else{
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
        return true;
    }
    return false;
}

void Server::getScores(){
    std::string downloadLink;
    std::string scores;

    playerNames.clear();
    playerScores.clear();
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl2 = curl_easy_init();

    downloadLink = Url();
    downloadLink.append("/getscores");

    curl_easy_setopt(curl2, CURLOPT_URL, downloadLink.c_str());
    curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION, writeScores);
    curl_easy_setopt(curl2, CURLOPT_WRITEDATA, &scores);

    CURLcode res = curl_easy_perform(curl2);
    if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
    else{
        curl_easy_cleanup(curl2);
    }

    json j1 = json::parse(scores);

    for (auto it1 = j1.begin(); it1 != j1.end(); ++it1)
    {
        std::string inScore;
        json j2 = json::parse(it1.value().dump());
        inScore.append(j2.dump());
        json j3 = json::parse(inScore);
        int i=0;
        std::string playerName;
        int playerScore;
        for (auto it = j3.begin(); it != j3.end(); ++it)
        {
            if (i==0){
                playerName = it.value().dump().c_str();
            }
            else{
                playerScore = atoi(it.value().dump().c_str());
            }
            i++;
        }
        Server::playerScores.push_back(playerScore);
        Server::playerNames.push_back(playerName);
    }
}
