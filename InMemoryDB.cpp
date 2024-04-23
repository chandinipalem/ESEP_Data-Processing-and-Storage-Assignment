// Author: Chandini Palem 
// ESEP: Extra Credit Assignment : Data Processing and Storage Assignment
// Language C++

#include <string>
#include <unordered_map>
using namespace std;


class InMemoryDB {

    unordered_map<string, int> table;
    bool transactionStarted = false;
    unordered_map<string, int> tempTable;

public:
    InMemoryDB () {

    }

    // will return the value associated with the key or null if the key doesn’t exist.
    int get(string key) {
        if (!table.count(key))
            return NULL;
        return table[key];

    }

    // when a transaction is not in progress throw an exception
    void put(string key, int val) {
        if (!transactionStarted)
            throw invalid_argument("Transaction not started, parameters in put() invalid.");
        tempTable[key] = val;
    }

    // starts a new transaction
    void begin_transaction() {
        if (transactionStarted)
            return;
        transactionStarted = true;
    }

    // applies changes made within the transaction to the main state
    void commit() {
        if (!transactionStarted)
            throw invalid_argument("Transaction not started, cannot commit any changes.");

        for (auto i : tempTable) {
            table[i.first] = i.second;
        }

        tempTable.clear();
        rollback();

    }

    // aborts all the changes made within the transaction and everything should go back 
    // to the way it was before.
    void rollback() {
        if (!transactionStarted)
            throw invalid_argument("Transaction not started, cannot rollback any changes.");

        // reset transaction
        transactionStarted = false;
        tempTable.clear();
    }

};