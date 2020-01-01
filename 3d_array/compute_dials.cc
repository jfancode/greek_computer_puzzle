/*
  We encode the puzzle using a 3d array (5 x 4 x 12), where:
  - dim 0 represents each plate, with the plates ordered from largest
  to smallest,
  - dim 1 represents the reachable numbers on each plate, which are ordered
  from farthest to closest-to-center,
  - dim 2 represents the 12 columns.

  Each of the numbers in the puzzle is a positive integer, so we'll
  use the number 0 to indicate a "hole" (in which case a larger
  plate's number will be shown).

  There should be a solution (int[4]) that encodes all four gear
  positions for the 4 moveable plates.

  We will use backtracking to solve this problem.
*/

#include <iostream>
#include <fstream>
#include <vector>

static const int puzzle[5][4][12] =
  {
   {10,  7, 16,  8,  7,  8,  8,  3,  4, 12,  2,  5,
    14, 14, 21, 21,  9,  9,  4,  4,  6,  6,  3,  3,
    10, 11, 12, 13, 14, 15,  4,  5,  6,  7,  8,  9,
    14, 14, 11, 14, 11, 14, 11, 11, 14, 11, 14, 11},  // plate 0
   {10,  0,  1,  0,  9,  0, 12,  0,  6,  0, 10,  0,
     3, 12,  3, 26,  6,  0,  2, 13,  9,  0, 17, 19,
     9,  0,  9, 20, 12,  3,  6,  0, 14, 12,  3,  8,
    16,  2,  7,  0,  9,  0,  7, 14, 11,  0,  8,  0},  // plate 1
   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     9,  0,  5,  0, 10,  0,  8,  0, 22,  0, 16,  0,
    12,  0, 21,  6, 15,  4,  9, 18, 11, 26, 14,  1,
     7,  8,  9, 13,  9,  7, 13, 21, 17,  4,  5,  0},  // plate 2
   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     7, 15,  0,  0, 14,  0,  9,  0, 12,  0,  4,  0,
     0,  6,  0, 11, 11,  6, 11,  0,  6, 17,  7,  3},  // plate 3
   { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     3,  0,  6,  0, 10,  0,  7,  0, 15,  0,  8,  0},  // plate 4
 };

static const int num_plates = 5;    // size of dim 0
static const int num_levels = 4;    // size of dim 1
static const int num_columns = 12;  // size of dim 2

static const int target_column_sum = 42;

static std::ofstream debug_file;

void print_solution(std::vector<int> solution) {
  std::cout << "Solution settings:" << std::endl;
  for (int i = 0; i < solution.size(); i++) {
    std::cout << " -Rotate plate " << i << " counter-clockwise by "
	      << solution[i] << " places." << std::endl;
  }
}

// Verification function. Do all columns of the partial solution sum
// to less than target_column_sum, or if check_completion=true, did
// we solve the puzzle?
bool is_valid(std::vector<int> potential_solution, bool check_completion) {
  // Sum all columns.
  debug_file << ": ";
  for (int k = 0; k < num_columns; k++) {
    int column_sum = 0;
    for (int j = 0; j < potential_solution.size(); j++) {
      // Start with the first moveable plate.
      int current_plate_i = j+1;
      // If current_plate_value is 0, use a lower level plate's
      // nonzero value. Keep iterating until we find the first
      // nonzero value.
      int current_plate_value;
      int offset;
      for (int visible_plate_i = current_plate_i; visible_plate_i >= 0;
	   visible_plate_i--) {
	offset = (visible_plate_i > 0 ?
		  potential_solution[visible_plate_i-1] : 0);
	current_plate_value = puzzle[visible_plate_i][j][(k+offset) %
							 num_columns];
	if (current_plate_value) {
	  break;
	}
      }
      column_sum += current_plate_value;
      debug_file << column_sum << ", ";
      // We can abort if column_sum is already over target_column_sum.
      if (column_sum > target_column_sum) {
	debug_file << std::endl;
	return false;
      }
    }
    if (check_completion && column_sum != target_column_sum) {
      debug_file << std::endl;
      return false;
    }
  }
  debug_file << std::endl;
  return true;
}

// Check for dead ends. We mark them as {-1,-1,-1,-1}.
bool is_null_solution(std::vector<int> potential_solution) {
  if (!potential_solution.empty() && potential_solution[0] < 0) {
    return true;
  }
  return false;
}

// Backtracking function.
// partial_solution: The partial_solution we'll recurse on.
// num_fixed_plates: The number of positions we've solved for,
//                   i.e. the new index position we need to solve.
std::vector<int> create_solution(std::vector<int> partial_solution) {
  // Find a solution for the last plate, or recurse on the
  // new_solutions where each column's partial_sum <
  // target_column_sum.
  for (int k = 0; k < num_columns; k++) {
    std::vector<int> new_solution = partial_solution;
    new_solution.push_back(k);
    for (int i = 0; i < new_solution.size(); i++) {
      debug_file << new_solution[i] << ",";
    }
    if (new_solution.size() == num_plates-1) {
      if (is_valid(new_solution, /*check_completion=*/true)) {
	return new_solution;
      }
    } else if (is_valid(new_solution, /*check_completion=*/false)) {
      auto potential_solution = create_solution(new_solution);
      if (!is_null_solution(potential_solution)) {
	return potential_solution;
      }
    }
  }
  return {-1,-1,-1,-1};
}

// Kickoff function.
std::vector<int> solve_puzzle() {
  return create_solution({});
}

int main(int argc, char* argv[]) {
  debug_file.open("verbose.txt");
  std::vector<int> solution = solve_puzzle();
  debug_file.close();

  print_solution(solution);
  return 0;
}
