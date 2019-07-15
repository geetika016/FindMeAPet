#include "matchingControl.h"

QStringList MatchingControl::clientERuleCliAttri = {"breed", "gender", "at_home_mostly", "colour", "dietary_needs", "special_needs", "kids",
                                                     "other_pets", "allergies", "pair", "tamed", "nocturnal"};
QStringList MatchingControl::clientERuleAniAttri = {"breed", "gender", "good_with_being_alone", "colour", "dietary", "special_needs", "kid_friendly",
                                                     "good_other_pets", "hypoallergenic", "pair", "tamed", "nocturnal"};
QStringList MatchingControl::animalERuleAniAttri = {"dietary", "good_with_being_alone", "special_needs", "kid_friendly", "good_other_pets", "pair"};
QStringList MatchingControl::animalERuleCliAttri = {"dietary_needs", "at_home_mostly", "special_needs", "kids", "other_pets", "pair"};


MatchingControl::MatchingControl(QObject *parent) : QObject(parent)
{
    dbControl = new StaffDatabaseControl;
    //temperary, shoulb be in widget class/////
    dbControl->dbRequest(NULL, NULL, ALGORITHM_CLEAN_TABLE);

    //////////////////////////////////////////
    ///can be based on breed
    lifespan["Dog"] = 11.5;
    lifespan["Cat"] = 12;
    lifespan["Bird"] = 20;
    lifespan["Rabbit"] = 8;
    lifespan["Hamster"] = 2.5;
    lifespan["Guinea Pig"] = 6;
}

MatchingControl::~MatchingControl()
{
    delete dbControl;
}

bool MatchingControl::start()
{
    startWithType("Dog");
    startWithType("Cat");
    startWithType("Bird");
    startWithType("Rabbit");
    startWithType("Hamster");
    startWithType("Guinea Pig");
    return true;
}

bool MatchingControl::startWithType(QString type)
{
    curType = type;
    buildAnimals(type);
    buildClients(type);
    scoreAllAnimals();
    scoreAllClients();
    compute();
    store();
    clean();   
}

void MatchingControl::buildAnimals(QString type)
{
    QHash<QString, QString> input;
    input["type"] = type;
    QList<QHash<QString, QString>> output;
    QString errMsg;
    if (!dbControl->dbRequest(&input, &output, ALGORITHM_READ_ANIMAL, &errMsg))
        QMessageBox::critical(NULL, "Error", errMsg);
    QHash<QString, QString> animalHash;
    foreach (animalHash, output) {
        Animal *animal = new Animal(animalHash);
        //qDebug()<<animalHash["id"];
        animals.insert(animalHash["id"].toInt(), animal);
    }
}

void MatchingControl::buildClients(QString type)
{
    QHash<QString, QString> input;
    input["animal_type"] = type;
    QList<QHash<QString, QString>> output;
    QString errMsg;
    if (!dbControl->dbRequest(&input, &output, ALGORITHM_READ_CLIENT, &errMsg))
        QMessageBox::critical(NULL, "Error", errMsg);
    QHash<QString, QString> clientHash;
    foreach (clientHash, output) {
        Client *client = new Client(clientHash);
        clients.insert(clientHash["id"].toInt(), client);
    }
}

void MatchingControl::scoreAllAnimals()
{
    Animal *animal;
    Client *client;
    foreach (client, clients) { //foreach extract values
        foreach (animal, animals) {
            scoreAnimal(client, animal);
        }
        client->sortScores();
    }
}

void MatchingControl::scoreAllClients()
{
    Animal *animal;
    Client *client;
    foreach (animal, animals) {
        foreach (client, clients) {
            scoreClient(animal, client);
        }
        animal->sortScores();
    }
}

void MatchingControl::scoreAnimal(Client *client, Animal *animal)
{
    Score score("animal", animal->getAttribute("id").toInt());
    eScoreAnimal(client, animal, &score);
    sScoreAnimal(client, animal, &score);

    score.calculate();
    client->addScore(score);
}

void MatchingControl::scoreClient(Animal *animal, Client *client)
{
    Score score("client", client->getPreference("id").toInt());
    eScoreClient(animal, client, &score);
    sScoreClient(animal, client, &score);

    score.calculate();
    animal->addScore(score);
}

