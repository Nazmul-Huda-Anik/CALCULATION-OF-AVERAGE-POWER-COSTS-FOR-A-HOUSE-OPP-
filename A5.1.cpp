#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
const int ave_con_per_person = 200;
const int ave_con_per_squ = 9;
const int Heater = 550;
const int global_column = 35;
bool control_print = true;
enum class Use
{
     once,
     daily,
     mo_fr,
     sa_su,
     weekly
};
void input_use(string name, Use &use)
{
     cout << name;
     char ch;
     cin >> ch;
     switch (ch)
     {
     case 'd':
          use = Use::daily;
          break;
     case 'm':
          use = Use::mo_fr;
          break;
     case 'o':
          use = Use::once;
          break;
     case 's':
          use = Use::sa_su;
          break;
     case 'w':
          use = Use::weekly;
          break;
     default:
          cout << "Please enter a valid option  d, m, o, s, or w\n";
     }
}
ostream &operator<<(ostream &out, const Use &use)
{
     switch (use)
     {
     case Use::once:
          out << "once";
          break;
     case Use::daily:
          out << "daily";
          break;
     case Use::mo_fr:
          out << "Monday to Friday";
          break;
     case Use::sa_su:
          out << "Saturday and Sunday";
          break;
     case Use::weekly:
          out << "weekly";
          break;
     }
     return out;
}

class Consumer
{
private:
     string description;
     float watt;
     float watt_standby;
     float hours;
     Consumer *next;
     Use use;
     static int Consumer_in_total;

public:
     Consumer() : next(nullptr) {Consumer_in_total++;}
     ~Consumer()
     {
          cout << "Consumer " << this->get_description() << " at address " << this << " deleted" << endl;
          Consumer_in_total--;
     }
     string get_description() const
     {
          return description;
     }
     float get_watt() const
     {
          return watt;
     }
     float get_watt_standby() const
     {
          return watt_standby;
     }
     float get_hours() const
     {
          return hours;
     }
     Use get_use() const
     {
          return use;
     }
     Consumer *get_next() const
     {
          return next;
     }

     void set_description(const string &Description)
     {
          description = Description;
     }
     void set_watt(float Watt)
     {
          watt = Watt;
     }
     void set_watt_standby(float W_standby)
     {
          watt_standby = W_standby;
     }
     void set_hours(float S_Hours)
     {
          hours = S_Hours;
     }
     void set_use(Use use)
     {
          this->use = use;
     }
     void set_next(Consumer *set_next_consumer)
     {
          next = set_next_consumer;
     }
     int get_total_consumer()
     {
          return Consumer_in_total;
     }
     float annual_hours_of_use() const;
     float annual_hours_of_standby() const;
     float annual_kWh() const;
     void print_consumer(Consumer *, int);
};

int Consumer :: Consumer_in_total=0;
class Household
{
private:
     string name_of_city;
     int number_of_sq;
     int number_of_person;
     Consumer *consumer_head;
     bool heater;
     float Power_price;
     string Power_supplier;

public:
     Household() : consumer_head(nullptr) {}
     ~Household() { cout << "Household at address " << this << " deleted" << endl; }
     
     void set_name_of_city(string City_name)
     {
          name_of_city = City_name;
     }
     void set_number_of_sq(int Number_of_sq)
     {
          number_of_sq = Number_of_sq;
     }
     void set_number_of_person(int Number_of_person)
     {
          number_of_person = Number_of_person;
     }
     void set_consumer_head(Consumer *Consumer_head)
     {
          consumer_head = Consumer_head;
     }
     void set_heater(bool heater_Y_N)
     {
          heater = heater_Y_N;
     }
     void ste_Price(float Price)
     {
          Power_price = Price;
     }
     void set_Power_supplier(string powerSupplier)
     {
          Power_supplier = powerSupplier;
     }

     string get_name_of_city() const
     {
          return name_of_city;
     }
     int get_Number_of_sq() const
     {
          return number_of_sq;
     }
     int get_number_of_person() const
     {
          return number_of_person;
     }
     Consumer *get_consumer_head() const
     {
          return consumer_head;
     }
     bool get_heater() const
     {
          return heater;
     }
     float get_Price()
     {
          return Power_price;
     }
     string get_Power_supplier()
     {
          return Power_supplier;
     }

