/*
 *
 * nmatrix.cpp
 * By Ming Kai Chen
 *
 * purpose: implements generic 2-D Matrix and operations
 *
 */

#ifdef __NMAT__

static const uint16_t LEAF_SIZE = 56;

template <typename T>
Matrix<T>::Matrix(uint16_t row, uint16_t col, T scalar) : nrow(row), ncol(col) {
	values = new T[row*col];
	size_t limit = (size_t) row * col;
	if (0 == scalar) memset(values, 0, sizeof(T)*limit);
	else std::fill_n(values, limit, scalar);
}

template <typename T>
Matrix<T>::Matrix(T** mat, uint16_t row, uint16_t col) : nrow(row), ncol(col) {
	values = new T[row*col];
	for (uint16_t i = 0; i < nrow; i++) {
		for (uint16_t j = 0; j < ncol; j++) {
			values[indexHash(i, j)] = mat[i][j];
		}
	}
}

template <typename T>
Matrix<T>::Matrix(const T* values, uint16_t row, uint16_t col) : nrow(row), ncol(col) {
	this->values = new T[row*col];
	memcpy(this->values, values, sizeof(T)*nrow*ncol);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& src) : nrow(src.nrow), ncol(src.ncol) {
	values = new T[nrow*ncol];
	memcpy(values, src.values, sizeof(T)*nrow*ncol);
}

template <typename T>
Matrix<T>::~Matrix() {
	delete[] values;
}

