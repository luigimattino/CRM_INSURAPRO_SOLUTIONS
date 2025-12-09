//
// Created by luigi on 09/12/2025.
//
#include "Interazione.h"
#include <iostream>  // Per cerr in toInterazione

using namespace std;

Interazione::Interazione(int _id) : id(_id) {}

Interazione::Interazione(int _id, int _id_cliente, const string& _tipo, const string& _data,
                         const string& _descrizione, const string& _stato)
    : id(_id), id_cliente(_id_cliente), tipo(_tipo), data(_data), descrizione(_descrizione), stato(_stato) {}

int Interazione::getId() const { return id; }
int Interazione::getIdCliente() const { return id_cliente; }

void Interazione::setTipo(const string& _tipo) { tipo = _tipo; }
void Interazione::setData(const string& _data) { data = _data; }
void Interazione::setDescrizione(const string& _descrizione) { descrizione = _descrizione; }
void Interazione::setStato(const string& _stato) { stato = _stato; }

string Interazione::getTipo() const { return tipo; }
string Interazione::getData() const { return data; }
string Interazione::getDescrizione() const { return descrizione; }
string Interazione::getStato() const { return stato; }


vector<string> toCSVRecordInterazione(const Interazione& interazione) {
    return {to_string(interazione.id), to_string(interazione.id_cliente), interazione.tipo,
            interazione.data, interazione.descrizione, interazione.stato};
};

Interazione toInterazione(const vector<string>& record) {
    if (record.size() != 6) {
        cerr << "Errore: record CSV non valido per interazione" << endl;
        return {};
    }
    int id = stoi(record[0]);
    int id_cliente = stoi(record[1]);
    return Interazione(id, id_cliente, record[2], record[3], record[4], record[5]);
};