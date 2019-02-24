#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<ctime>
#define MaxList 100
using namespace std;

bool compareString(string s1, string s2) 
{ 
    if((s1.compare(s2)) == 0) 
        return true; 
    else
        return false; 
} 
class date {
	private:
		int d;
		int m;
		int y;
		string datestamp;
	public:
		date(){
           time_t now = time(0);
           tm *systm = localtime(&now);
			d = systm->tm_mday;
			m = systm->tm_mon+1;
			y = systm->tm_year+1900;
			char dateString[11];
			snprintf(dateString,11,"%02d-%02d-%04d",d,m,y);
			datestamp = dateString;
		}
		string get(){
			return datestamp;
		}
};

class university;
class student {
	private:
		float gpa = -1;
		string name;
		string roll;
		string department;
		date admDate;
		int marks[5];
	public:
		//admDate.get()
		int getdata(university& u);
		void getmarks();
		void showData(int choice){
			switch(choice){
				case 0:{
					cout<<roll<<"\t\t"<<name<<"\t\t"<<department<<"\t\t"<<admDate.get()<<endl;
					break;
				}
				case 1:{
					cout<<"\t"<<roll<<"\t\t"<<name<<"\t\t"<<department<<endl;
					break;

				}
			}
		};
		string gettype(){
			return department.substr(0,3);
		};
		string getname(){
			return name;
		};
		string getroll(){
			return roll;
		};
		int sortMarks(int option=2){
			int i = 0;
			int totalMarks=0;
			while(i<5){
        		totalMarks += marks[i];
        		i++;
        	}
				float gpa=totalMarks/50;
				// if(9.1<= gpa && gpa >=10){
				// 	cout<<"\n\tGPA : S ";
				// }
				// else if(8.1<= gpa  && gpa >=9.0){
				// 	cout<<"\n\tGPA: A";
				// }
				// else if(7.1<= gpa && gpa >=8.0){
				// 	cout<<"\n\tGPA: B";
				// }
				// else if(6.1<= gpa && gpa >=7.0){
				// 	cout<<"\n\tGPA: C";
				// }
				// else if(5.1<= gpa && gpa >=6.0){
				// 	cout<<"\n\tGPA: D";
				// }
				// else if(4.1<= gpa && gpa >=5.0){
				// 	cout<<"\n\tGPA: E";
				// }
				// else if(4.0 > gpa){
				// 	cout<<"\n\tGPA: X";
				// }
				return totalMarks;
        if(option == 2) 
        	return gpa;
        else
        	return totalMarks;

		};
		int showMarks(int option = 0){
        	int i = 0;
        	char grade;
        	int totalMarks=0;
        	while(i<5){
        		totalMarks += marks[i];
        		if(option==1) {
        			cout<<endl;
        			if(marks[i]>90){
        				grade= 'S' ;
        				option==1;
        			}
        			else if(marks[i]>80){
        				grade= 'A';
        				option==1;
        			}
        			else if(marks[i]>70){
        				grade= 'B';
        				option==1;
        			}
        			else if(marks[i]>60){
        				grade= 'C';
        				option==1;
        			}
        			else if(marks[i]>50){
        				grade= 'D';
        				option==1;
        			}
        			else if(marks[i]>40){
        				grade= 'E';
        				option==1;
        			}
        			else{
        				grade= 'X';
        				option==1;
        			}
					cout<<"Subject "<<i+1<<":\t"<<marks[i]<<"\t"<<grade<<"\n";
        			i++;
        		}
        	}
					cout<<"\nTotal Marks = "<<totalMarks;
					float gpa=totalMarks/50;
					if(9.1<= gpa && gpa >=10){
						cout<<"\n\tGPA : S \n";
					}
					else if(8.1<= gpa  && gpa >=9.0){
						cout<<"\n\tGPA: A\n";
					}
					else if(7.1<= gpa && gpa >=8.0){
						cout<<"\n\tGPA: B\n";
					}
					else if(6.1<= gpa && gpa >=7.0){
						cout<<"\n\tGPA: C\n";
					}
					else if(5.1<= gpa && gpa >=6.0){
						cout<<"\n\tGPA: D\n";
					}
					else if(4.1<= gpa && gpa >=5.0){
						cout<<"\n\tGPA: E\n";
					}
					else if(4.0 > gpa){
						cout<<"\n\tGPA: X\n";
					}
					return totalMarks;
        	if(option == 2) 
        		return gpa;
        	else
        		return totalMarks;
        	if(gpa < 4.0){
        		cout<<"\n\t\tRemarks: Failed :( \n";
        	}
        	else
        		cout<<"Remarks : Passed :) \n";
        }
        void showMarkSheet(){
        	if(gpa==-1){
        		cout<<"Marks not yet entered.\n";
        		return;
        	}
        	showMarks(1);
        };
        bool operator <(student& s) {
        	//if(gpa==-1) cout<<"Marks not yet entered for "<<roll <<endl;
        	return (this->sortMarks() > s.sortMarks());
        };  
 };
//list[i].showMarks()
class university{
	private:
		int count=0;
		student list[MaxList];
	public:
		int incremnetCount(){
			count++;
		}
        void showTopper(){
        	uSort();
        	list[0].showData(1);
        }
		int getcount(){
			return count;
		}
		string rolltype(int i){
			string temp=list[i].gettype();
			return temp;
		}

