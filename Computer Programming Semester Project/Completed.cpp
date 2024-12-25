#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<sstream>
#include<iomanip>
using namespace std;

class Shopping {
private:
    int PrCode;
    float PrPrice;
    float PrDiscount;
    string PrName;
    const string adminUsername = "hayat_69";
    const string adminPassword = "Hayat+890";

    bool authenticate(const string& username, const string& password) {
        return username == adminUsername && password == adminPassword;
    }
public:
    void Menu();
    void Administration();
    void Buyer();
    void add();
    void Edit();
    void Remove();
    void List();
    void Receipt();
};
void Shopping::Menu() {
    int choice;
    string username, password;
    do {
        cout << "\n\n\t\t\t ---|  SuperMarket Main Menu  |---\n\n";
        Ag:
        cout<<"\n";
        cout << "\t\t\t1. Administration\n";
        cout << "\t\t\t2. Buyer\n";
        cout << "\t\t\t3. Exit\n\n";
        cout << "\t\t\tEnter Your Choice >>  ";
        cin >> choice;
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout<<"\n\t\t\t Error Invalid Input , Please Try again \n\n";
        goto Ag;
    } 
        switch (choice) {
            case 1:
                cout<<"\n\t\t- Prove Your Identity (Login) ......\n\n";
                cout << "\t\t\t Username >> ";
                cin >> username;
                cout << "\t\t\t Password >> ";
                cin >> password;

                if (authenticate(username, password)) {
                    
                    cout << "\n\t\t Login Successful!";
                    Administration();
                } else {
                    cout << "\n\t\t\tError ! Invalid Username or Password, Try Again\n";
                }
                break;

            case 2:
                Buyer();
                break;

            case 3:
                cout << "\n\t\t **|  Exiting Program... Goodbye!  |**";
                break;
                
            default:
                char ch;
                cout << "\n\t\t\t Invalid Option. Please Try Again.\n\n";
                cout<<"\t\t\t Do You Want To Try ? (Y/N) : ";
                cin>>ch;
                if((ch=='Y' )||(ch=='y')){
                goto Ag;
                }else{
                    cout<<"\t\t\t Exiting .... Good Bye ";
                    exit(0);
                }
        }
    } while (choice < 3 && choice >0 );
}
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void Shopping::Administration() {
    int choice;
    do {
        cout << "\n\n\t\t\t---|  Administration Menu  |---\n\n";
        m:
        cout << "\n\t\t\t- 1. Add Product\n";
        cout << "\t\t\t- 2. Modify Product\n";
        cout << "\t\t\t- 3. Remove Product\n";
        cout << "\t\t\t- 4. Back to Main Menu\n";
        
        cout << "\t\t\t Enter Your Choice >> ";
        cin >> choice;
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout<<"\n\t\t\t Error You Entered Character, Please Try with Integer \n\n";
        goto m;
    }

        switch(choice) {
            case 1:
                add();
                break;
            case 2:
                Edit();
                break;
            case 3:
                Remove();
                break;
            case 4:
                return;
            default:
                cout << "\n\t\t\tInvalid Option. Please Try Again.\n";
        }
    } while (choice != 4);
}

void Shopping::Buyer() {
    int choice;

    do {
        Ch:
        cout << "\n\n\t\t\t---|  Buyer Menu  |---\n\n";
        cout << "\t\t\t- 1. Buy Product\n";
        cout << "\t\t\t- 2. Back to Main Menu\n\n";
        cout << "\t\t\t  Enter Your Choice >> ";
        cin >> choice;
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout<<"\t\t\t Error Invalid Input , Please Try again \n";
        goto Ch;
    }
        switch (choice) {
            case 1:
                Receipt();
                break;

            case 2:
                return;

            default:
                cout << "Invalid Option. Please Try Again.\n";
        }
    } while (choice != 2);
}

