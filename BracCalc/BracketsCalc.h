//������� �����������. �� ���� ����� �������� ��������� ����������� ������ � ���������� *, /, +, -, ^.
//�������������� ����� � �� ����� �����. ���� ������� ������������� ����� ����� =. 
#include <string>
using namespace std;

class CBracketsCalc
{
	public:
		float calculation(); //���������� ���� ��������
		bool validation(); //�������� �������� ������� �� ������������
		void input(string str); //���� �������

	private:
		string primer;

		char *operations;
		float *numbers;
		float *turns;

		int numbersCount;
		int operatorsCount;

		int brackets(int num); //������� ������ �������� ������������ ������
		float exp (float x, float y); //���������� � ����� �������
};
