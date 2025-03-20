#include "../include/matrix.hpp"

#include <iostream>

int main() {
  Matrix matrix(3, 2);
  matrix.Print();

  Matrix matrix_2(3, 2);
  matrix_2.Print();

  auto matr_addition = matrix.Add(matrix_2);
  if (matr_addition) {
    matr_addition->Print();
  }

  auto matr_distr = matrix.Distract(matrix_2);
  if (matr_distr) {
    matr_distr->Print();
    delete matr_distr;
  }

  Matrix matrix_3(2, 6);
  matrix_3.Print();

  auto matr_mult = matrix.Multiply(matrix_3);

  if (matr_mult) {
    matr_mult->Print();

    delete matr_mult;
  }

  matrix = matrix;
  matrix_3 = std::move(matrix);
  matrix_3.Print();

  Matrix copied_m(*matr_addition);
  Matrix moved_m(std::move(matrix_3));

  if (matr_addition) {
    //    delete matr_addition;  //
  }

  copied_m.Print();
  moved_m.Print();

  return 0;
}

// TODO щоб