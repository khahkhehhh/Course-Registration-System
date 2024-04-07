#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

void getline(istream& stream, int& num, char delimiter) {
	int temp;
	stream >> temp;
	stream.ignore(500, delimiter);
	num = temp;
}

void getline(istream& stream, string& str, char delimiter) {
	char temp[100];
	stream.get(temp, 100, delimiter);
	stream.ignore(100, delimiter);
	str = temp;
}

class Lecturer
{
private:
	string LectName, LectID;

public:
	Lecturer()
	{
		LectName = "";
		LectID = "";
	}

	void setLectName(string lec_name)
	{
		LectName = lec_name;
	}

	void setLectID(string lec_id)
	{
		LectID = lec_id;
	}

	string getLectName()
	{
		return LectName;
	}

	string getLectID()
	{
		return LectID;
	}
};


class Course //NODE
{
public:
	string c_code, c_name, c_time, c_day, c_location;
	int c_hour;
	Lecturer lecturer;
	Course* next;

	Course() {
		c_code = ""; //course code
		c_name = ""; //course name
		c_day = ""; //course day
		c_hour = 0; //total course hour
		c_location = ""; //course location
		c_time = ""; //course time
		next = NULL;
	}

	Course(string ccode, string cname, string cday, string lectcname, string lecturerid, int chour, string clocation, string ctime) {
		c_code = ccode;
		c_name = cname;
		c_day = cday;
		c_hour = chour;
		c_location = clocation;
		c_time = ctime;
		lecturer.setLectID(lecturerid);
		lecturer.setLectName(lectcname);
	}

	void setCourse(Course* temp) {
		c_code = temp->c_code;
		c_name = temp->c_name;
		c_day = temp->c_day;
		c_hour = temp->c_hour;
		c_location = temp->c_location;
		c_time = temp->c_time;
		lecturer.setLectID(temp->getLecturer().getLectID());
		lecturer.setLectName(temp->getLecturer().getLectName());

	}

	Lecturer getLecturer() {
		return lecturer;
	}

};

class CourseLinkedList
{
private:
	Course* head;
	Course* tail;
	Lecturer incharge;

public:
	CourseLinkedList() {
		head = NULL;
		tail = NULL;
	}

	void displayCourse() {
		cout << "\n-----------------------------------------COURSE MENU---------------------------------------------------------\n";
		cout << left << setw(15) << "Course Code" << setw(30) << "Course Name" << setw(15) << "Day" << setw(15) << "Total Hours" << setw(15) << "Time" << setw(5) << "Location" << endl;
		cout << "\n-------------------------------------------------------------------------------------------------------------\n";

		Course* temp;
		temp = head;
		while (temp != NULL) {
			cout << left << setw(15) << temp->c_code << setw(30) << temp->c_name << setw(20) << temp->c_day << setw(8
			) << temp->c_hour << setw(18) << temp->c_time << setw(10) << temp->c_location << endl;
			temp = temp->next;
		}
		cout << endl;
	}

	void enQcourse(Course* newnode) {
		if (head == NULL) {
			head = newnode;
			tail = newnode;
		}
		else
		{
			tail->next = newnode;
			newnode->next = NULL;
			tail = newnode;
		}
	}

	void addCourse() {
		string ncode, nname, lname, locate, time, day, lid;
		int hour;

		cout << "Course Code: ";
		getline(cin, ncode, '\n');
		cout << "Course Name: ";
		getline(cin, nname, '\n');
		cout << "Location: ";
		getline(cin, locate, '\n');
		cout << "Time: ";
		getline(cin, time, '\n');
		cout << "Day: ";
		getline(cin, day, '\n');
		cout << "Total hours: ";
		getline(cin, hour, '\n');
		cout << "Lecturer Name: ";
		getline(cin, lname, '\n');
		cout << "Lecturer ID: ";
		getline(cin, lid, '\n');

		Course* temp = new Course(ncode, nname, day, lname, lid, hour, locate, time);
		enQcourse(temp);

	}

	void delcourse(string ncode) {
		Course* curr = head;
		Course* last = tail;
		Course* deleteNode = NULL;

		deleteNode = curr;
		while (curr->c_code != ncode) {
			last->next = curr;
			last = curr;

			curr = curr->next;
			deleteNode = curr;
		}

		head = curr->next;
		delete deleteNode;
		tail = last;
		last->next = NULL;
		cout << "\nSuccessfully deleted!\n";
		displayCourse();
	}