void MatchingControl::eScoreAnimal(Client *client, Animal *animal, Score *score)
{
    for(int i=0; i<clientERuleCliAttri.size(); i++)
    {
        float num = 0;
        ////qDebug()<<clientERuleAniAttri[i];
        if ((client->getPreference(clientERuleCliAttri[i])).isEmpty())
            num = 1;
        else if ((animal->getAttribute(clientERuleAniAttri[i])).isEmpty())
            num = 0.5;
        else if (clientERuleCliAttri[i] == "other_pets")
        {
            QString clientPref = client->getPreference(clientERuleCliAttri[i]);
            QString animalAttri = animal->getAttribute(clientERuleAniAttri[i]);
            bool containsAll = true;
            for (int i=0; i<clientPref.size(); i++)
                if (!animalAttri.contains(clientPref[i]))
                    containsAll = false;
            if (containsAll)
                num = 1;
        }
        else if (client->getPreference(clientERuleCliAttri[i]) == animal->getAttribute(clientERuleAniAttri[i]))
            num = 1;

        score->setAttriScore(clientERuleAniAttri[i], num);
    }
}

void MatchingControl::eScoreClient(Animal *animal, Client *client, Score *score)
{
    for(int i=0; i<animalERuleAniAttri.size(); i++)
    {
        float num = 0;
        if ((animal->getAttribute(animalERuleAniAttri[i])).isEmpty())
            num = 1;
        else if ((client->getPreference(animalERuleCliAttri[i])).isEmpty())
            num = 0.5;
        else if (animalERuleAniAttri[i] == "good_other_pets")
        {
            QString clientPref = client->getPreference(animalERuleCliAttri[i]);
            QString animalAttri = animal->getAttribute(animalERuleAniAttri[i]);
            bool containsAll = true;
            for (int i=0; i<clientPref.size(); i++)
                if (!animalAttri.contains(clientPref[i]))
                    containsAll = false;
            if (containsAll)
                num = 1;
        }
        else if (client->getPreference(animalERuleCliAttri[i]) == animal->getAttribute(animalERuleAniAttri[i]))
            num = 1;

        score->setAttriScore(animalERuleCliAttri[i], num);
    }
}

