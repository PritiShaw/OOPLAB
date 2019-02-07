#include<iostream>
#include<string>
#include <algorithm>
using namespace std;
#define MaxList 100

bool compareString(string s1, string s2) 
{ 
    if((s1.compare(s2)) == 0) 
        return true; 
    else
        return false; 
} 

class itemList;

class item{
	private:
		string code;
		string name;
		int qty;
		float rate;
	public:
		int getdata(itemList& s);
		void showData(int choice){			
			switch(choice){
				case 0:{
					cout<<code<<"\t\t"<<name<<"\t\t"<<qty<<"\t\t"<<rate<<endl;
				}
				break;
				case 1:{
					cout<<code<<"\t\t"<<name<<endl;
				}
				break;
				case 2:{
					cout<<code<<"\t\t"<<qty<<endl;
				}
				break;
				case 3:{
					cout<<code<<"\t\t"<<rate<<endl;
				}
				break;
				case 4:{
					cout<<code<<"\t\t"<<name<<"\t\t"<<qty<<endl;
				}
			}
		};
        string getType(){
            return code.substr(0,3);
        }
        string getCode(){
            return code;
        };
        int getQuantity(){
            return qty;
        };
        float getPrice(){
        	return rate;
        }
        void updateName(string temp){
        	name = temp;
        };
        void updatePrice(float temp){
        	rate = temp;
        }        
        void updateQuantity(int temp){
        	qty = temp;
        };
        void updateStockQuantity(int temp){
        	qty += temp;
        };
};

class itemList
{
	private:
		int count = 0;


		item list[MaxList];
	public:
		int getCount(){
			return count;
		};
		string getItemType(int i){
			string temp = list[i].getType();
			return temp;
		};
        int addItem(item t){
            list[count++] = t;
            return count;
        };
        void showList(){
        	int i=0;
        	while(i<count){
        		cout<<(i+1)<<"\t";
        		list[i++].showData(0);
        	}
        }
        void UshowList(){
        	int i=0;
        	while(i<count){
        		cout<<(i+1)<<"\t";
        		list[i++].showData(1);
        	}
        }
        int search(string key){
        	int i=0;
        	while(i<count){
        		if(compareString(key,list[i].getCode())){
			    	return i;
		    	}
				i++;
            }

            return -1;
        };
        item getItem(int i,int quant){
        	int stockQuant =  list[i].getQuantity();
        	if(quant>stockQuant){
        		cout<<"Stock Insufficient\n";
        	}
        	else{
        		list[i].updateStockQuantity(-1*quant);
        		return list[i];
        	}
        	item temp;
        	return temp;	 
        }
        int showItemDetails(string key,int choice){
        	int i = search(key);
            if(i<0)
            	return 0; //error 
            cout<<(i+1)<<"\t";           
            list[i].showData(choice);
            return 1;
        }
        int update(string key){
        	int i = search(key);
            if(i<0)
            	return 0; //error
            int choice;
            cout<<"\n\nWhat Do You Want To Update? \n\n\t 1) Update Name\n\n\t 2) Rate\n\n\t 3) Quantity\n\nPlease Choose One option : \t";
            cin>>choice;
            switch(choice){
            	case 1:{
            		string tempName;
            		cout<<"\nEnter new name:\t";
            		getline(cin,tempName);
            		list[i].updateName(tempName);
            		cin.ignore();
            	}
            		break;
            	case 2:
            		{
            		float newPrice;
            		cout<<"\nEnter new price:\t";
            		cin>>newPrice;
            		list[i].updatePrice(newPrice);
            	}
            		break;
            	case 3:
            	{
            		int newQuant;
            		cout<<"\nEnter new quantity:\t";
            		cin>>newQuant;
            		list[i].updateQuantity(newQuant);
            	}
            		break;

            	default:{
            		cout<<"Enter valid option:\t";
            		cin>>choice;
            	}
            		break;
            }
            return 1;
        }
};
int item::getdata(itemList& s){
    cout<<"\nEnter the name of item:\t";
    getline(cin,name);
    while(name.length()<4) {        
        cout<<"\nEnter valid name of item:\t";
    	cin.ignore();
        getline(cin,name);
    }
	cout<<"\nEnter the Quantity:\t"; 
    
    cin>>qty;
	while(qty<1){      
        cout<<"\nEnter valid Quantity:\t";  
        cin>>qty;
    }
	cout<<"\nEnter the rate of item:\t";       
    cin>>rate;
    cin.ignore();
    while(rate<0){ 
        cout<<"\nEnter valid rate of item:\t";       
        cin>>rate;
    }
	string type=name.substr(0,3);    
    transform(type.begin(), type.end(), type.begin(), [](char ch) {
        return ch == ' ' ? '_' : ch;
    });
    transform(type.begin(), type.end(),type.begin(), ::toupper);
	int stockCount=s.getCount();
	if(stockCount>(MaxList-2)){
		cout<<"List is Full";
		return 0;
	}
	int i=0,counter=1;
	while(i<stockCount){
		if(compareString(type,s.getItemType(i))){
			counter++;
		}
		i++;
	}
	char counterString[4];
	snprintf(counterString,4,"%03d",counter);
	code=type+counterString;
	s.addItem(*this);
	return 1;
}
class order
{
	private:
		int count = 0;
		item list[MaxList];
	public:
		int showCart(){
			int i = 0;
			while(i<count){
				cout<<(i+1)<<"\t";
				list[i++].showData(4);
			}
		}
		int showList(){
			int i = 0;
			while(i<count){
				cout<<(i+1)<<"\t";
				list[i++].showData(0);
			}
			cout<<"\n\tTotal Price (including GST): \t"<<getBill()<<endl;
		}
		
