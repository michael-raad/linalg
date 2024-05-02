// times: n is # of rows
//        m is # of columns

// A vector is considered to be an n x 1 matrix
struct matrix;

// create_matrix(rows, columns, data) returns a matrix/vector with
//   the rows, columns, and data provided to the function.
// requires: 
//   the number of elements in data is equal to rows * columns. (not asserted)
//   rows and columns are greater than 0
//   data is a valid pointer
// effects: allocates memory (client must call destroy matrix)
// time: O(nm)
struct matrix *create_matrix(int rows, int columns, float *data);

// destroy_matrix(mat) frees all memory for mat.
// requires: mat is a valid pointer
// effects: mat is no longer valid
//          may produce output
// time: O(1)
void destroy_matrix(struct matrix *mat);

// print_matrix(mat) prints the matrix mat
// requires: mat is a valid pointer
// effects: produces output
// time: O(nm)
void print_matrix(const struct matrix *mat);

// addsub_matrix(mat1, mat2, addsub) returns the matrix given by adding 
//   mat1 and mat2 if addsub is 0 and returns the matrix given by subtracting 
//   mat1 by mat2 if addsub is 1
// requires: mat1 and mat2 are both valid pointers
//           addsub = 0 or 1
// notes: outputs an error message and returns NULL if mat1 and mat2 are
//   not the same size
// effects: may produce output
//          may allocate memory
// time: O(nm)
struct matrix *addsub_matrix(struct matrix *mat1, struct matrix *mat2, int addsub);

// scaler_multiply(scalar, mat) returns the matrix given by scaling mat by scalar.
// requries: mat is a valid pointer
// effects: allocates memory
// time: O(nm)
struct matrix *scalar_multiply(float scalar, struct matrix *mat);

// dot_product(mat1, mat2) returns the dot product of mat1 and mat2
// requires: mat1 and mat2 are valid pointers
// notes: outputs an error message if the matrices are not vectors
//   or not the same size
// effects: may produce output
// time: O(n)
float dot_product(struct matrix *mat1, struct matrix *mat2);

// length(mat) returns the length (magnitude) of the vector mat
// requires: mat is a valid pointer
// notes: outputs an error message if mat is not a vector
// effects: may produce output
// time: O(n)
float length(struct matrix *mat);

// unit_vector(mat) returns a vector with the same direction
//   as mat but with magnitude 1
// requires: mat is a valid pointer
// notes: outputs an error message and returns NULL 
//   if mat is not a vector or is the zero vector
// effects: may produce output
//          may allocate memory
// time: O(n)
struct matrix *unit_vector(struct matrix *mat);

// angle_between(mat1, mat2) returns the angle between the
//   vectors mat1 and mat2
// requires: mat1 and mat2 are valid pointers
// notes: outputs an error message and returns NAN if 
//   mat1 or mat2 arent vectors, or if they are not the same size
//   or if one is the zero vector
// effects: may produce output
// time: O(n)
float angle_between(struct matrix *mat1, struct matrix *mat2);

// projection(mat1, mat2) returns the resulting matrix after projecting
//   mat1 onto mat2
// requires: mat1 and mat2 are valid pointers
// notes: outputs an error message and returns NULL if 
//   mat1 or mat2 aren't vectors, are not the same size, or if
//   mat2 is the zero vector
// effects: may allocate memory
//          may produce output
// time: O(n)
struct matrix *projection(struct matrix *mat1, struct matrix *mat2);

// perpendicular(mat1, mat2) returns the perpendicular of mat1 and mat2
// requires: mat1 and mat2 are valid pointers
// notes: outputs an error message and returns NULL if 
//   mat1 or mat2 aren't vectors, are not the same size, or if
//   mat2 is the zero vector
// effects: may allocate memory
//          may produce output
// time: O(n)
struct matrix *perpendicular(struct matrix *mat1, struct matrix *mat2);

// cross_product(mat1, mat2) returns the cross product of mat1 and mat2
// requires: mat1 and mat2 are valid pointers
// notes: outputs an error message and returns NULL if either 
//   matrix is not a 3x1 matrix
// effects: may allocate memory
//          may produce output
// time: O(1)
struct matrix *cross_product(struct matrix *mat1, struct matrix *mat2);

// row_swap(row1, row2, mat) returns a matrix with row1 and row2 of mat swapped.
// requires: mat is a valid pointer
// notes: outputs an error message and returns NULL if either
//   row1 or row2 have invalid indexes 
//   *row index starts at 0
// effects: may allocate memory
//          may produce output
// time: O(nm)
struct matrix *row_swap(int row1, int row2, struct matrix *mat);

// row_scale(row, scalar, mat) returns a matrix with the specified 
//   row of mat scaled by scalar
// requires: mat is a valid pointer
// notes: outputs an error message and returns NULL if 
//   row is an invalid index
// effects: may allocate memory
//          may produce output
// time: O(nm)
struct matrix *row_scale(int row, float scalar, struct matrix *mat);

// row_add(row1, scalar, row2, mat) adds all elements of row1 scaled by scalar
//   to row2 of mat. (row1 is NOT scaled or changed in the returned 
//   matrix, only row2 is changed)
// requires: mat is a valid pointer
// notes: outputs an error message  and returns NULL if row1 or row2 
//   are invalid row indexes
// effects: may allocate memory
//          may produce output
// time: O(nm)
struct matrix *row_add(int row1, float scalar, int row2, struct matrix *mat);

// argmax_col(mat, col, starting_row) returns the index of the 
//   maximum value between the absolute values of all entries of mat
//   in column col starting from row starting_row.
// requires: mat is a valid pointer
//           col and starting row are both valid indexes.
// time: O(n)
int argmax_col(struct matrix *mat, int col, int starting_row);

// ref(mat) returns the REF of mat.
// requires: mat is a valid pointer
// effects: allocates memory
// time: O(nm * min(m, n)) ???
struct matrix *ref(struct matrix *mat);

// rref(mat) returns the rref of mat.
// requires: mat is a valid pointer
// effects allocates memeory
// time: O(mn^2)
struct matrix *rref(struct matrix *mat);

// rank(mat) returns the rank (# pivots) of mat
// requires: mat is a valid pointer
// time: O(mn^2)
int rank(struct matrix *mat);

// nullity(mat) returns the nullity of mat
// requires: mat is a valid pointer
// time: O(mn^2)
int nullity(struct matrix *mat);

struct matrix *matrix_multiplication(struct matrix *mat1, struct matrix *mat2);