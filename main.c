#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linalg.h"
#include "linkedlist.h"

void handle_create(struct llist *list) {
    int rows = 0;
    int columns = 0;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &columns);
    if (rows <= 0 || columns <= 0) {
        fprintf(stderr, "Error: row or column number less or equal to zero\n");
        return;
    }
    float *input_array = malloc(rows * columns * sizeof(float));
    printf("Please enter the %d elements of your matrix from left to right, top to bottom:\n", rows * columns);
    for (int i = 0; i < rows * columns; ++i) {
        scanf("%f", &input_array[i]);
    }
    add_front(create_matrix(rows, columns, input_array), list);
    free(input_array);
}

void handle_remove(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix you'd like to remove: ");
    scanf("%d", &index);
    remove_item(index, list);
}

void handle_print(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix you'd like to print: ");
    scanf("%d", &index);
    const struct matrix *mat = matrix_at(index, list);
    if (mat) {
        print_matrix(mat);
    }
}

void save_matrix(struct llist *list, struct matrix *mat) {
    char yes_no = 0;
    while (1) {
        printf("Do you want to save this matrix? (y or n): ");
        scanf(" %c", &yes_no);
        if (yes_no == 'y') {
            add_front(mat, list);
            return;
        } else if (yes_no == 'n') {
            destroy_matrix(mat);
            return;
        } else {
            fprintf(stderr, "Error: invalid input\n");
        }
    }
}

