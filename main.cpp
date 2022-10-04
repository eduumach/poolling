#include <iostream>

int main() {
    int line, column, k, l, maior, cont_linha_pooling, cont_column_pooling, image_line, image_column, maxValue;

    int pooling_line_size = 2,pooling_column_size = 2, matrix_column, matrix_line, image_line_original,
    image_column_original, pooling_line, pooling_column, soma;

    FILE* img = fopen("./person.ascii.pgm", "r");
    fscanf(img, "%*s %d %d %d", &image_line_original, &image_column_original, &maxValue);

    image_line = image_line_original;
    image_column = image_column_original;

    if(image_line % pooling_line_size != 0){
        image_line +=  pooling_line_size - (image_line % pooling_line_size);
    }
    if(image_column % pooling_column_size !=0){
        image_column += pooling_column_size - (image_column % pooling_column_size);
    }

    pooling_line = image_line/pooling_line_size;
    pooling_column = image_column/pooling_column_size;

    int image[image_line][image_column];

    for(column = 0; column < image_column; column++){
        for(line = 0; line < image_line; line++){
            image[line][column] = 0;
        }
    }

    // add border to image
    for(column = 0; column < image_column_original; column++){
        for(line = 0; line < image_line_original; line++){
            fscanf(img, "%d", &image[line][column]);
        }
    }

    // close image
    fclose(img);

    int pooling[pooling_line][pooling_column];

    cont_linha_pooling = 0;
    for(line = 0; line < image_line; line += pooling_line_size){
        cont_column_pooling = 0;
        for(column = 0; column < image_column; column += pooling_column_size){
            maior = 0;
            for(k = line; k < line + pooling_line_size; k++){
                for(l = column; l < column + pooling_column_size; l++){
                    if(image[k][l] > maior){
                        maior = image[k][l];
                    }
                }
            }
            pooling[cont_linha_pooling][cont_column_pooling] = maior;
            cont_column_pooling++;
        }
        cont_linha_pooling++;
    }

    FILE* convolutional_image = fopen("pooling.ascii.pgm", "w");

    fprintf(convolutional_image, "P2\n");
    fprintf(convolutional_image, "%d %d \n", pooling_line, pooling_column);
    fprintf(convolutional_image, "%d \n", maxValue);

    for(column = 0; column < pooling_column; column++){
        for(line = 0; line < pooling_line; line++){
            if(pooling[line][column] < 0){
                fprintf(convolutional_image, "%d ", 0);
            } else if(pooling[line][column] > maxValue){
                fprintf(convolutional_image, "%d ", maxValue);
            } else{
                fprintf(convolutional_image, "%d ", pooling[line][column]);
            }

        }
        fprintf(convolutional_image, "\n");
    }
    fclose(convolutional_image);

    cont_linha_pooling = 0;
    for(line = 0; line < image_line; line += pooling_line_size){
        cont_column_pooling = 0;
        for(column = 0; column < image_column; column += pooling_column_size){
            soma = 0;
            for(k = line; k < line + pooling_line_size; k++){
                for(l = column; l < column + pooling_column_size; l++){
                    soma += image[k][l];
                }
            }
            pooling[cont_linha_pooling][cont_column_pooling] = soma/(pooling_line_size*pooling_column_size);
            cont_column_pooling++;
        }
        cont_linha_pooling++;
    }

    convolutional_image = fopen("media.ascii.pgm", "w");

    fprintf(convolutional_image, "P2\n");
    fprintf(convolutional_image, "%d %d \n", pooling_line, pooling_column);
    fprintf(convolutional_image, "%d \n", maxValue);

    for(column = 0; column < pooling_column; column++){
        for(line = 0; line < pooling_line; line++){
            if(pooling[line][column] < 0){
                fprintf(convolutional_image, "%d ", 0);
            } else if(pooling[line][column] > maxValue){
                fprintf(convolutional_image, "%d ", maxValue);
            } else{
                fprintf(convolutional_image, "%d ", pooling[line][column]);
            }

        }
        fprintf(convolutional_image, "\n");
    }
    fclose(convolutional_image);

    return 0;
}
