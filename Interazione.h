//
// Created by luigi on 09/12/2025.
//

#ifndef CRM_INSURAPRO_SOLUTIONS_INTERAZIONE_H
#define CRM_INSURAPRO_SOLUTIONS_INTERAZIONE_H

#include <string>
#include <vector>
using namespace std;

inline string INTERACTIONS_CSV_FILE = "interazioni.csv";

class Interazione {
    int id;
    int id_cliente;
    string tipo;  // "appuntamento" o "contratto"
    string data;
    string descrizione;
    string stato;  // per appuntamenti: "programmato", "completato", "cancellato"
    // per contratti: "attivo", "scaduto", "annullato"

    friend vector<string> toCSVRecordInterazione(const Interazione& interazione);
    friend Interazione toInterazione(const vector<string>& record);

public:
    Interazione() = default;

    Interazione(int _id);

    Interazione(int _id, int _id_cliente, const string& _tipo, const string& _data,
                const string& _descrizione, const string& _stato);

    int getId() const;
    int getIdCliente() const;

    void setTipo(const string& _tipo);
    void setData(const string& _data);
    void setDescrizione(const string& _descrizione);
    void setStato(const string& _stato);

    string getTipo() const;
    string getData() const;
    string getDescrizione() const;
    string getStato() const;

    ~Interazione() = default;
};

vector<string> toCSVRecordInterazione(const Interazione& interazione);
Interazione toInterazione(const vector<string>& record);

#endif //CRM_INSURAPRO_SOLUTIONS_INTERAZIONE_H