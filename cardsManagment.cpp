#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>


#define RESET_COLOR "\033[0m"
#define GREEN_TEXT "\033[32m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BLUE    "\033[34m"  
#define BRIGHT_MAGENTA_TEXT "\033[95;1m"
#define CYAN    "\033[36m"
#define RED     "\033[31m" 
#define YELLOW  "\033[33m"  
#define BOLDWHITE   "\033[1m\033[37m"  
using namespace std;

class Card
{
    protected:
    string cardName;
    int cardNumber;
    int CVV;
    int cardBalance;
    int cardPassword;

    public:
    Card() {}
    Card(string cardName, int cardNumber, int CVV, int cardBalance, int cardPassword) : cardName(cardName), cardNumber(cardNumber), CVV(CVV), cardBalance(cardBalance),cardPassword(cardPassword) {}
    
    string GetCardName() {return cardName;}
    int GetCardNumber() {return cardNumber;}
    int GetCardCVV() {return CVV; }
    int GetCardBalance() {return cardBalance;}
    int GetCardPassword() {return cardPassword;}

    void SetCardPassword(int cardpassword) {cardpassword = cardPassword;}

    void Print() 
    {
        cout << "Card name: "<< cardName << " Card Nummber: " << cardNumber << " CVV code " << CVV << " Balnce: " << cardBalance << " Password: " << cardPassword << endl;
        cout << endl;
    }

    void CreateCards(vector<Card*>& cards) 
    {
        cout << "How many cards do you want to create?" << endl;
        int amount;
        cin >> amount;
        for(int i = 0; i < amount; i++)
        {
            Card* card = new Card();
            cout << "Enter card name: (debit or credit)" << endl;
            cin >> card->cardName;
            cout << "Enter card number: " << endl;
            cin >> card->cardNumber;
            cout << "Enter card CVV: " << endl;
            cin >> card->CVV;
            cout << "Enter card balance: " << endl;
            cin >> card->cardBalance;
            cout << "Enter card password: " << endl;
            cin >> card->cardPassword;
            cards.push_back(card);
        }
    }

    void WriteCardsDataToAFile(ofstream& file)
    {
        file << cardName << endl;
        file << cardNumber << endl;
        file << CVV << endl;
        file << cardBalance << endl;
        file << cardPassword << endl;
    }

};

class DebitCard : public Card
{
    public:
    int cashBack;

    DebitCard() {}
    DebitCard(string cardName, int cardNumber, int CVV, int cardBalance, int cardPassword, int cashBack) : Card(cardName, cardNumber, CVV, cardBalance, cardPassword), cashBack(cashBack) {}
};

class CreditCard : public Card
{
    public:
    int withdrawlFee;

   
    CreditCard() {}
    CreditCard(string cardName, int cardNumber, int CVV, int cardBalance, int cardPassword, int withdrawlFee) : Card(cardName, cardNumber, CVV, cardBalance, cardPassword), withdrawlFee(withdrawlFee) {}
};

class Person
{
    protected:
    string personName;
    string password;

    public:
    Person() {}
    Person(string personName, string password) : personName(personName), password(password) {}

    virtual void SignUp() 
    {
        cout << "Registration: " << endl;
        cout << endl;
        cout << "Select a name: " << endl;
        cout << BLUE;
        cin >> personName;
        cout << RESET_COLOR;
        cout << "Select a password: " << endl;
        cout << BLUE;
        cin >> password;
        cout << RESET_COLOR << endl;
    }

    virtual void WritePersonsDataToAFile(ofstream& file)
    {
        file << personName << endl;
        file << password << endl;
    }
   
    virtual bool SignIn() {}

    virtual void Menu() {}
};

class User : public Person
{
    protected:
    int phoneNumber;
    vector<Card*> cards;

    public:
    User() {}
    User(string personName, string password, int phoneNumber) : Person(personName, password), phoneNumber(phoneNumber) {}

    vector<Card*>& GetCards() {return cards;}

    void SignUp() 
    {
        Person::SignUp();
        cout << "Select a phone number: " << endl;
        cout << BLUE;
        cin >> phoneNumber;
        cout << RESET_COLOR;

    }

    void WritePersonsDataToAFile(ofstream& file) override
    {
        Person::WritePersonsDataToAFile(file);
        file << phoneNumber << endl;
    } 

