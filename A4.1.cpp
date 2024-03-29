#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int ave_con_per_person = 200;
const int ave_con_per_squ = 9;
const int Heater = 550;
// 10 global integer
const int global_column = 35;

// 1 enum
enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    weekly
};

// 2 input_use
void input_use(string name, Use &use)
{
    cout << name;
    char ch;
    cin >> ch;
    switch (ch)
    {
    case 'd':
        use = daily;
        break;
    case 'm':
        use = mo_fr;
        break;
    case 'o':
        use = once;
        break;
    case 's':
        use = sa_su;
        break;
    case 'w':
        use = weekly;
        break;
    default:
        cout << "Please enter a valid option  d, m, o, s, or w\n";
    }
}
// A3 function
ostream &operator<<(ostream &out, const Use &use)
{
    switch (use)
    {
    case once:
        out << "once";
        break;
    case daily:
        out << "daily";
        break;
    case mo_fr:
        out << "Monday to Friday";
        break;
    case sa_su:
        out << "Saturday and Sunday";
        break;
    case weekly:
        out << "weekly";
        break;
    }
    return out;
}

// 3 consumer structure
struct consumer
{
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    consumer *next;
};

// 4 Pointer in List

struct household
{
    string Name_of_city;
    int number_of_sq;
    int number_of_person;
    consumer *consumer_Head;
    bool heater;
    float Power_price;
    string Power_supplier;
};

// 5 add consumer to household

void add_consumer_to_household(household *Hous_Hold, consumer *Consumer)
{
    Consumer->next = Hous_Hold->consumer_Head;
    Hous_Hold->consumer_Head = Consumer;
}

// 6 annual hours of use

float annual_hours_of_use(consumer *consumer)
{
    switch (consumer->use)
    {
    case once:
        return consumer->hours;
    case daily:
        return consumer->hours * 365;
    case mo_fr:
        return consumer->hours * 260;
    case sa_su:
        return consumer->hours * 104;
    case weekly:
        return consumer->hours * 52;
    default:
        return 0;
    }
}

// 7 annual_hours_of_standby
float annual_hours_of_standby(consumer *Con)
{
    float annual_hours_standby = ((365 * 24) - annual_hours_of_use(Con));
    return annual_hours_standby;
}

// 8 annual kwh

float annual_kWh(consumer *Cout)
{
    float annual_KWH = (((annual_hours_of_use(Cout) * Cout->watt) + (annual_hours_of_standby(Cout) * Cout->watt_standby)) / 1000);
    return annual_KWH;
}
// 9 move_up

consumer *move_up(consumer *Current_Head, int k)
{
    if (k <= 1)
    {
        return Current_Head;
    }

    consumer *current = Current_Head;
    consumer *kNode = current->next;

    if (k == 2 && kNode != nullptr)
    {
        current->next = kNode->next;
        kNode->next = Current_Head;
        Current_Head = kNode;
        return Current_Head;
    }
    else
    {
        for (int i = 1; i < k - 2; i++)
        {
            if (current->next == nullptr)
            {
                return Current_Head;
            }
            current = current->next;
        }
        consumer *Kth_Node = current->next->next;
        current->next->next = Kth_Node->next;
        Kth_Node->next = current->next;
        current->next = Kth_Node;
        return Current_Head;
    }
}

// 11 print_consumer

void print_consumer(consumer *Print_consumer, int no_of_consumer)
{
    cout << right << setw(global_column) << no_of_consumer << ": " << left << Print_consumer->description << " (at address: " << Print_consumer << " )\n"; // extension 1
    cout << right << setw(global_column) << "power consumption"
         << ": " << left << Print_consumer->watt << " w\n";
    cout << right << setw(global_column) << "power consumption standby"
         << ": " << left << Print_consumer->watt_standby << " w\n";
    cout << right << setw(global_column) << "annual hours of use"
         << ": " << left << annual_hours_of_use(Print_consumer) << " h\n";
}

