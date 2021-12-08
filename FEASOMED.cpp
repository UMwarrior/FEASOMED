//      Project Name : Feasomed

/*
        Object-Oreinted-Programming Project
        Submitted to : Dr. Sarabjeet Singh
        Submitted by : CO20318 Deepak Mahto
                       CO20320 Gopal Mengi
                       CO20365 Uday Madan
*/

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

int main();

//Login Class
class Login
{
    char login[30];
    char pass[30];

public:
    int check(const char *a, const char *b)
    {
        if (strcmp(a, login) == 0 && strcmp(b, pass) == 0)
        {
            return 1;
        }
        return 0;
    }
    Login(const char *a, const char *b)
    {
        strcpy(login, a);
        strcpy(pass, b);
    }
};

//Market Class
class market
{
public:
    char prod[20];
    int price;
    long int total;
    int sr_no;
};

//Item Class
class item
{
public:
    int quantity;
    int limit;
    int sr_no;
    int code;
    char name[20];
    int order_quantity = 0;
};

//Wholesaler Class
class wholesaler
{
public:
    char name[20];
    int rating;
    char r_id[30];
    char r_pass[30];
    int price;
    item items;
    char address[100];
    bool cofirmation = 0;
};

//Order Class
//Inheritance
class order : public item
{
};

//Main Storage Class
class mainStorage
{
public:
    item items;
};

//Class for State
//Inheritance
class st : public mainStorage
{
public:
    char s_name[20];
    char s_id[30];
    char s_pass[30];
    int o = 0;
};

//Class for Region
//Inheritance
class reg : public st
{
public:
    char r_name[20];
    int r_id;
};

//Class for Hospital
//Inheritance
class hos : public reg
{
public:
    char h_name[30];
    char h_id[30];
    char h_pass[30];
};

vector<hos> h;

mainStorage obj;

//Function For Admin
int admin()
{
    system("Color 06");
    cout << "\n\n\n\t\t\t\t\t\t\tWelcome to Admin Portal" << endl
         << endl;
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tPlease select an appropriate option:-" << endl
         << endl;
    cout << "\t\t\t\t \t\t\t1.Add State" << endl
         << "\t\t\t\t \t\t\t2.Add Item" << endl
         << "\t\t\t\t \t\t\t3.Check items" << endl
         << "\t\t\t\t \t\t\t4.Delete Item" << endl
         << "\t\t\t\t \t\t\t5.Change item" << endl
         << "\t\t\t\t \t\t\t6.Check States" << endl
         << "\t\t\t\t \t\t\t7.Add Wholesaler" << endl
         << "\t\t\t\t \t\t\t8.Check Wholesaler" << endl
         << "\t\t\t\t \t\t\t9.Goto Login Page" << endl
         << "\t\t\t\t \t\t\t10.Exit the System" << endl
         << endl
         << "\t\t\t\t\t\t\tEnter the required option:-";

    int option;

    cin >> option;

    system("cls");
    cout << endl
         << endl;

    //Option 1
    //Add State
    if (option == 1)
    {
        st S;
        fstream all_states("states.txt");

        all_states.seekg(0, ios::end);
        int no_states = all_states.tellg() / sizeof(S);

        int n;
        cout << "\n\t\t\t\t\t\t\tEnter number of states to be added :- ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "\n\t\t\t\t\t\t\tSr. No. :- " << no_states + 1 << endl;
            cout << "\t\t\t\t\t\t\tName of state :- ";
            cin >> S.s_name;

            char id[30] = "ID_";
            char pass[30] = "PASS_";

            strcat(id, S.s_name);
            strcat(pass, S.s_name);

            strcpy(S.s_id, id);
            strcpy(S.s_pass, pass);

            all_states.write((char *)&S, sizeof(S));
            char state_name[20];

            strcpy(state_name, S.s_name);
            strcat(state_name, ".txt");

            ofstream S1(state_name);
            fstream temp_s("temp_s.txt");

            cout << "\n\n\t\t\t\t\t\t\tState :- " << S.s_name << " added with Login ID :- " << id << " and Password :- " << pass << endl;

            if (temp_s && S1)
            {
                string line;
                while (getline(temp_s, line))
                {
                    S1 << line;
                }

                S1.close();
                temp_s.close();

                no_states++;
            }
        }
    }

    //Option 2
    //Add Item
    else if (option == 2)
    {

        ifstream in_file("main_storage.txt", ios::binary);
        in_file.seekg(0, ios::end);

        int file_size = in_file.tellg();
        mainStorage object;

        int n;
        int no_items = file_size / sizeof(object);

        cout << "\t\t\t\t\t\t\tEnter number of items to be added:- ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "\t\t\t\t\t\t\tSr. No. :- " << no_items + 1 << endl;
            object.items.sr_no = no_items + 1;

            cout << "\t\t\t\t\t\t\tName :- ";
            cin >> object.items.name;

            cout << "\t\t\t\t\t\t\tProduct Code:- ";
            cin >> object.items.code;
            object.items.quantity = 0;
            object.items.limit = 0;

            ofstream file1;

            file1.open("main_storage.txt", ios::app);
            file1.write((char *)&object, sizeof(object));

            file1.close();
            st S;

            fstream all_states("states.txt");
            all_states.seekg(0, ios::end);

            int no_states = all_states.tellg() / sizeof(S);
            all_states.seekg(0, ios::beg);

            for (int i = 0; i < no_states; i++)
            {
                all_states.read((char *)&S, sizeof(S));
                char state_name[20];

                strcpy(state_name, S.s_name);
                strcat(state_name, ".txt");

                ofstream fp(state_name, ios::app);
                st S1;

                S1.items.sr_no = no_items + 1;
                strcpy(S1.items.name, object.items.name);

                S1.items.quantity = 0;
                S1.items.limit = 0;

                S1.items.code = object.items.code;
                fp.write((char *)&S1, sizeof(S1));

                fp.close();
            }

            ofstream fp1("temp_s.txt", ios::app);
            st S2;

            S2.items.sr_no = no_items + 1;
            strcpy(S2.items.name, object.items.name);

            S2.items.quantity = 0;
            S2.items.limit = 0;

            S2.items.code = object.items.code;
            fp1.write((char *)&S2, sizeof(S2));

            fp1.close();
            file1.close();

            ofstream fp2("temp_h.txt", ios::app);

            hos h2;

            h2.items.sr_no = no_items + 1;
            strcpy(h2.items.name, object.items.name);

            h2.items.quantity = 0;
            h2.items.limit = 0;

            h2.items.code = object.items.code;
            fp2.write((char *)&h2, sizeof(h2));

            fp2.close();
            file1.close();

            no_items++;
        }

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tItems Added Successfully" << endl;
    }

    //Option 3
    //Check Items
    else if (option == 3)
    {
        mainStorage ms;
        ifstream file2;
        int keydec = 0;

        file2.open("main_storage.txt", ios::in);
        file2.seekg(0, ios::end);

        int file_size = file2.tellg();
        int n_items = file_size / sizeof(ms);

        file2.seekg(0, ios::beg);

        for (int i = 0; i < n_items; i++)
        {
            if (keydec == 0)
            {
                cout << "\n\t\t\t\t\t" << left
                     << setw(10) << "Sr. No."
                     << "|" << left << setw(40) << "Product Name"
                     << "|" << left << setw(20) << "Quantity"
                     << "|" << left << setw(20) << "Product Code"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t"
                     << "----------|----------------------------------------|--------------------|--------------------|";
                cout << "\t\t\t\t\t"
                     << "\n";
            }
            keydec++;

            file2.read((char *)&ms, sizeof(ms));

            cout << "\t\t\t\t\t" << left
                 << setw(10) << ms.items.sr_no << "|" << left << setw(40) << ms.items.name << "|" << left << setw(20) << ms.items.quantity << "|" << left << setw(20) << ms.items.code << "|"
                 << "\n";
        }
        file2.close();
    }

    //Option 4
    //Delete Items
    else if (option == 4)
    {
        int i = 1;

        fstream file2("main_storage.txt", ios::in);
        fstream file3("dup.txt", ios::app);

        mainStorage md;

        long long n;

        cout << "\t\t\t\t\t\t\tEnter the code of the product you want to delete : ";

        cin >> n;

        while (file2.read((char *)&md, sizeof(md)))
        {
            if (n == md.items.code)
            {
                continue;
            }

            else
            {
                md.items.sr_no = i;
                file3.write((char *)&md, sizeof(md));
            }
            i++;
        }
        file2.close();
        file3.close();

        remove("main_storage.txt");
        rename("dup.txt", "main_storage.txt");

        fstream file1("temp_s.txt");
        file2.open("dup1.txt", ios::app);

        st sd;

        i = 1;

        while (file1.read((char *)&sd, sizeof(sd)))
        {
            if (n == sd.items.code)
            {
                continue;
            }

            else
            {
                sd.items.sr_no = i;
                file2.write((char *)&sd, sizeof(sd));
            }
            i++;
        }

        file1.close();
        file2.close();

        remove("temp_s.txt");
        rename("dup1.txt", "temp_s.txt");

        file1.open("states.txt", ios::in);

        file1.seekg(0, ios::end);
        int no_states = file1.tellg() / sizeof(sd);
        file1.seekg(0, ios::beg);

        int j = 1;

        for (i = 0; i < no_states; i++)
        {
            file1.read((char *)&sd, sizeof(sd));
            char state_name[20];

            strcpy(state_name, sd.s_name);
            strcat(state_name, ".txt");

            fstream file2(state_name);

            st sdd;

            fstream file3("dup3.txt", ios::app);

            while (file2.read((char *)&sdd, sizeof(sdd)))
            {
                if (n == sdd.items.code)
                {
                    continue;
                }

                else
                {
                    sdd.items.sr_no = j;
                    file3.write((char *)&sdd, sizeof(sdd));
                }
                j++;
            }

            file2.close();
            file3.close();

            remove(state_name);
            rename("dup3.txt", state_name);
        }
        file1.close();
    }

    //Option 5
    //Change Items
    else if (option == 5)
    {
        int i = 1;
        char name[30];
        int code;

        fstream file2("main_storage.txt", ios::in);
        fstream file3("dup.txt", ios::app);
        mainStorage md;

        long long n;

        cout << "\t\t\t\t\t\t\tEnter the code of the product you want to Update : ";

        cin >> n;
        cout << "\t\t\t\t\t\t\tEnter the name of new product :- ";
        cin >> name;
        cout << "\t\t\t\t\t\t\tEnter the Product Code :- ";
        cin >> code;

        while (file2.read((char *)&md, sizeof(md)))
        {
            if (n == md.items.code)
            {
                md.items.sr_no = i;
                md.items.code = code;

                strcpy(md.items.name, name);

                md.items.quantity = 0;
                md.items.limit = 0;

                file3.write((char *)&md, sizeof(md));
            }

            else
            {
                md.items.sr_no = i;
                file3.write((char *)&md, sizeof(md));
            }
            i++;
        }
        file2.close();
        file3.close();

        remove("main_storage.txt");
        rename("dup.txt", "main_storage.txt");

        fstream file1("temp_s.txt");
        file2.open("dup1.txt", ios::app);

        st sd;

        i = 1;

        while (file1.read((char *)&sd, sizeof(sd)))
        {
            if (n == sd.items.code)
            {
                sd.items.sr_no = i;
                sd.items.code = code;

                strcpy(sd.items.name, name);

                sd.items.quantity = 0;
                sd.items.limit = 0;

                file2.write((char *)&sd, sizeof(sd));
            }

            else
            {
                sd.items.sr_no = i;
                file2.write((char *)&sd, sizeof(sd));
            }
            i++;
        }

        file1.close();
        file2.close();

        remove("temp_s.txt");
        rename("dup1.txt", "temp_s.txt");

        file1.open("states.txt", ios::in);

        file1.seekg(0, ios::end);
        int no_states = file1.tellg() / sizeof(sd);
        file1.seekg(0, ios::beg);

        int j = 1;

        for (i = 0; i < no_states; i++)
        {
            file1.read((char *)&sd, sizeof(sd));
            char state_name[20];

            strcpy(state_name, sd.s_name);
            strcat(state_name, ".txt");

            fstream file2(state_name);

            st sdd;
            fstream file3("dup3.txt", ios::app);

            while (file2.read((char *)&sdd, sizeof(sdd)))
            {
                if (n == sdd.items.code)
                {
                    sdd.items.sr_no = j;
                    sdd.items.code = code;

                    strcpy(sdd.items.name, name);
                    sdd.items.quantity = 0;
                    sdd.items.limit = 0;

                    file3.write((char *)&sdd, sizeof(sdd));
                }

                else
                {
                    sdd.items.sr_no = j;
                    file3.write((char *)&sdd, sizeof(sdd));
                }
                j++;
            }

            file2.close();
            file3.close();

            remove(state_name);
            rename("dup3.txt", state_name);
        }
        file1.close();
    }

    //Option 6
    //Check States
    else if (option == 6)
    {
        st S;
        fstream all_states("states.txt");

        all_states.seekg(0, ios::end);
        int no_states = all_states.tellg() / sizeof(S);
        all_states.seekg(0, ios::beg);

        for (int i = 0; i < no_states; i++)
        {
            // S.sno=i;
            all_states.read((char *)&S, sizeof(S));
            cout << "\t\t\t\t\t\t\tSr. No. : " << i + 1 << endl;
            cout << "\t\t\t\t\t\t\tName : " << S.s_name << endl;
        }
        all_states.close();
    }

    //Option 7
    //Add Wholesaler
    else if (option == 7)
    {
        wholesaler RT;

        int n;
        fstream in_file("wholesaler.txt");

        cout << "\n\t\t\t\t\t\t\tNumber of wholesalers you want to add :- ";
        cin >> n;

        in_file.seekg(0, ios::end);
        int file_size = in_file.tellg();
        int m = file_size / sizeof(RT);

        // in_file.open("wholesaler.txt", ios::app);

        for (int i = 0; i < n; i++)
        {
            cout << "\n\t\t\t\t\t\t\tEnter the details of the wholesaler\n";
            cout << "\t\t\t\t\t\t\tSr. No. : " << m + 1 << endl;

            cout << "\t\t\t\t\t\t\tName : ";
            cin >> RT.name;

            cout << "\t\t\t\t\t\t\tRating out of 5 : ";
            cin >> RT.rating;

            cout << "\t\t\t\t\t\t\tAddress : ";
            cin >> RT.address;

            char id[30] = "ID_";
            char pass[30] = "FEASO_";

            strcat(id, RT.name);
            strcat(pass, RT.name);

            strcpy(RT.r_id, id);
            strcpy(RT.r_pass, pass);
            in_file.write((char *)&RT, sizeof(RT));
            cout << endl
                 << endl
                 << endl
                 << endl
                 << "\t\t\t\t\tWholsaler " << RT.name << " added With Login ID :- " << id << " and Password " << pass << endl
                 << endl;

            m++;
        }
        in_file.close();
    }

    //Option 8
    //Check Wholesaler
    else if (option == 8)
    {
        cout << "\n\t\t\t\t\t\t\tThe Wholesalers are\n";

        wholesaler R;
        fstream ret("wholesaler.txt");

        ret.seekg(0, ios::end);
        int no_states = ret.tellg() / sizeof(R);
        ret.seekg(0, ios::beg);

        for (int i = 0; i < no_states; i++)
        {
            ret.read((char *)&R, sizeof(R));
            cout << "\n\t\t\t\t\t\t\tSr. No. : " << i + 1 << endl;
            cout << "\t\t\t\t\t\t\tName : " << R.name << endl;
            cout << "\t\t\t\t\t\t\tWholesaler ID : " << R.r_id << endl;
            cout << "\t\t\t\t\t\t\tWholesaler address : " << R.address << endl;
            cout << "\t\t\t\t\t\t\tWholesaler rating : " << R.rating << endl;
        }
        ret.close();
    }

    //Option 9
    //GOTO Login Page
    else if (option == 9)
    {
        main();

        return 0;
    }

    //Option 10
    //Exit The system
    else if (option == 10)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }

    //Defualt Option
    else
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t\tWrong Entry. Try again!\n";

        Sleep(2000);
        system("cls");

        admin();
    }
menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :- " << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");
        admin();

        return 0;
    }
    else if (option2 == 2)
    {
        system("cls");
        main();

        return 0;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");
        cout << "\t\t\t\t\t\t\tWrong Entry. Try again!\n";

        Sleep(2000);
        system("cls");

        goto menu2;
    }

    return 0;
}

//Function For Main Storage
int main_storage()
{
    system("Color 06");
    cout << "\n\n\n\t\t\t\t\t\t\tWelcome to Main Storage" << endl
         << endl;
    cout << "\t\t\t\t\t\t\t"
         << "Please select an appropriate option:-" << endl
         << endl;
    cout << "\t\t\t\t \t\t\t1.Display Stocks" << endl
         << "\t\t\t\t \t\t\t2.Check Orders" << endl
         << "\t\t\t\t \t\t\t3.Place Orders" << endl
         << "\t\t\t\t \t\t\t4.Finalise Quotation" << endl
         << "\t\t\t\t \t\t\t5.Recieve Order" << endl
         << "\t\t\t\t \t\t\t6.Goto Login Page" << endl
         << "\t\t\t\t \t\t\t7.Exit" << endl
         << endl
         << "\t\t\t\t\t\t\tEnter the required option:-";

    int option;
    cin >> option;

    system("cls");
    cout << endl
         << endl;

    //Option 1
    //Display Stocks
    if (option == 1)
    {
        mainStorage ms;
        ifstream file2;
        int keydec = 0;

        file2.open("main_storage.txt", ios::in);
        file2.seekg(0, ios::end);

        int file_size = file2.tellg();
        int n_items = file_size / sizeof(ms);

        file2.seekg(0, ios::beg);

        for (int i = 0; i < n_items; i++)
        {
            if (keydec == 0)
            {
                cout << "\t\t\t\t\t" << left
                     << setw(10) << "Sr. No."
                     << "|" << left << setw(40) << "Product Name"
                     << "|" << left << setw(20) << "Quantity"
                     << "|" << left << setw(20) << "Product Code"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t"
                     << "----------|----------------------------------------|--------------------|--------------------|";
                cout << "\t\t\t\t\t"
                     << "\n";
            }
            keydec++;

            file2.read((char *)&ms, sizeof(ms));

            cout << "\t\t\t\t\t" << left
                 << setw(10) << ms.items.sr_no << "|" << left << setw(40) << ms.items.name << "|" << left << setw(20) << ms.items.quantity << "|" << left << setw(20) << ms.items.code << "|"
                 << "\n";
        }
        file2.close();
    }
    /*{
        mainStorage ms;
        ifstream file2;

        file2.open("main_storage.txt", ios::in);
        file2.seekg(0, ios::end);

        int file_size = file2.tellg();
        int n_items = file_size / sizeof(ms);

        file2.seekg(0, ios::beg);

        for (size_t i = 0; i < n_items; i++)
        {
            file2.read((char *)&ms, sizeof(ms));

            cout << "\t\t\t\t\t\t\t"
                 << "Sr. No. :- " << ms.items.sr_no << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Name :- " << ms.items.name << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Quantity :- " << ms.items.quantity << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Code :- " << ms.items.code << endl
                 << endl;
        }
        file2.close();
    }*/

    //Option 2
    //Check Order
    else if (option == 2)
    {
        st S;
        fstream all_states("states.txt");

        all_states.seekg(0, ios::end);

        int no_states = all_states.tellg() / sizeof(S);

        all_states.seekg(0, ios::beg);

        for (int i = 0; i < no_states; i++)
        {
            all_states.read((char *)&S, sizeof(S));
            char state_name[30];

            strcpy(state_name, S.s_name);
            strcat(state_name, ".txt");

            fstream file2(state_name);

            st state1;

            file2.seekg(0, ios::end);
            int file_size = file2.tellg();
            int n_items = file_size / sizeof(state1);

            file2.seekg(0, ios::beg);

            int test = 0;
            fstream file3("oc.txt", ios::app);

            for (int i = 0; i < n_items; i++)
            {

                file2.read((char *)&state1, sizeof(state1));
                int h = 0, g = 0;
                if (state1.o == 1 && test == 0)
                {
                    if (h == 0)
                    {
                        cout << "\t\t\t\t\t" << left
                             << setw(10) << "Ref. No."
                             << "|" << left << setw(40) << "Name"
                             << "|"
                             << "\n";
                        cout << "\t\t\t\t\t"
                             << "----------|----------------------------------------|";
                        cout << "\t\t\t\t\t"
                             << "\n";
                        h++;
                    }
                    /* cout << "\t\t\t\t\t\t\t"
                         << "S No. : " << i + 1 << endl;
                    cout << "\t\t\t\t\t\t\t"
                         << "Name : " << S.s_name << endl;*/
                    cout << "\t\t\t\t\t" << left
                         << setw(10) << i + 1 << "|" << left << setw(40) << S.s_name << "|"
                         << "\n";

                    test++;
                }
                cout << "\n\n";

                if (state1.o == 1)
                {
                    /*cout << "\t\t\t\t\t\t\t"
                         << "Sr. No. :- " << state1.items.sr_no << endl;
                    cout << "\t\t\t\t\t\t\t"
                         << "Product Name :- " << state1.items.name << endl;
                    cout << "\t\t\t\t\t\t\t"
                         << "Quantity :- " << state1.items.order_quantity << endl;*/
                    if (g == 0)
                    {
                        cout << "\t\t\t\t\t" << left
                             << setw(10) << "Ref. No."
                             << "|" << left << setw(40) << "Product Name"
                             << "|" << left << setw(20) << "Order Quantity"
                             << "|"
                             << "\n";
                        cout << "\t\t\t\t\t"
                             << "----------|----------------------------------------|--------------------|";
                        cout << "\t\t\t\t\t"
                             << "\n";
                        g++;
                    }
                    cout << "\t\t\t\t\t" << left
                         << setw(10) << state1.items.sr_no << "|" << left << setw(40) << state1.items.name << "|" << left << setw(20) << state1.items.order_quantity << "|"
                         << "\n";

                    mainStorage ms;
                    fstream fp("main_storage.txt");
                    fstream temp("temp.txt", ios::app);

                    fp.seekg(0, ios::end);
                    int n = fp.tellg() / sizeof(ms);
                    fp.seekg(0, ios::beg);

                    cout << "\n\t\t\t\t\t\t\t"
                         << "Do you want to dispatch this order now? Y/N :- ";
                    char C;
                    cin >> C;

                    if (C == 'Y')
                    {
                        for (int i = 0; i < n; i++)
                        {
                            fp.read((char *)&ms, sizeof(ms));
                            if (strcmp(state1.items.name, ms.items.name) == 0)
                            {
                                ms.items.quantity = ms.items.quantity - state1.items.order_quantity;
                                cout << "\n\n\t\t\t\t\t\t\tProduct :- " << state1.items.name << " With Quantity :- " << state1.items.order_quantity << " Dispatched for " << state1.s_name << endl;
                            }
                            temp.write((char *)&ms, sizeof(ms));
                        }

                        state1.o = 2;
                    }
                    fp.close();
                    temp.close();

                    remove("main_storage.txt");
                    rename("temp.txt", "main_storage.txt");
                }

                file3.write((char *)&state1, sizeof(state1));
            }
            file2.close();
            file3.close();

            remove(state_name);
            rename("oc.txt", state_name);
        }
        all_states.close();
    }

    //Option 3
    //Place Order
    else if (option == 3)
    {
        mainStorage ms;
        ifstream file2;

        file2.open("main_storage.txt", ios::in);
        file2.seekg(0, ios::end);
        int file_size = file2.tellg();
        int n_items = file_size / sizeof(ms);

        file2.seekg(0, ios::beg);
        int u = 0;

        for (size_t i = 0; i < n_items; i++)
        {
            file2.read((char *)&ms, sizeof(ms));
            /*cout << "\t\t\t\t\t\t\t"
                 << "Sr. No. :- " << ms.items.sr_no << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Name :- " << ms.items.name << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Code :- " << ms.items.code << endl
                 << endl;*/
            if (u == 0)
            {
                cout << "\t\t\t\t\t" << left
                     << setw(10) << "Sr. No."
                     << "|" << left << setw(40) << "Product Name"
                     << "|" << left << setw(20) << "Product Code"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t"
                     << "----------|----------------------------------------|--------------------|";
                cout << "\t\t\t\t\t"
                     << "\n";
                u++;
            }
            cout << "\t\t\t\t\t" << left
                 << setw(10) << ms.items.sr_no << "|" << left << setw(40) << ms.items.name << "|" << left << setw(20) << ms.items.code << "|"
                 << "\n";
        }
        cout << "\n\t\t\t\t\t\t\tEnter number of items to be ordered :- ";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            if (n_items == 0)
            {
                cout << "\t\t\t\t\t\t\tNo items present\n";
                break;
            }

            int p_code;
            cout << "\n\t\t\t\t\t\t\tEnter product code of the product:- ";
            cin >> p_code;

            order test;
            fstream file3("order.txt");

            file3.seekg(0, ios ::end);
            int k = file3.tellg() / sizeof(test);
            file3.close();

            file2.seekg(0, ios::beg);

            for (int j = 0; j < n_items; j++)
            {
                file2.read((char *)&ms, sizeof(ms));
                if (p_code == ms.items.code)
                {
                    order odr;
                    strcpy(odr.name, ms.items.name);
                    cout << "\t\t\t\t\t\t\tEnter Quantity :- ";

                    int quantity;
                    cin >> quantity;

                    odr.quantity = quantity;
                    odr.sr_no = k + 1;

                    fstream file3("order.txt", ios::app);
                    file3.write((char *)&odr, sizeof(odr));
                    file3.close();

                    k++;

                    cout << "\n\t\t\t\t\t\t\tYour Order has been succesfully placed\n";
                }
            }
        }

        file2.close();
    }

    //Option 4
    //Finalize Quatation
    else if (option == 4)
    {
        wholesaler rt;

        fstream file1("application_from_retailor.txt");

        file1.seekg(0, ios::end);
        int no_of_bids = file1.tellg() / sizeof(rt);
        file1.seekg(0, ios::beg);

        fstream file2("order.txt");
        order odr;

        file2.seekg(0, ios::end);
        int file_size = file2.tellg();
        int n_items = file_size / sizeof(odr);

        file2.seekg(0, ios::beg);

        cout << "\t\t\t\t\t\t\t" << left << setw(10) << "Ref. No."
             << left << setw(30)
             << "Name" << endl;

        for (int i = 1; i <= n_items; i++)
        {
            file2.read((char *)&odr, sizeof(odr));

            cout << "\t\t\t\t\t\t\t" << left << setw(10) << odr.sr_no << left << setw(30) << odr.name << endl;
        }

        int n;

        cout << "\t\t\t\t\t\t\tEnter number of items :- ";
        cin >> n;

        for (int k = 0; k < n; k++)
        {

            cout << "\n\t\t\t\t\t\t\tEnter the Ref. No. of the item for which you want to Check the quotation :- ";
            int s_no;
            cin >> s_no;

            cout << "\t\t\t\t\t\t\t" << left << setw(30)
                 << "Id of Wholesaler"
                 << left << setw(30)
                 << "Item Name"
                 << left << setw(20)
                 << "Total Price" << endl;

            file1.seekg(0, ios::beg);

            for (int i = 0; i < no_of_bids; i++)
            {
                file1.read((char *)&rt, sizeof(rt));

                if (rt.items.sr_no == s_no)
                {
                    cout << "\t\t\t\t\t\t\t" << left << setw(30) << rt.r_id << left << setw(30) << rt.items.name << left << setw(20) << rt.price << endl;
                }
            }
        }
        file2.close();
        file1.close();

        cout << "\t\t\t\t\t\t\tYou Want to finalise a quotation ?"
             << "\n\t\t\t\t\t\t\tEnter Y for yes and N for no :- ";

        char a;
        cin >> a;

        if (a == 'Y')
        {
            cout << "\t\t\t\t\t\t\tEnter the number of items you want to finalise :- ";

            int z;
            cin >> z;

            for (int i = 0; i < z; i++)
            {
                fstream file1("application_from_retailor.txt");
                fstream file2("order.txt");

                cout << "\n\t\t\t\t\t\t\tEnter the Ref. No. of the item you want to finalise :- ";

                int s1_no;
                cin >> s1_no;

                cout << "\t\t\t\t\t\t\tEnter the retailor ID you want to finalise :- ";

                char rid[30];
                cin >> rid;

                file1.seekg(0, ios::beg);

                cout << endl
                     << endl
                     << "\t\t\t\t\t\t\tQuotation is finalised successfully." << endl;

                fstream temp1("temp1.txt", ios::app);
                fstream temp2("temp2.txt", ios::app);

                for (int l = 0; l < no_of_bids; l++)
                {
                    file1.read((char *)&rt, sizeof(rt));
                    if (s1_no == rt.items.sr_no && strcmp(rid, rt.r_id) == 0)
                    {
                        fstream file3("status.txt", ios::app);

                        file3.write((char *)&rt, sizeof(rt));
                        file3.close();
                    }
                    if (s1_no != rt.items.sr_no)
                    {
                        temp1.write((char *)&rt, sizeof(rt));
                    }
                }

                file2.seekg(0, ios::beg);
                for (int l = 0; l < n_items; l++)
                {
                    file2.read((char *)&odr, sizeof(odr));
                    if (odr.sr_no != s1_no)
                    {
                        temp2.write((char *)&odr, sizeof(odr));
                    }
                }

                temp1.close();
                temp2.close();

                file2.close();
                file1.close();

                remove("application_from_retailor.txt");
                rename("temp1.txt", "application_from_retailor.txt");

                remove("order.txt");
                rename("temp2.txt", "order.txt");
            }
        }
    }

    //Option 5
    //Receive Order
    else if (option == 5)
    {
        fstream file1("status.txt");
        wholesaler rt;

        file1.seekg(0, ios::end);
        int n_o = file1.tellg() / sizeof(rt);
        file1.seekg(0, ios::beg);

        if (n_o != 0)
        {
            cout << "\t\t\t\t\t" << left << setw(10) << "Sr.No." << left << setw(30) << "Retailor Id" << left << setw(30) << "Name of product" << left << setw(20) << "Quantity of Product" << endl;
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tNO items to recieve\n";

            Sleep(1500);
            system("cls");

            main_storage();
            exit(0);
        }

        for (int i = 0; i < n_o; i++)
        {
            file1.read((char *)&rt, sizeof(rt));

            if (rt.cofirmation == 1)
            {
                cout << "\t\t\t\t\t" << left << setw(10) << i + 1 << left << setw(30) << rt.r_id << left << setw(30) << rt.items.name << left << setw(20) << rt.items.quantity << endl;
            }
        }

        file1.close();

        cout << "\n\t\t\t\t\t\t\tYou want to recieve any order ? Enter Y for yes and N for No :- ";

        char a;
        cin >> a;

        if (a == 'N')
        {
            main_storage();
            exit(0);
        }

        for (int i = 0; i < n_o; i++)
        {
            cout << "\n\t\t\t\t\t\t\tEnter number of orders you want to recieve :- ";

            int orders;
            cin >> orders;

            for (int j = 0; j < orders; j++)
            {
                fstream file1("status.txt");
                fstream temp1("temp1.txt", ios::app);

                cout << "\n\t\t\t\t\t\t\tEnter the serial number of order you want to recieve :- ";

                int sno;
                cin >> sno;

                file1.read((char *)&rt, sizeof(rt));

                if (sno == j + 1)
                {
                    mainStorage ms;
                    fstream file2("main_storage.txt");

                    file2.seekg(0, ios::end);
                    int size_ms = file2.tellg() / sizeof(ms);
                    file2.seekg(0, ios::beg);

                    fstream temp2("temp2.txt", ios::app);

                    for (int k = 0; k < size_ms; k++)
                    {
                        file2.read((char *)&ms, sizeof(ms));

                        if (strcmp(rt.items.name, ms.items.name) == 0)
                        {
                            ms.items.quantity = ms.items.quantity + rt.items.quantity;

                            cout << "\n\n\t\t\t\t\t\t\tOrdered recieved successfully\n";
                        }
                        temp2.write((char *)&ms, sizeof(ms));
                    }
                    file2.close();
                    temp2.close();

                    remove("main_storage.txt");
                    rename("temp2.txt", "main_storage.txt");
                }
                else
                {
                    temp1.write((char *)&rt, sizeof(rt));
                }

                file1.close();
                temp1.close();

                remove("status.txt");
                rename("temp1.txt", "status.txt");
            }
        }
    }

    //Option 6
    //GOTO Login Page
    else if (option == 6)
    {

        system("cls");
        main();
        return 0;
    }

    //Option 7
    //Exit
    else if (option == 7)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }

    //Default Option
    else
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t\tWrong Entry. Try again!\n";

        Sleep(2000);
        system("cls");

        main_storage();

        return 0;
    }

menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :- "
         << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");

        main_storage();
        return 0;
    }
    else if (option2 == 2)
    {
        system("cls");

        main();
        return 0;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");

        cout << "\t\t\t\t\t\t\tWrong Entry" << endl
             << "\t\t\t\t\t\t\tTry again!";
        Sleep(2000);

        system("cls");

        goto menu2;
    }

    return 0;
}

//Function For State
int state(char *state)
{
    system("Color 06");
menu:
    st state1;
    char state_name[30];

    strcpy(state_name, state);
    char s_name[20];
    char s1_name[20];

    strcpy(s_name, state_name);
    strcpy(s1_name, state_name);

    cout << endl
         << endl
         << "\t\t\t\t\t\t\tWelcome to " << state_name << " Storage " << endl
         << endl;
    cout << "\t\t\t\t\t\t\tPlease select an appropriate option:-" << endl
         << endl;
    cout << "\t\t\t\t \t\t\t1.Display Stocks" << endl
         << "\t\t\t\t \t\t\t2.Check Orders" << endl
         << "\t\t\t\t \t\t\t3.Place Orders" << endl
         << "\t\t\t\t \t\t\t4.Recieve Order" << endl
         << "\t\t\t\t \t\t\t5.Add Hospital" << endl
         << "\t\t\t\t \t\t\t6.Display Hospital" << endl
         << "\t\t\t\t \t\t\t7.Goto Login Page" << endl
         << "\t\t\t\t \t\t\t8.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tEnter the required option:-";

    strcat(state_name, ".txt");

    int option;
    cin >> option;

    system("cls");
    cout << endl
         << endl;

    //Option 1
    //Display Stocks
    if (option == 1)
    {
        int keydec = 0;

        fstream file2(state_name);
        file2.seekg(0, ios::end);
        int file_size = file2.tellg();

        int n_items = file_size / sizeof(state1);

        file2.seekg(0, ios::beg);

        for (int i = 0; i < n_items; i++)
        {
            if (keydec == 0)
            {
                cout << "\t\t\t\t\t" << left
                     << setw(10) << "Sr. No."
                     << "|" << left << setw(40) << "Product Name"
                     << "|" << left << setw(20) << "Quantity"
                     << "|" << left << setw(20) << "Product Code"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t"
                     << "----------|----------------------------------------|--------------------|--------------------|";
                cout << "\t\t\t\t\t"
                     << "\n";
            }
            keydec++;

            file2.read((char *)&state1, sizeof(state1));

            cout << "\t\t\t\t\t" << left
                 << setw(10) << state1.items.sr_no << "|" << left << setw(40) << state1.items.name << "|" << left << setw(20) << state1.items.quantity << "|" << left << setw(20) << state1.items.code << "|"
                 << "\n";
        }
        file2.close();
    }
    /*if (option == 1)
    {

        fstream file2(state_name);
        file2.seekg(0, ios::end);
        int file_size = file2.tellg();
        int n_items = file_size / sizeof(state1);

        file2.seekg(0, ios::beg);

        for (int i = 0; i < n_items; i++)
        {
            file2.read((char *)&state1, sizeof(state1));
            cout << "\t\t\t\t\t\t\t"
                 << "Sr. No. :- " << state1.items.sr_no << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Name :- " << state1.items.name << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Quantity :- " << state1.items.quantity << endl;
            cout << "\t\t\t\t\t\t\t"
                 << "Product Code :- " << state1.items.code << endl
                 << endl;
        }
        file2.close();
    }*/

    //Option 2
    //Check Order
    else if (option == 2)
    {
        hos h1, h2;
        int v = 0;
        fstream file11("order_h.txt");

        file11.seekg(0, ios::end);
        int n_o = file11.tellg() / sizeof(h1);

        file11.seekg(0, ios::beg);

        cout << "\t\t\t\t\t\t\tEnter the region for which you want to check the order :- ";

        char r_name[30];
        cin >> r_name;

        fstream fp("temp_h.txt");
        fp.seekg(0, ios::end);
        int n_i = fp.tellg() / sizeof(h2);
        fp.seekg(0, ios::beg);
        cout << endl;

        int order[n_i];
        for (int i = 0; i < n_i; i++)
        {
            order[i] = 0;
        }

        for (int i = 0; i < n_o; i++)
        {
            file11.read((char *)&h1, sizeof(h1));

            if (strcmp(s_name, h1.s_name) == 0 && strcmp(r_name, h1.r_name) == 0 && h1.o == 0)
            {
                fp.seekg(0, ios::beg);
                for (int j = 0; j < n_i; j++)
                {

                    fp.read((char *)&h2, sizeof(h2));
                    if (strcmp(h1.items.name, h2.items.name) == 0)
                    {
                        order[h2.items.sr_no - 1] = order[h2.items.sr_no - 1] + h1.items.order_quantity;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < n_i; i++)
        {
            if (order[i] == 0)
            {
                continue;
            }
            fp.seekg(0, ios::beg);
            for (int j = 0; j < n_i; j++)
            {
                fp.read((char *)&h2, sizeof(h2));
                if (h2.items.sr_no == i + 1)
                {
                    if (v == 0)
                    {
                        cout << "\t\t\t\t\t" << left << setw(40) << "Product Name"
                             << "|" << left << setw(20) << "Quantity"
                             << "|"
                             << "\n";
                        cout << "\t\t\t\t\t"
                             << "----------------------------------------|--------------------|";
                        cout << "\t\t\t\t\t"
                             << "\n";
                        v++;
                    }
                    cout << "\t\t\t\t\t" << left
                         << setw(40) << h2.items.name << "|" << left << setw(20) << order[i] << "|"
                         << "\n";

                    /*cout << "\t\t\t\t\t\t\t"
                         << "Product Name :- " << h2.items.name << endl;

                    cout << "\t\t\t\t\t\t\t"
                         << "Quantity :- " << order[i] << endl
                         << endl;*/
                }
            }
        }
        file11.close();

        cout << "\n\t\t\t\t\t\t\tDo you want to dispatch any order ? Y/N :- ";

        char c;
        cin >> c;

        if (c == 'Y')
        {

            cout << "\n\t\t\t\t\t\t\tHow many orders you want to Dispatch :- ";

            int n;
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                file11.seekg(0, ios::beg);

                cout << "\n\t\t\t\t\t\t\tEnter the name of the product you want to dispatch :- ";

                char i_name[20];
                cin >> i_name;

                st st1;
                fstream store(state_name);
                fstream temp("temp.txt", ios::app);

                store.seekg(0, ios::end);
                int size = store.tellg() / sizeof(st1);
                store.seekg(0, ios::beg);

                for (int j = 0; j < size; j++)
                {
                    store.read((char *)&st1, sizeof(st1));
                    if (strcmp(st1.items.name, i_name) == 0)
                    {
                        st1.items.quantity = st1.items.quantity - order[st1.items.sr_no - 1];
                        cout << "\n\n\t\t\t\t\t\t\tProduct :-" << st1.items.name << " with Quantity :- " << order[st1.items.sr_no - 1] << " Dispatched" << endl;
                    }
                    temp.write((char *)&st1, sizeof(st1));
                }

                store.close();
                temp.close();

                remove(state_name);
                rename("temp.txt", state_name);

                fstream file("order_h.txt");
                fstream temp2("temp2.txt", ios::app);

                for (int i = 0; i < n_o; i++)
                {
                    file.read((char *)&h1, sizeof(h1));
                    if (strcmp(s_name, h1.s_name) == 0 && strcmp(r_name, h1.r_name) == 0)
                    {

                        if (strcmp(h1.items.name, i_name) == 0)
                        {
                            h1.o = 1;
                        }
                    }
                    temp2.write((char *)&h1, sizeof(h1));
                }
                file.close();
                temp2.close();

                remove("order_h.txt");
                rename("temp2.txt", "order_h.txt");
            }
        }
    }

    //Option 3
    //Place Order
    else if (option == 3)
    {
        st ss;
        ifstream file2;

        file2.open(state_name, ios::in);
        file2.seekg(0, ios::end);

        int file_size = file2.tellg();
        int n_items = file_size / sizeof(ss);
        file2.seekg(0, ios::beg);

        int items = 0;
        int f = 0;
        cout << endl;

        for (size_t i = 0; i < n_items; i++)
        {
            if (ss.o == 0)
            {
                file2.read((char *)&ss, sizeof(ss));
                if (f == 0)
                {
                    cout << "\t\t\t\t\t" << left
                         << setw(10) << "Sr. No."
                         << "|" << left << setw(40) << "Product Name"
                         << "|" << left << setw(20) << "Product Code"
                         << "|"
                         << "\n";
                    cout << "\t\t\t\t\t"
                         << "----------|----------------------------------------|--------------------|";
                    cout << "\t\t\t\t\t"
                         << "\n";
                    f++;
                }
                cout << "\t\t\t\t\t" << left
                     << setw(10) << ss.items.sr_no << "|" << left << setw(40) << ss.items.name << "|" << left << setw(20) << ss.items.code << "|"
                     << "\n";

                /*cout << "\t\t\t\t\t\t\t"
                     << "Sr. No. :- " << ss.items.sr_no << endl;
                cout << "\t\t\t\t\t\t\t"
                     << "Product Name :- " << ss.items.name << endl;
                cout << "\t\t\t\t\t\t\t"
                     << "Product Code :- " << ss.items.code << endl
                     << endl;*/

                items++;
            }
        }
        file2.close();
        if (items > 0)
        {
            cout << "\n\n\t\t\t\t\t\t\tEnter number of items to be ordered :- ";

            int n;
            cin >> n;

            for (int i = 0; i < n; i++)
            {
                fstream file2(state_name);
                if (n_items == 0)
                {
                    cout << "\n\t\t\t\t\t\t\tNo items present" << endl;
                    break;
                }

                int p_code;
                cout << "\n\t\t\t\t\t\t\tEnter product code of the product:- ";

                cin >> p_code;

                fstream file3("s1.txt", ios::app);

                file2.seekg(0, ios::beg);
                for (int j = 0; j < n_items; j++)
                {
                    file2.read((char *)&ss, sizeof(ss));
                    if (p_code == ss.items.code)
                    {
                        cout << "\t\t\t\t\t\t\tEnter Quantity :- ";

                        int quantity;
                        cin >> quantity;

                        ss.items.order_quantity = quantity;
                        ss.o = 1;

                        cout << "\n\n\t\t\t\t\t\t\tOrder Placed Successfully";
                    }
                    file3.write((char *)&ss, sizeof(ss));
                }
                file3.close();
                file2.close();

                remove(state_name);
                rename("s1.txt", state_name);
            }
        }
    }

    //Option 4
    //Receive Order
    else if (option == 4)
    {
        fstream file2(state_name);

        st state1;

        file2.seekg(0, ios::end);
        int file_size = file2.tellg();
        int n_items = file_size / sizeof(state1);

        file2.seekg(0, ios::beg);
        fstream file3("oc.txt", ios::app);

        for (int i = 0; i < n_items; i++)
        {

            file2.read((char *)&state1, sizeof(state1));

            if (state1.o == 2)
            {
                cout << "\t\t\t\t\t" << left << setw(10) << state1.items.sr_no << left << setw(30) << state1.items.name << left << setw(20) << state1.items.order_quantity << endl;

                cout << "\n\t\t\t\t\t\t\tDo you want to Recieve this order now? Y/N :- ";

                char C;
                cin >> C;

                if (C == 'Y')
                {
                    state1.o = 0;
                    state1.items.quantity = state1.items.quantity + state1.items.order_quantity;
                    state1.items.order_quantity = 0;

                    cout << "\n\n\t\t\t\t\t\t\tOrder Recieved Successfully\n";
                }
            }

            file3.write((char *)&state1, sizeof(state1));
        }
        file2.close();
        file3.close();

        remove(state_name);
        rename("oc.txt", state_name);
    }

    //Option 5
    //Add Hospital
    else if (option == 5)
    {
        hos h;
        fstream fp2("hospitals.txt");

        fp2.seekg(0, ios::end);
        int n = fp2.tellg() / sizeof(h);
        fp2.seekg(0, ios::beg);

        int q[4] = {0, 0, 0, 0};

        for (int i = 0; i < n; i++)
        {
            fp2.read((char *)&h, sizeof(h));

            if (strcmp(h.r_name, "North") == 0)
            {
                q[0]++;
            }
            if (strcmp(h.r_name, "South") == 0)
            {
                q[1]++;
            }
            if (strcmp(h.r_name, "East") == 0)
            {
                q[2]++;
            }
            if (strcmp(h.r_name, "West") == 0)
            {
                q[3]++;
            }
        }

        fp2.close();

        fstream fp1("hospitals.txt", ios::app);

        cout << "\t\t\t\t\t\t\t 1.North \n\t\t\t\t\t\t\t 2.South \n\t\t\t\t\t\t\t 3.East \n\t\t\t\t\t\t\t 4.West \n ";

    restart:

        cout << "\n\n\t\t\t\t\t\t\tSelect the region of hospitals you want to add :- ";

        int r;
        cin >> r;

        char r_n[4];

        if (r == 1)
        {
            strcpy(h.r_name, "North");
            strcpy(r_n, "-N-");
        }
        else if (r == 2)
        {
            strcpy(h.r_name, "South");
            strcpy(r_n, "-S-");
        }
        else if (r == 3)
        {
            strcpy(h.r_name, "East");
            strcpy(r_n, "-E-");
        }
        else if (r == 4)
        {
            strcpy(h.r_name, "West");
            strcpy(r_n, "-W-");
        }
        else
        {
            cout << "\n\t\t\t\t\t\t\tWrong input. Try again!!";

            goto restart;
        }

        cout << "\t\t\t\t\t\t\tEnter number of hospitals you want to add in above mentioned region :- ";

        int n_hos;
        cin >> n_hos;

        for (int i = 0; i < n_hos; i++)
        {

            cout << "\t\t\t\t\t\t\tSr. no :- " << q[r - 1] + 1 << endl;
            cout << "\t\t\t\t\t\t\tHospital Name :- ";

            cin >> h.h_name;
            int a = q[r - 1] + 1;

            stringstream w;
            w << a;
            char x[10];
            w >> x;

            char str[20];
            strcpy(str, s1_name);
            strcat(str, r_n);
            strcat(str, x);

            strcpy(h.h_id, str);

            q[r - 1]++;

            strcpy(h.s_name, s_name);
            char pass[30] = "FEASO_";
            strcat(pass, h.h_name);
            strcpy(h.h_pass, pass);

            fp1.write((char *)&h, sizeof(h));

            char f_name[20];

            strcpy(f_name, h.h_name);
            strcat(f_name, ".txt");

            ofstream S1(f_name);
            fstream temp_h("temp_h.txt");

            if (temp_h && S1)
            {
                string line;
                while (getline(temp_h, line))
                {
                    S1 << line;
                }

                S1.close();
                temp_h.close();
            }

            cout << endl
                 << endl
                 << "\t\t\t\t\t\t\tYour Id Generated for hospital " << h.h_name << " is :- " << h.h_id << endl;
            cout << "\t\t\t\t\t\t\tPassword is :- " << h.h_pass << endl;
        }
    }

    //Option 6
    //Display Hospital
    else if (option == 6)
    {
        fstream fp1(s_name);
        hos h;

        fp1.seekg(0, ios::end);
        int n = fp1.tellg() / sizeof(h);
        fp1.seekg(0, ios::beg);

        int q = 1;

        // stringstream w;
        // w >> q;
        // char x[10];
        // w << x;

        // char str[20];
        // strcpy(str, s_name);
        // strcat(str, "0N");
        // strcat(str, x);

        cout << "\t\t\t\t\t\t\tNorth \n";

        for (int i = 0; i < n; i++)
        {
            fp1.read((char *)&h, sizeof(h));

            if (strcmp(h.r_name, "North") == 0)
            {

                cout << "\t\t\t\t\t\t\tSr. no :- " << q << endl;
                cout << "\t\t\t\t\t\t\tHospital Name :- ";
                cout << h.h_name << endl;
                q++;
            }
            if (i == n - 1 && q == 1)
            {
                cout << "\t\t\t\t\t\t\tNo Hospitals\n";
            }
        }

        fp1.seekg(0, ios::beg);

        q = 1;

        cout << "\t\t\t\t\t\t\tSouth \n";

        for (int i = 0; i < n; i++)
        {
            fp1.read((char *)&h, sizeof(h));

            if (strcmp(h.r_name, "South") == 0)
            {

                cout << "\t\t\t\t\t\t\tSr. no :- " << q << endl;
                cout << "\t\t\t\t\t\t\tHospital Name :- ";
                cout << h.h_name << endl;
                q++;
            }
            if (i == n - 1 && q == 1)
            {
                cout << "\t\t\t\t\t\t\tNo Hospitals\n";
            }
        }

        fp1.seekg(0, ios::beg);

        q = 1;

        cout << "\t\t\t\t\t\t\tEast \n";

        for (int i = 0; i < n; i++)
        {
            fp1.read((char *)&h, sizeof(h));

            if (strcmp(h.r_name, "East") == 0)
            {

                cout << "\t\t\t\t\t\t\tSr. no :- " << q << endl;
                cout << "\t\t\t\t\t\t\tHospital Name :- ";
                cout << h.h_name << endl;
                q++;
            }
            if (i == n - 1 && q == 1)
            {
                cout << "\t\t\t\t\t\t\tNo Hospitals\n";
            }
        }

        fp1.seekg(0, ios::beg);

        q = 1;

        cout << "\t\t\t\t\t\t\tWest \n";

        for (int i = 0; i < n; i++)
        {
            fp1.read((char *)&h, sizeof(h));

            if (strcmp(h.r_name, "West") == 0)
            {

                cout << "\t\t\t\t\t\t\tSr. no :- " << q << endl;
                cout << "\t\t\t\t\t\t\tHospital Name :- ";
                cout << "\t\t\t\t\t\t\t" << h.h_name << endl;

                q++;
            }
            if (i == n - 1 && q == 1)
            {
                cout << "\t\t\t\t\t\t\tNo Hospitals\n";
            }
        }

        fp1.close();
    }

    //Option 7
    //GOTO Login page
    else if (option == 7)
    {

        system("cls");
        main();

        return 0;
    }

    //Option 8
    //Exit
    else if (option == 8)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }

    //Default Option
    else
    {
        system("cls");

        cout << "\t\t\t\t\t\t\tWrong Entry Try again!!\n";
        Sleep(2000);

        system("cls");

        goto menu;
    }

menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :-" << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MAIN MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");
        goto menu;

        return 0;
    }
    else if (option2 == 2)
    {

        system("cls");
        main();

        return 0;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t"
             << "Wrong Entry \nTry again!";

        Sleep(2000);

        system("cls");
        goto menu2;
    }
    return 0;
}

