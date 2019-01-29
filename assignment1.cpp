#include<iostream> //header files
#include<string>
#include<ctime>
#include<cmath>
using namespace std;

// class TIME is created with data members and member functions
class TIME
 {
 	private:                    //private data members
        int hh,mm,ss,n,valid=0;
 			  char input[11];

 	public:
                      //public member functions
     	int take(){
	       cout<<"Enter the time in the format hh:mm:ss :- ";
	       cin>>input;
         cout<<"Your time has been accepted.\n";
      	// if(input[8]=='\0'){
      	// 	cout<<"\nGIVEN INPUT IS IN 24 HOUR FORMAT\n";
      	// }
      	// else
      	// 	cout<<"\nGIVEN INPUT IS IN 12 HOUR FORMAT\n";
        // storing hour minute and second in three different variable
      	 hh=atoi(&input[0]);
      	 mm=atoi(&input[3]);
      	 ss=atoi(&input[6]);
          // cout<<hh<<"\n";
          // cout<<mm<<"\n";
          // cout<<ss<<"\n";
          if(hh>25){
            cout<<"\nInvalid INPUT\n";
            return 0;
          }
          if(hh<0 || hh>24){
          	cout<<"\nInvalid INPUT\n";
            return 0;
          	//break;
          }
          if(mm<0 || mm>60){
          	cout<<"\nInvalid INPUT\n";
            return 0;
          	//break;
          }
          if(ss<0 || ss>60){
          	cout<<"\nInvalid INPUT\n";
            return 0;
          	//break;.
          }
          if(input[8]=='p' || input[8]=='a' || hh>12){
          	cout<<"\nInvalid INPUT\n";
            return 0;
          	//break;
          }
          if(hh==24 && (mm>0 || ss>0)){
          	cout<<"Invalid INPUT";
            return 0;
          	//break;
          }
          if(input[8]=='p'){
          	hh+=12;
          }
          valid=1;
          return 1;
         }
         //function to display the time
         int show(){
          if(!valid){
            cout<<"TIME NOT YET ENTERED\n";
            return 0;
          }
         	cout<<"\nPlease Enter your choice to display the time(1 or 2)\n";
          cout<<"1.Display the time in 24-hour format\n";
          cout<<"2.Display the time in AM/PM format\n";
          cin>>n;
          //switch case
          switch(n)
          {
          	case 1:"\nShowing time in 24 hour format\n";
          	      cout<<"Time is :- "<<hh%24<<":"<<mm<<":"<<ss<<"\n";
          	      break;

          	case 2:"\nShowing time in AM/PM format\n";
          		if(hh>12){
          			cout<<"Time is:- "<<hh-12<<":"<<mm<<":"<<ss<<"PM\n";
          		}
          		else if(hh<12){
                if(hh==0){
                  cout<<"Time is:- "<<"12"<<":"<<mm<<":"<<ss<<"PM\n";
                }
                else{
                  cout<<"Time is:- "<<hh<<":"<<mm<<":"<<ss<<"AM\n";
                }

          		}
              else{
                cout<<"Time is:- "<<hh<<":"<<mm<<":"<<ss<<"PM\n";
              }
          		break;
          }//end of switch
         }
         //function to add time in minutes
         int addTime(int add){
          if(!valid){
            cout<<"TIME NOT YET ENTERED\n";
            return 0;
          }
            int count;
         		mm+=add;
         		if (mm>59){
         			count=mm/60;
         			hh+=count;
         			mm%=60;
         		}
         }
         //function to calculate system difference
         int sysTimeDiff(){
           time_t now = time(0);
           char* dt = ctime(&now);
           tm *systm = localtime(&now);
           cout<<" DIFFERENCE IS: "
               <<abs(hh-systm->tm_hour)<<":"<<abs(mm-systm->tm_min)<<":"<<abs(ss-systm->tm_sec)<<endl;
         }
}; //end of class
int main(){
	TIME t1; //object of class TIME
  int input,add;
  cout<<"\t\t\t\t\t--WELCOME--\n\n";
  while(1){
    //cout<<"************************************************************************************************************************";
    cout<<"\n\tPlease Enter your choice :\t\t\t\n";
    cout<<"\t1.INPUT TIME IN ANY FORMAT\n";
    cout<<"\t2.SHOW TIME\n";
    cout<<"\t3.ADD TIME\n";
    cout<<"\t4.FIND DIFFERENCE\n";
    cout<<"\t0.EXIT-------\n";
    //cout<<"************************************************************************************************************************\n";
    cin>>input;
    //switch case
    switch(input){
      case 1:
        t1.take(); //calling function to take input
        break;
      case 2:
          t1.show(); //calling function show to show output
          break;
      case 3:
        add=0;
        cout<<" Enter the minutes to add:- ";
        cin>>add;
        t1.addTime(add); //calling function addTime to add time
        break;
      case 4:
        t1.sysTimeDiff();//calling function sysTimeDiff to calculate time difference
        break;
      case 0:
        cout<<" EXITING \n";
        return 0;
    }//end of main function
  }
}//end of main function
