#include <expat.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../include/phonebook.h"
#include "../include/names.h"

#define BUFFER_SIZE 100000
#define INDENT "    "

phonebook_t book;
human_t human;

void start_element(void *data, const char *element, const char **attribute) {
    /*
    printf("start_element %s", element);
    for (int i = 0; attribute[i]; i += 2) {
        printf(" %s = %s ", attribute[i], attribute[i + 1]);
    }
    printf("\n");
    */

    if (strcmp(element, "human") == 0) {
        strcpy(human.name, strtok((char *)attribute[1], " "));
        strcpy(human.middle_name, strtok(NULL, " "));
        strcpy(human.family_name, strtok(NULL, " "));
        human.phones_total = 0;
    }
}

void end_element(void *data, const char *element) {
    //printf("end_element %s\n", element);
    if (strcmp(element, "phone") == 0) {
        human.phones_total++;
    }
    else if (strcmp(element, "human") == 0) {
        push_back_human(&book, &human);
    }
}

void handle_data(void *data, const char *content, int length) {
    char *tmp = malloc(length + 1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    //printf("handle_data '%s' (len %d)\n", tmp, length);
    strcpy(human.phones[human.phones_total], tmp);
    free(tmp);
}

int parse_xml(char *buff, size_t buff_size) {
    FILE *fp;
    fp = fopen("pbook.xml", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);

    memset(buff, 0, buff_size);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), buff_size, fp);
        done = len < buff_size;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);

    return 0;
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
    int result;
    char buffer[BUFFER_SIZE];
    result = parse_xml(buffer, BUFFER_SIZE);
    assert(result == 0);
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<phonebook>\n");
    for (size_t i = 0; i < book->size; i++) {
        fprintf(fp, "%s<human name=\"%s %s %s\">\n", INDENT, book->humans[i].family_name, book->humans[i].name, book->humans[i].middle_name);
        for (int j = 0; j < book->humans[i].phones_total; j++) {
            fprintf(fp, "%s%s<phone>%s</phone>\n", INDENT, INDENT, book->humans[i].phones[j]);
        }
        fprintf(fp, "%s</human>\n", INDENT);
    }
    fprintf(fp, "</phonebook>\n");
}

void print_phonebook(phonebook_t *book) {
    printf("%d\n", book->size);
    for (int i = 0; i < book->size; i++) {
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);
        for (int j = 0; j < book->humans[i].phones_total; j++) {
            printf("phone: %s\n", book->humans[i].phones[j]);
        }
        printf("\n");
    }
}

void gen_phonebook(phonebook_t *book, size_t size) {
    clear_phonebook(book);
    char phone_number[21];
    int phones_total;

    srand(time(NULL));

    for (size_t i = 0; i < size; i++) {
        strcpy(human.name, kNames[rand() % NAMES_CNT]);
        strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
        strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);

        human.phones_total = rand() % 10;
        for (int j = 0; j < human.phones_total; j++) {
            sprintf(phone_number, "%d", rand());
            strcpy(human.phones[j], phone_number);
        }
        push_back_human(book, &human);
    }
}

void clear_phonebook(phonebook_t *book) {
    book->size = 0;
    book->capacity = 0;
    free(book->humans);
}

human_t get_human(phonebook_t *book, char* family_name) {
    return *(human_t *)bsearch(family_name, book->humans, book->size, sizeof(human_t), compar);
}

void push_back_human(phonebook_t *book, human_t *human) {
    if (book->size == book->capacity) {
        book->capacity = book->capacity * 2 + 1;

        human_t * tmp = realloc(book->humans, sizeof(human_t) * book->capacity);
        if (tmp != NULL) {
            if (tmp != book->humans) {
                book->humans = tmp;
            }
        } else {
            // Do something about the failed allocation
            printf("Failed to (re)allocate memory.");
            exit(1);
        }
    }
    memcpy(book->humans + book->size++, human, sizeof(human_t));
}

int compar (const void* p1, const void* p2) {
    return strcmp(((human_t *)p1)->family_name, ((human_t *)p2)->family_name);
}

int main(int argc, char **argv) {

    assert(argc > 2);

    load_phonebook_xml(argv[1], &book);
    qsort(book.humans, book.size, sizeof(human_t), compar);
    print_phonebook(&book);

    gen_phonebook(&book, 10);
    qsort(book.humans, book.size, sizeof(human_t), compar);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);

    return 0;
}
