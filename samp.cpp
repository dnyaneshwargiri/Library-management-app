#include<fstream>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
using namespace std;
class book
{
char book_number[30];
char book_name[50];
char author_name[50];
public:
void create_book()
{
cout<<"\nEnter The Book Number: ";
cin>>book_number;
cout<<"\nEnter The Name of The Book: ";
cin.ignore();
cin.getline(book_name,50);
cout<<"\nEnter The Author's Name: ";
cin>>author_name;
//cin.ignore();
//cin.getline(author_name,50);
cout<<"\t\t\n\nBook Created Successfully...";
}
void show_book()
{
cout<<"\nBook Number: "<<book_number;
cout<<"\nBook Name: "<<book_name;
cout<<"\nAuthor's Name: "<<author_name;
}
void modify_book()
{
cout<<"\nBook number : "<<book_number;
cout<<"\nModify Book Name : ";
cin.ignore();
cin.getline(book_name,50);
cout<<"\nModify Author's Name: ";
cin>>author_name;
//cin.ignore();
//cin.getline(author_name,50);
}
char* getbooknumber()
{
return book_number;
}
void report()
{cout<<book_number<<setw(30)<<book_name<<setw(30)<<author_name<<endl;
}
};
class student
{
char ID_number[20];
char Student_name[20];
char stbno[6];
int token;
public:
void create_student()
{
cout<<"\nEnter The ID Number ";
cin>>ID_number;
cout<<"\n\nEnter The Name of The Student: ";
cin>>Student_name;
token=0;
stbno[0]='\0';
cout<<"\t\t\n\nStudent Record Created Successfully...";
}
void show_student()
{
cout<<"\nID Number: "<<ID_number;
cout<<"\nStudent Name: ";
puts(Student_name);
cout<<"\nNo of Book issued: "<<token;
if(token==1)
cout<<"\nBook No "<<stbno;
}
void modify_student()
{
cout<<"\nID Number: "<<ID_number;
cout<<"\nModify Student Name: ";
cin.ignore();
cin.getline(Student_name,50);
}
char* get_ID_number()
{
return ID_number;
}
char* retstbno()
{
return stbno;
}
int rettoken()
{
return token;
}
void addtoken()
{token=1;}
void resettoken()
{token=0;}
void getstbno(char t[])
{
strcpy(stbno,t);
}
void report()
{cout<<"\t"<<ID_number<<setw(20)<<Student_name<<setw(10)<<token<<endl;}
};
fstream fp,fp1;
book bk;
student st;
void write_book()
{

int more_or_main;
fp.open("book.dat",ios::out|ios::app);
do
{
bk.create_book();
fp.write((char*)&bk,sizeof(book));
cout<<"\nPress 1 to add more books.";
cout<<"\nPress 2 to return to main menu.\n";
cout<<"Enter: ";
cin>>more_or_main;
}while(more_or_main == 1);
fp.close();
}
void write_student()
{

int more_or_main;
fp.open("student.dat",ios::out|ios::app);
do
{
st.create_student();
fp.write((char*)&st,sizeof(student));
cout<<"\nPress 1 to add more students.";
cout<<"\nPress 2 to return to main menu.\n";
cout<<"Enter: ";
cin>>more_or_main;
}while(more_or_main == 1);
fp.close();
}
void display_a_book(char n[])
{

cout<<"\nBOOK DETAILS\n";
int check=0;
fp.open("book.dat",ios::in);
while(fp.read((char*)&bk,sizeof(book)))
{
if(strcmp(bk.getbooknumber(),n)==0)
{
bk.show_book();
check=1;
}
}
fp.close();
if(check==0)
cout<<"\n\nBook does not exist";
getchar();
}
void display_a_student(char n[])
{

cout<<"\nSTUDENT DETAILS\n";
int check=0;
fp.open("student.dat",ios::in);
while(fp.read((char*)&st,sizeof(student)))
{
if((strcmp(st.get_ID_number(),n)==0))
{
st.show_student();
check=1;
}
}
fp.close();
if(check==0)
cout<<"\n\nStudent does not exist";
getchar();
}
void modify_book()
{

char n[20];
int found=0;
cout<<"\n\n\tMODIFY BOOK";
cout<<"\n\n\tEnter The book number: ";
cin>>n;
fp.open("book.dat",ios::in|ios::out);
while(fp.read((char*)&bk,sizeof(book)) && found==0)
{
if(strcmp(bk.getbooknumber(),n)==0)
{
bk.show_book();
cout<<"\nEnter The New Details of book"<<endl;
bk.modify_book();
int pos=-1*sizeof(bk);
fp.seekp(pos,ios::cur);
fp.write((char*)&bk,sizeof(book));
cout<<"\n\n\t Record Updated Successfully...";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getchar();
}
void modify_student()
{

char n[20];
int found=0;
cout<<"\n\n\tMODIFY STUDENT RECORD... ";
cout<<"\n\n\tEnter Student's ID number: ";
cin>>n;
fp.open("student.dat",ios::in|ios::out);
while(fp.read((char*)&st,sizeof(student)) && found==0)
{
if(strcmp(st.get_ID_number(),n)==0)
{
st.show_student();
cout<<"\nEnter The New Details of student"<<endl;
st.modify_student();
int pos=-1*sizeof(st);
fp.seekp(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Record Updated Successfully...";
found=1;
}
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getchar();
}
void delete_student()
{

char n[20];
int flag=0;
cout<<"\n\n\n\tDELETE STUDENT";
cout<<"\n\nEnter The ID number of the Student You Want To Delete: ";
cin>>n;
fp.open("student.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&st,sizeof(student)))
{
if(strcmp(st.get_ID_number(),n)!=0)
fp2.write((char*)&st,sizeof(student));
else
flag=1;
}
fp2.close();
fp.close();
remove("student.dat");
rename("Temp.dat","student.dat");
if(flag==1)
cout<<"\n\n\tRecord Deleted ..";
else
cout<<"\n\nRecord not found";
getchar();
}
void delete_book()
{

char n[20];
int flag=0;
cout<<"\n\n\n\tDELETE BOOK";
cout<<"\n\nEnter The Book's number You Want To Delete: ";
cin>>n;
fp.open("book.dat",ios::in|ios::out);
fstream fp2;
fp2.open("Temp.dat",ios::out);
fp.seekg(0,ios::beg);
while(fp.read((char*)&bk,sizeof(book)))
{
if(strcmp(bk.getbooknumber(),n)!=0)
{
fp2.write((char*)&bk,sizeof(book));
}
else
flag=1;
}
fp2.close();
fp.close();
remove("book.dat");
rename("Temp.dat","book.dat");
if(flag==1)
cout<<"\n\n\tRecord Deleted ..";
else
cout<<"\n\nRecord not found";
getchar();
}
void display_all_students()
{

fp.open("student.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
getchar();
return;
}
cout<<"\n\n\t\tSTUDENT LIST\n\n";
cout<<"==================================================================\n";
cout<<"\tID Number."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
cout<<"==================================================================\n";
while(fp.read((char*)&st,sizeof(student)))
{
st.report();
}
fp.close();
getchar();
}
void display_allb()
{

fp.open("book.dat",ios::in);
if(!fp)
{
cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
getchar();
return;
}
cout<<"\n\n\t\tBook LIST\n\n";
cout<<"=========================================================================\n";
cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
cout<<"=========================================================================\n";
while(fp.read((char*)&bk,sizeof(book)))
{
bk.report();
}
fp.close();
getchar();
}
void issue_book()
{

char sn[20],bn[20];
int found=0,flag=0;
cout<<"\t\t\nBOOK ISSUE";
cout<<"\n\n\tEnter student's ID number: ";
cin>>sn;
fp.open("student.dat",ios::in|ios::out);
fp1.open("book.dat",ios::in|ios::out);
while(fp.read((char*)&st,sizeof(student)) && found==0)
{
if(strcmp(st.get_ID_number(),sn)==0)
{
found=1;
if(st.rettoken()==0)
{
cout<<"\n\n\tEnter book number: ";
cin>>bn;
while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
{
if(strcmp(bk.getbooknumber(),bn)==0)
{
bk.show_book();
flag=1;
st.addtoken();
st.getstbno(bk.getbooknumber());
int pos=-1*sizeof(st);
fp.seekp(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Book issued successfully";

fp.close();
fp1.close();
}
}}}}}/*added }}*/
void book_return()
{

char sn[20];/*,bn[20] removed*/
int found=0,flag=0,day,fine;
cout<<"\t\tRETURN BOOKS\n";
cout<<"\n\n\tEnter The student’s ID Number: ";
cin>>sn;
fp.open("student.dat",ios::in|ios::out);
fp1.open("book.dat",ios::in|ios::out);
while(fp.read((char*)&st,sizeof(student)) && found==0)
{
if(strcmp(st.get_ID_number(),sn)==0)
{
found=1;
if(st.rettoken()==1)
{
while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
{
if(strcmp(bk.getbooknumber(),st.retstbno())==0)
{
bk.show_book();
flag=1;
cout<<"\n\nBook returned in no. of days";
cin>>day;
if(day>15)
{
fine=(day-15)*1;
cout<<"\n\nThe Book is last. You have to pay a fine of"<<"\t"<<fine<<"\t"<<"Rs.only(Rate::1 Rs.per day after 15 days over.)";
}
st.resettoken();
int pos=-1*sizeof(st);
fp.seekp(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Book returned successfully...";
}
}
if(flag==0)
cout<<"Book number does not exist";
}
else
cout<<"No book is issued..please check!!";
}
}
if(found==0)
cout<<"Student record not exist...";
getchar();

fp.close();
fp1.close();
}
void intro()
{

	cout<<"\n\n\t\t\tWELCOME TO LIBRARY SYSTEM\n\n";
}
void book_menu()
{
int option;
cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
cout<<"\n\t\tPress 1 to CREATE BOOKS";
cout<<"\n\t\tPress 2 to DISPLAY ALL BOOKS";
cout<<"\n\t\tPress 3 to DISPLAY SPECIFIC BOOK";
cout<<"\n\t\tPress 4 to MODIFY BOOKS";
cout<<"\n\t\tPress 5 to DELETE BOOKS";
cout<<"\n\t\tPress 6 to GO BACK TO MAIN MENU";

cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\n\t\tOption: ";
cin>>option;
switch(option)
{
case 1:
write_book();
break;
case 2: display_allb();
break;
case 3:
char num[20];

cout<<"\n\n\tPlease Enter The book No. ";
cin>>num;
display_a_book(num);
break;
case 4: modify_book();break;
case 5: delete_book();break;
case 6:
break;
default:cout<<"\a";
}
}
void student_menu()
{
int option;
cout<<"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
cout<<"\n\t\tPress 1 to CREATE STUDENT RECORD";
cout<<"\n\t\tPress 2 to DISPLAY ALL STUDENTS RECORD";
cout<<"\n\t\tPress 3 to DISPLAY SPECIFIC STUDENT RECORD";
cout<<"\n\t\tPress 4 to MODIFY STUDENT RECORD";
cout<<"\n\t\tPress 5 to DELETE STUDENT RECORD";
cout<<"\n\t\tPress 6 to GO BACK TO MAIN MENU";
cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\n\t\tOption: ";
cin>>option;
switch(option)
{
case 1:
write_student();
break;
case 2:
case 3:
display_all_students();
break;
char num[20];
system("cls");
cout<<"\n\n\tPlease Enter The ID Number: ";
cin>>num;
display_a_student(num);
break;
case 4:
modify_student();break;
case 5:
delete_student();break;
case 6:
break;
default:cout<<"\a";
}
}
int main()
{
int option=0;
for(;;)
{
intro();
cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
cout<<"\n\t\tPress 1 to ISSUE BOOKS";
cout<<"\n\t\tPress 2 to RETURN BOOKS";
cout<<"\n\t\tPress 3 to UPDATE STUDENT RECORDS";
cout<<"\n\t\tPress 4 to UPDATE BOOK RECORDS";
cout<<"\n\t\tPress 5 to TO EXIT";
cout<<"\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
cout<<"\n\t\tOption: ";
cin>>option;
switch(option)
{
case 1:
issue_book();
break;
case 2:
book_return();
break;
case 3:
student_menu();
break;
case 4:
book_menu();
break;
case 5:exit(0);
break;
default :cout<<"\a";
exit(0);
}
}
return 0;
}



