#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHash>
#include <algorithm>
#include "score.h"

class Client : public QObject
{
    Q_OBJECT

private:
    QHash<QString, QString> preferences;
    QList<Score> scores;
    QHash<int, Score> storage;

public:
    explicit Client(QHash<QString, QString> pref, QObject *parent = nullptr);
    void addScore(Score score);
    QString getPreference(QString field);
    void sortScores();
    int idRank(int ranking);
    Score* getScore(int id);
};

#endif // CLIENT_H