    bool SignIn(string filename) 
    {
        string name;
        string password;
        int number;

        cout << "Enter your name: " << endl;
        cout << CYAN;
        cin >> name;
        cout << RESET_COLOR;
        cout << "Enter your password: " << endl;
        cout << CYAN;
        cin >> password;
        cout << RESET_COLOR;
        cout << "Enter your number: " << endl;
        cout << CYAN;
        cin >> number;
        cout << RESET_COLOR;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return false;
        }

        string storedName;
        string storedPassword;
        int storedNumber;

        while (file >> storedName >> storedPassword >> storedNumber) {
            if (name == storedName && password == storedPassword && number == storedNumber) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }


    void AddCards()
    {
        Card* card = new Card();
        card->CreateCards(cards);
        cards.push_back(card);
    }

    void SaveCardsDataToAFile() 
    {
        ofstream file("personsCards.txt");
        
        if (file.is_open()) 
        {
            for (auto card : cards) 
            {
                card->WriteCardsDataToAFile(file);
                file << endl;
            }
            file.close();
        } else 
        {
            cout << RED << "Can't open the file!" << RESET_COLOR << endl;
        }
    }

    void ReadCardsDataFromFile() 
    {
        ifstream file("personsCards.txt");

        if (file.is_open()) 
        {
            string cardName;
            int cardNumber, CVV, endingData, cardBalance, cardPassword;

            while (file >> cardName >> cardNumber >> CVV  >> cardBalance >> cardPassword) 
            {
                Card* card = new Card(cardName, cardNumber, CVV, cardBalance, cardPassword);

                cards.push_back(card);
            }

            file.close();

        } else {
            cout << RED << "Can't open the file!" << RESET_COLOR << endl;
        }
    }

    void ViewAllCards() 
    {
        if (cards.empty()) 
        {
            cout << RED << "No cards available." << RESET_COLOR << endl;
        } else {
            cout << YELLOW << "List of cards:" << RESET_COLOR << endl;
            for (const auto& card : cards)
            {
                card->Print(); 
            }
        }
    }

    void ViewBalanceOnTheCard()
    {
        cout << "Enter card number: " << endl;
        int cardNumber;
        cin >> cardNumber;
        for(auto card: cards)
        {
            if(cardNumber == card->GetCardNumber())
            {
                cout << YELLOW << "Card balance: " << RESET_COLOR << card->GetCardBalance() << endl;
            }
        }
    } 

    int ChangePassword()
    {
        cout << "Enter card number: " << endl;
        int cardNumber;
        cin >> cardNumber;

        int password;
        cout << "Enter old password: " << endl;
        cin >> password;

        ofstream fileout("personsCards.txt"); 

        if (!fileout)
        {
            cout << "Error opening file!" << endl;
            return 1; 
        }

        bool passwordChanged = false; 

        for (auto card : cards)
        {
            int newPassword;
            if (cardNumber == card->GetCardNumber() && password == card->GetCardPassword())
            {
                cout << "Enter your new password: " << endl;
                cin >> newPassword;
                card->SetCardPassword(newPassword);
                passwordChanged = true; 

                cout << GREEN_TEXT << "Successfully changed." << RESET_COLOR << endl;
            }
        
            fileout << card->GetCardName() << endl;
            fileout << card->GetCardNumber() << endl;
            fileout << card->GetCardCVV() << endl;
            fileout << card->GetCardBalance() << endl;
            fileout << newPassword << endl;
        }

        if (!passwordChanged)
        {
            cout << RED << "Incorrect data!" << RESET_COLOR << endl;
            return 1; 
        }

    }

