/**
 * Progetto di CRM per impresa di assicurazioni.
 * InsuraPro Solutions
 *
 */

#include <iostream>
#include <vector>
#include <sstream> // string stream
#include "csv_utils.h"
#include "Cliente.h"
#include "Interazione.h"

using namespace std;

/**
* Divide la stringa di input specificata in un vettore di sottostringhe (token) in base agli spazi vuoti.
*
* La funzione legge la stringa di input utilizzando un flusso di stringhe ed estrae le sottostringhe
* separate da spazi. Ogni token viene aggiunto al vettore risultante, che viene quindi restituito.
* Gli spazi vuoti consecutivi vengono trattati come un singolo delimitatore.
*
* @param input La stringa di input da tokenizzare.
* @return Un vettore contenente i token estratti dalla stringa di input.
*/
vector<string> split(const string& input) {
    vector<string> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
* Gestisce la visualizzazione paginata dei risultati.
* Mostra PAGE_SIZE risultati alla volta e chiede all'utente se continuare o terminare.
*
* @param current_index L'indice corrente nella visualizzazione
* @param total_size Il numero totale di risultati
* @return true se l'utente vuole continuare, false se vuole terminare (skip)
*/
bool handle_pagination(int current_index, int total_size) {
    const int PAGE_SIZE = 5; // Numero di risultati per pagina

    if ((current_index + 1) % PAGE_SIZE == 0 && current_index + 1 < total_size) {
        cout << "\n--- Mostrati " << (current_index + 1) << " di " << total_size
             << " risultati. Premi INVIO per continuare o digita 'q' per terminare > ";
        string user_input;
        getline(cin, user_input);
        if (user_input == "q") {
            cout << "Visualizzazione terminata dall'utente." << endl;
            return false;
        }
    }
    return true;
}

/**
* Carica tutti i clienti dal file CSV dei clienti.
*
* Legge il file CSV dei clienti e crea un vettore di oggetti Cliente.
*
* @return Un vettore di oggetti Cliente caricati dal file CSV.
*/
vector<Cliente> load_all_clients() {
    vector<Cliente> clienti;
    vector<vector<string>> records = read_records_from_csv(CLIENTS_CSV_FILE, 6);
    for (int x = 0; x < records.size(); x++) {
        const vector<string>& record = records[x];
        clienti.push_back(toCliente(record));
    }
    return clienti;
}

/**
* Salva tutti i clienti nel file CSV dei clienti.
*
* Scrive il vettore di oggetti Cliente nel file CSV dei clienti.
*
* @param clienti Un vettore di oggetti Cliente da salvare.
*/
void save_all_clients(const vector<Cliente>& clienti) {
    vector<vector<string>> records;
    for (int x = 0; x < clienti.size(); x++) {
        records.push_back(toCSVRecord(clienti[x]));
    }
    write_all_records_to_csv(CLIENTS_CSV_FILE, records);
}

/**
* Verifica se un cliente esiste dato il suo ID.
*
* @param clienti Un vettore di oggetti Cliente.
* @param id_cliente L'ID del cliente da verificare.
* @return true se il cliente esiste, false altrimenti.
*/
bool cliente_exists(const vector<Cliente>& clienti, int id_cliente) {
    for (int x = 0; x < clienti.size(); x++) {
        if (clienti[x].getId() == id_cliente) {
            return true;
        }
    }
    return false;
}

/**
* Ottiene l'ID massimo tra tutti i clienti.
*
* @param clienti Un vettore di oggetti Cliente.
* @return L'ID massimo tra tutti i clienti.
*/
int get_max_client_id(const vector<Cliente>& clienti) {
    int max_id = 0;
    for (int x = 0; x < clienti.size(); x++) {
        Cliente c = clienti[x];
        if (c.getId() > max_id) max_id = c.getId();
    }
    return max_id;
}

/**
* Carica tutte le interazioni dal file CSV delle interazioni.
*
* Legge il file CSV delle interazioni e crea un vettore di oggetti Interazione.
*
* @return Un vettore di oggetti Interazione caricati dal file CSV.
*/
vector<Interazione> load_all_interactions() {
    vector<Interazione> interazioni;
    vector<vector<string>> records = read_records_from_csv(INTERACTIONS_CSV_FILE);
    for (int x = 0; x < records.size(); x++) {
        const vector<string>& record = records[x];
        interazioni.push_back(toInterazione(record));
    }
    return interazioni;
}

/**
* Salva tutte le interazioni nel file CSV delle interazioni.
*
* Scrive il vettore di oggetti Interazione nel file CSV delle interazioni.
*
* @param interazioni Un vettore di oggetti Interazione da salvare.
*/
void save_all_interactions(const vector<Interazione>& interazioni) {
    vector<vector<string>> records;
    for (int x = 0; x < interazioni.size(); x++) {
        records.push_back(toCSVRecordInterazione(interazioni[x]));
    }
    write_all_records_to_csv(INTERACTIONS_CSV_FILE, records);
}

/**
* Ottiene l'ID massimo tra tutte le interazioni.
*
* @param interazioni Un vettore di oggetti Interazione.
* @return L'ID massimo tra tutte le interazioni.
*/
int get_max_interaction_id(const vector<Interazione>& interazioni) {
    int max_id = 0;
    for (int x = 0; x < interazioni.size(); x++) {
        Interazione i = interazioni[x];
        if (i.getId() > max_id) max_id = i.getId();
    }
    return max_id;
}

int main() {
    //Inizializzazione
    vector<Cliente> clienti = load_all_clients();
    cout << "InsuraPro Solutions - Caricati " << clienti.size() << " clienti dal database." << endl;
    vector<Interazione> interazioni = load_all_interactions();
    cout << "InsuraPro Solutions - Caricate " << interazioni.size() << " interazioni dal database." << endl;

    int curr_cli_id = get_max_client_id(clienti) + 1;
    int curr_int_id = get_max_interaction_id(interazioni) + 1;

    cout << "InsuraPro Solutions - Command Shell (digita 'help' per conoscere i comandi, 'exit' per terminare)" << endl;

    string input;
    while (true) {
        cout << "inserisci cmd > ";  // Prompt
        getline(cin, input);// uso getline perche comodo nella gestione delle stringhe

        if (input.empty()) continue;  // elimina le linee vuote

        auto tokens = split(input);
        string command = tokens[0]; // prendo sempre il primo token che rappresenta il comando

        if (command == "exit") {
            cout << "Salvataggio dati in corso..." << endl;
            save_all_clients(clienti);
            cout << "Termino la shell..." << endl;
            break;
        } else if (command == "help") {
            // mostro i comandi disponibili
            cout << "Comandi disponibili:" << endl;
            cout << "  echo <message> - Print the message" << endl;
            cout << "  add <entity> - Avvio procedura inserimento nuovo record nella tabella <entity> (clienti/interazioni)" << endl;
            cout << "  list <entity> - Elenca tutti i record della tabella <entity> (clienti/interazioni)" << endl;
            cout << "  update <entity> - Avvio procedura di aggiornamento record nella tabella <entity> (clienti/interazioni)" << endl;
            cout << "  delete <entity> <id> - Cancella il record nella tabella <entity> (clienti/interazioni) con <id> fornito" << endl;
            cout << "  find <entity> <field> <value> - Cerca il record nella tabella <entity> (clienti/interazioni) con <field> = <value>" << endl;
            cout << "  help - Mostra i comandi disponibili" << endl;
            cout << "  exit - Termina la shell" << endl;
        } else if (command == "echo") {
            if (tokens.size() < 2) {
                cout << "Usage: echo <message>" << endl;
            } else {
                for (size_t i = 1; i < tokens.size(); ++i) {
                    cout << tokens[i] << " ";
                }
                cout << endl;
            }
        } else if (command == "add") {
            if (tokens.size() > 1) {
                string entity = tokens[1];
                if (entity == "cliente") {
                    cout << "[add cliente]inserisci nome : ";
                    string name; getline(cin, name);
                    cout << "[add cliente]inserisci cognome : ";
                    string surname; getline(cin, surname);
                    cout << "[add cliente]inserisci email : ";
                    string email; getline(cin, email);
                    cout << "[add cliente]inserisci telefono : ";
                    string phone; getline(cin, phone);
                    cout << "[add cliente]inserisci indirizzo : ";
                    string address; getline(cin, address);
                    Cliente c = Cliente(curr_cli_id, name, surname, email, phone, address);
                    clienti.push_back(c);
                    curr_cli_id++;

                    save_all_clients(clienti);
                    cout << "Cliente aggiunto con successo (ID: " << c.getId() << ")" << endl;
                } else if (entity == "interazione") {
                    cout << "[add interazione]inserisci ID cliente : ";
                    string id_cli_str; getline(cin, id_cli_str);
                    int id_cli = stoi(id_cli_str);

                    if (!cliente_exists(clienti, id_cli)) {
                        cout << "Errore: Cliente con ID " << id_cli << " non trovato!" << endl;
                    } else {
                        cout << "[add interazione]inserisci tipo (appuntamento/contratto) : ";
                        string tipo; getline(cin, tipo);
                        cout << "[add interazione]inserisci data (formato: gg/mm/aaaa) : ";
                        string data; getline(cin, data);
                        cout << "[add interazione]inserisci descrizione : ";
                        string descrizione; getline(cin, descrizione);
                        cout << "[add interazione]inserisci stato : ";
                        string stato; getline(cin, stato);

                        Interazione i = Interazione(curr_int_id, id_cli, tipo, data, descrizione, stato);
                        interazioni.push_back(i);
                        curr_int_id++;

                        save_all_interactions(interazioni);
                        cout << "Interazione aggiunta con successo (ID: " << i.getId() << ")" << endl;
                    }
                } else {
                    cout << "Entity not supported: " << entity << endl;
                    cout << "Uso: add cliente - procedura inserimento Cliente " << endl;
                    cout << "Uso: add interazione - procedura inserimento Interazione " << endl;
                }
            } else {
                cout << "Uso: add cliente - procedura inserimento Cliente " << endl;
                cout << "Uso: add interazione - procedura inserimento Interazione " << endl;
            }
        } else if (command == "list") {
            if (tokens.size() == 2) {
                string entity = tokens[1];
                if (entity == "cliente") {
                    if (clienti.empty()) cout << "Nessun cliente presente" << endl;
                    else cout << "Totale clienti: " << clienti.size() << endl;
                    bool continue_display = true;
                    for (int x = 0; x < clienti.size() && continue_display; x++) {
                        cout << clienti[x].getId() << " (id), "
                        << clienti[x].getNome() << " (Nome), "
                        << clienti[x].getCognome() << " (Cognome), "
                        << clienti[x].getEmail() << " (E-Mail), "
                        << clienti[x].getTelefono() << " (Telefono), "
                        << clienti[x].getIndirizzo() << " (Indirizzo) " << endl;

                        continue_display = handle_pagination(x, clienti.size());
                    }
                } else if (entity == "interazione") {
                    if (interazioni.empty()) cout << "Nessuna interazione presente" << endl;
                    else cout << "Totale interazioni: " << interazioni.size() << endl;
                    bool continue_display = true;
                    for (int x = 0; x < interazioni.size() && continue_display; x++) {
                        cout << interazioni[x].getId() << " (id), "
                        << interazioni[x].getIdCliente() << " (ID Cliente), "
                        << interazioni[x].getTipo() << " (Tipo), "
                        << interazioni[x].getData() << " (Data), "
                        << interazioni[x].getDescrizione() << " (Descrizione), "
                        << interazioni[x].getStato() << " (Stato) " << endl;

                        continue_display = handle_pagination(x, interazioni.size());
                    }
                } else {
                    cout << "Entity not supported: " << entity << endl;
                    cout << "Uso: list cliente - elenco tutti i clienti " << endl;
                    cout << "Uso: list interazione - elenco tutte le interazioni " << endl;
                }
            } else {
                cout << "Uso: list cliente - elenco tutti i clienti " << endl;
                cout << "Uso: list interazione - elenco tutte le interazioni " << endl;
            }
        } else if (command == "find") {
            if (tokens.size() > 3) {
                string entity = tokens[1];
                string field = tokens[2];
                string value = tokens[3];
                if (entity == "cliente" &&
                    (field == "nome" || field == "cognome")) {
                    vector<Cliente> clienti_trovati;
                    bool found = false;
                    for (int x = 0; x < clienti.size(); x++) {
                        Cliente c = clienti[x];
                        if ( field == "nome" && c.getNome() == value ||
                            field == "cognome" && c.getCognome() == value) {
                            clienti_trovati.push_back(c);
                            found = true;
                        }
                    }

                    if (!found) cout << "Nessun cliente trovato con " << field << " = " << value << endl;
                    else cout << "Totale clienti trovati: " << clienti_trovati.size() << endl;

                    bool continue_display = true;
                    for (int x = 0; x < clienti_trovati.size() && continue_display; x++) {
                        Cliente c = clienti_trovati[x];
                        cout << c.getId() << " (id), "
                        << c.getNome() << " (Nome), "
                        << c.getCognome() << " (Cognome), "
                        << c.getEmail() << " (E-Mail), "
                        << c.getTelefono() << " (Telefono), "
                        << c.getIndirizzo() << " (Indirizzo) " << endl;

                        continue_display = handle_pagination(x, clienti_trovati.size());

                    }
                } else if (entity == "interazione" && field == "id_cliente") {
                    vector<Interazione> interazioni_trovate;
                    bool found = false;
                    int id_cli = stoi(value);
                    for (int x = 0; x < interazioni.size(); x++) {
                        Interazione i = interazioni[x];
                        if (i.getIdCliente() == id_cli) {
                            interazioni_trovate.push_back(i);
                            found = true;
                        }
                    }

                    if (!found) cout << "Nessuna interazione trovata per cliente con ID = " << value << endl;
                    else cout << "Totale interazioni trovate: " << interazioni_trovate.size() << endl;

                    bool continue_display = true;
                    for (int x = 0; x < interazioni_trovate.size() && continue_display; x++) {
                        Interazione i = interazioni_trovate[x];
                        cout << i.getId() << " (id), "
                        << i.getIdCliente() << " (ID Cliente), "
                        << i.getTipo() << " (Tipo), "
                        << i.getData() << " (Data), "
                        << i.getDescrizione() << " (Descrizione), "
                        << i.getStato() << " (Stato) " << endl;

                        continue_display = handle_pagination(x, interazioni_trovate.size());
                    }
                } else if (entity == "interazione" && field == "tipo") {
                    vector<Interazione> interazioni_trovate;
                    bool found = false;
                    for (int x = 0; x < interazioni.size(); x++) {
                        Interazione i = interazioni[x];
                        if (i.getTipo() == value) {
                            interazioni_trovate.push_back(i);
                            found = true;
                        }
                    }
                    for (int x = 0; x < interazioni_trovate.size(); x++) {
                        Interazione i = interazioni_trovate[x];
                        cout << i.getId() << " (id), "
                        << i.getIdCliente() << " (ID Cliente), "
                        << i.getTipo() << " (Tipo), "
                        << i.getData() << " (Data), "
                        << i.getDescrizione() << " (Descrizione), "
                        << i.getStato() << " (Stato) " << endl;
                    }
                    if (!found) cout << "Nessuna interazione trovata con tipo = " << value << endl;
                } else {
                    if (entity != "cliente" && entity != "interazione")  cout << "Entity not supported: " << entity << endl;
                    cout << "Field not supported: " << field << endl;
                    cout << "Uso: find cliente <field> <value> - cerca il cliente per nome/cognome <nome>/<cognome> " << endl;
                    cout << "Uso: find interazione id_cliente <id> - cerca le interazioni del cliente con id <id> " << endl;
                }

            } else {
                cout << "Uso: find cliente <field> <value> - cerca il cliente per nome/cognome <nome>/<cognome> " << endl;
                cout << "Uso: find interazione id_cliente <id> - cerca le interazioni del cliente con id <id> " << endl;
            }
        } else if (command == "delete") {
            if (tokens.size() > 2) {
                string entity = tokens[1];
                string id = tokens[2];
                if (entity == "cliente") {
                    bool found = false;
                    for (int x = 0; x < clienti.size(); x++) {
                        Cliente c = clienti[x];
                        if (c.getId() == stoi(id)) {
                            clienti.erase(clienti.begin() + x);
                            found = true;
                        }
                    }
                    if (found) {
                        save_all_clients(clienti);
                        cout << "Cliente cancellato con successo" << endl;
                    } else {
                        cout << "Cliente non trovato con id " << id << endl;
                    }
                } else if (entity == "interazione") {
                    bool found = false;
                    for (int x = 0; x < interazioni.size(); x++) {
                        Interazione i = interazioni[x];
                        if (i.getId() == stoi(id)) {
                            interazioni.erase(interazioni.begin() + x);
                            found = true;
                        }
                    }
                    if (found) {
                        save_all_interactions(interazioni);
                        cout << "Interazione cancellata con successo" << endl;
                    } else {
                        cout << "Interazione non trovata con id " << id << endl;
                    }
                } else {
                    cout << "Entity not supported: " << entity << endl;
                    cout << "Uso: delete cliente <id> - cancella il cliente con id <id> " << endl;
                    cout << "Uso: delete interazione <id> - cancella l'interazione con id <id> " << endl;
                }
            } else {
                cout << "Uso: delete cliente <id> - cancella il cliente con id <id> " << endl;
                cout << "Uso: delete interazione <id> - cancella l'interazione con id <id> " << endl;
            }
        } else if (command == "update") {
            if (tokens.size() > 1) {
                string entity = tokens[1];
                if (entity == "cliente") {
                    cout << "[update cliente] inserisci id record da modificare : ";
                    string id; getline(cin, id);
                    int id_cli = stoi(id);
                    bool found = false;
                    for (int x = 0; x < clienti.size(); x++) {
                        Cliente c = clienti[x];
                        if (c.getId() == id_cli) {
                            cout << "inserire i nuovi valori oppure premere invio per mantenere il valore corrente" << endl;
                            cout << "[update cliente] inserisci nome : ";
                            string name; getline(cin, name);
                            if (name.empty()) name = c.getNome();
                            cout << "[update cliente] inserisci cognome : ";
                            string cognome; getline(cin, cognome);
                            if (cognome.empty()) cognome = c.getCognome();
                            cout << "[update cliente] inserisci email : ";
                            string email; getline(cin, email);
                            if (email.empty()) email = c.getEmail();
                            cout << "[update cliente] inserisci telefono : ";
                            string telefono; getline(cin, telefono);
                            if (telefono.empty()) telefono = c.getTelefono();
                            cout << "[update cliente] inserisci indirizzo : ";
                            string indirizzo; getline(cin, indirizzo);
                            if (indirizzo.empty()) indirizzo = c.getIndirizzo();
                            clienti[x] = Cliente(id_cli, name, cognome, email, telefono, indirizzo);
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "Cliente non trovato con id " << id_cli << endl;
                    } else {
                        save_all_clients(clienti);
                        cout << "Cliente aggiornato con successo" << endl;
                    }
                } else if (entity == "interazione") {
                    cout << "[update interazione] inserisci id record da modificare : ";
                    string id; getline(cin, id);
                    int id_int = stoi(id);
                    bool found = false;
                    for (int x = 0; x < interazioni.size(); x++) {
                        Interazione i = interazioni[x];
                        if (i.getId() == id_int) {
                            cout << "inserire i nuovi valori oppure premere invio per mantenere il valore corrente" << endl;

                            int id_cli = i.getIdCliente();
                            cout << "[update interazione] inserisci ID cliente (attuale: " << id_cli << ") : ";
                            string id_cli_str; getline(cin, id_cli_str);
                            if (!id_cli_str.empty()) {
                                id_cli = stoi(id_cli_str);
                                if (!cliente_exists(clienti, id_cli)) {
                                    cout << "Errore: Cliente con ID " << id_cli << " non trovato! Mantengo ID precedente." << endl;
                                    id_cli = i.getIdCliente();
                                }
                            }

                            cout << "[update interazione] inserisci tipo : ";
                            string tipo; getline(cin, tipo);
                            if (tipo.empty()) tipo = i.getTipo();
                            cout << "[update interazione] inserisci data : ";
                            string data; getline(cin, data);
                            if (data.empty()) data = i.getData();
                            cout << "[update interazione] inserisci descrizione : ";
                            string descrizione; getline(cin, descrizione);
                            if (descrizione.empty()) descrizione = i.getDescrizione();
                            cout << "[update interazione] inserisci stato : ";
                            string stato; getline(cin, stato);
                            if (stato.empty()) stato = i.getStato();

                            interazioni[x] = Interazione(id_int, id_cli, tipo, data, descrizione, stato);
                            found = true;
                        }
                    }
                    if (!found) {
                        cout << "Interazione non trovata con id " << id_int << endl;
                    } else {
                        save_all_interactions(interazioni);
                        cout << "Interazione aggiornata con successo" << endl;
                    }
                } else {
                    cout << "Entity not supported: " << entity << endl;
                    cout << "Uso: update cliente <id> - procedura aggiornamento Cliente " << endl;
                    cout << "Uso: update interazione <id> - procedura aggiornamento Interazione " << endl;
                }

            } else {
                cout << "Uso: update cliente <id> - procedura aggiornamento Cliente " << endl;
                cout << "Uso: update interazione <id> - procedura aggiornamento Interazione " << endl;
            }

        } else {
            cout << "Comando sconosciuto: " << command << ". Digita 'help' per i comandi disponibili." << endl;
        }
    }
    return 0;
}
