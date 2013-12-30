	/*			STOCKMASTER  v.1.0 (BETA)
		   The Ultimate Stock Management System						*/
#include <fstream>
#include <conio.h>
#include <process.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
using namespace std;

//class defined to hold user account data

class worker
{
	char wname[20];
	char designation[10];
	char password[18];
	int emp_no;
	public:
	worker()
	{
		emp_no=0;
	}
	char * return_password(){return password;}
	void enter_account_data();
	void display_account_data();
	void create_account();
	int return_emp_no(){return emp_no;}
	char * return_designation(){return designation;}
	void login();
}w1;

COORD coord={0,0}; // this is global variable
                                    //center of axis is set to the top left cornor of the screen
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
//class defined to hold items(stock)data

class stock
{
	int item_ID;
	char item_name[20];
	char item_type[20];
	int capacity;
	int amount;
	int alert_limit;
	long  item_price;
	public:
	stock()
	{
		item_ID=item_price=alert_limit=amount=capacity=0;
	}
	void update();
	void manage_items();
	void display();
	void display_status();
	void add_items();
	void item_add_details();
	void display_item_statusID(int);
	void display_item_statusNAME(char c[]);
	void display_item_statusTYPE(char d[]);
	void display_item_statusLIMIT(int);
	void display_item_statusPRICE(int,int);
	char *return_item_name(){	return item_name;}
	int return_item_price(){	return item_price;}
	int return_itemID(){		return item_ID;}
	int return_alert_limit(){	return alert_limit;}
	int return_amount(){		return amount;}
	char *return_item_type(){	return item_type;}
	void searchmenu();

}stock1;

void display_account();
void delete_account_info();
void stock_alert();

void facilities()
{
    int flag;
    system("CLS");
	for(int i=0;i<72;i++)
		cout<<"*";
	cout<<endl;
	cout<<"\t\t\t\tMAIN MENU\n";
	for(int j=0;j<72;j++)
		cout<<"*";
	gotoxy(15,8);
	cout<<"\n1.To display account information\n";
	gotoxy(15,9);
	cout<<"\n2.To delete existing account(Manager Only)\n";
	gotoxy(15,10);
	cout<<"\n3.to manage stock items\n";
	gotoxy(15,11);
	cout<<"\n4.Check for shortages\n";
	gotoxy(15,12);
	cout<<"\n5.Exit\n";
	int ch2;
	cin>>ch2;
	fflush(stdin);
	fstream f1;
	switch(ch2)
	{
		case 1:display_account();
		       break;
		case 2:
		       flag=0;
		       if(strcmp(w1.return_designation(),"manager")==0)
		       {
				flag=1;
				delete_account_info();
		       }
		       if(!flag)
		       cout<<"\nYou do not have this privilege\n";
		       getch();
		       f1.close();
		       facilities();
		       break;
		case 3:stock1.manage_items();
		       break;
		case 4:stock_alert();
		       break;
		case 5:exit(0);
	}
}

void worker::enter_account_data()
{
	system("CLS");
	fflush(stdin);
	cout<<"\nEnter name of employee : ";
	gets(wname);
	cout<<"\nEnter employee number of employee : ";
	cin>>emp_no;
	fflush(stdin);
	cout<<"\nEnter designation of employee : ";
	cin>>designation;
	fflush(stdin);
	cout<<"\nEnter desirable password : ";
	gets(password);
}

void create_account()
{
	system("CLS");
	fstream f1;
	f1.open("worker.dat",ios::out|ios::app);
	cout<<"\nEnter details of worker\n";
	w1.enter_account_data();
	f1.write((char*)&w1,sizeof(w1));
	cout<<"\nYour account has been created successfully\n";
	f1.close();
	w1.login();
}

void worker::display_account_data()
{
	cout<<"\nname of employee is "<<wname;
	cout<<"\nemployee number is "<<emp_no;
	cout<<"\ndesgnation of the employee is "<<designation;
}