// 12 print_household
void print_household(household *House, float price, int num)
{
    string Heater_Y_N = (House->heater == true ? "Yes" : "No");
    consumer *Temp = House->consumer_Head;
    cout << "H O U S E H O L D  N  O   " << num << "   P O W E R   C O N S U M P T I O N\n";
    cout << "----------------------------------------------------------------------\n";
    cout << right << setw(global_column) << "city"
         << ": " << left << House->Name_of_city << " (at address: " << House << " )\n"; // extension 2
    cout << right << setw(global_column) << "price for one kWh"
         << ": " << left << price * 100 << " ct/kWh\n";
     cout << right << setw(global_column) << "power supplier"
         << ": " << left << House->Power_supplier << " \n";
    cout << right << setw(global_column) << "square meters"
         << ": " << left << House->number_of_sq << " qm\n";
    cout << right << setw(global_column) << "persons"
         << ": " << left << House->number_of_person << "\n";
    cout << right << setw(global_column) << "water heated using electricity"
         << ": " << left << Heater_Y_N << "\n";
    cout << right << setw(global_column) << "list of consumers\n";
    float total_power;
    if (House->heater)
    {
        total_power = ((House->number_of_sq) * ave_con_per_squ) + (House->number_of_person * Heater);
    }
    else
    {
        total_power = ((House->number_of_sq) * ave_con_per_squ) + (House->number_of_person * ave_con_per_person);
    }
    int i = 1;
    cout << "----------------------------------------------------------------------\n";
    while (Temp != nullptr)
    {
        total_power += annual_kWh(Temp);
        print_consumer(Temp, i);
        cout << right << setw(global_column) << "annual hours of standby"
             << ": " << left << annual_hours_of_standby(Temp) << " h\n";
        cout << right << setw(global_column) << "annual consumption"
             << ": " << left << annual_kWh(Temp) << " kWh\n";
        cout << right << setw(global_column) << "annual consumption"
             << ": " << left << annual_kWh(Temp) * price << " EUR\n";
        Temp = Temp->next;
        i++;
    }

    cout << "----------------------------------------------------------------------\n";
    cout << right << setw(global_column) << "power consumption square meters"
         << ": " << left << ((House->number_of_sq) * ave_con_per_squ) << " kwh\n";
    if (House->heater == true) // with Heater
    {
        cout << right << setw(global_column) << "power consumption all persons"
             << ": " << left << House->number_of_person * Heater << " kwh\n";
    }
    else
    {
        cout << right << setw(global_column) << "power consumption all persons"
             << ": " << left << House->number_of_person * ave_con_per_person << " kwh\n";
    }
    cout << right << setw(global_column) << "total annual power consumption"
         << ": " << left << total_power << " kwh\n";
    cout << right << setw(global_column) << "total annual power costs"
         << ": " << left << total_power * price << " EUR\n";
}
// extension 3 function
void input_household(household *Household)
{
    cout << "How many square meters does the household have? ";
    cin >> Household->number_of_sq;
    cout << "How many persons live in this household? ";
    cin >> Household->number_of_person;
    char heaterChar;
    cout << "Is hot water heated using electricity? (y(es) or n(o))";
    cin >> heaterChar;
    Household->heater = (heaterChar == 'y');
    cout << "What is the price for one kWh in EUR? ";
    cin>>Household->Power_price;
    cout<<"whom is the power supplier? ";
    getline(cin >> ws, Household->Power_supplier);
    Household->consumer_Head = nullptr;
}

// extension 4 function copy_consumers
household *copy_consumers(household *fromHouse, household *toHouse)
{
    if (fromHouse->consumer_Head == nullptr)
    {
        return toHouse;
    }
    consumer *fromHouseConsumer = fromHouse->consumer_Head;
    consumer *House2Consumer = toHouse->consumer_Head;
    consumer *tempHead = nullptr;
    consumer *tempTail = nullptr;
    while (fromHouseConsumer != nullptr)
    {
        consumer *FromConsumer = new consumer;
        FromConsumer->description = fromHouseConsumer->description;
        FromConsumer->watt = fromHouseConsumer->watt;
        FromConsumer->watt_standby = fromHouseConsumer->watt_standby;
        FromConsumer->hours = fromHouseConsumer->hours;
        FromConsumer->use = fromHouseConsumer->use;
        FromConsumer->next = fromHouseConsumer->next;

        if (tempHead == nullptr)
        {
            tempHead = FromConsumer;
            tempTail = FromConsumer;
        }
        else
        {
            tempTail->next = FromConsumer;
            tempTail = FromConsumer;
        }
        fromHouseConsumer = fromHouseConsumer->next;
    }
    tempTail->next = toHouse->consumer_Head;
    toHouse->consumer_Head = tempHead;
    return toHouse;
}
// int main function

