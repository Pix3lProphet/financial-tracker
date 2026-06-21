#include<iostream>
#include<fstream>
#include<string>
#include<array>

void enterexpense(void); //Function to enter expense, writes to existing file, create new if not found
void displayexpense(void); //Function to display expense from the existing file
std::array<std::string,2> monthyear(void);

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
		std::cout<<"Enter expense for "<<monthyear()[0]<<" "<<monthyear()[1]<< " Enter 0.00 to end.";
		for(int i =1;user_expense != 0.00;i++){
			std::cout<<"\nExpense "<<i<<": ";
			std::cin>>user_expense;
			file<<user_expense<<'\n';
			total_expense += user_expense;
			counter++;
		}
		file<< "Month: "<<monthyear()[0]<<" "<<monthyear()[1]<<"\n";
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
	std::string label,month,year; //To store string value from the file
	std::ifstream file("financial.txt");
	if(file.is_open()){
		if(file.peek() == std::ifstream::traits_type::eof()){ //Checks if file exists but no data recorded.
			std::cout<<"\nNo expense record found in the file\n\n";
		}
		else{
			std::getline(file,label,':');
			file>>month;
			std::getline(file,label);
			file>>year;
			file.ignore(1000,'\n');

			std::getline(file,label,':'); //To extract value after the delimeter ':'
			file>>expense_count;
	
			file.ignore(1000,'\n');
	
			std::getline(file,label,':');
			file>>total_expense;
			
			std::cout<<"Month: "<<month<<" Year: "<<year;
			std::cout<<"Number of expenditure: "<< expense_count<<'\n';
			std::cout<<"Total Expenditure: "<< total_expense<<'\n'<<std::endl;
		}
	}
	else{
		std::cout<<"\n\nFile not found\n\n";
	}
}
std::array<std::string,2> monthyear(void){
	std::string months[12] = {"Jan","Feb","Mar","Apr","May","Jun"
	,"Jul","Aug","Sep","Oct","Nov","Dec"};
	time_t now = time(nullptr); /*time returns the current timestamp. Used nullptr because time expects ptr of time_t*
								instead called it directly*/
	tm* local = localtime(&now);
	std::array<std::string,2> list;
	list[0] = months[local->tm_mon];
	list[1] = std::to_string(local->tm_year+1900);
	return list;

}
