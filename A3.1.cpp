#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Example Program Run 1 for 10 days and 12 quarter hours
const int number_of_days=10;
const int number_of_quater_hour=12;

//Example Program Run 2 for 365 days and 96 quarter hours
// const int number_of_days=365;
// const int number_of_quater_hour=96;
const float priceKwh=.3;
// 1 enum
enum Use 
{  
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    once,
    daily,
    mo_fr,
    sa_su   
};
// 2 function overloded binary operator <<
ostream& operator<<(ostream& o, const Use& use)
{
    switch (use) 
    {
        case monday:
            o << "Monday";
            break;
        case tuesday:
            o << "Tuesday";
            break;
        case wednesday:
            o << "Wednesday";
            break;
        case thursday:
            o << "Thursday";
            break;
        case friday:
            o << "Friday";
            break;
        case saturday:
            o << "Saturday";
            break;
        case sunday:
            o << "Sunday";
            break;
        case once:
            o << "once";
            break;
        case daily:
            o << "daily";
            break;
        case mo_fr:
            o << "Monday to Friday";
            break;
        case sa_su:
            o << "Saturday and Sunday";
            break;
    }
    return o;
}

// 3 overloaded unarry operator++
Use operator++(const Use& use_enum)
{
    switch (use_enum) 
    {
        case monday:
            return tuesday;
        case tuesday:
            return wednesday;
        case wednesday:
            return thursday;
        case thursday:
            return friday;
        case friday:
            return saturday;
        case saturday:
            return sunday;
        case sunday:
            return monday;
        default:
            return use_enum;
    }
}
  



// 4 input_use function
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
          case '0':
               use = monday;
               break;
          case '1':
               use = tuesday;
               break;
          case '2':
               use = wednesday;
               break;
          case '3':
               use = thursday;
               break;
          case '4':
               use = friday;
               break;
          case '5':
               use = saturday;
               break;
          case '6':
               use = sunday;
               break;
               
          default:
               
               cout << "Please enter a valid option  \n";
               input_use(name, use); 
               break;             
    }
}
// A3 6 structure year
struct year
{
    int Year;
    Use use_first_day;
    string unit_value;
    float floating_array [number_of_days][number_of_quater_hour];
};

// A3 7 function inline
 inline year& zeros(year &Struct_year)
{
    for(int i=0;i<number_of_days;i++)
    {
        for(int j=0;j<number_of_quater_hour;j++)
        {
            Struct_year.floating_array[i][j]=0.0;
        }
    }
    return Struct_year;
}
//extension part 2
inline year& ones(year &Struct_year)
{
    for(int i=0;i<number_of_days;i++)
    {
        for(int j=0;j<number_of_quater_hour;j++)
        {
            Struct_year.floating_array[i][j]=1.0;
        }
    }
    return Struct_year;
}


 // A3 8 function inline time
 inline int time(int hour,int minute)
 {
    return (hour*60+minute);
 }


//A3 9 overloded binary operator<<
ostream& operator<<(ostream& o, const year& Struct_year)
{     
    Use day=Struct_year.use_first_day;
    o<<"year: "<<Struct_year.Year<<" (unit: "<<Struct_year.unit_value<<")"<<endl;
    for(int i=0;i<number_of_days;i++)
    {    
        int increm=0;
        o<<"day "<<i<<": "<< day<<endl;
        for(int j=0;j<number_of_quater_hour/4;j++)
        {    
            o<<" "<<j<<":00"<<"\t";
            for(int k=0;k<4;k++)
            {        
                o<< setw(6)<<fixed << setprecision(2) <<Struct_year.floating_array[i][increm] << right<<" \t";
                increm++;
            }
            o<<"\n";
        }
        o<<"\n";
        day=operator++(day);    
    }
    return o;
}


