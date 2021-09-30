#include "widget.h"
#include "utils.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // lors du lancement de l'application, on vérifie que le dossier images/images_boites existe bien dans le repertoire actif et on le créé si necessaire
    newDir("images/images_boites");

    /*
     *
     * structure du programme
     *
     * */
    mainLayout = new QHBoxLayout;

    stackedWidget = new QStackedWidget;

    page_login = new QWidget;
    page_code_barres = new QWidget;
    page_resultat = new QWidget;

    stackedWidget->addWidget(page_login);
    stackedWidget->addWidget(page_code_barres);
    stackedWidget->addWidget(page_resultat);

    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    stackedWidget->setCurrentWidget(page_login);

    // page_login
    page_loginLayout = new QVBoxLayout;

    page_loginGroupBox = new QGroupBox;
    page_loginGroupBox->setTitle("Connexion au compte :");

    page_loginGroupBoxLayout = new QFormLayout;

    page_loginLineEditPseudo = new QLineEdit;
    page_loginLineEditPassword = new QLineEdit;

    page_loginGroupBoxLayout->addRow("Pseudo :", page_loginLineEditPseudo);
    page_loginGroupBoxLayout->addRow("Mot de passe :", page_loginLineEditPassword);

    page_loginLineEditPseudo->setText("operateur2");
    page_loginLineEditPassword->setText("password2");

    page_loginGroupBox->setLayout(page_loginGroupBoxLayout);
    page_loginLayout->addWidget(page_loginGroupBox);

    page_loginDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    page_loginLayout->addWidget(page_loginDialogButtonBox);

    page_login->setLayout(page_loginLayout);

    connect(page_loginDialogButtonBox, &QDialogButtonBox::accepted, this, [&] () {
        /*
         *
         * paramètres de connexion à la bdd
         * quand le programme sera opérationel, changer ces infos par celle du serveur bdd ovh
         *
         * */

        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        //db.setUserName("root");
        db.setUserName(page_loginLineEditPseudo->text());
        //db.setPassword("1234");
        db.setPassword(page_loginLineEditPassword->text());
        db.setDatabaseName("yoti_test");


        /*
            // connexion bdd ovh
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName("rl239142-001.dbaas.ovh.net");
            db.setPort(35191);
            //db.setUserName("loic");
            db.setUserName(page_loginLineEditPseudo->text());
            //db.setPassword("qZJchZ7T");
            db.setPassword(page_loginLineEditPassword->text());
            db.setDatabaseName("jouets");
*/

        if(db.open())
        {
            stackedWidget->setCurrentWidget(page_code_barres);

            /*
             * page_code_barres
             *
             * */
            page_code_barresLayout = new QVBoxLayout;

            page_code_barresGroupBox = new QGroupBox;
            page_code_barresGroupBox->setTitle("Code-barres d'identification :");
            page_code_barresGroupBoxLayout = new QFormLayout;

            page_code_barresLineEditCodeBarres = new QLineEdit;

            page_code_barresGroupBoxLayout->addRow("Code-barres :", page_code_barresLineEditCodeBarres);

            page_code_barresGroupBox->setLayout(page_code_barresGroupBoxLayout);

            page_code_barresLayout->addWidget(page_code_barresGroupBox);

            page_rechercheDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            connect(page_rechercheDialogButtonBox, &QDialogButtonBox::accepted, this, &Widget::page_code_barresAccepted);
            connect(page_rechercheDialogButtonBox, &QDialogButtonBox::rejected, this, [&]() {

            });
            page_code_barresLayout->addWidget(page_rechercheDialogButtonBox);

            page_code_barres->setLayout(page_code_barresLayout);

            // page_resultat
            page_resultatLayout = new QVBoxLayout;

            page_resultatScrollArea = new QScrollArea;
            page_resultatScrollArea->setWidgetResizable(true);
            page_resultatWidget = new QWidget;
            page_resultatWidgetLayout = new QVBoxLayout;

            page_resultatGroupBoxFicheJeuSociete = new QGroupBox;
            page_resultatGroupBoxFicheJeuSociete->setTitle("Création/Validation fiche produit :");

            page_resultatGroupBoxFicheJeuSocieteLayout = new QFormLayout;

            page_resultatPhotoAffiche = new QLabel;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Photo :", page_resultatPhotoAffiche);

            page_resultatLineEditNom = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Nom du jeu :", page_resultatLineEditNom);

            page_resultatLineEditEdition = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Edition :", page_resultatLineEditEdition);

            page_resultatLineEditEditeur = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Editeur :", page_resultatLineEditEditeur);

            page_resultatLineEditAge = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Age :", page_resultatLineEditAge);

            page_resultatLineEditNbJoueurs = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Nombre de joueurs :", page_resultatLineEditNbJoueurs);

            page_resultatCheckBoxNormeCE = new QCheckBox;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Norme CE :", page_resultatCheckBoxNormeCE);

            page_resultatLineEditLongueur = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Longueur (cm) :", page_resultatLineEditLongueur);

            page_resultatLineEditLargeur = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Largeur (cm) :", page_resultatLineEditLargeur);

            page_resultatLineEditHauteur = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Hauteur (cm) :", page_resultatLineEditHauteur);

            page_resultatLineEditPoids = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Poids (kg) :", page_resultatLineEditPoids);

            page_resultatTextEditDescription = new QTextEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Description :", page_resultatTextEditDescription);

            page_resultatLineEditPrix = new QLineEdit;
            page_resultatGroupBoxFicheJeuSocieteLayout->addRow("Prix neuf ht eur :", page_resultatLineEditPrix);

            page_resultatGroupBoxFicheJeuSociete->setLayout(page_resultatGroupBoxFicheJeuSocieteLayout);

            page_resultatWidgetLayout->addWidget(page_resultatGroupBoxFicheJeuSociete);

            page_resultatDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

            connect(page_resultatDialogButtonBox, &QDialogButtonBox::accepted, this, &Widget::page_resultatAccepted);
            connect(page_resultatDialogButtonBox, &QDialogButtonBox::rejected, this, [&]() {
                stackedWidget->setCurrentWidget(page_code_barres);
            });

            page_resultatWidgetLayout->addWidget(page_resultatDialogButtonBox);

            page_resultatWidget->setLayout(page_resultatWidgetLayout);

            page_resultatScrollArea->setWidget(page_resultatWidget);

            page_resultatLayout->addWidget(page_resultatScrollArea);

            page_resultat->setLayout(page_resultatLayout);

            db.close();
        }
        else
        {
            QMessageBox::information(this, "Erreur login", "Informations de connexion erronées !");
        }
    });
}

