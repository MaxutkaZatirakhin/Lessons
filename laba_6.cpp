// laba_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

void printMatrix(int** matrix, int rows, int cols) {
	if (matrix == nullptr) {
		cout << "Матрица пуста" << endl;
		return;
	}

	cout << "Матрица " << rows << "x" << cols << ":" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
int** createMatrix(int A, int B, int C, int D, int& rows, int& cols) {

	int** matrix = (int**)malloc(2 * sizeof(int*));
	for (int i = 0; i < 2; i++) {
		matrix[i] = (int*)malloc(2 * sizeof(int));
	}
	cout << A << B << C << D<< endl;
	matrix[0][0] = A;
	matrix[0][1] = B;
	matrix[1][0] = C;
	matrix[1][1] = D;
	printMatrix(matrix, 2, 2);

	rows = 2 + A;  
	cols = 2 + B;  
	// меняем память для матрицы через реалок
	matrix = (int**)realloc(matrix, rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int*)malloc(cols * sizeof(int));
	}
	for (int i = 0; i < rows; i++) {
		matrix[i] = (int*)realloc(matrix[i], cols * sizeof(int));
		if (i < 2) {
			for (int j = cols - 1; j >= B; j--) {
				matrix[i][j] = matrix[i][j - B];
			}
		}
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = i * C + j * D;
		}
	}

	return matrix;
}

int* findZeroRows(int** matrix, int rows, int cols, int& count) {
	count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == 0) {
				count++;
				break;
			}
		}
	}
	// Запись индексов
	int* zeroRows = (int*)malloc(count * sizeof(int));
	int index = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == 0) {
				zeroRows[index++] = i;
				break;
			}
		}
	}
	return zeroRows;
}

void DeleteRows(int**& matrix, int& rows, int cols, int* rowsToRemove, int removeCount) {
	if (removeCount == 0 || matrix == nullptr) {
		return;
	}

	// Сдвигаем строки, которые нужно сохранить, в начало матрицы
	int newIndex = 0;
	for (int i = 0; i < rows; i++) {
		bool shouldRemove = false;
		for (int j = 0; j < removeCount; j++) {
			if (i == rowsToRemove[j]) {
				shouldRemove = true;
				break;
			}
		}

		if (!shouldRemove) {
			// Если текущая строка не должна быть удалена, копируем ее на новую позицию
			if (newIndex != i) {
				for (int k = 0; k < cols; k++) {
					matrix[newIndex][k] = matrix[i][k];
				}
			}
			newIndex++;
		}
	}
	// Освобождаем память удаленных строк (от newIndex до rows-1)
	for (int i = newIndex; i < rows; i++) {
		free(matrix[i]);
	}
	// Изменяем размер матрицы
	rows = newIndex;
	// Перераспределяем память для указателей на строки
	if (rows > 0) {
		int** temp = (int**)realloc(matrix, rows * sizeof(int*));
		if (temp != nullptr) {
			matrix = temp;
		}
	}
	else {
		free(matrix);
		matrix = nullptr;
	}
}

void freeMatrix(int** matrix, int rows) {
	if (matrix == nullptr) return;

	for (int i = 0; i < rows; i++) {
		free(matrix[i]);
	}
	free(matrix);
}


int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "Пункт 1:\n";

	int A, B, C, D;
	
	do {
		cout << "Введите A (количество строк для добавления сверху): ";
		cin >> A;
		if (A < 0) {
			cout << "Ошибка! A должно быть неотрицательным числом. Попробуйте снова." << endl;
		}
	} while (A < 0);

	do {
		cout << "Введите B (количество столбцов для добавления слева): ";
		cin >> B;
		if (B < 0) {
			cout << "Ошибка! B должно быть неотрицательным числом. Попробуйте снова." << endl;
		}
	} while (B < 0);

	cout << "Введите C (коэффициент): ";
	cin >> C;

	cout << "Введите D (коэффициент): ";
	cin >> D;
	
	int rows, cols;
	int** matrix = createMatrix(A, B, C, D, rows, cols);

	cout << "\nРасширенная матрица:" << endl;
	printMatrix(matrix, rows, cols);



	int zeroRowsCount;
	int* zeroRows = findZeroRows(matrix, rows, cols, zeroRowsCount);

	cout << "Найдено строк с нулевыми значениями: " << zeroRowsCount << endl;
	if (zeroRowsCount > 0) {
		cout << "Индексы строк для удаления: ";
		for (int i = 0; i < zeroRowsCount; i++) {
			cout << zeroRows[i] << " ";
		}
		cout << endl << endl;
	}

	DeleteRows(matrix, rows, cols, zeroRows, zeroRowsCount);

	cout << "Матрица после удаления строк:" << endl;
	printMatrix(matrix, rows, cols);

	freeMatrix(matrix, rows);
	if (zeroRowsCount > 0) {
		free(zeroRows);
	}

	cout << "Пункт 2:\n";

	int a, b;
	cin >> a >> b;
	cout << a << " " << b << endl;

	int* ptrA = new int(a);
	int* ptrB = new int(b);
	*ptrA *= 2;
	int temp = *ptrA;
	*ptrA = *ptrB;
	*ptrB = temp;
	a = *ptrA;
	b = *ptrB;
	delete ptrA;
	delete ptrB;

	cout << a << " " << b << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
