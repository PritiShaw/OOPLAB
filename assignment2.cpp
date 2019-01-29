// USING CONSTRUCTOR AND OPERATOR OVERLOADING
#include <iostream>  //header file
#include<math.h>
#include<cstring>
using namespace std;  

// creating a class COMPLEX with data members real and imag and member functions getdata,Display
class COMPLEX{
	private:                  //private data members
		int real,imag;
	public:                   //public member functions 

		COMPLEX(int r=0,int i=0){  //constructor with 2 arguments  
			real=r;
			imag=i;
		}
	
		COMPLEX operator +(COMPLEX x){		//defining the - operator 
			COMPLEX temp;
			temp.real=real+x.real;
			temp.imag=imag+x.imag;
			return temp;
		}
		COMPLEX operator -(COMPLEX x){
			COMPLEX temp;
			temp.real=real-x.real;
			temp.imag=imag-x.imag;
			return temp;
		}
		
		friend ostream & operator << (ostream &out,COMPLEX &c);
		friend istream & operator >> (istream &in,COMPLEX &c);
}; // end of class COMPLEX

ostream & operator << (ostream &out,COMPLEX &c)
{
	cout<<c.real;
	if(c.imag<0){
		cout<<"-";
	}
	else 
		cout<<"+";
	cout<<fabs(c.imag)<<"i";
	return out;
}

istream & operator >> (istream &in,COMPLEX &c)
{
	string s;
	in>>s;
	c.real=0;
	c.imag=0;
	int flag=0,negative=0,negativei=0,num=0,tag=0;
	if(s[0]=='-'){
		s=s.substr(1,s.length());
		negative=1;
	}
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='+' || s[i]=='-'){
			flag=1;
			tag=1;
			if(s[i]=='-') negativei=1;
			num=0;
		}
		else if(s[i]=='i')
		{
			if(flag==0)
			{
				negativei=negative;
				c.imag=c.real;
				c.real=0;
			}
			break;
		}
		else 
		{
			if(flag==0)
			{
				num=num*pow(10,i)+(s[i]-48);
				c.real=num;
			}
			if(flag==1)
			{
				num=num*pow(10,i-tag-1)+s[i]-48;
				c.imag=num;
			}
		}
		if(negative==1)
			c.real=-1*c.real;
		if(negativei==1)
			c.imag=-1*c.imag;
	}
    return in;
}

int main(){
	//beginning of main function 
	COMPLEX c1,c2;
	cout<<"Enter the first complex number :";
	cin>>c1;
	cout<<"Complex number entered is : ";
	cout<<c1;
	int input;
    cout<<"\n\t\t\t--WELCOME--\n\n";
	while(1)
	{
    //cout<<"**********************************************************************************************************";
    cout<<"\n\tPlease Enter your choice :\t\t\t\n";
    cout<<"\t1.ADD A COMPLEX NUMBER\n";
    cout<<"\t2.SUBTRACT A COMPLEX NUMBER\n";
    cout<<"\t3.DISPLAY A COMPLEX NUMBER\n";
    cout<<"\t4.EXIT-------\n";
    //cout<<"***************************************************************************************\n";
    cin>>input;
    //switch case 
    switch(input){
      case 1:
        	cout<<"Enter a complex number :- ";
        	cin>>c2;ss
        	cout<<"Complex number after addition is: ";
        	c1=c1+c2; 
        	break;
      case 2:
            cout<<"Enter a complex number :- ";
        	cin>>c2;
        	cout<<"Complex number after subtraction is: ";
        	c1=c1-c2;
        	break;
      case 3:
           cout<<"Complex number is :"<<c1;
           break;
      case 4:
        cout<<"\nEXITING ...........\n";
        cout<<"\t\t\t\tThank you !!"<<endl<<"\t\t:)";
        break;
	}
  }
}
