#include <string>
#include "BracketsCalc.h"

float CBracketsCalc::calculation()
{
	char *new_operations;
	float *new_turns;

	if (numbersCount>1) {
		//����������� ��������� ���������� ��������
		for(int i=0; i<operatorsCount; i++) {
			switch (operations[i]) {
			case '^' : turns[i]=4.5; break;
			case '*' : turns[i]=4; break;
			case '/' : turns[i]=4; break;
			case '+' : turns[i]=3; break;
			case '-' : turns[i]=3; break;
			}
		}

		//��������� ���������� ������
		for(int i=0; i<operatorsCount; i++)
			if ((operations[i] == '*') || (operations[i] == '/') || (operations[i] == '+') || (operations[i] == '-') || (operations[i] == '^'))
				turns[i]=turns[i]+brackets(i);

		int t=0, h=0;

		for(int i=0; i<operatorsCount; i++) //������� ������� ��_��������� ��������
			if (!(operations[i]=='(' || operations[i]==')')) t++;

		new_turns=new float [t];
		new_operations=new char [t];

		//�������� ������� ����� � �������� � �����-������������. 
		//��� �� � ����� ������ �������� ������ �� ��������
		for(int i=0; i<operatorsCount; i++)
			if (!(operations[i]=='(' || operations[i]==')')) {
				new_operations[h]=operations[i];
				new_turns[h]=turns[i];
				h++;
			}


			int g, l, y;
			float max_priority = new_turns[0], min_priority = new_turns[0];
			//��������� ������������ � ����������� ���������
			for (int i=0; i<(numbersCount-1); i++) if (new_turns[i]>=max_priority) max_priority = new_turns[i]; 
			for (int i=0; i<(numbersCount-1); i++) if (new_turns[i]<=min_priority) min_priority = new_turns[i];


			//���������� ���� � ����� 0,25 ��� ��������.
			//�������� ���������: �������� ����������� �� �������� ����������, ����� ���������� � ������, �� �������� �����, ������������ ���������.
			//�������� ������������� 0 � ��� ������ ��� �������� ��������� �� ���� �����.
			for (float i=max_priority; i>=min_priority; i-=0.25) { 
				for (int j=0; j<(numbersCount-1); j++) {
					if (new_turns[j]==i) {
						switch (new_operations[j]) {
						case '*' : numbers[j+1]=numbers[j]*numbers[j+1]; new_operations[j]='0'; break;
						case '/' : numbers[j+1]=numbers[j]/numbers[j+1]; new_operations[j]='0'; break;
						case '+' : numbers[j+1]=numbers[j]+numbers[j+1]; new_operations[j]='0'; break;
						case '-' : numbers[j+1]=numbers[j]-numbers[j+1]; new_operations[j]='0'; break;
						case '^' : numbers[j+1]=exp(numbers[j], numbers[j+1]); new_operations[j]='0'; break;
						}
					}	
				}			

				l=0;
				g=0;
				y=0;

				//��� ���������� �������� ����� ��������
				do {
					if (new_operations[g]=='0') {
						for (y=g; y<numbersCount-l; y++) {
							new_operations[y]=new_operations[y+1];
							new_turns[y]=new_turns[y+1];
							numbers[y]=numbers[y+1];
						}	
						l++;
					} else g++;
				} while (g<numbersCount-l);
			}
	}

	return numbers[0]; //�� ��������� ���������� ������� ����� ������ ��������� � ������� ������ ������� numbers[]
}


bool CBracketsCalc::validation()
{
	//�������� ������������ �����
	//�������� ����� ����������� ������ ����� ������� �������
	int signCount=0;
	int openBrackets=0; int closeBrackets=0; int i=0;

	for(int i=0; i<primer.length()-1; i++) {
		if (!(primer[i]=='1' || primer[i]=='2' || primer[i]=='3' || primer[i]=='4' || primer[i]=='5' || primer[i]=='6' || primer[i]=='7' || 
			primer[i]=='8' || primer[i]=='9' || primer[i]=='0' || primer[i]=='.' || primer[i]=='(' || primer[i]==')' || primer[i]=='+' || 
			primer[i]=='-' || primer[i]=='*' || primer[i]=='/' || primer[i]==' ' || primer[i]=='\n' || primer[i]=='=' || primer[i]=='^')) 
			return false;

		if (((primer[i]=='(') && ((primer[i+1] == '*') || (primer[i+1] == '/') || 
			(primer[i+1] == '+') || (primer[i+1] == '-') || (primer[i+1] == '^'))) ||

			((primer[i+1]==')') && ((primer[i] == '*') || (primer[i] == '/') || 
			(primer[i] == '+') || (primer[i] == '-') || (primer[i] == '^'))))

			return false;
	} 

	for(int i=0; i<operatorsCount; i++) {
		if ((operations[i] == '*') || (operations[i] == '/') || 
			(operations[i] == '+') || (operations[i] == '-') || (operations[i] == '^'))
			signCount++;

		if (operations[i] == '(') openBrackets++;
		if (operations[i] == ')') closeBrackets++;

		if (((operations[i] == '(') && (operations[i+1] == ')')) ||
			((operations[i] == ')') && (operations[i+1] == '(')))
			return false;
	}

	for(int i=0; i<operatorsCount; i++) {
		if (operations[i] == '(') break;
		if (operations[i] == ')') return false; 
	}


	if ((signCount+1 !=numbersCount) || (openBrackets != closeBrackets)) return false;

	return true;
}


