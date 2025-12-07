#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>

using namespace std;

//Цвета текста
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"


//Объявление переменных
HANDLE hStdout;
COORD destCoord;

const int matrix_order = 6; //можно изменить порядок на чётное число
const int num_count = matrix_order * matrix_order;
const int block_size = matrix_order / 2;
int matrix[matrix_order][matrix_order];


//Прототипы функций
int menu_commands(int choice);


//Функции
void separation() {
	cout << "\n";
}

void waiting() {
	separation();
	separation();
	cout << RED << "Нажмите Enter для продолжения..." << RESET << endl;
	cin.ignore();
	cin.get();
}

void clear_screen() {
	system("cls");
}

void clear_matrix() {
	int* end = *matrix + num_count - 1;
	for (int* p = *matrix; p <= end; p++) {
		*p = 0;
	}
	cout << GREEN << "Матрица успешно очищена!" << RESET << endl;
}

int get_random_num() {
	return rand() % (matrix_order * matrix_order) + 1;
}

void console_output(int* p) {
	destCoord.X = ((p - *matrix) % matrix_order) * 4 + 2;
	destCoord.Y = ((p - *matrix) / matrix_order + 1) * 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << *p;
	cout.flush();
	Sleep(200);
}

void matrix_output() {

	const int num_count = matrix_order * matrix_order;
	int* end = *matrix + num_count - 1;
	cout << BLUE;
	for (int* p = *matrix, element_num = 1; p <= end; p++, element_num++) {
		cout << setw(5) << *p;
		if (element_num % matrix_order == 0) {
			separation();
			separation();
		}
		else {
			cout << " ";
		}
	}
	cout << RESET;
}

void spiral_fill_matrix() {
	int* p = *matrix;
	int* right = p + (matrix_order - 1);
	int* left = p + ((matrix_order * matrix_order - 1) - (matrix_order - 1));
	int* up = p + matrix_order;
	int* down = p + (matrix_order * matrix_order - 1);
	int* end = p + (matrix_order * (matrix_order / 2) + (matrix_order / 2 - 1));

	*p = get_random_num(); // 1 элемент матрицы
	console_output(p);
	while (true) {
		while (p < right) {
			p++;
			*p = get_random_num();
			console_output(p);
		}
		right += matrix_order - 1;

		while (p < down) {
			p += matrix_order;
			*p = get_random_num();
			console_output(p);
		}
		down -= matrix_order + 1;

		while (p > left) {
			p--;
			*p = get_random_num();
			console_output(p);
		}
		left -= matrix_order - 1;
		if (p == end) {
			break;
		}

		while (p > up) {
			p -= matrix_order;
			*p = get_random_num();
			console_output(p);
		}
		up += matrix_order + 1;
	}
}

void zigzag_fill_matrix() {
	int* p = *matrix;
	int* down_border = p + (matrix_order * (matrix_order - 1));
	int* up_border = p + 1;
	int* end = p + matrix_order - 1;

	while (true) {
		*p = get_random_num();
		console_output(p);
		while (p < down_border) {
			p += matrix_order;
			*p = get_random_num();
			console_output(p);
		}
		p++;
		down_border += 2;

		*p = get_random_num();
		console_output(p);
		while (p > up_border) {
			p -= matrix_order;
			*p = get_random_num();
			console_output(p);
		}
		if (p == end) {
			break;
		}
		p++;
		up_border += 2;
	}
}

void matrix_sort() {
	int* left = *matrix;
	int* right = *matrix + num_count - 1;
	while (left <= right) {
		for (int* p = left; p < right; ++p) {
			if (*p > *(p + 1)) {
				swap(*p, *(p + 1));
			}
		}
		--right;

		for (int* p = right; p > left; --p) {
			if (*p < *(p - 1)) {
				swap(*p, *(p - 1));
			}
		}
		++left;
	}
}

void matrix_sort_menu() {
	cout << GREEN << "Матрица успешно отсортирована!" << RESET << endl;
	separation();
	cout << RED << "Матрица до сортировки:" << RESET << endl;
	matrix_output();
	separation();
	cout << RED << "Матрица после сортировки:" << RESET << endl;
	matrix_sort();
	matrix_output();
}

