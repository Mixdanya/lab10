#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>


double calc_f1(double val_x);
double calc_f2(double val_x);
double calc_ln_terms(double val_x, int count);
double calc_ln_precision(double val_x, double precision);

float calc_area_rect(float width, float height);
void print_rect_info(void);
void render_rect(int width, int height, char symbol);
int input_side(void);
float compare_rects(float area1, float area2);


int task1();
int task2();
int task3();

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    task1();
    task2();
    task3();

    return 0;
}

int task1()
{
    double input_x, res1, res2;
    int action;

    printf("\n--- Задание 1 ---\n");
    printf("Введите значение аргумента x: ");
    scanf("%lf", &input_x);

    res1 = calc_f1(input_x);
    res2 = calc_f2(input_x);

    printf("\nЗначение F1(x) = %lf", res1);
    printf("\nЗначение F2(x) = %lf\n", res2);

    printf("\n1 - Вывести F1(x)");
    printf("\n2 - Вывести F2(x)");
    printf("\n3 - Произведение функций");
    printf("\n4 - Разность квадратов");
    printf("\n5 - Удвоенная сумма");
    printf("\nВыберите номер операции: ");
    scanf("%d", &action);

    switch (action)
    {
    case 1:
        printf("Результат F1(x) = %lf\n", res1);
        break;
    case 2:
        printf("Результат F2(x) = %lf\n", res2);
        break;
    case 3:
        printf("Произведение = %lf\n", res1 * res2);
        break;
    case 4:
        printf("Разность квадратов = %lf\n", res1 * res1 - res2 * res2);
        break;
    case 5:
        printf("Удвоенная сумма = %lf\n", 2.0 * (res1 + res2));
        break;
    default:
        printf("Ошибка: выбран неверный пункт меню!\n");
        break;
    }

    return 0;
}

int task2()
{
    double arg_x, accuracy;
    int terms_count;

    printf("\n--- Задание 2 ---\n");
    printf("Введите значение x (x > 0): ");
    scanf("%lf", &arg_x);

    if (arg_x <= 0)
    {
        printf("Ошибка! Аргумент x должен быть строго больше 0.\n");
        return 0;
    }

    printf("Введите количество членов ряда N: ");
    scanf("%d", &terms_count);

    printf("Введите требуемую точность eps: ");
    scanf("%lf", &accuracy);

    if (terms_count <= 0 || accuracy <= 0)
    {
        printf("Ошибка! Значения N и eps должны быть положительными.\n");
        return 0;
    }

    double std_log = log(arg_x);
    double approx_n = calc_ln_terms(arg_x, terms_count);
    double approx_eps = calc_ln_precision(arg_x, accuracy);

    printf("\nСтандартная функция log(x) = %lf\n", std_log);
    printf("Сумма %d членов ряда = %lf\n", terms_count, approx_n);
    printf("Значение с точностью eps = %lf\n", approx_eps);

    printf("\nПогрешность при фиксированном N = %lf\n", fabs(std_log - approx_n));
    printf("Погрешность при заданной точности eps = %lf\n", fabs(std_log - approx_eps));

    return 0;
}

int task3()
{
    int menu_item, width1, height1, width2, height2;
    char brush;

    printf("\n--- Задание 3 (Прямоугольник) ---\n");

    printf("Задайте ширину прямоугольника.\n");
    width1 = input_side();
    printf("Задайте высоту прямоугольника.\n");
    height1 = input_side();

    if (width1 <= 0 || height1 <= 0)
    {
        printf("Ошибка! Стороны фигуры должны быть больше 0.\n");
        return 0;
    }

    printf("Введите символ для отрисовки контура: ");
    scanf(" %c", &brush);

    printf("\nМеню операций:");
    printf("\n1 - Рассчитать площадь фигуры");
    printf("\n2 - Вывести определение фигуры");
    printf("\n3 - Нарисовать фигуру");
    printf("\n4 - Сравнить по площади со вторым прямоугольником");
    printf("\nВаш выбор: ");
    scanf("%d", &menu_item);

    switch (menu_item)
    {
    case 1:
        printf("Площадь прямоугольника = %.2f\n", calc_area_rect((float)width1, (float)height1));
        break;

    case 2:
        print_rect_info();
        break;

    case 3:
        render_rect(width1, height1, brush);


        break;

    case 4:
        printf("\nВведите параметры второго прямоугольника:\n");
        printf("Ширина второй фигуры:\n");
        width2 = input_side();
        printf("Высота второй фигуры:\n");
        height2 = input_side();

        if (width2 <= 0 || height2 <= 0)
        {
            printf("Ошибка! Размеры должны быть положительными.\n");
        }
        else
        {
            float s1 = calc_area_rect((float)width1, (float)height1);
            float s2 = calc_area_rect((float)width2, (float)height2);
            float diff = compare_rects(s1, s2);
            printf("Разница площадей (первая минус вторая) = %.2f\n", diff);
        }
        break;

    default:
        printf("Ошибка: такого пункта меню не существует!\n");
        break;
    }

    return 0;
}

// функции

double calc_f1(double val_x)
{
    double result;
    if (val_x <= 3.0)
        result = val_x * val_x - 3.0 * val_x + 9.0;
    else
        result = 1.0 / (val_x * val_x * val_x + 3.0);

    return result;
}

double calc_f2(double val_x)
{
    return val_x * exp(sin(val_x * val_x));
}

double calc_ln_terms(double val_x, int count)
{
    double ratio = (val_x - 1.0) / (val_x + 1.0);
    double current_term, total_sum = 0.0;

    for (int idx = 0; idx < count; idx++)
    {
        current_term = 2.0 * pow(ratio, 2 * idx + 1) / (2 * idx + 1);
        total_sum += current_term;
    }

    return total_sum;
}

double calc_ln_precision(double val_x, double precision)
{
    double ratio = (val_x - 1.0) / (val_x + 1.0);
    double current_term, total_sum = 0.0;
    int idx = 0;

    do
    {
        current_term = 2.0 * pow(ratio, 2 * idx + 1) / (2 * idx + 1);
        total_sum += current_term;
        idx++;
    } while (2.0 * pow(fabs(ratio), 2 * idx + 1) / ((2 * idx + 1) * (1.0 - ratio * ratio)) > precision);

    return total_sum;
}



float calc_area_rect(float width, float height)
{
    return width * height;
}

void print_rect_info(void)
{
    printf("Прямоугольник — это четырёхугольник, у которого все углы прямые (равны 90 градусам), ");
    printf("а противоположные стороны попарно равны и параллельны.\n");
}

void render_rect(int width, int height, char symbol)
{
    printf("\n");
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {

            if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
                printf("%c", symbol);
            else
                printf(" ");
        }
        printf("\n");
    }
}

int input_side(void)
{
    int dimension;
    printf("Введите размер стороны: ");
    scanf("%d", &dimension);
    return dimension;
}

float compare_rects(float area1, float area2)
{
    return area1 - area2;
}