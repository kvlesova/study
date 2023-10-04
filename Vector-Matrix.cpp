#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_array(double *A, int len) {
	for (int i = 0; i < len; i++) {
		printf("%9.2f", A[i]);
	}
	printf("\n");
}

class vector {
	double* arr;
	int len;
public:
	vector(const int Lenght);
	vector(const int Lenght, double ** Array);
	vector(const vector &orig);
	~vector();
	double *Varray() const;
	void print() const;
	vector operator+(const vector b) const {
		double * array = (double*) malloc(len * sizeof(double));
		for (int i = 0; i < len; i++)
			array[i] = arr[i] + b.arr[i];
		vector result(len, &array);
		return result;
	}
	vector &operator+=(const vector b) {
		for (int i = 0; i < len; i++) {
			arr[i] += b.arr[i];
		}
		return *this;
	}
	vector operator*(const double c) const {
		double * array = (double*)malloc(len * sizeof(double));
		for (int i = 0; i < len; i++)
			array[i] = arr[i] * c;
		vector result(len, &array);
		return result;
	}
	vector &operator*=(const double c) {
		for (int i = 0; i < len; i++)
			arr[i] *= c;
		return *this;
	}
	double operator*(const vector b) const {
		double a = 0;
		for (int i = 0; i < len; i++)
			a += arr[i] * b.arr[i];
		return a;
	}
	vector operator^(const vector b) const {
		double * array = (double*)malloc(len * sizeof(double));
		array[0] = arr[1] * b.arr[2] - arr[2] * b.arr[1];
		array[1] = arr[2] * b.arr[0] - arr[0] * b.arr[2];
		array[2] = arr[0] * b.arr[1] - arr[1] * b.arr[0];
		vector result(len, &array);
		return result;
	}
	vector &operator^=(const vector b) {
		vector mem = *this ^ b;
		for (int i = 0; i < 3; i++)
		arr[i] = mem.arr[i];
		return *this;
	}
};

vector::vector(int Lenght) {
	len = Lenght;
	arr = (double*)malloc(len * sizeof(double));
	for (int i = 0; i < len; i++)
		arr[i] = rand() % 10;
}

vector::vector(int Length, double ** Array) {
	len = Length;
	arr = *Array;
}

vector::vector(const vector &orig) {
	int len = orig.len;
	double *a = (double *)malloc(len * sizeof(double));
	for (int i = 0; i < len; i++)
		a[i] = orig.arr[i];
	this->arr = a;
	this->len = len;
}

vector::~vector() {
	free(this->arr);
}

double * vector::Varray() const {
	return arr;
}

void vector::print() const {
	print_array(arr, len);
}

class Matrix {
	double **matrix;
	int I;
	int J;
public:
	Matrix();
	Matrix(const int I, const int J);
	Matrix(double ***M);
	Matrix(const Matrix &orig);
	~Matrix();
	void print() const;
	Matrix operator+(const Matrix B) const;
	Matrix &operator+=(const Matrix B);
	Matrix operator*(const Matrix B) const;
	Matrix &operator*=(const Matrix B);
	vector operator*(const vector V) const;
};

Matrix::Matrix() {
	double **matrix;
	int I;
	int J;
}

Matrix::Matrix(const int Ii, const int Jj) {
	this->I = Ii;
	this->J = Jj;
	matrix = (double**)malloc(I * sizeof(double*));
	for (int i = 0; i < I; i++) {
		matrix[i] = (double*)malloc(J * sizeof(double));
		for (int j = 0; j < J; j++)
			matrix[i][j] = rand() % 10;
	}
}

Matrix::Matrix(double ***M) {
	matrix = *M;
}

Matrix::Matrix(const Matrix &orig) {
	I = orig.I;
	J = orig.J;
	matrix = (double**)malloc(I * sizeof(double*));
	for (int i = 0; i < I; i++) {
		matrix[i] = (double*)malloc(J * sizeof(double));
		for (int j = 0; j < J; j++)
			matrix[i][j] = orig.matrix[i][j];
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < I; i++)
		free(matrix[i]);
	free(matrix);
}

void Matrix::print() const {
	for (int i = 0; i < I; i++)
		print_array(matrix[i], J);
}

Matrix Matrix::operator+(const Matrix B) const {
	double **res = (double**)malloc(I * sizeof(double*));
	for (int i = 0; i < I; i++) {
		res[i] = (double*)malloc(J * sizeof(double));
		for (int j = 0; j < J; j++)
			res[i][j] = matrix[i][j] + B.matrix[i][j];
	}
	Matrix result(&res);
	result.I = I;
	result.J = J;
	return result;
}

Matrix &Matrix::operator+=(const Matrix B) {
	for (int i = 0; i < I; i++)
		for (int j = 0; j < J; j++)
			matrix[i][j] += B.matrix[i][j];
	return *this;
}

Matrix Matrix::operator*(const Matrix B) const {
	double **res = (double**)malloc(I*sizeof(double*));
	for (int i = 0; i < I; i++)
		res[i] = (double*)calloc(B.J, sizeof(double));
	for (int i = 0; i < I; i++)
		for (int k = 0; k < B.J; k++)
			for (int j = 0; j < J; j++)
				res[i][k] += matrix[i][j] * B.matrix[j][k];
	Matrix result(&res);
	result.I = I;
	result.J = B.J;
	return result;
}

Matrix &Matrix::operator*=(const Matrix B) {
	Matrix M = *this * B;
	J = B.J;
	for (int i = 0; i < I; i++)
		for (int j = 0; j < J; j++)
			matrix[i][j] = M.matrix[i][j];
	return *this;
}

vector Matrix::operator*(const vector V) const {
	double *v = V.Varray();
	double *arr = (double*)calloc(I, sizeof(double));
	for (int i = 0; i < I; i++)
		for (int j = 0; j < J; j++)
			arr[i] += matrix[i][j] * v[j];
	vector result(I, &arr);
	return result;
}

void main() {
	srand(time(NULL));
	int len = 5;
	vector V = vector(len);
	vector *T = new vector(len);
	vector R = *T;
	printf("a\n");
	V.print();
	printf("b\n");
	T->print();
	vector H = V + *T;
	printf("a+b\n");
	H.print();
	delete(T);
	V += R;
	printf("a+=b\n");
	V.print();
	vector O = V * 7;
	printf("a*7\n");
	O.print();
	V *= 8;
	printf("a*=8\n");
	V.print();
	double p = V * R;
	printf("a*b\n  %.3f\n", p);
	T = new vector(3);
	vector *T2 = new vector(3);
	printf("c\n");
	T->print();
	printf("d\n");
	T2->print();
	vector J = *T ^ *T2;
	printf("c^d\n");
	J.print();
	*T ^= *T2;
	printf("c^=d\n");
	T->print();
	delete(T);
	delete(T2);

	printf("=====================================\n");

	int i = 5, j = 4;
	Matrix M(i, j);
	printf("M1\n");
	M.print();
	Matrix *M2 = new Matrix(i, j);
	printf("M2\n");
	M2->print();
	Matrix F = M + *M2;
	printf("M1+M2\n");
	F.print();
	M += *M2;
	printf("M1+=M2\n");
	M.print();
	delete(M2);
	M2 = new Matrix(j, i);
	Matrix D = M * *M2;
	printf("M1 * M2\n");
	D.print();
	M *= *M2;
	printf("M1*=M2\n");
	M.print();
	T = new vector(i);
	printf("V\n");
	T->print();
	vector Y = M * *T;
	printf("M*V\n");
	Y.print();
	delete(T);
	delete(M2);
}