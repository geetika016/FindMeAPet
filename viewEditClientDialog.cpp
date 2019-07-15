#include "viewEditClientDialog.h"
#include "ui_viewEditClientDialog.h"

ViewEditClientDialog::ViewEditClientDialog(QString name, QWidget *parent, int user_type) :
    username(name),
    QDialog(parent),
    ui(new Ui::ViewEditClientDialog)
{
    ui->setupUi(this);
    dbControl = new ClientDatabaseControl(username);
    ui->animal_Characteristics->setCurrentIndex(0);
    ui->dog_characteristics_tab->setCurrentIndex(0);
    ui->cat_characteristics_tab->setCurrentIndex(0);
    ui->bird_characteristics->setCurrentIndex(0);
    ui->rabbit_characteristics->setCurrentIndex(0);
    ui->hamster_characteristics->setCurrentIndex(0);
    ui->guineaPig_characteristics->setCurrentIndex(0);
    this->user_type = user_type;

    if(user_type == 0)
    {
        ui->saveButton->hide();
        ui->resetButton->hide();
        ui->cancelButton->hide();
    }
    connect(ui->client_animal_type,SIGNAL(currentIndexChanged(int)),ui->animal_Characteristics,SLOT(setCurrentIndex(int)));
    QList<QHash<QString, QString>> listOutput;
    QString errMsg;
    if (!dbControl->dbRequest(NULL, &listOutput, READ_CLIENT, &errMsg))
        QMessageBox::critical(NULL, "Database Error", errMsg);
    QHash<QString, QString> output = listOutput.first();
    clientID = output.value("id");
    initialInfo(output);
    if(output.value("animal_type") != "")
    {
        animal_type = output.value("animal_type");
        fillInfo(output);
        ui->client_animal_type->setCurrentText(animal_type);
        ui->client_animal_type->setDisabled(true);
    }

}

