//
//  main.cpp
//  Travel Management System
//
//  Created by Arek Brodowski on 04/07/2022.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <vector>


using namespace std;

void menu();

class ManageMenu
{
protected:
    string userName;

public:

    

    ManageMenu()
    {
        system("color 0A");
        cout << "\n\n\n\n\n\n\n\n\n\t  Enter Your Name to Continue as an Admin: ";
        cin >> userName;
        system("CLS");
        menu();
    }

    ~ManageMenu(){}
};

class Customer
{
public:
    string name, lastName, adress;
    int age, mobileNumber;
    static int customerID;
    char all[999];
    
    void getData()
    {
        
        ofstream out("customer.txt", ios::app);
        {
            cout << "Enter customer ID: ";
            cin >> customerID;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter last name: ";
            cin >> lastName;
            cout << "Enter adress: ";
            cin >> adress;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter mobile number: ";
            cin >> mobileNumber;
        }
        out << "\nCustomer Id: " << customerID << "\nName: " << name << " " << lastName << "\nAdress: " << adress << "\nAge: " << age << "\nMobile number: " << mobileNumber;
        out.close();
        
        cout << "\nSAVED";
        
        
    }
    
    void showData()
    {
        ifstream in("customer.txt");
        {
            if(!in) cout << "File error" << endl;
            
        }
        while(!(in.eof()))
        {
            in.getline(all, 999);
            cout << all << endl;
        }
        in.close();
    }
    
};
int Customer::customerID;

class Cabs
{
public:
    int cab, distance, cabSelect;
    static float cabCost;
    string cabClass;
    float price;
    
    
    void cabInfo()
    {
        cout << "---------- Avaialbe cabs ----------" << endl;
        cout << "|  1. Standard cab - 2,99/km      |" << endl;
        cout << "|  2. Economy cab - 1,59/km       |" << endl;
        cout << "|  3. Business cab - 3,79/km      |" << endl;
        cout << "|  4. Premium cab - 5,99/km       |" << endl;
        cout << "-----------------------------------" << endl;
        cout << "\n\n\n\n";
        cout << "Enter your chose: ";
        cin >> cab;
        cout << "Enter estimated distance: ";
        cin >> distance;
        cout << endl;
        cabCost=calcPrice(cab, distance);
        cout << "Estimated price: " << cabCost << "\n\n";
        
        
        cout << "To order cab input 1\nTo change choose input 2\nInput: " << endl;
        
        system("clear");
        
        if(cabSelect == 1)
        {
            cout << "You ordered " << cabClass << " for " << cabCost << endl;
        }
        else if (cabSelect == 2)
        {
            cabInfo();
        }
        else
        {
            cout << "Invalid input, redirecting to previous menu" << endl;
            sleep(3000000);
            system("clear");
            cabInfo();
        }
    }
    

    
    
    float calcPrice(int cab, int distance)
    {
        switch(cab)
        {
            case 1:
                price = 2.99;
                cabClass = "standard";
                break;
            case 2:
                price = 1.59;
                cabClass = "economy";
                break;
            case 3:
                price = 3.79;
                cabClass = "businnes";
                break;
            case 4:
                price = 5.99;
                cabClass = "premium";
                break;
            default:
                cout << "invalid input";
        }
        return price * distance;
    }
};
float Cabs::cabCost;



class Booking
{
public:
    static float hotelCost;
    int hotelChoice, packageChoice,nights;
    string hotelName;
    vector <vector <pair <string, float>>> hotelPackages;
    vector <pair <string, float>> optionPrice;
    
    
    void hotel()
    {
        string hotelNo[] = {"Lazy","Active", "Sunny", "Beach Vibe"};
        optionPrice = {{"option 1.1",150.00}, {"option 1.2",300.00}};
        hotelPackages.push_back(optionPrice);
        optionPrice = {{"option 2.1",100.00}, {"option 2.2",180.50}, {"option 2.3",225.00}};
        hotelPackages.push_back(optionPrice);
        optionPrice = {{"option 3.1",170.00}, {"option 3.2",199.00}, {"option 3.3",220.00}, {"option 3.4",300.00}};
        hotelPackages.push_back(optionPrice);
        optionPrice = {{"option 4.1",110.00}, {"option 4.2",180.00}, {"option 4.3",210.00}};
        hotelPackages.push_back(optionPrice);
        
        
        system("clear");
        
        cout << "Available hotels:\n";
        for(int i = 0; i < (sizeof(hotelNo)/sizeof(hotelNo[0])); i++)
        {
            cout << (i+1) << ". Hotel: " << hotelNo[i] << endl;
        }
        cout << "Choose hotel or pres \"0\" to go back: ";
        cin >> hotelChoice;
        
        
        chosePackage:
        
        system("clear");
        
        if(hotelChoice != 0 && hotelChoice <=(sizeof(hotelNo)/sizeof(hotelNo[0])))
        {
            cout << "Welcome to " << hotelNo[hotelChoice-1] << " Hotel"<<endl;
            cout << "Available packages: \n";
            for(int i = 0; i < hotelPackages[hotelChoice-1].size(); i++)
            {
                cout << (i+1) << ". Option: " << (hotelPackages[hotelChoice-1][i]).first << " for: " << (hotelPackages[hotelChoice-1][i]).second << " per night"<< endl;
                
                
            }
            cout << "Choose package or pres \"0\" to go back: ";
            cin >> packageChoice;
            if(packageChoice==0)
            {
                hotel();
            }
            else if(packageChoice != 0 && packageChoice < hotelPackages[hotelChoice-1].size())
            {
                system("clear");
                cout << (hotelPackages[hotelChoice-1][packageChoice-1]).first << endl;
                cout << "press 0 to go back or type number of nights";
                cin >> nights;
                
                if(nights==0)
                {
                    system("clear");
                    goto chosePackage;
                }
                else if (nights>0){
                    hotelCost = nights * (hotelPackages[hotelChoice-1][packageChoice-1]).second;
                    cout << "total cost: " << hotelCost << endl;
                }
                else
                {
                    system("clear");
                    goto chosePackage;
                }
                    
            }
        }
        else if( hotelChoice == 0)
        {
            system("clear");
            hotel();
        }
        else
        {
            system("clear");
            cout << "invalid input. Redirecting...";
            sleep(3000000);
            system("clear");
            hotel();
        }
       
        
    }
        
};
float Booking::hotelCost;