// A3 10 overloaded binary addition operator +
year& operator+(year& Total, const year& Actual)
{
     
    if ((Total.Year == Actual.Year) && (Total.use_first_day == Actual.use_first_day)&&(Total.unit_value==Actual.unit_value))
    {     
          year newYearSum;
          newYearSum.Year=Total.Year;
          newYearSum.unit_value=Total.unit_value;
          newYearSum.use_first_day=Total.use_first_day;
          
        for (int i = 0; i < number_of_days; i++)  
        {
            for (int j = 0; j < number_of_quater_hour; j++)
            {
                newYearSum.floating_array[i][j] = Total.floating_array[i][j];
            }
        } 
        for (int i = 0; i < number_of_days; i++)  
        {
            for (int j = 0; j < number_of_quater_hour; j++)
            {
                newYearSum.floating_array[i][j] += Actual.floating_array[i][j];
            }
        } 
        return newYearSum;
    }
    else
    return Total;
}
// extension A3 3 overloaded binary subtraction operator -
year& operator-(year& Total, const year& Actual)
{
     
    if ((Total.Year == Actual.Year) && (Total.use_first_day == Actual.use_first_day)&&(Total.unit_value==Actual.unit_value))
    {     
          year newYearSub;
          newYearSub.Year=Total.Year;
          newYearSub.unit_value=Total.unit_value;
          newYearSub.use_first_day=Total.use_first_day;
          
        for (int i = 0; i < number_of_days; i++)  
        {
            for (int j = 0; j < number_of_quater_hour; j++)
            {
                newYearSub.floating_array[i][j] = Total.floating_array[i][j];
            }
        } 
        for (int i = 0; i < number_of_days; i++)  
        {
            for (int j = 0; j < number_of_quater_hour; j++)
            {
                newYearSub.floating_array[i][j] -= Actual.floating_array[i][j];
            }
        } 
        return newYearSub;
    }
    else
    return Total;
}
// extension A3 3 overloaded binary subtraction operator -
year& operator*(float mul_val, year& Year_data)
{
     
     year newYearMul;
          newYearMul.Year=Year_data.Year;
          newYearMul.unit_value=Year_data.unit_value;
          newYearMul.use_first_day=Year_data.use_first_day;
          
        for (int i = 0; i < number_of_days; i++)  
        { 
            for (int j = 0; j < number_of_quater_hour; j++)
            {
               Year_data.floating_array[i][j]*= mul_val;
            }
        } 
        for (int i = 0; i < number_of_days; i++)  
        {
            for (int j = 0; j < number_of_quater_hour; j++)
            {
                newYearMul.floating_array[i][j] = Year_data.floating_array[i][j];
            }
        } 
        return newYearMul;
}

// extension 5 functionn set unit
void set_unit (year& year_data, char* unit_val) 
{
     year_data.unit_value = unit_val;
}

// 11 overloded function add_consumption day 

void add_consumption(year& Actual, int day_no, int from_minute, int to_minute, float wattage) 
{   
     float minute_of_consumption=wattage/60;
     int startQuarterHour = from_minute / 15;
     int startReminder=15-(from_minute%15);
     int endQuarterHour = (to_minute) / 15;
     int endReminder=(to_minute%15);
     int start_interval=startQuarterHour;
     if(startQuarterHour !=endQuarterHour)
     Actual.floating_array[day_no][startQuarterHour]+=startReminder*minute_of_consumption;
     
        for( start_interval+=1; start_interval<endQuarterHour;start_interval++)
        {
            Actual.floating_array[day_no][start_interval]+=15*minute_of_consumption;
        }

        if( startQuarterHour ==endQuarterHour) 
        Actual.floating_array[day_no][endQuarterHour] += endReminder * minute_of_consumption;
        else
        Actual.floating_array[day_no][endQuarterHour] += endReminder * minute_of_consumption;
}

//12 overloded function add_consumption enum
void add_consumption(year& Actual, Use use, int from_minute, int to_minute, float wattage) 
{   
    

        float minute_of_consumption = wattage / 60.0;  
        int startQuarterHouract = from_minute / 15;
        int startReminder = 15 - (from_minute % 15);
        int endQuarterHour = (to_minute) / 15;
        int endReminder = (to_minute % 15);
        
        for (int i = 0; i < number_of_days; ++i) 
        {
                if ((use== daily) || (use == mo_fr && ((Actual.use_first_day+i)%7 == monday || (Actual.use_first_day+i)%7 <= friday)) || 
                (use == sa_su && ((Actual.use_first_day+i)%7 == saturday ||(Actual.use_first_day+i)%7 == sunday))||(use==(Actual.use_first_day+i)%7)) 
            {
                int startQuarterHour = startQuarterHouract;
                if( startQuarterHouract !=endQuarterHour)
                Actual.floating_array[i][startQuarterHour] += startReminder * minute_of_consumption;

                for(startQuarterHour += 1; startQuarterHour < endQuarterHour; startQuarterHour++)
                {
                   Actual.floating_array[i][startQuarterHour] += 15 * minute_of_consumption;
                }

                if( startQuarterHouract!=endQuarterHour) 
                Actual.floating_array[i][endQuarterHour] += endReminder * minute_of_consumption;
                else
                Actual.floating_array[i][endQuarterHour] += (endReminder-(from_minute % 15)) * minute_of_consumption;
                
            }
        }
}

