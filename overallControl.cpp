#include "overallControl.h"

OverAllControl::OverAllControl()
{
    proxy = new Proxy;
}

OverAllControl::~OverAllControl()
{
    delete proxy;
}

void OverAllControl::launch()
{
    dbControl = new DatabaseControl;
    if (initializeDB())
        proxy->displayRequest();
}

void OverAllControl::initializeHelper(QHash<QString, QString> &hash, QString *fields, QString *data, int size, QString table)
{
    for(int i=0; i<size ;i++)
        hash[fields[i]] = data[i];
    QString errMsg;
    DBSettings settings;
    settings.table = table;
    if (!dbControl->dbRequest(&hash, NULL, &settings, WRITE, &errMsg))
        QMessageBox::critical(NULL,
                              QObject::tr("Database error"),
                              errMsg);
    hash.clear();
}

bool OverAllControl::initializeDB()
{
    if (!dbControl->openDB("cuACS_DB"))
        return false;

    bool hasTable;
    DBSettings settings;//dummy, used when setting fields
    QHash<QString, QString> input;

    input["results"] = "(matching_id integer not null primary key, "
                       "client_id integer not null, "
                       "client_name varchar not null,"
                       "total_score_client_get float not null, "
                       "animal_id integer not null, "
                       "animal_name varchar not null, "
                       "total_score_animal_get float not null,"
                       "details char(4) default 'More', "
                       "type_afc varchar,"
                       "breed_afc varchar,"
                       "gender_afc varchar, "
                       "size_afc varchar, "
                       "age_afc varchar,"
                       "weight_afc double,"
                       "expected_life_span_afc varchar,"
                       "colour_afc varchar,"
                       "coat_pattern_afc varchar,"
                       "coat_length_afc varchar, "
                       "coat_layers_afc varchar,"
                       "shedding_afc varchar default null,"
                       "hypoallergenic_afc varchar,"
                       "good_new_owners_afc varchar,"
                       "good_with_being_alone_afc varchar,"
                       "kid_friendly_afc varchar,"
                       "vocality_afc varchar,"
                       "trainability_afc varchar,"
                       "playful_afc varchar,"
                       "energetic_afc varchar,"
                       "intelligence_afc varchar,"
                       "good_other_pets_afc varchar default null,"
                       "affection_owner_afc varchar,"
                       "affection_family_afc varchar,"
                       "affection_stranger_afc varchar,"
                       "budget_afc double,"
                       "special_needs_afc varchar,"
                       "dietary_afc varchar,"
                       "vet_visits_afc varchar,"
                       "grooming_afc varchar,"
                       "weather_afc varchar,"
                       "attention_afc varchar,"
                       "exercise_afc varchar,"
                       "space_afc varchar default null,"
                       "independent_afc varchar default null,"
                       "social_afc varchar default null,"
                       "pair_afc varchar default null,"
                       "interactive_afc varchar default null,"
                       "temperament_afc varchar default null,"
                       "tamed_afc varchar default null,"
                       "sensitivity_afc varchar default null,"
                       "nocturnal_afc varchar default null,"
                       "feeding_afc varchar default null,"
                       "cleaning_afc varchar default null,"////////
                       "space_cfa varchar,"
                       "weather_cfa varchar,"
                       "at_home_mostly_cfa varchar,"
                       "allergies_cfa varchar,"
                       "pair_cfa varchar,"
                       "first_pet_cfa varchar,"
                       "kids_cfa varchar,"
                       "budget_cfa double,"
                       "breed_cfa varchar,"
                       "gender_cfa varchar,"
                       "size_cfa varchar,"
                       "age_cfa varchar,"
                       "colour_cfa varchar,"
                       "shedding_cfa varchar,"
                       "grooming_cfa varchar,"
                       "dietary_needs_cfa varchar,"
                       "special_needs_cfa varchar,"
                       "vet_visits_cfa varchar,"
                       "other_pets_cfa varchar,"
                       "attention_cfa varchar,"
                       "energetic_cfa varchar,"
                       "trainability_cfa varchar,"
                       "intelligence_cfa varchar,"
                       "exercise_cfa varchar,"
                       "vocality_cfa varchar,"
                       "playful_cfa varchar,"
                       "affection_owner_cfa varchar,"
                       "affection_family_cfa varchar,"
                       "affection_stranger_cfa varchar)";
    if(!dbControl->dbRequest(&input, NULL, &settings, CREATE_TABLE, NULL))
           QMessageBox::critical(NULL, "Database Error", "Fail to create table");
    input.clear();

    input["users"] = "(id integer not null primary key autoincrement, "
                     "username varchar not null unique, "
                     "password varchar not null, "
                     "role varchar not null)";
    if(!dbControl->dbRequest(&input, &hasTable, &settings, CREATE_TABLE, NULL))
            QMessageBox::critical(NULL, "Database Error", "Fail to create table");
        //hasTable = true;
    input.clear();
    if(!hasTable)
    {
        QString usersFields[4] = {"id", "username", "password", "role"};
        QString usersData1[4] = {"1","Joe", "joe", "client"};
        QString usersData2[4] = {"2","Lars", "lars", "client"};
        QString usersData3[4] = {"3","Leo", "leo", "client"};
        QString usersData4[4] = {"4","Lora", "lora", "client"};
        QString usersData5[4] = {"5","Jacob", "jacob", "client"};
        QString usersData6[4] = {"6","Jonathan", "jonathan", "client"};
        QString usersData7[4] = {"7","Sam", "sam", "client"};
        QString usersData8[4] = {"8","Tony", "tony", "client"};
        QString usersData9[4] = {"9","Chandler", "chandler", "client"};
        QString usersData10[4] = {"10","Monica", "monica", "client"};
        QString usersData11[4] = {"11","Rachel", "rachel", "client"};
        QString usersData12[4] = {"12","Phoebe", "phoebe", "client"};
        QString usersData13[4] = {"13","Sammie", "sammie", "client"};
        QString usersData14[4] = {"14","Charles", "charles", "client"};
        QString usersData15[4] = {"15","Chen", "chen", "client"};
        QString usersData16[4] = {"16","Jamaica", "jamaica", "client"};
        QString usersData17[4] = {"17","Sally", "sally", "client"};
        QString usersData18[4] = {"18","Jonas", "jonas", "client"};
        QString usersData19[4] = {"19","Joseph", "joseph", "client"};
        QString usersData20[4] = {"20","Lily", "lily", "client"};
        QString staffData1[4] = {"21","matilda23", "matilda23", "staff"};
        initializeHelper(input, usersFields, usersData1, 4, "users");
        initializeHelper(input, usersFields, usersData2, 4, "users");
        initializeHelper(input, usersFields, usersData3, 4, "users");
        initializeHelper(input, usersFields, usersData4, 4, "users");
        initializeHelper(input, usersFields, usersData5, 4, "users");
        /*initializeHelper(input, usersFields, usersData6, 4, "users");
        initializeHelper(input, usersFields, usersData7, 4, "users");
        initializeHelper(input, usersFields, usersData8, 4, "users");
        initializeHelper(input, usersFields, usersData9, 4, "users");
        initializeHelper(input, usersFields, usersData10, 4, "users");
        initializeHelper(input, usersFields, usersData11, 4, "users");
        initializeHelper(input, usersFields, usersData12, 4, "users");
        initializeHelper(input, usersFields, usersData13, 4, "users");
        initializeHelper(input, usersFields, usersData14, 4, "users");
        initializeHelper(input, usersFields, usersData15, 4, "users");
        initializeHelper(input, usersFields, usersData16, 4, "users");
        initializeHelper(input, usersFields, usersData17, 4, "users");
        initializeHelper(input, usersFields, usersData18, 4, "users");
        initializeHelper(input, usersFields, usersData19, 4, "users");
        initializeHelper(input, usersFields, usersData20, 4, "users");*/
        initializeHelper(input, usersFields, staffData1, 4, "users");
    }

    input["animals"] = "(id integer primary key ,"
                     "name varchar not null,"
                     "type varchar,"
                     "breed varchar,"
                     "gender varchar, "
                     "size integer, "
                     "age integer,"
                     "weight double,"
                     "expected_life_span varchar,"
                     "colour varchar,"
                     "coat_pattern varchar,"
                     "coat_length varchar, "
                     "coat_layers varchar,"
                     "shedding varchar default null,"
                     "hypoallergenic varchar,"
                     "good_new_owners varchar,"
                     "good_with_being_alone varchar,"
                     "kid_friendly varchar,"
                     "vocality varchar,"
                     "trainability varchar,"
                     "playful integer,"
                     "energetic integer,"
                     "intelligence integer,"
                     "good_other_pets varchar default null,"
                     "affection_owner integer,"
                     "affection_family integer,"
                     "affection_stranger integer,"
                     "budget double,"
                     "special_needs varchar,"
                     "dietary varchar,"
                     "vet_visits varchar,"
                     "grooming varchar,"
                     "weather varchar,"
                     "attention integer,"
                     "exercise integer,"
                     "space varchar default null,"
                     "independent integer default null,"
                     "social integer default null,"
                     "pair varchar default null,"
                     "interactive integer default null,"
                     "temperament varchar default null,"
                     "tamed varchar default null,"
                     "sensitivity integer default null,"
                     "nocturnal varchar default null,"
                     "feeding integer default null,"
                     "cleaning integer default null,"
                     "details char(4) default 'More')";
    if(!dbControl->dbRequest(&input, &hasTable, &settings, CREATE_TABLE, NULL))
        hasTable = true;
    input.clear();
    if(!hasTable)
    {

        QString dogFields[ATTRIBUTES_NUM_DOG] = {"name","type","breed","gender","size","age","weight","expected_life_span","colour","coat_length",
                                   "coat_layers","shedding","hypoallergenic","good_new_owners","good_with_being_alone","kid_friendly","vocality",
                                   "trainability","playful","energetic","intelligence","good_other_pets","affection_owner","affection_family",
                                   "affection_stranger","budget","special_needs","dietary","vet_visits","grooming","weather","attention","exercise","space"};
        QString dog_data1[ATTRIBUTES_NUM_DOG] = {"Pooh","Dog","Beagle","Female","Small","1","15","12-15","Brown","Short(less than 1 inch)",
                                                 "1-Layer","Infrequent","No","Yes","No","Yes","Likes to be vocal",
                                                 "Trained","4","4","4","DBHRG","5","5",
                                                 "3","700","Yes","No","Monthly","Once a week","Hot","3","5","SL"};
        QString dog_data2[ATTRIBUTES_NUM_DOG]= {"Bowie","Dog","Siberian","Male","Large","7","89.6","11-14","Brown","Medium(1-3 inches)",
                                                "1-Layer","Frequent","No","Yes","No","Yes","Likes to be vocal",
                                                "Docile(easy to train)","5","5","5","DCBRHG","5","5",
                                                "4","600","No","Yes","Every 2 months","Once a week","Moderate","5","5","L"};
        QString dog_data3[ATTRIBUTES_NUM_DOG] = {"QTPie","Dog","Poodle","Female","Large","2","70.3","12-15","Grey","Medium(1-3 inches)",
                                                 "1-Layer","Regularly","Yes","No","No","Yes","Infrequent",
                                                 "Trained","4","3","4","DBC","5","4",
                                                 "4","1100","Yes","Yes","Half-Yearly","Daily","Moderate","4","4","SL"};
        QString dog_data4[ATTRIBUTES_NUM_DOG] = {"Peirce","Dog","St. Bernard","Male","Large","3","93.2","13-16","White",
                                                 "Medium(1-3 inches)","2-Layer","Seasonal","Yes","No","Yes","Yes",
                                                 "Only when necessary","Trained","4","4","5","RD","4","4","3",
                                                 "1100","Yes","No","Half-Yearly","Daily","Cold","4","5","L"};
        QString dog_data5[ATTRIBUTES_NUM_DOG] = {"Percy","Dog","St. Bernard","Male","Large","2","68.4","12-13","White",
                                                 "Medium(1-3 inches)","1-Layer","Regularly","No","No","No","No","Frequent",
                                                 "Agreeable","5","5","5","DGCBRH","5","5","3","600","No","Yes","Every 2 months",
                                                 "Daily","Moderate","5","5","L"};
        QString dog_data6[ATTRIBUTES_NUM_DOG] = {"Jack","Dog","Alaskan Malamute","Male","Large","7","141.06","8-10","Brown",
                                                 "Short(less than 1 inch)","1-Layer","Frequent","Yes","Yes","No","Yes",
                                                 "Only when necessary","Trained","3","3","4","DC","4","4","4","1250","No",
                                                 "No","Monthly","2-3 times/week","Moderate","2","5","SL"};
        QString dog_data7[ATTRIBUTES_NUM_DOG] = {"Walley","Dog","Pug","Female","Medium","8","68.4","12-15","White","Short(less than 1 inch",
                                                 "2-Layer","Regularly","No","No","Yes","Yes","Only when necessary",
                                                 "Trained","3","5","5","BHGC","5","4",
                                                 "2","1500","No","Yes","Yearly","Daily","Cold","5","5","L"};
        QString dog_data8[ATTRIBUTES_NUM_DOG] = {"Shadow","Dog","German Shepherd","Male","Large","4","89.03","9-13","Black",
                                                 "Short(less than 1 inch)","1-Layer","Infrequent","Yes","No","No","Yes",
                                                 "Frequent","Trained","3","5","5","B","5","3","1","700","Yes","No",
                                                 "Half-Yearly","Once a week","Moderate","2","4","L" };
        QString dog_data9[ATTRIBUTES_NUM_DOG] = {"Snowy","Dog","Pomeranian","Female","Small","6","7.8","12-18","White",
                                                 "Medium(1-3 inches)","1-Layer","Frequent","Yes","Yes","Yes","Yes",
                                                 "Likes to be Vocal","Docile(easy to train)","5","5","3",
                                                 "DBCH","5","5","4","900","No","No","Every 2 months","2-3 times/week",
                                                 "Moderate","4","4","ASL"};
        QString dog_data10[ATTRIBUTES_NUM_DOG] = {"Bosco","Dog","German Shepherd","Female","Small","3","19.6","12-15","White","Short(less than 1 inch)",
                                                  "1-Layer","Infrequent","No","No","Yes","Yes","Only when necessary","Trained",
                                                  "5","3","2","CDGH","5","5","5","900","No","Yes","Half-Yearly",
                                                  "Once a week","Moderate","3","4","ASL"};
        initializeHelper(input, dogFields, dog_data1, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data2, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data3, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data4, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data5, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data6, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data7, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data8, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data9, ATTRIBUTES_NUM_DOG, "animals");
        initializeHelper(input, dogFields, dog_data10, ATTRIBUTES_NUM_DOG, "animals");

        QString catFields[ATTRIBUTES_NUM_CAT] = {"name","type","breed","gender","size","age","weight","expected_life_span","colour","coat_length",
                                                 "coat_pattern","shedding","hypoallergenic","good_new_owners","kid_friendly","vocality",
                                                 "trainability","independent","playful","energetic","intelligence","good_other_pets","affection_owner","affection_family",
                                                 "affection_stranger","budget","special_needs","dietary","vet_visits","grooming","weather","attention","space","social","pair"};
        QString cat_data1[ATTRIBUTES_NUM_CAT] = {"Murphy","Cat","Abyssinian","Female","Medium","3","15.0","6-8","White","Short(less than 1 inch)",
                                                  "Solid(1-Colour)","Infrequent","No","Yes","Yes","Infrequent",
                                                  "Docile","5","3","4","5","C","3","2",
                                                  "1","400","No","No","Half-Yearly","Once a week","Moderate","2","I","2","No"};
        QString cat_data2[ATTRIBUTES_NUM_CAT] = {"Sky","Cat","American Curl","Female","Medium","3","18","2-8","White","Short(less than 1 inch)",
                                                  "Bi-colour","Infrequent","No","No","Yes","Infrequent",
                                                  "Independent","5","4","3","5","C","3","3",
                                                  "2","410","No","No","Half-Yearly","Once a week","Moderate","2","O","1","No"};
        QString cat_data3[ATTRIBUTES_NUM_CAT] = {"Ivy","Cat","Persian","Female","Small","2","19","6-9","Golden Brown","Short(less than 1 inch)",
                                                  "Stripped Tabby","Frequent","No","Yes","No","Infrequent",
                                                  "Independent","5","5","5","5","C","3","2",
                                                  "1","500","No","No","Every 2 months","Once a week","Cold","2","IO","3","No"};
        QString cat_data4[ATTRIBUTES_NUM_CAT] = {"Garfield","Cat","Siamese","Male","Medium","1","14","8-10","Grey","Medium(1-3 inches)",
                                                  "Solid(1-colour)","Regularly","No","No","Yes","Infrequent",
                                                  "Independent","5","2","5","5","C","3","3",
                                                  "2","600","No","No","Half-Yearly","Once a week","Hot","3","I","2","No"};
        QString cat_data5[ATTRIBUTES_NUM_CAT] = {"Joana","Cat","Highlander","Female","Small","4","10","5-8","Chocolate Brown","Medium(1-3 inches)",
                                                  "Calico(3-colour)","Ocassional","No","Yes","No","Infrequent",
                                                  "Independent","5","5","5","5","C","3","3",
                                                  "2","450","No","No","Every 2 months","Once a week","Moderate","2","I","3","No"};
        QString cat_data6[ATTRIBUTES_NUM_CAT] = {"Tom","Cat","Savannah","Male","Medium","2","8","6-9","Black","Medium(1-3 inches)",
                                                  "Tortoiseshell","Seasonal","No","No","Yes","Likes to be vocal",
                                                  "Independent","5","3","5","5","C","4","3",
                                                  "2","430","No","No","Half-Yearly","Once a week","Hot","3","O","2","No"};
        initializeHelper(input, catFields, cat_data1, ATTRIBUTES_NUM_CAT, "animals");
        initializeHelper(input, catFields, cat_data2, ATTRIBUTES_NUM_CAT, "animals");
        initializeHelper(input, catFields, cat_data3, ATTRIBUTES_NUM_CAT, "animals");
        initializeHelper(input, catFields, cat_data4, ATTRIBUTES_NUM_CAT, "animals");
        initializeHelper(input, catFields, cat_data5, ATTRIBUTES_NUM_CAT, "animals");
        initializeHelper(input, catFields, cat_data6, ATTRIBUTES_NUM_CAT, "animals");

        QString birdFields[ATTRIBUTES_NUM_BIRD] = {"name","type","breed","gender","size","age","dietary","pair","weather","budget","colour","special_needs",
                                 "vet_visits","expected_life_span","vocality","shedding","interactive","intelligence"};
        QString bird_data1[ATTRIBUTES_NUM_BIRD] = {"Nancy","Bird","Dove","Female","Tiny","1","Yes","No","Hot","200","White",
                                                   "No","Yearly","4-8","Infrequent","Occationaly","4","3"};
        QString bird_data2[ATTRIBUTES_NUM_BIRD] = {"Nona","Bird","Parrot","Female","Medium","2","Yes","No","Hot","150","Green","No",
                                                   "Yearly","3-8","Likes to be vocal","Occationaly","5","5"};
        QString bird_data3[ATTRIBUTES_NUM_BIRD] = {"Meethu","Bird","Mynah","Female","Tiny","1","Yes","No","Hot","175","Blue","No",
                                                   "Yearly","4-7","Frequent","Occationaly","2","4"};
        QString bird_data4[ATTRIBUTES_NUM_BIRD] = {"Stella","Bird","Conures","Female","Small","1","Yes","No","Hot","125","Blue","No",
                                                   "Yearly","2-6","Frequent","Occationaly","3","3"};
        QString bird_data5[ATTRIBUTES_NUM_BIRD] = {"Gypsy","Bird","Canaries","Female","Tiny","2","Yes","No","Moderate","300","Yellow","No",
                                                   "Yearly","8-12","Frequent","Occationaly","3","4"};
        initializeHelper(input, birdFields, bird_data1, ATTRIBUTES_NUM_BIRD, "animals");
        initializeHelper(input, birdFields, bird_data2, ATTRIBUTES_NUM_BIRD, "animals");
        initializeHelper(input, birdFields, bird_data3, ATTRIBUTES_NUM_BIRD, "animals");
        initializeHelper(input, birdFields, bird_data4, ATTRIBUTES_NUM_BIRD, "animals");
        initializeHelper(input, birdFields, bird_data5, ATTRIBUTES_NUM_BIRD, "animals");

        QString rabbitFields[ATTRIBUTES_NUM_RABBIT] = {"name","type","gender","breed","colour","temperament","age","budget","expected_life_span","tamed",
                                   "hypoallergenic","good_other_pets","social","sensitivity"};
        QString rabbit_data1[ATTRIBUTES_NUM_RABBIT] = {"Stuart","Rabbit","Male","Lionhead","Brown","Docile","1","400","2-4","Yes",
                                                       "No","DCBRHG","3","3"};
        QString rabbit_data2[ATTRIBUTES_NUM_RABBIT] = {"Ruby","Rabbit","Female","Angora","White","Calm","1","400","2-4","Yes",
                                                       "No","DCBRHG","5","5"};
        initializeHelper(input, rabbitFields, rabbit_data1, ATTRIBUTES_NUM_RABBIT, "animals");
        initializeHelper(input, rabbitFields, rabbit_data2, ATTRIBUTES_NUM_RABBIT, "animals");

        QString hamsterFields[ATTRIBUTES_NUM_HAMSTER] = {"name","type","gender","breed","colour","age","budget","hypoallergenic",
                                   "expected_life_span","nocturnal","tamed","social","attention","cleaning","feeding"};

        QString hamster_data1[ATTRIBUTES_NUM_HAMSTER] = {"Joe","Hamster","Female","Syrian","Brown","1","200","Yes",
                                                         "1-3","Yes","Yes","5","5","4","4"};

        initializeHelper(input, hamsterFields, hamster_data1, ATTRIBUTES_NUM_HAMSTER, "animals");

        QString guineaPigFields[ATTRIBUTES_NUM_GUINEA_PIGS] = {"name","type","gender","breed","colour","age","budget","hypoallergenic",
                                   "expected_life_span","tamed","social","attention","cleaning","feeding"};


        QString guineaPig_data1[ATTRIBUTES_NUM_GUINEA_PIGS] = {"Jim","Guinea Pig","Female","Teddy","Chocolate","3","250","Yes",
                                                               "4-8","Yes","4","4","5","5"};

        initializeHelper(input, guineaPigFields, guineaPig_data1, ATTRIBUTES_NUM_GUINEA_PIGS, "animals");
    }


    input["clients"] = "(id integer not null primary key autoincrement,"
                           "name varchar not null unique, "
                           "phone_number varchar not null, "
                           "email varchar not null,"
                           "animal_type varchar,"
                           "space varchar,"
                           "weather varchar,"
                           "at_home_mostly varchar,"
                           "allergies varchar,"
                           "first_pet varchar,"
                           "kids varchar,"
                           "budget double,"
                           "breed varchar,"
                           "gender varchar,"
                           "size varchar,"
                           "age varchar,"
                           "colour varchar,"
                           "shedding varchar,"
                           "grooming varchar,"
                           "dietary_needs varchar,"
                           "special_needs varchar,"
                           "vet_visits varchar,"
                           "coat_length varchar,"
                           "other_pets varchar,"
                           "attention integer,"
                           "energetic integer,"
                           "trainability integer,"
                           "intelligence integer,"
                           "exercise integer,"
                           "vocality integer,"
                           "playful integer,"
                           "affection_owner integer,"
                           "affection_family integer,"
                           "affection_stranger integer,"
                           "pair varchar,"
                           "coat_pattern varchar,"
                           "social integer,"
                           "independent integer,"
                            "interactive integer,"
                            "tamed varchar,"
                            "temperament integer,"
                            "sensitivity integer,"
                            "nocturnal varchar,"
                            "cleaning integer,"
                            "feeding integer,"
                            "details char(4) default 'More')";
    if(!dbControl->dbRequest(&input, &hasTable, &settings, CREATE_TABLE, NULL))
        hasTable = true;
    input.clear();
    if(!hasTable)
    {
        QString clientFields[ATTRIBUTES_NUM_CLIENT] = {"id","name","phone_number","email","animal_type","space",
                                                              "weather","at_home_mostly","allergies","first_pet","kids",
                                                              "budget","breed","gender","size","age","colour","shedding",
                                                              "grooming","dietary_needs","special_needs","vet_visits",
                                                               "other_pets","attention","energetic","trainability","intelligence",
                                                              "exercise", "vocality","playful","affection_owner",
                                                              "affection_family","affection_stranger"};



                QString clientData1[ATTRIBUTES_NUM_CLIENT] = {"1","Joe", "3423629617", "joe682@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","Yes","Yes","Yes","600","German Shepherd","Male",
                                                              "Small","4","White","Infrequent","Daily",
                                                              "Yes","No","Monthly","HGD","4","3","2","4","2","4","3","2","4","2"};

                QString clientData2[ATTRIBUTES_NUM_CLIENT] = {"4","Jonathan", "6473629897", "jonathan@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pomeranian","Female",
                                                              "Small","2","White","Infrequent","Daily",
                                                              "No","No","Monthly","RG","4","3","2","4","2","4","3","2","4","2"};

                QString clientData3[ATTRIBUTES_NUM_CLIENT] = {"3","Leo", "3423678997", "samantha@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","Yes","Yes","No","600","Alaskan Malamute","Male",
                                                              "Small","1","White","Infrequent","Daily",
                                                              "No","Yes","Monthly","CBR","4","3","2","4","2","4","3","2","4","2"};


                QString clientData4[ATTRIBUTES_NUM_CLIENT] = {"2","Lars", "3423629897", "jack482@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","6","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","BC","4","3","2","4","2","4","3","2","4","2"};


                QString clientData5[ATTRIBUTES_NUM_CLIENT] = {"5","Jacob", "7899629897", "joey@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","No","600","Alaskan Malamute","Male",
                                                              "Small","1","White","Infrequent","Daily",
                                                              "Yes","No","Monthly","BR","4","3","2","4","2","4","3","2","4","2"};


                QString clientData6[ATTRIBUTES_NUM_CLIENT] =  {"6","Lily", "3423629897", "lily@cmail.carleton.ca","Dog",
                                                               "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                               "Small","5","White","Infrequent","Daily",
                                                               "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData7[ATTRIBUTES_NUM_CLIENT] = {"7","Sam", "2133627897", "sam@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Labrador","Male",
                                                              "Small","6","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CRBD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData8[ATTRIBUTES_NUM_CLIENT] = {"8","Tony", "6893629851", "tony82@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Female",
                                                              "Small","3","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CBD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData9[ATTRIBUTES_NUM_CLIENT] = {"9","Chandler", "3424536298", "chandler16@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","5","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","C","4","3","2","4","2","4","3","2","4","2"};


                QString clientData10[ATTRIBUTES_NUM_CLIENT] = {"10","Monica", "3423629897", "monica2@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Female",
                                                              "Small","9","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CH","4","3","2","4","2","4","3","2","4","2"};


                QString clientData11[ATTRIBUTES_NUM_CLIENT] = {"11","Rachel", "4563629897", "rachel482@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","2","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData12[ATTRIBUTES_NUM_CLIENT] = {"12","Phoebe", "3424536298", "phoebe482@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","4","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData13[ATTRIBUTES_NUM_CLIENT] = {"13","Sammie", "3423629897", "sammie2@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","5","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData14[ATTRIBUTES_NUM_CLIENT] = {"14","Charles", "3423629897", "charles3@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","1","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData15[ATTRIBUTES_NUM_CLIENT] = {"15","Chen", "3423629897", "chen7@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","7","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData16[ATTRIBUTES_NUM_CLIENT] = {"16","Jamaica", "3423629897", "jamaica32@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","7","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData17[ATTRIBUTES_NUM_CLIENT] = {"17","Sally", "3423629897", "sally@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","5","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData18[ATTRIBUTES_NUM_CLIENT] = {"18","Jonas", "3423629897", "jonas21@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","4","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData19[ATTRIBUTES_NUM_CLIENT] = {"19","Joseph", "3423629897", "joseph23@cmail.carleton.ca","Dog",
                                                              "Appartment","Hot","Yes","No","Yes","Yes","600","Pug","Male",
                                                              "Small","7","White","Infrequent","Daily",
                                                              "Yes","Yes","Monthly","CD","4","3","2","4","2","4","3","2","4","2"};


                QString clientData20[ATTRIBUTES_NUM_CLIENT] = {"20","Lora", "6457629897", "samuel@cmail.carleton.ca","Cat",
                                                               "Appartment","Hot","Yes","No","Yes","No","600","Siamese","Male",
                                                               "Small","6","White","Infrequent","Daily",
                                                               "No","Yes","Monthly","DCBRHG","4","3","2","4","2","4","3","2","4","2"};
                initializeHelper(input, clientFields, clientData1, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData2, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData3, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData4, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData5, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData6, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData7, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData8, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData9, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData10, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData11, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData12, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData13, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData14, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData15, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData16, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData17, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData18, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData19, ATTRIBUTES_NUM_CLIENT, "clients");
                initializeHelper(input, clientFields, clientData20, ATTRIBUTES_NUM_CLIENT, "clients");
    }

    return true;
}