//Function for Region
int region()
{
menu:

    fstream file("hospitals.txt");
    hos h;

    file.seekg(0, ios::end);
    int n = file.tellg() / sizeof(h);
    file.seekg(0, ios::beg);

    cout << "\n\n\n\n\t\t\t\t\t\t\tEnter the State Name:- ";

    char state[30];
    cin >> state;

    system("cls");
    system("Color 06");
    cout << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tState Name :- " << state << endl;

    int k = 1;

    cout << "\n\n\t\t\t\t\t\t\tNorth Region:-\n";

    for (int i = 0; i < n; i++)
    {
        file.read((char *)&h, sizeof(h));

        if (strcmp(state, h.s_name) == 0 && strcmp("North", h.r_name) == 0)
        {
            cout << "\t\t\t\t\t\t\t" << left << setw(10) << k << left << setw(30) << h.h_name << endl;
            k++;
        }
    }
    if (k == 1)
    {
        cout << "\t\t\t\t\t\t\tNo Hospitals" << endl;
    }

    cout << "\n\n\t\t\t\t\t\t\tSouth Region:-\n";

    k = 1;

    file.seekg(0, ios::beg);

    for (int i = 0; i < n; i++)
    {
        file.read((char *)&h, sizeof(h));

        if (strcmp(state, h.s_name) == 0 && strcmp("South", h.r_name) == 0)
        {
            cout << "\t\t\t\t\t\t\t" << left << setw(10) << k << left << setw(30) << h.h_name << endl;
            k++;
        }
    }
    if (k == 1)
    {
        cout << "\t\t\t\t\t\t\tNo Hospitals" << endl;
    }
    cout << "\n\n\t\t\t\t\t\t\tEast Region:-\n";

    k = 1;

    file.seekg(0, ios::beg);

    for (int i = 0; i < n; i++)
    {
        file.read((char *)&h, sizeof(h));

        if (strcmp(state, h.s_name) == 0 && strcmp("East", h.r_name) == 0)
        {
            cout << "\t\t\t\t\t\t\t" << left << setw(10) << k << left << setw(30) << h.h_name << endl;
            k++;
        }
    }
    if (k == 1)
    {
        cout << "\t\t\t\t\t\t\tNo Hospitals" << endl;
    }

    cout << "\n\n\t\t\t\t\t\t\tWest Region:-\n";

    k = 1;

    file.seekg(0, ios::beg);

    for (int i = 0; i < n; i++)
    {
        file.read((char *)&h, sizeof(h));
        if (strcmp(state, h.s_name) == 0 && strcmp("West", h.r_name) == 0)
        {
            cout << "\t\t\t\t\t\t\t" << left << setw(10) << k << left << setw(30) << h.h_name << endl;
            k++;
        }
    }
    if (k == 1)
    {
        cout << "\t\t\t\t\t\t\tNo Hospitals" << endl;
    }

menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :- " << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");
        goto menu;

        return 0;
    }
    else if (option2 == 2)
    {
        system("cls");
        main();

        return 0;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");
        cout << "\t\t\t\t\t\t\tWrong Entry \nTry again!";

        Sleep(2000);
        system("cls");

        goto menu2;
    }
}

