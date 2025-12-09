//
// Created by luigi on 08/12/2025.
//
#include "Cliente.h"
#include <iostream>  // Per cerr in toCliente

using namespace std;

Cliente::Cliente(int _id) : id(_id) {}

Cliente::Cliente(int _id, const string& _nome, const string& _cognome, const string& _email,
                 const string& _telefono, const string& _indirizzo)
    : id(_id), nome(_nome), cognome(_cognome), email(_email), telefono(_telefono), indirizzo(_indirizzo) {}

int Cliente::getId() const { return id; }

void Cliente::setNome(const string& _nome) { nome = _nome; }
void Cliente::setCognome(const string& _cognome) { cognome = _cognome; }
void Cliente::setEmail(const string& _email) { email = _email; }
void Cliente::setTelefono(const string& _telefono) { telefono = _telefono; }
void Cliente::setIndirizzo(const string& _indirizzo) { indirizzo = _indirizzo; }

string Cliente::getNome() const { return nome; }
string Cliente::getCognome() const { return cognome; }
string Cliente::getEmail() const { return email; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getIndirizzo() const { return indirizzo; }


vector<string> toCSVRecord(const Cliente& cliente) {
    return {to_string(cliente.id), cliente.nome, cliente.cognome, cliente.email, cliente.telefono, cliente.indirizzo};
};

Cliente toCliente(const vector<string>& record) {
    if (record.size() != 6) {
        cerr << "Errore: record CSV non valido" << endl;
        return {};
    }
    int id = stoi(record[0]);
    return Cliente(id, record[1], record[2], record[3], record[4], record[5]);
};