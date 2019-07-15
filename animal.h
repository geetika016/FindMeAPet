#ifndef ANIMAL_H
#define ANIMAL_H

#include <QObject>
#include <QHash>
#include <algorithm>
#include "score.h"

class Animal : public QObject
{
    Q_OBJECT

private:
    QHash<QString, QString> attributes;
    QList<Score> scores;
    QHash<int, Score> storage;

public:
    explicit Animal(QHash<QString, QString> attri, QObject *parent = nullptr);
    void addScore(Score score);
    QString getAttribute(QString field);
    void sortScores();
    int idRank(int ranking);
    Score* getScore(int id);
};

#endif // ANIMAL_H