//Function for Hospital
int hospital(char *ID)
{
    system("Color 06");
menu:

    int keydec = 0;
    hos current_hos;

    char id[20];
    char name[20];
    strcpy(id, ID);

    int k = 0;

    fstream file("hospitals.txt");

    for (int i = 0; !file.eof(); i++)
    {
        file.read((char *)&current_hos, sizeof(current_hos));
        if (strcmp(current_hos.h_id, id) == 0)
        {
            k = 1;
            break;
        }
    }
    if (k == 0)
    {
        return 0;
    }

    cout << "\n\n\t\t\t\t\t\t\tWelcome to " << current_hos.h_name << " Hospital" << endl
         << endl
         << endl;
    strcpy(name, current_hos.h_name);
    strcat(name, ".txt");

    cout << "\t\t\t\t\t\t\tSelect an appropriate option\n\n\n";
    cout << "\t\t\t\t \t\t\t1.Display Stocks" << endl
         << "\t\t\t\t \t\t\t2.Place Order" << endl
         << "\t\t\t\t \t\t\t3.Recieve Order " << endl
         << "\t\t\t\t \t\t\t4.Goto Login Page" << endl
         << "\t\t\t\t \t\t\t5.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tEnter the required option:- ";

    int option;
    cin >> option;

    system("cls");
    cout << endl
         << endl;

    //Option 1
    //Display Stocks
    if (option == 1)
    {
        hos h;
        fstream file1(name);

        file1.seekg(0, ios::end);
        int n_i = file1.tellg() / sizeof(h);
        file1.seekg(0, ios::beg);

        for (int i = 0; i < n_i; i++)
        {
            if (keydec == 0)
            {
                cout << "\t\t\t\t\t\t\t" << left
                     << setw(10) << "Ref. No."
                     << "|" << left << setw(25) << "Product Name"
                     << "|" << left << setw(15) << "Quantity"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t\t\t"
                     << "----------|-------------------------|---------------|";
                cout << "\t\t\t\t\t\t\t"
                     << "\n";
            }
            keydec++;

            file1.read((char *)&h, sizeof(h));

            cout << "\t\t\t\t\t\t\t" << left
                 << setw(10) << h.items.sr_no << "|" << left << setw(25) << h.items.name << "|" << left << setw(15) << h.items.quantity << "|"
                 << "\n";
        }
    }

    //Option2
    //Place Order
    else if (option == 2)
    {
        hos h;
        fstream file1(name);

        file1.seekg(0, ios::end);
        int n_i = file1.tellg() / sizeof(h);
        file1.seekg(0, ios::beg);

        for (int i = 0; i < n_i; i++)
        {
            if (keydec == 0)
            {
                cout << "\t\t\t\t\t\t\t" << left
                     << setw(10) << "Ref. No."
                     << "|" << left << setw(25) << "Product Name"
                     << "|" << left << setw(15) << "Quantity"
                     << "|"
                     << "\n";
                cout << "\t\t\t\t\t\t\t"
                     << "----------|-------------------------|---------------|";
                cout << "\t\t\t\t\t\t\t"
                     << "\n";
            }
            keydec++;
            file1.read((char *)&h, sizeof(h));
            cout << "\t\t\t\t\t\t\t" << left
                 << setw(10) << h.items.sr_no << "|" << left << setw(25) << h.items.name << "|" << left << setw(15) << h.items.quantity << "|"
                 << "\n";
        }

        fstream file3("order_h.txt", ios::app);
        int n;

        cout << "\n\t\t\t\t\t\t\tEnter number of items to be ordered :- ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "\n\t\t\t\t\t\t\tEnter the refrence number of product :- ";

            int x;
            cin >> x;

            file1.seekg(0, ios::beg);

            for (int j = 0; j < n_i; j++)
            {
                file1.read((char *)&h, sizeof(h));
                if (x == h.items.sr_no)
                {
                    cout << "\n\t\t\t\t\t\t\tProduct Name :- " << h.items.name << endl;

                    cout << "\t\t\t\t\t\t\tEnter quantity :- ";
                    cin >> h.items.order_quantity;

                    strcpy(h.s_name, current_hos.s_name);
                    strcpy(h.r_name, current_hos.r_name);
                    strcpy(h.h_name, current_hos.h_name);

                    file3.write((char *)&h, sizeof(h));

                    cout << "\n\n\t\t\t\t\t\t\tOrder Placed Successfully\n";
                }
            }
        }

        file3.close();
        file1.close();
    }

    //Option 3
    //Receive Order
    else if (option == 3)
    {
        hos h;
        fstream file4("order_h.txt");

        file4.seekg(0, ios::end);
        int n_o = file4.tellg() / sizeof(current_hos);
        file4.seekg(0, ios::beg);

        fstream temp2("temp2.txt", ios::app);
        cout << endl
             << endl;

        for (int i = 0; i < n_o; i++)
        {
            file4.read((char *)&h, sizeof(h));
            if (strcmp(current_hos.s_name, h.s_name) == 0 && strcmp(current_hos.r_name, h.r_name) == 0 && h.o == 1 && strcmp(current_hos.h_name, h.h_name) == 0)
            {
                cout << "\t\t\t\t\t\t\t" << left << setw(30) << h.items.name << left << setw(20) << h.items.order_quantity << endl;

                cout << "\n\t\t\t\t\t\t\tDo you want to recieve this order ? Y/N :- ";

                char c;
                cin >> c;

                if (c == 'Y')
                {
                    hos h1;

                    fstream s(name);
                    fstream temp1("temp1.txt", ios::app);

                    s.seekg(0, ios::end);
                    int n_i = s.tellg() / sizeof(h1);
                    s.seekg(0, ios::beg);

                    for (int j = 0; j < n_i; j++)
                    {
                        s.read((char *)&h1, sizeof(h1));
                        if (strcmp(h1.items.name, h.items.name) == 0)
                        {
                            h1.items.quantity = h1.items.quantity + h.items.order_quantity;

                            cout << endl
                                 << endl
                                 << endl
                                 << "\t\t\t\t\t\t\tOrder Recieved Successfully" << endl;
                        }
                        temp1.write((char *)&h1, sizeof(h1));
                    }

                    temp1.close();
                    s.close();

                    remove(name);
                    rename("temp1.txt", name);

                    continue;
                }
            }
            temp2.write((char *)&h, sizeof(h));
        }
        temp2.close();
        file4.close();

        remove("order_h.txt");
        rename("temp2.txt", "order_h.txt");
    }

    //Option 4
    //GOTO Login Page
    else if (option == 4)
    {
        system("cls");
        main();

        return 0;
    }
    else if (option == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t\tWrong Entry \nTry again!";

        Sleep(2000);
        system("cls");

        goto menu;
    }

menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :- " << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");
        goto menu;

        return 0;
    }
    else if (option2 == 2)
    {

        system("cls");
        main();

        return 0;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    else
    {
        system("cls");
        cout << "\t\t\t\t\t\t\tWrong Entry \nTry again!";

        Sleep(2000);
        system("cls");

        goto menu2;
    }
}

//Function for Wholesaler
void w_saler(char *name, char *id, int rating)
{
    system("Color 06");
menu:

    char sr_no[30];
    strcpy(sr_no, id);

    system("cls");

    int option;
    cout << endl
         << "\t\t\t\t\t\t Welcome " << name << " to quotation portal" << endl;
    cout << "\t\t\t\t\t\t\t"
         << "Your Rating is :- " << rating << endl;
    cout << "\t\t\t\t\t\t\t"
         << "Select an appropriate option" << endl
         << endl
         << endl;
    cout << "\t\t\t\t \t\t\t1.To add your quotation" << endl
         << "\t\t\t\t \t\t\t2.Status of quotation" << endl
         << "\t\t\t\t \t\t\t3.Dispatch Order" << endl
         << "\t\t\t\t \t\t\t4.Goto Login Page" << endl
         << "\t\t\t\t \t\t\t5.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tEnter the required option:- ";
    cin >> option;

    system("cls");
    cout << endl
         << endl;

    //Option 1
    //Add Quotation
    if (option == 1)
    {
        fstream file1("order.txt");
        order odr;

        file1.seekg(0, ios::end);
        int file_size = file1.tellg();
        int n_items = file_size / sizeof(odr);

        file1.seekg(0, ios::beg);

        cout << "\t\t\t\t\t\t\t"
             << left << setw(10)
             << "Sr. No."
             << left << setw(30)
             << "Name"
             << left << setw(20)
             << "Quantity" << endl;

        for (int i = 1; i <= n_items; i++)
        {
            file1.read((char *)&odr, sizeof(odr));
            cout << "\t\t\t\t\t\t\t" << left << setw(10) << i << left << setw(30) << odr.name << left << setw(20) << odr.quantity << endl;
        }

        cout << "\n\t\t\t\t\t\t\tIf you can fullfill all the order then only fill the form!!!" << endl;

        cout << "\t\t\t\t\t\t\tEnter the number of items you can supply :- ";

        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "\t\t\t\t\t\t\tEnter the serial number of product :- ";

            int a;
            cin >> a;

            file1.seekg(0, ios::beg);

            for (int j = 1; j <= n_items; j++)
            {
                file1.read((char *)&odr, sizeof(odr));

                if (a == j)
                {
                    wholesaler rt;

                    cout << "\t\t\t\t\t\t\tProduct Name :- " << odr.name << endl;

                    strcpy(rt.items.name, odr.name);
                    // cout << "\t\t\t\t\t\t\t" << "enter quantity :- ";
                    // cin >> rt.items.quantity;

                    cout << "\t\t\t\t\t\t\tEnter price of one piece :- ";
                    int price_of_one;
                    cin >> price_of_one;
                    int price = price_of_one * odr.quantity;

                    cout << "\t\t\t\t\t\t\tPercentage discount you will give :- ";
                    int discount;
                    cin >> discount;
                    price = price - (price * discount / 100);
                    cout << "\t\t\t\t\t\t\tTotal :- " << price << endl;
                    rt.price = price;

                    strcpy(rt.r_id, sr_no);
                    rt.items.sr_no = odr.sr_no;
                    rt.items.quantity = odr.quantity;

                    fstream file2("application_from_retailor.txt", ios ::app);

                    file2.write((char *)&rt, sizeof(rt));
                    file2.close();

                    cout << endl
                         << endl
                         << endl
                         << "\t\t\t\t\t\t\tQuotation Added Successfully" << endl;
                }
            }
        }

        file1.close();
    }

    //Option 2
    //Status Of Quotation
    else if (option == 2)
    {
        wholesaler rt;
        fstream file1("status.txt");

        int count = 0;

        file1.seekg(0, ios::end);
        int n = file1.tellg() / sizeof(rt);
        file1.seekg(0, ios::beg);

        for (int i = 1; i <= n; i++)
        {
            file1.read((char *)&rt, sizeof(rt));
            if (strcmp(sr_no, rt.r_id) == 0 && count == 0 && rt.cofirmation == 0)
            {
                cout << endl
                     << "\t\t\t\t\t\t\tYour quotation for following items is selected :- " << endl
                     << endl;
                cout << "\t\t\t\t\t\t\t" << left << setw(10)
                     << "Sr. No." << left << setw(30) << "Product Name" << left << setw(20) << "Quantity" << endl;
            }

            if (strcmp(sr_no, rt.r_id) == 0 && rt.cofirmation == 0)
            {
                cout << "\t\t\t\t\t\t\t" << left << setw(10) << i << left << setw(30) << rt.items.name << left << setw(20) << rt.items.quantity << endl;
                count++;
            }
        }

        if (count == 0)
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t\t\tNo order is pending" << endl;
        }
        file1.close();
    }

    //Option 3
    //Dispatch Order
    else if (option == 3)
    {
        wholesaler rt;
        fstream file1("status.txt");

        int count = 0;

        file1.seekg(0, ios::end);
        int n = file1.tellg() / sizeof(rt);

        file1.seekg(0, ios::beg);

        for (int i = 1; i <= n; i++)
        {
            file1.read((char *)&rt, sizeof(rt));
            if (strcmp(sr_no, rt.r_id) == 0 && count == 0 && rt.cofirmation == 0)
            {
                cout << "\n\t\t\t\t\t\t\tYour quotation for following items is selected :- " << endl
                     << endl;
                cout << "\t\t\t\t\t\t\t" << left << setw(10)
                     << "Sr. No." << left << setw(30) << "Product Name" << left << setw(20) << "Quantity" << endl;
            }

            if (strcmp(sr_no, rt.r_id) == 0 && rt.cofirmation == 0)
            {
                cout << "\t\t\t\t\t\t\t" << left << setw(10) << i << left << setw(30) << rt.items.name << left << setw(20) << rt.items.quantity << endl;
                count++;
            }
        }

        if (count == 0)
        {
            cout << "\n\t\t\t\t\t\t\tNo Order to Dispatch";
            file1.close();
            Sleep(1500);
            goto menu;
        }

        cout << "\t\t\t\t\t\t\tEnter the number of orders you want to dispatch :- ";

        int q;
        cin >> q;

        fstream temp("temp.txt", ios::app);
        file1.seekg(0, ios::beg);

        for (int i = 0; i < q; i++)
        {
            file1.read((char *)&rt, sizeof(rt));
            cout << "\n\t\t\t\t\t\t\tEnter the Sr. No. of the order you want to dispatch :- ";

            int s_no;
            cin >> s_no;

            for (int j = 1; j <= n; j++)
            {
                if (strcmp(sr_no, rt.r_id) == 0 && rt.cofirmation == 0 && s_no == j)
                {
                    cout << endl
                         << "\t\t\t\t\t\t\tProduct :-" << rt.items.name << " with Quantity :- " << rt.items.quantity << " Dispatched" << endl;

                    rt.cofirmation = 1;
                }
            }

            temp.write((char *)&rt, sizeof(rt));
        }

        file1.close();
        temp.close();

        remove("status.txt");
        rename("temp.txt", "status.txt");
    }

    //Option 4
    //GOTO Login Page
    else if (option == 4)
    {

        system("cls");
        main();
        return;
    }

    //Option 5
    //Exit
    else if (option == 5)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return;
    }

    //Default Option
    else
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t"
             << "Wrong Entry \nTry again!";

        Sleep(2000);
        system("cls");

        goto menu;
    }

