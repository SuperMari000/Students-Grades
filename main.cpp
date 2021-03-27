#include "header.h"
#include <bits/stdc++.h>
using namespace std;

/*---------------------------*\
____________Mari000____________         
____Mostafa Mounir Shehab______
_________ICPC Targted_________   
\*---------------------------*/



// Start Student Function

void Student::setID(string id){
	this->ID=id;
}
void Student::setFName(string fName){
	this->First_Name=fName;
}
void Student::setlName(string lName){
	this->Last_Name=lName;
}
void Student::setCity(string city){
	this->City=city;
}
void Student::setTotal(int total){
	this->Total=total;
}

string Student::getID(){
	return this->ID;
}
string Student::getFName(){
	return this->First_Name;
}
string Student::getlName(){
	return this->Last_Name;
}
string Student::getCity(){
	return this->City;
}
int Student::getTotal(){
	return this->Total;
}


// End Student Function



//**********************************************************************//


shared_ptr<StudentsManager> gStudentsManager(new StudentsManager());


int StudentsManager::HandelGread(string str,int &low,int &heigh){
	low=INT_MAX,heigh=-1;
	int i=0;
	while(i<6 && Helper::gd[i] != str)
		++i;
	if(i == 6)
		cout<<("\n\n\t\t\tThis Gread Not Exsiste\n\n");
	for(int j=0;j<101;++j)
		if(Helper::arr[j] == i)
			low=min(low,j),heigh=max(j,heigh);
	return i;
}
void StudentsManager::Search(){
	int choise,low,heigh;
	string str;
	
	vector<string> menu = { "ID", "City", "Gread" };
	choise=Helper::RunSubMenu(menu);
	
	cout<<("\n\n\t\t\tEnter Search Key : ");
	cin>>str;
	
	if(choise == 3 && HandelGread(str,low,heigh) == 6)
		return;
		
	students_vec.clear();
	
	ifstream myfile;
	myfile.open("data.txt");	
	while(myfile>>current){
		if(choise == 1 && str==current.getID())
			students_vec.push_back(current);
		else if(choise == 2 && str==current.getCity())
			students_vec.push_back(current);
		else if(choise == 3 && current.getTotal()>=low && current.getTotal()<=heigh)
			students_vec.push_back(current);
	}

	myfile.close();
	
	if(students_vec.size() < 1){
		cout<<("\n\n\t\t\tThis Student Not Exiest\n\n\n");
		return;
	}
		
	cout<<"\n"<<setw(12)<<setiosflags(ios::left)<<"ID"<<setw(15)<<"First Name"<<setw(15)<<"Last Name"<<setw(25)<<"City"<<setw(10)<<"Gread"<<"\n\n";
	for(Student st:students_vec)
		cout<<st;
	cout<<("\n\n");
	
}

void StudentsManager::Add(bool flage,int s){
	while(true){
		cin>>NewStudent;
		
		int x=FindRecord(NewStudent.getID());
		
		if( (flage && x == -1) || (!flage && (x == -1 || x == s)) )
			break;
			
		cout<<("\n\n\t\t\tThis ID Already Exiest \n\n\t\t\tPlease Try Again !!\n\n");
	}
	
	
	if(!flage)
		return;

	AddInFile(NewStudent,Helper::NumRecord);
	++Helper::NumRecord;
	cout<<("\n\n\t\t\tThis Stident is Added \n\n");
	
}

void StudentsManager::AddInFile(Student &NStudent,int rec){
	ofstream idxfile,datafile;
	idxfile.open("index.txt",ios::app);
	datafile.open("data.txt",ios::app);
	idxfile<<rec<<" "<<NStudent.getID()<<"\n";
	datafile<<NStudent;
	idxfile.close();
	datafile.close();
}

void StudentsManager::sendID(bool flage){
	string str;
	cout<<("\n\n\t\t\tPlease Enter Your ID : ");
	cin>>str;
	int x=FindRecord(str);
	
	if(x == -1)
		cout<<("\n\t\t\tThis ID ( ")<<str<<(" ) Not Found\n\n\n");
	else if(flage)
		Delete(str,true);
	else
		Update(str,x);
	
}

void StudentsManager::Delete(string Key,bool flage){
	
	students_vec.clear();
	
	ifstream myfile;
	myfile.open("data.txt");

	while(myfile>>current)
		if(current.getID() != Key)
			students_vec.push_back(current);	
	
	
	myfile.close();

	Helper::NumRecord=0;	
	
	ofstream datafile,indexfile;
	datafile.open("data.txt");
	indexfile.open("index.txt");
	
	
	for(int i=0;i<students_vec.size();++i){
		datafile<<students_vec[i];
		indexfile<<i<<" "<<students_vec[i].getID()<<"\n";
		++Helper::NumRecord;
	}
	
	datafile.close();
	indexfile.close();

	if(flage)
		cout<<("\n\n\t\t\tThis Student is Deleted\n");
}

