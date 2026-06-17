#include<iostream>
#include<fstream>
#include<string>

void enterexpense(void); //Function to enter expense, writes to existing file, create new if not found
void displayexpense(void); //Function to display expense from the existing file

int main(){
	short user_choice;
	bool running_flag = true;
	while(running_flag){
		std::cout<<"Enter following for\nEntering expense:1\nDisplay total expense:2\nExit application:3\n";
		std::cin>>user_choice;
		switch(user_choice){
			case 1:
			enterexpense();
			break;

			case 2:
			displayexpense();
			break;

			case 3:
			running_flag = false;
			break;

			default:
			std::cout<<"\nWrong input\n";
			break;
		}
	}
	return 0;
}
void enterexpense(){
	std::cout<<"\n\n\n********************************************\n\n\n";
	std::ofstream file("financial.txt"); //Opening file, creates new file if not found
	if(file.is_open()){
		short counter; //tracks number of expense via increment in the for loop
		float user_expense; //Takes user exepense
		float total_expense; //Sum of user_expense
		std::cout<<"Enter expense. Enter 0.00 to end.";
		for(int i =1;user_expense != 0.00;i++){
			std::cout<<"\nExpense "<<i<<": ";
			std::cin>>user_expense;
			total_expense += user_expense;
			counter++;
		}
		file<< "Number of expenditure: "<<counter<<"\n";
		file<< "Total expenditure: "<<total_expense<<"\n";
		file.close();
	}
	else{
		std::cout<<"\nFile not found or is corrupted\n";
	}
}
void displayexpense(){
	std::cout<<"\n\n\n***************************\n\n";
	float expense_count,total_expense;
	std::string label; //To store string value from the file
	std::ifstream file("financial.txt");
	if(file.is_open()){
		if(file.peek() == std::ifstream::traits_type::eof()){
			std::cout<<"\nNo expense record found in the file\n\n";
		}
		else{

			std::getline(file,label,':'); //To extract value after the delimeter ':'
			file>>expense_count;
	
			file.ignore(1000,'\n');
	
			std::getline(file,label,':');
			file>>total_expense;
	
			std::cout<<"Number of expenditure: "<< expense_count<<'\n';
			std::cout<<"Total Expenditure: "<< total_expense<<'\n'<<std::endl;
		}
	}
	else{
		std::cout<<"\n\nFile not found\n\n";
	}
}
