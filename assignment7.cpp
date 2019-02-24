#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <memory>
using namespace std;
class String
{
	char* ptr;
	int size;

	int* count;//no of shared objects
	void dispose() {
        if (--*count == 0) {
             delete count;
             delete [] ptr;
        }
    }
public:
	//constructor
	String(int k=0,char c='\0')
	{
		size=k;
		if(k!=0)
		{
			ptr=new char[k+1];
			ptr[k]='\0';
			for (int i = 0; i < size; ++i)
			{
				ptr[i]=c;
			}
		}
		else
			ptr=NULL;
		count=new int(1);
		*count=1;
	}
	//copy constructor
	String(const String &a)
	{
		size=a.size;
		if(size!=0)
		{
			ptr=new char[size];
			for (int i = 0; i < size; ++i)
			{
				ptr[i]=a.ptr[i];
			}
		}
		else
			ptr=NULL;

		count=a.count;
		*count++;
	}
	//assignment
	String & operator=( String& s)//String &s= c;
	{
		cout<<"hello"<<endl;
		if (this != &s) {
            dispose();
            size=s.size;
			if(size==0)
			{
				ptr=NULL;
			}
			else
			{
				ptr=new char[size+1];
				ptr[size]='\0';
				for (int i = 0; i < size; ++i)
				{
					ptr[i]=s.ptr[i];
				}
			}
            count = s.count;
            ++*count;
            cout<<*count<<endl;
		}
        return *this;
	}
	//input
	friend istream& operator>>(istream &is, String &s)//cin>>s;
	{
		char ch;
		cout<<"Enter the length of the string\n";
		is>>s.size;
		char * a=new char[s.size+1];
		a[s.size]='\0';
		cout<<"Enter the string\n";
		for (int i = 0; i < s.size; ++i)
		{
			cin>>ch;
			a[i]=ch;
		}
		s.ptr=a;
		return is;
	}
	//output
	friend ostream& operator<<(ostream &os, String &s)//cout<<s;
	{
		cout<<"The string is\n";
		for(int i=0;i<s.size;i++)
			os<<s.ptr[i];
		int *a=s.count;
		cout<<"pointer points to address: "<<&(s.ptr)<<endl;
		cout<<"no of object sharing is: "<<*a<<endl;
		return os;
	}
	//return ith char in the string
	char operator [] (int i)//s[i]
	{
		if(i>size)
			cout<<"Wrong access point\n";
		else
			return ptr[i-1];
	}
	//concatenation
	String operator +(const String& t)
	{
		String res;
		int i;
		if(size==0 && t.size==0)
		{
			res.size=0;
			res.ptr=NULL;
		}
		else
		{
			res.size=size+t.size;
			res.ptr=new char[res.size];

			for (int i = 0; i < res.size; ++i)
			{
				if(i>=size)
				{
					res.ptr[i]=t.ptr[i-size];
				}
				else
					res.ptr[i]=ptr[i];
			}

		}
		return res;
	}

	int operator==(const String& b)
	{
		int r=1;
		if(size!=b.size)
			r=0;
		else
		{
			for (int i = 0; i < size; ++i)
			{
				if(ptr[i]!=b.ptr[i])
				{
					r=0;
					break;
				}
			}
		}
		return r;

	}
	int operator <(String &s)
	{
		
	}
	int operator >(String &s)
	{
		//return 1-(s<*this);
	} 
	~String()
	{
		dispose();
	}
};



int main()
{
	int c;
	int k;
	String s,d;
	while(1)
	{
		cout<<"Enter your choice\n1.To initialize string with size & enter the characters\n2.display\n3.initialize by present created object\n4.compare\n5.Concatenate\n6.reference\n0.exit\n";
		cin>>c;
		switch(c)
		{
			case 1:
			{
				cin>>s;
				break;
			}
			case 2:
			{
				cout<<"enter the position to display\n";
				cin>>k;
				cout<<s[k]<<endl;
				cout<<s<<endl;
				break;
			}
			case 3:
			{
				String ss=s;
				cout<<"initialized\n";
				cout<<ss<<endl;
				break;
			}
			case 4:
			{
				cout<<"Enter another string to compare with\n";
				cin>>d;
				cout<<(s==d)<<endl;
				break;
			}
			case 5:
			{
				cout<<"Enter another string to add:\n";
				cin>>d;
				String a=s+d;
				cout<<a;
				break;
			}
			case 6:
			{
			    String s1,s2,s3;
				s1=s;
				//s1.count;
				cout<<s1<<endl;
				
				s2=s;
				//s2.count;
				cout<<s2;
				s3=s;
				//s3.count;
				cout<<s2;
				cout<<s3;
				cout<<s3;
				break;
			}
			default:exit(0);
		}
	}
}