		int getCount(){
			return count;
		};
		int search(string key){
			int i=0;
        	while(i<count){
        		if(compareString(key,list[i].getCode())){
			    	return i;
		    	}
				i++;
            }
            return -1;
		}		
		float getBill(){
			int i = 0;
			float tempPrice = 0;
			while(i<count){
				tempPrice += list[i].getPrice();
				i++;
			}
			return tempPrice;
		}
		int addItem(string key,itemList& s){
        	int i=search(key);
        	if(i>-1){
        		cout<<"Item already in list\n";
        		list[i].showData(0);
        		return -1;
        		// -1 -> already in list

        		cout<<"Do you want to update quantity?\n";
        		int choice;
        		cin>>choice;
        		if(choice==1){
        			//yes        	
	        		int si = s.search(key);
        			int quantity;
        			cout<<"Please enter quantity to add/subtract:\t";
        			cin>>quantity;
        			item temp = s.getItem(si,quantity);
        			quantity += temp.getQuantity();
        			temp.updateQuantity(quantity);
        			float price = temp.getPrice() * quantity;
        			temp.updatePrice(price);
        			list[i] = temp;
        		}	
        	}
        	else{
        		int si = s.search(key);
        		if(si>-1){ 
        			int quantity;
        			cout<<"Please enter quantity:\t";
        			cin>>quantity;
        			item temp = s.getItem(si,quantity);
        			temp.updateQuantity(quantity);
        			float price = temp.getPrice() * quantity;
        			temp.updatePrice(price);
        			list[count++] = temp;
        			cout<<"\nItem Successfully Added To Cart \n";
        		}
        		else{
        			cout<<"Item not found\n";
        			return 0;
        		}
        	}
        };
        int updateOrder(string key,itemList& s){ 
        	cout<<"Do you want to update quantity (1 or 0) ?\n";
        	int choice;
        	cin>>choice;
        	if(choice==1){    	
	        	int si = s.search(key);
        		int quantity;
        		cout<<"Please enter quantity to add/subtract:\t";
        		cin>>quantity;
        		// list[si].updateQuantity(baad me dekhte hai )
//        		item temp = s.getItem(si,quantity);
 //       		quantity += temp.getQuantity();
  //      		temp.updateQuantity(quantity);
   //     		float price = temp.getPrice() * quantity;
    //    		temp.updatePrice(price);
     //   		list[si] = temp;
            }
        }; 
};

