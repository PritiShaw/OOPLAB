
#include<iostream>
#include<ctime>

using namespace std;

//Class to create date type

class Date {
    int day;
    int month;
    int year;

public:
    //Constructor

    Date() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        year = 1900 + ltm->tm_year;
        month = 1 + ltm->tm_mon;
        day = ltm->tm_mday;
    }

    friend ostream & operator<<(ostream& out, const Date& c);
};

//To display date

ostream & operator<<(ostream &ost, const Date &c) {
    ost << c.day << "-" << c.month << "-" << c.year << endl;
}

class Transaction {
    int ac_no;
    int type; //1- withdrawal 0-deposit
    Date d;
    double amount;

public:

    Transaction(int ano = 0, int t = -1, double a = 0) {
        ac_no = ano;
        type = t;
        Date dt;
        d = dt;
        amount = a;
    }

    //Function to display a transaction

    void displayTrans() {
        cout << "\n=====================================" << endl;
        cout << "TRANSACTION DETAILS" << endl;
        string ty = (type == 0) ? "Deposit" : "Withdrawal";
        cout << "Account number: " << ac_no << endl <<
                "Date: " << d << "Type: " << ty << endl <<
                "Amount: " << amount << endl;
        cout << "======================================\n" << endl;
    }
};

class Account //To store account details an abstract class
{
protected:
    int acno;
    string name;
    double balance;
    Transaction t[100];
    int noOfTrans;

public:
    //Parametrized constructor

    Account(int ano, string na, double bal) {
        acno = ano;
        name = na;
        balance = bal;
        noOfTrans = 0;
    }
    //Set balance

    void setBal(double b) {
        balance = b;
    }
    //Get balance

    double getBal() {
        return balance;
    }

    //Get account number

    int getAcno() {
        return acno;
    }

    //Function to display account details

    void display() {
        cout << "==================================================\n" << endl;
        cout << "YOUR ACCOUNT DETAILS ARE:" << endl <<
                "Account number: " << acno << endl <<
                "Name: " << name << endl <<
                "Balance: Rs." << balance <<
                " (if negative then consider overdraft)" << endl;
        cout << "===================================================\n" << endl;
    }

    //Display all transactions for an account

    void displayTransactions() {
        int i;
        for (i = 0; i < noOfTrans; i++)
            t[i].displayTrans();
    }

    //Function to desposit
    virtual void deposit(double d) = 0;
    //Function to withdraw
    virtual void withdraw(double d) = 0;

};







//Class for savings account

class Savings : public Account {
public:
    //Constructor

    Savings(int ano = 0, string n = "", double bal = 0.0) : Account(ano, n, bal) {
    }
    //Overriding deposit

    void deposit(double d) {
        Transaction temp(acno, 0, d);
        t[noOfTrans++] = temp;
        balance += d;
        cout << "Deposit successfull" << endl;
    }
    //Overriding withdraw

    void withdraw(double d) {
        if (balance <= 500 || (balance - d) < 500)
            cout << "Cannot withdraw...minimum balance must be maintained\n";
        else {
            
            
            //Storing all transactions
            Transaction temp(acno, 1, d);
            t[noOfTrans++] = temp;

            //Update balance
            balance -= d;
            cout << "Withdraw successfull" << endl;
        }
    }


};

//Class for current account

class Current : public Account {
public:
    //Constructor

    Current(int ano = 0, string n = "", double bal = 0.0) : Account(ano, n, bal) {
    }
    //Overriding deposit

    void deposit(double d) {
        Transaction temp(acno, 0, d);
        t[noOfTrans++] = temp;

        //Update balance
        balance += d;
        cout << "Deposit successfull" << endl;
    }
    //Overriding withdraw

    void withdraw(double d) {
        if (balance <= -20000 || (balance - d)<-20000)
            cout << "Cannot withdraw..overdraft limit reached" << endl;
        else {
            //Storing all transactions
            Transaction temp(acno, 1, d);
            t[noOfTrans++] = temp;

            //Update balance
            balance -= d;
            cout << "Withdraw successfull" << endl;
        }
    }

};




//Class for storing all the Savings account

class Savings_list {
    Savings list[100];
    int count;

private:
    //Function to check whether name is valid

    int isName(string n) {
        int flag = 1, i;
        for (i = 0; i < n.length(); i++)
            if (n[i] != ' ')
                if (n[i] < 65 || (n[i] > 90 && n[i] < 97) || n[i] > 122) {
                    flag = 0;
                    break;
                }
        return flag;
    }

public:

    Savings_list() {
        count = 0;
    }

    //Function to get total number of current account

    int getCount() {
        return count;
    }
    //Function to add a savings account

    void addSavings() {
        double amount;
        string name;

        //Accept name
        do {
            cout << "Enter name of account holder " << endl;
            cin>>name;
            if (!isName(name))
                cout << "Name not valid" << endl;
        } while (!isName(name));

        //Accept starting balance
        do {
            cout << "Enter amount to deposit" << endl;
            cin>>amount;
            if (amount < 500)
                cout << "Invalid amount...at least Rs.500 must be deposited\n";

        } while (amount < 500);

        Savings s(10000 + count, name, amount);

        cout << "Your account details are " << endl;
        s.display();
        list[count++] = s;
        cout << "Account successfully added" << endl;
    }

    //Function to check whether an account number is in list

