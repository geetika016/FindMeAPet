#include "animal.h"


Animal::Animal(QHash<QString, QString> attri, QObject *parent) :
    QObject(parent),
    attributes(attri)
{

}

void Animal::addScore(Score score)
{
    scores.append(score);
}

QString Animal::getAttribute(QString field)
{
    return attributes[field];
}

void Animal::sortScores()
{
    std::sort(scores.begin(), scores.end(), std::greater<Score>());
    Score score;
    foreach (score, scores) {
        storage[score.getId()] = score;
    }
}

int Animal::idRank(int ranking)
{
    return scores.at(ranking).getId();
}

Score* Animal::getScore(int id)
{
   return &storage[id];
}
