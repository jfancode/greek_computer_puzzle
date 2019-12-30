
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
*/

static const int[5][4][12] puzzle =
  [
   [10,  7, 16,  8,  7,  8,  8,  8,  4, 12,  2,  5,
    14, 14, 21, 21,  9,  9,  4,  4,  6,  6,  3,  3,
    10, 11, 12, 13, 14, 15,  4,  5,  6,  7,  8,  9,
    14, 14, 11, 14, 11, 14, 11, 11, 14, 11, 14, 11],  # plate 0
   [10,  0,  1,  0,  9,  0, 12,  0,  6,  0, 10,  0,
     3, 12,  3, 26,  6,  0,  2, 13,  9,  0, 17, 19,
     9,  0,  9, 20, 12,  3,  6,  0, 14, 12,  3,  8,
    16,  2,  7,  0,  9,  0,  7, 14, 11,  0,  8,  0],  # plate 1
   [ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     9,  0,  5,  0, 10,  0,  8,  0, 22,  0, 16,  0,
    12,  0, 21,  6, 15,  4,  9, 18, 11, 26, 14,  1,
     7,  8,  9, 13,  9,  7, 13, 21, 17,  4,  5,  0],  # plate 2
   [ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     7, 15,  0,  0, 14,  0,  9,  0, 12,  0,  4,  0,
     0,  6,  0, 11, 11,  6, 11,  0,  6, 17,  7,  3],  # plate 3
   [ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     3,  0,  6,  0, 10,  0,  7,  0, 15,  0,  8,  0],  # plate 4
 ];

int main(int argc, char* argv[]) {

}