    int isPresent(int ano) {
        int i, flag = 0;
        for (i = 0; i < count; i++) {
            if (list[i].getAcno() == ano) {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            return i;
        else
            return -1;
    }

    //Get details of an account

    void dispDetails(int ano) {
        list[isPresent(ano)].display();
    }

    //For transaction

    int transactionWithAcno(int ano) {
        int type;
        double amount;
        do {
            cout << "Enter type of transaction" << endl << "0. Deposit"
                    << endl << "1. Withdrawal" << endl;
            cin>>type;
            if (type != 0 && type != 1)
                cout << "Invalid choice" << endl;
        } while (type != 0 && type != 1);

        do {
            cout << "Enter amount" << endl;
            cin>>amount;
            if (amount <= 0)
                cout << "Invalid amount" << endl;
        
        } while (amount <= 0);
        if (type == 0)
            list[isPresent(ano)].deposit(amount);
        else
            list[isPresent(ano)].withdraw(amount);
        return 1;
    }

    //Function to display all transactions for a particular account

    void displayAllTrans(int acno) {
        list[isPresent(acno)].displayTransactions();
    }

};



//Class for current account

class Current_list {
    Current list[100];
    int count;

private:
    //Function to check whether name is valid

    int isName(string n) {
        int flag = 1, i;
        for (i = 0; i < n.length(); i++)
            if (n[i] != ' ')
                if (n[i] < 65 || (n[i] > 90 && n[i] < 97) || n[i] > 122) {
                    flag = 0;
                    break;
                }
        return flag;
    }

public:

    Current_list() {
        count = 0;
    }

    //Function to get total number of current account

    int getCount() {
        return count;
    }

    
    
    //Function to add a savings account

    void addCurrent() {
        double amount;
        string name;

        //Accept name
        do {
            cout << "Enter name of account holder " << endl;
            cin>>name;
            if (!isName(name))
                cout << "Name not valid" << endl;
        } while (!isName(name));

        //Accept starting balance
        do {
            cout << "Enter amount to deposit" << endl;
            cin>>amount;
            if (amount <= 0)
                cout << "Invalid amount...at least Rs.500 must be deposited\n";

        } while (amount <= 0);

        Current s(20000 + count, name, amount);

        cout << "Your account details are " << endl;
        s.display();
        list[count++] = s;
        cout << "Account successfully added" << endl;
    }

    //Function to check whether an account number is in list

    int isPresent(int ano) {
        int i, flag = 0;
        for (i = 0; i < count; i++) {
            if (list[i].getAcno() == ano) {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            return i;
        else
            return -1;
    }

    //Get details of an account

    void dispDetails(int ano) {
        list[isPresent(ano)].display();
    }

    //For transaction

    int transactionWithAcno(int ano) {
        int type;
        double amount;
        do {
            cout << "Enter type of transaction" << endl <<
                    "0. Deposit" << endl << "1. Withdrawal" << endl;
            cin>>type;
            if (type != 0 && type != 1)
                cout << "Invalid choice" << endl;
        } while (type != 0 && type != 1);

        do {
            cout << "Enter amount" << endl;
            cin>>amount;
            if (amount <= 0)
                cout << "Invalid amount" << endl;
        } while (amount <= 0);
        if (type == 0)
            list[isPresent(ano)].deposit(amount);
        else
            list[isPresent(ano)].withdraw(amount);
        return 1;
    }

    //Function to display all transactions for a particular account

    void displayAllTrans(int acno) {
        list[isPresent(acno)].displayTransactions();
    }

};

int main() {
    int ch, acno;
    Savings_list listS;
    Current_list listC;

    do {
        cout << "1. Add new savings account" << endl <<
                "2. Add new current account" << endl <<
                "3. Transact with existing savings account" << endl <<
                "4. Transact with existing current account" << endl <<
                "5. Display details of existing savings account" << endl <<
                "6. Display details of existing current account" << endl <<
                "7. Display transaction details of existing savings account" <<
                endl << "8. Display transaction details of existing "
                "current account" << endl << "9. Exit" << endl
                << "Enter choice" << endl;
        cin>>ch;

        switch (ch) {
            case 1:

                listS.addSavings();
                break;

            case 2:

                listC.addCurrent();
                break;

            case 3:

                if (listS.getCount() == 0) {
                    cout << "Add some new savings account first" << endl;
                    break;
                }
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listS.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listS.isPresent(acno) == -1);
                listS.transactionWithAcno(acno);
                break;

            case 4:

                if (listC.getCount() == 0) {
                    cout << "Add some new current account first" << endl;
                    break;
                }
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listC.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listC.isPresent(acno) == -1);
                listC.transactionWithAcno(acno);
                break;

            case 5:

                
                if (listS.getCount() == 0) {
                    cout << "Add some new savings account first" << endl;
                    break;
                }
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listS.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listS.isPresent(acno) == -1);
                listS.dispDetails(acno);
                break;

            case 6:

                if (listC.getCount() == 0) {
                    cout << "Add some new current account first" << endl;
                    break;
                }
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listC.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listC.isPresent(acno) == -1);
                listC.dispDetails(acno);
                break;

            case 7:

                if (listS.getCount() == 0) {
                    cout << "Add some new savings account first" << endl;
                    break;
                }
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listS.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listS.isPresent(acno) == -1);
                listS.displayAllTrans(acno);
                break;

            case 8:

                if (listC.getCount() == 0) {
                    cout << "Add some new current account first" << endl;
                    break;
                }
                
                                
                do {
                    cout << "Enter account number" << endl;
                    cin>>acno;
                    if (listC.isPresent(acno) == -1)
                        cout << "Invalid account number..Re-enter" << endl;
                } while (listC.isPresent(acno) == -1);
                
                
                listC.displayAllTrans(acno);
                break;


            case 9:
                cout << "Quitting" << endl;
                exit(0);

            default:
                cout << "Invalid choice" << endl;

        }
    } while (ch != 9);
    return 0;
}