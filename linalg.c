#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linalg.h"

struct matrix {
    int rows;
    int columns;
    float *entries;
};

struct matrix *create_matrix(int rows, int columns, float *data) {
    assert(rows > 0);
    assert(columns > 0);
    assert(data);
    struct matrix *mat = malloc(sizeof(struct matrix));
    mat->rows = rows;
    mat->columns = columns;
    mat->entries = malloc(rows * columns * sizeof(float));
    for (int i = 0; i < rows * columns; ++i) {
        mat->entries[i] = data[i];
    }
    return mat;
}

void destroy_matrix(struct matrix *mat) {
    assert(mat);
    free(mat->entries);
    free(mat);
}

void print_matrix(const struct matrix *mat) {
    assert(mat);
    printf("Matrix (%d x %d):\n\n", mat->rows, mat->columns);
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->columns; ++j) {
            printf("%g\t", mat->entries[i * mat->columns + j]);
        }
        printf("\n\n\n\n");
    }
}

struct matrix *addsub_matrix(struct matrix *mat1, struct matrix *mat2, int addsub) {
    assert(mat1);
    assert(mat2);
    assert(addsub == 0 || addsub == 1);
    if (mat1->columns != mat2->columns || mat1->rows != mat2->rows) {
        fprintf(stderr, "Error: Matrices are not the same size\n");
        return NULL;
    }
    int num_entries = mat1->columns * mat1->rows;
    float *sum_entries = malloc(num_entries * sizeof(float));
    if (addsub == 0) {
        for (int i = 0; i < num_entries; ++i) {
            sum_entries[i] = mat1->entries[i] + mat2->entries[i];
        }
    } else {
        for (int i = 0; i < num_entries; ++i) {
            sum_entries[i] = mat1->entries[i] - mat2->entries[i];
        }
    }
    struct matrix *matrix_sum = create_matrix(mat1->rows, mat1->columns, sum_entries);
    free(sum_entries);
    return matrix_sum;
}

struct matrix *scalar_multiply(float scalar, struct matrix *mat) {
    assert(mat);
    int num_entries = mat->rows * mat->columns;
    float *scaled_entries = malloc(num_entries * sizeof(float));
    for (int i = 0; i < num_entries; ++i) {
        scaled_entries[i] = scalar * mat->entries[i];
    }
    struct matrix *scaled_matrix = create_matrix(mat->rows, mat->columns, scaled_entries);
    free(scaled_entries);
    return scaled_matrix;
}

float dot_product(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    assert(mat2);
    if (mat1->columns != 1 || mat2->columns != 1) {
        fprintf(stderr, "Error: All matrices must be vectors (1 column)\n");
        return NAN;
    }
    if (mat1->rows != mat2->rows) {
        fprintf(stderr, "Error: Matrices are not same size\n");
        return NAN;
    }
    float dot_product = 0;
    for (int i = 0; i < mat1->rows; ++i) {
        dot_product += mat1->entries[i] * mat2->entries[i];
    }
    return dot_product;
}

float length(struct matrix *mat) {
    assert(mat);
    if (mat->columns != 1) {
        fprintf(stderr, "Error: Matrix must be a vector (1 column)\n");
        return NAN;
    }
    float dot_value = dot_product(mat, mat);
    if (dot_value < 0) {
        return 0;
    }
    float norm = sqrt(dot_value);
    return norm;
}

struct matrix *unit_vector(struct matrix *mat) {
    assert(mat);
    if (mat->columns != 1) {
        fprintf(stderr, "Error: Matrix must be a vector (1 column)\n");
        return NULL;
    }
    if (length(mat) == 0) {
        fprintf(stderr, "Error: length 0 (cannot use zero vector)\n");
        return NULL;
    }
    struct matrix *unitvector = scalar_multiply(1 / length(mat), mat);
    return unitvector;
}

float angle_between(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    assert(mat2);
    if (mat1->columns != 1 || mat2->columns != 1) {
        fprintf(stderr, "Error: All matrices must be vectors (1 column)\n");
        return NAN;
    }
    if (mat1->rows != mat2->rows) {
        fprintf(stderr, "Error: Matrices are not same size\n");
        return NAN;
    }
    float ratio = (dot_product(mat1, mat2)) / (length(mat1) * length(mat2));
    if (isnan(ratio)) {
        fprintf(stderr, "Error: length product 0 (cannot use zero vector)\n");
        return NAN;
    }
    float anglerad = acos(fmin(fmax(ratio, -1), 1));
    return anglerad;
}