void display_account()
{
	worker w3;
    system("CLS");
	cout<<"\nEnter employee number of the employee whose details need to be displayed\n";
	int emp1;
	cin>>emp1;
	fflush(stdin);
	int c=0;
	fstream f1;
	f1.open("worker.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&w3,sizeof(w3));
	while(!f1.eof())
	{
		if(emp1==w3.return_emp_no())
		{
			c++;
			w3.display_account_data();
			cout<<"\n\npress any key to continue..\n";
			getch();
		}
		f1.read((char *)&w3,sizeof(w3));
	}
	if(c==0)
	{
		cout<<"sorry account not found\n";
		getch();
	}
	f1.close();
	facilities();
}

void delete_account_info()
{
    system("CLS");
	worker w2;
	int c=0;
	fstream f2,f1;
	f1.open("worker.dat",ios::in);
	cout<<"\nEnter employee number of employee whose account is to be deleted\n";
	int emp;
	cin>>emp;
	fflush(stdin);
	if(emp!=w1.return_emp_no())
	{
		f2.open("temp.dat",ios::out);
		f1.seekg(0);
		f1.read((char *)& w2,sizeof(w2));
		while(!f1.eof())
		{
			if(emp!=w2.return_emp_no())
			{
				f2.write((char*)& w2,sizeof(w2));
			}
			if(emp==w2.return_emp_no())
			c++;
			f1.read((char*)&w2,sizeof(w2));
		}
		if(c==0)
		cout<<"\naccount not found\n";
		else
		cout<<"\nACCOUNT DELETED!!!\n";
		f1.close();
		f2.close();
		remove("worker.dat");
		rename("temp.dat","worker.dat");
	}
	else
	{
	for(int i=1;i<=5;i++)
	//textcolor(YELLOW+BLINK);
	cout<<"\nSORRY!! cannot delete logged in account!\n";
	}
//	textcolor(WHITE);
}

void worker::login()
{
    system("CLS");
	int ctr=0;
	fstream f1;
	do
	{
        system("cls");
		gotoxy(5,5);
		for(int i=0;i<72;i++)
		cout<<"*";
		cout<<endl;
		cout<<"\t\t\t\t    LOGIN";
		cout<<endl;
		cout<<"    ";
		for(int j=0;j<72;j++)
		cout<<"*";
		gotoxy(20,10);
		cout<<"enter your employee number: ";
		int emp;
		cin>>emp;
		fflush(stdin);
		gotoxy(20,12);
		cout<<"enter your password(case sensitive): ";
		char pass[18];
		fflush(stdin);
		gets(pass);
		f1.open("worker.dat",ios::in);
		f1.seekg(0);
		f1.read((char*) &w1,sizeof(w1));
		while(!f1.eof())
		{
			if((emp==w1.return_emp_no())&&(strcmp(pass,w1.return_password())==0))
			{
				gotoxy(20,19);
                cout<<"login successful\n";
				cout<<"\nPress any key to continue\n";
				getch();
				facilities();
				ctr=1;
			}
			f1.read((char*)&w1,sizeof(w1));
		}
	if(ctr==0)
	{
		gotoxy(20,15);
		cout<<"sorry, login unsuccessful\n";
		gotoxy(20,16);
		cout<<"please try again(check for case too)\n";
		gotoxy(20,18);
		cout<<"press any key\n";
		getch();
	}
	f1.close();
	}while(ctr==0);
	getch();
}

void stock_alert()
{
    system("cls");
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.read ((char*)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(stock1.return_amount()<=stock1.return_alert_limit())
		{
			stock1.display();
			for(int i=1;i<=5;i++)
//			textcolor(YELLOW+BLINK);
			cout<<"\nthere is a shortage of ";
			char name[20];
			strcpy(name,stock1.return_item_name());
			cout<<name;
			cout<<" in the stock\n";
		}
		f1.read((char*)&stock1,sizeof(stock1));
	}
//	textcolor(WHITE);
	f1.close();
	cout<<"\npress any key to continue...\n";
	getch();
	facilities();
}

void stock::display()
{
	cout<<"\nItem Name  : "<<item_name;
	cout<<"\nItem Type  : "<<item_type;
	cout<<"\nItem ID    : "<<item_ID;
	cout<<"\nCapacity   : "<<capacity;
	cout<<"\nTotal Stock: "<<amount;
	cout<<"\nAlert Limit: "<<alert_limit;
	cout<<"\nItem price : "<<item_price;
}

void stock::display_status()
{
    system("cls");
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		stock1.display();
		cout<<"\n";
		f1.read((char *)&stock1,sizeof(stock1));
	}
	f1.close();
	cout<<"\npress any key to go back...\n";
	getch();
	stock1.manage_items();
}

