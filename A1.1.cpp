//CALCULATION-OF-AVERAGE-POWER-COSTS-FOR-A-HOUSE//

#include<iostream>
#include<string>
using namespace std;
//1  Define three global integer constant variables for the three annual average consumption values above.
const int ave_con_per_person=200;
const int ave_con_per_squ=9;
const int ave_con_per_ele_dev=200;
const int Heater=550;//extension 1

//2 Define a structure called household with the following components:

struct household
{
    string Name_of_city;
    int number_of_person;
    int number_of_sq;
    int number_of_ele_dev;
    bool Hot_water;//extension 2
};

//3 function the annual power consumption

float the_annual_power_consumption(household *House)
{
    float total_power_consumption;

    total_power_consumption=(House->number_of_person * ave_con_per_person)
    +(House->number_of_sq * ave_con_per_squ)
    +(House->number_of_ele_dev * ave_con_per_ele_dev);

    if(House->Hot_water)//extension 3
    {
        total_power_consumption=(House->number_of_person * Heater)
        +(House->number_of_sq * ave_con_per_squ)
        +(House->number_of_ele_dev * ave_con_per_ele_dev);
    }

    return total_power_consumption;


}

// 4 function the annual power costs

float the_annual_power_cost(household * House,float price)
{
    
    return (the_annual_power_consumption(House) * price);

}

// 5 function print household

void print_household(household * House,float prices)
{
     string Yes_No="No";
     if(House->Hot_water)
     {
          Yes_No="Yes";
     }
    cout<<"AVERAGE POWER COSTS\n===================\n";
    cout<<"household in:                   "<<House->Name_of_city<<"\n";
    cout<<"square metres:                  "<<House->number_of_sq<<"\n";
    cout<<"persons:                        "<<House->number_of_person<<"\n";
    cout<<"(major) electrical devices:     "<<House->number_of_ele_dev<<"\n";
    cout<<"water heated using electricity: "<<Yes_No<<"\n";//extension 4
    cout<<"price for one KWH:              "<<prices<<" EUR \n";
    cout<<"annual power consumption:       "<<the_annual_power_consumption(House)<<" kWh\n";
    cout<<"annual power costs:             "<<the_annual_power_cost(House,prices)<<" EUR\n";
}
//extension 5
void input_city(string& name_of_city)
{
    cout<<"in which city is the household located? ";
    cin>>name_of_city;
}
//extension 6
void input_integer(string prompt,int &integer_value)
{
    cout<<prompt;
    cin>>integer_value;
}
//extension 7
void input_electric_water_heating(bool& is_heater)
{   
    char in_put;
    cout<<"is hot water heated using electricity? (y(es) or n(o)) ";
    cin>>in_put;
    is_heater=(in_put=='y');
}

// 6 main function 
int main()
{   
    
    household *Household = new household ;
    cout<<"\nCALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD\n";
    input_city(Household->Name_of_city);
    input_integer("how many square metres does the household have?",Household->number_of_sq);
    input_integer("how many (major) electrical devices does the household have? ",Household->number_of_ele_dev);
    input_electric_water_heating(Household->Hot_water);
    for(int i=1;i<6;i++)
    {  
        float Price=.3;
        for(int j=1;j<=3;j++)
        {
            
            Household->number_of_person = i;
            print_household(Household,Price);
            cout<<"\n";
            Price +=0.05;
        }
    }
   
    return 0;
}
