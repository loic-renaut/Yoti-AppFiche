#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QSqlDatabase>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void page_code_barresAccepted();

    void page_resultatAccepted();

    void completerEditeur();

    void initialisationChamps();

    void timer_initialisation();

    QStringList chargementEtatBoite();

    QStringList chargementEtatContenu();

private:
    // variables globales
    QTimer* timer1s;
    QElapsedTimer timer;
    int id_editeur;
    int id_jouet;
    int id_operateur;

    // bdd
    QSqlDatabase db;

    // structure generale du programme
    QHBoxLayout* mainLayout;
    QStackedWidget* stackedWidget;

    // page_login
    QWidget* page_login;
    QVBoxLayout* page_loginLayout;

    QGroupBox* page_loginGroupBox;
    QFormLayout* page_loginGroupBoxLayout;

    QLineEdit* page_loginLineEditPseudo;
    QLineEdit* page_loginLineEditPassword;

    QDialogButtonBox* page_loginDialogButtonBox;

    // page_code_barres
    QWidget* page_code_barres;
    QVBoxLayout* page_code_barresLayout;
    QGroupBox* page_code_barresGroupBox;
    QFormLayout* page_code_barresGroupBoxLayout;
    QLineEdit* page_code_barresLineEditCodeBarres;
    QDialogButtonBox* page_rechercheDialogButtonBox;

    // page_resultat
    QWidget* page_resultat;
    QVBoxLayout* page_resultatLayout;

    QScrollArea* page_resultatScrollArea;
    QWidget* page_resultatWidget;
    QVBoxLayout* page_resultatWidgetLayout;

    QGroupBox* page_resultatGroupBoxFicheJeuSociete;
    QFormLayout* page_resultatGroupBoxFicheJeuSocieteLayout;
    QLabel* page_resultatPhotoAffiche;
    QLineEdit* page_resultatLineEditNom;
    QLineEdit* page_resultatLineEditEdition;
    QLineEdit* page_resultatLineEditEditeur;
    QLineEdit* page_resultatLineEditAge;
    QLineEdit* page_resultatLineEditNbJoueurs;
    QCheckBox* page_resultatCheckBoxNormeCE;
    QLineEdit* page_resultatLineEditHauteur;
    QLineEdit* page_resultatLineEditLongueur;
    QLineEdit* page_resultatLineEditLargeur;
    QLineEdit* page_resultatLineEditPoids;
    QTextEdit* page_resultatTextEditDescription;
    QLineEdit* page_resultatLineEditPrix;
    QCheckBox* page_resultatCheckBoxIsFull;
    QComboBox* page_resultatComboBoxEtatBoite;
    QComboBox* page_resultatComboBoxEtatContenu;
    QDialogButtonBox* page_resultatDialogButtonBox;
};

#endif // WIDGET_H
