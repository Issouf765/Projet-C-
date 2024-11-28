#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Classe Destination
class Destination {
public:
    string nom;
    string pays;
    vector<string> attractions;

    Destination(string n, string p, vector<string> att) : nom(n), pays(p), attractions(att) {}

    void afficher() const {
        cout << "========================" << endl;
        cout << "Nom: " << nom << "\nPays: " << pays << endl;
        cout << "Attractions principales: ";
        for (const string& attraction : attractions) {
            cout << attraction << " ";
        }
        cout << "\n========================" << endl;
    }
};

// Classe Reservation
class Reservation {
public:
    string nomClient;
    string numeroTelephone;
    Destination destination;
    double tarif;

    Reservation(string client, string tel, Destination dest, double t)
        : nomClient(client), numeroTelephone(tel), destination(dest), tarif(t) {}

    void afficher() const {
        cout << "========================" << endl;
        cout << "Client: " << nomClient << "\nTel: " << numeroTelephone << endl;
        cout << "Destination: " << destination.nom << ", " << destination.pays << endl;
        cout << "Tarif: " << tarif << " FCFA" << endl;
        cout << "========================" << endl;
    }
};

// Classe CompagnieDeVoyage
class CompagnieDeVoyage {
private:
    vector<Destination> destinations;
    vector<Reservation> reservations;

public:
    // Ajouter une destination
    void ajouterDestination() {
        string nom, pays, attraction;
        vector<string> attractions;

        cout << "\n--- Ajouter une Destination ---" << endl;
        cout << "Entrez le nom de la destination: ";
        cin.ignore();
        getline(cin, nom);

        cout << "Entrez le pays de la destination: ";
        getline(cin, pays);

        cout << "Entrez les attractions principales (Entrez 'fin' pour terminer):" << endl;
        while (true) {
            cout << "Attraction: ";
            getline(cin, attraction);
            if (attraction == "fin") break;
            attractions.push_back(attraction);
        }

        destinations.push_back(Destination(nom, pays, attractions));
        cout << "Destination ajoutee avec succes !" << endl;
    }

    // Afficher toutes les destinations
    void afficherDestinations() {
        cout << "\n--- Liste des Destinations ---" << endl;
        if (destinations.empty()) {
            cout << "Aucune destination disponible." << endl;
            return;
        }

        for (const Destination& d : destinations) {
            d.afficher();
        }
    }

    // Ajouter une reservation
    void ajouterReservation() {
        string nomClient, numeroTelephone, destinationNom;
        double tarif;

        cout << "\n--- Ajouter une Reservation ---" << endl;
        cout << "Entrez le nom du client: ";
        cin.ignore();
        getline(cin, nomClient);

        cout << "Entrez le numero de telephone du client: ";
        getline(cin, numeroTelephone);

        cout << "Entrez la destination choisie: ";
        getline(cin, destinationNom);

        cout << "Entrez le tarif de la reservation: ";
        cin >> tarif;

        // Chercher la destination
        for (const Destination& dest : destinations) {
            if (dest.nom == destinationNom) {
                reservations.push_back(Reservation(nomClient, numeroTelephone, dest, tarif));
                cout << "Reservation ajoutee avec succes !" << endl;
                return;
            }
        }
        cout << "Destination introuvable !" << endl;
    }

    // Afficher les reservations d'une destination specifique
    void afficherReservationsParDestination() {
        string destinationNom;

        cout << "\n--- Afficher les Reservations par Destination ---" << endl;
        cout << "Entrez le nom de la destination pour afficher les reservations: ";
        cin.ignore();
        getline(cin, destinationNom);

        bool trouve = false;
        for (const Reservation& res : reservations) {
            if (res.destination.nom == destinationNom) {
                res.afficher();
                trouve = true;
            }
        }
        if (!trouve) {
            cout << "Aucune reservation trouvee pour cette destination." << endl;
        }
    }