void Shopping::add() {
    setConsoleColor(3);
    fstream data;
    int Token = 0; // Track product with same code
    cout << "\n\t\t\t---|  Add New Product  |---\n\n";

    // Input product details
    PCode:
    cout << "\t\t\t Enter Product Code >> ";
    cin>>PrCode;
    if(cin.fail()){
    // while (!(cin >> PrCode)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\t\t Error: Invalid Input. Please Try Again \n\n";
        goto PCode;
    }

    cout << "\t\t\t Enter Product Name >> ";
    cin.ignore(); // Ignore leftover newline character
    getline(cin, PrName);
    pr:
    cout << "\t\t\t Enter Product Price >> ";
    cin>>PrPrice;
    if(cin.fail()){
    // while (!(cin >> PrPrice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\t\t Error: Invalid Input. Please Try Again \n\n";
        goto pr;
    // }
    }
    PDis:
    cout << "\t\t\t Enter Discount (%) >> ";
    cin >> PrDiscount;
    if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\t\t\t Error: Invalid Input. Please Try Again \n\n";
        goto PDis;
    }

    data.open("Database.txt", ios::in); // Check Duplicates
    if (data) { // opened success or data available
        string line;
        while (getline(data, line)) {
            if (line.empty()) 
            continue; // Skip empty lines

            stringstream ss(line); // Line is Passed for Parsing or divided into separate parts.
            string tempCode, tempName, tempPrice, tempDiscount;

            // Parse the line into individual fields
            getline(ss, tempCode, '|');
            getline(ss, tempName, '|');
            getline(ss, tempPrice, '|');
            getline(ss, tempDiscount, '|');

            if (stoi(tempCode) == PrCode) {
                Token++;
                break;
            }
        }
        data.close();
    }

    // Handle duplicate code case
    if (Token > 0) {
        cout << "\n\t\t\t**  Product with this code already exists. Try again...  **\n\n";
    } else {
        // Append new product to the database
        data.open("Database.txt", ios::app);
        data << PrCode << "|" << PrName << "|" << PrPrice << "|" << PrDiscount << "\n";
        data.close();
        cout << "\n\t\t\t Product Added Successfully.\n";
    }

    setConsoleColor(7);
}

void Shopping::Edit() {
    fstream data, temp;
    int Pkey, Token = 0;
    cout << "\n\t\t\t ---|  EDIT PRODUCTS  |---\n\n";
    cout << "\t\t\t ---|  AVAILABLE PRODUCTS  |---\n";
    List();
    
    m:
    cout << "\t\t\t Enter Product Code to Modify >> ";
    cin >> Pkey;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout << "\t\t\t Error: Invalid Input. Please Try Again.\n";
        goto m;
    }

    data.open("Database.txt", ios::in);
    if (!data) { // Not opened successfully or data does not available/exist
        cout << "\t\t\t ** No Products Found ** \n";
        return;
    }
    temp.open("Temp.txt", ios::out);
    int Code;
    string Name;
    float Price, Discount;

    while (data) { // iterate until data exist , or till the end of data.
        string line;
        getline(data, line);
        if (line.empty()) 
        continue;

        stringstream ss(line);
        string tempCode, tempPrice, tempDiscount;
        getline(ss, tempCode, '|');
        getline(ss, Name, '|');
        getline(ss, tempPrice, '|');
        getline(ss, tempDiscount, '|');

        Code = stoi(tempCode);
        Price = stof(tempPrice);
        Discount = stof(tempDiscount);

        if (Code == Pkey) {
            // Prompt for new details
            CodeInput: 
            cout << "\t\t\t Enter New Code >> ";
            cin >> PrCode;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "\t\t\t Error: Invalid Input. Please Try Again.\n";
                goto CodeInput;
            }

            fstream checkData("Database.txt", ios::in); // Duplicate Check.
            bool duplicateCode = false;
            while (checkData) { // Iterate until data exist / available.
                string checkLine;
                getline(checkData, checkLine); // from checkData to checkLine
                if (checkLine.empty()) 
                continue;

                stringstream checkSS(checkLine);
                string checkCode;
                getline(checkSS, checkCode, '|');

                if (stoi(checkCode) == PrCode && PrCode != Code) {
                    duplicateCode = true;
                    break;
                }
            }
            checkData.close();
            if (duplicateCode) {
                cout << "\t\t\t Error: Product with this code already exists. Try again.\n";
                goto CodeInput;
            }
            cout << "\t\t\t Enter New Name >> ";
            cin.ignore();
            getline(cin, PrName);

            PriceInput:
            cout << "\t\t\t Enter New Price >> ";
            cin >> PrPrice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "\t\t\t Error: Invalid Input. Please Try Again.\n";
                goto PriceInput;
            }
            DiscountInput:
            cout << "\t\t\t Enter New Discount (%) >> ";
            cin >> PrDiscount;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "\t\t\t Error: Invalid Input. Please Try Again.\n";
                goto DiscountInput;
            }

            temp << PrCode << "|" << PrName << "|" << PrPrice << "|" << PrDiscount << "\n";
            cout << "\n\t\t\t |-|   Product Updated Successfully   |-| \n";
            Token++;
        } else {
            temp << Code << "|" << Name << "|" << Price << "|" << Discount << "\n";
        }
    }

    data.close();
    temp.close();

    if (Token == 0) {
        cout << "\n\t\t\t ** Product Not Found **\n";
        remove("Temp.txt");
    } else {
        remove("Database.txt");
        rename("Temp.txt", "Database.txt");
    }
}