void second_page() {
	cout << RED << "Выберите способ заполнения матрицы:" << RESET << endl;
	cout << GREEN << "1) Спиральный (а)" << RESET << endl;
	cout << GREEN << "2) Зигзагообразный (б)" << RESET << endl;
	cout << endl;
	cout << RED << "Выбор: " << RESET;
	int second_page_choice;
	cin >> second_page_choice;
	clear_screen();
	cout << GREEN << "Заполнение матрицы: " << RESET << endl;
	cout << BLUE;
	switch (second_page_choice) {
	case 1:
		spiral_fill_matrix();
		break;
	case 2:
		zigzag_fill_matrix();
		break;
	}
	cout << RESET;
	destCoord.X = 0;
	destCoord.Y = matrix_order * 2 + 1;
	SetConsoleCursorPosition(hStdout, destCoord);
}

void reduce_elements(int& value) {
	const int num_count = matrix_order * matrix_order;
	int* end = *matrix + num_count - 1;
	for (int* p = *matrix; p <= end; p++) {
		*p -= value;
	}
}

void increase_elements(int& value) {
	const int num_count = matrix_order * matrix_order;
	int* end = *matrix + num_count - 1;
	for (int* p = *matrix; p <= end; p++) {
		*p += value;
	}
}

void multiply_elements(int& value) {
	const int num_count = matrix_order * matrix_order;
	int* end = *matrix + num_count - 1;
	for (int* p = *matrix; p <= end; p++) {
		*p *= value;
	}
}

void divide_elements(int& value) {
	const int num_count = matrix_order * matrix_order;
	int* end = *matrix + num_count - 1;
	for (int* p = *matrix; p <= end; p++) {
		*p /= value;
	}
}

void elements_operations_menu() {
	cout << RED << "Матрица до изменений:" << RESET << endl;
	matrix_output();
	separation();
	separation();
	cout << RED << "Выберите операцию над элементами матрицы:" << RESET << endl;
	cout << GREEN << "1) Уменьшить" << RESET << endl;
	cout << GREEN << "2) Увеличить" << RESET << endl;
	cout << GREEN << "3) Умножить" << RESET << endl;
	cout << GREEN << "4) Поделить" << RESET << endl;
	cout << RED << "Выбор: " << RESET;
	int user_choice;
	int value;
	cin >> user_choice;
	separation();
	switch (user_choice) {
	case 1:
		cout << RED << "Уменьшить элементы на: " << RESET;
		cin >> value;
		reduce_elements(value);
		break;
	case 2:
		cout << RED << "Увеличить элементы на: " << RESET;
		cin >> value;
		increase_elements(value);
		break;
	case 3:
		cout << RED << "Умножить элементы на: " << RESET;
		cin >> value;
		multiply_elements(value);
		break;
	case 4:
		cout << RED << "Поделить элементы на: " << RESET;
		cin >> value;
		divide_elements(value);
		break;
	}
	separation();
	cout << RED << "Матрица после изменений:" << RESET << endl;
	matrix_output();
}

void column_permutation() {
	cout << RED << "Матрица со случайными числами (от 1 до 100):" << RESET << endl;
	int* end = *matrix + (matrix_order * matrix_order) - 1;
	for (int* p = *matrix; p <= end; ++p) {
		*p = rand() % 100 + 1;
	}
	matrix_output();
	Sleep(2500);
	cout << GREEN << "Процесс перестановки: " << RESET << endl;
	int* p = *matrix;
	for (int i = 0; i < matrix_order; ++i) {
		separation();
		swap(*p, *(p + (matrix_order - 1)));
		p = p + matrix_order;
		matrix_output();
		Sleep(800);
	}
	cout << RED << "Матрица после перестановки первого и последнего столбца:" << RESET << endl;
	matrix_output();
}

void blocks_permutations(int* block_a, int* block_b) {

	int* pa;
	int* pb;
	int* end_row;

	for (int step = 0; step < block_size; ++step) {
		pa = block_a + step * matrix_order;
		pb = block_b + step * matrix_order;
		end_row = pa + block_size;

		while (pa < end_row) {
			swap(*pa, *pb);
			++pa;
			++pb;
		}
	}
}