int main()
{
    int total_household;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE" << endl;
    cout << "how many households does the house have? ";
    cin >> total_household;
    household *array_of_household[total_household];
    for (int i = 0; i < total_household; i++)
    {
        array_of_household[i] = nullptr;
    }
    string Name_of_city;
    //float PricekWh;
    cout << "In which city is the household located? ";
    getline(cin >> ws, Name_of_city);
//     cout << "What is the price for one kWh in EUR? ";
//     cin >> PricekWh;
    while (true)
    {
        cout << "q quit\ni input power consumer\nu move up power consumer\np print household\na print all households" << endl
             << "n new household\nc copy all consumers (added to already existing ones)\nr read data from file\nw write data into file\n>> ";
        char choose;
        cin >> choose;
        switch (choose)
        {
        case 'q':
            exit(0);
            break;
        case 'u':
            int position, Household_no;
            cout << "which household? ";
            cin >> Household_no;
            cout << "\nwhich one? ";
            cin >> position;
            if (array_of_household[Household_no] != nullptr)
            {
                array_of_household[Household_no]->consumer_Head = move_up(array_of_household[Household_no]->consumer_Head, position);
            }
            break;

        case 'i':
            int num_of_houshold;
            cout << "number of household? ";
            cin >> num_of_houshold;
            if (array_of_household[num_of_houshold] != nullptr)
            {
                consumer *newConsumer;
                newConsumer = new consumer;
                cout << "What is the description of the power consumer? ";
                getline(cin >> ws, newConsumer->description);
                cout << "How many watts will it have? ";
                cin >> newConsumer->watt;
                cout << "How many watts standby will it have? ";
                cin >> newConsumer->watt_standby;
                cout << "How often will it be used?";
                input_use("\ndaily  (d)\nmo_fr  (m)\nonce   (o)\nsa_su  (s)\nweekly (w)? ", newConsumer->use);
                cout << "how many hours it will be operating then? ";
                cin >> newConsumer->hours;
                newConsumer->next = nullptr;
                add_consumer_to_household(array_of_household[num_of_houshold], newConsumer);
            }
            else
                cout << "house hold not exist";
            break;

        case 'p':
            int num_household;
            cout << "number of household? ";
            cin >> num_household;
            if (array_of_household[num_household] != nullptr)
            {
                print_household(array_of_household[num_household], array_of_household[num_household]->Power_price, num_household);
            }
            else
                cout << "household not exist";
            break;
        case 'n':
            int index_no;
            cout << "number of household? ";
            cin >> index_no;
            if (array_of_household[index_no] == nullptr)
            {
                household *HousHold = new household;
                HousHold->consumer_Head = nullptr;
                array_of_household[index_no] = HousHold;
                array_of_household[index_no]->Name_of_city = Name_of_city;
                input_household(array_of_household[index_no]);
            }
            else
                cout << "Household already exist\n";
            break;

        case 'a':
            for (int i = 0; i < total_household; i++)
            {
                if (array_of_household[i] != nullptr)
                {
                    print_household(array_of_household[i], array_of_household[i]->Power_price, i);
                    cout << "\n";
                }
            }
            break;
        case 'c':
            int from, to;
            cout << "number of household from which to copy consumers? ";
            cin >> from;
            cout << "number of household to copy to? ";
            cin >> to;
            array_of_household[to] = copy_consumers(array_of_household[from], array_of_household[to]);
            break;

        case 'r':
        {
            string ReadfileName, assignment_no, readCity, readPrice, read_no_of_household,unKnowData;
            char separator_character_read;
            cout << "input file name: ";
            cin >> ReadfileName;
            cout << "input separator character: ";
            cin >> separator_character_read;
            ifstream read_File(ReadfileName);
            if (read_File.is_open())
            {
                cout << "output file " << ReadfileName << " opened..." << endl;
                getline(read_File, assignment_no, separator_character_read) &&
                getline(read_File, read_no_of_household, separator_character_read) &&
                getline(read_File, readCity); 
                Name_of_city = readCity;
                int no_of_house_Hold = stoi(read_no_of_household);
                if (total_household < no_of_house_Hold)
                    cout << "file contains up to " << no_of_house_Hold << " households, but here only " << total_household << " are supported" << endl;
                while (!read_File.eof())
                {
                    int house_hold_no;
                    string household_or_consumer, read_household_no, read_person, read_city_name, read_heater, read_Sq;
                    getline(read_File, household_or_consumer, separator_character_read);
                    if (household_or_consumer == "household")
                    {
                        getline(read_File, read_household_no, separator_character_read);
                        house_hold_no = stoi(read_household_no);
                        if (array_of_household[house_hold_no] == nullptr)
                        {
                            household *HousHold = new household;
                            HousHold->consumer_Head = nullptr;
                            array_of_household[house_hold_no] = HousHold;
                        }
                        getline(read_File, read_city_name, separator_character_read);
                        array_of_household[house_hold_no]->Name_of_city = read_city_name;
                        getline(read_File, read_heater, separator_character_read);
                        array_of_household[house_hold_no]->heater = (read_heater == "true" ? true : false);
                        getline(read_File, read_person, separator_character_read);
                        array_of_household[house_hold_no]->number_of_person = stoi(read_person);
                        getline(read_File, read_Sq, separator_character_read);
                        array_of_household[house_hold_no]->number_of_sq = stoi(read_Sq);
                        getline(read_File,readPrice, separator_character_read);
                        array_of_household[house_hold_no]->Power_price=stof(readPrice);
                        getline(read_File,array_of_household[house_hold_no]->Power_supplier);
                    }
                    else if (household_or_consumer == "consumer")
                    {
                        string read_description, read_using_hours, use_consumer, read_watt, read_watt_standby;
                        if (array_of_household[house_hold_no] != nullptr)
                        {
                            consumer *newConsumer;
                            newConsumer = new consumer;
                            getline(read_File, newConsumer->description, separator_character_read);
                            // newConsumer->description=read_description;
                            getline(read_File, read_using_hours, separator_character_read);
                            newConsumer->hours = stof(read_using_hours);
                            getline(read_File, use_consumer, separator_character_read);
                            newConsumer->use = (use_consumer == "daily" ? daily : use_consumer == "Monday to Friday"    ? mo_fr
                                                                                : use_consumer == "Saturday and Sunday" ? sa_su
                                                                                : use_consumer == "weekly"              ? weekly
                                                                                                                        : once);
                            getline(read_File, read_watt, separator_character_read);
                            newConsumer->watt = stof(read_watt);
                            getline(read_File, read_watt_standby);
                            newConsumer->watt_standby = stof(read_watt_standby);
                            newConsumer->next = nullptr;

                            if (array_of_household[house_hold_no]->consumer_Head == NULL)
                            {
                                array_of_household[house_hold_no]->consumer_Head = newConsumer;
                            }
                            else
                            {
                                consumer *currentConsumer = array_of_household[house_hold_no]->consumer_Head;
                                while (currentConsumer->next != NULL)
                                {
                                    currentConsumer = currentConsumer->next;
                                }
                                currentConsumer->next = newConsumer;
                            }
                        }
                        
                    }
                    else
                        getline(read_File, unKnowData);        
                }
                read_File.close();
                cout << "output file " << ReadfileName << " closed" << endl;
            }
            else
                cout << "output file " << ReadfileName << " is error" << endl;
            break;
        }
        case 'w':
        {
            string writefileName;
            char separator_character;
            cout << "input file name: ";
            cin >> writefileName;
            cout << "input separator character: ";
            cin >> separator_character;
            ofstream writefile(writefileName);
            if (writefile.is_open())
            {
                cout << "output file " << writefileName << " opened..." << endl;
                writefile << "A4" << separator_character << total_household << separator_character << Name_of_city << endl;
                for (int i = 0; i < total_household; i++)
                {
                    if (array_of_household[i] != nullptr)
                    {

                        consumer *tempcon = array_of_household[i]->consumer_Head;
                        writefile << "household" << separator_character << i << separator_character << array_of_household[i]->Name_of_city
                             << separator_character << (array_of_household[i]->heater ? "true" : "false") << separator_character
                             << array_of_household[i]->number_of_person << separator_character 
                             << array_of_household[i]->number_of_sq << separator_character 
                             << array_of_household[i]->Power_price << separator_character
                             << array_of_household[i]->Power_supplier << separator_character << endl;
                        while (tempcon != 0)
                        {
                            writefile << "consumer" << separator_character << tempcon->description << separator_character
                                 << tempcon->hours << separator_character << tempcon->use << separator_character << tempcon->watt
                                 << separator_character << tempcon->watt_standby << endl;
                            tempcon = tempcon->next;
                        }
                    }
                }
                writefile.close();
                cout << "output file " << writefileName << " closed" << endl;
            }
            else
                cout << "output file " << writefileName << " is error" << endl;
            break;
        }
        default:
            cout << "Please input the correct option." << endl;
            break;
        }
    }
    return 0;
}