void Shopping::Remove() {
    fstream data, temp;
    int Pkey, Token = 0;

    cout << "\n\t\t\t---| Remove Product |---\n";
    List(); // Display the available products first

    // Ask for the product code to remove
    Pk:
    cout << "\n\t\t\tEnter Product Code to Remove >> ";
    cin>>Pkey;
    if(cin.fail()){
    // while (!(cin >> Pkey)) {
        cout << "\t\t\tInvalid input! Please enter a valid product code >> ";
        cin.clear();
        cin.ignore(10000, '\n');
        goto Pk;
    }

    data.open("Database.txt", ios::in);
    if (!data) { // doesn't exist/Available
        cout << "\n\t\t\t** No Products Found **\n";
        return;
    }

    temp.open("Temp.txt", ios::out); 
    string line;

    // Read each line and process it
    while (getline(data, line)) {
        if (line.empty()) continue; // Skip empty lines

        stringstream ss(line);
        string tempCode, tempName, tempPrice, tempDiscount;
        getline(ss, tempCode, '|');
        getline(ss, tempName, '|');
        getline(ss, tempPrice, '|');
        getline(ss, tempDiscount, '|');

        int Code = stoi(tempCode);

        if (Code == Pkey) {
            cout << "\n\t\t\t*** Product Removed Successfully ***\n";
            Token++; // Mark that the product was found and removed
        } else {
            // Write the product to the temporary file if it's not the one to remove
            temp << tempCode << "|" << tempName << "|" << tempPrice << "|" << tempDiscount << "\n";
        }
    }

    data.close();
    temp.close();

    // Replace the original file with the updated temporary file
    if (Token == 0) {
        cout << "\n\t\t\t** Product Not Found **\n";
        remove("Temp.txt");
    } else {
        remove("Database.txt");
        rename("Temp.txt", "Database.txt");
    }
}

void Shopping::List() {
    fstream data;
    data.open("Database.txt", ios::in);

    if (!data) {
        cout << "\n\t\t\t ** Error To Open File **\n";
        return;
    }

    if (data.peek() == EOF) {
        cout << "\n\t\t\t ** No Products In Inventory **\n\n\n";
        data.close();
        return;
    }

    cout << "\n\n\t\t\t ---| Product List |---\n\n";
    cout << "\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\t| Code   | Name                 | Price     | Discount (%) |\n";
    cout << "\t\t\t-------------------------------------------------------------\n";

    string line;
    while (getline(data, line)) {
        stringstream ss(line);

        string Code, Name, Price, Discount;

        // Use 'getline' with a delimiter to extract values
        getline(ss, Code, '|');
        getline(ss, Name, '|');
        getline(ss, Price, '|');
        getline(ss, Discount, '|');

        // Output the formatted result
        cout << "\t\t\t| " << setw(6) << Code << " | "
             << setw(20) << left << Name << " | "
             << setw(9) << right << Price << " | "
             << setw(12) << Discount << " |\n";
    }
    cout << "\t\t\t-------------------------------------------------------------\n";

    data.close();
}

