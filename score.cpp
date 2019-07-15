#include "score.h"

Score::Score(QString tp, int idNum) :
    type(tp),
    id(idNum)
{
    float veryHigh = -1000;
    float high = 30;
    float moderate = 2;
    float low = 1;
    QHash<QString, float> inferFactor;
    inferFactor["grooming"] = 0.9;
    inferFactor["budget"] = 0.8;
    inferFactor["good_new_owners"] = 0.8;
    inferFactor["trainability"] = 0.9;
    inferFactor["interactive"] = 0.9;
    inferFactor["playful"] = 0.9;
    inferFactor["affection_owner"] = 0.8;
    inferFactor["affection_family"] = 0.9;
    inferFactor["attention"] = 0.8;
    //animal field name for anifactors, priorities are based on client preference<--------------!!!
    anifactors["special_needs"] = veryHigh;
    anifactors["hypoallergenic"] = veryHigh;
    anifactors["nocturnal"] = veryHigh;
    anifactors["pair"] = veryHigh;
    anifactors["good_with_being_alone"] = high*1.2;
    anifactors["breed"] = high*1.3;
    anifactors["tamed"] = high*1.4;
    anifactors["kid_firendly"] = moderate*1.2;
    anifactors["good_other_pets"] = moderate*1.1;
    anifactors["colour"] = low*1.1;
    anifactors["gender"] = low*1.3;
    anifactors["dietary"] = low*1.1;
    anifactors["size"] = high*1.1;
    anifactors["feeding"] = high*1.1;
    anifactors["energetic"] = moderate;
    anifactors["exercise"] = moderate;
    anifactors["vocality"] = moderate*1.1;
    anifactors["age"] = moderate*1.3;
    anifactors["shedding"] = moderate*1.2;
    anifactors["coat_length"] = moderate;
    anifactors["coat_layers"] = moderate;
    anifactors["interactive"] = moderate*1.3;
    anifactors["cleaning"] = moderate*1.2;
    anifactors["temperament"] = moderate*1.2;
    anifactors["vet_visits"] = low*1.2;
    anifactors["weather"] = low*1.1;
    anifactors["playful"] = low*1.2;
    anifactors["space"] = low*1.3;
    anifactors["intelligence"] = low*1.1;
    anifactors["independent"] = low*1.2;
    anifactors["social"] = low*1.1;
    anifactors["sensitivity"] = low*1.3;
    anifactors["grooming"] = moderate*1.2*inferFactor["grooming"];
    anifactors["budget"] = high*1.3*inferFactor["budget"];
    anifactors["good_new_owners"] = low*1.3*inferFactor["good_new_owners"];
    anifactors["trainability"] = low*1.2*inferFactor["trainability"];
    anifactors["affection_stranger"] = moderate*1.1;
    anifactors["affection_owner"] = moderate*1.3*inferFactor["affection_owner"];
    anifactors["affection_family"] = moderate*1.2*inferFactor["affection_family"];
    anifactors["attention"] = moderate*1.2*inferFactor["attention"];

    //client field name for clifactors, priorities are based on animal preference<--------------!!!
    clifactors["special_needs"] = high*1.4;
    clifactors["dietary"] = high*1.2;
    clifactors["pair"] = high*1.2;
    clifactors["at_home_mostly"] = high*1.3;
    clifactors["kids"] = moderate;
    clifactors["other_pets"] = moderate;
    clifactors["feeding"] = high*1.3;
    clifactors["exercise"] = moderate*1.4;
    clifactors["interactive"] = moderate*1.2;
    clifactors["vet_visits"] = high*1.4;
    clifactors["sensitivity"] = high*1.3;
}

int Score::getId() const
{
    return id;
}

float Score::getTotal() const
{
    return total;
}

void Score::setAttriScore(QString field, float num)
{
    scores[field] = num;
}

QHash<QString, float>* Score::getAttriScores()
{
    return &scores;
}

void Score::calculate()
{
    if (type == "client")
    {

        QHashIterator<QString, float> i(scores);
        total = 0;
        float attriScore;
        while (i.hasNext()) {
            i.next();
            if(clifactors[i.key()] < 0)
            {
                if(i.value() == 0)
                    attriScore = clifactors[i.key()];
                else
                    attriScore = i.value();
            }
            else
                attriScore = i.value() * clifactors[i.key()];

            total += attriScore;
        }
    }
    else
    {

        QHashIterator<QString, float> i(scores);
        total = 0;
        float attriScore;
        while (i.hasNext()) {
            i.next();
            if(anifactors[i.key()] < 0)
            {
                if(i.value() == 0)
                    attriScore = anifactors[i.key()];
                else
                    attriScore = i.value();
            }
            else
                attriScore = i.value() * anifactors[i.key()];

            total += attriScore;
        }
    }
}

bool operator<(const Score &score1, const Score &score2)
{
    if (score1.getTotal() < score2.getTotal())
        return true;
    return false;
}

bool operator>(const Score &score1, const Score &score2)
{
    if (score1.getTotal() > score2.getTotal())
        return true;
    return false;
}
