
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int ave_con_per_person=200;
const int ave_con_per_squ=9;
const int Heater=550;
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

// 3 consumer structure
struct consumer
 {
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    consumer* next;
    
};

// 4 Pointer in List

struct household 
{
    string Name_of_city;
    int number_of_sq;
    int number_of_person;    
    consumer* consumer_Head;
    bool heater;   
};

// 5 add consumer to household

void add_consumer_to_household(household* Hous_Hold, consumer* Consumer) 
{
    Consumer->next = Hous_Hold->consumer_Head;
    Hous_Hold->consumer_Head = Consumer;
}

// 6 annual hours of use

float annual_hours_of_use(consumer* consumer) 
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
float annual_hours_of_standby(consumer* Con)
{
    float annual_hours_standby = ((365 * 24) - annual_hours_of_use(Con));
    return annual_hours_standby;
}

// 8 annual kwh

float annual_kWh(consumer* Cout)
{
    float annual_KWH = (((annual_hours_of_use(Cout) * Cout->watt) + (annual_hours_of_standby(Cout)*Cout->watt_standby))/1000);
    return annual_KWH;
}
// 9 move_up

consumer* move_up(consumer* Current_Head, int k) 
{
    if (k <= 1) 
    {
        return Current_Head;  
    }

    consumer* current = Current_Head;
    consumer* kNode = current->next;
 
    if (k==2 && kNode != nullptr) 
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
            consumer* Kth_Node = current->next->next;
            current->next->next = Kth_Node->next;
            Kth_Node->next = current->next;
            current->next = Kth_Node;
            return Current_Head;
    }
}

// 11 print_consumer

void print_consumer(consumer* PrCon, int valu) 
{
    cout <<right<< setw(global_column)<< valu << ": " << left << PrCon->description <<" (at address: "<<PrCon<< " )\n";//extension 1
    cout <<right<< setw(global_column)<< "power consumption"<< ": "<< left << PrCon->watt << " w\n";
    cout <<right<< setw(global_column)<< "power consumption standby"<< ": "<< left << PrCon->watt_standby << " w\n";
    cout <<right<< setw(global_column)<< "annual hours of use"<< ": "<< left << annual_hours_of_use(PrCon) << " h\n";
    
}

// 12 print_household
void print_household(household* House, float price,int num) 
{   
    string HeaterStr;
    if(House->heater==true)
    {
        HeaterStr="Yes";
    }
    else
    {
         HeaterStr="No";
    }
    consumer* Temp = House->consumer_Head;
    cout << "H O U S E H O L D  N  O  " << num <<"  P O W E R   C O N S U M P T I O N\n";
    cout << "----------------------------------------------------------------------\n";
    cout << right << setw(global_column) << "city" << ": " << left << House->Name_of_city <<" (at address: "<<House << " )\n";//extension 2
    cout << right << setw(global_column) << "price for one kWh" << ": " << left << price*100 << " ct/kWh\n";
    cout << right << setw(global_column) << "square meters" << ": " << left << House->number_of_sq << " qm\n";
    cout << right << setw(global_column) << "persons" << ": " << left << House->number_of_person << "\n";
    cout << right << setw(global_column) << "water heated using electricity" << ": " << left << HeaterStr<< "\n";
    cout << right << setw(global_column) << "list of consumers\n";
    float total_power ;
    if(House->heater)
    {
        total_power =((House->number_of_sq) * ave_con_per_squ)+(House->number_of_person * Heater);
    }
    else
    {
        total_power =((House->number_of_sq) * ave_con_per_squ)+(House->number_of_person *  ave_con_per_person);
    }
    int i = 1;
    cout << "----------------------------------------------------------------------\n";
    while (Temp != nullptr) 
    {
        total_power += annual_kWh(Temp);
        print_consumer(Temp, i);
        cout << right << setw(global_column) << "annual hours of standby"<< ": " << left << annual_hours_of_standby(Temp)<< " h\n";
        cout << right << setw(global_column) << "annual consumption"<< ": "<< left << annual_kWh(Temp)<< " kWh\n";
        cout << right << setw(global_column) << "annual consumption"<< ": "<< left << annual_kWh(Temp)*price<<" EUR\n";
        Temp = Temp->next;
        i++;
    }
    
    cout << "----------------------------------------------------------------------\n";
    cout << right << setw(global_column) << "power consumption square meters" << ": " << left << ((House->number_of_sq) * ave_con_per_squ) << " kwh\n";
    if(House->heater==true)//with Heater
    {
        cout << right << setw(global_column) << "power consumption all persons" << ": " << left << House->number_of_person * Heater << " kwh\n";
    }
    else
    {
        cout << right << setw(global_column) << "power consumption all persons" << ": " << left << House->number_of_person * ave_con_per_person << " kwh\n";
    }
    cout<< right <<setw(global_column)<<"total annual power consumption"<< ": " << left <<total_power<< " kwh\n";
    cout << right << setw(global_column) << "total annual power costs" << ": " << left << total_power * price << " EUR\n";
}
//extension 3 function
 void input_household(household* Household)
 {
    cout << "How many square meters does the household have? ";
    cin >> Household->number_of_sq;
    cout << "How many persons live in this household? ";
    cin >> Household->number_of_person;
    char heaterChar;
    cout << "Is hot water heated using electricity? (y(es) or n(o))";
    cin >> heaterChar;
    Household->heater=(heaterChar=='y');
    Household->consumer_Head=nullptr;
 }

 //extension 4 function copy_consumers  