    int WithdrawFunds()
    {
        CreditCard credit;
        string name;
        cout << "Enter a card name: " << endl;
        cin >> name;

        int cardnumber;
        cout << "Enter number of card: " << endl;
        cin >> cardnumber;

        int password;
        cout << "Enter password: " << endl;
        cin >> password;

        int balance;
        cout << "Enter sum which you want to get: " << endl;
        cin >> balance;

        ofstream fileout("personsCards.txt"); 

        if (!fileout)
        {
            cout << "Error opening file!" << endl;
            return 1; 
        }

        for(auto card: cards)
        {
            int sum;
            int money;
            if(name == card->GetCardName() && cardnumber == card->GetCardNumber() && password == card->GetCardPassword())
            {
                if(name == "credit")
                {
                        if(balance <= 1000)
                        {
                            credit.withdrawlFee = 10;
                            sum = balance - credit.withdrawlFee;
                            cout << YELLOW << "Your money -- " << RESET_COLOR << sum << endl;
                            
                            money = card->GetCardBalance() - sum;
                        }else if (balance >= 1000)
                        {
                            credit.withdrawlFee = 20;
                            sum = balance - credit.withdrawlFee; 
                            money = card->GetCardBalance() - sum;
                            cout << YELLOW << "Your money -- " << RESET_COLOR << sum << endl;
                        }
                    
                } else if(name == "debit")
                {
                    cout << YELLOW << "Your money: " << RESET_COLOR << balance << endl;
                    money = card->GetCardBalance() - balance;
                }
            }

            fileout << card->GetCardName() << endl;
            fileout << card->GetCardNumber() << endl;
            fileout << card->GetCardCVV() << endl;
            fileout << money << endl;
            fileout << card->GetCardPassword() << endl;
        }

       
    }

    int DepositMoneyToTheAccount()
    {
        DebitCard debit;
        string name;
        cout << "Enter a card name: " << endl;
        cin >> name;


        int cardnumber;
        cout << "Enter number of card: " << endl;
        cin >> cardnumber;

        int password;
        cout << "Enter password: " << endl;
        cin >> password;

        int amount;
        cout << "Enter sum which you want to put on the card: " << endl;
        cin >> amount;

        ofstream fileout("personsCards.txt"); 

        if (!fileout)
        {
            cout << "Error opening file!" << endl;
            return 1; 
        }

        for(auto card: cards)
        {
            int sum;
            int balance;

            if(name == card->GetCardName() && cardnumber == card->GetCardNumber() && password == card->GetCardPassword())
            {
                if(name == "debit")
                {
                    debit.cashBack = 1;
                    sum = amount + debit.cashBack;
                    cout << YELLOW << "You put this amount on the card: " << RESET_COLOR << sum << endl;
                    balance = card->GetCardBalance() + sum;
                    
                } else if(name == "credit")
                {
                    sum = card->GetCardBalance() + amount;
                    cout << YELLOW << "You put this amount on the card: " << RESET_COLOR << sum << endl;
                    balance = card->GetCardBalance() + sum;
                }
            }

            fileout << card->GetCardName() << endl;
            fileout << card->GetCardNumber() << endl;
            fileout << card->GetCardCVV() << endl;
            fileout << balance << endl;
            fileout << card->GetCardPassword() << endl; 
            
        }
    }


    void Menu() 
    {
        int option;

        cout << BOLDWHITE << "-------------------Menu for User-------------------" << RESET_COLOR << endl;
        cout << BOLDWHITE << "1. Add cards\n"
                          << "2. View all the cards\n"
                          << "3. View balance on the card\n" 
                          << "4. Change the card's password\n" 
                          << "5. Withdraw funds\n" 
                          << "6. Deposit money to the account\n" 
                          << "7. Exit " << RESET_COLOR << endl;
        cin >> option;
        ReadCardsDataFromFile();
        switch (option)
        {
            case 1:
                AddCards();
                SaveCardsDataToAFile();
            break;
                
            case 2: 
                ViewAllCards();
            break;
                
            case 3: 
                ViewBalanceOnTheCard();
            break; 

            case 4: 
                ChangePassword();
            break;

            case 5: 
                WithdrawFunds();
            break;

            case 6: 
                DepositMoneyToTheAccount();
            break;

            case 7: 
            break;
        
        } 


    }


};

class Admin : public Person
{
    protected:
    int ID;

    public:
    Admin() {}
    Admin(string personName, string password, int ID) : Person(personName, password), ID(ID) {}

    void SignUp() 
    {
        Person::SignUp();
        cout << "Select an ID: " << endl;
        cout << BLUE;
        cin >> ID;
        cout << RESET_COLOR;
    }

    void WritePersonsDataToAFile(ofstream& file) override
    {
        Person::WritePersonsDataToAFile(file);
        file << ID << endl;
    }

    bool SignIn(string filename) 
    {
        string name;
        string password;
        int ID;

        cout << "Enter your name: " << endl;
        cout << CYAN;
        cin >> name;
        cout << RESET_COLOR;
        cout << "Enter your password: " << endl;
        cout << CYAN;
        cin >> password;
        cout << RESET_COLOR;
        cout << "Enter your ID: " << endl;
        cout << CYAN;
        cin >> ID;
        cout << RESET_COLOR;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return false;
        }

