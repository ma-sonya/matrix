#include <boost/optional.hpp>

class Matrix {
public:
  Matrix(int rows, int columns);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  boost::optional<Matrix> Add(const Matrix &other) const;
  boost::optional<Matrix> Distract(const Matrix &other) const;
  boost::optional<Matrix> Multiply(const Matrix &other) const;
  boost::optional<Matrix> Traverse(const Matrix &other) const;

  int GetValueInField(int rows, int columns) const;
  void Print() const;

  ~Matrix();

  Matrix &operator=(const Matrix &other) noexcept;
  Matrix &operator=(Matrix &&other) noexcept;

private:
  void FillMatrixWithRandNumbers();
  void ClearMemory();

  bool IsCorrupted() const;

  int columns_{0};
  int rows_{0};
  int **ptr_ = nullptr;
  uint *counter_ = nullptr;
};