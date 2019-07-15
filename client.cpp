#include "client.h"

Client::Client(QHash<QString, QString> pref, QObject *parent) :
    QObject(parent),
    preferences(pref)
{

}

void Client::addScore(Score score)
{
    scores.append(score);
}

QString Client::getPreference(QString field)
{
    return preferences[field];
}

void Client::sortScores()
{
    std::sort(scores.begin(), scores.end(), std::greater<Score>());

    Score score;
    foreach (score, scores) {
        storage[score.getId()] = score;
    }
}

int Client::idRank(int ranking)
{
    return scores.at(ranking).getId();
}

Score* Client::getScore(int id)
{
   return &storage[id];
}
