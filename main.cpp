#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class user{
	private:
		string username;
		string password;
		
		public:
			user(string u = "",string p = ""){
				username = u;
				password = p;
			}

};
class notice {
	public:
		string msg;
		void postnotice(string m){
			msg = m;
			ofstream N("notice.",ios::app);
			if(N.is_open()){
				N<<msg<<endl;
				N.close();
			}
			else{
				cout<<"Error "<<endl;
			}
		
		}
};
class admin : public user{
	public:
		admin(string u = "",string p = ""):user(u,p){
			}
};


class leave{
	public:
		string reason;
		void applyleave(string r){
			reason = r;
			ofstream L("leave_request.txt",ios::app);
			if(L.is_open()){
				L<<reason<<endl;
				L.close();
			}
			else{
				cout<<"Error "<<endl;
			}
		}
};

class course{
	public:
		string course_name;
		int marks;
		
		course(string n,int m){
			course_name = n;
			marks = m;
		}
		
		
};

class StudentGrades {
public:
    string username;
    vector<course> courses;

    StudentGrades(string u) {
        username = u;
    }

    void add_course(string course_name, int marks) {
        courses.push_back(course(course_name, marks));
    }
};


class student_info{
	private:
		string username;
		string name;
		int rollno;
		string email;
		string phone;
		
	
	public:
		student_info(string user = "",string n = "",int r = 0,string e = "",string p = 0){
			username = user;
			name = n;
			rollno = r;
			email = e;
			phone = p;
		}
	
	void set_email(string e){
		email = e;
	}
	
	void set_phone(string p){
		phone = p;
	}
	
    string to_string_format(char sep = '|') {
        return username + " " + sep + " " + name + " " + sep + " " +
               to_string(rollno) + " " + sep + " " + email + " " + sep + " " + phone;
    }
};

class students : public user{
	public:
		students(string u = "",string p = ""):user(u,p){}
};

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


string get_grade(int marks) {
    if (marks >= 90) return "A+";
    else if (marks >= 80) return "A";
    else if (marks >= 70) return "B+";
    else if (marks >= 60) return "B";
    else if (marks >= 50) return "C";
    else return "F";
}

