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
void input_use(string name, Use& use)
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
ostream& operator<<(ostream& out, const Use& use)
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

        if (control_print)
        {
            cout << "Address " << this->to_string() << " at address " << this << " deleted" << endl;
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

class Device
{
private:
    string description;
    Device* next;

public:
    Device(Device* ptr = nullptr) : next(ptr) {}
    virtual ~Device()
    {
        cout << "Device " << this->get_description() << " at address " << this << " deleted" << endl;
    }
    string get_description() const
    {
        return description;
    }
    Device* get_next()
    {
        return next;
    }
    void set_description(string set_Description)
    {
        description = set_Description;
    }
    void set_next(Device* set_next_Device)
    {
        next = set_next_Device;
    }
    virtual void input()
    {
        cout << "what is the description of the power consumer: ";
        cin.ignore();
        getline(cin, description);
    }

    virtual void print(int intValue, float floatValue) const = 0;
    virtual float annual_kWh() const = 0;
    virtual Device* get_a_copy() const = 0;
    virtual string get_string_for_file(char) const = 0;
};

class Consumer : public Device
{
private:
    float watt;
    Use use;
    static int total_number;

public:
    Consumer(Device* ptr = nullptr) : Device(ptr) { total_number++; }
    virtual ~Consumer()
    {
        cout << "Consumer " << this->get_description() << " at address " << this << " deleted" << endl;
        total_number--;
    }

    float get_watt() const
    {
        return watt;
    }

    Use get_use() const
    {
        return use;
    }
    void set_watt(float Watt)
    {
        watt = Watt;
    }
    void set_use(Use use)
    {
        this->use = use;
    }
    static int get_total_consumer()
    {
        return total_number;
    }
    virtual void input()
    {
        Device::input();
        cout << "how many watt it will have? ";
        cin >> watt;
        cout << "how often it will be used? ";
        input_use("\ndaily  (d)\nmo_fr  (m)\nonce   (o)\nsa_su  (s)\nweekly (w)? ", this->use);
    }
};

int Consumer::total_number = 0;

class Immobile : public Consumer
{
private:
    float watt_standby;
    float hours;

public:
    Immobile(Device* ptr = nullptr) : Consumer(ptr) {}
    
    virtual ~Immobile()
    {
        cout << "Immobile " << this->get_description() << " at address " << this << " deleted" << endl;
    }
    
    float get_watt_standby() const
    {
        return watt_standby;
    }
    
    float get_hours() const
    {
        return hours;
    }
    
    void set_watt_standby(float W_standby)
    {
        watt_standby = W_standby;
    }
    
    void set_hours(float S_Hours)
    {
        hours = S_Hours;
    }
    
    float annual_hours_of_use() const
    {
        {
            switch (Consumer::get_use())
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
    }
    
    float annual_hours_of_standby() const
    {
        float annual_hours_standby = (365 * 24) - annual_hours_of_use();
        return annual_hours_standby;
    }
    
    float annual_kWh() const
    {
        float annual_KWH = ((annual_hours_of_use() * Consumer::get_watt()) + (annual_hours_of_standby() * watt_standby)) / 1000;
        return annual_KWH;
    }

    void print(int valu, float price) const override
    {
        cout << right << setw(global_column - 2) << valu
            << left << ": " << this->get_description() << "\n";
        cout << right << setw(global_column) << "(this: "
            << left << this << " )\n";
        cout << right << setw(global_column) << "power consumption: "
            << left << this->get_watt() << " w\n";
        cout << right << setw(global_column) << "power consumption standby: "
            << left << this->get_watt_standby() << " w\n";
        cout << right << setw(global_column) << "annual hours of use: "
            << left << this->annual_hours_of_use() << " h\n";
        cout << right << setw(global_column) << "annual hours of standby: "
            << left << this->annual_hours_of_standby() << " h\n";
        cout << right << setw(global_column) << "annual consumption: " << annual_kWh() << " h" << endl;
        cout << right << setw(global_column) << "annual cost: " << annual_kWh() * price << " EUR" << endl;
    }
    
    virtual void input()
    {
        Device::input();
        cout << "Enter watt standby: ";
        cin >> watt_standby;
        cout << "How many hours: ";
        cin >> hours;
    }
    
    virtual Device* get_a_copy() const  override
    {
        Immobile* copy = new Immobile();
        *copy = *this;
        return copy;
    }

    virtual string get_string_for_file(char separator) const override
    {
        string use;

        switch (get_use())
        {
        case Use::once:
            use = "once";
            break;
        case Use::daily:
            use = "daily";
            break;
        case Use::mo_fr:
            use = "Monday to Friday";
            break;
        case Use::sa_su:
            use = "Saturday Sunday";
            break;
        case Use::weekly:
            use = "weekly";
            break;
        default:
            use = "";
        }

        string s = "Immobile";

        s += separator + get_description() + separator + to_string(get_watt()) +
            separator + use + separator + to_string(get_watt_standby()) +
            separator + to_string(get_hours());
        return s;
    }
};

class Mobile : public Consumer
{
private:
    float km;

public:
    Mobile(Device* ptr = nullptr) : Consumer(ptr) {}
    virtual ~Mobile()
    {
        cout << "Mobile " << this->get_description() << " at address " << this << " deleted" << endl;
    }
    float get_km() const
    {
        return km;
    }
    void set_km(float set_KM)
    {
        km = set_KM;
    }
    virtual void input()
    {
        Consumer::input();
        cout << "how many km will be driven? ";
        cin >> km;
    }

    float annual_hours_of_use() const
    {
        switch (this->get_use())
        {
        case Use::once: return 1;
        case Use::daily: return 365;
        case Use::mo_fr: return 260;
        case Use::sa_su: return 104;
        case Use::weekly: return 52;
        default: return 0;
        }
    }

    float annual_kWh() const override
    {
        return (get_watt() * get_km() * annual_hours_of_use()) / 100000.0;
    }

    virtual Device* get_a_copy() const override
    {
        Mobile* copy = new Mobile();
        *copy = *this;
        return copy;
    }
    virtual string get_string_for_file(char separator) const override
    {
        string useStr;

        switch (get_use())
        {
        case Use::once:
            useStr = "once";
            break;
        case Use::daily:
            useStr = "daily";
            break;
        case Use::mo_fr:
            useStr = "Monday to Friday";
            break;
        case Use::sa_su:
            useStr = "Saturday Sunday";
            break;
        case Use::weekly:
            useStr = "weekly";
            break;
        default:
            useStr = "";
        }

        string s = "Mobile";
        s += separator + get_description() + separator + to_string(get_km()) +
            separator + useStr + separator + to_string(this->get_watt());
        return s;
    }

    void print(int number, float pricePerKWh) const override
    {
        cout << right << setw(global_column - 2) << number
            << left << ": " << get_description() << endl;
        cout << right << setw(global_column) << "(this: "
            << left << this << "\n";
        cout << right << setw(global_column) << "power consumption 100 Km: "
            << left << this->get_watt() / 1000 << " KW\n";
        cout << right << setw(global_column) << "Km driven: "
            << left << this->get_km() << "Km " << get_use() << endl;
        cout << right << setw(global_column) << "annual consumption: "
            << left << this->annual_kWh() << " h" << endl;
        cout << right << setw(global_column) << "annual cost: "
            << left << this->annual_kWh() * pricePerKWh << " EUR" << endl;
    }
};

class Producer : public Device
{
public:
    Producer(Device* ptr = nullptr) : Device(ptr) {}

    virtual ~Producer()
    {
        cout << "Producer " << this->get_description() << "at address " << this << " deleted " << endl;
    }

    void input() override
    {
        Device::input();
    }
};

class Solar : public Producer
{
private:
    float watt_peak;
    int year;

public:
    Solar(Device* ptr = nullptr) : Producer(ptr), watt_peak(0.0), year(0) {}

    virtual ~Solar()
    {
        cout << "Solar " << this->get_description() << " at address " << this << " deleted " << endl;
    }

    float get_watt_peak() const
    {
        return watt_peak;
    }
    int get_year() const
    {
        return year;
    }

    void set_watt_peak(float set_watt_Peak)
    {
        watt_peak = set_watt_Peak;
    }
    void set_year(int set_Year)
    {
        year = set_Year;
    }

    void input() override
    {
        Producer::input();
        cout << "how many watt peak have been installed? ";
        cin >> watt_peak;
        cout << "in which year the solar modules are installed? ";
        cin >> year;
    }

    virtual float annual_kWh() const override
    {
        int currentYear = 2024;
        float agingFactor = 1.0 - (0.005 * (currentYear - year));
        return -watt_peak * agingFactor;
    }

    void print(int deviceNumber, float pricePerKWh) const override
    {
        cout << right << setw(global_column - 2) << deviceNumber
            << left << ": " << this->get_description() << endl;
        cout << right << setw(global_column) << "(this: "
            << left << this << "\n";
        cout << right << setw(global_column) << "solar cells installed power: "
            << left << get_watt_peak() << " watt_peak " << endl;
        int currentYear = 2024;
        int age = currentYear - year;
        cout << right << setw(global_column) << "age of solar cells: "
            << left << to_string(age) << " years " << endl;
        float annualGeneration = this->annual_kWh();
        float costsSaved = annualGeneration * pricePerKWh;
        cout << right << setw(global_column) << "annual production: "
            << left << annualGeneration << " kWh" << endl;
        cout << right << setw(global_column) << "annual savings: "
            << left << costsSaved << " EUR" << endl;
    }

    Device* get_a_copy() const override
    {
        Solar* copy = new Solar();
        *copy = *this;
        return copy;
    }

    virtual string get_string_for_file(char separator) const override
    {
        string s = "Solar";
        s += separator + get_description() + separator + to_string(get_year()) +
            separator + to_string(get_watt_peak());
        return s;
    }

};

class Household
{
private:
    string name_of_city;
    int number_of_sq;
    int number_of_person;
    Device* device_head;
    bool heater;
    float Power_price;
    string Power_supplier;

public:
    Household() : device_head(nullptr) {}
    ~Household()
    {
        Device* currentDevice = device_head;
        while (currentDevice != nullptr)
        {
            Device* nextDevice = currentDevice->get_next();
            delete currentDevice;
            currentDevice = nextDevice;
        }
        cout << "Household at address " << this << " deleted" << endl; 
    }

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
    void set_Device_head(Device* set_Device_head)
    {
        device_head = set_Device_head;
    }
    void set_heater(bool heater_Y_N)
    {
        heater = heater_Y_N;
    }
    void set_Price(float Price)
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
    Device* get_Device_head() const
    {
        return device_head;
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

    void add_Device_to_household(Household* house_hold, Device* add_Device);
    void add_device_to_household(Device* newdevice);
    Device* move_up(Device* Device_Head, int k);
    void print_household(Household* house, int);
    Household* copy_Device(Household* fromHouse, Household* toHouse);
    void input_household(Household* household);
};

void Household::add_device_to_household(Device* newdevice)
{
    if (!this->device_head)
    {
        this->device_head = newdevice;
    }
    else
    {
        Device* temp = this->device_head;
        while (temp->get_next()) temp = temp->get_next();
        temp->set_next(newdevice);
    }
}

//HouseHold Member Function Implementation
void Household::add_Device_to_household(Household* house_hold, Device* set_Device)
{
    if (!this->device_head)
    {
        this->device_head = set_Device;
    }
    else
    {
        set_Device->set_next(this->device_head);
        this->device_head = set_Device;
    }

    //device_head->set_next(house_hold->get_Device_head());
    //house_hold->set_Device_head(set_Device);
}
void Household::input_household(Household* household)
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
    household->set_Price(PricekWh);
    cout << "who is the power supplier? ";
    cin.ignore();
    getline(cin, PowerSupplierName);
    household->set_Power_supplier(PowerSupplierName);
    household->set_Device_head(nullptr);
}
void Household::print_household(Household* house, int number)
{

    string heaterStr = (house->get_heater()) ? "Yes" : "No";
    Device* temp = house->get_Device_head();
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
    cout << right << setw(global_column - 1) << "list of devices\n";
    cout << "----------------------------------------------------------------------\n";
    while (temp != nullptr)
    {
        total_power += temp->annual_kWh();
        temp->print(i, house->get_Price());
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
Device* Household::move_up(Device* Device_Head, int k)
{
    Device* current_head = Device_Head;
    if (k <= 1)
    {
        return current_head;
    }

    else
    {
        Device* current = current_head;
        Device* next_device = current->get_next();

        if (k == 2 && next_device != nullptr)
        {
            current->set_next(next_device->get_next());
            next_device->set_next(current_head);
            current_head = next_device;
            return current_head;
        }

        else
        {

            while (current != nullptr)
            {
                int i = 1;
                while (i < k - 2)
                {
                    if (current->get_next() == nullptr)
                    {
                        return current_head;
                    }
                    current = current->get_next();
                    i++;
                }

                if (current->get_next() == nullptr || current->get_next()->get_next() == nullptr)
                {
                    return current_head;
                }

                Device* kth_node = current->get_next()->get_next();
                current->get_next()->set_next(kth_node->get_next());
                kth_node->set_next(current->get_next());
                current->set_next(kth_node);

                return current_head;
            }

        }
    }
}
Household* Household::copy_Device(Household* fromHouse, Household* toHouse)
{
    if (fromHouse->get_Device_head() == nullptr)
    {
        return toHouse;
    }
    Device* fromHouseConsumer = fromHouse->get_Device_head();
    Device* House2Consumer = toHouse->get_Device_head();
    Device* tempHead = nullptr;
    Device* tempTail = nullptr;
    while (fromHouseConsumer != nullptr)
    {
        Device* FromConsumer = fromHouseConsumer->get_a_copy();

        FromConsumer->set_next(nullptr);

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
    tempTail->set_next(toHouse->get_Device_head());
    toHouse->set_Device_head(tempHead);
    return toHouse;
}
class House
{
private:
    int number_of_households;
    Household** household;
    Address address;

public:
    House(int num, const Address& ad) : number_of_households(num), address(ad)
    {
        household = new Household * [number_of_households];
        for (int i = 0; i < number_of_households; ++i)
        {
            household[i] = nullptr;
        }
    }
    ~House()
    {
        for (int i = 0; i < number_of_households; i++)
        {
            delete household[i];
        }

        cout << "House at address " << this << " deleted\n";
        delete[] household;
    }
    Address get_Address() const
    {
        return address;
    }

    void set_household(int num, Household* house_set)
    {
        household[num] = house_set;
    }
    Household* get_household(int num)
    {
        return household[num];
    }
    Household* operator[](int n) 
    {
        return this->household[n];
    }
    int getNumberHouse()
    {
        return number_of_households;
    }

    void print_all(Household*, int);
    House* readDataFromFile(string, char);
    void WriteDataIntoFile(string,char);
};

Use readfrequencyofuse(string curr)
{
    if (curr == "once")
        return Use::once;
    else if (curr == "daily")
        return Use::daily;
    else if (curr == "Monday to Friday")
        return Use::mo_fr;
    else if (curr == "Saturday and Sunday")
        return Use::sa_su;
    else
        return Use::weekly;
}

House* House::readDataFromFile(string ReadfileName, char separator_character_read) 
{
    string assignment_no, readStreet, redHouseNo, readZip, readCity, readPrice, read_no_of_household, unKnowData, power_company;
    string Description;
    ifstream read_File(ReadfileName);

    if (read_File.is_open()) 
    {
        cout << "input file " << ReadfileName << " opened..." << endl;

        getline(read_File, assignment_no, separator_character_read) &&
        getline(read_File, read_no_of_household, separator_character_read) &&
        getline(read_File, readStreet, separator_character_read) &&
        getline(read_File, redHouseNo, separator_character_read) &&
        getline(read_File, readZip, separator_character_read) &&
        getline(read_File, readCity);

        Address houseAddress;
        houseAddress.input(readStreet, redHouseNo, readZip, readCity);
        House* readhouse = new House(stoi(read_no_of_household), houseAddress);

        readhouse->household = new Household*[stoi(read_no_of_household)];

        for (int i = 0; i < stoi(read_no_of_household); i++) 
        {
            readhouse->household[i] = nullptr;
        }

        while (!read_File.eof()) 
        {
            int house_hold_no;
            string household_or_consumer, read_household_no, read_person, read_city_name, read_heater, read_Sq;
            getline(read_File, household_or_consumer, separator_character_read);

            if (household_or_consumer == "Household") 
            {
                getline(read_File, read_household_no, separator_character_read);
                house_hold_no = stoi(read_household_no);
                Household* housHold = new Household;

                housHold->set_Device_head(nullptr);
                getline(read_File, read_heater, separator_character_read);
                housHold->set_heater((read_heater == "true" ? true : false));
                getline(read_File, read_person, separator_character_read);
                housHold->set_number_of_person(stoi(read_person));
                getline(read_File, read_Sq, separator_character_read);
                housHold->set_number_of_sq(stoi(read_Sq));
                getline(read_File, readPrice, separator_character_read);
                housHold->set_Price(stof(readPrice));
                getline(read_File, power_company);
                housHold->set_Power_supplier(power_company);

                readhouse->household[house_hold_no] = housHold;
            }
            else if (household_or_consumer == "Immobile") 
            {
                string description, frequency,watt, watt_standby, hour;

                if (readhouse->household[house_hold_no] != nullptr) 
                {
                    Immobile* consumer = new Immobile;
                    getline(read_File, description, separator_character_read);
                    consumer->set_description(description);
                     getline(read_File, hour, separator_character_read);
                    
                    consumer->set_hours(stof(hour));
                    getline(read_File, frequency, separator_character_read);
                   consumer->set_use(readfrequencyofuse(frequency));
                     getline(read_File, watt, separator_character_read);
                    consumer->set_watt(stof(watt));
                    getline(read_File, watt_standby);
                    consumer->set_watt_standby(stof(watt_standby));

                    readhouse->household[house_hold_no]->add_device_to_household(consumer);
                }
            }
            else if (household_or_consumer == "Mobile") 
            {
                string Description, frequency, read_watt, Km;

                if (readhouse->household[house_hold_no] != nullptr) 
                {
                    Mobile* new_mobile = new Mobile();
                    getline(read_File, Description, separator_character_read);
                    new_mobile->set_description(Description);
                    getline(read_File, Km, separator_character_read);
                    new_mobile->set_km(stof(Km));
                    getline(read_File, frequency, separator_character_read);
                    new_mobile->set_use(readfrequencyofuse(frequency));
                    getline(read_File, read_watt);
                    new_mobile->set_watt(stof(read_watt));

                    readhouse->household[house_hold_no]->add_device_to_household(new_mobile);
                }
            }
            else if (household_or_consumer == "Solar") 
            {
                string supplier,year,peakwatt;
                
                Solar* new_producer = new Solar;

                if (readhouse->household[house_hold_no] != nullptr) 
                {
                    getline(read_File, supplier, separator_character_read);
                    new_producer->set_description(supplier);
                    getline(read_File, year, separator_character_read);
                    new_producer->set_year(stoi(year));
                     getline(read_File, peakwatt);
                    new_producer->set_watt_peak(stod(peakwatt));

                    readhouse->household[house_hold_no]->add_device_to_household(new_producer);
                }
            }
            
        }

        return readhouse;
    }
     
    read_File.close();
     cout << "input file " << ReadfileName << " closed" << endl;
       
    
}

void House::WriteDataIntoFile(string fname, char sep)
{
    ofstream fout(fname);

    cout << "output file " << fname << " opened...\n";

    //first line
    fout << "A6" << sep << this->number_of_households << sep << address.get_Street() << sep << address.get_Street_No() << sep << address.get_Zip_Code() << sep << address.get_City() << '\n';

    // iterate through each household
    for (int i = 0; i < this->number_of_households; i++)
    {
        // check if the household exists
        if (this->household[i])
        {
            // write household information to the file
            fout << "Household" << sep << to_string(i) << sep;
            if (this->household[i]->get_heater())
                fout << "true";
            else
                fout << "false";
            fout << sep << to_string(this->household[i]->get_number_of_person()) << sep << to_string(this->household[i]->get_Number_of_sq()) << sep;
            fout << to_string(this->household[i]->get_Price()) << sep << this->household[i]->get_Power_supplier() << '\n';

            // iterate through each device in the household
            Device* curr = this->household[i]->get_Device_head();
            while (curr)
            {
                fout << curr->get_string_for_file(sep) << '\n';
                curr->set_next(curr->get_next());
                curr = curr->get_next();
            }
        }
    }

    // close the output file
    cout << "output file " << fname << " closed...\n";
    fout.close();
}

void House::print_all(Household* house, int i)
{
    house->print_household(house, i);
}

int main()
{
    House* house1 = nullptr;
    cout << "\nCALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION WITH INHERITANCE" << endl;
    while (true)
    {
        cout << "q quit\nd delete house\nh house initialisation\ni input power consumer" << endl
            << "m input mobile consumer\ns input solar producer\n"
            << "u move up power consumer\np print household\na print all households" << endl
            << "n new household\nc copy all consumers (added to already existing ones)" << endl
            << "r read data from file\nw write data into file\n>> ";
        char ch;
        cin >> ch;
        switch (ch)
        {
        case 'w':
        {
            string filename;
            char separator;
            cout << "output file name: ";
            cin >> filename;
            cout << "output separator character: ";
            cin >> separator;
            house1->WriteDataIntoFile(filename, separator);
            break;
        }
        case 'r':
        {
            string filename;
            char separator;
            cout << "input file name: ";
            cin >> filename;
            cout << "input separator character: ";
            cin >> separator;
            house1 = house1->readDataFromFile(filename, separator);
            cout << "input file " << filename << " closed...\n";
            break;
        }
        case 'u':
        {
            int k, num;
            cout << "number of household? ";
            cin >> num;
            cout << "which one? ";
            cin >> k;
            Household* h = house1->get_household(num);
            h->move_up(h->get_Device_head(), k);
            break;
        }
        case 'c':
        {
            int num1, num2;
            cout << "number of household from which to copy devices? ";
            cin >> num1;
            cout << "number of household to copy to? ";
            cin >> num2;
            Household* h1 = house1->get_household(num1);
            Household* h2 = house1->get_household(num2);

            if (h1 && h2)
            {
                h2 = h2->copy_Device(h1,h2);
            }
            break;
        }
        case 'd':
        {
            house1->~House();
            house1 = nullptr;
            break;
        }
        case 'm':
        {
            int num;
            cout << "number of household?";
            cin >> num;
            Consumer* new_mobile = new Mobile();
            new_mobile->input();
            house1->get_household(num)->add_Device_to_household(house1->get_household(num), new_mobile);
            break;
        }
        case 's':
        {
            int num;
            cout << "number of household?";
            cin >> num;

            Solar* new_producer = new Solar;
            new_producer->input();

            house1->get_household(num)->add_Device_to_household(house1->get_household(num), new_producer);

            break;
        }
        case 'i':
        {
            int num_of_household;
            cout << "number of household ? ";
            cin >> num_of_household;
            if (num_of_household >= 0)
            {
                string Description;
                float WATT, WATT_STANDBY, HOUR;
                Immobile* newImmobile = new Immobile;
                newImmobile->input();
                house1->get_household(num_of_household)->add_Device_to_household(house1->get_household(num_of_household), newImmobile);
            }
            else
                cout << "Household does not exist";
            break;
        }

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
                Household* housHold = new Household;
                housHold->set_Device_head(nullptr);
                house1->set_household(num, housHold);
                house1->get_household(num)->input_household(house1->get_household(num));
            }
            else
                cout << "Household already exist\n";
            break;
        case 'a':
            if (house1 != nullptr)
            {
                control_print = false;
                cout << "======================================================================" << endl
                    << "                             H O U S E                                " << endl
                    << "======================================================================" << endl;
                cout << right << setw(global_column) << "(this: "
                    << left << house1 << ")\n";
                cout << right << setw(global_column) << "address: "
                    << left << house1->get_Address().to_string() << "\n";
                cout << right << setw(global_column) << "number of households: "
                    << left << house1->getNumberHouse() << "\n";
                cout << right << setw(global_column) << "total number of all consumers: "
                    << left << Consumer::get_total_consumer() << "\n";

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
                cout << "house is a nullptr, please first choose h to initialise a new house or r to read from file" << endl;
            control_print = true;
            break;

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
            Address* temp_address = new Address;
            temp_address->input(str, str_no, zip_c, city_nam);
            full_address = temp_address->to_string();
            Address houseAddress;
            houseAddress.input(str, str_no, zip_c, city_nam);
            House* house = new House(num_house, houseAddress);
            house1 = house;
            delete temp_address;
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