void stock::searchmenu()
{
    system("cls");
	for(int i=0;i<72;i++)
		cout<<"*";
	cout<<endl;
	cout<<"\t\t\t\tSEARCH MENU\n";
	for(int j=0;j<72;j++)
		cout<<"*";
	gotoxy(20,9);
	cout<<"\n1.Search for items by itemID";
	gotoxy(20,10);
	cout<<"\n2.Search for items by itemname";
	gotoxy(20,11);
	cout<<"\n3.Search for items by itemtype";
	gotoxy(20,12);
	cout<<"\n4.Search for items by alert limit";
	gotoxy(20,13);
	cout<<"\n5.Search for items by item cost";
	gotoxy(20,14);
	cout<<"\n6.Return to previous menu";
	gotoxy(20,15);
	cout<<"\n7.Exit\n";
	int choice;
	cin>>choice;
	fflush(stdin);
	switch(choice)
	{
			case 1:cout<<"\nEnter itemID of item whose status is to be displayed\n";
			       int item_ID1;
			       cin>>item_ID1;
			       fflush(stdin);
			       display_item_statusID(item_ID1);
			       break;
			case 2:cout<<"\nEnter name of item whose status is to be displayed\n";
			       char str[20];
			       gets(str);
			       display_item_statusNAME(str);
			       break;
			case 3:cout<<"\nEnter item type of the items whose status is to be displayed\n";
			       char item_typ[20];
			       cin>>item_typ;
			       fflush(stdin);
			       display_item_statusTYPE(item_typ);
			       break;
			case 4:cout<<"\nEnter alert limit of the item whose status is to be displayed\n";
			       int al_lim;
			       cin>>al_lim;
			       fflush(stdin);
			       display_item_statusLIMIT(al_lim);
			       break;
			case 5:cout<<"\nEnter price range in which the items should lie\n";
			       int lower_limit,upper_limit;
			       cout<<"\nEmter lower limit\n";
			       cin>>lower_limit;
			       fflush(stdin);
			       cout<<"\nEnter upper limit\n";
			       cin>>upper_limit;
			       fflush(stdin);
			       display_item_statusPRICE(lower_limit,upper_limit);
			       break;
			case 6:stock1.manage_items();
			       break;
			case 7:exit(0);
			       break;
	}
}

void stock::display_item_statusID(int itemID2)
{
    system("cls");
	int c=0;
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(itemID2==stock1.return_itemID())
		{
		stock1.display();
		c++;
		}
		f1.read((char *)&stock1,sizeof(stock1));
	}
	if(c==0)
	cout<<"\nSorry item not found\n";
	f1.close();
	cout<<"\nPress any key to go back...\n";
	getch();
	stock1.searchmenu();
}


void stock::display_item_statusNAME(char str1[])
{
    system("cls");
	int c=0;
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(strcmpi(str1,stock1.return_item_name())==0)
		{
			stock1.display();
			c++;
		}
		f1.read((char *)&stock1,sizeof(stock1));
	}
	if(c==0)
	cout<<"\nSorry item not found please try again..\n";
	f1.close();
	cout<<"\nPress any key to go back...\n";
	getch();
	stock1.searchmenu();
}