Widget::~Widget()
{

}

void Widget::completerEditeur()
{
    // auto completion de l'éditeur
    // quand un nouvel editeur est traité il est ajouté dans la bdd
    QStringList stringListEditeurs;
    if(db.open())
    {
        QSqlQuery requeteEditeurs;

        if(requeteEditeurs.exec("SELECT * FROM nom_editeur;"))
        {
            while(requeteEditeurs.next())
            {
                stringListEditeurs << requeteEditeurs.value("pk_nom").toString();
            }
        }

        db.close();
    }
    else
    {
        qDebug() << "Erreur connection bdd !";
    }

    QCompleter *completer = new QCompleter(stringListEditeurs, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    page_resultatLineEditEditeur->setCompleter(completer);
}

void Widget::page_resultatAccepted()
{
    if(db.open())
    {
        QSqlQuery query;
        // on rajoute l'éditeur seulement s'il n'était pas déjà présent
        if(query.exec("INSERT INTO nom_editeur ( pk_nom ) VALUES ( '" + page_resultatLineEditEditeur->text() + "' )"))
        {
            query.exec("INSERT INTO editeur ( nom_editeur ) VALUES ( '" + page_resultatLineEditEditeur->text() + "' );");
            id_editeur = query.exec("SELECT LAST_INSERT_ID();");
        }
        else
        {
            if(query.exec("SELECT * FROM editeur WHERE nom_editeur = '" + page_resultatLineEditEditeur->text() + "';"))
            {
                while(query.next())
                {
                    id_editeur = query.value("id_editeur").toInt();
                }
            }
        }
        qDebug() << "id_editeur : " << id_editeur;

        QSqlQuery requeteUpdate;
        //QString requeteUpdateQString = "UPDATE jouet INNER JOIN exemplaire ON jouet.id_jouet = exemplaire.fk_id_jouet AND code_barres_exemplaire = '" + page_code_barresLineEditCodeBarres->text() + "' SET nom_jouet = '" + page_resultatLineEditNom->text() + "', annee_edition = " + page_resultatLineEditEdition->text() + ", age = '" + page_resultatLineEditAge->text() + "', nb_joueurs = '" + page_resultatLineEditNbJoueurs->text() + "', norme_ce = " + page_resultatCheckBoxNormeCE->isChecked() + ", hauteur_cm = " + page_resultatLineEditHauteur->text() + ", longueur_cm = " + page_resultatLineEditLongueur->text() + ", largeur_cm = " + page_resultatLineEditLargeur->text() + ", poids_kg = " + page_resultatLineEditPoids->text() + ", description_jouet = '" + page_resultatTextEditDescription->toPlainText() + "', prix_neuf_ht_eur = " + page_resultatLineEditPrix->text() + ";";
        QString requeteUpdateQString = "UPDATE jouet INNER JOIN exemplaire ON jouet.id_jouet = exemplaire.fk_id_jouet AND code_barres_exemplaire = '" + page_code_barresLineEditCodeBarres->text() + "' SET nom_jouet = '" + page_resultatLineEditNom->text() + "', annee_edition = " + page_resultatLineEditEdition->text() + ", age = '" + page_resultatLineEditAge->text() + "', nb_joueurs = '" + page_resultatLineEditNbJoueurs->text() + "', norme_ce = " + QString::number(page_resultatCheckBoxNormeCE->isChecked()) + ", hauteur_cm = " + page_resultatLineEditHauteur->text() + ", longueur_cm = " + page_resultatLineEditLongueur->text() + ", largeur_cm = " + page_resultatLineEditLargeur->text() + ", poids_kg = " + page_resultatLineEditPoids->text() + ", description_jouet = '" + page_resultatTextEditDescription->toPlainText() + "', prix_neuf_ht_eur = " + page_resultatLineEditPrix->text() + ", fk_id_editeur = " + QString::number(id_editeur) + ";";
        qDebug() << requeteUpdateQString;
        //page_resultatLineEditEditeur->setText(requeteFindCodeBarres.value("nom_editeur").toString());

        if(requeteUpdate.exec(requeteUpdateQString))
        {
            stackedWidget->setCurrentWidget(page_code_barres);
            initialisationChamps();
        }
        else
        {
            qDebug() << "erreur requeteUpdate";
        }
        db.close();
    }
    else
    {
        qDebug() << "erreur connection bdd";
    }
}

void Widget::page_code_barresAccepted()
{
    // recherche dans la table exemplaire par code-barres
    if(db.open())
    {
        QSqlQuery requeteFindCodeBarres;
        QString requeteFindCodeBarresQString = "SELECT * FROM exemplaire INNER JOIN jouet ON exemplaire.fk_id_jouet = jouet.id_jouet INNER JOIN photo ON exemplaire.fk_id_jouet = photo.fk_id_jouet WHERE code_barres_exemplaire = '" + page_code_barresLineEditCodeBarres->text() + "';";

        if(requeteFindCodeBarres.exec(requeteFindCodeBarresQString))
        {
            while(requeteFindCodeBarres.next())
            {
                id_jouet = requeteFindCodeBarres.value("fk_id_jouet").toInt();
                // dl de la photo
                QString s = qApp->applicationDirPath() + "/images/images_boites/tmp.jpg";
                QString s_url = requeteFindCodeBarres.value("url_photo").toString();
                qDebug() << s;
                qDebug() << s_url;
                downloadImage(s_url, s);
                delay();

                QPixmap pixPicture(qApp->applicationDirPath() + "/images/images_boites/tmp.jpg");
                page_resultatPhotoAffiche->setPixmap(pixPicture.scaled(800, 500, Qt::KeepAspectRatio));
                page_resultatLineEditNom->setText(requeteFindCodeBarres.value("nom_jouet").toString());
                page_resultatLineEditEdition->setText(requeteFindCodeBarres.value("annee_edition").toString());
                page_resultatLineEditAge->setText(requeteFindCodeBarres.value("age").toString());
                page_resultatLineEditNbJoueurs->setText(requeteFindCodeBarres.value("nb_joueurs").toString());
                page_resultatCheckBoxNormeCE->setChecked(requeteFindCodeBarres.value("norme_ce").toInt());
                page_resultatLineEditHauteur->setText(requeteFindCodeBarres.value("hauteur_cm").toString());
                page_resultatLineEditLongueur->setText(requeteFindCodeBarres.value("longueur_cm").toString());
                page_resultatLineEditLargeur->setText(requeteFindCodeBarres.value("largeur_cm").toString());
                page_resultatLineEditPoids->setText(requeteFindCodeBarres.value("poids_kg").toString());
                page_resultatTextEditDescription->setText(requeteFindCodeBarres.value("description_jouet").toString());
                page_resultatLineEditPrix->setText(requeteFindCodeBarres.value("prix_neuf_ht_eur").toString());
            }
            QSqlQuery query;
            QString s_query = "SELECT * FROM jouet INNER JOIN editeur ON jouet.fk_id_editeur = editeur.id_editeur WHERE id_jouet = " + QString::number(id_jouet) + ";";
            qDebug() << s_query;
            query.exec(s_query);
            while(query.next())
            {
                page_resultatLineEditEditeur->setText(query.value("nom_editeur").toString());
            }
        }
        else
        {
            qDebug() << "erreur requeteFindCodeBarres";
        }
        db.close();
    }
    else
    {
        qDebug() << "erreur connection bdd";
    }

    completerEditeur();
    stackedWidget->setCurrentWidget(page_resultat);
}

void Widget::initialisationChamps()
{
    page_code_barresLineEditCodeBarres->setText("");

    page_resultatLineEditNom->setText("");
    page_resultatLineEditEdition->setText("");
    page_resultatLineEditEditeur->setText("");
    page_resultatLineEditAge->setText("");
    page_resultatLineEditNbJoueurs->setText("");
    page_resultatCheckBoxNormeCE->setChecked(0);
    page_resultatLineEditHauteur->setText("");
    page_resultatLineEditLongueur->setText("");
    page_resultatLineEditLargeur->setText("");
    page_resultatLineEditPoids->setText("");
    page_resultatTextEditDescription->setText("");
    page_resultatLineEditPrix->setText("");

    completerEditeur();
}