int CBracketsCalc::brackets(int num)
{
	//�����, �� ������� ����������� ��������� �������� ������, ����� ��������� ��������� �������:
	//	���� � ������� ������� ����������� ������ ����� � ������� ����������� ������ ����� �� ��������.
	//	������� ����� ����� ����� ������� � ����� �������������� �����������, ������� ���������� ��� �������.
	//	��� �� ����� ������� � ������� ����� �������� ������������� ������ �� ��������.
	//	������: (((1+2)+3+(4+5))+6). � �������� 4+5 ��� ����� ����� 3. � ��� �������� �������� ��� ������
	int open_brackets_left=0, close_brackets_left=0, brackets=0;
	for(int i=0; i<operatorsCount; i++)
	{
		if ((operations[i]=='(') && (i<=num)) open_brackets_left++;
		if ((operations[i]==')') && (i<=num)) close_brackets_left++;
	}
	brackets = open_brackets_left - close_brackets_left;

	return (brackets*2); //��������� �� 2 ����������, ��� �� ��������� �������� ����������� ��������
}



void CBracketsCalc::input(string str)
{
	primer=str;

	if (primer.length()<1)
		primer="0=";

	enum itsaNum {NO, YES}; 
	itsaNum isNum = NO;
	char ch='1';
	string str_num;
	int t = 0, h = 0; 

	operatorsCount=0; numbersCount=0;

	for (std::string::iterator it = primer.begin() ; it<primer.end(); ++it ) {
		if (*it == ' ') primer.erase(it);
	}

	int i=0;

	//������� ���� � �������. ������� � ���������� ���������� numbersCount, ��� �� ��� ������.
	do {
		ch=primer[i];  
		if(ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch==' ' || ch=='\n' || ch=='=' || ch=='^') {
			if( isNum == YES ) {                 
				numbersCount++;         
				isNum = NO;     
			}
		}                   
		else                
			if ( isNum == NO )     
				isNum= YES;

		if(ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
			operatorsCount++;

		i++;
	} while( ch !='=' && i<primer.length());

	turns=new float [operatorsCount];
	numbers=new float [numbersCount];
	operations=new char [operatorsCount];

	i=0;
	h=0;

	//���������� ����� �������, ����������. ����������� �� ������ �������� ������ �������� ������
	do { 
		ch=primer[i];
		if( ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='8' || ch=='9' || ch=='0' || ch=='.') {       
			isNum = YES; //���� ��� ������� - ������ ������������ ���� �����	
			str_num+=ch; //��������� ���� �����, ��� ������, ��������� ����������� ����� �, ���� ����, �����.
		}                        
		if (ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch==' ' || ch=='\n' || ch=='=' || ch=='^') {
			if (isNum == YES) {
				//�������� �� ���� ��������� ���� ���� ��������, �� �������� ������ 
				//���������� ����������� � ������ ����� � ����� � �������� ��� � ������ ������. ����� - ������� ������.
				numbers[t]=atof(str_num.c_str());  
				t++; 
				str_num.clear();
			}

			isNum = NO; //�.�. ���������� ��_�������� ������ - ����� �����������.

			if (ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^') {
				operations[h]=ch; //� ���, ���� ���� �������� ������ ��������, �������� ��� � ������ ��������
				h++; 
			}
		}
		i++;
	} while( ch !='=' && i<primer.length());    
}

float CBracketsCalc::exp (float x, float y)
{
	//�� ��� �� ������ � �������
	int z = x;
	if (y - (int) y == 0) {
		if (y>0) {
			for (int i=1; i<abs(y); i++)
				x *= z;
			return x;
		} else {
			for (int i=1; i<abs(y); i++)
				x *= z;
			return 1/x;
		}
	} else { 
		for (int i=1; i<y; i++)
			x = (int) x;
		x *= z;
		return (int) x;
	}
}