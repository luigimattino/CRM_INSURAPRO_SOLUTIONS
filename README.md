# CRM InsuraPro Solutions

Sistema di Customer Relationship Management per imprese di assicurazioni sviluppato in C++.

## Descrizione del Progetto

InsuraPro Solutions è un'applicazione console interattiva che permette di gestire le informazioni sui clienti e le loro interazioni (appuntamenti e contratti) in modo efficiente.

## Struttura del Progetto

Il progetto è composto dai seguenti file:

- **Cliente.h / Cliente.cpp**: Definizione e implementazione della classe Cliente
- **Interazione.h / Interazione.cpp**: Definizione e implementazione della classe Interazione
- **csv_utils.h**: Funzioni di utilità per la gestione dei file CSV
- **main.cpp**: File principale con l'interfaccia utente a linea di comando
- **CMakeLists.txt**: File di configurazione per CMake

## Compilazione

Per compilare il progetto:

```bash
mkdir build
cd build
cmake ..
make
```

## Esecuzione

Per eseguire il programma:

```bash
./CRM_INSURAPRO_SOLUTIONS
```

## Funzionalità Implementate

### Gestione Clienti

1. **Aggiungere un Cliente**: `add cliente`
    - Inserisce un nuovo cliente nel sistema
    - Richiede: nome, cognome, email, telefono, indirizzo

2. **Visualizzare tutti i Clienti**: `list cliente`
    - Mostra l'elenco completo di tutti i clienti

3. **Cercare un Cliente**: `find cliente <campo> <valore>`
    - Cerca clienti per nome o cognome
    - Esempio: `find cliente nome Mario`

4. **Modificare un Cliente**: `update cliente`
    - Modifica i dati di un cliente esistente
    - Richiede l'ID del cliente da modificare

5. **Eliminare un Cliente**: `delete cliente <id>`
    - Rimuove un cliente dal sistema
    - Esempio: `delete cliente 1`

### Gestione Interazioni

Le interazioni rappresentano appuntamenti con la forza vendita o contratti stipulati.

1. **Aggiungere un'Interazione**: `add interazione`
    - Inserisce una nuova interazione nel sistema
    - Richiede: ID cliente, tipo (appuntamento/contratto), data, descrizione, stato

2. **Visualizzare tutte le Interazioni**: `list interazione`
    - Mostra l'elenco completo di tutte le interazioni

3. **Cercare Interazioni**:
    - Per cliente: `find interazione id_cliente <id>`
    - Per tipo: `find interazione tipo <tipo>`
    - Esempio: `find interazione id_cliente 1`
    - Esempio: `find interazione tipo appuntamento`

4. **Modificare un'Interazione**: `update interazione`
    - Modifica i dati di un'interazione esistente
    - Richiede l'ID dell'interazione da modificare

5. **Eliminare un'Interazione**: `delete interazione <id>`
    - Rimuove un'interazione dal sistema
    - Esempio: `delete interazione 1`

### Altri Comandi

- **help**: Mostra l'elenco dei comandi disponibili
- **echo <messaggio>**: Stampa il messaggio inserito
- **exit**: Salva i dati e termina il programma

## Persistenza dei Dati

I dati vengono salvati automaticamente in file CSV:

- **clienti.csv**: Contiene tutti i dati dei clienti
- **interazioni.csv**: Contiene tutte le interazioni

I file vengono caricati all'avvio del programma e salvati quando si esegue il comando `exit`.

## Formato dei Dati

### Cliente
- ID (intero)
- Nome (stringa)
- Cognome (stringa)
- Email (stringa)
- Telefono (stringa)
- Indirizzo (stringa)

### Interazione
- ID (intero)
- ID Cliente (intero - riferimento al cliente)
- Tipo (stringa: "appuntamento" o "contratto")
- Data (stringa, formato: gg/mm/aaaa)
- Descrizione (stringa)
- Stato (stringa):
    - Per appuntamenti: "programmato", "completato", "cancellato"
    - Per contratti: "attivo", "scaduto", "annullato"

## Esempio di Utilizzo

```
InsuraPro Solutions - Command Shell (digita 'help' per conoscere i comandi, 'exit' per terminare)
enter > add cliente
[add cliente]inserisci nome : Mario
[add cliente]inserisci cognome : Rossi
[add cliente]inserisci email : mario.rossi@email.com
[add cliente]inserisci telefono : 3331234567
[add cliente]inserisci indirizzo : Via Roma 1, Milano
Cliente aggiunto con successo (ID: 1)

enter > add interazione
[add interazione]inserisci ID cliente : 1
[add interazione]inserisci tipo (appuntamento/contratto) : appuntamento
[add interazione]inserisci data (formato: gg/mm/aaaa) : 15/12/2025
[add interazione]inserisci descrizione : Primo incontro per valutazione polizza auto
[add interazione]inserisci stato : programmato
Interazione aggiunta con successo (ID: 1)

enter > list cliente
1 (id), Mario (Nome), Rossi (Cognome), mario.rossi@email.com (E-Mail), 3331234567 (Telefono), Via Roma 1, Milano (Indirizzo)

enter > find interazione id_cliente 1
1 (id), 1 (ID Cliente), appuntamento (Tipo), 15/12/2025 (Data), Primo incontro per valutazione polizza auto (Descrizione), programmato (Stato)

enter > exit
Salvataggio dati in corso...
Termino la shell...
```

## Note Tecniche

- Il progetto utilizza C++20
- La gestione dei file è implementata tramite funzioni di utilità in `csv_utils.h`
- Le classi Cliente e Interazione utilizzano friend functions per la conversione da/verso formato CSV
- Gli ID vengono assegnati automaticamente in modo incrementale
- Il programma verifica che il cliente esista prima di creare un'interazione