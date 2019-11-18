//
// Created by eric on 02/09/19.
//

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
#include "Banque.h"
#include "utils.h"


using namespace std;

Banque::Banque():nbclients(0) {

}

void Banque::ajouterclient(const string &nom_du_client) {
    clients[nbclients]=Client(nom_du_client);
    nbclients++;

}

void Banque::bilanclient(const  int numeroduclient) {


        for(int i=0;i<clients[numeroduclient].getNbcomptes();i++)
        {

            clients[numeroduclient].afficherSolde(i);
        }


}

void Banque::afficherBilan() {
    for(int i=0;i<nbclients;i++)
    {
        bilanclient(i);
    }

}

 Client *Banque::getClients() {
    return clients;
}

void Banque::interaction() {
    int saisie=0;
    cout<<"Quel opération voulez-vous effectuer?"<<endl;
    cout<<"1-Ajouter un client"<<endl;
    cout<<"2-Effectuer une opération sur un client"<<endl;
    cout<<"3-Afficher un bilan général"<<endl;
    cin>>saisie;

    switch (saisie)
    {
        case 1:
            while(true) {
                try {
                    this->ajouterclient(this->saisieClient());
                    break;
                } catch (runtime_error &re) {
                    cout << re.what() << endl;

                }
            }
     break;
        case 2:
            while(true) {
                try {
                    this->opclient(this->choix("client", nbclients));
                    break;
                } catch (invalid_argument &iv)
                {
                    cout<<"Erreur veuillez saisir un nombre"<<endl;
                }
                catch (runtime_error &re)
                {
                    cout<<re.what()<<endl;
                }
            }
        case 3:
            this->afficherBilan();
            break;

        default:
            cout<<"entrée invalide"<<endl;
            interaction();

    }


    interaction(); //Recursivité
}

string Banque::saisieClient() {
    string saisie="";
    cout<<"Veuillez saisir un nom\n";
    cin>>saisie;
    if(!utils::is_alpha(saisie))
    {
        throw runtime_error("Veuillez saisir uniquement des caractères alphabetiques");
    }
    return saisie;
}

void Banque::opclient(int numcli) {
    int saisie=0;
    cout<<"1-Créer un compte\n";
    cout<<"2-Créditer\n";
    cout<<"3-Débiter\n";
    cout<<"4-Virer\n";
    cout<<"5-Afficher un bilan\n";
    cout<<"6-Retour au menu principal\n";
    cin>>saisie;

        switch (saisie) {
            case 1:
                clients[numcli].ajouterCompte();
                break;
            case 2:
                while(true) {
                    try {
                        clients[numcli].getComptes()[this->choix("compte", clients[numcli].getNbcomptes())].depot(
                                this->choixMontant());
                        break;
                    }catch (invalid_argument &iv)
                    {
                        cout<<"La saisie doit être un nombre"<<endl;
                    }
                }
            case 3:
                while(true) {
                    try {
                        clients[numcli].getComptes()[this->choix("compte", clients[numcli].getNbcomptes())].retrait(
                                this->choixMontant());
                        break;
                    }catch (invalid_argument &iv)
                    {
                        cout<<"La saisie doit être un nombre"<<endl;
                    }
                }



            case 4:
                while(true) {
                    try {
                        clients[numcli].getComptes()[this->choix("compte", clients[numcli].getNbcomptes())].
                                virer(this->choixMontant(), clients[this->choix("client", nbclients)].
                                getComptes()[this->choix("compte", clients[numcli].getNbcomptes())]);
                        break;
                    }catch (invalid_argument &iv)
                    {
                        cout<<"La saisie doit être un nombre"<<endl;
                    }
                }



            case 5:

                bilanclient(numcli);
                break;

            case 6:
                this->interaction();
                break;


        }


    this->opclient(numcli);

}

int Banque::choix(string type,int limit) {
    string saisie="";
    for(int i=0;i<limit;i++)
    {
        cout<<i<<endl;
    }
    cout<<"Veuillez choisir un "<<type<<endl;
    cin>>saisie;
    int numerosaisie=stoi(saisie); //lance une exception su conversion impossible
    if(numerosaisie<0||numerosaisie>=limit)
    {
        throw runtime_error("Veuillez saisir dans la plage indiquée");
    }

    return stoi(saisie);

}

float Banque::choixMontant() {
    string montant;
    cout << "Veuillez donner un montant";
    cin >> montant;


    return stof(montant);
}






