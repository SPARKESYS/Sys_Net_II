#include <iostream>
#include <sstream>
#include <stdio.h>      
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fstream>
#include <dirent.h>
#include <unistd.h>

#include "user.hpp"

using namespace std;

//CONSTRUCTORS///////////////////////////////////////////////////////////////////////////////////
User::User()
{
	_username = NULL;
	_password = NULL;
	_admin = false; // no background processing
	_accountNumber = 0;
	_socketNumber = -1;
		
} 

User::User (char* username, char* password, char admin, char* accountNumber)
{
		_username = username;
		_password = password;
		if(admin == 'A')
		{
			_admin = true;
		}else _admin = false;
		_accountNumber = accountNumber;
}

//SETTERS/////////////////////////////////////////////////////////////////////////////////////////
void User::setUsername (char *username)
{
	_username = username;
}
  
void User::setPassword(char *password)
{
	_pasword = password;
}

void User::setAdmin(bool admin);
{
	_admin = admin;
}

void User::setAccountNumber(char *accountNumber)
{
	_accountNumber = accountNumber;
}

//DEBUGGING////////////////////////////////////////////////////////////////////////////////////////
void User::printUser()    
{ 
	cout << "username: [" << ((_username != NULL) ? _username : "NULL") << "]" << endl <<         
			"password: [" << ((_password != NULL) ? _password : "NULL") << "]" << endl;         
 
}

//GETTERS////////////////////////////////////////////////////////////////////////////////////////
char* User::getUsername()
{
	return _username;
}

char* User::getPassword()
{
	return _password;
}

char* User::getAdmin()
{
	return _admin;
}

//PRINTERS///////////////////////////////////////////////////////////////////////////////////////
void User::printFile()
{
	
	if(_argumentVector[1] == NULL)
	{
		return;
	}
	if(_argumentVector[1][0] == '<')
	{
		ifstream f(_username);
		if(f.is_open())
		{
			cout<<f.rdbuf();
		}
		return;
	}
	else 
	{
		ifstream f(_argumentVector[1]);
		if(f.is_open())
		{
			cout<<f.rdbuf();
		}
		return;
	}
	return;
	//prints out file until it reaches the end
	
	

}

void User::printDir()
{
	
	DIR*    dir;
	dirent* pdir;
	char* files[255];

	if(_argumentCount >= 3 && _argumentVector[2][0]== '>')
	{
		dir = opendir(".");
		int i = 0;
		FILE *fp;
		fp = fopen(_password,"w");
		while (pdir = readdir(dir)) 
		{
		    //files[i] = pdir->d_name;
		    fprintf(fp,pdir->d_name);
		    fprintf(fp,"\n");
		    i++;
		}
		fclose(fp);
	}
	else
	{	
		dir = opendir(".");
		int i = 0;
		while (pdir = readdir(dir)) 
		{
			
		    files[i] = pdir->d_name;
		    if(i%5==0 && i!=0)
		    {
		    	cout<<endl;
		    }
		    cout<<files[i]<<"\t";
		    i++;
		}
		cout<<endl;
	}
}

void User::grep()
{
	ifstream fp (_argumentVector[3]);
	string buffer;
	char buff2[255];
	if(fp == NULL)
	{
		cout<<"file can't be opened"<<endl;
		return;
	}
	else
	{
		while(getline(fp,buffer))
		{
			strcpy(buff2,buffer.c_str());
			char* token = strtok(buff2, " \t\n");

			if (token == NULL) {
				return;
			}
			while (token != NULL) 
			{
	
				if(strcmp(token,_argumentVector[2])==0)
			    {
			    	cout<<buffer<<endl;
				}
				// get next token
				token = strtok (NULL, " \t\n");
				
		    }
		}
	}
	
}

//FLAGS//////////////////////////////////////////////////////////////////////////////////////////



