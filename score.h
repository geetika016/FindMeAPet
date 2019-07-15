#ifndef SCORE_H
#define SCORE_H

#include <QObject>
#include <QHash>

class Score
{
private:
    int id;
    QString type;
    float total;
    QHash<QString, float> scores;
    QHash<QString, float> anifactors;
    QHash<QString, float> clifactors;

public:
    explicit Score(QString tp = "dummy", int idNum = -1);
    int getId() const;
    void setAttriScore(QString field, float num);
    QHash<QString, float> *getAttriScores();
    void calculate();
    float getTotal() const;
};

bool operator<(const Score &score1, const Score &score2);
bool operator>(const Score &score1, const Score &score2);

#endif // SCORE_H