		void showAllStudent(int department = 0){
        	int i=0;
        	int flag = 0;
        	string dept;
        	switch(department){
        		default:
        			flag = 1;
        			break;
        		case 1:
        			dept = "CSE";
        			break;
        		case 2:
        			dept = "ETCE";
        			break;
        		case 3:
        			dept = "CE";
        			break;
        	}
        	while(i<count){
        		if(flag) 
        			list[i++].showData(0);
        		else{
        			if(compareString(dept,list[i].gettype()))
        				list[i++].showData(0);
        		}
        	}
        };
        int admCount(){
			return count;
		}
		void uSort(){
			sort(list,list+count);
		};
		student& getStudentmarks(string key){
			int i = search(key);
			//
			// if(i<0) return nullptr;
			return list[i];
		}
        int Marksheet(string key){
        	int i=search(key);
        	if(i<0){
        		cout<<"Roll not found\n";
        		return -1;
        	}
        	list[i].showMarkSheet();
        }
        int addStudent(student& s){
        	student temp;
        	list[count++] = s;
        	return 1;
        }
        int search(string key){
        	int i=0;
        	while(i<count){
        		if(compareString(key,list[i].getroll())){
			    	return i;
		    	}
				i++;
            }

            return -1;
        };
        int updateStudent(int i,student& s){
        	list[i] = s;
        	return 1;
        }
        int showStudentDetails(string key,int choice){
        	int i = search(key);
            if(i<0)
            	return 0; //error 
           // cout<<(i+1)<<"\t";           
            list[i].showData(choice);
            return 1;
        }
};
int student::getdata(university& u){
	cin.ignore();
	cout<<"\n\n\tEnter the name of student :\t";
	getline(cin,name);
	while(name.length()<2) {        
    	cin.ignore();
        cout<<"\n\tEnter valid name of student :\t";
        getline(cin,name);
    }
    int odept; 
    cout<<"\n\tEnter the department of student :\t";
    cout<<"\n\t\t1.CSE"<<endl;
    cout<<"\t\t2.ETC"<<endl;
    cout<<"\t\t3.EEE"<<endl;
    cout<<"\t";
    cin>>odept;  
    switch(odept){
       	case 1:
       		department = "CSE";
       		break;
       	case 2:
       		department = "ETC";
       		break;
       	case 3:
       		department = "EEE";
           	break;
    }
    transform(department.begin(), department.end(),department.begin(), ::toupper);
    int totalStudent=u.getcount();
    int i=0,counter=1;
    while(i<totalStudent){
		if(compareString(department,u.rolltype(i))){
			counter++;
		}
		i++;
	}
	char counterString[4];
	snprintf(counterString,4,"%03d",counter);
	roll=department+counterString;
	u.addStudent(*this);
	return 1;
}
void student::getmarks(){
	int i,totalmarks=0;
	for(i=0;i<5;i++){
		cout<<"Enter the marks of Subject "<<i+1<<": ";
		cin>>marks[i];
		if(marks[i]<40)
			totalmarks +=10000;
		else 
			totalmarks+=marks[i];
	}
	
	if(totalmarks<501)
		gpa = totalmarks/50;
	else
		gpa = 0;
}
int main(){
	student s;
	university u;
	int option,flag=1;
	cout<<"\n\n\n\t\t\t\t****************WELCOME****************"<<endl<<endl;	
	while(flag){
		cout<<"\n\t1. Take Admission";					
		cout<<"\n\t2. Show Details of All Student";
		cout<<"\n\t3. Marks Entry";
		cout<<"\n\t4. Display MarkSheet"; //add update price and update quantity here in case 3
		cout<<"\n\t5. Number of students Till now";
		cout<<"\n\t6. Sort the students according to GPA";
		cout<<"\n\t7. Get University Topper";
        cout<<"\n\t8. Exit"<<endl;
		cout<<"\n\tPlease Enter your Choice: ";
		cin>>option;
			switch(option){
			case 1:{
				s.getdata(u);
				flag=1;
				break;
			}
			case 2:{
				cout<<"\nRoll No.\tName\t\tDepartment\tAdmission Date\n";
				cout<<"***************************************************************"<<endl<<endl;
				u.showAllStudent();
				flag=1;
				break;
			}
			case 3:{
				string key;
				cout<<"Enter the roll to search:";
				cin.ignore();
				getline(cin,key);
				student &temp = u.getStudentmarks(key);
				temp.getmarks();
				flag=1;
				break;
			}
			case 4:{
				string key;
				cout<<"Enter the roll to search:";
				cin.ignore();
				getline(cin,key);
				cout<<endl;
				cout<<"------------------------Marksheet---------------------------------------";
				cout<<"\n\n\tRoll No.\tName\t\tDepartment\n";
				cout<<"***********************************************"<<endl;
				u.showStudentDetails(key,1);
				u.Marksheet(key);
				flag=1;
				break;
			}
			case 5:{
			  	cout<<endl<<endl;
				cout<<"Numbers of Student that have taken Admission are : "<<u.admCount();
				cout<<endl;
				flag=1;
				break;
			}
			case 6:{
				u.uSort();
				flag=1;
				break;
			}
			case 7:{
				cout<<"\nUniversity Topper Is\n";
				cout<<"\tRoll\t\tName\t\tDepartment\n";
				cout<<"************************************************\n";
				u.showTopper();
				flag=1;
				break;
			}
			case 8:{
				cout<<"Exiting........";
				flag=0;
				break;
			}
		}
	}	
}