     void add_consumer_to_household(Household *house_hold, Consumer *consumer);
     Consumer *move_up(Consumer *Current_Head, int k);
     void print_household(Household *house, int);
     Household *copy_consumers(Household *fromHouse, Household *toHouse);
     void input_household(Household *household);
};

class Address
{
private:
     string street;
     string street_no;
     string zip_code;
     string city;

public:
     Address() : street("null"), street_no("null"), zip_code("null"), city("null") {}
     ~Address()
     {

          if(control_print)
          {
               cout<<"Address "<<this->to_string()<<" at address "<<this<<" deleted"<<endl;
          }
          
     }
     string get_Street() const
     {
          return street;
     }

     string get_Street_No() const
     {
          return street_no;
     }

     string get_Zip_Code() const
     {
          return zip_code;
     }

     string get_City() const
     {
          return city;
     }
     void input(string Street, string Street_no, string Zip_Code, string City)
     {
          street = Street;
          street_no = Street_no;
          zip_code = Zip_Code;
          city = City;
     }
     string to_string()
     {
          return get_Street() + " " + get_Street_No() + ", " + get_Zip_Code() + " " + get_City();
     }
};

class House
{
     private:
          int number_of_households;
          Household **household;
          Address address;

     public:
          House(int num, const Address &ad) : number_of_households(num), address(ad)
          {
               household = new Household *[number_of_households];
               for (int i = 0; i < number_of_households; ++i)
               {
                    household[i] = nullptr;
               }
          }
          ~House()
          {
               cout<<"House at address "<<this<<" deleted"<<endl;
          }
          Address get_Address() const
          {
               return address;
          }

          void set_household(int num, Household *house_set)
          {
               household[num] = house_set;
          }
          Household *get_household(int num)
          {
               return household[num];
          }
          int getNumberHouse()
          {
               return number_of_households;
          }

          void print_all(Household *, int);
          House *readDataFromFile(string, House *);
          void WriteDataIntoFile(House *);
};

void House ::print_all(Household *house, int i)
{
     house->print_household(house, i);
}

float Consumer::annual_hours_of_use() const
{
     switch (use)
     {
     case Use::once:
          return hours;
     case Use::daily:
          return hours * 365;
     case Use::mo_fr:
          return hours * 260;
     case Use::sa_su:
          return hours * 104;
     case Use::weekly:
          return hours * 52;
     default:
          return 0;
     }
}

float Consumer::annual_hours_of_standby() const
{
     float annual_hours_standby = (365 * 24) - annual_hours_of_use();
     return annual_hours_standby;
}

float Consumer::annual_kWh() const
{
     float annual_KWH = ((annual_hours_of_use() * watt) + (annual_hours_of_standby() * watt_standby)) / 1000;
     return annual_KWH;
}

void Household::add_consumer_to_household(Household *house_hold, Consumer *consumer)
{
     consumer->set_next(house_hold->get_consumer_head());
     house_hold->set_consumer_head(consumer);
}

Consumer *Household::move_up(Consumer *Current_Head, int k)
{
     if (k <= 1)
     {
          return Current_Head;
     }

     Consumer *current = Current_Head;
     Consumer *kNode = (current->get_next());

     if (k == 2 && kNode != nullptr)
     {
          current->set_next(kNode->get_next());
          kNode->set_next(Current_Head);
          Current_Head = kNode;
          return Current_Head;
     }
     else
     {
          for (int i = 1; i < k - 2; i++)
          {
               if (current->get_next() == nullptr)
               {
                    return Current_Head;
               }
               current = current->get_next();
          }
          Consumer *Kth_Node = current->get_next()->get_next();
          current->get_next()->set_next(Kth_Node->get_next());
          Kth_Node->set_next(current->get_next());
          current->set_next(Kth_Node);
          return Current_Head;
     }
}