void MatchingControl::sScoreAnimal(Client *client, Animal *animal, Score *score)
{
    //use animal attribute field name when setting scores<---------------!!!

    score->setAttriScore("age", scoreSize(client->getPreference("age"), animal->getAttribute("age")));
    score->setAttriScore("budget", scoreBudget(client->getPreference("budget"), animal->getAttribute("budget")));
    if(curType == "Dog")
    {
        score->setAttriScore("size", scoreSize(client->getPreference("size"), animal->getAttribute("size")));
        score->setAttriScore("energetic", scoreEnergetic(client->getPreference("energetic"), animal->getAttribute("energetic")));
        score->setAttriScore("exercise", scoreExercise(client->getPreference("exercise"), animal->getAttribute("exercise"), "client"));
        //score->setAttriScore("vocality", scoreVocality(client->getPreference("vocality"), animal->getAttribute("vocality")));
        score->setAttriScore("shedding", scoreShedding(client->getPreference("shedding"), animal->getAttribute("shedding")));
        score->setAttriScore("coat_length", scoreShedding(client->getPreference("coat_length"), animal->getAttribute("coat_length")));
        score->setAttriScore("coat_layers", scoreCoatLayers(client->getPreference("coat_layers"), animal->getAttribute("coat_layers")));
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
        score->setAttriScore("weather", scoreWeather(client->getPreference("weather"), animal->getAttribute("weather")));
        score->setAttriScore("playful", scorePlayful(client->getPreference("playful"), animal->getAttribute("playful")));
        score->setAttriScore("intelligence", scoreIntelligence(client->getPreference("intelligence"), animal->getAttribute("intelligence")));
        score->setAttriScore("grooming", scoreGrooming(client->getPreference("grooming"), animal->getAttribute("grooming")));
        score->setAttriScore("good_new_owners", scoreFirstPet(client->getPreference("first_pet"), animal->getAttribute("good_new_owners")));
        score->setAttriScore("trainability", scoreTrainability(client->getPreference("trainability"), animal->getAttribute("trainability")));
        score->setAttriScore("affection_stranger", scoreAffectionStranger(client->getPreference("affection_stranger"), animal->getAttribute("affection_stranger")));
        score->setAttriScore("affection_owner", scoreAffectionStranger(client->getPreference("affection_owner"), animal->getAttribute("affection_owner")));
        score->setAttriScore("affection_family", scoreAffectionStranger(client->getPreference("affection_family"), animal->getAttribute("affection_family")));
        score->setAttriScore("attention", scoreAttention(client->getPreference("attention"), animal->getAttribute("attention")));
        score->setAttriScore("space", scoreDogSpace(client->getPreference("space"), animal->getAttribute("space")));
    }
    if(curType == "Cat")
    {
        score->setAttriScore("size", scoreSize(client->getPreference("size"), animal->getAttribute("size")));
        score->setAttriScore("energetic", scoreEnergetic(client->getPreference("energetic"), animal->getAttribute("energetic")));
        //score->setAttriScore("vocality", scoreVocality(client->getPreference("vocality"), animal->getAttribute("vocality")));
        score->setAttriScore("shedding", scoreShedding(client->getPreference("shedding"), animal->getAttribute("shedding")));
        score->setAttriScore("coat_length", scoreShedding(client->getPreference("coat_length"), animal->getAttribute("coat_length")));
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
        score->setAttriScore("weather", scoreWeather(client->getPreference("weather"), animal->getAttribute("weather")));
        score->setAttriScore("playful", scorePlayful(client->getPreference("playful"), animal->getAttribute("playful")));
        score->setAttriScore("intelligence", scoreIntelligence(client->getPreference("intelligence"), animal->getAttribute("intelligence")));
        score->setAttriScore("independent", scoreIndependent(client->getPreference("independent"), animal->getAttribute("independent")));
        score->setAttriScore("social", scoreSocial(client->getPreference("social"), animal->getAttribute("social")));
        score->setAttriScore("grooming", scoreGrooming(client->getPreference("grooming"), animal->getAttribute("grooming")));
        score->setAttriScore("good_new_owners", scoreFirstPet(client->getPreference("first_pet"), animal->getAttribute("good_new_owners")));
        score->setAttriScore("trainability", scoreTrainability(client->getPreference("trainability"), animal->getAttribute("trainability")));
        score->setAttriScore("affection_stranger", scoreAffectionStranger(client->getPreference("affection_stranger"), animal->getAttribute("affection_stranger")));
        score->setAttriScore("affection_owner", scoreAffectionStranger(client->getPreference("affection_owner"), animal->getAttribute("affection_owner")));
        score->setAttriScore("affection_family", scoreAffectionStranger(client->getPreference("affection_family"), animal->getAttribute("affection_family")));
        score->setAttriScore("space", scoreCatSpace(client->getPreference("space"), animal->getAttribute("space")));
    }
    if(curType == "Bird")
    {
        //score->setAttriScore("vocality", scoreVocality(client->getPreference("vocality"), animal->getAttribute("vocality")));
        score->setAttriScore("shedding", scoreShedding(client->getPreference("shedding"), animal->getAttribute("shedding")));
        score->setAttriScore("interactive", scoreInteractive(client->getPreference("interactive"), animal->getAttribute("interactive")));
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
        score->setAttriScore("weather", scoreWeather(client->getPreference("weather"), animal->getAttribute("weather")));
        score->setAttriScore("intelligence", scoreIntelligence(client->getPreference("intelligence"), animal->getAttribute("intelligence")));
    }
    if(curType == "Rabbit")
    {
        score->setAttriScore("social", scoreSocial(client->getPreference("social"), animal->getAttribute("social")));
        score->setAttriScore("sensitivity", scoreSensitivity(client->getPreference("sensitivity"), animal->getAttribute("sensitivity")));
        score->setAttriScore("temperament", scoreTemperament(client->getPreference("temperament"), animal->getAttribute("temperament")));
    }
    if(curType == "Hamster")
    {
        score->setAttriScore("feeding", scoreFeeding(client->getPreference("feeding"), animal->getAttribute("feeding"), "client"));
        score->setAttriScore("cleaning", scoreCleaning(client->getPreference("cleaning"), animal->getAttribute("cleaning")));
        score->setAttriScore("social", scoreSocial(client->getPreference("social"), animal->getAttribute("social")));
    }
    if(curType == "Guinea Pig")
    {
        score->setAttriScore("feeding", scoreFeeding(client->getPreference("feeding"), animal->getAttribute("feeding"), "client"));
        score->setAttriScore("cleaning", scoreCleaning(client->getPreference("cleaning"), animal->getAttribute("cleaning")));\
        score->setAttriScore("social", scoreSocial(client->getPreference("social"), animal->getAttribute("social")));
    }
}