void StudentsManager::Update(string Key,int rec){
	Add(false,rec);
	Delete(Key,false);
	AddInFile(NewStudent,Helper::NumRecord);
	++Helper::NumRecord;
	
	cout<<("\n\n\t\t\tThis Student is Updated\n");
	
}

void StudentsManager::DisplayTable(){
	ifstream myfile;
	myfile.open("data.txt");
	cout<<"\n"<<setw(12)<<setiosflags(ios::left)<<"ID"<<setw(15)<<"First Name"<<setw(15)<<"Last Name"<<setw(25)<<"City"<<setw(10)<<"Gread"<<"\n\n";
	
	while(myfile>>current){
		for(int i=0;i<77;++i)
				cout<<("-");
				
		cout<<("\n");
		cout<<current;
	}

	myfile.close();
	
}

int StudentsManager::FindRecord(string key){
	int num,val=-1;
	string id="";
	
	ifstream myfile;
	myfile.open("index.txt");
	
	while(myfile>>num>>id)
		if(id == key)
			val=num;
	myfile.close();
	if(id != "")
		Helper::NumRecord=num+1;
	return val;
}

//*********************************************************************//

int Helper::NumRecord=0;
int Helper::arr[101]={0};
string Helper::gd[6]={""};

int Helper::ReadInt(int low, int high) {
	int value;
	cin>>value;
	
	if (cin.fail()) {
		cout<<("ERROR: Expected integer input...Try again - Enter number ");
		cin.clear();
		cin.ignore(10000,'\n');
		return ReadInt(low, high);
	}
	
	if (low <= value && value <= high)
		return value;
	
	cout<<("ERROR: Expected range is low = ")<<low<<(", high = ")<<high<<(" ...Try again - Enter number ");
	return ReadInt(low, high);
}
bool Helper::CreatGread(){
	
	memset(arr,0,sizeof(arr));
	arr[45]=arr[50]=arr[65]=arr[75]=arr[85]=1;
	
	for(int i=1;i<101;++i)
		arr[i]+=arr[i-1];
		
		
	gd[0]="Very Weak";
	gd[1]="Weak";
	gd[2]="Acceptable";
	gd[3]="Good";
	gd[4]="Very Good";
	gd[5]="Excellent";
	

	
	return true;
}
bool Helper::RunMainMenu() {
	Helper::CreatGread();
	int choise;
	do{
		
		system("cls");
		system("color 71");
		cout<<("\n\n\n\tMAIN MENU\n");
		cout<<("\n\n\t\t01. Search For Added Student\n");
		cout<<("\n\n\t\t02. See Student Table\n");
		cout<<("\n\n\t\t03. Add A New Student\n");
		cout<<("\n\n\t\t04. Modify Student You Have added\n");
		cout<<("\n\n\t\t05. Delete Student You Have added\n");
		cout<<("\n\n\t\t00. Exit\n");
		cout<<("\n\n\tSelect Your Option (0 - 5) : ");
		choise = Helper::ReadInt(0,5);
		system("cls");
	    switch(choise){
	        case 1:
	        	gStudentsManager->Search();
	            break;
	        case 2:
	        	gStudentsManager->DisplayTable();
	            break;
	        case 3:
	        	gStudentsManager->Add(true);
	            break;
	        case 4:
	        	gStudentsManager->sendID(false);
	            break;
	        case 5:
	        	gStudentsManager->sendID(true);
	            break;
	    }
	    
	    
	    if(choise != 0){
	    	cout<<("\n\n\n\t\t\t");
	    	system("pause");
		}
	    	
		
	    
	
	} while(choise != 0);
	
	return false;
	
}
int Helper::RunSubMenu(vector<string> &menu) {
  	cout<<"\n\n\t\t\tPLEASE MAKE A CHOICE:\n\n\n\n";

  	for (int i = 0; i < menu.size(); ++i)
    	cout<<"\t\t\t0"<<i+1<<": Search By "<<menu[i]<<"\n";

  	cout<<"\n\t\t\tENTER SELECTION [ 1 - "<<menu.size()<<" ] : ";

  	return Helper::ReadInt(1, menu.size());
}


//***********************************************************************//


int main(){
	return Helper::RunMainMenu();	
}

