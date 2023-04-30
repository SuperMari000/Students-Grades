#ifndef HEADER_H_
#define HEADER_H_

/*---------------------------*\
____________Mari000____________         
____Mostafa Mounir Shehab______
_________ICPC Targted_________   
\*---------------------------*/

#include <bits/stdc++.h>
using namespace std;


class Helper {
	public:
		static int arr[101];
  		static string gd[6];
  		static int NumRecord;
  		
  		static int ReadInt(int low, int high);
  		static bool RunMainMenu();
  		static bool CreatGread();
  		static int RunSubMenu(vector<string> &menu);
		
};

class Student {
	private:
		string ID;
		string First_Name;
		string Last_Name;
		string City;
		int Total;
	public:

		// Seter
		void setID(string id);
		void setFName(string fName);
		void setlName(string lName);
		void setCity(string city);
		void setTotal(int total);
		
		// Geter
		string getID();
		string getFName();
		string getlName();
		string getCity();
		int getTotal();

		
		friend ifstream& operator >> (ifstream& in, Student &s1){
	
			in>>s1.ID>>s1.First_Name>>s1.Last_Name>>s1.City>>s1.Total;
		    return in;
		}
		friend ofstream& operator << (ofstream& out, Student &s1){
			
			out<<s1.ID<<" "<<s1.First_Name<<" "<<s1.Last_Name<<" "<<s1.City<<" "<<s1.Total<<"\n";
		    return out;
		}
		friend istream& operator >> (istream& in, Student &s1){
			cout<<("\n\n\t\t\tPlease Enter NEW ID : ");
			in>>s1.ID;
			cout<<("\n\t\t\tPlease Enter NEW First Name : ");
			in>>s1.First_Name;
			cout<<("\n\t\t\tPlease Enter NEW Last Name : ");
			in>>s1.Last_Name;
			cout<<("\n\t\t\tPlease Enter NEW City : ");
			in>>s1.City;
			cout<<("\n\t\t\tPlease Enter NEW Total : ");
			s1.Total=Helper::ReadInt(0,100);
			
		    return in;
		}
		friend ostream& operator << (ostream& out, Student &s1){
			
			out<<setw(12)<<setiosflags(ios::left)<<s1.ID<<setw(15)<<s1.First_Name<<setw(15)<<s1.Last_Name<<setw(25)<<s1.City<<setw(10)<<Helper::gd[Helper::arr[s1.Total]]<<"\n";
		    return out;
		}
  
};

class StudentsManager {
	private:
		vector<Student> students_vec;
  		Student current,NewStudent;
	public:

		int FindRecord(string key);
		int HandelGread(string str,int &low,int &heigh);
		void Delete(string Key,bool flage);
		void Update(string Key,int rec);
		void sendID(bool flage);
		void DisplayTable();
		void Add(bool flage,int s=-2);
		void AddInFile(Student &NStudent,int rec);
		void Search();
		
		
  		
  		
  		

};

extern shared_ptr<StudentsManager> gStudentsManager;




#endif /* Mari000 */