void MatchingControl::sScoreClient(Animal *animal, Client *client, Score *score)
{
    //use client attribute field name when setting scores<---------------!!!

    if(curType == "Dog")
    {
        score->setAttriScore("exercise", scoreExercise(client->getPreference("exercise"), animal->getAttribute("exercise"), "animal"));
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
    }
    if(curType == "Cat")
    {
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
    }
    if(curType == "Bird")
    {
        score->setAttriScore("interactive", scoreInteractive(client->getPreference("interactive"), animal->getAttribute("interactive")));
        score->setAttriScore("vet_visits", scoreVetVisits(client->getPreference("vet_visits"), animal->getAttribute("vet_visits")));
    }
    if(curType == "Rabbit")
    {
        score->setAttriScore("sensitivity", scoreSensitivity(client->getPreference("sensitivity"), animal->getAttribute("sensitivity")));
    }
    if(curType == "Hamster")
    {
        score->setAttriScore("feeding", scoreFeeding(client->getPreference("feeding"), animal->getAttribute("feeding"), "animal"));
    }
    if(curType == "Guinea Pig")
    {
        score->setAttriScore("feeding", scoreFeeding(client->getPreference("feeding"), animal->getAttribute("feeding"), "animal"));
    }
}


float MatchingControl::scoreSize(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    QList<QString> level = {"Large", "Medium", "Small", "Tiny"};
    if(level.indexOf(pref)-level.indexOf(attri) > 1)
        return 0;
    else if(level.indexOf(pref)-level.indexOf(attri) == 1)
        return 0.5;
    else
        return 1;
}

float MatchingControl::scoreFeeding(QString pref, QString attri, QString from)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    //deltaMax can change based on animal type
    if(from == "client")
        return formula2(prefNum, attriNum, deltaMax);
    else
        return formula2(prefNum, attriNum, deltaMax, 0.5);
}