class Charges :  public Booking, Customer, Cabs
{
public:
    
    void printBill()
    {
        ofstream outf("receipt.txt");
        {
            outf << "----------Receipt----------" << endl;
            outf << "Customer ID: " << Customer::customerID << endl << endl;
            outf << "Description\t\t Total"<< endl;
            outf << "Cab\t\t "<< fixed << setprecision(2) << Cabs::cabCost << endl;
            outf << "Hotel\t\t "<< fixed << setprecision(2) << Booking::hotelCost << endl;
            outf << "___________________________\n\n";
            outf << "Total\t\t "<< fixed << setprecision(2) << Booking::hotelCost + Cabs::cabCost << endl;
            
            
         }
        outf.close();
    }
    
    void showBill()
    {
        ifstream inf("receipt.txt");
        {
            if(!inf)
            {
                cout << "file openning error" << endl;
            }
            while(!(inf.eof()))
            {
                inf.getline(all, 999);
                cout << all << endl;
                
            }
        }
        inf.close();
        
    }
    
};

void menu()
{
    int mainChoice, inChoice,gotoMenu;
    
    cout << "-----------MAIN MENU-----------" << endl;
    cout << "Customer Management    ->     1" << endl;
    cout << "Cabs Management        ->     2" << endl;
    cout << "Bookings Management    ->     3" << endl;
    cout << "Charges & Bills        ->     4" << endl;
    cout << "Exit                   ->     5" << endl;
    cout << "\n\n\n";
    cout << "Enter your choice: " << endl;
    cin >> mainChoice;
    
    
    Customer a2;
    Cabs a3;
    Booking a4;
    Charges a5;

       
    if(mainChoice == 1){
        cout << "------Customers------\n" << endl;
        cout << "1. Enter New Customer"<< endl;
        cout << "2. See Old Customers"<< endl;
        cout << "\nEnter choice: ";
        cin >> inChoice;

        system("CLS");
        if(inChoice == 1){
            a2.getData();
        }
        else if(inChoice == 2){
            a2.showData();
        }
        else{
            cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
            sleep(1100);
            system("CLS");
            menu();
        }
        cout << "Press 1 to Redirect Main Menu: ";
        cin >> gotoMenu;
        system("CLS");
        if(gotoMenu == 1){
            menu();
        }
        else{
            menu();
        }
    }
    else if(mainChoice == 2){
        a3.cabInfo();
    }
    else if(mainChoice == 3){
        cout << "--> Book a Luxury Hotel using the System <--\n" << endl;
        a4.hotel();
    }
    else if(mainChoice == 4){
        cout << "-->Get your receipt<--\n" << endl;
        a5.printBill();
        cout << "Your receipt is already printed you can get it from file path\n" << endl;
        cout << "to display the your receipt in the screen, Enter 1: or Enter another key to back main menu: ";
        cin >> gotoMenu;
        if(gotoMenu == 1){
            system("CLS");
            a5.showBill();
            cout << "Press 1 to Redirect Main Menu: ";
            cin >> gotoMenu;
            system("CLS");
            if(gotoMenu == 1){
                menu();
            }
            else{
                menu();
            }
        }
        else{
            system("CLS");
            menu();
        }
    }
    else if(mainChoice == 5){
        cout << "\n\n\t--GOOD-BYE!--" << endl;
        sleep(1100);
        system("CLS");
        ManageMenu();
    }
    else{
        cout << "Invalid Input! Redirecting to Previous Menu \nPlease Wait!" << endl;
        sleep(1100);
        system("CLS");
        menu();
    }
}



int main() {
 
    ManageMenu startObj;
    
    return 0;
}
