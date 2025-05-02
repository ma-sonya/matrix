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
  }

  Matrix matrix_3(2, 6);
  matrix_3.Print();

  auto matr_mult = matrix.Multiply(matrix_3);

  if (matr_mult) {
    matr_mult->Print();
  }

  matrix = matrix;
  matrix_3 = std::move(matrix);
  matrix_3.Print();

  Matrix copied_m(*matr_addition);
  Matrix moved_m(std::move(matrix_3));

  copied_m.Print();
  moved_m.Print();

  auto traversed_m = moved_m.Traverse();
  if (traversed_m) {
    traversed_m->Print();
  }

  return 0;
}

// TODO щоб