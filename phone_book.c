
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Структура контакта

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

// Функция просмотра контакта

void view_contacts(struct Contact *contacts, int size) {
    if (size == 0) {
        printf("\nСписок контактов пуст.\n");
        return;
    }

    printf("\nВсе контакты:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. Имя: %s, Телефон: %s, Email: %s\n",
               i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

// Функция добавления контакта

void add_contact(struct Contact **contacts, int *size){
    (*size)++;
    *contacts = realloc(*contacts, (*size) * sizeof(struct Contact));

    printf("\nВведите имя нового контакта (Имя Фамилия): ");
    while (getchar() != '\n');
    fgets((*contacts)[*size-1].name, 50, stdin);
    (*contacts)[*size-1].name[strcspn((*contacts)[*size-1].name, "\n")] = '\0';
    
    printf("Введите номер телефона: ");
    scanf("%14s", (*contacts)[*size - 1].phone);
    
    printf("Введите email: ");
    scanf("%49s", (*contacts)[*size - 1].email);

    printf("\nКонтакт добавлен!\n");
}

// Функция удаления контакта

void delete_contact(struct Contact **contacts, int *size){
    char del_name[50];

    printf("\nВведите имя для удаления: ");
    while (getchar() != '\n');
    fgets(del_name, 50, stdin);
    del_name[strcspn(del_name, "\n")] = '\0';

    for(int i=0; i < *size; i++){
        if(strcmp((*contacts)[i].name, del_name) == 0){
            for(int j=i; j<*size-1;j++){
                (*contacts)[j]=(*contacts)[j+1];
            }
            (*size)--;
            (*contacts) = realloc(*contacts, (*size) * sizeof(struct Contact));
            printf("\nКонтакт удален.");
            return;
        }
    }
    printf("\nКонтакт не найден!\n");
}

// Функция поиска контакта

void search_contact(struct Contact *contacts, int size){
    char search_name[50];

    printf("\nВведите имя для поиска: ");
    while (getchar() != '\n');
    fgets(search_name, 50, stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    for(int i=0; i < size; i++){
        if(strcmp(contacts[i].name, search_name) == 0){    
            printf("Найден контакт:\n");
            printf("Имя: %s, тел.: %s, e-mail: %s", contacts[i].name, contacts[i].phone, contacts[i].email);
            return;
        }
    }
    printf("\nКонтакт не найден.\n");
}

// Функция изменения контакта (поиск и если не было ввода, оставляем прежнее)

void edit_contact(struct Contact *contacts, int size){

    char search_name[50];

    char new_name[50] = "";
    char new_phone[15] = "";
    char new_email[50] = "";

    printf("Введите имя контакта, для редактирования: ");
    while (getchar() != '\n');
    fgets(search_name, 50, stdin);
    search_name[strcspn(search_name, "\n")] = '\0';

    for(int i=0; i < size; i++){
        if(strcmp(contacts[i].name, search_name) == 0){    
            printf("Найден контакт:\n");
            printf("Имя: %s, тел.: %s, e-mail: %s \n", contacts[i].name, contacts[i].phone, contacts[i].email);

            // Изменяем поля, если ничего не введено, оставляем как есть
            
            printf("Введите новое имя или нажмите <Ввод>, чтобы оставить без изменений: ");
            // while (getchar() != '\n');
            fgets(new_name, 50, stdin);
            if (new_name[0] != '\n'){
                new_name[strcspn(new_name, "\n")] = '\0';
                strcpy(contacts[i].name, new_name);
            }       

            printf("Введите новый телефон или нажмите <Ввод>, чтобы оставить без изменений: ");
            //while (getchar() != '\n');
            fgets(new_phone, 15, stdin);
            if (new_phone[0] != '\n'){
                new_phone[strcspn(new_phone, "\n")] = '\0';
                strcpy(contacts[i].phone, new_phone);
            }  

            printf("Введите новый e-mail или нажмите <Ввод>, чтобы оставить без изменений: ");
            //while (getchar() != '\n');
            fgets(new_email, 50, stdin);
            if (new_email[0] != '\n'){
                new_email[strcspn(new_email, "\n")] = '\0';
                strcpy(contacts[i].email, new_email);
            }

            printf("Изменения в контакте:\n");
            printf("Имя: %s, тел.: %s, e-mail: %s \n", contacts[i].name, contacts[i].phone, contacts[i].email);
            return;
        }
    }
    printf("Контакт не найден.\n");
}

// Функция записи контактов в файл

void save_to_file(struct Contact *contacts, int size) {
    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла для записи.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s %s %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(file);
    printf("Контакты сохранены в файл.\n");
}

// Функция чтения контактов из файла

void load_from_file(struct Contact **contacts, int *size) {

    char firstname[25];
    char secondname[25];

    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("\nФайл с контактами не найден.\n");
        return;
    }

    struct Contact temp;
    while (fscanf(file, "%25s %25s %14s %49s", firstname, secondname, temp.phone, temp.email) == 4) {
        (*size)++;
        *contacts = realloc(*contacts, (*size) * sizeof(struct Contact));
        strcat(firstname, " ");
        strcat(firstname, secondname);
        strcpy(temp.name, firstname);
        (*contacts)[*size - 1] = temp;
    }
    fclose(file);
    printf("Контакты загружены из файла.\n");
}

// Основная программа

int main(void) {

    struct Contact *contacts = NULL;
    int size = 0;
    int choice;

    load_from_file(&contacts, &size);  // Загружаем контакты при старте программы

    do {
        printf("\nМеню:\n");
        printf("1. Добавить контакт\n");
        printf("2. Показать все контакты\n");
        printf("3. Найти контакт\n");
        printf("4. Изменить контакт\n");
        printf("5. Удалить контакт\n");
        printf("6. Сохранить контакты в файл\n");
        printf("0. Выйти\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_contact(&contacts, &size);
                break;
            case 2:
                view_contacts(contacts, size);
                break;
            case 3:
                search_contact(contacts, size);
                break;
            case 4:
                edit_contact(contacts, size);
                break;
            case 5:
                delete_contact(&contacts, &size);
                break;
            case 6:
                save_to_file(contacts, size);
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Ошибка: Неверный выбор.\n");
        }
    } while (choice != 0);

    free(contacts);  // Освобождаем память перед выходом
    return 0;
}