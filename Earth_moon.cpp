#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
const int LIM=20;
struct planet
{
    char name[LIM];
    double population;
    double g;
};

inline void eatline(){while(std::cin.get()!='\n')continue;}
const char * file="planet.dat";

int main()
{
    using namespace std;
    planet p1;
    cout<<fixed;

    fstream finout;
    finout.open(file,ios_base::in|ios_base::out|ios_base::binary);
    int ct=0;
    if(finout.is_open())
    {
        finout.seekg(0);
        cout<<"Here are the current contents of the "<<file<<" file:\n";
         while (finout.read((char *) &p1,sizeof p1))
        {
            cout<<ct++<<":  "<<setw(LIM)<<p1.name<<": " 
                     <<setprecision(0)<<setw(12)<<p1.population
                     <<setprecision(2)<<setw(6)<<p1.g<<endl;
        }
        if(finout.eof())
        {
            finout.clear();
        }
        else
        {
            cerr<<"Error in reading "<<file<<".\n";
            exit(EXIT_FAILURE);
        }
        
    }
    else
    {
        cerr<<file<<" could not be open--bye.\n";
        exit(EXIT_FAILURE);
    }
    
    cout<<"Enter the record number you wish change: ";
    long rec;
    cin>>rec;
    eatline();
    if(rec<0||rec>=ct)
    {
        cerr<<"Invalid record number--bye\n";
        exit(EXIT_FAILURE);
    }
    streampos place=rec*sizeof p1;
    finout.seekg(place);
    if(finout.fail())
    {
        cerr<<"Error on attempted seek\n";
        exit(EXIT_FAILURE);
    }

    finout.read((char *) &p1,sizeof p1);
    cout<<"Your selection:\n";
    cout<<ct++<<":  "<<setw(LIM)<<p1.name<<": " 
                     <<setprecision(0)<<setw(12)<<p1.population
                     <<setprecision(2)<<setw(6)<<p1.g<<endl;
    if(finout.eof())
    {
        finout.clear();
    }

    cout<<"Enter planet name: ";
    cin.get(p1.name,LIM);
    eatline();
    cout<<"Enter planet populaton: ";
    cin>>p1.population;
    cout<<"Enter planet gravity: ";
    cin>>p1.g;
    finout.seekp(place);
    finout.write((char *) &p1,sizeof p1)<<flush;
    if(finout.fail())
    {
        cerr<<"Error on attempted write\n";
        exit(EXIT_FAILURE);
    }

    ct=0;
    finout.seekg(0);
    cout<<"Here are the new contents of the "<<file<<" file:\n";
    while (finout.read((char *) &p1,sizeof p1))
    {
        cout<<ct++<<":  "<<setw(LIM)<<p1.name<<": " 
                     <<setprecision(0)<<setw(12)<<p1.population
                     <<setprecision(2)<<setw(6)<<p1.g<<endl;
    }
    finout.close();
    cout<<"Done.\n";
    return 0;
}
