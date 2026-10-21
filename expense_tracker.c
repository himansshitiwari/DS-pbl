#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CATEGORY_LEN 20
#define DESC_LEN 50
#define NUM_CATEGORIES 5

/* ---------- Node structure ---------- */
struct Expense {
    int id;
    float amount;
    char category[CATEGORY_LEN];
    char description[DESC_LEN];
    struct Expense *next;
};

/* Fixed list of categories, shared by readCategory() and categoryTotals() */
const char *categories[NUM_CATEGORIES] = {
    "Food", "Travel", "Shopping", "Education", "Other"
};

/* ---------- Helper functions ---------- */

/* Gives a new unique ID every time it is called: 1, 2, 3, ... */
int generateId(void) {
    static int counter = 1;   /* keeps its value between calls */
    return counter++;
}

/* Reads one line safely and removes the trailing '\n'.
   Extra characters of a too-long line are discarded. */
void readLine(char *buf, int size) {
    char *newline;
    int c;

    if (fgets(buf, size, stdin) == NULL) {
        exit(0);              /* input closed (Ctrl+Z), quit quietly */
    }
    newline = strchr(buf, '\n');
    if (newline != NULL) {
        *newline = '\0';
    } else {
        while ((c = getchar()) != '\n' && c != EOF) {
            ;                 /* throw away the rest of the long line */
        }
    }
}

/* Keeps asking until the user enters a valid whole number */
int readInt(const char *prompt) {
    char line[50];
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        readLine(line, sizeof(line));
        /* result 1 means: a number was read and nothing else followed it */
        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            return value;
        }
        printf("Invalid input. Please enter a whole number.\n");
    }
}

/* Keeps asking until the user enters a valid amount */
float readAmount(void) {
    char line[50];
    float value;
    char extra;

    while (1) {
        printf("Enter amount (Rs.): ");
        readLine(line, sizeof(line));
        if (sscanf(line, "%f %c", &value, &extra) == 1 &&
            value > 0 && value <= 10000000) {
            return value;
        }
        printf("Invalid amount. Enter a number greater than 0.\n");
    }
}

/* Lets the user pick a category from the fixed list */
void readCategory(char *category) {
    int i, choice;

    printf("\nSelect category:\n");
    for (i = 0; i < NUM_CATEGORIES; i++) {
        printf(" %d. %s\n", i + 1, categories[i]);
    }

    while (1) {
        choice = readInt("Enter category number (1-5): ");
        if (choice >= 1 && choice <= NUM_CATEGORIES) {
            break;
        }
        printf("Invalid choice. Please select between 1 and 5.\n");
    }
    strcpy(category, categories[choice - 1]);
}

/* Reads a non-empty description that fits in the structure */
void readDescription(char *description) {
    char temp[100];

    while (1) {
        printf("Enter description (max %d characters): ", DESC_LEN - 1);
        readLine(temp, sizeof(temp));
        if (strlen(temp) == 0) {
            printf("Description cannot be empty.\n");
        } else if (strlen(temp) >= DESC_LEN) {
            printf("Description is too long.\n");
        } else {
            strcpy(description, temp);
        break;
        }
    }
}