// 13 line function sum
inline float sum(year& y)
{
    float total_consumption=0;
    for(int i=0;i<number_of_days;i++)
    {
        for(int j=0;j<number_of_quater_hour;j++)
        {
            total_consumption+=y.floating_array[i][j];
        }
    }
    return total_consumption;

}

int main() 
{   
    year actual={2024,monday,"Watt"};
    year total={2024,monday,"Watt"}; 
    actual=zeros(actual);
    total=zeros(total);
    cout<<"YEARLY CONSUMPTION QUARTER HOUR"<<endl;
    
    while (true) 
    {
       cout << "q quit\na add actual to total (using operator +)\nm subtract actual from total (using operator -)" << endl
             << "s scalar multiplication" << endl
             << "c change unit\nv sum up values\no output actual (using operator <<)" << endl
             << "t output total (using operator <<)\nu add consumption according to frequency of use (call functions add_consumption)" << endl
             << "y set actual to ones (call function ones)" << endl
             << "z set actual to zeros (call function zeros)\n>> ";
         char ch;
        cin >> ch;
        switch (ch) 
          {
               case 'q':
                    exit(0);
                    break;
               case 'o':
                    cout<<actual<<endl;
                    break;
               case 'z':
                    actual=zeros(actual);
                    break;
               case 'u':
                    int from_min_value,to_min_value,day;
                    char colon; 
                    int hour,minute;
                    float watt_val;
                    Use use;
                    input_use("how often it will be used?\nMonday    (0)\nTuesday   (1)\nWednesday (2)\nThursday  (3)\nFriday    (4)\nSaturday  (5)\nSunday    (6)\ndaily     (d)\nmo_fr     (m)\nonce      (o)\nsa_su     (s)?\n", use);
                    if(use==once)
                    {    
                        cout<<"on which day? ";
                        cin>>day;
                    }
                    cout<<"from hour:minute? ";
                    cin >> setw(2) >> hour >> colon >> setw(2) >> minute;
                    from_min_value=time(hour,minute);
                    cout<<"to hour:minute? ";
                    cin >> setw(2) >> hour >> colon >> setw(2) >> minute;
                    to_min_value=time(hour,minute);
                    cout<<"how many watt it will have? ";
                    cin>>watt_val;
                    if(use==once)
                    add_consumption(actual,day, from_min_value, to_min_value, watt_val);
                    else
                    add_consumption(actual,use, from_min_value, to_min_value, watt_val);
                    
                    break;
               case 'a':
                    total= operator+(total,actual);
                    break;
               case 't':
                    cout<<total<<endl;
                    break;
               case 'v':
                    cout<<"sum actual = "<< sum(actual) <<" " <<actual.unit_value<<endl;
                    cout<<"sum total = "<< sum(total)<<" " <<total.unit_value<<endl;
                    break;
               case 'm':
                    total=(total-actual);
                    break;
               case 's':
                    char userInput;
                    float scalar_val;
                    cout<<"a for actual\nt for total\n";
                    cin>>userInput;
                    cout<<"value of scalar? ";
                    cin>>scalar_val;
                    if(userInput=='a')
                    {
                         actual=(scalar_val*actual);
                    }
                    else
                    total=(scalar_val*total);
                    break;
               case 'c':
                    char units[10];
                    char userinput;
                    cout<<"a for actual\nt for total\n";
                    cin>>userinput;
                    cout<<"what is the new unit? ";
                    cin>>units;
                    if(userinput=='a')
                    {
                         set_unit(actual,units);
                    }
                    else
                    set_unit(total,units);
                    break;
               case 'y':
                    actual=ones(actual);
                    break;
               default:
                    cout<<"Please enter a valid option q , c, o, t , u or z\n";
          }
     }
    return 0;
}