    // Modifier une reservation
    void modifierReservation() {
        string nomClient, nouveauNomClient, nouveauNumero;
        double nouveauTarif;

        cout << "\n--- Modifier une Reservation ---" << endl;
        cout << "Entrez le nom du client a modifier: ";
        cin.ignore();
        getline(cin, nomClient);

        for (Reservation& res : reservations) {
            if (res.nomClient == nomClient) {
                cout << "Entrez le nouveau nom du client: ";
                getline(cin, nouveauNomClient);
                cout << "Entrez le nouveau numero de telephone: ";
                getline(cin, nouveauNumero);
                cout << "Entrez le nouveau tarif: ";
                cin >> nouveauTarif;

                res.nomClient = nouveauNomClient;
                res.numeroTelephone = nouveauNumero;
                res.tarif = nouveauTarif;
                cout << "Reservation modifiee avec succes !" << endl;
                return;
            }
        }
        cout << "Reservation introuvable !" << endl;
    }

    // Annuler une reservation
    void annulerReservation() {
        string nomClient;

        cout << "\n--- Annuler une Reservation ---" << endl;
        cout << "Entrez le nom du client a annuler: ";
        cin.ignore();
        getline(cin, nomClient);

        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if (it->nomClient == nomClient) {
                reservations.erase(it);
                cout << "Reservation annulee avec succes !" << endl;
                return;
            }
        }
        cout << "Reservation introuvable !" << endl;
    }

    // Generer un rapport des revenus par destination
    void genererRapportRevenus() {
        cout << "\n--- Rapport des Revenus par Destination ---" << endl;
        for (const Destination& dest : destinations) {
            double revenu = 0.0;
            int nombreReservations = 0;
            for (const Reservation& res : reservations) {
                if (res.destination.nom == dest.nom) {
                    revenu += res.tarif;
                    nombreReservations++;
                }
            }
            cout << dest.nom << " (" << dest.pays << ") : " << nombreReservations << " reservations, Revenu: " << revenu << " FCFA" << endl;
        }
    }

    // Exporter les informations de reservation dans un fichier
    void exporterReservations() {
        string fichier;
        cout << "\n--- Exporter les Reservations ---" << endl;
        cout << "Entrez le nom du fichier d'exportation: ";
        cin >> fichier;

        ofstream out(fichier);
        if (out.is_open()) {
            for (const Reservation& res : reservations) {
                out << res.nomClient << "," << res.numeroTelephone << "," << res.destination.nom << "," << res.tarif << endl;
            }
            cout << "Informations exportees avec succes dans " << fichier << endl;
        } else {
            cout << "Erreur lors de l'ouverture du fichier !" << endl;
        }
    }

    // Afficher le menu et choisir l'action
    void menu() {
        int choix;
        do {
            cout << "\n========================" << endl;
            cout << "        MENU        " << endl;
            cout << "========================" << endl;
            cout << "1. Ajouter une destination" << endl;
            cout << "2. Afficher toutes les destinations" << endl;
            cout << "3. Ajouter une reservation" << endl;
            cout << "4. Afficher les reservations par destination" << endl;
            cout << "5. Modifier une reservation" << endl;
            cout << "6. Annuler une reservation" << endl;
            cout << "7. Generer un rapport des revenus" << endl;
            cout << "8. Exporter les reservations dans un fichier" << endl;
            cout << "9. Quitter" << endl;
            cout << "========================" << endl;
            cout << "Votre choix: ";
            cin >> choix;

            switch (choix) {
                case 1:
                    ajouterDestination();
                    break;
                case 2:
                    afficherDestinations();
                    break;
                case 3:
                    ajouterReservation();
                    break;
                case 4:
                    afficherReservationsParDestination();
                    break;
                case 5:
                    modifierReservation();
                    break;
                case 6:
                    annulerReservation();
                    break;
                case 7:
                    genererRapportRevenus();
                    break;
                case 8:
                    exporterReservations();
                    break;
                case 9:
                    cout << "Au revoir et a bientot!" << endl;
                    break;
                default:
                    cout << "Choix invalide, essayez a nouveau." << endl;
            }
        } while (choix != 9);
    }
};

int main() {
    CompagnieDeVoyage compagnie;
    compagnie.menu();
    return 0;
}
