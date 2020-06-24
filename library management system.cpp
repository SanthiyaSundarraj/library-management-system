//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
using namespace std;
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

#define clrscr system("cls");

void header()
{
	cout<<"**********************************************************************************************************\n                                          LIBRARY MANAGEMENT SYSTEM\n*********************************************************************************";
}
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
		cout<<"\nNEW BOOK ENTRY...\n";
		cout<<"\n\nEnter the book no. : ";		
		cin>>bno;
		cout<<"\n\nEnter The Name of The Book :";
		cin>>bname;
		cout<<"\n\nEnter The Author's Name :";
		cin>>aname;
		cout<<"\n\n\n\t\tBook Created..";
	}
	void show_book()
	{
		cout<<"\n\t\tBook no. : "<<bno;
		cout<<"\n\t\tBook Name : "<<bname;
		cout<<"\n\t\tAuthor Name : "<<aname;
	}

	void modify_book()
	{
		cout<<"\n\t\tBook no. : "<<bno;
		cout<<"\n\t\tModify Book Name : ";
		cin>>bname;
		cout<<"\n\t\tModify Author's Name of Book : ";
		cin>>aname;
	}

	string retbno()
	{
		return bno;
	}

	void report()
	{
		cout<<bno<<"\t\t"<<bname<<"\t\t\t\t"<<aname<<"\n";
	}


};         //class ends here


class student
{
	char admno[6];
	string name;
	string stbno;
	int token;
public:
	void create_student()
	{
		clrscr;
	 	cout<<"\n\t\t\t\t\tNEW STUDENT ENTRY...\n";
		cout<<"\n\t\tEnter The admission no. : ";
		cin>>admno;
		cout<<"\n\t\tEnter The Name of The Student : ";
		cin>>name;
		token=0;
		stbno="";
		cout<<"\n\n\t\t\t\tStudent Record Created..";
	}

	void show_student()
	{
		header();
		cout<<"\n\t\tAdmission no. : "<<admno;
		cout<<"\n\t\tStudent Name : "<<name;
		cout<<"\n\t\tNo of Book issued : "<<token;
		if(token==1)
			cout<<"\n\t\tBook No : "<<stbno;
	}

	void modify_student()
	{
		cout<<"\n\t\tAdmission no. : "<<admno;
		cout<<"\n\t\tModify Student Name : ";
		cin>>name;
	}

	string retadmno()
	{
		return admno;
	}

	string retstbno()
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

	void getstbno(string t)
	{
		stbno=t;
	}

	void report()
	{
	cout<<"\t"<<admno<<"\t\t\t"<<name<<"\t\t\t"<<token<<"\n";
	}

};         //class ends here