Household *Household::copy_consumers(Household *fromHouse, Household *toHouse)
{
     if (fromHouse->get_consumer_head() == nullptr)
     {
          return toHouse;
     }
     Consumer *fromHouseConsumer = fromHouse->get_consumer_head();
     Consumer *House2Consumer = toHouse->get_consumer_head();
     Consumer *tempHead = nullptr;
     Consumer *tempTail = nullptr;
     while (fromHouseConsumer != nullptr)
     {
          Consumer *FromConsumer = new Consumer;
          FromConsumer->set_description(fromHouseConsumer->get_description());
          FromConsumer->set_watt(fromHouseConsumer->get_watt());
          FromConsumer->set_watt_standby(fromHouseConsumer->get_watt_standby());
          FromConsumer->set_hours(fromHouseConsumer->get_hours());
          FromConsumer->set_use(fromHouseConsumer->get_use());
          FromConsumer->set_next(fromHouseConsumer->get_next());

          if (tempHead == nullptr)
          {
               tempHead = FromConsumer;
               tempTail = FromConsumer;
          }
          else
          {
               tempTail->set_next(FromConsumer);
               tempTail = FromConsumer;
          }
          fromHouseConsumer = fromHouseConsumer->get_next();
     }
     tempTail->set_next(toHouse->get_consumer_head());
     toHouse->set_consumer_head(tempHead);
     return toHouse;
}

void Consumer ::print_consumer(Consumer *pr_con, int valu)
{
     cout << right << setw(global_column-2) << valu
          << left << ": " << pr_con->get_description() << "\n";
     cout << right << setw(global_column) << "(this: "
          << left << pr_con << "\n";
     cout << right << setw(global_column) << "power consumption: "
          << left << pr_con->get_watt() << " w\n";
     cout << right << setw(global_column) << "power consumption standby: "
          << left << pr_con->get_watt_standby() << " w\n";
     cout << right << setw(global_column) << "annual hours of use: "
          << left << pr_con->annual_hours_of_use() << " h\n";
}

void Household ::print_household(Household *house, int number)
{

     string heaterStr = (house->get_heater()) ? "Yes" : "No";
     Consumer *temp = house->get_consumer_head();
     float total_power;

     if (house->get_heater())
          total_power = (house->get_Number_of_sq() * ave_con_per_squ) + (house->get_number_of_person() * Heater);
     else
          total_power = (house->get_Number_of_sq() * ave_con_per_squ) + (house->get_number_of_person() * ave_con_per_person);
          int i = 1;
          cout << "H O U S E  H O L D  N O  " << number << "  P O W E R   C O N S U M P T I O N\n";
          cout << "----------------------------------------------------------------------\n";
          cout << right << setw(global_column) << "(this: "
               << left << house << ")\n";
          cout << right << setw(global_column) << "price for one kWh: "
               << left << house->get_Price() * 100 << " ct/kWh\n";
          cout << right << setw(global_column) << "power supplier: "
               << left << house->get_Power_supplier() << " \n";
          cout << right << setw(global_column) << "square meters: "
               << left << house->get_Number_of_sq() << " qm\n";
          cout << right << setw(global_column) << "persons: "
               << left << house->get_number_of_person() << "\n";
          cout << right << setw(global_column) << "water heated using electricity: "
               << left << heaterStr << "\n";
          cout << right << setw(global_column-1) << "list of consumers\n";
          cout << "----------------------------------------------------------------------\n";
     while (temp != nullptr)
     {
          total_power += temp->annual_kWh();
          temp->print_consumer(temp, i);
          cout << right << setw(global_column) << "annual hours of standby: "
               << left << temp->annual_hours_of_standby() << " h\n";
          cout << right << setw(global_column) << "annual consumption: "
               << left << temp->annual_kWh() << " kWh\n";
          cout << right << setw(global_column) << "annual cost: "
               << left << temp->annual_kWh() * house->get_Price() << " EUR\n";
          temp = temp->get_next();
          i++;
     }
          cout << "----------------------------------------------------------------------\n";
          cout << right << setw(global_column) << "power consumption square meters: "
               << left << (house->get_Number_of_sq() * ave_con_per_squ) << " kwh\n";
     if (house->get_heater())
          cout << right << setw(global_column) << "power consumption all persons: "
               << left << house->get_number_of_person() * Heater << " kwh\n";
     else
          cout << right << setw(global_column) << "power consumption all persons: "
               << left << house->get_number_of_person() * ave_con_per_person << " kwh\n";
          cout << right << setw(global_column) << "total annual power consumption: "
               << left << total_power << " kwh\n";
          cout << right << setw(global_column) << "total annual power costs: "
               << left << total_power * house->get_Price() << " EUR\n";
}