int main() {
    ifstream file("User.txt");
    string line;
	
	string user_input,input_pass;
	cout<<"Enter your username "<<endl;
	cin>>user_input;
	cout<<"Enter your passwor "<<endl;
	cin>>input_pass;
	
	notice n;
	string mynotice;
	
	cout<<"Enter your notice "<<endl;
	getline(cin, mynotice); 
    
    n.postnotice(mynotice);
	bool found = false;
	
	while(getline(file,line)){
		istringstream iss(line);
		
		string username,password,role;
		
		getline(iss,username, ',');
		getline(iss,password, ',');
		getline(iss,role, ',');
		
		if(username == user_input && password == input_pass ){
			cout<<"Verified Account "<<endl;
			cout<<role<<endl;
			found = true;
			
			if(role == "admin"){
				string choice;
				while(true){
				cout<<"Welcome Admin!"<<endl;
				cout<<"1. Post a Notice"<<endl;
				cout<<"2. View All Notices"<<endl;
				cout<<"3. View Students Grades"<<endl;
				cout<<"4. Logout"<<endl;
				cout<<"Enter your choice:"<<endl;
				cin>>choice;
				if(choice == "1"){
					notice n;
					string mynotice;
					cin.ignore();
					cout<<"Enter your notice "<<endl;
					getline(cin, mynotice); 
	    
					n.postnotice(mynotice);	
					
				}
				else if (choice == "2") {
					ifstream notice_file("notice.txt");
					string line;
					
					if(notice_file.is_open()){
						
						while(getline(notice_file,line)){
							cout<<line<<endl;
						}
						notice_file.close();
					}
					else{
						cout<<"nothing found "<<endl;
					}

                }
                else if(choice == "3"){
			    string target_name, target_course;
			    cout << "Enter student name: ";
			    cin.ignore(); 
			    getline(cin, target_name);
			    
			    cout << "Enter course name to update: ";
			    getline(cin, target_course);
			
			    int new_marks;
			    cout << "Enter new marks: ";
			    cin >> new_marks;
			
			    ifstream infile("grades.txt");
			    vector<string> updated_lines;
			    string line;
			    bool updated = false;
			
			    while (getline(infile, line)) {
			        istringstream iss(line);
			        string name, course, marks_str, grade;
			        getline(iss, name, '|');
			        getline(iss, course, '|');
			        getline(iss, marks_str, '|');
			        getline(iss, grade);
			
			        name = trim(name);
			        course = trim(course);
			        marks_str = trim(marks_str);
			
			        if (name == target_name && course == target_course) {
			            string new_grade = get_grade(new_marks);
			            updated_lines.push_back(name + " | " + course + " | " + to_string(new_marks) + " | " + new_grade);
			            updated = true;
			        } else {
			            updated_lines.push_back(line);
			        }
			    }
			    infile.close();
			
			    ofstream outfile("grades.txt");
			    for (const string& updated_line : updated_lines) {
			        outfile << updated_line << endl;
			    }
			    outfile.close();
			
			    if (updated)
			        cout << "Grade updated successfully!" << endl;
			    else
			        cout << "Student or course not found!" << endl;
			}
				
	
			

            else if (choice == "4") {
                    cout << "Logging out..." << endl;
                    break;
                }
                else {
                    cout << "Invalid choice. Try again.\n";
                    }
			}
	}
	
				
			else if(role == "student"){
				string choice;
				while(true){
				cout<<"Welcome Student!"<<endl;
				cout<<"1. View Profile"<<endl;
				cout<<"2. Update Email"<<endl;
				cout<<"3. Update Phone"<<endl;
				cout<<"4. Apply for Leave"<<endl;
				cout<<"5. Logout"<<endl;
				cout<<"Enter your choice "<<endl;
				cin>>choice;
			
		 	if(choice == "1"){
		 		string search;
		 		cout<<"Enter your user name: "<<endl;
		 		cin>>search;
		 		
		 		ifstream student_file("Students.txt");
		 		string line;
		 		bool found = false;
		 		
		 		while(getline(student_file,line)){
		 			istringstream iss(line);
        			string username, name, roll_str, email, phone;
        			
        			getline(iss,username,'|');
        			getline(iss,name,'|');
        			getline(iss,roll_str,'|');
        			getline(iss,email,'|');
        			getline(iss,phone,'|');
        			
        			username = trim(username);
        			name = trim(name);
        			roll_str = trim(roll_str);
        			email = trim(email);
        			phone = trim(phone);
        			
        			if(username == search){
        				cout<<"Profile found "<<endl;
						cout << "Username: " << username << endl;
			            cout << "Name: " << name << endl;
			            cout << "Roll No: " << roll_str << endl;
			            cout << "Email: " << email << endl;
			            cout << "Phone: " << phone << endl;
			            found = true;
			            break;					}
				 }	
			
			if(!found){
				cout<<"Profile not found "<<endl;
			}
			
  			student_file.close();
  }
			else if (choice == "2") {
			    ifstream email_file("Students.txt");
			    vector<string> updated_lines;
			    string line;
			    string old_email, new_email;
			
			    cout << "Enter your old email: ";
			    cin >> old_email;
			    cout << "Enter your new email: ";
			    cin >> new_email;
			
			    bool update = false;
			
			    getline(email_file, line); 
			    updated_lines.push_back(line); 
			
			    while (getline(email_file, line)) {
			        istringstream iss(line);
			        string username, name, roll_str, email_field, phone_str;
			
			        getline(iss, username, '|');
			        getline(iss, name, '|');
			        getline(iss, roll_str, '|');
			        getline(iss, email_field, '|');
			        getline(iss, phone_str, '|');
			
			        username = trim(username);
			        name = trim(name);
			        roll_str = trim(roll_str);
			        email_field = trim(email_field);
			        phone_str = trim(phone_str);
			
			        if (roll_str.empty() || phone_str.empty()) {
			            cerr << "Skipping malformed line: " << line << endl;
			            continue;
			        }
			
			        try {
			            int roll = stoi(roll_str);
						string phone = phone_str;
			
			            if (email_field == old_email) {
			                student_info s(username, name, roll, email_field, phone);
			                s.set_email(new_email);
			                updated_lines.push_back(s.to_string_format('|'));
			                update = true;
			            } else {
			                updated_lines.push_back(line);
			            }
			        } catch (invalid_argument& e) {
			            cerr << "Invalid number in line: " << line << endl;
			            continue;
			        } catch (out_of_range& e) {
			            cerr << "Out of range number in line: " << line << endl;
			            continue;
			        }
			    }
			
			    email_file.close();
			
			    if (update) {
			        ofstream outfile("Students.txt");
			        for (const string& updated_line : updated_lines) {
			            outfile << updated_line << endl;
			        }
			        outfile.close();
			        cout << "Email updated successfully!" << endl;
			    } else {
			        cout << "Email not found!" << endl;
			    }
			}

	else if(choice == "3"){
		    ifstream phonefile("Students.txt");
		    vector<string> updated_lines;
		    string line;
		
		    string oldnumber, newnumber;
		    cout << "Enter your old phone number: " << endl;
		    cin >> oldnumber;
		    cout << "Enter your new phone number: " << endl;
		    cin >> newnumber;
		
		    bool update = false;
		
		    getline(phonefile, line); 
		    updated_lines.push_back(line);
		
		    while (getline(phonefile, line)) {
		        istringstream iss(line);
		        string username, name, roll_str, email_field, phone_str;
		
		        getline(iss, username, '|');
		        getline(iss, name, '|');
		        getline(iss, roll_str, '|');
		        getline(iss, email_field, '|');
		        getline(iss, phone_str, '|');
		
		        username = trim(username);
		        name = trim(name);
		        roll_str = trim(roll_str);
		        email_field = trim(email_field);
		        phone_str = trim(phone_str);
		
		        int roll = 0;
		        try {
		            roll = stoi(roll_str);
		        } catch (invalid_argument& e) {
		            cerr << "Invalid roll number in line: " << line << endl;
		            continue;
		        } catch (out_of_range& e) {
		            cerr << "Out of range roll number in line: " << line << endl;
		            continue;
		        }
		
		        if (phone_str == oldnumber) {
		            student_info s(username, name, roll, email_field, phone_str);  
		            s.set_phone(newnumber);  
		            updated_lines.push_back(s.to_string_format('|'));  
		            update = true;
		        } else {
		            updated_lines.push_back(line);  
		        }
		    }
		
		    phonefile.close();
		
		    if (update) {
		        ofstream outfile("Students.txt");
		        for (const string& updated_line : updated_lines) {
		            outfile << updated_line << endl;
		        }
		        outfile.close();
		        cout << "Phone number updated successfully!" << endl;
		    } else {
		        cout << "Phone number not found!" << endl;
		    }
		
	}
			
			else if(choice == "4"){
					leave l;
					string  studentleave;
					cin.ignore();
					cout<<"Enter your leaves "<<endl;
					getline(cin,studentleave);
					l.applyleave(studentleave);
				}
					
				else if(choice == "5"){
					cout << "Logging out..." << endl;
	                break;
				}
				else {
	                cout << "Invalid choice. Try again.\n";
	                }
	            }
	        }
			
			break;
			}
		}
		if(!found){
			cout<<"Invalid Username or password "<<endl;
		}
    return 0;
}