household* copy_consumers(household* fromHouse, household* toHouse)
{
    if (fromHouse->consumer_Head == nullptr) 
    {
        return toHouse;
    }
    consumer*fromHouseConsumer = fromHouse->consumer_Head;
    consumer* House2Consumer = toHouse->consumer_Head; 
    consumer* tempHead = nullptr;
    consumer* tempTail = nullptr;
    while (fromHouseConsumer != nullptr) 
    {
        consumer* FromConsumer = new consumer;
        FromConsumer->description =fromHouseConsumer->description;
        FromConsumer->watt =fromHouseConsumer->watt;
        FromConsumer->watt_standby =fromHouseConsumer->watt_standby;
        FromConsumer->hours =fromHouseConsumer->hours;
        FromConsumer->use =fromHouseConsumer->use;
        FromConsumer->next =fromHouseConsumer->next;

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
       fromHouseConsumer=fromHouseConsumer->next;
    }
        tempTail->next=toHouse->consumer_Head;
        toHouse->consumer_Head = tempHead;
    return toHouse;
}
// int main function 

int main() 
{   
    int n;
    cout << "CALCULATION OF AVERAGE POWER CoutTS FOR A HOUSEHOLD" << endl;
    cout<<"how many households does the house have? ";
    cin>>n;
    household* array[n];
    for(int i=0;i<n;i++)
    {
        array[i]=nullptr;
    }
    float PricekWh;
    string Name_of_city;
    cout << "In which city is the household located? ";
    cin >> Name_of_city;
    cout << "What is the price for one kWh in EUR? ";
    cin >> PricekWh;
    

    while (true) 
    {
        cout << "q quit\ni input power consumer\nu move up power consumer\np print household\na print all households\nn new household\nc copy all consumers (added to already existing ones)\n>> " ;
        char ch;
        cin >> ch;
        switch (ch) 
        {
            case 'q': 
                exit(0);
                break;

            case 'u':
                int Poutition,houseHold_num;
                cout<<"which household? ";
                cin>>houseHold_num;
                cout<<"\nwhich one? ";
                cin>>Poutition;
                if(array[houseHold_num]!= nullptr)
                {
                    array[houseHold_num]->consumer_Head=move_up(array[houseHold_num]->consumer_Head,Poutition);
                }
                break;

            case 'i':
                int num_of_houshold;
                cout<<"number of household? ";
                cin>>num_of_houshold;
                if(array[num_of_houshold]!=nullptr)
                {
                    consumer *newConsumer,*NewTemp;
                newConsumer=new consumer;
                cout << "What is the description of the power consumer? ";
                cin >> newConsumer->description;
                cout << "How many watts will it have? ";
                cin >> newConsumer->watt;
                cout << "How many watts standby will it have? ";
                cin >> newConsumer->watt_standby;
                cout << "How often will it be used?";
                input_use("\ndaily  (d)\nmo_fr  (m)\nonce   (o)\nsa_su  (s)\nweekly (w)? ", newConsumer->use);
                cout << "how many hours it will be operating then? ";
                cin >>newConsumer->hours;
                newConsumer->next = nullptr;
                add_consumer_to_household(array[num_of_houshold], newConsumer);
                }
                else
                cout<<"house hold not exist";
                break;

            case 'p':
                int num_household;
                cout<<"number of household? ";
                cin>>num_household;
                if(array[num_household]!=nullptr)
                {
                     print_household(array[num_household], PricekWh,num_household);
                }
                else
                cout<<"household not exist";
                break;
            case 'n':
                int num;
                cout<<"number of household? ";
                cin>>num;
                if(array[num]==nullptr)
                {
                    household* HousHold = new household;
                    HousHold->consumer_Head=nullptr;
                    array[num]=HousHold;
                    array[num]->Name_of_city=Name_of_city;
                    input_household(array[num]);
                }
                else 
                cout<<"Household all rady exist\n";
                break;

            case 'a':
                for(int i=0;i<n;i++)
                {
                    if(array[i]!=nullptr)
                    {
                         print_household(array[i], PricekWh,i);
                         cout<<"\n";
                    }
                }
                 break;
            case 'c':
                int from,to;
                cout<<"number of household from which to copy consumers? ";
                cin>> from;
                cout<<"number of household to copy to? ";
                cin>>to;
                array[to]=copy_consumers(array[from],array[to]);
            break;

            default:
                cout<<"Please enter a valid option q , u , i or p\n";
        }
    }
    return 0;
}