void Household ::input_household(Household *household)
{
     int sq_house, N_person;
     char heater_char;
     float PricekWh;
     string PowerSupplierName;
     cout << "How many square meters does the household have? ";
     cin >> sq_house;
     household->set_number_of_sq(sq_house);
     cout << "How many persons live in this household? ";
     cin >> N_person;
     household->set_number_of_person(N_person);
     cout << "Is hot water heated using electricity? (y(es) or n(o))";
     cin >> heater_char;
     household->set_heater(heater_char == 'y');
     cout << "What is the price for one kWh in EUR? ";
     cin >> PricekWh;
     household->ste_Price(PricekWh);
     cout << "who is the power supplier? ";
     cin.ignore();
     getline(cin, PowerSupplierName);
     household->set_Power_supplier(PowerSupplierName);
     household->set_consumer_head(nullptr);
}

House *House ::readDataFromFile(string ReadfileName, House *readhouse)
{
     string assignment_no, readStreet, redHouseNo, readZip, readCity, readPrice, read_no_of_household, unKnowData, power_company;
     string Description;
     char separator_character_read;
     cout << "input separator character: ";
     cin >> separator_character_read;
     ifstream read_File(ReadfileName);
     if (read_File.is_open())
     {
          cout << "output file " << ReadfileName << " opened..." << endl;
               getline(read_File, assignment_no, separator_character_read) &&
               getline(read_File, read_no_of_household, separator_character_read) &&
               getline(read_File, readStreet, separator_character_read) &&
               getline(read_File, redHouseNo, separator_character_read) &&
               getline(read_File, readZip, separator_character_read) &&
               getline(read_File, readCity);
          Address *temp_address1 = new Address;
          Address *temp_address2 = new Address;
          temp_address2->input(readStreet, redHouseNo, readZip, readCity);
          temp_address1->input(readStreet, redHouseNo, readZip, readCity);
          delete temp_address2;
          House *house2 = new House(stoi(read_no_of_household), *temp_address1);
          readhouse = house2;
          delete temp_address1;
          while (!read_File.eof())
          {
               int house_hold_no;
               string household_or_consumer, read_household_no, read_person, read_city_name, read_heater, read_Sq;
               getline(read_File, household_or_consumer, separator_character_read);
               if (household_or_consumer == "household")
               {
                    getline(read_File, read_household_no, separator_character_read);
                    house_hold_no = stoi(read_household_no);
                    if (readhouse->get_household(house_hold_no) == nullptr)
                    {
                         Household *housHold = new Household;
                         readhouse->set_household(house_hold_no, housHold);
                    }
                    getline(read_File, read_heater, separator_character_read);
                    readhouse->get_household(house_hold_no)->set_heater((read_heater == "true" ? true : false));
                    getline(read_File, read_person, separator_character_read);
                    readhouse->get_household(house_hold_no)->set_number_of_person(stoi(read_person));
                    getline(read_File, read_Sq, separator_character_read);
                    readhouse->get_household(house_hold_no)->set_number_of_sq(stoi(read_Sq));
                    getline(read_File, readPrice, separator_character_read);
                    readhouse->get_household(house_hold_no)->ste_Price(stof(readPrice));
                    getline(read_File, power_company);
                    readhouse->get_household(house_hold_no)->set_Power_supplier(power_company);
               }
               else if (household_or_consumer == "consumer")
               {
                    string read_description, read_using_hours, use_consumer, read_watt, read_watt_standby;
                    if (readhouse->get_household(house_hold_no) != nullptr)
                    {
                         Consumer *newConsumer = new Consumer;
                         getline(read_File, Description, separator_character_read);
                         newConsumer->set_description(Description);
                         getline(read_File, read_using_hours, separator_character_read);
                         newConsumer->set_hours(stof(read_using_hours));
                         getline(read_File, use_consumer, separator_character_read);
                         newConsumer->set_use((use_consumer == "daily" ? Use::daily : use_consumer == "Monday to Friday"  ? Use::mo_fr
                                                                                  : use_consumer == "Saturday and Sunday" ? Use::sa_su
                                                                                  : use_consumer == "weekly"              ? Use::weekly
                                                                                                                          : Use::once));
                         getline(read_File, read_watt, separator_character_read);
                         newConsumer->set_watt(stof(read_watt));
                         getline(read_File, read_watt_standby);
                         newConsumer->set_watt_standby(stof(read_watt_standby));

                         if (readhouse->get_household(house_hold_no)->get_consumer_head() == NULL)
                         {
                              readhouse->get_household(house_hold_no)->set_consumer_head(newConsumer);
                         }
                         else
                         {
                              Consumer *currentConsumer = readhouse->get_household(house_hold_no)->get_consumer_head();
                              while (currentConsumer->get_next() != NULL)
                              {
                                   currentConsumer = currentConsumer->get_next();
                              }
                              currentConsumer->set_next(newConsumer);
                         }
                    }
               }
               else
                    getline(read_File, unKnowData);
          }
          read_File.close();
          cout << "output file " << ReadfileName << " closed" << endl;
          return readhouse;
     }
     else
          cout << "output file " << ReadfileName << " is error" << endl;
     return readhouse;
}