ViewEditClientDialog::~ViewEditClientDialog()
{
    delete ui;
    delete dbControl;
}
void ViewEditClientDialog::initialInfo(QHash<QString, QString> input){

    ui->client_name->setText(input.value("name"));
    ui->client_cat_name->setText(input.value("name"));
    ui->client_bird_name->setText(input.value("name"));
    ui->client_rabbit_name->setText(input.value("name"));
    ui->client_hamster_name->setText(input.value("name"));
    ui->client_guineaPig_name->setText(input.value("name"));

    ui->client_name->setReadOnly(true);
    ui->client_cat_name->setReadOnly(true);
    ui->client_bird_name->setReadOnly(true);
    ui->client_rabbit_name->setReadOnly(true);
    ui->client_hamster_name->setReadOnly(true);
    ui->client_guineaPig_name->setReadOnly(true);

    ui->client_phoneNumber->setText(input.value("phone_number"));
    ui->client_cat_phoneNumber->setText(input.value("phone_number"));
    ui->client_bird_phoneNumber->setText(input.value("phone_number"));
    ui->client_rabbit_phoneNumber->setText(input.value("phone_number"));
    ui->client_hamster_phoneNumber->setText(input.value("phone_number"));
    ui->client_guineaPig_phoneNumber->setText(input.value("phone_number"));


    ui->client_email->setText(input.value("email"));
    ui->client_cat_email->setText(input.value("email"));
    ui->client_bird_email->setText(input.value("email"));
    ui->client_rabbit_email->setText(input.value("email"));
    ui->client_hamster_email->setText(input.value("email"));
    ui->client_guineaPig_email->setText(input.value("email"));

}
void ViewEditClientDialog::fillInfo(QHash<QString, QString> input){
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    //qDebug()<<"inside fillInfo";
    //qDebug()<<user_type;
    switch (ui->client_animal_type->currentIndex()) {
        case 1:
            setClientDogView(input);
            break;
        case 2:
            setClientCatView(input);
            break;
        case 3:
            setClientBirdView(input);
            break;
        case 4:
            setClientRabbitView(input);
            break;
        case 5:
            setClientHamsterView(input);
            break;
        case 6:
            setClientGuineaPigView(input);
            break;
        default:
            break;
    }
}
void ViewEditClientDialog::setClientDogView(QHash<QString, QString> input)
{
    //qDebug()<<"inside setDogview";
    //qDebug()<<user_type;
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_dog_space->setCurrentText(input.value("space"));
    ui->client_dog_weather->setCurrentText(input.value("weather"));
    ui->client_dog_being_alone->setCurrentText(input.value("at_home_mostly"));
    ui->client_dog_allergies->setCurrentText(input.value("allergies"));
    ui->client_dog_novice_owners->setCurrentText(input.value("first_pet"));
    ui->client_dog_kid_friendly->setCurrentText(input.value("kids"));
    ui->client_dog_cost->setText(input.value("budget"));
    ui->client_dog_breed->setCurrentText(input.value("breed"));
    ui->client_dog_gender->setCurrentText(input.value("gender"));
    ui->client_dog_size->setCurrentText(input.value("size"));
    ui->client_dog_age->setCurrentText(input.value("age"));
    ui->client_dog_coat_colour->setCurrentText(input.value("colour"));
    ui->client_dog_shedding->setCurrentText(input.value("shedding"));
    ui->client_dog_grooming->setCurrentText(input.value("grooming"));
    ui->client_dog_dietary->setCurrentText(input.value("dietary_needs"));
    ui->client_dog_special_needs->setCurrentText(input.value("special_needs"));
    ui->client_dog_vet_visits->setCurrentText(input.value("vet_visits"));
    ui->client_dog_attention_2->setValue(input.value("attention").toInt());
    ui->client_dog_energetic_2->setValue(input.value("energetic").toInt());
    ui->client_dog_trainability_2->setValue(input.value("trainability").toInt());
    ui->client_dog_intelligence_2->setValue(input.value("intelligence").toInt());
    ui->client_dog_exercise_2->setValue(input.value("exercise").toInt());
    ui->client_dog_vocality_2->setValue(input.value("vocality").toInt());
    ui->client_dog_playful_2->setValue(input.value("playful").toInt());
    ui->client_dog_affection_owner_2->setValue(input.value("affection_owner").toInt());
    ui->client_dog_affection_family_2->setValue(input.value("affection_family").toInt());
    ui->client_dog_affection_stranger_2->setValue(input.value("affection_stranger").toInt());

    if(input.value("other_pets").contains("D"))
        ui->client_dog_dog->setChecked(true);
    if(input.value("other_pets").contains("C"))
        ui->client_dog_cat->setChecked(true);
    if(input.value("other_pets").contains("B"))
        ui->client_dog_bird->setChecked(true);
    if(input.value("other_pets").contains("R"))
        ui->client_dog_rabbit->setChecked(true);
    if(input.value("other_pets").contains("H"))
        ui->client_dog_hamster->setChecked(true);
    if(input.value("other_pets").contains("G"))
        ui->client_dog_guineaPig->setChecked(true);
    if(input.value("other_pets").contains("N"))
        ui->client_dog_none->setChecked(true);

//    QHash<QString, QString>::iterator i;
//        for (i = input.begin(); i != input.end(); ++i)
//            //qDebug() << i.key() << ": " << i.value();

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_4->findChildren<QWidget *>();

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
                    widgets = ui->basic->findChildren<QWidget *>();

                        foreach(QWidget* widget, widgets)
                        {

                            widget->setDisabled(true);
                    //qDebug()<<widget;
                            //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                             }

    }
}
void ViewEditClientDialog::setClientCatView(QHash<QString, QString> input)
{
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_cat_space->setCurrentText(input.value("space"));
    ui->client_cat_weather->setCurrentText(input.value("weather"));
    ui->client_cat_being_alone->setCurrentText(input.value("at_home_mostly"));
    ui->client_cat_allergies->setCurrentText(input.value("allergies"));
    ui->client_cat_novice_owners->setCurrentText(input.value("first_pet"));
    ui->client_cat_kid_friendly->setCurrentText(input.value("kids"));
    ui->client_cat_cost->setText(input.value("budget"));
    ui->client_cat_breed->setCurrentText(input.value("breed"));
    ui->client_cat_gender->setCurrentText(input.value("gender"));
    ui->client_cat_size->setCurrentText(input.value("size"));
    ui->client_cat_age->setCurrentText(input.value("age"));
    ui->client_cat_coat_colour->setCurrentText(input.value("colour"));
    ui->client_cat_shedding->setCurrentText(input.value("shedding"));
    ui->client_cat_grooming->setCurrentText(input.value("grooming"));
    ui->client_cat_dietary->setCurrentText(input.value("dietary_needs"));
    ui->client_cat_special_needs->setCurrentText(input.value("special_needs"));
    ui->client_cat_vet_visits->setCurrentText(input.value("vet_visits"));
    ui->client_cat_attention_2->setValue(input.value("attention").toInt());
    ui->client_cat_energetic_2->setValue(input.value("energetic").toInt());
    ui->client_cat_trainability_2->setValue(input.value("trainability").toInt());
    ui->client_cat_intelligence_2->setValue(input.value("intelligence").toInt());
    ui->client_cat_vocality_2->setValue(input.value("vocality").toInt());
    ui->client_cat_playful_2->setValue(input.value("playful").toInt());
    ui->client_cat_affection_owner_2->setValue(input.value("affection_owner").toInt());
    ui->client_cat_affection_family_2->setValue(input.value("affection_family").toInt());
    ui->client_cat_affection_stranger_2->setValue(input.value("affection_stranger").toInt());
    ui->client_cat_pair->setCurrentText(input.value("pair"));
    ui->client_cat_coat_pattern->setCurrentText(input.value("coat_pattern"));
    ui->client_cat_social_2->setValue(input.value("social").toInt());
    ui->client_cat_independent_2->setValue(input.value("independent").toInt());

    if(input.value("other_pets").contains("D"))
        ui->client_cat_dog->setChecked(true);
    if(input.value("other_pets").contains("C"))
        ui->client_cat_cat->setChecked(true);
    if(input.value("other_pets").contains("B"))
        ui->client_cat_bird->setChecked(true);
    if(input.value("other_pets").contains("R"))
        ui->client_cat_rabbit->setChecked(true);
    if(input.value("other_pets").contains("H"))
        ui->client_cat_hamster->setChecked(true);
    if(input.value("other_pets").contains("G"))
        ui->client_cat_guineaPig->setChecked(true);
    if(input.value("other_pets").contains("N"))
        ui->client_cat_none->setChecked(true);

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_15->findChildren<QWidget *>();

            foreach(QWidget* widget, widgets)
            {

                widget->setDisabled(true);
        //qDebug()<<widget;
                //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                 }
            widgets = ui->tab->findChildren<QWidget *>();

                foreach(QWidget* widget, widgets)
                {

                    widget->setDisabled(true);
            //qDebug()<<widget;
                    //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                     }
                widgets = ui->tab_7->findChildren<QWidget *>();

                    foreach(QWidget* widget, widgets)
                    {

                        widget->setDisabled(true);
                //qDebug()<<widget;
                        //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                         }
                    widgets = ui->tab_8->findChildren<QWidget *>();

                        foreach(QWidget* widget, widgets)
                        {

                            widget->setDisabled(true);
                    //qDebug()<<widget;
                            //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                             }

    }
}
void ViewEditClientDialog::setClientBirdView(QHash<QString, QString> input)
{
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_bird_weather->setCurrentText(input.value("weather"));
    ui->client_bird_kid_friendly->setCurrentText(input.value("kids"));
    ui->client_bird_cost->setText(input.value("budget"));
    ui->client_bird_breed->setCurrentText(input.value("breed"));
    ui->client_bird_gender->setCurrentText(input.value("gender"));
    ui->client_bird_size->setCurrentText(input.value("size"));
    ui->client_bird_colour->setCurrentText(input.value("colour"));
    ui->client_bird_shedding_2->setValue(input.value("shedding").toInt());
    ui->client_bird_dietary->setCurrentText(input.value("dietary_needs"));
    ui->client_bird_special_needs->setCurrentText(input.value("special_needs"));
    ui->client_bird_vet_visits->setCurrentText(input.value("vet_visits"));
    ui->client_bird_vocality_2->setValue(input.value("vocality").toInt());
    ui->client_bird_pair->setCurrentText(input.value("pair"));
    ui->client_bird_interactive_2->setValue(input.value("interactive").toInt());
//    QHash<QString, QString>::iterator i;
//        for (i = input.begin(); i != input.end(); ++i)
//            //qDebug() << i.key() << ": " << i.value();

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_16->findChildren<QWidget *>();

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
                widgets = ui->tab_10->findChildren<QWidget *>();

                    foreach(QWidget* widget, widgets)
                    {

                        widget->setDisabled(true);
                //qDebug()<<widget;
                        //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                         }

    }
}
void ViewEditClientDialog::setClientRabbitView(QHash<QString, QString> input)
{
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_rabbit_allergies->setCurrentText(input.value("allergies"));
    ui->client_rabbit_cost->setText(input.value("budget"));
    ui->client_rabbit_breed->setCurrentText(input.value("breed"));
    ui->client_rabbit_gender->setCurrentText(input.value("gender"));
    ui->client_rabbit_colour->setCurrentText(input.value("colour"));
    ui->client_rabbit_social_2->setValue(input.value("social").toInt());
    ui->client_rabbit_tamed->setCurrentText(input.value("tamed"));
    ui->client_rabbit_temperament_2->setValue(input.value("temperament").toInt());
    ui->client_rabbit_sensitivity_2->setValue(input.value("sensitivity").toInt());


    if(input.value("other_pets").contains("D"))
        ui->client_rabbit_dog->setChecked(true);
    if(input.value("other_pets").contains("C"))
        ui->client_rabbit_cat->setChecked(true);
    if(input.value("other_pets").contains("B"))
        ui->client_rabbit_bird->setChecked(true);
    if(input.value("other_pets").contains("R"))
        ui->client_rabbit_rabbit->setChecked(true);
    if(input.value("other_pets").contains("H"))
        ui->client_rabbit_hamster->setChecked(true);
    if(input.value("other_pets").contains("G"))
        ui->client_rabbit_guineaPig->setChecked(true);
    if(input.value("other_pets").contains("N"))
        ui->client_rabbit_none->setChecked(true);

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_17->findChildren<QWidget *>();

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
                widgets = ui->tab_11->findChildren<QWidget *>();

                    foreach(QWidget* widget, widgets)
                    {

                        widget->setDisabled(true);
                //qDebug()<<widget;
                        //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                         }

    }
}
void ViewEditClientDialog::setClientHamsterView(QHash<QString, QString> input)
{
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_hamster_allergies->setCurrentText(input.value("allergies"));
    ui->client_hamster_kid_friendly->setCurrentText(input.value("kids"));
    ui->client_hamster_cost->setText(input.value("budget"));
    ui->client_hamster_breed->setCurrentText(input.value("breed"));
    ui->client_hamster_gender->setCurrentText(input.value("gender"));
    ui->client_hamster_colour->setCurrentText(input.value("colour"));
    ui->client_hamster_attention_2->setValue(input.value("attention").toInt());
    ui->client_hamster_social_2->setValue(input.value("social").toInt());
    ui->client_hamster_tamed->setCurrentText(input.value("tamed"));
    ui->client_hamster_cleaning_2->setValue(input.value("cleaning").toInt());
    ui->client_hamster_feeding_2->setValue(input.value("feeding").toInt());
    ui->client_hamster_nocturnal->setCurrentText(input.value("nocturnal"));

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_18->findChildren<QWidget *>();

            foreach(QWidget* widget, widgets)
            {

                widget->setDisabled(true);
        //qDebug()<<widget;
                //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                 }
            widgets = ui->tab_9->findChildren<QWidget *>();

                foreach(QWidget* widget, widgets)
                {

                    widget->setDisabled(true);
            //qDebug()<<widget;
                    //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                     }
                widgets = ui->tab_12->findChildren<QWidget *>();

                    foreach(QWidget* widget, widgets)
                    {

                        widget->setDisabled(true);
                //qDebug()<<widget;
                        //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                         }

    }

}
void ViewEditClientDialog::setClientGuineaPigView(QHash<QString, QString> input)
{
    ui->client_animal_type->setCurrentText(input.value("animal_type"));
    ui->client_guineaPig_allergies->setCurrentText(input.value("allergies"));
    ui->client_guineaPig_kid_friendly->setCurrentText(input.value("kids"));
    ui->client_guineaPig_cost->setText(input.value("budget"));
    ui->client_guineaPig_breed->setCurrentText(input.value("breed"));
    ui->client_guineaPig_gender->setCurrentText(input.value("gender"));
    ui->client_guineaPig_colour->setCurrentText(input.value("colour"));
    ui->client_guineaPig_attention_2->setValue(input.value("attention").toInt());
    ui->client_guineaPig_social_2->setValue(input.value("social").toInt());
    ui->client_guineaPig_tamed->setCurrentText(input.value("tamed"));
    ui->client_guineaPig_cleaning_2->setValue(input.value("cleaning").toInt());
    ui->client_guineaPig_feeding_2->setValue(input.value("feeding").toInt());

    if(user_type == 0)
    {
        this->setStyleSheet("QWidget:disabled{color: black}");
        ui->client_animal_type->setDisabled(true);
        QList<QWidget *> widgets;
        widgets = ui->tab_19->findChildren<QWidget *>();

            foreach(QWidget* widget, widgets)
            {

                widget->setDisabled(true);
        //qDebug()<<widget;
                //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                 }
            widgets = ui->tab_13->findChildren<QWidget *>();

                foreach(QWidget* widget, widgets)
                {

                    widget->setDisabled(true);
            //qDebug()<<widget;
                    //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                     }
                widgets = ui->tab_14->findChildren<QWidget *>();

                    foreach(QWidget* widget, widgets)
                    {

                        widget->setDisabled(true);
                //qDebug()<<widget;
                        //setEventTrigger :: QAbstractItemVIew::NoEditTriggers
                         }

    }

}
void ViewEditClientDialog::clientUpdateDog(QHash<QString, QString> &input){
    input[QString("name")] = ui->client_name->text();
    input[QString("email")] = ui->client_email->text();
    input[QString("phone_number")] = ui->client_phoneNumber->text();
    QString others = "";
    input[QString("animal_type")] = ui->client_animal_type->currentText();
    input[QString("space")] = ui->client_dog_space->currentText();
    input[QString("weather")] =ui->client_dog_weather->currentText();
    input[QString("at_home_mostly")] = ui->client_dog_being_alone->currentText();
    input[QString("allergies")] = ui->client_dog_allergies->currentText();
    input[QString("first_pet")] = ui->client_dog_novice_owners->currentText() ;
    input[QString("kids")] = ui->client_dog_kid_friendly->currentText();
    input[QString("budget")] = ui->client_dog_cost->text();
    input[QString("breed")] = ui->client_dog_breed->currentText();
    input[QString("gender")] = ui->client_dog_gender->currentText();
    input[QString("size")] = ui->client_dog_size->currentText();
    input[QString("age")] = ui->client_dog_age->currentText() ;
    input[QString("colour")] = ui->client_dog_coat_colour->currentText();
    input[QString("shedding")] = ui->client_dog_shedding->currentText();
    input[QString("grooming")] = ui->client_dog_grooming->currentText() ;
    input[QString("dietary_needs")] = ui->client_dog_dietary->currentText() ;
    input[QString("special_needs")] = ui->client_dog_special_needs->currentText();
    input[QString("vet_visits")] = ui->client_dog_vet_visits->currentText();
    input[QString("attention")] = ui->client_dog_attention->text();
    input[QString("energetic")] = ui->client_dog_energetic->text();
    input[QString("trainability")] = ui->client_dog_trainability->text();
    input[QString("intelligence")] =ui->client_dog_intelligence->text() ;
    input[QString("exercise")] = ui->client_dog_exercise->text();
    input[QString("vocality")] = ui->client_dog_vocality->text();
    input[QString("playful")] = ui->client_dog_playful->text();
    input[QString("affection_owner")] = ui->client_dog_affection_owner->text();
    input[QString("affection_family")] = ui->client_dog_affection_family->text();
    input[QString("affection_stranger")] = ui->client_dog_affection_stranger->text();


    if(ui->client_dog_dog->isChecked())
        others+="D";
    if(ui->client_dog_cat->isChecked())
        others+= "C";
    if(ui->client_dog_bird->isChecked())
        others+= "B";
    if(ui->client_dog_rabbit->isChecked())
        others+= "R";
    if(ui->client_dog_hamster->isChecked())
        others+= "H";
    if(ui->client_dog_guineaPig->isChecked())
        others+= "G";
    if(ui->client_dog_none->isChecked())
        others+= "N";

    input[QString("other_pets")] = others;

}
void ViewEditClientDialog::clientUpdateCat(QHash<QString, QString> &input){
    input[QString("name")] = ui->client_cat_name->text();
    input[QString("email")] = ui->client_cat_email->text();
    input[QString("phone_number")] = ui->client_cat_phoneNumber->text();
    QString others = "";
    input[QString("animal_type")] = ui->client_animal_type->currentText();
    input[QString("space")] = ui->client_cat_space->currentText();
    input[QString("weather")] =ui->client_cat_weather->currentText();
    input[QString("at_home_mostly")] = ui->client_cat_being_alone->currentText();
    input[QString("allergies")] = ui->client_cat_allergies->currentText();
    input[QString("first_pet")] = ui->client_cat_novice_owners->currentText() ;
    input[QString("kids")] = ui->client_cat_kid_friendly->currentText();
    input[QString("budget")] = ui->client_cat_cost->text();
    input[QString("breed")] = ui->client_cat_breed->currentText();
    input[QString("gender")] = ui->client_cat_gender->currentText();
    input[QString("size")] = ui->client_cat_size->currentText();
    input[QString("age")] = ui->client_cat_age->currentText() ;
    input[QString("colour")] = ui->client_cat_coat_colour->currentText();
    input[QString("shedding")] = ui->client_cat_shedding->currentText();
    input[QString("grooming")] = ui->client_cat_grooming->currentText() ;
    input[QString("dietary_needs")] = ui->client_cat_dietary->currentText() ;
    input[QString("special_needs")] = ui->client_cat_special_needs->currentText();
    input[QString("vet_visits")] = ui->client_cat_vet_visits->currentText();
    input[QString("attention")] = ui->client_cat_attention->text();
    input[QString("energetic")] = ui->client_cat_energetic->text();
    input[QString("trainability")] = ui->client_cat_trainability->text();
    input[QString("intelligence")] =ui->client_cat_intelligence->text() ;
    input[QString("vocality")] = ui->client_cat_vocality->text();
    input[QString("playful")] = ui->client_cat_playful->text();
    input[QString("affection_owner")] = ui->client_cat_affection_owner->text();
    input[QString("affection_family")] = ui->client_cat_affection_family->text();
    input[QString("affection_stranger")] = ui->client_cat_affection_stranger->text();
    input[QString("pair")] = ui->client_cat_pair->currentText();
    input[QString("coat_pattern")] = ui->client_cat_coat_pattern->currentText();
    input[QString("social")] = ui->client_cat_social->text();
    input[QString("independent")] = ui->client_cat_independent->text();

    if(ui->client_cat_dog->isChecked())
        others+="D";
    if(ui->client_cat_cat->isChecked())
        others+= "C";
    if(ui->client_cat_bird->isChecked())
        others+= "B";
    if(ui->client_cat_rabbit->isChecked())
        others+= "R";
    if(ui->client_cat_hamster->isChecked())
        others+= "H";
    if(ui->client_cat_guineaPig->isChecked())
        others+= "G";
    if(ui->client_cat_none->isChecked())
        others+= "N";

    input[QString("other_pets")] = others;
}
void ViewEditClientDialog::clientUpdateBird(QHash<QString, QString> &input){
    input[QString("name")] = ui->client_bird_name->text();
    input[QString("email")] = ui->client_bird_email->text();
    input[QString("phone_number")] = ui->client_bird_phoneNumber->text();
    input[QString("animal_type")] = ui->client_animal_type->currentText();
    input[QString("weather")] =ui->client_bird_weather->currentText();
    input[QString("kids")] = ui->client_bird_kid_friendly->currentText();
    input[QString("budget")] = ui->client_bird_cost->text();
    input[QString("breed")] = ui->client_bird_breed->currentText();
    input[QString("gender")] = ui->client_bird_gender->currentText();
    input[QString("size")] = ui->client_bird_size->currentText();
    input[QString("colour")] = ui->client_bird_colour->currentText();
    input[QString("shedding")] = ui->client_bird_shedding->text();
    input[QString("dietary_needs")] = ui->client_bird_dietary->currentText() ;
    input[QString("special_needs")] = ui->client_bird_special_needs->currentText();
    input[QString("vet_visits")] = ui->client_bird_vet_visits->currentText();
    input[QString("vocality")] = ui->client_bird_vocality->text();
    input[QString("pair")] = ui->client_bird_pair->currentText();
    input[QString("interactive")] = ui->client_bird_interactive->text();
}
void ViewEditClientDialog::clientUpdateRabbit(QHash<QString, QString> &input){
      input[QString("name")] = ui->client_rabbit_name->text();
      input[QString("email")] = ui->client_rabbit_email->text();
      input[QString("phone_number")] = ui->client_rabbit_phoneNumber->text();
      QString others = "";
      input[QString("animal_type")] = ui->client_animal_type->currentText();
      input[QString("allergies")] = ui->client_rabbit_allergies->currentText();
      input[QString("budget")] = ui->client_rabbit_cost->text();
      input[QString("breed")] = ui->client_rabbit_breed->currentText();
      input[QString("gender")] = ui->client_rabbit_gender->currentText();
      input[QString("colour")] = ui->client_rabbit_colour->currentText();
      input[QString("social")] = ui->client_rabbit_social->text();
      input[QString("tamed")] = ui->client_rabbit_tamed->currentText();
      input[QString("temperament")] = ui->client_rabbit_temperament->text();
      input[QString("sensitivity")] = ui->client_rabbit_sensitivity->text();

    if(ui->client_rabbit_dog->isChecked())
        others+="D";
    if(ui->client_rabbit_cat->isChecked())
        others+= "C";
    if(ui->client_rabbit_bird->isChecked())
        others+= "B";
    if(ui->client_rabbit_rabbit->isChecked())
        others+= "R";
    if(ui->client_rabbit_hamster->isChecked())
        others+= "H";
    if(ui->client_rabbit_guineaPig->isChecked())
        others+= "G";
    if(ui->client_rabbit_none->isChecked())
        others+= "N";

    input[QString("other_pets")] = others;
}
void ViewEditClientDialog::clientUpdateHamster(QHash<QString, QString> &input){
    input[QString("name")] = ui->client_hamster_name->text();
    input[QString("email")] = ui->client_hamster_email->text();
    input[QString("phone_number")] = ui->client_hamster_phoneNumber->text();
    input[QString("animal_type")] = ui->client_animal_type->currentText();
    input[QString("allergies")] = ui->client_hamster_allergies->currentText();
    input[QString("kids")] = ui->client_hamster_kid_friendly->currentText();
    input[QString("budget")] = ui->client_hamster_cost->text();
    input[QString("breed")] = ui->client_hamster_breed->currentText();
    input[QString("gender")] = ui->client_hamster_gender->currentText();
    input[QString("colour")] = ui->client_hamster_colour->currentText();
    input[QString("attention")] = ui->client_hamster_attention->text();
    input[QString("social")] = ui->client_hamster_social->text();
    input[QString("tamed")] = ui->client_hamster_tamed->currentText();
    input[QString("nocturnal")] = ui->client_hamster_nocturnal->currentText();
    input[QString("cleaning")] = ui->client_hamster_cleaning->text();
    input[QString("feeding")] = ui->client_hamster_feeding->text();
}
void ViewEditClientDialog::clientUpdateGuineaPig(QHash<QString, QString> &input){
    input[QString("name")] = ui->client_guineaPig_name->text();
    input[QString("email")] = ui->client_guineaPig_email->text();
    input[QString("phone_number")] = ui->client_guineaPig_phoneNumber->text();
    input[QString("animal_type")] = ui->client_animal_type->currentText();
    input[QString("allergies")] = ui->client_guineaPig_allergies->currentText();
    input[QString("kids")] = ui->client_guineaPig_kid_friendly->currentText();
    input[QString("budget")] = ui->client_guineaPig_cost->text();
    input[QString("breed")] = ui->client_guineaPig_breed->currentText();
    input[QString("gender")] = ui->client_guineaPig_gender->currentText();
    input[QString("colour")] = ui->client_guineaPig_colour->currentText();
    input[QString("attention")] = ui->client_guineaPig_attention->text();
    input[QString("social")] = ui->client_guineaPig_social->text();
    input[QString("tamed")] = ui->client_guineaPig_tamed->currentText();
    input[QString("cleaning")] = ui->client_guineaPig_cleaning->text();
    input[QString("feeding")] = ui->client_guineaPig_feeding->text();
}




void ViewEditClientDialog::on_saveButton_clicked()
{
    QHash<QString, QString> input;
    input[QString("id")] = clientID;
    bool prefChanged = false;
    if(ui->client_animal_type->currentText() != animal_type)
    {
        prefChanged = true;
        //send a query to the database to clear all fields that pertain to the previous type
    }
    switch (ui->client_animal_type->currentIndex()) {
        case 1:
            clientUpdateDog(input);
            break;
        case 2:
            clientUpdateCat(input);
            break;
        case 3:
            clientUpdateBird(input);
            break;
        case 4:
            clientUpdateRabbit(input);
            break;
        case 5:
            clientUpdateHamster(input);
            break;
        case 6:
            clientUpdateGuineaPig(input);
            break;
        default:
            break;
    }


    QString errMsg;

    if(dbControl->dbRequest(&input, NULL, UPDATE_CLIENT, &errMsg, &prefChanged))
    {
        QMessageBox::information(this,tr("Save"),tr("Saved"));
        this->close();
    }
    else
    {
        QMessageBox::critical(this, tr("Error!"), errMsg);
        //this->clearFields();
    }
}
