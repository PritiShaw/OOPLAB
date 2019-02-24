#include<iostream>
#include<string>
#include<math.h>
using namespace std;
class STRING{
  char *c;
  int stringlength;
public:
  STRING ()
  {
    stringlength=0;
    //*c=NULL;
  }
  STRING( const STRING &object)
  {
    stringlength=object.stringlength;
    c=(char*)malloc((stringlength+1)*sizeof(char));
    for(int i=0;i<=stringlength;i++)
    c[i]=object.c[i];
  }
  STRING (string s)
  {
    stringlength=s.length();
    c=(char*)malloc((stringlength+1)*sizeof(char));
    for(int i=0;i<stringlength;i++)
    c[i]=s[i];
    c[stringlength]='\0';

  }
  STRING operator+(STRING str)
  {
    STRING s;
    s.stringlength=stringlength+str.stringlength;
    s.c=(char*)malloc((s.stringlength+1)*sizeof(char));
    for(int i=0;i<stringlength;i++)
    s.c[i]=c[i];
    for(int i=stringlength;i<s.stringlength;i++)
    s.c[i]=str.c[i-stringlength];
    return s;
  }

  char & operator [](int index)
  {
    if(index>=stringlength)
    {
      cout<<"Error! Invalid Index"<<endl;
    }
    else
    {
      return c[index];
    }
  }
  int retlength()
  {
    return stringlength;
  }
  friend istream & operator >> (istream &in,  STRING &obj);
  friend ostream & operator << (ostream &out,  STRING obj);
  friend bool operator >(STRING str1,STRING str2);
  friend bool operator <(STRING str1,STRING str2);

};
istream & operator >> (istream &in,  STRING &obj)
{
  string s;
  cin>>s;
  STRING mystring(s);
  obj=mystring;
  return in;
}
ostream & operator << (ostream &out,  STRING obj)
{
  for(int i=0;i<obj.stringlength;i++)
  cout<<obj.c[i];
  return out;
}
bool operator <(STRING str1,STRING str2)
{
  for(int i=0;i<min(str1.stringlength,str2.stringlength);i++)
  {
    if (str1.c[i]<str2.c[i])
     {
       return true;
     }
     if (str1.c[i]>str2.c[i])
      {
        return false;
      }
  }
  if(str1.stringlength>=str2.stringlength) return false;
  if(str1.stringlength<str2.stringlength) return true;
}
bool operator >(STRING str1,STRING str2)
{
  for(int i=0;i<min(str1.stringlength,str2.stringlength);i++)
  {
    if (str1.c[i]>str2.c[i])
     {
       return true;
     }
     if (str1.c[i]<str2.c[i])
      {
        return false;
      }
  }
  if(str1.stringlength>str2.stringlength) return true;
  if(str1.stringlength<=str2.stringlength) return false;
}

int main()
{
  STRING a;
  STRING b;
  cout<<"\t****************WELCOME*****************\n\n";
while(1){
  cout<<"1. Input a and b\n";
  cout<<"2. Concatinate a and b\n";
  cout<<"3. Compare a and b\n";
  cout<<"4. Access ith element"<<endl;
  cout<<"5. Exit"<<endl;
  int option;
  cin>>option;
  if(option==1){
    cout<<"Enter a ";
    cin>>a;
    cout<<"Enter b ";
    cin>>b;
  }
  if(option==2)
  {
    cout<<"String after Concatanation : " << a+b<<endl;
  }
  if(option==3)
  {
    int dect=0;
    if(a<b) {cout<<"String a is greater than string b "<<endl;dect=1;}
    if(a>b) {cout<<"String b is greater than string a "<<endl;dect=1;}
    if(dect==0)cout<<"Both the strings are equal"<<endl;
  }

  if(option==4)
  {
    cout<<"1. For ith elemnet of a "<<endl;
    cout<<"2. For ith elemnet of b "<<endl;
    int x;
    cin>>x;
    if(x==1)
    {
      int i;
    //  cin>>i;
      cout<<"Enter i "<<endl;cin>>i;
      cout<<i<<" th element :";
      cout<<a[i]<<endl;
    }
    if(x==2)
    {
      int i;

      cout<<"Enter i "<<endl;cin>>i;
      cout<<i<<" th element :";
      cout<<b[i]<<endl;
      b[i]='X';
      cout<<b[i]<<endl;
    }
  }
  if(option==5){
  	cout<<"Exiting ....... "<<endl;
  	break;
  }
  }
}