void Shopping::Receipt() {
    fstream data;
    List(); // Show the list of products first
    cout << "\n\n\n\n\t\t\t ---|     Place Order     |---\n\n";

    data.open("Database.txt", ios::in);
    if (!data) {
        cout << "\t\t\t **  Error To Open File  **\n";
        return;
    }

    int Code[1000], Quant[1000], Count = 0;
    char Choice;
    double TotalBill = 0;

    // Taking user input for product codes and quantities
    do {
        GetCode:
        cout << "\t\t\t Enter Product Code >> ";
        cin >> Code[Count];
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout<<"\t\t\t Error Invalid You Enter Character, Please Try again with Integer \n";
        goto GetCode;
    }
        GetQuant:
        cout << "\t\t\t Enter Quantity >> ";
        cin >> Quant[Count];
        if(cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n'); 
        cout<<"\t\t\t Error Invalid Input , Please Try again \n";
        goto GetQuant;
    }
        Count++;

        cout << "\t\t\t Do you want to add more products ? (Press Y for Yes | Other Keys For No) >> ";
        cin >> Choice;
    } while (Choice == 'y' || Choice == 'Y');

    int PrCode;
    string PrName;
    float PrPrice, PrDiscount;
    bool ProductFound;
    cout<<"\n\t\t\t ---|  RECEIPT  |--- \n\n";
    // cout << "\t\t\t----------------------------------------------------------------------------------\n";
    cout << "\t\t\t-----------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t| Code   | Name                 | Quantity    | Price     |Discount (%) | Total With Discount |\n";
    cout << "\t\t\t-----------------------------------------------------------------------------------------------\n";
    // For each entered product code, search the database
    for (int i = 0; i < Count; i++) {
        data.clear();       // Clear EOF flags
        data.seekg(0);      // Rewind to the start of the file
        ProductFound = false;

        while (data) {
            string line;
            getline(data, line); // Read the entire line from database and assign it to line Variable

            if (line.empty()) 
            continue; // Skip empty lines

            stringstream ss(line); // Parse the line using stringstream
            string tempCode, tempPrice, tempDiscount;

            // Read fields using the '|' delimiter
            getline(ss, tempCode, '|');      // Product Code
            getline(ss, PrName, '|');        // Product Name
            getline(ss, tempPrice, '|');     // Product Price
            getline(ss, tempDiscount, '|');  // Product Discount

            // Convert numeric fields from string to proper types
            PrCode = stoi(tempCode);
            PrPrice = stof(tempPrice);
            PrDiscount = stof(tempDiscount);

            // Match the product code
            if (Code[i] == PrCode) { // Code[i] is the code Entered BY User and the PrCode is readed from Database.txt
                double Amount = PrPrice * Quant[i];
                double Discount = Amount * (PrDiscount / 100);
                double FinalAmount = Amount - Discount;
                ProductFound = true;

                TotalBill += FinalAmount;

                // Output the formatted result

                cout << "\t\t\t| " << setw(6) << PrCode << " | "
                     << setw(20) << left << PrName << " | "
                     << setw(8) << right << Quant[i] << "    | "
                     << setw(6) << right << PrPrice << "    | "
                     << setw(8) << PrDiscount << "    | "
                     << setw(8) << FinalAmount << "            |\n";
            }
        }

        // If the product was not found in the database
        if (!ProductFound) {
            cout << "\n\t\t\t ** Error: Invalid Product Code " << Code[i] << " **\n\n\n";
            exit(0);
        }
    }

    data.close();
    cout << "\t\t\t-----------------------------------------------------------------------------------------------\n";
    cout << "\n\n\t\t\t|  Total Amount: " << TotalBill << " |\n";
}

int main() {
    Shopping shop;
    shop.Menu();
    return 0;
}
