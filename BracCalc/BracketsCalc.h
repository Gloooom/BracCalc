//Простой калькулятор. На ввод можно подавать корректно оформленный пример с операциями *, /, +, -, ^.
//Поддерживаются целые и не целые числа. Ввод примера заканчивается после знака =. 
#include <string>
using namespace std;

class CBracketsCalc
{
	public:
		float calculation(); //выполнение всех операций
		bool validation(); //проверка введёного примера на правильность
		void input(string str); //ввод примера

	private:
		string primer;

		char *operations;
		float *numbers;
		float *turns;

		int numbersCount;
		int operatorsCount;

		int brackets(int num); //подсчёт уровня операции относительно скобок
		float exp (float x, float y); //возведение в целую степень
};