template <typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& src) {
	if (this != &src) {
        delete[] values;
        nrow = src.nrow;
        ncol = src.ncol;
		values = new T[nrow*ncol];
		memcpy(values, src.values, sizeof(T)*nrow*ncol);
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator + (const Matrix<T>& b) {
	forEach(b, [](T value1, T value2) -> T {
		return value1 + value2;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator * (const Matrix<T>& b) {
	forEach(b, [](T value1, T value2) -> T {
		return value1 * value2;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator - (const Matrix<T>& b) {
	forEach(b, [](T value1, T value2) -> T {
		return value1 - value2;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator * (T scalar) {
	forEach([scalar](T value) -> T {
		return value * scalar;
	});
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator + (T scalar) {
	forEach([scalar](T value) -> T {
		return value + scalar;
	});
	return *this;
}

template <typename T>
void Matrix<T>::forEach(T (*operation)(T)) {
    size_t limit = (size_t) nrow * ncol;
	for (size_t i = 0; i < limit; i++) {
		values[i] = operation(values[i]);
	}
}

template <typename T>
void Matrix<T>::forEach(const Matrix<T>& b, T (*operation)(T, T)) {
	size_t limit = (size_t) nrow * ncol;
	if ((size_t) b.nrow * b.ncol != limit) return;
	for (size_t i = 0; i < limit; i++) {
		values[i] = operation(values[i], b.values[i]);
	}
}

template <typename T>
void Matrix<T>::fill(const Matrix<T>& src, uint16_t startR, uint16_t startC) {
	assert(src.nrow > startR && src.ncol > startC);
	for (uint16_t i = startR; i < src.nrow && i < startR+nrow; i++) {
		for (uint16_t j = startC; j < src.ncol && j < startC+ncol; j++) {
			values[indexHash(i-startR, j-startC)] = src.values[src.indexHash(i, j)];
		}
	}
}

template <typename T>
void Matrix<T>::place(const Matrix<T>& src, uint16_t startR, uint16_t startC) {
	assert(nrow > startR && ncol > startC);
	for (uint16_t i = startR; i < startR+src.nrow && i < nrow; i++) {
		for (uint16_t j = startC; j < startC+src.ncol && j < ncol; j++) {
			values[indexHash(i, j)] = src.values[src.indexHash(i-startR, j-startC)];
		}
	}
}

template <typename T>
void Matrix<T>::rowOp(uint16_t row, T (*operation)(T)) {
	for (uint16_t i = 0; i < ncol; i++) {
		values[indexHash(row, i)] = operation(values[indexHash(row, i)]);
	}
}

template <typename T>
void Matrix<T>::rowOp(uint16_t row, T (*operation)(T, T), const T* data, uint16_t datasize) {
	if (datasize > ncol) datasize = ncol; 
	for (uint16_t i = 0; i < datasize; i++) {
		values[indexHash(row, i)] = operation(values[indexHash(row, i)], data[i]);
	}
}

template <typename T>
void Matrix<T>::rowInsert(uint16_t row, const T* data) {
	memcpy(values+indexHash(row, 0), data, sizeof(T)*ncol);
}

template <typename T>
const T* Matrix<T>::rowRead(uint16_t row) const {
	return values+indexHash(row, 0);
}

template <typename T>
Matrix<T>* Matrix<T>::transpose(const Matrix<T>& A) {
	uint16_t c = A.nrow;
	uint16_t r = A.ncol;
	Matrix<T>* tmat = new Matrix<T>(r, c, 0);
	for (uint16_t i = 0; i < tmat->nrow; i++) {
		for (uint16_t j = 0; j < tmat->ncol; j++) {
			tmat->values[tmat->indexHash(i, j)] = A.values[A.indexHash(j, i)];
		}
	}
	return tmat;
}

template <typename T>
Matrix<T>* Matrix<T>::diag(uint16_t nrow, uint16_t ncol) {
	Matrix<T>* m = new Matrix<T>(nrow, ncol, 0);
	uint16_t min = nrow > ncol ? ncol : nrow;
	for (uint16_t i = 0; i < min; i++) {
		m->values[m->indexHash(i, i)] = 1;
	}
	return m;
}

template <typename T>
Matrix<T>* Matrix<T>::rand(uint16_t nrow, uint16_t ncol, T (*randfunc)()) {
	Matrix<T>* m = new Matrix<T>(nrow, ncol, 0);
    size_t limit = (size_t) nrow * ncol;
	for (size_t i = 0; i < limit; i++) {
		m->values[i] = NULL == randfunc ? std::rand() % MAX_RAND : randfunc();
	}
	return m;
}

template <typename T>
Matrix<T>* mulN3(const Matrix<T>& A, const Matrix<T>& B) {
	if (A.getNcol() != B.getNrow()) return NULL;
	uint16_t M = A.getNrow();
	uint16_t J = A.getNcol();
	uint16_t N = B.getNcol();
	size_t len = M*N;
	T* input = new T[len];
	for (uint16_t r = 0; r < M; r++) {
		for (uint16_t c = 0; c < N; c++) {
			input[r*N+c] = 0;
			for (uint16_t l = 0; l < J; l++) {
				input[r*N+c] += A.get(r, l) * B.get(l, c);
			}
		}
	}
	Matrix<T>* product = new Matrix<T>(input, M, N);
	delete[] input;
	return product;
}

template <typename T>
Matrix<T>* mul(const Matrix<T>& A, const Matrix<T>& B) {
	Matrix<T>* product = NULL;
	uint16_t M = A.getNrow();
	uint16_t J = A.getNcol();
	uint16_t N = B.getNcol();
	if (J != B.getNrow()) return product;
	uint16_t max = M > N ? M : N;
	if (J > max) {
		max = J;
	}
	
	if (max < LEAF_SIZE) {
		product = mulN3(A, B);
	} else {
		product = new Matrix<T>(M, N, 0);
		if (max % 2 == 1) {
			max++;
		}
		uint16_t half = max/2;
		
		Matrix<T> A1(half);
		Matrix<T> A2(half);
		Matrix<T> A3(half);
		Matrix<T> A4(half);
		Matrix<T> B1(half);
		Matrix<T> B2(half);
		Matrix<T> B3(half);
		Matrix<T> B4(half);
		
		A1.fill(A);
		A2.fill(A, 0, half);
		A3.fill(A, half, 0);
		A4.fill(A, half, half);
		
		B1.fill(B);
		B2.fill(B, 0, half);
		B3.fill(B, half, 0);
		B4.fill(B, half, half);
		
		Matrix<T>* M1;
		{
			Matrix<T> buffer = A1;
			Matrix<T> buffer2 = B1;
			M1 = mul(buffer+A4, buffer2+B4);
		}
		Matrix<T>* M2;
		{
			Matrix<T> buffer = A3;
			M2 = mul(buffer+A4, B1);
		}
		Matrix<T>* M3;
		{
			Matrix<T> buffer = B2;
			M3 = mul(A1, buffer-B4);
		}
		Matrix<T>* M4;
		{
			Matrix<T> buffer = B3;
			M4 = mul(A4, buffer-B1);
		}
		Matrix<T>* M5;
		{
			Matrix<T> buffer = A1;
			M5 = mul(buffer+A2, B4);
		}
		Matrix<T>* M6 = mul(A3-A1, B1+B2);
		Matrix<T>* M7 = mul(A2-A4, B3+B4);

		Matrix<T> C1 = *M1; // C1
		product->fill(C1+*M4-*M5+*M7);
		Matrix<T> C4 = *M1; // C4
		product->place(C4-*M2+*M3+*M6, half, half);
		// C2
		product->place(*M3+*M5, 0, half);
		// C3
		product->place(*M2+*M4, half, 0);
		delete M1;
		delete M2;
		delete M3;
		delete M4;
		delete M5;
		delete M6;
		delete M7;
	}
	
	return product;
}

bool crout(const Matrix<double>* Ain, Matrix<double>*& Lout, Matrix<double>*& Uout) {
	Lout = NULL;
	Uout = NULL;
	if (Ain->getNrow() != Ain->getNcol()) return false;
	uint16_t n = Ain->getNrow();
	double** L = new double*[n];
	double** U = new double*[n];

	for (uint16_t i = 0; i < n; i++) {
		L[i] = new double[n];
		U[i] = new double[n];
		U[i][i] = 1;
	}

	for (uint16_t j = 0; j < n; j++) {
		for (uint16_t i = j; i < n; i++) {
			double sum = 0;
			for (uint16_t k = 0; k < j; k++) {
				sum += L[i][k] * U[k][j];	
			}
			L[i][j] = Ain->get(i, j) - sum;
		}

		for (uint16_t i = j; i < n; i++) {
			double sum = 0;
			for(uint16_t k = 0; k < j; k++) {
				sum += L[j][k] * U[k][i];
			}
			if (L[j][j] == 0) {
				for (uint16_t i = 0 ; i < n; i++) {
					delete[] L[i];
					delete[] U[i];
				}
				delete[] L;
				delete[] U;
				return false;
			}
			U[j][i] = (Ain->get(j, i) - sum) / L[j][j];
		}
	}

	Lout = new Matrix<double>(L, n, n);
	Uout = new Matrix<double>(U, n, n);
	for (uint16_t i = 0 ; i < n; i++) {
		delete[] L[i];
		delete[] U[i];
	}
	delete[] L;
	delete[] U;
	return true;
}

double determinant(Matrix<double>& A) {
	Matrix<double>* L;
	Matrix<double>* U;
	if (crout(&A, L, U)) {
		uint16_t r = L->getNrow();
		uint16_t c = L->getNcol();
		uint16_t min = r > c ? c : r;
		double det = 1;
		for (uint16_t i = 0; i < min; i++) {
			det *= L->get(i, i);
		}
		delete L;
		delete U;
		return det;
	} else {
		return 0;
	}
}

template<typename T>
Matrix<T>* Matrix<T>::inverse(const Matrix<T>& A) {
	return NULL;
}

Matrix<double>* GaussJordan(const Matrix<double>& A) {
	return NULL;
}

#endif