struct matrix *projection(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    assert(mat2);
    if (mat1->columns != 1 || mat2->columns != 1) {
        fprintf(stderr, "Error: All matrices must be vectors (1 column)\n");
        return NULL;
    }
    if (mat1->rows != mat2->rows) {
        fprintf(stderr, "Error: Matrices are not same size\n");
        return NULL;
    }
    struct matrix *unit2 = unit_vector(mat2);
    if (!unit2) {
        return NULL;
    }
    struct matrix *proj = scalar_multiply(dot_product(mat1, unit2), unit2);
    destroy_matrix(unit2);
    return proj;
}

struct matrix *perpendicular(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    assert(mat2);
    struct matrix *proj = projection(mat1, mat2);
    if (!proj) {
        return NULL;
    }
    struct matrix *perp = addsub_matrix(mat1, proj, 1);
    destroy_matrix(proj);
    return perp;
}

struct matrix *cross_product(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    assert(mat2);
    if (mat1->columns != 1 || mat2->columns != 1) {
        fprintf(stderr, "Error: All matrices must be vectors (1 column)\n");
        return NULL;
    }
    if (mat1->rows != 3 || mat2->rows != 3) {
        fprintf(stderr, "Error: All vectors must belong to R^3 (3 rows)\n");
        return NULL;
    }
    float *entries = malloc(3 * sizeof(float));
    entries[0] = (mat1->entries[1] * mat2->entries[2]) - (mat1->entries[2] * mat2->entries[1]);
    entries[1] = (mat1->entries[2] * mat2->entries[0]) - (mat1->entries[0] * mat2->entries[2]);
    entries[2] = (mat1->entries[0] * mat2->entries[1]) - (mat1->entries[1] * mat2->entries[0]);
    struct matrix *crossproduct = create_matrix(3, 1, entries);
    free(entries);
    return crossproduct;
}

struct matrix *row_swap(int row1, int row2, struct matrix *mat) {
    assert(mat);
    if (row1 < 0 || row1 >= mat->rows || row2 < 0 || row2 >= mat->rows) {
        fprintf(stderr, "Error: invalid row index\n");
        return NULL;
    }
    float *swap_entries = malloc(mat->columns * mat->rows * sizeof(float));
    int new_row = -1;
    for (int i = 0; i < mat->rows; ++i) {
        if (i == row1) {
            new_row = row2;
        } else if (i == row2) {
            new_row = row1;
        } else {
            new_row = i;
        }
        for (int j = 0; j < mat->columns; ++j) {
            swap_entries[i * mat->columns + j] = mat->entries[new_row * mat->columns + j];
        }
    }
    struct matrix *swap_matrix = create_matrix(mat->rows, mat->columns, swap_entries);
    free(swap_entries);
    return swap_matrix;
}

struct matrix *row_scale(int row, float scalar, struct matrix *mat) {
    assert(mat);
    if (row < 0 || row >= mat->rows) {
        fprintf(stderr, "Error: invalid row index\n");
        return NULL;
    } 
    float *scale_entries = malloc(mat->columns * mat->rows * sizeof(float));
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->columns; ++j) {
            if (i == row) {
                scale_entries[i * mat->columns + j] = scalar * mat->entries[i * mat->columns + j];
            } else {
                scale_entries[i * mat->columns + j] = mat->entries[i * mat->columns + j];
            }
        }
    }
    struct matrix *scale_matrix = create_matrix(mat->rows, mat->columns, scale_entries);
    free(scale_entries);
    return scale_matrix;
}

struct matrix *row_add(int row1, float scalar, int row2, struct matrix *mat) {
    assert(mat);
    if (row1 < 0 || row1 >= mat->rows || row2 < 0 || row2 >= mat->rows) {
        fprintf(stderr, "Error: invalid row index\n");
        return NULL;
    }
    float *new_entries = malloc(mat->rows * mat->columns * sizeof(float));
    for (int i = 0; i < mat->rows; ++i) {
        for (int j = 0; j < mat->columns; ++j) {
            if (i == row2) {
                new_entries[i * mat->columns + j] = mat->entries[row1 * mat->columns + j] * scalar + mat->entries[i * mat->columns + j];
            } else {
                new_entries[i * mat->columns + j] = mat->entries[i * mat->columns + j];
            }
        }
    }
    struct matrix *new_mat = create_matrix(mat->rows, mat->columns, new_entries);
    free(new_entries);
    return new_mat;
}