        string storedName;
        string storedPassword;
        int storedID;

        while (file >> storedName >> storedPassword >> storedID) {
            if (name == storedName && password == storedPassword && ID == storedID) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }


    int BlockTheUsersCard(vector<Card*>& cards)
    {
        cout << "Enter card number: " << endl;
        int cardNumber;
        cin >> cardNumber;

        ofstream fileout("personsCards.txt"); 

        if (!fileout)
        {
            cout << "Error opening file!" << endl;
            return 1; 
        }
       
        string num = "blocked";
        for(auto card: cards)
        {
            
                if(cardNumber == card->GetCardNumber())
                {
                    num = cardNumber;
                    cout << RED << "Card is blocked!" << RESET_COLOR << endl;
                } 

                fileout << card->GetCardName() << endl;
                fileout << num << endl;
                fileout << card->GetCardCVV() << endl;
                fileout << card->GetCardBalance() << endl;
                fileout << card->GetCardPassword() << endl; 
            
        }     
    }

    void Menu() 
    {
        User user;
        int opportunity;

        cout << BOLDWHITE << "-------------------Menu for Admin-------------------" << RESET_COLOR << endl;
        cout << BOLDWHITE << "1. View user data\n"
                          << "2. Block the user card\n"
                          << "3. Exit" << RESET_COLOR << endl;

        cin >> opportunity;

        switch(opportunity)
        {
            case 1:
                user.ReadCardsDataFromFile();
                user.ViewAllCards();
            
            break;
            case 2:
                user.ReadCardsDataFromFile();
                BlockTheUsersCard(user.GetCards());
            break;

            case 3:
            break;    
        } 
       
    }
};

class Application
{
    protected:
    vector<Person*> persons;

    public:

    Application() {}
    Application(vector<Person*>& newPerson) : persons(newPerson) {}

    void RegisterAsAdmin()
    {
        Admin* admin = new Admin();
        admin->SignUp();
        persons.push_back(admin);
    }

    void RegisterAsUser()
    {
        User* user = new User();
        user->SignUp();
        persons.push_back(user);
    }

    void SaveToAFile()
    {
        ofstream file("personsData.txt", ios::app);
        
        if(file.is_open())
        {
            for(auto person: persons)
            {
                person->WritePersonsDataToAFile(file);
                file << endl;
            }
            file.close();
        }else{
            cout << RED << "Can't open the file!" << RESET_COLOR << endl;
        }
    }

    void Menu()
    {
        Admin admin;
        User user;

        int choice;
        do
        {
            cout << BRIGHT_MAGENTA_TEXT << "-------------------✨CARD MANAGMENT!✨-------------------" << RESET_COLOR << endl;
            cout << endl;
            cout << BOLDWHITE <<" -------------------Menu-------------------" << RESET_COLOR << endl;
            cout << BOLDWHITE << "1. Register as an Admin\n"
                              << "2. Register as a User\n"
                              << "3. Login as an Admin\n"
                              << "4. Login as a User\n" 
                              << "5. Exit" << RESET_COLOR << endl;
            cout << "Enter your choice: " ;
            cin >> choice;

            switch(choice)
            {
                case 1:
                
                    RegisterAsAdmin();
                    SaveToAFile();
                    admin.Menu();
                break;
                
                
                case 2:

                    RegisterAsUser();
                    SaveToAFile();
                    user.Menu();
                break;
                

                case 3:
                
                    if (admin.SignIn("personsData.txt")) 
                    {
                        cout << GREEN_TEXT << "Successfully logged in!" << RESET_COLOR << endl;
                        admin.Menu();
                    } else 
                    {
                        cout << RED << "Invalid login!" << RESET_COLOR << endl;
                    }
                break;
                

                case 4:
                
                    if (user.SignIn("personsData.txt")) 
                    {
                        cout << GREEN_TEXT << "Successfully logged in!" << RESET_COLOR << endl;
                        user.Menu();
                    } else 
                    {
                        cout << RED << "Invalid login!" << RESET_COLOR << endl;
                    }

                break;
            
            }
        }while(choice != 5);
    }

    

};

int main()
{
    Application app;
    app.Menu();

  
    return 0;
}