menu2:
    cout << endl
         << endl
         << endl
         << endl
         << "\t\t\t\t\t\t\tSelect The Appropriate option :- " << endl;
    cout << "\t\t\t\t \t\t\t1.BACK TO MENU" << endl
         << "\t\t\t\t \t\t\t2.GOTO LOGIN PAGE" << endl
         << "\t\t\t\t \t\t\t3.EXIT" << endl
         << endl
         << "\t\t\t\t\t\t\tENTER YOUR CHOICE :- ";

    int option2;
    cin >> option2;

    if (option2 == 1)
    {
        system("cls");
        goto menu;

        return;
    }
    else if (option2 == 2)
    {

        system("cls");
        main();
        return;
    }
    else if (option2 == 3)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return;
    }
    else
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t\tWrong Entry \nTry again!";

        Sleep(2000);
        system("cls");

        goto menu2;
    }
}

//Main Function
int main()
{
    system("cls");
    system("Color 4E");

    cout << "\n\t\t\t\t\t   ----------------------------------------------------------------------- \n";
    cout << "\t\t\t\t\t  |                                                                       |\n";
    cout << "\t\t\t\t\t  |                                                                       |\n";
    cout << "\t\t\t\t\t  |  OOOOOO   OOOOOO OOOOOO OOOOOO OOOOOO OOOOOO O    O OOOOOOO  OOOOOO   |\n";
    cout << "\t\t\t\t\t  |  O        O    O O      O        O      O    O O  O O        O        |\n";
    cout << "\t\t\t\t\t  |  O  OOOOO OOOOOO OOOOO  OOOOO    O      O    O  O O O  OOOOO OOOOOO   |\n";
    cout << "\t\t\t\t\t  |  O    O   O  O   O      O        O      O    O   OO O    O        O   |\n";
    cout << "\t\t\t\t\t  |  OOOOOO   O   O  OOOOOO OOOOOO   O    OOOOOO O    O OOOOOOO  OOOOOO   |\n";
    cout << "\t\t\t\t\t  |                                                                       |\n";
    cout << "\t\t\t\t\t   ----------------------------------------------------------------------- \n";
    cout << "\t\t\t\t\t\t\t*************************************************\n";
    cout << "\t\t\t\t\t\t\t*       -----------------------------           *\n";
    cout << "\t\t\t\t\t\t\t*            WELCOME TO FEASOMED                *\n";
    cout << "\t\t\t\t\t\t\t*       -----------------------------           *\n";
    cout << "\t\t\t\t\t\t\t*************************************************\n\n";

    //system("Color 40");

    cout << "\n\t\t\t\t\t\t\tLOGIN AS :-" << endl
         << endl
         << "\t\t\t\t\t\t\t1.ADMIN\n"
         << endl
         << "\t\t\t\t\t\t\t2.MAIN STORAGE\n"
         << endl
         << "\t\t\t\t\t\t\t3.STATE\n"
         << endl
         << "\t\t\t\t\t\t\t4.REGION\n"
         << endl
         << "\t\t\t\t\t\t\t5.HOSPITAL\n"
         << endl
         << "\t\t\t\t\t\t\t6.WHOLESALER\n"
         << endl
         << "\t\t\t\t\t\t\t7.CLOSE APPLICATION\n"
         << endl
         << endl
         << "\t\t\t\t\t\t\tENTER THE NUMBER OF YOUR DESIGNATION : -";

    int login;

    cin >> login;

    system("cls");
    system("Color 16");

    //Option 1
    //Admin Option
    if (login == 1)
    {
        //Login ID and Password Admin
        Login pass("Ladmin", "Padmin");

        system("cls");

    admin:
        char a[30];
        char b[30];

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tEnter Login Id :- ";
        cin >> a;

        cout << endl
             << "\t\t\t\t\t\t\tEnter Password :- ";
        char c;

        for (int i = 0; i < 30; i++)
        {
            c = getch();
            if (c == 13)
            {
                b[i] = '\0';
                break;
            }
            b[i] = c;
            cout << '*';
        }

        if (pass.check(a, b))
        {
            system("cls");
            admin();
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t Login ID or password is incorrect ! Try Again " << endl
                 << endl;
            goto admin;
        }
    }

    //Option 2
    //Main Storage Option
    else if (login == 2)
    {
        //Login ID and Password Main Storage
        Login lmain("Lmain", "Pmain");

        system("cls");

    m_s:
        char a[30];
        char b[30];

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tEnter Login Id :- ";
        cin >> a;

        cout << endl
             << "\t\t\t\t\t\t\tEnter Password :- ";

        char c;

        for (int i = 0; i < 30; i++)
        {
            c = getch();
            if (c == 13)
            {
                b[i] = '\0';
                break;
            }
            b[i] = c;
            cout << '*';
        }

        if (lmain.check(a, b))
        {
            system("cls");
            main_storage();
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t Login ID or password is incorrect ! Try Again\n\n";
            goto m_s;
        }
    }

    //Option 3
    //State Option
    else if (login == 3)
    {
        system("cls");

    s_s:
        char login1[30];
        char name[30];
        char pass1[30];
        char pass2[30];

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tEnter Login Id :- ";
        cin >> login1;

        fstream file("states.txt");
        st st1;

        file.seekg(0, ios::end);

        int n = file.tellg() / sizeof(st1);

        file.seekg(0, ios::beg);

        for (int i = 0; i < n; i++)
        {
            file.read((char *)&st1, sizeof(st1));

            if (strcmp(st1.s_id, login1) == 0)
            {
                strcpy(pass1, st1.s_pass);
                strcpy(name, st1.s_name);
                break;
            }
        }

        Login lstate(login1, pass1);
        cout << endl
             << "\t\t\t\t\t\t\tEnter Password :- ";

        char c;

        for (int i = 0; i < 30; i++)
        {
            c = getch();
            if (c == 13)
            {
                pass2[i] = '\0';
                break;
            }
            pass2[i] = c;
            cout << '*';
        }

        if (lstate.check(login1, pass2))
        {
            system("cls");
            state(name);
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t Login ID or password is incorrect ! Try Again" << endl
                 << endl;

            goto s_s;
        }
    }

    //Option 4
    //Region Option
    else if (login == 4)
    {
        system("cls");

        region();
    }

    //Option 5
    //Hospital Option
    else if (login == 5)
    {
        system("cls");

    h_s:
        char login1[30];
        char name[30];
        char pass1[30];
        char pass2[30];

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tEnter Login Id :- ";

        cin >> login1;

        fstream file("hospitals.txt");
        hos h1;

        file.seekg(0, ios::end);

        int n = file.tellg() / sizeof(h1);

        file.seekg(0, ios::beg);

        for (int i = 0; i < n; i++)
        {
            file.read((char *)&h1, sizeof(h1));

            if (strcmp(h1.h_id, login1) == 0)
            {
                strcpy(pass1, h1.h_pass);
                strcpy(name, h1.h_name);
                break;
            }
        }

        Login lhos(login1, pass1);

        cout << endl
             << "\t\t\t\t\t\t\tEnter Password :- ";

        char c;

        for (int i = 0; i < 30; i++)
        {
            c = getch();
            if (c == 13)
            {
                pass2[i] = '\0';
                break;
            }
            pass2[i] = c;
            cout << '*';
        }

        if (lhos.check(login1, pass2))
        {
            system("cls");
            hospital(login1);
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t Login ID or password is incorrect ! Try Again" << endl
                 << endl;

            goto h_s;
        }
    }

    //Option 6
    //Wholesaler Option
    else if (login == 6)
    {
        system("cls");

    h_w:
        char login1[30];
        char name[30];
        char pass1[30];
        char pass2[30];

        cout << endl
             << endl
             << endl
             << "\t\t\t\t\t\t\tEnter Login Id :- ";

        cin >> login1;

        fstream file("wholesaler.txt");
        wholesaler h1;

        file.seekg(0, ios::end);

        int n = file.tellg() / sizeof(h1);

        file.seekg(0, ios::beg);

        int rating;

        for (int i = 0; i < n; i++)
        {
            file.read((char *)&h1, sizeof(h1));

            if (strcmp(h1.r_id, login1) == 0)
            {
                strcpy(pass1, h1.r_pass);
                strcpy(name, h1.name);
                rating = h1.rating;
                break;
            }
        }

        Login lwh(login1, pass1);
        cout << endl
             << "\t\t\t\t\t\t\tEnter Password :- ";
        char c;

        for (int i = 0; i < 30; i++)
        {
            c = getch();
            if (c == 13)
            {
                pass2[i] = '\0';
                break;
            }
            pass2[i] = c;
            cout << '*';
        }

        if (lwh.check(login1, pass2))
        {
            system("cls");
            w_saler(name, login1, rating);
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t Login ID or password is incorrect ! Try Again" << endl
                 << endl;

            goto h_w;
        }
    }
    //Option 7
    //Close Application
    else if (login == 7)
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThanks For Using" << endl;
        cout << "\t\t\t\t\t\t\tPress Enter to exit" << endl;
        getch();
        return 0;
    }
    //Default Option
    else
    {
        cout << endl
             << endl
             << "\t\t\t\t\t\t\tEnter a valid option" << endl
             << endl;

        main();
    }

    return 0;
}

//End of Code