void stock::display_item_statusTYPE(char item_typ1[])
{
    system("cls");
	int c=0;
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if (strcmpi(item_typ1,stock1.return_item_type())==0)
		{
		stock1.display();
		c++;
		}
		f1.read((char *)&stock1,sizeof(stock1));
	}
	if(c==0)
	cout<<"\nSorry item not found please try again..\n";
	f1.close();
	cout<<"\nPress any key to go back...\n";
	getch();
	stock1.searchmenu();
}

void stock::display_item_statusLIMIT(int al_lim1)
{
    system("cls");
	int c=0;
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(al_lim1==return_alert_limit())
		{
		stock1.display();
		c++;
		}
		f1.read((char *)&stock1,sizeof(stock1));
	}
	if(c==0)
	cout<<"\nSorry item not found please try again...\n";
	f1.close();
	cout<<"\nPress any key to go back...\n";
	getch();
	stock1.searchmenu();
}

void stock::display_item_statusPRICE(int lower_limit1,int upper_limit1)
{
    system("cls");
	int c=0;
	fstream f1;
	f1.open("stock.dat",ios::in);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if ((stock1.return_item_price()<upper_limit1)&&(stock1.return_item_price()>lower_limit1))
		{
		stock1.display();
		c++;
		}
		f1.read((char *)&stock1,sizeof(stock1));
	}
	if(c==0)
	cout<<"\nSorry item not found please try again...\n";
	f1.close();
	cout<<"\nPress any key to go back...\n";
	getch();
	stock1.searchmenu();
}

void stock::item_add_details()
{
	cout<<"Enter item Name: ";
	fflush(stdin);
	gets(item_name);
	cout<<"Enter item Type: ";
	fflush(stdin);
	gets(item_type);
	cout<<"Enter Item ID: ";
	cin>>item_ID;
	fflush(stdin);
	cout<<"Enter Capacity: ";
	cin>>capacity;
	fflush(stdin);
	cout<<"Enter Total Stock: ";
	cin>>amount;
	fflush(stdin);
	while(amount>capacity)
	{
		cout<<"NOT ENOUGH ROOM TO STORE ALL PRODUCTS\n";
		cout<<"please enter Total Stock again\n";
		cin>>amount;
		fflush(stdin);
	}
	cout<<"Enter Alert Limit: ";
	cin>>alert_limit;
	fflush(stdin);
	cout<<"Enter cost of item: ";
	cin>>item_price;
	fflush(stdin);
}

void stock::add_items()
{
    system("cls");
	int flag=0;
	fstream f2;
	f2.open("worker.dat",ios::in);
	f2.read((char*)&w1,sizeof(w1));
	while(!f2.eof())
	{
		if(strcmp(w1.return_designation(),"manager")==0)
		{
			cout<<"\nYour designation is : "<<w1.return_designation()<<endl;
			flag=1;
			fstream f1;
			f1.open("stock.dat",ios::out|ios::app);
			cout<<"\nEnter details of item to add to the stock\n";
			item_add_details();
			cout<<"\nitem successfully added to stock\n";
			f1.write((char*)&stock1,sizeof(stock1));
			f1.close();
		}
		f2.read((char*)&w1,sizeof(w1));
	}
	if(!flag)
	{
		cout<<"\nYou do not have this privelege(Manager ONLY)\n";
	}
	f2.close();
	cout<<"press any key to go back...\n";
	getch();
	stock1.manage_items();
}

void edit_items()
{
    system("cls");
	int ItemID1;
	cout<<"Enter item ID of item to edit\n";
	cin>>ItemID1;
	fflush(stdin);
	fstream f1,f2;
	f1.open("stock.dat",ios::in);
	f2.open("temp.dat",ios::out);
	f1.read((char *)& stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(ItemID1==stock1.return_itemID())
		{
			cout<<"Enter new details\n";
			stock1.item_add_details();
		}
		f2.write((char *)&stock1,sizeof(stock1));
		f1.read((char*)&stock1,sizeof(stock1));
	}
	f1.close();
	f2.close();
	remove("stock.dat");
	rename("temp.dat","stock.dat");
	cout<<"press any key to go back...\n";
	getch();
	stock1.manage_items();
}


