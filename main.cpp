#include <iostream>

#include "InMemoryDB.cpp"

int main() {
    
    // Create an InMemoryDB object 
    InMemoryDB DBobj;
    cout << "Make database" << endl;

    // should return null, because A doesn’t exist in the DB yet
    DBobj.get("A");
    cout << "A: " << DBobj.get("A") << endl;


    // should throw an error because a transaction is not in progress
    DBobj.put("A", 5);


    // starts a new transaction
    DBobj.begin_transaction();
    cout << "beginning transaction" << endl;

    // set’s value of A to 5, but its not committed yet
    DBobj.put("A", 5);
    cout << "setting A to 5" << endl;

    // should return null, because updates to A are not committed yet
    DBobj.get("A");
    cout << "A: " << DBobj.get("A") << endl;

    // update A’s value to 6 within the transaction
    DBobj.put("A", 6);
    cout << "setting A to 6" << endl;

    // commits the open transaction
    DBobj.commit();
    cout << "moving changes into main table" << endl;

    // should return 6, that was the last value of A to be committed
    DBobj.get("A");
    cout << "A: " << DBobj.get("A") << endl;

    // throws an error, because there is no open transaction
    DBobj.commit();

    // throws an error because there is no ongoing transaction
    DBobj.rollback();

    // should return null because B does not exist in the database
    DBobj.get("B");
    cout << "B: " << DBobj.get("B") << endl;

    // starts a new transaction
    DBobj.begin_transaction();
    cout << "beginning transaction" << endl;

    // Set key B’s value to 10 within the transaction
    DBobj.put("B", 10);
    cout << "setting B to 10" << endl;

    // Rollback the transaction - revert any changes made to B
    DBobj.rollback();
    cout << "reverting changes" << endl;

    // Should return null because changes to B were rolled back
    DBobj.get("B");
    cout << "B: " << DBobj.get("B") << endl;

    return 0;
}