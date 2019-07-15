#ifndef MATCHINGCONTROL_H
#define MATCHINGCONTROL_H

#include <QObject>
#include <QMessageBox>
#include <QMap>
#include <QtMath>
#include "staffDatabaseControl.h"
#include "animal.h"
#include "client.h"

class MatchingControl : public QObject
{
    Q_OBJECT

private:
    int animalNum;
    int clientNum;
    int matchedNum;
    float fullScore;
    QMap<int, Animal*> animals;
    QMap<int, Client*> clients;
    QList<QList<int>> matchingIdPairs;
    StaffDatabaseControl *dbControl;
    QString curType;
    static QStringList clientERuleCliAttri;
    static QStringList clientERuleAniAttri;
    static QStringList animalERuleAniAttri;
    static QStringList animalERuleCliAttri;
    QHash<QString, float> lifespan;
    bool startWithType(QString type);
    void buildAnimals(QString type);
    void buildClients(QString type);
    void scoreAllAnimals();
    void scoreAllClients();
    void scoreAnimal(Client *client, Animal *animal);
    void scoreClient(Animal *animal, Client *client);
    void equalityRuleScoring(Client *client, Animal *animal);
    void eScoreAnimal(Client *client, Animal *animal, Score *score);
    void eScoreClient(Animal *animal, Client *client, Score *score);
    void sScoreAnimal(Client *client, Animal *animal, Score *score);
    void sScoreClient(Animal *animal, Client *client, Score *score);
    float scoreSize(QString pref, QString attri);
    float scoreFeeding(QString pref, QString attri, QString from);
    float scoreAffectionStranger(QString pref, QString attri);
    float scoreExercise(QString pref, QString attri, QString from);
    float scoreVocality(QString pref, QString attri);
    float scoreAge(QString pref, QString attri);
    float scoreShedding(QString pref, QString attri);
    float scoreCoatLength(QString pref, QString attri);
    float scoreCoatLayers(QString pref, QString attri);
    float scoreTemperament(QString pref, QString attri);
    float scoreInteractive(QString pref, QString attri);
    float scoreCleaning(QString pref, QString attri);
    float scoreVetVisits(QString pref, QString attri);
    float scoreDogSpace(QString pref, QString attri);
    float scoreCatSpace(QString pref, QString attri);
    float scoreWeather(QString pref, QString attri);
    float scorePlayful(QString pref, QString attri);
    float scoreEnergetic(QString pref, QString attri);
    float scoreIntelligence(QString pref, QString attri);
    float scoreIndependent(QString pref, QString attri);
    float scoreSocial(QString pref, QString attri);
    float scoreSensitivity(QString pref, QString attri);
    float scoreGrooming(QString pref, QString attri);
    float scoreBudget(QString pref, QString attri);
    float scoreFirstPet(QString pref, QString attri);
    float scoreTrainability(QString pref, QString attri);
    float scoreAttention(QString pref, QString attri);
    inline float formula1(float pref, float attri, float deltaMax, float factor = 1);
    inline float formula2(float pref, float attri, float deltaMax, float factor = 1);
    inline float formula3(float pref, float attri, float deltaMax, float factor = 1);
    void compute();
    void clean();
    void store();

public:
    explicit MatchingControl(QObject *parent = nullptr);
    ~MatchingControl();
    bool start();    
};

#endif // MATCHINGCONTROL_H
