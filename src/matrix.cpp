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
    std::cerr << "ERROR: columns < 1 || rows < 1.\n";
    return;
  }

  rows_ = rows;
  columns_ = columns;

  int i = 0;
  try {
    counter_ = new uint(1);

    ptr_ = new int *[rows_];
    for (; i < rows_; ++i) {
      ptr_[i] = new int[columns_];
    }
  } catch (const std::bad_alloc &e) {
    std::cerr << "ERROR: unable to allocate memory during construction: "
              << e.what() << "\n";

    if (counter_) {
      delete counter_;
    }

    if (ptr_) {
      for (; i - 1 >= 0; i--) {
        delete[] ptr_[i];
      }
      delete[] ptr_;
    }

    ptr_ = nullptr;
    counter_ = nullptr;

    return;
  }

  FillMatrixWithRandNumbers();
}

Matrix::Matrix(const Matrix &other)
    : ptr_(other.ptr_), counter_(other.counter_), rows_(other.rows_),
      columns_(other.columns_) {
  if (other.ptr_) {
    (*counter_)++;
  }
}

Matrix::Matrix(Matrix &&other)
    : ptr_(other.ptr_), counter_(other.counter_), rows_(other.rows_),
      columns_(other.columns_) {
  other.ptr_ = nullptr;
  other.counter_ = nullptr;
  other.rows_ = 0;
  other.columns_ = 0;
}

Matrix::~Matrix() { ClearMemory(); }

void Matrix::FillMatrixWithRandNumbers() {
  if (!ptr_ || !counter_) {
    return;
  }

  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      try {
        ptr_[i][x] = GenerateRandomNumber();
      } catch (...) {
        std::cerr << "ERROR: Filling matrix is forbiden since iteration [" << i
                  << "][" << x << "].\n";
        break;
      }
    }
  }
}

void Matrix::ClearMemory() {
  if (!ptr_ || !counter_) {
    return;
  }

  (*counter_)--;

  if (*counter_ == 0) {
    for (int i = 0; i < rows_; ++i) {
      if (ptr_[i]) {
        delete[] ptr_[i];
      }
    }

    delete[] ptr_;
    delete counter_;
    ptr_ = nullptr;
    counter_ = nullptr;
  }
}

boost::optional<Matrix> Matrix::Add(const Matrix &other) const {
  if (!ptr_ || !other.ptr_ || other.columns_ != columns_ ||
      other.rows_ != rows_) {
    std::cerr << "ERROR: Matrix addition forbiden.\n";
    return boost::none;
  }

  Matrix res_matrix(this->rows_, this->columns_);

  if (!res_matrix.ptr_) {
    std::cerr << "ERROR: Matrix addition forbiden, unable to allocate memory "
                 "for res_matrix.\n";
    return boost::none;
  }

  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      try {
        res_matrix.ptr_[i][x] = this->ptr_[i][x] + other.GetValueInField(i, x);
      } catch (const std::bad_alloc &e) {
        std::cerr << "ERROR: Matrix addition forbiden, unable to access "
                     "memory: this->ptr_["
                  << i << "][" << x << "].\n";
        return boost::none;
      }
    }
  }

  return res_matrix;
}

boost::optional<Matrix> Matrix::Distract(const Matrix &other) const {
  if (!ptr_ || !other.ptr_ || other.columns_ != columns_ ||
      other.rows_ != rows_) {
    std::cerr << "Matrix distraction forbiden.\n";
    return boost::none;
  }

  Matrix res_matrix(this->rows_, this->columns_);

  if (!res_matrix.ptr_) {
    std::cerr << "ERROR: Matrix addition forbiden, unable to allocate memory "
                 "for res_matrix.\n";
    return boost::none;
  }

  for (int i = 0; i < rows_; i++) {
    for (int x = 0; x < columns_; x++) {
      try {
        res_matrix.ptr_[i][x] = this->ptr_[i][x] + other.GetValueInField(i, x);
      } catch (const std::bad_alloc &e) {
        std::cerr << "ERROR: Matrix addition forbiden, unable to access "
                     "memory: this->ptr_["
                  << i << "][" << x << "].\n";
        return boost::none;
      }
    }
  }

  return res_matrix;
}

boost::optional<Matrix> Matrix::Multiply(const Matrix &other) const {
  if (!ptr_ || !other.ptr_ || columns_ != other.rows_) {
    std::cerr << "Matrix multiplying forbiden.\n";
    return boost::none;
  }

  Matrix res_matrix(this->rows_, other.columns_);

  if (!res_matrix.ptr_) {
    std::cerr << "ERROR: Matrix addition forbiden, unable to allocate memory "
                 "for res_matrix.\n";
    return boost::none;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.columns_; j++) {
      res_matrix.ptr_[i][j] = 0;

      for (int k = 0; k < columns_; k++) {
        try {
          res_matrix.ptr_[i][j] += ptr_[i][k] * other.ptr_[k][j];
        } catch (const std::bad_alloc &e) {
          std::cerr << "ERROR: Matrix addition forbiden, unable to access "
                       "memory: this->ptr_["
                    << i << "][" << k << "] or other.ptr_[" << i << "][" << k
                    << "].\n";
          return boost::none;
        }
      }
    }
  }

  return res_matrix;
}

boost::optional<Matrix> Matrix::Traverse(const Matrix &other) const {}

int Matrix::GetValueInField(int rows, int columns) const {
  if (!ptr_ || !counter_ || rows < 0 || rows >= rows_ || columns < 0 ||
      columns >= columns_ || !ptr_[rows][columns]) {
    std::cerr << "ERROR: unable get value of [" << rows << "][" << columns
              << "].\n";
    return -1;
  }

  return ptr_[rows][columns];
}

void Matrix::Print() const {
  if (!ptr_ || !counter_) {
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

  if (ptr_) {
    (*counter_)++;
  }
}

Matrix &Matrix::operator=(Matrix &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  ClearMemory();

  ptr_ = other.ptr_;
  counter_ = other.counter_;
  rows_ = other.rows_;
  columns_ = other.columns_;

  other.ptr_ = nullptr;
  other.counter_ = nullptr;
  other.rows_ = 0;
  other.columns_ = 0;
}