int main(){

	itemList Stock;
	item temp;
	order bill;
	cout<<"\n\n\n\t\t\t\t****************WELCOME****************"<<endl<<endl;	
	while(1){
		cout<<"\t1.Login as a Admin "<<endl;
		cout<<"\t2.Login as a user "<<endl;
		int AOU,adminChoice,userChoice; 
		cout<<"\nPlease enter your choice(1 or 2) : ";
		cin>>AOU;
		switch(AOU){
			case 1:{
				string pass,password;
				password = "password";
				cout<<"Enter Password:\t";
				cin.ignore(); 
				getline(cin,pass);
				int flag = 0;
				if(compareString(pass,password)){
					flag = 1;
					cout<<"SUCCESSFUL"<<endl;
					cout<<"\n\tYOU ARE IN ADMIN MENU"<<endl;
				}
				else
					cout<<"OOPS!WRONG PASSWORD"<<endl;
				while(flag){
					cout<<"\n1. Add product to stock";					
					cout<<"\n2. Show Stock";
					cout<<"\n3. Update a product"; //add update price and update quantity here in case 3
					cout<<"\n4. Exit Application";
					cout<<"\n5. Exit From Admin Menu"<<endl;
					cout<<"\nPlease Enter your Choice: ";
					cin>>adminChoice;
					cout<<endl;
					cin.ignore();
					switch(adminChoice){
						case 1:{
							temp.getdata(Stock);
							break;
						}
						case 2:{
							cout<<"\n\nSL.NO\tItem Code\tItem Name\tQuantity\tRate"<<endl;
							cout<<"***************************************************************"<<endl;
							Stock.showList();
							break;
						}
						case 3:{
							string key;
							cout<<"Enter the Item code to update a item:";
							getline(cin,key);
							Stock.update(key);
							cout<<"\n\tDate Is Updated"<<endl;

						}
						case 4:{
							return 0;
						}
						case 5:{
							cout<<"\n\nExiting From Admin......"<<endl;
							cout<<"\n\n\t\tThank you\n";
							flag = 0;
							break;
						}
					}
		    	}
			}
			case 2:{
				cout<<"\n\n\tYou Are in User Menu "<<endl;
				int flag=1;
				while(flag){
					cout<<"\n\n\t\tMenu";
					cout<<"\n\t1. Show Available products ";
					cout<<"\n\t2. Know Price of a product";
					cout<<"\n\t3. Know Quantity of a product";
					cout<<"\n\t4. Add to Cart ";
					cout<<"\n\t5. Change Cart "; 
					cout<<"\n\t6. Show Cart ";
					cout<<"\n\t7. Generate Bill ";
					cout<<"\n\t8. Exit From User Menu"<<endl;
					cout<<"\nPlease Enter your Choice: ";
					cin>>userChoice;
					switch(userChoice){
						case 1:{
							cout<<"\n\nSL.No\tItem Code\tItem Name\t"<<endl;
							cout<<"*********************************************"<<endl;
							Stock.UshowList();
							break;

						}
						case 2:{
							string key;
							cout<<"Enter the Item code to Check Rate : ";
							cin.ignore();
							getline(cin,key);

							cout<<"\n\nSL.No\tItem Code\tItem Price\t"<<endl;
							cout<<"**********************************************"<<endl;
							Stock.showItemDetails(key,3);
							break;

						}
						case 3:{
							string key;
							cout<<"Enter the Item code to Check Quantity : ";
							cin.ignore();
							getline(cin,key);
							cout<<"\n\nSL.No\tItem Code\tQuantity\t"<<endl;
							cout<<"**********************************************"<<endl;
							Stock.showItemDetails(key,2);
							break;
						}
						case 4:{
							string key;
							cout<<"Enter the Item Code of an Item you want to add to cart :";
							cin.ignore();
							getline(cin,key);
							bill.addItem(key,Stock);
							break;
						}
						case 5:{
							string key;
							cout<<"Enter the Item Code of an Item you want to Update : ";
							cin.ignore();
							getline(cin,key);
							bill.updateOrder(key,Stock);
							break;
						}
						case 6:{
							cout<<"\nSL.No\tItem Code\tName\t\tQuantity\n";
							cout<<"*********************************************************"<<endl;
							bill.showCart();
							break;

						}
						case 7:{
							cout<<"\nSL.NO\tItem Code\tName\t\tQuantity\tPrice\n";
							cout<<"*********************************************************"<<endl;	
							bill.showList();
							cout<<"\tYour Bill Is Ready\n";
							cout<<"\n\nThank You\n";
							break;
						}
						case 8:{
							cout<<"\n\n\tExiting From User Menu ..........."<<endl;
							cout<<"\n\n\t\t\tTHANK YOU\n";
							flag=0;
							break;
						}
					}
				}

			}
		}
	}	
}