//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;
student st;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_book()
{
	char ch;
	fp.open("book.dat",ios::out|ios::app);
	do
	{
		clrscr;
		bk.create_book();
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\nDo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}

void write_student()
{
	char ch;
	fp.open("student.dat",ios::out|ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st,sizeof(student));
		cout<<"\n\ndo you want to add more record..(y/n?)  : ";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_spb(char n[])
{
	cout<<"\nBOOK DETAILS\n";
	int flag=0;
	fp.open("book.dat",ios::in);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.retbno()==n)
		{
			bk.show_book();
		 	flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
		cout<<"\n\nBook does not exist";
	getch();
}

void display_sps(char n[])
{
	cout<<"\nSTUDENT DETAILS\n";
	int flag=0;
	fp.open("student.dat",ios::in);
	while(fp.read((char*)&st,sizeof(student)))
	{
		if(st.retadmno()==n)
		{
			st.show_student();
			flag=1;
		}
	}
	
	fp.close();
	if(flag==0)
    		cout<<"\n\nStudent does not exist";
 	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{
	char n[6];
	int found=0,pos;
	clrscr;
	cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
	cout<<"\n\n\tEnter The book no. of The book";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&bk,sizeof(book)) && found==0)
	{
		if(bk.retbno()==n)
		{
			bk.show_book();
			cout<<"\nEnter The New Details of book"<<endl;
			bk.modify_book();
			 pos=-1*(sizeof(book));
		    	fp.seekp(pos,ios::cur);
		    	fp.write((char*)&bk,sizeof(book));
		    	cout<<"\n\n\t Record Updated";
		    	found=1;
		}
	}

    	fp.close();
    	if(found==0)
    		cout<<"\n\n Record Not Found ";
    	getch();
}


void modify_student()
{
	char n[6];
	int found=0,pos;
	clrscr;
	cout<<"\n\n\tMODIFY STUDENT RECORD... ";
	cout<<"\n\n\tEnter The admission no. of The student";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	{
		if(st.retadmno()==n)
		{
			st.show_student();
			cout<<"\n\t\t\t\tEnter The New Details of student"<<endl;
			st.modify_student();
			pos=-1*(sizeof(student));
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	
	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_student()
{
	char n[6];
	int flag=0;	
	clrscr;
    	cout<<"\n\n\n\t\t\t\tDELETE STUDENT...";
    	cout<<"\n\n\t\tEnter The admission no. of the Student You Want To Delete : ";
    	cin>>n;
    	fp.open("student.dat",ios::in|ios::out);
    	fstream fp2;
    	fp2.open("Temp.dat",ios::out);
    	fp.seekg(0,ios::beg);
    	while(fp.read((char*)&st,sizeof(student)))
	{
		if(st.retadmno()!=n)
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
    	getch();
}


void delete_book()
{
	char n[6];
	clrscr;
	cout<<"\n\n\n\t\t\tDELETE BOOK ...";
	cout<<"\n\n\t\tEnter The Book no. of the Book You Want To Delete : ";
	cin>>n;
	fp.open("book.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&bk,sizeof(book)))
	{
		if(bk.retbno()!=n)  
		{
			fp2.write((char*)&bk,sizeof(book));
		}
	}
    	
	fp2.close();
    	fp.close();
    	remove("book.dat");
    	rename("Temp.dat","book.dat");
    	cout<<"\n\n\tRecord Deleted ..";
    	getch();
}



//***************************************************************
//    	function to display all students list
//****************************************************************

void display_alls()
{
	clrscr;
     	fp.open("student.dat",ios::in);
     	if(!fp)
     	{
       		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
       		return;
     	}

	cout<<"\n\n\t\tSTUDENT LIST\n\n";
	cout<<"==================================================================\n";
	cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
	cout<<"==================================================================\n";

	while(fp.read((char*)&st,sizeof(student)))
	{
		st.report();
	}
     	
	fp.close();
	getch();
}


//***************************************************************
//    	function to display Books list
//****************************************************************

void display_allb()
{
	clrscr;
	fp.open("book.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       		getch();
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
     	getch();
}



//***************************************************************
//    	function to issue book
//****************************************************************

void book_issue()
{
	char sn[6],bn[6];
	int found=0,flag=0;
	clrscr;
	cout<<"\n\nBOOK ISSUE ...";
	cout<<"\n\n\tEnter The student's admission no.";
	cin>>sn;
	fp.open("student.dat",ios::in|ios::out);
    	fp1.open("book.dat",ios::in|ios::out);
    	while(fp.read((char*)&st,sizeof(student)) && found==0)
       	{
		if(st.retadmno()==sn)
		{
			found=1;
			if(st.rettoken()==0)
			{
		      		cout<<"\n\n\tEnter the book no. ";
				cin>>bn;
				while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
				{
			   		if(bk.retbno()==bn)
					{
						bk.show_book();
						flag=1;
						st.addtoken();
						st.getstbno(bk.retbno());
       						int pos=-1*sizeof(student);
						fp.seekp(pos,ios::cur);
						fp.write((char*)&st,sizeof(student));
						cout<<"\n\n\t Book issued successfully\n\n\n\t\tPlease Note: Write the current date in backside of your book and submit within 15 days Else fine Rs. 1 for each day after 15 days period is included...\n\n";
					}
		    		}
		  		if(flag==0)
		    			cout<<"Book no does not exist";
			}
	    		else
		  		cout<<"You have not returned the last book ";

		}
	}
      	if(found==0)
		cout<<"Student record not exist...";
	getch();
  	fp.close();
  	fp1.close();
}

//***************************************************************
//    	function to deposit book
//****************************************************************

void book_deposit()
{
    string sn,bn;
    int found=0,flag=0,day,fine;
    clrscr;
    cout<<"\n\n\t\t\t\tBOOK DEPOSIT ...";
    cout<<"\n\n\t\tEnter The student’s admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	    if(st.retadmno()==sn)
	    {
		    found=1;
		    if(st.rettoken()==1)
		    {
			while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
			{
			   if(bk.retbno()==st.retstbno())
			{
				bk.show_book();
				flag=1;
				cout<<"\n\n\t\tBook deposited in no. of days : ";
				cin>>day;
				if(day>15)
				{
				   fine=(day-15)*1;
				   cout<<"\n\n\t\tFine has to deposited Rs. : "<<fine;
				}
					st.resettoken();
					int pos=-1*sizeof(st);
					fp.seekp(pos,ios::cur);
					fp.write((char*)&st,sizeof(student));
					cout<<"\n\n\t Book deposited successfully";
			}
		    }
		  if(flag==0)
		    cout<<"Book no does not exist";
		      }
		 else
			cout<<"No book is issued..please check!!";
		}
	   }
      if(found==0)
	cout<<"Student record not exist...";
	getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	clrscr;
	////gotoxy(35,11);
	cout<<"\n\n\n\t\t\t\t\t\t\tLIBRARY   ";
	////gotoxy(35,14);
	cout<<"MANAGEMENT   ";
	////gotoxy(35,17);
	cout<<"SYSTEM\n\n";
	cout<<"\n\n\t\t\t\tMADE BY : \n\n\n\t\t\t\t\tSANTHIYA.S,18 31 048\n\t\t\t\t\tMSc.Software Systems\n\t\t\t\t\tCoimbatore Institute of Technology\n\n";
	getch();
}



//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	clrscr;
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.CREATE BOOK ";
	cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
	cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout<<"\n\n\t9.MODIFY BOOK ";
	cout<<"\n\n\t10.DELETE BOOK ";
	cout<<"\n\n\t11.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
	cin>>ch2;
	switch(ch2)
	{
    		case 1: clrscr;
	    		write_student();break;
    		case 2: display_alls();break;
    		case 3:
	       		char num[6];
	       		clrscr;
	       		cout<<"\n\n\tPlease Enter The Admission No. ";
	       		cin>>num;
	       		display_sps(num);
	       		break;
      		case 4: modify_student();break;
      		case 5: delete_student();break;
		case 6: clrscr;
			write_book();break;
		case 7: display_allb();break;
		case 8: {
	       		char num[6];
	       		clrscr;
	       		cout<<"\n\n\tPlease Enter The book No. ";
	       		cin>>num;
	       		display_spb(num);
	       		break;
			}
      		case 9: modify_book();break;
      		case 10: delete_book();break;
     		case 11: return;
      		default:cout<<"\a";
   	}
   	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
	char ch;
	intro();
	do
	{
		clrscr;
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. BOOK ISSUE";
		cout<<"\n\n\t02. BOOK DEPOSIT";
	  	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  	cout<<"\n\n\t04. EXIT";
	  	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  	ch=getche();
	  	switch(ch)
	  	{
			case '1':clrscr;
				 book_issue();
			   	 break;
		  	case '2':book_deposit();
			    	 break;
		  	case '3':admin_menu();
				 break;
		  	case '4':
			  	clrscr;
				cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tThank you for visiting..Have a nice day...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			  	exit(0);
		  	default :cout<<"\a";
		}
    	}while(ch!='4');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