void matrix_permutations_menu() {
	cout << RED << "Матрица до изменений:" << RESET << endl;
	matrix_output();
	separation();
	separation();
	cout << RED << "Выберите вид перестановки:" << RESET << endl;
	cout << GREEN << "1) Циклическая (a)" << RESET << endl;
	cout << GREEN << "2) Диагональная (b)" << RESET << endl;
	cout << GREEN << "3) Вертикальная (c)" << RESET << endl;
	cout << GREEN << "4) Горизонтальная (d)" << RESET << endl;
	cout << RED << "Выбор: " << RESET;
	int user_choice;
	cin >> user_choice;

	int step = matrix_order / 2;
	int* block_a = *matrix;
	int* block_b = block_a + step;
	int* block_c = *matrix + (matrix_order * step);
	int* block_d = block_c + step;

	separation();
	switch (user_choice) {
	case 1:
		blocks_permutations(block_a, block_b);
		blocks_permutations(block_a, block_d);
		blocks_permutations(block_a, block_c);
		break;
	case 2:
		blocks_permutations(block_a, block_d);
		blocks_permutations(block_b, block_c);
		break;
	case 3:
		blocks_permutations(block_a, block_c);
		blocks_permutations(block_b, block_d);
		break;
	case 4:
		blocks_permutations(block_a, block_b);
		blocks_permutations(block_c, block_d);
		break;
	}
	separation();
	cout << RED << "Матрица после изменений:" << RESET << endl;
	matrix_output();
}

void command_choice() {
	cout << RED << "Введите номер команды: " << RESET;
	int user_choice;
	cin >> user_choice;
	separation();
	menu_commands(user_choice);
}

int menu_commands(int choice) {
	switch (choice) {
	case 1:
		second_page();
		waiting();
		return 0;
		break;
	case 2:
		matrix_permutations_menu();
		waiting();
		return 0;
		break;
	case 3:
		matrix_sort_menu();
		waiting();
		return 0;
		break;
	case 4:
		clear_screen();
		elements_operations_menu();
		waiting();
		return 0;
		break;
	case 5:
		clear_screen();
		column_permutation();
		waiting();
		return 0;
		break;
	case 6:
		clear_screen();
		cout << RED << "Текущая матрица:" << RESET << endl;
		matrix_output();
		waiting();
		return 0;
		break;
	case 7:
		clear_matrix();
		waiting();
		return 0;
		break;
	default:
		cout << RED << "Ошибка! Введите номер команды от 1 до 7\n" << RESET << endl;
		command_choice();
		break;
	}
}

void lab_page() {
	cout << "|=======================================================|" << endl;
	cout << "|                 " << BLUE << "Лабораторная работа 3" << RESET << "                 |" << endl;
	cout << "|=======================================================|" << endl;
	cout << "| " << GREEN << "1) Заполнение матрицы по схемам" << RESET << "                       |" << endl;
	cout << "| " << GREEN << "2) Создать новую матрицу с помощью перестановок" << RESET << "       |" << endl;
	cout << "| " << GREEN << "3) Отсортировать матрицу" << RESET << "                              |" << endl;
	cout << "| " << GREEN << "4) Операции над элементами матрицы" << RESET << "                    |" << endl;
	cout << "| " << GREEN << "5) Перестановка столбцов (ИДЗ)" << RESET << "                        |" << endl;
	cout << "|                                                       |" << endl;
	cout << "| " << RED << "6) Вывести текущую матрицу" << RESET << "                            |" << endl;
	cout << "| " << RED << "7) Очистить матрицу" << RESET << "                                   |" << endl;
	cout << "|=======================================================|" << endl;
	cout << "|                 " << BLUE << "Лабораторная работа 3" << RESET << "                 |" << endl;
	cout << "|=======================================================|" << endl;
	cout << endl;
}


int main() {
	setlocale(0, "");
	srand(time(NULL));
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true) {
		lab_page();
		command_choice();
		clear_screen();
	}
	return 0;
}