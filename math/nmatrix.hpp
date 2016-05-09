/*
 *
 * nmatrix.hpp
 * By Ming Kai Chen
 *
 * purpose: defines generic 2-D Matrix and operations
 *
 */

#pragma once
#ifndef __NMAT__
#define __NMAT__

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdint>

namespace NMat {
	
	#define MAX_RAND 109
	
	template <typename T>
	class Matrix {
		protected:
			T* values;
			
			size_t indexHash(size_t row, size_t col) const {
				return row*ncol+col;
			}

			uint16_t nrow;
			uint16_t ncol;
		public:
			class Row {
				public:
					const T* values;
					const uint16_t size;

				private:
					Row(T* values, uint16_t size) : values(values), size(size) {}
			};
			
			uint16_t getNrow() const { return nrow; }
			uint16_t getNcol() const { return ncol; }
			
			Matrix(uint16_t row) : Matrix(row, 0) {}
			Matrix(uint16_t row, T scalar) : Matrix(row, row, scalar) {}
			Matrix(uint16_t row, uint16_t col, T scalar);
			Matrix(T** mat, uint16_t row, uint16_t col);
			Matrix(const T* values, uint16_t row, uint16_t col);
			Matrix(const Matrix<T>& src);
			virtual ~Matrix();
			Matrix<T>& operator = (const Matrix<T>& src);
			Matrix<T>& operator + (const Matrix<T>& b);
			Matrix<T>& operator * (const Matrix<T>& b);
			Matrix<T>& operator - (const Matrix<T>& b);
			Matrix<T>& operator * (T scalar);
			Matrix<T>& operator + (T scalar);

			void forEach(T (*operation)(T));
			// this is the first parameter of operation
			void forEach(const Matrix<T>& b, T (*operation)(T, T));
			
			// fills this with src at start
			void fill(const Matrix<T>& src, uint16_t startR = 0, uint16_t startC = 0);
			// places src to this at start
			void place(const Matrix<T>& src, uint16_t startR = 0, uint16_t startC = 0);

			// row operations
			void rowOp(uint16_t row, T (*operation)(T));
			void rowOp(uint16_t row, T (*operation)(T, T), const T* data, uint16_t datasize = -1);
			void rowInsert(uint16_t row, const T* data);
			const T* rowRead(uint16_t row) const;

			friend std::ostream& operator << (std::ostream& out, const Matrix& mat) {
		        for (uint16_t i = 0; i < mat.nrow; i++) {
		        	for (uint16_t j = 0; j < mat.ncol; j++) {
		        		out << mat.values[mat.indexHash(i, j)] << " ";
		        	}
		        	out << std::endl;
		        }
		        return out;
		    }
			
			T get(uint16_t row, uint16_t col) const {
				return values[indexHash(row, col)];
			}

			static Matrix<T>* inverse(const Matrix<T>& A);
			static Matrix<T>* transpose(const Matrix<T>& A);
			static Matrix<T>* diag(uint16_t nrow, uint16_t ncol);
			static Matrix<T>* rand(uint16_t nrow, uint16_t ncol, T (*randfunc)() = NULL);
	};
	
	template <typename T>
	Matrix<T>* mul(const Matrix<T>& A, const Matrix<T>& B);

	// numeral matrices only
	double determinant(Matrix<double>& A);
	Matrix<double>* GaussJordan(const Matrix<double>& A);

	#include "nmatrix.cpp"

}

#endif
