#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <iostream>
#include <vector>

/**
* @class Server
* @brief Class to upload scores to server and acquire highscores from server
* @details We define the constructor, variables and
* necessary methods.
*/

class Server{
public:
    /**
    * Uploads scores to server.
    */
    bool uploadScore(int totalnumberofPencil);

    /**
    * Acquires score from server.
    */
    void getScores();

    /**
    * Vector containing highest scores.
    */
    std::vector<int> playerScores;

    /**
    * Vector containing playernames of highest scorers.
    */
    std::vector<std::string> playerNames;
};


#endif // SERVER_H_INCLUDED
