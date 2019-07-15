#include "addAnimalDialog.h"
#include "ui_addAnimalDialog.h"

AddAnimalDialog::AddAnimalDialog(QWidget *parent) :
    Subject(parent),
    ui(new Ui::AddAnimalDialog)
{
    typecounter = 0;
    update = false;
    ui->setupUi(this);
    ui->update_Button->hide();
    ui->edit_Button->hide();
    dbControl = new StaffDatabaseControl;
    //ui->animal_Characteristics->hide();
    //connect(ui->type_comboBox,SIGNAL(activated(int)),ui->animal_Characteristics,SLOT(show()));

    ui->animal_Characteristics->setCurrentIndex(0);
    ui->dog_characteristics_tab->setCurrentIndex(0);
    ui->cat_characteristics_tab->setCurrentIndex(0);
    connect(ui->animal_type,SIGNAL(currentIndexChanged(int)),ui->animal_Characteristics,SLOT(setCurrentIndex(int)));
}

AddAnimalDialog::AddAnimalDialog(int row, int num, QString* attr, QWidget *parent, int animal_type, int user_type, bool readOnly) :
    rowNum(row),
    Subject(parent),
    ui(new Ui::AddAnimalDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget:disabled{color: black}");
    ui->saveButton->hide();
    ui->edit_Button->hide();
    dbControl = new StaffDatabaseControl;
    ui->dog_characteristics_tab->setCurrentIndex(0);
    ui->cat_characteristics_tab->setCurrentIndex(0);
    ui->animal_Characteristics->setCurrentIndex(animal_type);
    ui->animal_type->setDisabled(true);

    if(readOnly)
    {
        if(user_type ==0)
        {
            ui->edit_Button->show();
        }
        ui->cancelButton->hide();
        ui->resetButton->hide();
        ui->update_Button->hide();
                      switch(animal_type)
                       {
                           case 1:
                                 {
                                    QList<QWidget *> widgets;
                                    widgets = ui->basic->findChildren<QWidget *>();

                                        foreach(QWidget* widget, widgets)
                                        {

                                            widget->setDisabled(true);
                                    //qDebug()<<widget;
                                            //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                             }

                                        widgets = ui->tab_2->findChildren<QWidget *>();

                                            foreach(QWidget* widget, widgets)
                                            {

                                                widget->setDisabled(true);
                                        //qDebug()<<widget;
                                                //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                                 }
                                            widgets = ui->tab_3->findChildren<QWidget *>();

                                                foreach(QWidget* widget, widgets)
                                                {

                                                    widget->setDisabled(true);
                                            //qDebug()<<widget;
                                                    //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                                     }


                                    }
                           break;
                      case 2:
                      {
                          QList<QWidget *> widgets;
                          widgets = ui->tab_4->findChildren<QWidget *>();

                              foreach(QWidget* widget, widgets)
                              {

                                  widget->setDisabled(true);
                          //qDebug()<<widget;
                                  //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                   }

                              widgets = ui->tab_5->findChildren<QWidget *>();

                                  foreach(QWidget* widget, widgets)
                                  {

                                      widget->setDisabled(true);
                              //qDebug()<<widget;
                                      //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                       }
                                  widgets = ui->tab_6->findChildren<QWidget *>();

                                      foreach(QWidget* widget, widgets)
                                      {

                                          widget->setDisabled(true);
                                  //qDebug()<<widget;
                                          //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                           }
                      }
                          break;
                           default:
                      {
                          QList<QWidget *> widgets = this->findChildren<QWidget *>();

                                                foreach(QWidget* widget, widgets)
                                                {

                                                    widget->setDisabled(true);
                                                        //qDebug()<<widget;
                                                  //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                                                }
                                                if(user_type ==0)
                                                {
                                                    ui->edit_Button->setEnabled(true);
                                                }

                      }
                           break;
                       }

    }

   switch(animal_type)
    {
        case 1:
            setDogView(attr);
        break;
        case 2:
            setCatView(attr);
        break;
        case 3:
            setBirdView(attr);
        break;
        case 4:
            setRabbitView(attr);
        break;
        case 5:
            setHamsterView(attr);
        break;
        case 6:
            setGuineaPigView(attr);
        break;

        default:
            //qDebug()<<"default case throw error here";
        break;
    }
}



AddAnimalDialog::~AddAnimalDialog()
{
    delete ui;
    delete dbControl;
}

void AddAnimalDialog::setBreed()
{

}



void AddAnimalDialog::clearFields()
{
    this->ui->animal_type->setCurrentIndex(0);
}

void AddAnimalDialog::addDog(QHash<QString, QString> &input)
{
    QString otherPets = "";
    QString space = "";
    input[QString("name")] = ui->dog_name->text();
    input[QString("type")] = "Dog";
    input[QString("breed")] = ui->dog_breed->currentText();
    input[QString("gender")] = ui->dog_gender->currentText();
    input[QString("size")] = ui->dog_size->currentText();
    input[QString("age")] = ui->dog_age->text();
    input[QString("weight")] = ui->dog_weight->text();
    input[QString("expected_life_span")] = ui->dog_expected_life_span->text();
    input[QString("colour")] = ui->dog_coat_colour->currentText();
    input[QString("coat_length")] = ui->dog_coat_length->currentText();
    input[QString("coat_layers")] = ui->dog_coat_layers->currentText();
    input[QString("shedding")] = ui->dog_shedding->currentText();
    if(ui->dog_hypoallergenic_yes->isChecked())
        input[QString("hypoallergenic")] = "Yes";
    else
        input[QString("hypoallergenic")] = "No";
    input[QString("good_new_owners")] = ui->dog_novice_owners->currentText();
    input[QString("good_with_being_alone")] = ui->dog_being_alone->currentText();
    input[QString("kid_friendly")] = ui->dog_kid_friendly->currentText();
    input[QString("vocality")] = ui-> dog_vocality->currentText();
    input[QString("trainability")] = ui->dog_trainability->currentText();
    input[QString("playful")] = ui->dog_playful->text();
    input[QString("energetic")] = ui->dog_energetic->text();
    input[QString("intelligence")] = ui->dog_intelligence->text();
    /*
     * other pets basically stores the first letter of the type of animal selected
     * as being compatible with the current animal who's profile is being set up
    */
    if(ui->dog_dog->isChecked())
        otherPets +="D";
    if(ui->dog_cat->isChecked())
        otherPets +="C";
    if(ui->dog_bird->isChecked())
        otherPets +="B";
    if(ui->dog_rabbit->isChecked())
        otherPets +="R";
    if(ui->dog_hamster->isChecked())
        otherPets +="H";
    if(ui->dog_guineaPig->isChecked())
        otherPets +="G";
    //qDebug()<<"other pets"+otherPets;
    input[QString("good_other_pets")] = otherPets;
    input[QString("affection_owner")] = ui->dog_affection_owner->text();
    input[QString("affection_family")] = ui->dog_affection_family->text();
    input[QString("affection_stranger")] = ui->dog_affection_stranger->text();
    input[QString("budget")] = ui->dog_cost->text();
    input[QString("special_needs")] = ui->dog_special_needs->currentText();
    input[QString("dietary")] = ui->dog_dietary->currentText();
    input[QString("vet_visits")] = ui->dog_vet_visits->currentText();
    input[QString("grooming")] = ui->dog_grooming->currentText();
    input[QString("weather")] = ui->dog_weather->currentText();
    input[QString("attention")] = ui->dog_attention->text();
    input[QString("exercise")] = ui->dog_exercise->text();
    /*
     * The space stores the first initial of the type of space that is required by the animal
     * A => Apartment
     * S=> House with a Small Yard
     * L=> House with a Big Yard
     *
    */
    if(ui->dog_apartment->isChecked())
        space +="A";
    if(ui->dog_small_yard->isChecked())
        space +="S";
    if(ui->dog_big_yard->isChecked())
        space +="L";
    input[QString("space")] = space;
}
void AddAnimalDialog::setDogView(QString* attr)
{
    ui->animal_type->setCurrentText("Dog");
    ui->dog_name->setText(attr[3]);
    ui->dog_breed->setCurrentText(attr[7]);
    ui->dog_gender->setCurrentText(attr[9]);
    ui->dog_size->setCurrentText(attr[11]);
    ui->dog_age->setText(attr[13]);
    ui->dog_weight->setText(attr[15]);
    ui->dog_expected_life_span->setText(attr[17]);
    ui->dog_coat_colour->setCurrentText(attr[19]);
    ui->dog_coat_length->setCurrentText(attr[21]);
    ui->dog_coat_layers->setCurrentText(attr[23]);
    ui->dog_shedding->setCurrentText(attr[25]);
    if(attr[27] == "Yes")
        ui->dog_hypoallergenic_yes->setChecked(true);
     else
        ui->dog_hypoallergenic_no->setChecked(true);
    ui->dog_novice_owners->setCurrentText(attr[29]);
    ui->dog_being_alone->setCurrentText(attr[31]);
    ui->dog_kid_friendly->setCurrentText(attr[33]);
    ui-> dog_vocality->setCurrentText(attr[35]);
    ui->dog_trainability->setCurrentText(attr[37]);
    ui->dog_playful_2->setValue(attr[39].toInt());
    ui->dog_energetic_2->setValue(attr[41].toInt());
    ui->dog_intelligence_2->setValue(attr[43].toInt());
    /*
     * other pets basically stores the first letter of the type of animal selected
     * as being compatible with the current animal who's profile is being set up
    */

    if(attr[45].contains("D"))
        ui->dog_dog->setChecked(true);
    if(attr[45].contains("C"))
        ui->dog_cat->setChecked(true);
    if(attr[45].contains("B"))
        ui->dog_bird->setChecked(true);
    if(attr[45].contains("R"))
        ui->dog_rabbit->setChecked(true);
    if(attr[45].contains("H"))
        ui->dog_hamster->setChecked(true);
    if(attr[45].contains("G"))
        ui->dog_guineaPig->setChecked(true);


    ui->dog_affection_owner_2->setValue((attr[47]).toInt());
    ui->dog_affection_family_2->setValue(attr[49].toInt());
    ui->dog_affection_stranger_2->setValue(attr[51].toInt());
    ui->dog_cost->setText(attr[53]);
    ui->dog_special_needs->setCurrentText(attr[55]);
    ui->dog_dietary->setCurrentText(attr[57]);
    ui->dog_vet_visits->setCurrentText(attr[59]);
    ui->dog_grooming->setCurrentText(attr[61]);
    ui->dog_weather->setCurrentText(attr[63]);
    ui->dog_attention_2->setValue(attr[65].toInt());
    ui->dog_exercise_2->setValue(attr[67].toInt());
    /*
     * The space stores the first initial of the type of space that is required by the animal
     * A => Apartment
     * S=> House with a Small Yard
     * L=> House with a Big Yard
     *
    */
    if(attr[69].contains("A"))
        ui->dog_apartment->setChecked(true);
    if(attr[69].contains("S"))
        ui->dog_small_yard->setChecked(true);
    if(attr[69].contains("L"))
        ui->dog_big_yard->setChecked(true);
}

void AddAnimalDialog::addCat(QHash<QString, QString> &input)
{
    QString otherPets = "";
    QString space = "";

    if(ui->cat_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in Animal name"));
    }
    input[QString("name")] = ui->cat_name->text();
    input[QString("type")] = "Cat";
    input[QString("breed")] = ui->cat_breed->currentText();
    input[QString("gender")] = ui->cat_gender->currentText();
    input[QString("size")] = ui->cat_size->currentText();
    input[QString("age")] = ui->cat_age->text();
    input[QString("weight")] = ui->cat_weight->text();
    input[QString("expected_life_span")] = ui->cat_expected_lifespan->text();
    input[QString("colour")] = ui->cat_coat_colour->currentText();
    input[QString("coat_length")] = ui->cat_coat_length->currentText();
    input[QString("coat_pattern")] = ui->cat_coat_pattern->currentText();
    input[QString("shedding")] = ui->cat_shedding->currentText();
    if(ui->cat_hypoallergenic_yes->isChecked())
        input[QString("hypoallergenic")] = "Yes";
    else
        input[QString("hypoallergenic")] = "No";
    input[QString("good_new_owners")] = ui->cat_novice_owners->currentText();

    input[QString("kid_friendly")] = ui->cat_kid_friendly->currentText();
    input[QString("vocality")] = ui-> cat_vocality->currentText();
    input[QString("trainability")] = ui->cat_trainability->currentText();
    input[QString("independent")] = ui->cat_independent->text();
    input[QString("playful")] = ui->dog_playful->text();
    input[QString("energetic")] = ui->dog_energetic->text();
    input[QString("intelligence")] = ui->dog_intelligence->text();
    if(ui->cat_dog->isChecked())
        otherPets +="D";
    if(ui->cat_cat->isChecked())
        otherPets +="C";
    if(ui->cat_bird->isChecked())
        otherPets +="B";
    if(ui->cat_rabbit->isChecked())
        otherPets +="R";
    if(ui->cat_hamster->isChecked())
        otherPets +="H";
    if(ui->cat_guinea_pig->isChecked())
        otherPets +="G";
    //qDebug()<<"other pets"+otherPets;
    input[QString("good_other_pets")] = otherPets;
    input[QString("affection_owner")] = ui->cat_affection_owner->text();
    input[QString("affection_family")] = ui->cat_affection_family->text();
    input[QString("affection_stranger")] = ui->cat_affection_stranger->text();
    input[QString("budget")] = ui->cat_cost->text();
    input[QString("special_needs")] = ui->cat_special_needs->currentText();
    input[QString("dietary")] = ui->cat_dietary->currentText();
    input[QString("vet_visits")] = ui->cat_vet_visits->currentText();
    input[QString("grooming")] = ui->cat_grooming->currentText();
    input[QString("weather")] = ui->cat_weather->currentText();
    input[QString("attention")] = ui->cat_attention->text();


    /*
     * Here the space string holds the first letter of the type of space ideal for cat
     * I => Indoor
     * O => Outdoor
     * */
    if(ui->cat_indoor->isChecked())
        space +="I";
    if(ui->cat_outdoor->isChecked())
        space +="O";
    input[QString("space")] = space;
    input[QString("social")] = ui->cat_social->text();
    input[QString("pair")] = ui->cat_pair->currentText();
}
void AddAnimalDialog::setCatView(QString* attr)
{
    ui->animal_type->setCurrentText("Cat");
    ui->cat_name->setText(attr[3]);
    ui->cat_breed->setCurrentText(attr[7]);
    ui->cat_gender->setCurrentText(attr[9]);
    ui->cat_size->setCurrentText(attr[11]);
    ui->cat_age->setText(attr[13]);
    ui->cat_weight->setText(attr[15]);
    ui->cat_expected_lifespan->setText(attr[17]);
    ui->cat_coat_colour->setCurrentText(attr[19]);
    ui->cat_coat_length->setCurrentText(attr[21]);
    ui->cat_coat_pattern->setCurrentText(attr[23]);
    ui->cat_shedding->setCurrentText(attr[25]);
    if(attr[27] == "Yes")
        ui->cat_hypoallergenic_yes->setChecked(true);
     else
        ui->cat_hypoallergenic_no->setChecked(true);

    ui->cat_novice_owners->setCurrentText(attr[29]);

    ui->cat_kid_friendly->setCurrentText(attr[31]);
    ui-> cat_vocality->setCurrentText(attr[33]);
    ui->cat_trainability->setCurrentText(attr[35]);
    ui->cat_independent_2->setValue(attr[67].toInt());
    ui->cat_playful_2->setValue(attr[37].toInt());
    ui->cat_energetic_2->setValue(attr[39].toInt());
    ui->cat_intelligence_2->setValue(attr[41].toInt());


    if(attr[43].contains("D"))
        ui->cat_dog->setChecked(true);
    if(attr[43].contains("C"))
        ui->cat_cat->setChecked(true);
    if(attr[43].contains("B"))
        ui->cat_bird->setChecked(true);
    if(attr[43].contains("R"))
        ui->cat_rabbit->setChecked(true);
    if(attr[43].contains("H"))
        ui->cat_hamster->setChecked(true);
    if(attr[43].contains("G"))
        ui->cat_guinea_pig->setChecked(true);

    ui->cat_affection_owner_2->setValue(attr[45].toInt());
    ui->cat_affection_family_2->setValue(attr[47].toInt());
    ui->cat_affection_stranger_2->setValue(attr[49].toInt());
    ui->cat_cost->setText(attr[51]);
    ui->cat_special_needs->setCurrentText(attr[53]);
    ui->cat_dietary->setCurrentText(attr[55]);
    ui->cat_vet_visits->setCurrentText(attr[57]);
    ui->cat_grooming->setCurrentText(attr[59]);
    ui->cat_weather->setCurrentText(attr[61]);
    ui->cat_attention_2->setValue(attr[63].toInt());


    /*
     * Here the space string holds the first letter of the type of space ideal for cat
     * I => Indoor
     * O => Outdoor
     * */
    if(attr[65].contains("I"))
        ui->cat_indoor->setChecked(true);
    if(attr[65].contains("S"))
        ui->cat_outdoor->setChecked(true);

    ui->cat_social_2->setValue(attr[69].toInt());
    ui->cat_pair->setCurrentText(attr[71]);
}

void AddAnimalDialog::addBird(QHash<QString, QString> &input)
{
    if(ui->bird_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in Animal name"));
    }

    input[QString("name")] = ui->bird_name->text();
    input[QString("type")] = "Bird";
    input[QString("breed")] = ui->bird_breed->currentText();
    input[QString("gender")] = ui->bird_gender->currentText();
    input[QString("size")] = ui->bird_size->currentText();
    input[QString("age")] = ui->bird_age->text();
    input[QString("dietary")] = ui->bird_dietary->currentText();
    input[QString("pair")] = ui->bird_pair->currentText();
    input[QString("weather")] = ui->bird_weather->currentText();
    input[QString("budget")] = ui->bird_cost->text();
    input[QString("colour")] = ui->bird_colour->currentText();
    input[QString("special_needs")] = ui-> bird_special_needs->currentText();
    input[QString("vet_visits")] = ui->bird_vet_visits->currentText();
    input[QString("expected_life_span")] = ui->bird_expected_lifespan->text();
    input[QString("vocality")] = ui->bird_vocality->currentText();
    input[QString("shedding")] = ui->bird_shedding->text();
    input[QString("interactive")] = ui->bird_interactive->text();
    input[QString("intelligence")] = ui->bird_intelligence->text();
}
void AddAnimalDialog::setBirdView(QString* attr){
    ui->animal_type->setCurrentText("Bird");
    ui->bird_name->setText(attr[3]);
    ui->bird_breed->setCurrentText(attr[7]);
    ui->bird_gender->setCurrentText(attr[9]);
    ui->bird_size->setCurrentText(attr[11]);
    ui->bird_age->setText(attr[13]);
    ui->bird_dietary->setCurrentText(attr[29]);
    ui->bird_pair->setCurrentText(attr[35]);
    ui->bird_weather->setCurrentText(attr[33]);
    ui->bird_cost->setText(attr[25]);
    ui->bird_colour->setCurrentText(attr[17]);
    ui-> bird_special_needs->setCurrentText(attr[27]);
    ui->bird_vet_visits->setCurrentText(attr[31]);
    ui->bird_expected_lifespan->setText(attr[15]);
    ui->bird_vocality->setCurrentText(attr[21]);
    ui->bird_shedding_2->setValue(attr[19].toInt());
    ui->bird_interactive_2->setValue(attr[37].toInt());
    ui->bird_intelligence_2->setValue(attr[23].toInt());
}

void AddAnimalDialog::addRabbit(QHash<QString, QString> &input)
{
    QString otherPets = "R";

    if(ui->rabbit_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in Animal name"));
    }

    if(ui->rabbit_dog->isChecked())
        otherPets +="D";
    if(ui->rabbit_cat->isChecked())
        otherPets +="C";
    if(ui->rabbit_bird->isChecked())
        otherPets +="B";
    if(ui->rabbit_hamster->isChecked())
        otherPets +="H";
    if(ui->rabbit_guineaPig->isChecked())
        otherPets +="G";
    input[QString("good_other_pets")] = otherPets;
    if(ui->rabbit_hypoallergenic_yes->isChecked())
        input[QString("hypoallergenic")] = "Yes";
    else
        input[QString("hypoallergenic")] = "No";
    if(ui->rabbit_tamed_yes->isChecked())
        input[QString("tamed")] = "Yes";
    else
        input[QString("tamed")] = "No";


    input[QString("name")] = ui->rabbit_name->text();
    input[QString("type")] = "Rabbit";
    input[QString("gender")] = ui->rabbit_gender->currentText();
    input[QString("breed")] = ui->rabbit_breed->currentText();
    input[QString("temperament")] = ui->rabbit_temprament->currentText();
    input[QString("age")] = ui->rabbit_age->text();
    input[QString("budget")] = ui->rabbit_cost->text();
    input[QString("expected_life_span")] = ui->rabbit_expected_lifespan->text();
    input[QString("social")] = ui->rabbit_social->text();
    input[QString("sensitivity")] = ui->rabbit_sensitivity->text();
}
void AddAnimalDialog::setRabbitView(QString* attr){

    ui->animal_type->setCurrentText("Rabbit");
    if(attr[19].contains("D"))
        ui->rabbit_dog->setChecked(true);
    if(attr[19].contains("C"))
        ui->rabbit_cat->setChecked(true);
    if(attr[19].contains("B"))
        ui->rabbit_bird->setChecked(true);
    if(attr[19].contains("H"))
        ui->rabbit_hamster->setChecked(true);
    if(attr[19].contains("G"))
        ui->rabbit_guineaPig->setChecked(true);

    if(attr[17] == "Yes")
        ui->rabbit_hypoallergenic_yes->setChecked(true);
     else
        ui->rabbit_hypoallergenic_no->setChecked(true);

    if(attr[27] == "Yes")
        ui->rabbit_tamed_yes->setChecked(true);
     else
        ui->rabbit_tamed_no->setChecked(true);


    ui->rabbit_name->setText(attr[3]);
    ui->rabbit_gender->setCurrentText(attr[9]);
    ui->rabbit_breed->setCurrentText(attr[7]);
    ui->rabbit_temprament->setCurrentText(attr[25]);
    ui->rabbit_age->setText(attr[11]);
    ui->rabbit_cost->setText(attr[21]);
    ui->rabbit_expected_lifespan->setText(attr[13]);
    ui->rabbit_social_2->setValue(attr[23].toInt());
    ui->rabbit_sensitivity_2->setValue(attr[29].toInt());
}

void AddAnimalDialog::addHamster(QHash<QString, QString> &input)
{
    if(ui->hamster_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in Animal name"));
    }

    if(ui->hamster_hypoallergenic_yes->isChecked())
        input[QString("hypoallergenic")] = "Yes";
    else
        input[QString("hypoallergenic")] = "No";
    if(ui->hamster_tamed_yes->isChecked())
        input[QString("tamed")] = "Yes";
    else
        input[QString("tamed")] = "No";
    if(ui->hamster_nocturnal_yes->isChecked())
        input[QString("nocturnal")] = "Yes";
    else
        input[QString("nocturnal")] = "No";


    input[QString("name")] = ui->hamster_name->text();
    input[QString("type")] = "Hamster";
    input[QString("gender")] = ui->hamster_gender->currentText();
    input[QString("breed")] = ui->hamster_breed->currentText();
    input[QString("colour")] = ui->hamster_colour->currentText();
    input[QString("age")] = ui->hamster_age->text();
    input[QString("budget")] = ui->hamster_cost->text();
    input[QString("expected_life_span")] = ui->hamster_expected_lifespan->text();
    input[QString("social")] = ui->hamster_social->text();
    input[QString("attention")] = ui->hamster_attention->text();
    input[QString("cleaning")] = ui->hamster_cleaning->text();
    input[QString("feeding")] = ui->hamster_feeding->text();
}
void AddAnimalDialog::setHamsterView(QString* attr){

    ui->animal_type->setCurrentText("Hamster");
    if(attr[17] == "Yes")
        ui->hamster_hypoallergenic_yes->setChecked(true);
     else
        ui->hamster_hypoallergenic_no->setChecked(true);

    if(attr[25] == "Yes")
        ui->hamster_tamed_yes->setChecked(true);
     else
        ui->hamster_tamed_no->setChecked(true);

    if(attr[27] == "Yes")
        ui->hamster_nocturnal_yes->setChecked(true);
     else
        ui->hamster_nocturnal_no->setChecked(true);


    ui->hamster_name->setText(attr[3]);

    ui->hamster_gender->setCurrentText(attr[9]);
    ui->hamster_breed->setCurrentText(attr[7]);
    ui->hamster_colour->setCurrentText(attr[15]);
    ui->hamster_age->setText(attr[11]);
    ui->hamster_cost->setText(attr[19]);
    ui->hamster_expected_lifespan->setText(attr[13]);
    ui->hamster_social_2->setValue(attr[23].toInt());
    ui->hamster_attention_2->setValue(attr[21].toInt());
    ui->hamster_cleaning_2->setValue(attr[31].toInt());
    ui->hamster_feeding_2->setValue(attr[29].toInt());
}

void AddAnimalDialog::addGuineaPig(QHash<QString, QString> &input)
{
    if(ui->guineaPig_name->text().isEmpty()) {
        //qDebug() << "Empty name";
        QMessageBox::critical(this,tr(""),tr("Please fill in Animal name"));
    }

    if(ui->guineaPig_hypoallergenic_yes->isChecked())
        input[QString("hypoallergenic")] = "Yes";
    else
        input[QString("hypoallergenic")] = "No";
    if(ui->guineaPig_tamed_yes->isChecked())
        input[QString("tamed")] = "Yes";
    else
        input[QString("tamed")] = "No";


    input[QString("name")] = ui->guineaPig_name->text();
    input[QString("type")] = "GuineaPig";
    input[QString("gender")] = ui->guineaPig_gender->currentText();
    input[QString("breed")] = ui->guineaPig_breed->currentText();
    input[QString("colour")] =ui->guineaPig_colour->currentText();
    input[QString("age")] =ui->guineaPig_age->text();
    input[QString("budget")] =ui->guineaPig_cost->text();
    input[QString("expected_life_span")] =ui->guineaPig_expectedlifespan->text();
    input[QString("social")] = ui->guineaPig_social->text();
    input[QString("attention")] = ui->guineaPig_attention->text();
    input[QString("cleaning")] = ui->guineaPig_cleaning->text();
    input[QString("feeding")] = ui->guineaPig_feeding->text();
}
void AddAnimalDialog::setGuineaPigView(QString* attr){

    ui->animal_type->setCurrentText("Guinea Pig");
    if(attr[17] == "Yes")
        ui->guineaPig_hypoallergenic_yes->setChecked(true);
     else
        ui->guineaPig_hypoallergenic_no->setChecked(true);

    if(attr[25] == "Yes")
        ui->guineaPig_tamed_yes->setChecked(true);
     else
        ui->guineaPig_tamed_no->setChecked(true);

    ui->guineaPig_name->setText(attr[3]);
    ui->guineaPig_gender->setCurrentText(attr[9]);
    ui->guineaPig_breed->setCurrentText(attr[7]);
    ui->guineaPig_colour->setCurrentText(attr[15]);
    ui->guineaPig_age->setText(attr[11]);
    ui->guineaPig_cost->setText(attr[19]);
    ui->guineaPig_expectedlifespan->setText(attr[13]);
    ui->guineaPig_social_2->setValue(attr[23].toInt());
    ui->guineaPig_attention_2->setValue(attr[21].toInt());
    ui->guineaPig_cleaning_2->setValue(attr[29].toInt());
    ui->guineaPig_feeding_2->setValue(attr[27].toInt());
}

void AddAnimalDialog::on_saveButton_clicked()
{
    //TODO : set up Animal Control and pass arguments to create() in Animal class

    typecounter = ui->animal_Characteristics->currentIndex();

    QHash<QString, QString> input;

    //switch to different helper funtions based on the client's choice
    switch (typecounter) {
    case 1:
        addDog(input);
        break;
    case 2:
        addCat(input);
        break;
    case 3:
        addBird(input);
        break;
    case 4:
        addRabbit(input);
        break;
    case 5:
        addHamster(input);
        break;
    case 6:
        addGuineaPig(input);
        break;

    default:
        break;
    }

    QString errMsg;

    if(dbControl->dbRequest(&input, NULL, ADD_ANIMAL, &errMsg))
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        this->close();
        //emit newAnimalAdded();//send a signal to staffMainWindow object
        notify();
    }
    else
    {
        QMessageBox::critical(this, tr("Error!"), errMsg);
        //this->clearFields();
    }
}

void AddAnimalDialog::on_resetButton_clicked()
{
    this->clearFields();
}

void AddAnimalDialog::on_cancelButton_clicked()
{
    this->close();
}

void AddAnimalDialog::on_update_Button_clicked()
{
    typecounter = ui->animal_Characteristics->currentIndex();

    QHash<QString, QString> input;

    //switch to different helper funtions based on the client's choice
    switch (typecounter) {
    case 1:
        addDog(input);
        break;
    case 2:
        addCat(input);
        break;
    case 3:
        addBird(input);
        break;
    case 4:
        addRabbit(input);
        break;
    case 5:
        addHamster(input);
        break;
    case 6:
        addGuineaPig(input);
        break;

    default:
        break;
    }

    QString errMsg;

    input["id"] = QString::number(rowNum + 1);
    if(dbControl->dbRequest(&input, NULL, UPDATE_ANIMAL, &errMsg))
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        this->close();
        emit animalEdited();//send a signal to staffMainWindow object
    }
    else
    {
        QMessageBox::critical(this, tr("Error!"), errMsg);
        //this->clearFields();
    }
}


void AddAnimalDialog::on_edit_Button_clicked()
{
    ui->update_Button->show();
    ui->edit_Button->hide();
    ui->cancelButton->show();
    QList<QWidget *> widgets = this->findChildren<QWidget *>();
                          foreach(QWidget* widget, widgets)
                          {

                              widget->setEnabled(true);
                                  //qDebug()<<widget;
                            //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                          }
      ui->animal_type->setDisabled(true);

}
