class Matrix {
public:
  Matrix(int rows, int columns);
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  Matrix *Add(const Matrix &other) const;
  Matrix *Distract(const Matrix &other) const;
  Matrix *Multiply(const Matrix &other) const;
  Matrix *Traverse(const Matrix &other) const;

  int GetValueInField(int rows, int columns) const;
  void Print() const;

  ~Matrix();

  Matrix &operator=(const Matrix &other) noexcept;
  Matrix &operator=(Matrix &&other) noexcept;

private:
  void FillMatrixWithRandNumbers();
  void ClearMemory();
  int columns_;
  int rows_;
  int **ptr_ = nullptr;
};