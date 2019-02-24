#include<iostream>
#include<cmath>
using namespace std;

class array{
		int size;
		int *p;
	public :
		array(int n){
			size=n;
			p=(int *) malloc(size*sizeof(int));
			for(int i=0;i<size;i++)
				p[i]=0;
		}
		array(const array &object){
			size=object.size;
			p=(int *)malloc(size*sizeof(int));
			for(int i=0;i<size;i++)
				p[i]=object.p[i];
		}
		array(int *arr,int n){
			size=n;
			p=(int*)malloc(size*sizeof(int));
			for(int i=0;i<size;i++)
				p[i]=arr[i];
		}
		void displayArray(){
			for(int i=0;i<size;i++){
				cout<<p[i]<<" "<<endl;
			}
		}
		void insertArray(){
			cout<<"Enter "<<size<<" numbers : "<<endl;
			for(int i=0;i<size;i++){
				cin>>p[i];	
			}
		}
		array operator +(const array &object){
			array add(max(size,object.size));
			int loop= min(size,object.size);
			for(int i=0;i<loop;i++){
				add.p[i]=p[i]+object.p[i];
			}
			if(size>object.size){
				for(int i=loop;i<(max(size,object.size));i++){
					add.p[i]=p[i];
				}
			}
			else{
				for(int i=loop;i<(max(size,object.size));i++){
					add.p[i]=object.p[i];
			    }
			}
			return add;
		}
		array operator -(const array &object){
			array sub(max(size,object.size));
			int loop=min(size,object.size);
			for(int i=0;i<loop;i++){
				sub.p[i]=p[i]-object.p[i];
			}
			if(size>object.size){
				for(int i=loop;i<max(size,object.size);i++){
					sub.p[i]=p[i]-object.p[i];
				}
			}
			else{
				for(int i=loop;i<max(size,object.size);i++){
					sub.p[i]=object.p[i];
				}
			}
			return sub;
		}
		int operator [](int index){
			if(size<index){
				cout<<"ERROR !! INVALID INDEX ";
			}
			else
				return p[index];
		}
		  // p is a private member and int val is not a data member of class array thats why we are using friend function to access the private members of class array 
		array operator *(int val){
     		array mult(size);
      		for(int i=0;i<size;i++)
      		mult.p[i]=p[i]*val;
      		return mult;
    	}
    	friend array operator *(int val, array arr);
};
array operator *(int val, array arr){
	return val*arr;
}
int main(){
	int option;
	while(1){
		cout<<"1. Intialise Array A and B "<<endl;
		cout<<"2. Exit "<<endl;
		cin>>option;
		if(option == 1){
			int Asize=0,Bsize;
			cout<<"\nEnter the size of Array A :\t";
			cin>>Asize;
			array A(Asize);
			A.displayArray();
			cout<<"\nArray A has been Intialised by 0 .\n";
			cout<<"Insert numbers in Array A \n";
			A.insertArray();
			array copy(A);
			cout<<"\nCopy constructed array copy \n";
			copy.displayArray();
			cout<<"\nEnter the size of B :\n";
			cin>>Bsize;
			int arr[Bsize];
			cout<<"Enter the numbers in Array B :\n";
			for(int i=0;i<Bsize;i++){
				cin>>arr[i];
			}
			array B(arr,Bsize);
			B.displayArray();
			int flag=1;
			while(flag){
				cout<<"\n\n\t---------MENU--------\n";
				cout<<" 1. Add A to B"<<endl;
				cout<<" 2. Subtract A with B"<<endl;
				cout<<" 3. Multiply A with a constant Integer"<<endl;
				cout<<" 4. Multiply B with a constant Integer"<<endl;
				cout<<" 5. ith Element of A"<<endl;
				cout<<" 6. ith Element of B"<<endl;
				cout<<" 7. Exit"<<endl;
				int option1;
				cin>>option1;
				switch(option1){
					case 1:{
						A=A+B;
						A.displayArray();
						flag=1;
						break;
					}
					case 2:{
						A=A-B;
						A.displayArray();
						flag=1;
						break;
					}
					case 3:{
						int val;
						cout<<"\nEnter the number to Multiply : ";
						cin>>val;
						A=A*val;
						A.displayArray();
						flag=1;
						break;
					}
					case 4:{
						cout<<"Enter the number to Multiply : ";
						int val;
						cin>>val;
						A=B*val;
						A.displayArray();
						flag=1;
						break;
					}
					case 5:{
						cout<<"Enter the index :";
						int index;
						cin>>index;
						cout<<endl<<A[index]<<endl;
						flag=1;
						break;
					}
					case 6:{	
						cout<<"Enter the index :";
						int index;
						cin>>index;
						cout<<endl<<B[index]<<endl;
						flag=1;
						break;
					}
					case 7:{
						cout<<"Exiting....... ";
						flag=0;
						break;
					}
				}
			}
		}
		if(option == 2){
			cout<<"\n\n\t\tExiting............\n\n";
			break;
		}
	}
}
