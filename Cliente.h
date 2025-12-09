//
// Created by luigi on 08/12/2025.
//

#ifndef CRM_INSURAPRO_SOLUTIONS_CLIENTE_H
#define CRM_INSURAPRO_SOLUTIONS_CLIENTE_H
#include <string>
#include <vector>
using namespace std;

inline string CLIENTS_CSV_FILE = "clienti.csv";

class Cliente {
    int id;
    string nome;
    string cognome;
    string email;
    string telefono;
    string indirizzo;

    // Dichiarazione delle friend functions (possono accedere ai membri privati)
    friend vector<string> toCSVRecord(const Cliente& cliente);
    friend Cliente toCliente(const vector<string>& record);

public:
    Cliente() = default;

    Cliente(int _id);

    Cliente(int _id, const string& _nome, const string& _cognome, const string& _email,
            const string& _telefono, const string& _indirizzo);

    int getId() const;

    void setNome(const string& _nome);
    void setCognome(const string& _cognome);
    void setEmail(const string& _email);
    void setTelefono(const string& _telefono);
    void setIndirizzo(const string& _indirizzo);

    string getNome() const;
    string getCognome() const;
    string getEmail() const;
    string getTelefono() const;
    string getIndirizzo() const;

    ~Cliente() = default;
};

vector<string> toCSVRecord(const Cliente& cliente);
Cliente toCliente(const vector<string>& record);
#endif //CRM_INSURAPRO_SOLUTIONS_CLIENTE_H