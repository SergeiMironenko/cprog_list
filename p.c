#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

// Узел
typedef struct Node
{
    int a;
    struct Node *next;
} Node;

// Инициализация списка
Node *init_list()
{
    Node *head = (Node*)malloc(sizeof(Node));
    head->a = 0;
    head->next = NULL;
    return head;
}

// Добавление нового узла
void add_node(Node *head, int pos, int val)
{
    Node *node = head;
    while (node->next && pos)
    {
        node = node->next;
        pos--;
    }

    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->a = val;
    new_node->next = node->next;
    node->next = new_node;
}

// Добавление нового уникального узла
void add_unique_node(Node *head, int pos, int val)
{
    Node *node = head;
    int unique = 1;
    while (unique && node->next && pos)
    {
        node = node->next;
        if (node->a == val) unique = 0;
        pos--;
    }
    if (unique)
    {
         Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->a = val;
        new_node->next = node->next;
        node->next = new_node;
    }
}

// Редактирование узла
void edit_node(Node *head, int pos, int val)
{
    Node *node = head->next;
    while (node && pos)
    {
        node = node->next;
        pos--;
    }
    if (node)
    {
        node->a = val;
    }
}

// Удаление узла
void delete_node(Node *head, int pos)
{
    Node *node = head;
    while (node->next && node->next->next && pos)
    {
        node = node->next;
        pos--;
    }
    if (node->next)
    {
        Node *del_node = node->next;
        node->next = node->next->next;
        free(del_node);
    }
}

// Получение случайного числа в диапазоне
int random_int(int min, int max)
{
    return min + rand() % (max - min);
}

// Заполнение списками случайными числами
void random_list(Node *head)
{
    srand(time(NULL));
    Node *node = head->next;
    while (node)
    {
        node->a = random_int(-100, 100);
        node = node->next;
    }
}

// Объединение двух списков
Node *union_list(Node *head, Node *head2)
{
    Node *head3 = init_list();

    Node *node = head->next;
    while(node)
    {
        (head3, -1, node->a);
        node = node->next;
    }

    Node *node2 = head2->next;
    while(node2)
    {
        add_unique_node(head3, -1, node2->a);
        node2 = node2->next;
    }

    return head3;
}

// Длина списка
int list_len(Node *head)
{
    int len = 0;
    Node *node = head;
    while (node->next)
    {
        node = node->next;
        len++;
    }
    return len;
}

// Сравнение узлов
int node_cmp(Node *node1, Node *node2)
{
    int cmp = 0;
    if (node1->a > node2->a) cmp = 1;
    else if (node1->a < node2->a) cmp = -1;
    return cmp;
}

// Поменять местами значения узлов
void node_swap(Node *node1, Node *node2)
{
    int tmp = node1->a;
    node1->a = node2->a;
    node2->a = tmp;
}

// Сортировка пузырьком
void bubble_sort(Node *head)
{
    Node *node1 = head;
    while (node1->next != NULL)
    {
        Node *node2 = node1->next;
        while (node2->next != NULL)
        {
            if (node_cmp(node1->next, node2->next) > 0) node_swap(node1->next, node2->next);
            node2 = node2->next;
        }
        node1 = node1->next;
    }
}

// Сортировка расческой
void comb_sort(Node *head)
{
    float coef = 1.247;
    int len = list_len(head);
    int i = 0, j = (int)(len / coef);
    while (j - i >= 1)
    {
        Node *node1 = head->next;
        Node *node2 = node1;
        for (int k = 0; k < j; k++) node2 = node2->next;
        for (int k = j; k < len; k++)
        {
            if (node_cmp(node1, node2) == -1) node_swap(node1, node2);
            node1 = node1->next;
            node2 = node2->next;
        }
        j = (int)(j / coef);
    }
}

// Вывод списка
void print_list(Node *head)
{
    Node *node = head->next;
    printf("--- ---\n");
    int i = 0;
    while (node)
    {
        printf("%d [%d]\n", node->a, i++);
        node = node->next;
    }
    if (!i) printf("Список пустой\n");
    printf("--- ---\n");
}

// Вывод списка с конца
void print_list_reverse(Node *node, int i)
{
    if (node)
    {
        print_list_reverse(node->next, i + 1);
        printf("%d [%d]\n", node->a, i);
    }
}

// Освобождение памяти
int free_list(Node *head)
{
    Node *node = head->next;
    while(node)
    {
        Node *free_node = node;
        node = node->next;
        free(free_node);
    }
    free(head);
}

// Интерактивное меню
void menu(char *ch, Node *head)
{
    int pos = 0, val = 0;
    char x = 0;
    switch(*ch)
    {
        case '1':
            printf("Формат ввода: <позиция> <значение>\n> ");
            scanf("%d %d%c", &pos, &val, ch);
            if (*ch == '\n')
            {
                add_node(head, pos, val);
                print_list(head);
            }
            else 
            {
                printf("Некорректный ввод\n");
            }
            break;
        case '2':
            printf("Формат ввода: <позиция>\n> ");
            scanf("%d%c", &pos, ch);
            if (*ch == '\n')
            {
                delete_node(head, pos);
                print_list(head);
            }
            else
            {
                printf("Некорректный ввод\n");
            }
            *ch = '\n';
            break;
        case '3':
            printf("Формат ввода: <позиция> <значение>\n> ");
            scanf("%d %d%c", &pos, &val, ch);
            if (*ch == '\n')
            {
                edit_node(head, pos, val);
                print_list(head);
            }
            else
            {
                printf("Некорректный ввод\n");
            }
            break;
        case '4':
            print_list(head);
            break;
        case '5':
            print_list_reverse(head->next, 0);
            break;
        case '6':
            random_list(head);
            print_list(head);
            break;
        case '7':
            printf("Введите кол-во узлов\n> ");
            scanf("%d%c", &val, ch);
            if (*ch == '\n')
            {
                for (int i = 0; i < val; i++) add_node(head, -1, random_int(-100, 100));
                print_list(head);
            }
            else
            {
                printf("Некорректный ввод\n");
            }
            break;
        case '8':
            printf("Пузырьком: 0, расческой: 1\n> ");
            scanf("%d%c", &val, ch);
            if (val) comb_sort(head);
            else bubble_sort(head);
            print_list(head);
            break;
        case '9':
            system("clear");
            break;
    }
    printf("<< Меню взаимодествия со списком >>\n");
    printf("1 - Добавить узел.\n");
    printf("2 - Удалить узел.\n");
    printf("3 - Редактировать узел.\n");
    printf("4 - Вывести список.\n");
    printf("5 - Вывести список с конца.\n");
    printf("6 - Заполнить список случайными числами.\n");
    printf("7 - Добавить в список n случайных чисел.\n");
    printf("8 - Сортировка.\n");
    printf("9 - Очистка экрана.\n");
    printf("q - Выход.\n");
}

// Очистка потока ввода stdin
void clear_stdin(char *ch)
{
    while (*ch != '\n') { *ch = getchar(); }
}

int run()
{
    Node *head = init_list();
    char ch = '\n';
    while (ch != 'q')
    {
        menu(&ch, head);
        clear_stdin(&ch);
        printf("> ");
        scanf("%c", &ch);
    }
    free_list(head);
}

int main(int argc, char *argv[])
{
    run();
    return 0;
}
