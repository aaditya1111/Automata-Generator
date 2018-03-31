#include<iostream>
#include<stack>
#include<string>

using namespace std;

class PDA_Palindrome {
public:
	stack<char> input;
	int final_state;
	int cur_state;

	PDA_Palindrome() {
		final_state = 4;
		cur_state = 0;
	}

	bool is_digit(char digit) {
		if(digit >= 48 && digit <= 57)
			return true;
		return false;
	}

	bool is_slash(char slash) {
		if(slash == 47)
			return true;
		return false;
	}

	bool check_if_palindrome(string input_string) {
		string::iterator it = input_string.begin();
		char cur;
		int flag = 0;
		while(it != input_string.end()) {
			if(flag && input.size() == 0) {
				return false;
			}
			cur = *it;
			switch(cur_state) {
				case 0:
					if(is_digit(cur)) {
						input.push(cur);
						cur_state = 1;
					} else if(is_slash(cur)) {
						cur_state = 2;
						flag = 1;
					} else {
						return false;
					}
					break;
				
				case 1:
					if(is_digit(cur) && cur == input.top()) {
						input.push(cur);
						cur_state = 0;
					} else {
						return false;
					}
					break;

				case 2:
					if(is_digit(cur) && cur == input.top()) {
						input.pop();
						cur_state = 3;
					} else {
						return false;
					}
					break;

				case 3:
					if(is_digit(cur) && cur == input.top()) {
						input.pop();
						cur_state = 2;
					} else {
						return false;
					}
					break;

				default:
					break;
			}
			++it;
		}

		if(cur_state == 2 && input.size() == 0) {
			cur_state = 4;
		}

		if(cur_state == final_state) 
			return true;
		return false;
	}
};

void read_input() {
	string input_string;
	cout<<"\n"
		<<"INPUT FORMAT ::: \n"
		<<"\t> This program checks for palindromes made of digits "
		<<"\t> The pattern involves digits coming in pairs "
		<<"\t> Separate the repetition part of the palindrome with a '/' "
		<<"\t> Example : 0011/1100"
		<<"\n\n";

	cout<<"Enter the pattern : ";
	cin>>input_string;

	PDA_Palindrome pda;

	cout<<((pda.check_if_palindrome(input_string)) ? "\nPALINDROME !" : "\nNOT PALINDROME")<<endl;

	return;
}

int main() {
	read_input();
	return 0;
}