	void deQcLect(string lname) {
		Course* curr = head;
		Course* last = tail;
		Course* deleteNode = NULL;

		deleteNode = curr;

		while (curr->getLecturer().getLectName() != lname) {
			last->next = curr;
			last = curr;
			curr = curr->next;
			deleteNode = curr;
		}

		head = curr->next;
		delete deleteNode;
		tail = last;
		last->next = NULL;
	}

	Course* findCourse(string coursecode) {
		Course* temp;
		temp = head;
		while (temp != NULL) {
			if (temp->c_code == coursecode) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void displaycCode(Course* newnode) {
		if (newnode == NULL) {
			cout << "NO RESULTS FOUND!" << endl;
		}
		else {
			cout << "RESULTS FOUND!" << endl;
			cout << endl;
			cout << "Lecturer ID: " << newnode->getLecturer().getLectID() << endl;
			cout << "Lecturer Name: " << newnode->getLecturer().getLectName() << endl;
			cout << "Course Code: " << newnode->c_code << endl;
			cout << "Course Name: " << newnode->c_name << endl;
			cout << "Day: " << newnode->c_day << endl;
			cout << "Total Hours: " << newnode->c_hour << endl;
			cout << "Time: " << newnode->c_time << endl;
			cout << "Location: " << newnode->c_location << endl;
		}
	}

	Course* deleteNext(Course* prev) {
		if (prev) {
			if (prev->next) {
				Course* temp = prev->next;
				prev->next = temp->next;
				return temp;
			}
		}
		else if (head) {
			Course* temp = head;
			head = head->next;
			return temp;
		}
		return NULL;
	}

	void displayCourseList() { //display registration course list
		int num = 0;
		Course* newnode = head;
		while (newnode != NULL) {
			cout << left << setw(5) << num + 1 << setw(20)
				<< newnode->c_code << setw(18) << newnode->c_name << endl;
			newnode = newnode->next;
			num++;
		}
	}

	void pushregister(Course* newnode) { //doubly linked list
		Course* temp = new Course; //allocate new memory for node
		temp->setCourse(newnode);

		if (temp == NULL)
			cout << "Cannot allocate memory\n";
		else {
			temp->next = head;
			head = temp;
		}
	}

	void popregister() {
		Course* deleteNode = head;
		if (head == NULL) {
			cout << "\nEmpty registration. Cannot pop!\n";
		}
		else {
			cout << "\n" << head->c_code << ", " << head->c_name << " successfully popped out!\n";
			head = head->next;
			delete deleteNode;
		}
	}

	void setLecturerInfo(Course* newnode) {
		incharge.setLectID(newnode->getLecturer().getLectID());
		incharge.setLectName(newnode->getLecturer().getLectName());
	}

	void stuCourseList() { //display list
		int num = 0;
		Course* newnode = head;
		while (newnode != NULL) {
			cout << left << setw(5) << num + 1 << setw(20)
				<< newnode->c_code << setw(18)
				<< newnode->c_name << setw(10) << endl;
			newnode = newnode->next;
			num++;
		}
	}

	Course* findLectName(string lectname) {
		Course* temp = head;
		while (temp != NULL) {
			if (temp->getLecturer().getLectName() == lectname) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void updateCourse(Course* newnode) { //list students who are under this teacher
		if (newnode == NULL) {
			cout << "  NO RESULT!!!\n";
		}
		else {

			cout << "  RESULT FOUND!\n";

			cout << "Lecturer ID: " << newnode->getLecturer().getLectID() << endl
				<< "Lecturer Name: " << newnode->getLecturer().getLectName() << endl
				<< "Course ID: " << newnode->c_code << endl
				<< "Course Name: " << newnode->c_name << endl
				<< "Day: " << newnode->c_day << endl
				<< "Total Hours: " << newnode->c_hour << endl
				<< "Time: " << newnode->c_time << endl
				<< "Location: " << newnode->c_location << endl;

			deQcLect(newnode->getLecturer().getLectName()); //dequeue the node that user entered
			cout << "\n** Please enter NEW course to enqueue.. **\n";
			addCourse(); //enqueue
			cout << "Update successful!\n";
		}
	}

	void displayLecturerList() {
		Course* temp = head;
		if (head == NULL)
			cout << "\nNo lecturer yet.\nPlease enqueue a new course to add lecturer.\n";
		else {
			cout << "--------------------------------------------------------------------" << endl;
			cout << left << setw(15) << "Lecturer ID" << setw(20) << "Lecturer Name"
				<< setw(15) << "Course ID" << setw(20) << "Course Name" << endl;
			cout << "--------------------------------------------------------------------" << endl;
			while (temp != NULL) {
				cout << left << setw(15) << temp->getLecturer().getLectID() << setw(20)
					<< temp->getLecturer().getLectName() << setw(15) << temp->c_code
					<< setw(20) << temp->c_name << endl;
				temp = temp->next;
			}
			cout << endl;
		}
	}

	void displayStudentLecturerList() {
		Course* temp = head;
		string daytime;
		if (head == NULL)
			cout << "\nNo lecturer yet.\nPlease enqueue a new course to add lecturer.\n";
		else {
			cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
			cout << left << setw(15) << "Lecturer ID" << setw(20) << "Lecturer Name" << setw(15) << "Course ID" << setw(20)
				<< "Course Name" << setw(25) << "Time (Day)" << setw(30) << "Location " << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

			while (temp != NULL) {
				daytime = temp->c_time + " (" + temp->c_day + ")";
				cout << left << setw(15) << temp->getLecturer().getLectID() << setw(20)
					<< temp->getLecturer().getLectName() << setw(15) << temp->c_code
					<< setw(20) << temp->c_name << setw(25) << daytime << setw(30) << temp->c_location << endl;
				temp = temp->next;
			}
		}
	}



};


class Register
{
private:
	CourseLinkedList* course;
	int courseNum;

public:
	Register()
	{
		courseNum = 0;
		course = NULL;
	}

	void addCourseReg(Course* c)
	{
		if (course == NULL)
		{
			course = new CourseLinkedList;
			course->pushregister(c);
		}
		else
		{
			course->pushregister(c);
		}
		courseNum++;
	}

	void deleteCourseReg()
	{
		course->popregister();
		courseNum--;
	}

	void displayCourseReg()
	{
		cout << "\nRegistration List" << endl << endl;
		course->displayCourse();
	}

	int getCourseNum()
	{
		return courseNum;
	}
};


class Student
{
public:
	string name, matricNo;
	Register reg;
	Student* next;
	CourseLinkedList courses;
	Lecturer lect;

	Student()
	{
		name = "";
		matricNo = "";
		next = NULL;
	}

	Student(string n, string matric, Student* temp)
	{
		name = n;
		matricNo = matric;
		next = temp;
	}

	void setStudentDetail(string n, string id)
	{
		name = n;
		matricNo = id;
	}
	void studCourse(CourseLinkedList temp) {
		int option;
		char choice;
		string courseID;
		Course* c = NULL;

		do {
			cout << "\nPlease choose an option......" << endl;
			cout << "1. Add course"
				<< "\n2. Drop course"
				<< "\n3. Return to Student Menu\n\n"
				<< "Option: ";
			cin >> option;
			cin.ignore();

			if (option == 1) { // Add course to register
				system("pause");
				system("CLS");
				bool addCourse = true;

				temp.displayCourse();

				cout << "\n** Student Detail ** "; //display student's info
				cout << "\nStudent ID: " << matricNo;
				cout << "\nStudent Name: " << name << endl;

				do
				{
				A: 	cout << "\n\nEnter Course Details";
					cout << "\n Course Code: ";
					cin >> courseID;
					cin.ignore();
					c = temp.findCourse(courseID);
					if (c == NULL) {
						cout << "\nInvalid Course ID.Please enter again.\n";
						goto A;
					}

					reg.addCourseReg(c);
					reg.displayCourseReg();

				B:  cout << "\nDo you want to register another course? Y/N ";
					cin >> choice;
					if ((choice == 'Y' || choice == 'y'))
						addCourse = true;
					else
						addCourse = false;
				} while (addCourse);
				system("pause");
				system("CLS");
			}

			else if (option == 2) { // Remove course	
				bool removeCourse = true;
				if (reg.getCourseNum() == 0) {
					cout << "\nNo course register yet.\n";
				}
				else {
					do {
						reg.displayCourseReg(); //display student's registered course
						reg.deleteCourseReg(); //ask student whether want to delete (pop) course
						cout << "\nDo you want to delete another Course? Y/N ";
						cin >> choice;
						if ((choice == 'Y' || choice == 'y'))
							removeCourse = true;
						else
							removeCourse = false;
					} while (removeCourse);
				}
				system("pause");
				system("CLS");
			}
			else if (option == 3) {
				cout << "Returning to Student Menu" << endl;
				system("pause");
				system("CLS");
			}
		} while (option != 3);
	}


	void displayStudentCourse()  //display student registered course
	{
		reg.displayCourseReg();
	}
};

class StudentLinkedList
{
private:
	Student* head;
	Student* tail;
	Register* reg;

public:
	StudentLinkedList()
	{
		head = NULL;
		tail = NULL;
	}

	void StudentList()
	{
		Student* temp = head;
		cout << "--------------------------------------------------------------------" << endl;
		cout << left << setw(20) << "Student Matric No";  cout << setw(30) << "Student Name" << endl;
		cout << "--------------------------------------------------------------------" << endl;
		while (temp != NULL) {
			cout << left << setw(20) << temp->matricNo << setw(30) << temp->name << setw(10) << endl;
			temp = temp->next;
		}
	}

	void enQStudent(Student* node)
	{
		if (head == NULL) {
			head = node;
			tail = node;
		}
		else {
			tail->next = node;
			node->next = NULL;
			tail = node;
		}
	}

	Student* findStudent(string studentId)//find stud based on studID
	{
		Student* stud = head;
		while (stud != NULL) {
			if (stud->matricNo == studentId) {
				return stud;
			}
			stud = stud->next;
		}
		return NULL;
	}

	void addStudent(string n, string id, CourseLinkedList temp)
	{
		Student* newStudent = new Student; //everytime want add, must use new
		newStudent->setStudentDetail(n, id);
		newStudent->studCourse(temp);
		enQStudent(newStudent);
	}

	int getStudentListSize()
	{
		Student* temp = head;
		int n = 0;
		while (temp != NULL) {
			temp = temp->next;
			n++;
		}
		return n;
	}
	void deQstudent(string studentName)
	{
		Student* curr = head;
		Student* last = tail;
		Student* deleteNode = NULL;

		deleteNode = curr;

		while (curr->name != studentName) {
			last->next = curr;
			last = curr;
			curr = curr->next;
			deleteNode = curr;
		}
		head = curr->next;
		delete deleteNode;
		tail = last;
		last->next = NULL;
		cout << "\nDelete successfully!\n";
		if (getStudentListSize() == 0) {
			cout << "No student registered yet.\n";
		}
		else {
			StudentList();
		}
	}

	void displayStudRegistration(Student* node)
	{
		if (node == NULL) {
			cout << "===============\n";
			cout << "  NO RESULTS FOUND\n";
			cout << "===============\n";
		}
		else {
			cout << "==================\n";
			cout << "  RESULTS FOUND\n";
			cout << "==================\n\n";
			cout << "Student ID: " << node->matricNo << endl;
			cout << "Student Name: " << node->name << endl;
			node->displayStudentCourse();
		}
	}
};

void addStudent(StudentLinkedList* stud, CourseLinkedList cll) {
	string stud_name, stud_id;
	cout << "===============================\n";
	cout << "  STUDENT REGISTRATION SYSTEM  \n";
	cout << "===============================\n";
	cout << "Student Name: ";
	cin.ignore(100, '\n');
	getline(cin, stud_name, '\n');
	cout << "Student ID: ";
	getline(cin, stud_id, '\n');

	stud->addStudent(stud_name, stud_id, cll);
}

void LecturerMenu() {
	cout << "***LECTURER MENU***"
		<< "\n1. Add course"
		<< "\n2. Delete course"
		<< "\n3. Search course"
		<< "\n4. Display course"
		<< "\n5. Update course"
		<< "\n6. Display student registration info"
		<< "\n7. Delete student registration info"
		<< "\n8. Return to User Menu"
		<< "\n\nChoice: ";
}

void studentMenu() {
	cout << "***STUDENT MENU***"
		<< "\n1. View Course"
		<< "\n2. Register Course"
		<< "\n3. View Lecturer Info"
		<< "\n4. Return to User Menu"
		<< "\n\nEnter your choice: ";
}


int main()
{
	int choice;
	CourseLinkedList cll;
	StudentLinkedList* stud = new StudentLinkedList;

	int numCourse, hour;
	string tid, cCode, cName, tName, venue, day, time;
	ifstream info("Text.txt", ios::in);

	info >> numCourse;
	info.ignore(100, '\n');
	for (int i = 0; i < numCourse; i++) {
		getline(info, cCode, ',');
		getline(info, cName, ',');
		getline(info, day, ',');
		getline(info, tName, ',');
		getline(info, tid, ',');
		getline(info, hour, ',');
		getline(info, venue, ',');
		getline(info, time, '\n');

		Course* crs = new Course(cCode, cName, day, tName, tid, hour, venue, time); //node
		cll.enQcourse(crs);
	}

	do {
	E:	cout << "\n";
		cout << "\t\t\t\t\tWelcome to UTM Course Registration System\n";
		cout << "---- User Menu ----\n"

			<< "1 - Lecturer\n"
			<< "2 - Student\n"
			<< "3 - Exit The System\n\n";

		cout << "Enter your menu interface: ";
		cin >> choice;
		cout << endl;

	C:	if (choice == 1)
	{
		int option;
		do {
		J:	LecturerMenu(); //display lecturer menu
			cin >> option;
			system("CLS");
			switch (option) {
			case 1: cin.ignore(100, '\n');
				cll.addCourse(); //Enqueue  course 
				system("pause");
				system("CLS");
				goto J;

			case 2: cll.displayCourse();
				cout << "Please enter the courseID to delete: ";
				cout << "Please enter the courseID to delete: ";
				cin >> cCode;
				cll.delcourse(cCode);
				cout << endl;
				system("pause");
				system("CLS");
				goto J;

			case 3: {
				cout << "Please enter the course ID to search: ";//Search course based on course ID
				cin >> cCode;
				Course* search = NULL; //initialise node
				search = cll.findCourse(cCode); //return node
				cll.displaycCode(search);
				cout << endl;
				system("pause");
				system("CLS");
				goto J;
			}

			case 4: cll.displayCourse();
				system("pause");
				system("CLS");
				goto J;

			case 5: {cll.displayLecturerList();
				cout << "Please enter lecturer name to be update: "; //update lecturer's course
				cin.ignore(100, '\n');
				getline(cin, tName, '\n');
				Course* searchLect = NULL;
				searchLect = cll.findLectName(tName);
				cll.updateCourse(searchLect);
				cout << endl;
				system("pause");
				system("CLS");
				goto J; }

			case 6: if (stud->getStudentListSize() == 0) {
				cout << "No student registered yet.\n";
			}
				  else {
				char option;
				string studCode;
				do {
					stud->StudentList(); //Display student registration info  
					cout << "\nPlease enter studentID to search: ";
					cin >> studCode;
					Student* searchStudent = NULL;
					searchStudent = stud->findStudent(studCode);
					stud->displayStudRegistration(searchStudent);
					cout << "\nDo you want continue to search? Y/N\n";
					cin >> option;
					system("CLS");
				} while (option == 'Y' || option == 'y');
			}
				  cout << endl;
				  system("pause");
				  system("CLS");
				  goto J;

			case 7: {stud->StudentList();					//Delete student registration info
				if (stud->getStudentListSize() == 0) {
					cout << "No student registered yet.\n";
				}
				else {
					string name;
					cout << "\nPlease enter Student Name to delete: ";
					cin.ignore(100, '\n');
					getline(cin, name, '\n');
					stud->deQstudent(name);
					cout << endl;
				}
				cout << endl;
				system("pause");
				system("CLS");
				goto J; }

			case 8: cout << "Returning to User Menu......" << endl;
				system("pause");
				system("CLS");
				goto E;

			default: cout << "Invalid choice! Please re-enter your choice." << endl;
				break;
			}
		} while (option != 8); //lecturer menu while loop
	}
	else if (choice == 2) {
		int ch;
	D:	studentMenu(); //display student menu
		cin >> ch;
		system("pause");
		system("CLS");
		switch (ch) {
		case 1: cll.displayCourse(); //View Course
			
			system("pause");
			system("CLS");
			goto D;

		case 2: addStudent(stud, cll); //Register Course
			goto D;

		case 3: cll.displayLecturerList();

			cout << "\nReturning to Student Menu......" << endl;

			system("pause");
			system("CLS");
			goto D;

		case 4: cout << "\nReturning to User Menu......" << endl;
			system("pause");
			system("CLS");
			goto E;

		default: cout << "Enter wrong choice! Please re-enter choice." << endl;
			break;
		}
	}
	else if (choice == 3) { //EXIT from the system
		cout << "Thank you for using UTM Course Registration System.";
		exit(1);
	}
	} while (choice != 3);

	return 0;

}