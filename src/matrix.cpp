#include "../include/matrix.hpp"

#include <iostream>
#include <random>

namespace {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1, 100);

int GenerateRandomNumber() { return dist(gen); }
} // namespace

Matrix::Matrix(int rows, int columns) {
  if (columns < 1 || rows < 1) {
    std::cerr << "....\n"; // TODO add notmal comment
    return;
  }

  rows_ = rows;
  columns_ = columns;

  ptr_ = new int *[rows_];

  for (int i = 0; i < rows_; ++i) {
    ptr_[i] = new int[columns_];
  }

  FillMatrixWithRandNumbers();
}

Matrix::Matrix(const Matrix &other)
    : ptr_(other.ptr_), rows_(other.rows_), columns_(other.columns_) {}

Matrix::Matrix(Matrix &&other)
    : ptr_(other.ptr_), rows_(other.rows_), columns_(other.columns_) {
  other.ptr_ = nullptr;
  other.rows_ = 0;
  other.columns_ = 0;
}

Matrix::~Matrix() { ClearMemory(); }

void Matrix::FillMatrixWithRandNumbers() {
  if (!ptr_) {
    return;
  }

  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      ptr_[i][x] = GenerateRandomNumber();
    }
  }
}

void Matrix::ClearMemory() {
  if (!ptr_) {
    return;
  }

  for (int i = 0; i < rows_; ++i) {
    if (ptr_[i]) {
      delete[] ptr_[i];
    }
  }

  delete[] ptr_;
  ptr_ = nullptr;
}

Matrix *Matrix::Add(const Matrix &other) const {
  if (!ptr_ || other.columns_ != columns_ || other.rows_ != rows_) {
    std::cerr
        << "Matrix addition forbiden. Other. .....\n"; // TODO add meaningfull
                                                       // comment
    return nullptr;
  }

  Matrix *res_matrix = new Matrix(this->rows_, this->columns_);

  // check res_matrix чи виділилась пам'ять при new ?????
  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      res_matrix->ptr_[i][x] = this->ptr_[i][x] + other.GetValueInField(i, x);
    }
  }

  return res_matrix;
}

Matrix *Matrix::Distract(const Matrix &other) const {
  if (!ptr_ || other.columns_ != columns_ || other.rows_ != rows_) {
    std::cerr
        << "Matrix distraction forbiden. Other. .....\n"; // TODO add
                                                          // meaningfull comment
    return nullptr;
  }

  Matrix *res_matrix = new Matrix(this->rows_, this->columns_);

  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      res_matrix->ptr_[i][x] = this->ptr_[i][x] + other.GetValueInField(i, x);
    }
  }

  return res_matrix;
}

Matrix *Matrix::Multiply(const Matrix &other) const {
  if (!ptr_ || columns_ != other.rows_ || other.columns_ < 1 || rows_ < 1) {
    std::cerr
        << "Matrix multiplying forbiden. Other. .....\n"; // TODO add
                                                          // meaningfull comment
    return nullptr;
  }

  Matrix *res_matrix = new Matrix(rows_, other.columns_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.columns_; j++) {
      res_matrix->ptr_[i][j] = 0;

      for (int k = 0; k < columns_; k++) {
        res_matrix->ptr_[i][j] += ptr_[i][k] * other.ptr_[k][j];
      }
    }
  }

  return res_matrix;
}

Matrix *Matrix::Traverse(const Matrix &other) const {}

int Matrix::GetValueInField(int rows, int columns) const {
  if (!ptr_ || rows < 0 || rows >= rows_ || columns < 0 ||
      columns >= columns_) {
    std::cerr << "...\n"; // TODO add comment
    return -1;
  }

  auto &returned_value = ptr_[rows][columns];
  // std::cout << "returned_value is: " << returned_value << "\n";
  return returned_value;
}

void Matrix::Print() const {
  if (!ptr_) {
    std::cout << "Printing cannot be performed\n";
    return;
  }

  std::cout << "Printing Matrix:\n";

  for (int i = 0; i < rows_; ++i) {
    for (int x = 0; x < columns_; ++x) {
      if (!ptr_[i][x]) {
        std::cout << "\n there are no value at position [" << i << "] [" << x
                  << "]\n";
      } else {
        std::cout << ptr_[i][x] << " ";
      }
    }
    std::cout << '\n';
  }
}

Matrix &Matrix::operator=(const Matrix &other) noexcept {
  if (&other == this) {
    return *this;
  }

  ClearMemory();

  ptr_ = other.ptr_;
  rows_ = other.rows_;
  columns_ = other.columns_;
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  ClearMemory();

  ptr_ = other.ptr_;
  rows_ = other.rows_;
  columns_ = other.columns_;

  other.ptr_ = nullptr;
  other.rows_ = 0;
  other.columns_ = 0;
}