void delete_items(int itemID1)
{
    system("cls");
	fstream f1,f2;
	f1.open("stock.dat",ios::in);
	f2.open("temp.dat",ios::out);
	f1.seekg(0);
	f1.read((char *)&stock1,sizeof(stock1));
	while(!f1.eof())
	{
		if(itemID1!=stock1.return_itemID())
		f2.write((char*)& stock1,sizeof(stock1));
		f1.read((char *)&stock1,sizeof(stock1));
	}
	f1.close();
	f2.close();
	remove("stock.dat");
	rename("temp.dat","stock.dat");
	cout<<"\nItem Removed successfully\n";
	cout<<"press any key to go back...\n";
	getch();
	stock1.manage_items();
}

void stock::manage_items()
{
        system("cls");
		for(int i=0;i<72;i++)
			cout<<"*";
		cout<<endl;
		cout<<"\t\t\t\tSTOCK MENU\n";
		for(int j=0;j<72;j++)
			cout<<"*";
		gotoxy(25,8);
		cout<<"choose the action\n";
		gotoxy(16,9);
		cout<<"\n1. add more items";
		gotoxy(16,10);
		cout<<"\n2. edit item status";
		gotoxy(16,11);
		cout<<"\n3.remove existing item";
		gotoxy(16,12);
		cout<<"\n4.Display status of all items";
		gotoxy(16,13);
		cout<<"\n5.Search the stock for a particular item";
		gotoxy(16,14);
		cout<<"\n6.Return to previous menu";
		gotoxy(16,15);
		cout<<"\n7.Exit\n";
		int ch;
		cin>>ch;
		fflush(stdin);
		switch(ch)
		{
			case 1:add_items();
			       break;
			case 2:edit_items();
			       break;
			case 3:int itemID;
			       cout<<"\nEnter ID of item to be deleted\n";
			       cin>>itemID;
			       fflush(stdin);
			       delete_items(itemID);
			       break;
			case 4:display_status();
			       break;
			case 5:searchmenu();
			       break;
			case 6:facilities();
			       break;
			case 7:exit(0);
			       break;
		}
}


int main()
{
	//textcolor(WHITE);
    system("cls");
	gotoxy(18,9);
	cout<<"*******WELCOME TO STOCKMASTER VERSION 1.0(BETA)*******\n";
	gotoxy(30,20);
	cout<<"Press any key to continue";
	getch();
    system("cls");
	gotoxy(5,5);
	for(int i=0;i<72;i++)
			cout<<"*";
		cout<<endl;
		cout<<"\t\t\t\t    LOGIN";
		cout<<endl;
		cout<<"    ";
		for(int j=0;j<72;j++)
			cout<<"*";
	gotoxy(20,10);
	cout<<"\nDo you have an existing account(y/n): ";
	char ch1;
	cin>>ch1;
	fflush(stdin);
	if((ch1=='y')||(ch1=='Y'))
	{
		w1.login();
	}
	else if((ch1=='n')||(ch1=='N'))
	{
		char ch2;
		gotoxy(20,14);
		cout<<"do you wish to create an account?(y/n): ";
		cin>>ch2;
		fflush(stdin);
		if((ch2=='y')||(ch2=='Y'))
		create_account();
		else if((ch2=='n')||(ch2=='N'))
		{
		cout<<"\nexiting... press any key..";
		getch();
		}
		else
		{
		cout<<"\ninvalid choice.. exiting.. press any key..";
		getch();
		exit(0);
		}
	}
	else
	{
		cout<<"\ninvalid choice.. exiting.. press any key..";
		getch();
		exit(0);
	}
	return 0;
}