float MatchingControl::scoreAffectionStranger(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 4;
    return formula3(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreEnergetic(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 4;
    return formula1(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreExercise(QString pref, QString attri, QString from)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    if(from == "client")
        return formula2(prefNum, attriNum, deltaMax);
    else
        return formula2(prefNum, attriNum, deltaMax, 0.5);
}

float MatchingControl::scoreVocality(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    QList<QString> level = {"Infrequent", "Only when necessary", "Frequent", "Likes to be vocal"};
    float prefNum = level.indexOf(pref)+1;
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreAge(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    float prefNum = pref.toFloat(); //Not a number now
    float attriNum = attri.toFloat();
    float deltaMax = lifespan[curType];
    //deltaMax can change based on animal type
    return formula1(prefNum, attriNum, deltaMax, 2);
}

float MatchingControl::scoreShedding(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    QList<QString> level = {"Infrequent", "Ocassional", "Seasonal", "Regularly", "Frequent"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float deltaMax = 4;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreCoatLength(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    QList<QString> level = {"Short(less than 1 inch)", "Medium(1-3 inches)", "Long(more than 3 inches)"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float delta = qFabs(prefNum-attriNum);
    if(delta == 0)
        return 1;
    else if(delta == 1)
        return 0.5;
    else
        return 0;
}

float MatchingControl::scoreCoatLayers(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    QList<QString> level = {"1-Layer", "2-Layer", "Multi-Layer"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float delta = qFabs(prefNum-attriNum);
    if(delta == 0)
        return 1;
    else if(delta == 1)
        return 0.5;
    else
        return 0;
}

float MatchingControl::scoreTemperament(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
     QList<QString> level = {"headstrong", "docile", "calm", "aggressive"};
     float prefNum = level.indexOf(pref);
     float attriNum = level.indexOf(attri);
     float deltaMax = 3;
     return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreInteractive(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula1(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreCleaning(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreVetVisits(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    QList<QString> level = {"Yearly", "Half-Yearly", "Every 2 months", "Monthly"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float deltaMax = 3;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreWeather(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    QList<QString> level = {"Cold", "Moderate", "Hot"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float delta = qFabs(prefNum-attriNum);
    if(delta == 0)
        return 1;
    else if(delta == 1)
        return 0.5;
    else
        return 0;
}

float MatchingControl::scorePlayful(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula1(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreIntelligence(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula1(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreIndependent(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 4;
    return formula3(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreSocial(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 3;
    return formula1(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreSensitivity(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 4;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreGrooming(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    QList<QString> level = {"2-3 times/week", "Once a week", "Daily"};
    float prefNum = level.indexOf(pref);
    float attriNum = level.indexOf(attri);
    float deltaMax = 2;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreBudget(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 1000;
    return formula2(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreFirstPet(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    if(pref == "Yes" && attri == "No")
        return 1;
    else
        return 0;
}

float MatchingControl::scoreTrainability(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.17;
    QList<QString> level = {"Independent", "Docile(easy to train)", "Trained"};
    float prefNum = level.indexOf(pref)+1;
    float attriNum = attri.toFloat();
    float deltaMax = 1;
    return formula3(prefNum, attriNum, deltaMax);
}

float MatchingControl::scoreDogSpace(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    QList<QChar> alevel = {'A','S','L'};
    QList<QString> clevel = {"Apartment", "House with a small yard", "House with a large yard"};
    float prefNum = clevel.indexOf(pref);
    QList<float> attriNums;
    int i = 0;
    for(i=0; i<attri.size(); i++){
        attriNums.append(alevel.indexOf(attri[i]));
        if(prefNum == attriNums[i])
            return 1;
    }
    float deltaMax = 2;
    return formula3(prefNum, attriNums[i-1], deltaMax);
}

float MatchingControl::scoreCatSpace(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.5;
    if(attri == "O" && pref == "Indoor")
        return 0;
    else
        return 1;
}

float MatchingControl::scoreAttention(QString pref, QString attri)
{
    if(pref.isEmpty() || attri.isEmpty())
        return 0.25;
    float prefNum = pref.toFloat();
    float attriNum = attri.toFloat();
    float deltaMax = 4;
    return formula2(prefNum, attriNum, deltaMax);
}

inline float MatchingControl::formula1(float pref, float attri, float deltaMax, float factor)
{
    float delta = pref-attri;
    if(delta > deltaMax)
        return 0;
    else return 1-qPow(qFabs(delta)/deltaMax, factor);
}

inline float MatchingControl::formula2(float pref, float attri, float deltaMax, float factor)
{
    if(pref >= attri)
        return 1;
    float delta = attri-pref;
    if(delta > deltaMax)
        return 0;
    else return 1-qPow(delta/deltaMax, factor);
}

inline float MatchingControl::formula3(float pref, float attri, float deltaMax, float factor)
{
    if(attri >= pref)
        return 1;
    float delta = attri-pref;
    if(delta > deltaMax)
        return 0;
    else return 1-qPow(delta/deltaMax, factor);
}

void MatchingControl::compute()
{
    //build ranking table
    QList<QList<int>> ranking;
    int m, n;
    n = animals.size();
    m = clients.size();
    Animal *animal;
    Client *client;
    QList<int> aniIds;
    QList<int> cliIds;
    foreach(animal, animals)
    {
        aniIds.append(animal->getAttribute("id").toInt());
        QList<int> animalPref;
        for(int j=0; j<m; j++){            
            animalPref.append(animal->idRank(j));
        }
        ranking.append(animalPref);
    }
    foreach (client, clients)
    {
        cliIds.append(client->getPreference("id").toInt());
        QList<int> clientPref;
        for(int k=0; k<n; k++){
            clientPref.append(client->idRank(k));
        }
        ranking.append(clientPref);
    }
    QString line;
    for(int i=0; i<n+m; i++){
        for(int j=0; j<ranking[i].size(); j++)
            line += QString::number(ranking[i][j])+" ";
        //qDebug()<<line;
        line.clear();
    }

    //core algorithm
    int aniMatchedNum = 0;
    QList<int> curAdopteeIndexes;
    for(int i=0; i<m; i++)
        curAdopteeIndexes.append(-1);
    QList<int> aniIsMatched;
    for(int i=0; i<n; i++)
        aniIsMatched.append(0);
    while (aniMatchedNum<n)
    {
        int curAniIndex;
        for(curAniIndex=0; curAniIndex<n; curAniIndex++) {
            if (aniIsMatched[curAniIndex] == 0)
                break;
        }
        if (curAniIndex == n)
            break;
        int curCliIndex;
        for(curCliIndex=0; curCliIndex<m && aniIsMatched[curAniIndex]==0; curCliIndex++)
        {
            int preferedCliIndex = cliIds.indexOf(ranking[curAniIndex][curCliIndex]);
            if (curAdopteeIndexes[preferedCliIndex] == -1) {
                curAdopteeIndexes[preferedCliIndex] = curAniIndex;
                aniIsMatched[curAniIndex] = 1;
                ++aniMatchedNum;
            } else {
                int competitorAniIndex = curAdopteeIndexes[preferedCliIndex];
                //*compare ranking//
                bool preferNewAni = false;
                for (int i=0; i<n; i++)
                {
                    if (aniIds[competitorAniIndex] == ranking[preferedCliIndex+n][i]){
                        break;
                    }
                    if (aniIds[curAniIndex] == ranking[preferedCliIndex+n][i]){
                        preferNewAni = true;
                        break;
                    }
                }
                //compare ranking*//
                if(preferNewAni) {
                    curAdopteeIndexes[preferedCliIndex] = curAniIndex;
                    aniIsMatched[curAniIndex] = 1;
                    aniIsMatched[competitorAniIndex] = 0;
                }
            }
        }
        if (aniIsMatched[curAniIndex] == 0)
            aniIsMatched[curAniIndex] = -1;
        //qDebug()<<"loop";
    }

    //matching results
    if(m <= n)
    {
        //normal case
        for(int i=0; i<n; i++)
        {
            QList<int> pair;
            pair.append(aniIds[i]);
            pair.append(-1);
            matchingIdPairs.append(pair);
        }
        for(int i=0; i<m; i++)
        {
            matchingIdPairs[curAdopteeIndexes[i]][1] = cliIds[i];
        }
    }
    else
    {
        for(int i=0; i<m; i++)
        {
            QList<int> pair;
            pair.append(-1);
            pair.append(cliIds[i]);
            matchingIdPairs.append(pair);
        }
        for(int i=0; i<m; i++)
        {
            if(curAdopteeIndexes[i] != -1)
                matchingIdPairs[i][0] = aniIds[curAdopteeIndexes[i]];
        }
    }
    ///////////
    QList<int> pair;
    //qDebug() << '\t' << "animal" << '\t' << "client" << '\n';
    foreach (pair, matchingIdPairs) {
        //qDebug() << '\t' << pair[0] << '\t' << pair[1] << '\n';
    }
}

void MatchingControl::clean()
{
    Animal *animal;
    foreach (animal, animals) {
        delete animal;
    }
    animals.clear();

    Client *client;
    foreach (client, clients) {
        delete client;
    }
    clients.clear();
    matchingIdPairs.clear();
}

void MatchingControl::store()
{
    for(int i=0; i<matchingIdPairs.size(); i++)
    {
        int animalId = matchingIdPairs[i][0];
        int clientId = matchingIdPairs[i][1];
        float totalAniGet;
        float totalCliGet;
        if(clientId == -1 || animalId == -1)
            continue;
        Client *client = clients[clientId];
        Animal *animal = animals[animalId];
        Score *scoreOfAnimalFromClient = client->getScore(animalId);
        Score *scoreOfClientFromAnimal = animal->getScore(clientId);
        QHash<QString, QString> input;
        QHash<QString, float> *aniAttriScores;
        QHash<QString, float> *cliAttriScores;
        //animal
        aniAttriScores = scoreOfAnimalFromClient->getAttriScores();
        if((totalAniGet = scoreOfAnimalFromClient->getTotal()) < 0)
            continue;//refuse
        input["total_score_animal_get"] = QString::number(totalAniGet);
        input["animal_id"] = QString::number(scoreOfAnimalFromClient->getId());
        input["animal_name"] = animal->getAttribute("name");
        QHashIterator<QString, float> j(*aniAttriScores);
        while(j.hasNext())
        {
            j.next();
            input[j.key()+"_afc"] = QString::number(j.value());
        }
        //cleint
        cliAttriScores = scoreOfClientFromAnimal->getAttriScores();
        if((totalCliGet = scoreOfClientFromAnimal->getTotal()) < 0)
            continue;//refuse
        input["total_score_client_get"] = QString::number(totalCliGet);
        input["client_id"] = QString::number(scoreOfClientFromAnimal->getId());
        input["client_name"] = client->getPreference("name");
        QHashIterator<QString, float> k(*cliAttriScores);
        while(k.hasNext())
        {
            k.next();
            input[k.key()+"_cfa"] = QString::number(k.value());
        }

        QString errMsg;
        if(!dbControl->dbRequest(&input, NULL, WRITE_RESULT, &errMsg))
            QMessageBox::critical(NULL, "Database Error", errMsg);
    }
}