void House::WriteDataIntoFile(House *WriteHouse)
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
          writefile << "A4"
                    << separator_character << WriteHouse->getNumberHouse()
                    << separator_character << WriteHouse->get_Address().get_Street()
                    << separator_character << WriteHouse->get_Address().get_Street_No()
                    << separator_character << WriteHouse->get_Address().get_Zip_Code()
                    << separator_character << WriteHouse->get_Address().get_City() << endl;

          for (int i = 0; i < WriteHouse->getNumberHouse(); i++)
          {
               if (WriteHouse->get_household(i) != nullptr)
               {

                    Consumer *tempcon = WriteHouse->get_household(i)->get_consumer_head();
                    writefile << "household" << separator_character << i

                              << separator_character << (WriteHouse->get_household(i)->get_heater() ? "true" : "false")
                              << separator_character << WriteHouse->get_household(i)->get_number_of_person()
                              << separator_character << WriteHouse->get_household(i)->get_Number_of_sq()
                              << separator_character << WriteHouse->get_household(i)->get_Price()
                              << separator_character << WriteHouse->get_household(i)->get_Power_supplier()
                              << endl;
                    while (tempcon != 0)
                    {
                         writefile << "consumer"
                                   << separator_character << tempcon->get_description()
                                   << separator_character << tempcon->get_hours()
                                   << separator_character << tempcon->get_use()
                                   << separator_character << tempcon->get_watt()
                                   << separator_character << tempcon->get_watt_standby() << endl;
                         tempcon = tempcon->get_next();
                    }
               }
          }
          writefile.close();
          cout << "output file " << writefileName << " closed" << endl;
     }
     else
          cout << "output file " << writefileName << " is error" << endl;
}
int main()
{
     House *house1 = nullptr;
     cout << "\nCALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION" << endl;
     while (true)
     {
          cout << "q quit\nd delete house\nh house initialisation\ni input power consumer"<<endl
               <<"u move up power consumer\np print household\na print all households" << endl
               << "n new household\nc copy all consumers (added to already existing ones)"<<endl
               <<"r read data from file\nw write data into file\n>> ";
          char ch;
          cin >> ch;

          switch (ch)
          {
          case 'i':
          {
               int num_of_household;
               cout << "number of household ? ";
               cin >> num_of_household;
               if (num_of_household >= 0)
               {
                    string Description;
                    float WATT, WATT_STANDBY, HOUR;
                    Consumer *newConsumer = new Consumer;
                    cout << "what is the description of the power consumer? ";
                    cin.ignore();
                    getline(cin, Description);
                    newConsumer->set_description(Description);
                    cout << "How many watts will it have? ";
                    cin >> WATT;
                    newConsumer->set_watt(WATT);
                    cout << "How many watts standby will it have? ";
                    cin >> WATT_STANDBY;
                    newConsumer->set_watt_standby(WATT_STANDBY);
                    cout << "How often will it be used?";
                    Use use_input;
                    input_use("\ndaily  (d)\nmo_fr  (m)\nonce   (o)\nsa_su  (s)\nweekly (w)? ", use_input);
                    newConsumer->set_use(use_input);
                    cout << "How many hours will it be operating then? ";
                    cin >> HOUR;
                    newConsumer->set_hours(HOUR);
                    newConsumer->set_next(nullptr);
                    house1->get_household(num_of_household)->add_consumer_to_household(house1->get_household(num_of_household), newConsumer);
               }
               else
                    cout << "Household does not exist";
               break;
          }
          case 'u':
               int position, Household_no;
               cout << "which household? ";
               cin >> Household_no;
               cout << "which one? ";
               cin >> position;
               if (house1->get_household(Household_no) != nullptr)
               {
                    Consumer *currentConsumer = house1->get_household(Household_no)->get_consumer_head();
                    house1->get_household(Household_no)->set_consumer_head(house1->get_household(Household_no)->move_up(currentConsumer, position));
               }
               break;

          case 'p':
          {
               int num_household;
               cout << "Enter the household number: ";
               cin >> num_household;
               if (num_household >= 0)
               {
                    house1->get_household(num_household)->print_household(house1->get_household(num_household), num_household);
               }
               else
                    cout << "Household does not exist";
               break;
          }
          case 'n':
               int num;
               cout << "number of household? ";
               cin >> num;
               if (house1->get_household(num) == nullptr)
               {
                    Household *housHold = new Household;
                    housHold->set_consumer_head(nullptr);
                    house1->set_household(num, housHold);
                    house1->get_household(num)->input_household(house1->get_household(num));
               }
               else
                    cout << "Household already exist\n";
               break;
          case 'a':
               if (house1 != nullptr)
               {
                    control_print=false;
                    cout << "======================================================================" << endl
                         << "                             H O U S E                                " << endl
                         << "======================================================================" << endl;
                    cout << right << setw(global_column) << "(this: "
                         << left << house1 << ")\n";
                    cout << right << setw(global_column) << "address: "
                         << left << house1->get_Address().to_string() << "\n";
                    cout << right << setw(global_column) << "number of households: "
                         << left << house1->getNumberHouse() << "\n";
                    int totalnumber_consumer=0;
                    for (int i = 0; i < house1->getNumberHouse(); i++)
                    {
                         if (house1->get_household(i) != nullptr)
                         {
                              totalnumber_consumer=house1->get_household(i)->get_consumer_head()->get_total_consumer();
                             
                         }
                    }
                    cout << right << setw(global_column) << "total number of all consumers: "
                         << left << totalnumber_consumer << "\n";

                    for (int i = 0; i < house1->getNumberHouse(); i++)
                    {
                         if (house1->get_household(i) != nullptr)
                         {

                              house1->print_all(house1->get_household(i), i);
                              cout << "\n";
                         }
                    }
                    cout << "======================================================================" << endl;
               }
               else
                    cout << "house is a nullptr, please first choose h to initialise a new house " << endl;
                    control_print=true;
               break;
          case 'c':
          {
               int from, to;
               cout << "number of household from which to copy consumers? ";
               cin >> from;
               cout << "number of household to copy to? ";
               cin >> to;
               Household *tempHousehold = new Household;
               house1->set_household(to, tempHousehold->copy_consumers(house1->get_household(from), house1->get_household(to)));
               break;
          }
          case 'h':
          {
               int num_house;
               string str, str_no, zip_c, city_nam, full_address;
               cout << "how many households does the house have? ";
               cin >> num_house;
               cout << "what is the street name? ";
               getline(cin >> ws, str);
               cout << "what is the house number? ";
               cin >> str_no;
               cout << "what is the zip code? ";
               cin >> zip_c;
               cin.ignore();
               cout << "what is the city name? ";
               getline(cin, city_nam);
               Address *temp_address = new Address;
               temp_address->input(str, str_no, zip_c, city_nam);
               full_address = temp_address->to_string();
               Address houseAddress;
               houseAddress.input(str, str_no, zip_c, city_nam);
               House *house = new House(num_house, houseAddress);
               house1 = house;
               delete temp_address;
               break;
          }
          case 'r':
          {
               string ReadfileName;
               cout << "input file name: ";
               cin >> ReadfileName;
               house1 = house1->readDataFromFile(ReadfileName, house1);
               break;
          }
          case 'w':
          {
               house1->WriteDataIntoFile(house1);
               break;
          }
          case 'd':
          {
               for (int i = 0; i < house1->getNumberHouse(); i++)
               {
                    if (house1->get_household(i) != nullptr)
                    {
                         while (house1->get_household(i)->get_consumer_head() != nullptr)
                         {
                         Consumer *tempConsumer = house1->get_household(i)->get_consumer_head();
                         house1->get_household(i)->set_consumer_head(tempConsumer->get_next());
                         delete tempConsumer;
                         }

                         delete house1->get_household(i);
                    }
               }

               delete house1;
               break;
          }
          case 'q':
               return 0;
          default:
               cout << "Please enter a valid option: i, p, q\n";
          }
     }
     return 0;
}