int argmax_col(struct matrix *mat, int col, int starting_row) {
    assert(mat);
    assert(col >= 0 && col < mat->columns);
    assert(starting_row >= 0 && starting_row < mat->rows);
    int max_index = starting_row * mat->columns + col;
    float max_value = mat->entries[starting_row * mat->columns + col];
    for (int i = starting_row + 1; i < mat->rows; ++i) {
        if (mat->entries[i * mat->columns + col] > max_value) {
            max_value = mat->entries[i * mat->columns + col];
            max_index = i * mat->columns + col; 
        }
    }
    return max_index;
}

struct matrix *ref(struct matrix *mat) {
    assert(mat);
    struct matrix *REF = create_matrix(mat->rows, mat->columns, mat->entries);
    struct matrix *REF_NEXT = NULL;
    for (int i = 0, j = 0; i < REF->rows && j < REF->columns;) {
        int row = i; 
        int col = j;
        int max_index = argmax_col(REF, col, row);
        if (!REF->entries[max_index]) {
            ++j;
        } else {
            REF_NEXT = row_swap(row, (max_index - col) / REF->columns, REF);
            destroy_matrix(REF);
            REF = REF_NEXT;
            for (int k = row + 1; k < REF->rows; ++k) {
                float ratio = REF->entries[k * REF->columns + col] / REF->entries[row * REF->columns + col];
                REF->entries[k * REF->columns + col] = 0;
                for (int l = col + 1; l < REF->columns; ++l) {
                    REF->entries[k * REF->columns + l] = REF->entries[k * REF->columns + l] - REF->entries[row * REF->columns + l] * ratio;
                }
            }
            ++i;
            ++j;
        }
    }
    return REF;
}

struct matrix *rref(struct matrix *mat) {
    assert(mat);
    struct matrix *RREF = ref(mat);
    struct matrix *RREF_NEXT = NULL;
    for (int row = RREF->rows - 1; row >= 0; --row) {
        for (int col = 0; col < RREF->columns; ++col) {
            float entry = RREF->entries[row * RREF->columns + col];
            if (entry) {
                if (entry != 1) {
                    RREF_NEXT = row_scale(row, 1 / entry, RREF);
                    destroy_matrix(RREF);
                    RREF = RREF_NEXT;
                }
                for (int i = 0; i < row; ++i) {
                    float ratio = -1 * RREF->entries[i * RREF->columns + col];
                    RREF_NEXT = row_add(row, ratio, i, RREF);
                    destroy_matrix(RREF);
                    RREF = RREF_NEXT;
                    RREF->entries[i * RREF->columns + col] = 0;
                }
                break;
            }
        }
    }
    return RREF;
}

int rank(struct matrix *mat) {
    assert(mat);
    struct matrix *REF = ref(mat);
    int rank = 0;
    for (int row = REF->rows - 1; row >=0; --row) {
        for (int col = 0; col < REF->columns; ++col) {
            if (REF->entries[row * REF->columns + col]) {
                ++rank;
                break;
            }
        }
    }
    destroy_matrix(REF);
    return rank;
}

int nullity(struct matrix *mat) {
    assert(mat);
    return mat->columns - rank(mat);
}

struct matrix *matrix_multiplication(struct matrix *mat1, struct matrix *mat2) {
    assert(mat1);
    if (mat1->columns != mat2->rows) {
        fprintf(stderr, "Error: first matrix columns must equal second matrix rows \n");
        return NULL;
    }
    float *new_entries = malloc(mat1->rows * mat2->columns * sizeof(float));
    for (int i = 0; i < mat1->rows; ++i) {
        for (int j = 0; j < mat2->columns; ++j) {
            float entry = 0;
            for (int k = 0; k < mat2->rows; ++k) {
                entry += mat1->entries[i * mat1->columns + k] * mat2->entries[k * mat2->columns + j];
            }
            new_entries[i * mat2->columns + j] = entry;
        }
    }
    struct matrix *new_mat = create_matrix(mat1->rows, mat2->columns, new_entries);
    free(new_entries);
    return new_mat;
}
