//
// Created by luigi on 07/12/2025.
//

#ifndef CRM_INSURAPRO_SOLUTIONS_CSV_UTILS_H
#define CRM_INSURAPRO_SOLUTIONS_CSV_UTILS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
* Scrive un elenco di record in un file CSV.
*
* @param filename Il nome del file in cui verranno scritti i record. Se il file esiste, verrà sovrascritto.
* @param records Un vettore di record, in cui ogni record è rappresentato come un vettore di stringhe.
* Ogni vettore interno corrisponde a una riga nel file CSV e ogni stringa corrisponde a una cella in quella riga.
*/
void write_all_records_to_csv(const string& filename, const vector<vector<string>>& records) {
    //apro file in modalita di sovrascrittura, sovrascrivendo eventuali contenuti esistenti
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Errore apertura file: " << filename << endl;
        return;
    }
    for (const auto& record : records) {
        for (size_t i = 0; i < record.size(); ++i) {
            file << record[i];
            if (i < record.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}

/**
* Scrive un record in un file CSV.
*
* @param filename Il nome del file in cui verrà scritto il record.
* @param data Un vettore di stringhe rappresentante il record da scrivere nel file CSV.
*/
void write_record_to_csv(string& filename, vector<string> data) {
    //apro file in modalita di append, senza sovrascrivere eventuali contenuti esistenti
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    if (data.empty()) return;

    string record;
    for (int i = 0; i < data.size(); ++i) {
        record += data[i];
        if (i != data.size() - 1) {
            record += ",";
        }
    }
    file << record << endl;

    file.close();

    cout << "Record aggiunto con successo" << endl;
}

/**
* Legge tutti i record da un file CSV.
*
* @param filename Il nome del file da cui leggere i record.
* @return Un vettore di vettori di stringhe rappresentanti i record letti dal file CSV.
*/
vector<vector<string>> read_records_from_csv(string& filename, int expected_fields = 6) {
    ifstream file(filename);

    if (!file.is_open()) {
        //Puo verificarci che il file non esiste
        ofstream newFile(filename);
        if (!newFile.is_open()) {
            cerr << "Errore apertura file: " << filename << endl;
            return {};
        } else {
            newFile.close();
            cout << "File " << filename << " creato (nessun cliente presente)." << endl;
            return {};
        }
    }

    vector<vector<string>> records;
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        stringstream ss(line);
        string field;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        /// garantisce sempre expected_fields elementi
        while (fields.size() < expected_fields) {
            fields.push_back("");
        }
        if (fields.size() > expected_fields) {
            fields.resize(expected_fields);
        }
        records.push_back(fields);
    }

    file.close();
    return records;
}

#endif //CRM_INSURAPRO_SOLUTIONS_CSV_UTILS_H