void handle_addsub(struct llist *list, int addsub) {
    int index = 0;
    printf("Enter the index of the first matrix: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the next matrix: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    struct matrix *mat_sum = addsub_matrix(mat1, mat2, addsub);
    if (!mat_sum) {
        return;
    }
    if (addsub == 0) {
        printf("The sum of those two matrices are:\n");
    } else {
        printf("The difference of those two matrices are:\n");
    }
    print_matrix(mat_sum);
    save_matrix(list, mat_sum);
}

void handle_scalarmultiply(struct llist *list) {
    int index = 0;
    float scalar = 0;
    printf("Enter the index of the matrix you wish to scale: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("Enter the value of the scalar: ");
    scanf("%f", &scalar);
    struct matrix *scaled_matrix = scalar_multiply(scalar, mat);
    printf("Your scaled matrix is:\n");
    print_matrix(scaled_matrix);
    save_matrix(list, scaled_matrix);
}

void handle_dotproduct(struct llist *list) {
    int index = 0;
    printf("Enter the index of the first matrix: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the second matrix: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    float dotproduct = dot_product(mat1, mat2);
    if (isnan(dotproduct)) {
        return;
    }
    printf("The dot product is %g\n", dotproduct);
}

void handle_length(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    float norm = length(mat);
    if (isnan(norm)) {
        return;
    }
    printf("The length (magnitude) of this matrix is %g\n", norm);
}

void handle_unitvector(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    struct matrix *unit_vec = unit_vector(mat);
    if (!unit_vec) {
        return;
    }
    printf("The resulting unit vector is:\n");
    print_matrix(unit_vec);
    save_matrix(list, unit_vec);
}

void handle_angle(struct llist *list) {
    int index = 0;
    printf("Enter the index of the first matrix: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the second matrix: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    float anglerad = angle_between(mat1, mat2);
    if (isnan(anglerad)) {
        return;
    }
    float angledeg = anglerad * (180.0 / 3.14159265358979323846);
    printf("The angle between these two vectors is %g radians or %g degrees\n", anglerad, angledeg);
}

void handle_proj(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix you'd like to project: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the matrix to be projected onto: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    struct matrix *proj = projection(mat1, mat2);
    if (!proj) {
        return;
    }
    printf("The projected matrix is:\n");
    print_matrix(proj);
    save_matrix(list, proj);
}

void handle_perp(struct llist *list) {
    int index = 0;
    printf("Enter the index of the matrix that is projected: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the matrix that is projected onto: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    struct matrix *perp = perpendicular(mat1, mat2);
    if (!perp) {
        return;
    }
    printf("The perpendicular matrix is:\n");
    print_matrix(perp);
    save_matrix(list, perp);
}

void handle_crossproduct(struct llist *list) {
    int index = 0;
    printf("Enter the index of the first matrix: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the second matrix: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    struct matrix *crossproduct = cross_product(mat1, mat2);
    if (!crossproduct) {
        return;
    }
    printf("The crossproduct is:\n");
    print_matrix(crossproduct);
    save_matrix(list, crossproduct);
}

void handle_rowswap(struct llist *list) {
    int index = 0;
    int row1 = -1;
    int row2 = -1;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("Enter the index of the row to swap: ");
    scanf("%d", &row1);
    printf("Enter the index of the row to swap with: ");
    scanf("%d", &row2);
    struct matrix *swap_mat = row_swap(row1, row2, mat);
    if (!swap_mat) {
        return;
    }
    printf("The resulting matrix is:\n");
    print_matrix(swap_mat);
    save_matrix(list, swap_mat);
}

void handle_rowscale(struct llist *list) {
    int index = 0;
    int row = -1;
    float scale = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("Enter the index of the row to scale: ");
    scanf("%d", &row);
    printf("Enter the value of the scalar: ");
    scanf("%f", &scale);
    struct matrix *rowscale = row_scale(row, scale, mat);
    if (!rowscale) {
        return;
    }
    printf("The resulting matrix is:\n");
    print_matrix(rowscale);
    save_matrix(list, rowscale);
}

void handle_rowadd(struct llist *list) {
    int index = 0;
    int row1 = -1;
    int row2 = -1;
    float scale = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("Enter the index of the first row: ");
    scanf("%d", &row1);
    printf("Enter the value of the scalar for this row: ");
    scanf("%f", &scale);
    printf("Enter the index of the row you will add the scaled first row to: ");
    scanf("%d", &row2);
    struct matrix *rowadd = row_add(row1, scale, row2, mat);
    if (!rowadd) {
        return;
    }
    printf("The resulting matrix is:\n");
    print_matrix(rowadd);
    save_matrix(list, rowadd);
}

void handle_ref(struct llist *list) {
    int index = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    struct matrix *REF = ref(mat);
    printf("The resulting matrix is:\n");
    print_matrix(REF);
    save_matrix(list, REF);
}

void handle_rref(struct llist *list) {
    int index = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    struct matrix *RREF = rref(mat);
    printf("The resulting matrix is:\n");
    print_matrix(RREF);
    save_matrix(list, RREF);
}

void handle_rank(struct llist *list) {
    int index = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("The rank of this matrix is %d\n", rank(mat));
}

void handle_nullity(struct llist *list) {
    int index = 0;
    printf("Enter the index of your matrix: ");
    scanf("%d", &index);
    struct matrix *mat = matrix_at(index, list);
    if (!mat) {
        return;
    }
    printf("The nullity of this matrix is %d\n", nullity(mat));
}

void handle_matprod(struct llist *list) {
    int index = 0;
    printf("Enter the index of the first matrix: ");
    scanf("%d", &index);
    struct matrix *mat1 = matrix_at(index, list);
    if (!mat1) {
        return;
    }
    printf("Enter the index of the second matrix: ");
    scanf("%d", &index);
    struct matrix *mat2 = matrix_at(index, list);
    if (!mat2) {
        return;
    }
    struct matrix *new_vec = matrix_multiplication(mat1, mat2);
    if (!new_vec) {
        return;
    }
    printf("The resulting matrix is:\n");
    print_matrix(new_vec);
    save_matrix(list, new_vec);
}

void handle_help(void) {
    printf("Setup comands:\n");
    printf("- create\n- remove\n- removeall\n- print\n- printall\n- end\n");
    printf("operation commands:\n");
    printf("- add\t\t\t- subtract\n- scalarmultiply\t- dotproduct\n- length\t\t");
    printf("- unitvector\n- anglebetween\t\t- proj\n- perp\t\t\t- crossproduct\n- rowswap\t\t");
    printf("- rowscale\n- rowadd\t\t- ref\n- rref\t\t\t- rank\n- nullity\t\t- matprod\n");
}

int main(void) {
    struct llist *list = list_create();
    char command[20];
    while (1) {
        printf("Enter command: ");
        if (scanf("%s", command) < 0) {
            printf("\n");
            list_destroy(list, 1);
            return 0;
        }
        if (!(strcmp(command, "create"))) {
            handle_create(list);
        } else if (!(strcmp(command, "remove"))) {
            handle_remove(list);
        } else if (!(strcmp(command, "print"))) {
            handle_print(list);
        } else if (!(strcmp(command, "end"))) {
            list_destroy(list, 1);
            return 0;
        } else if (!(strcmp(command, "add"))) {
            handle_addsub(list, 0);
        } else if (!(strcmp(command, "subtract"))) {
            handle_addsub(list, 1);
        } else if (!(strcmp(command, "scalarmultiply"))) {
            handle_scalarmultiply(list);
        } else if (!(strcmp(command, "dotproduct"))) {
            handle_dotproduct(list);
        } else if (!(strcmp(command, "unitvector"))) {
            handle_unitvector(list);
        } else if (!(strcmp(command, "length"))) {
            handle_length(list);
        } else if (!(strcmp(command, "anglebetween"))) {
            handle_angle(list);
        } else if (!(strcmp(command, "proj"))) {
            handle_proj(list);
        } else if (!(strcmp(command, "perp"))) {
            handle_perp(list);
        } else if (!(strcmp(command, "crossproduct"))) {
            handle_crossproduct(list);
        } else if (!(strcmp(command, "rowswap"))) {
            handle_rowswap(list);
        } else if (!(strcmp(command, "rowscale"))) {
            handle_rowscale(list);
        } else if (!(strcmp(command, "rowadd"))) {
            handle_rowadd(list);
        } else if (!(strcmp(command, "ref"))) {
            handle_ref(list);
        } else if (!(strcmp(command, "rref"))) {
            handle_rref(list);
        } else if (!(strcmp(command, "rank"))) {
            handle_rank(list);
        } else if (!(strcmp(command, "nullity"))) {
            handle_nullity(list);
        } else if (!(strcmp(command, "matprod"))) {
            handle_matprod(list);
        } else if (!(strcmp(command, "printall"))) {
            print_llist(list);
        } else if (!(strcmp(command, "removeall"))) {
            list_destroy(list, 0);
        } else if (!(strcmp(command, "help"))) {
            handle_help();
        } else {
            printf("Invalid command\n");
        }
    }
}
