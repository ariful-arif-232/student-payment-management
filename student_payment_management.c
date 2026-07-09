#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct node {
    int reg;
    int due;
    struct node *prev;
    struct node *next;
};

struct qnode {
    int reg;
    struct qnode *next;
};

struct node *head = NULL;
struct qnode *qhead = NULL, *tail = NULL;

int A[20] = {0}, B[20] = {0}, C[20] = {0}, D[20] = {0};

int menu() {
    int n;
    printf("\n====== Student Payment and Finance Management System ======\n\n");
    printf("[1]  Add An Account for One Student\n");
    printf("[2]  Add Accounts for Multiple Students\n");
    printf("[3]  First Installment\n");
    printf("[4]  Final Installment\n");
    printf("[5]  Payment for One Student\n");
    printf("[6]  Payment for Multiple Students\n");
    printf("[7]  Student List and Due Amount\n");
    printf("[8]  Clearance List\n");
    printf("[9]  Section Application\n");
    printf("[10] Section Based Student List\n");
    printf("[91] Exit Program\n");
    printf("Enter Your Choice: ");
    scanf("%d", &n);
    system("cls");
    return n;
}

void goBack() {
    int go;
    printf("\n[1] Go Back\n");
    while (1) {
        printf("Enter Your Choice: ");
        scanf("%d", &go);
        if (go == 1) {
            system("cls");
            break;
        }
    }
}

struct node* createNode() {
    struct node *newnode, *temp;
    newnode = (struct node*)malloc(sizeof(struct node));

    printf("Registration number: ");
    scanf("%d", &newnode->reg);
    newnode->due = 0;
    newnode->prev = NULL;
    newnode->next = NULL;

    temp = head;
    while (temp != NULL) {
        if (temp->reg == newnode->reg) {
            printf("Student already exists.\n");
            free(newnode);
            return createNode();
        }
        temp = temp->next;
    }

    printf("\nNew Account Added\n");
    printf("Registration Number: %d\n", newnode->reg);
    printf("Due Balance: %d\n\n", newnode->due);

    return newnode;
}

void addNode(struct node *newnode) {
    struct node *temp;

    if (head == NULL) {
        head = newnode;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;
    }
}

void a_student() {
    printf("=== Account for A Single Student ===\n\n");
    addNode(createNode());
    goBack();
}

void multi_student() {
    int n, i;
    printf("=== Account for Multiple Students ===\n\n");
    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("\nEnter Data for Student No. %d\n", i);
        addNode(createNode());
    }

    goBack();
}

void display() {
    struct node *temp = head;
    int i = 1;

    printf("=== Student List and Due Amount ===\n\n");

    if (temp == NULL) {
        printf("No student found.\n");
    }

    while (temp != NULL) {
        printf("%d. Registration No: %d\n", i, temp->reg);
        printf("   Due Amount: %d\n", temp->due);
        temp = temp->next;
        i++;
    }

    goBack();
}

void add_due(int amount) {
    struct node *temp = head;

    while (temp != NULL) {
        temp->due += amount;
        temp = temp->next;
    }
}

void first_install() {
    printf("Adding First Installment Due...\n");
    add_due(50000);
    Sleep(1000);
    printf("First Installment Due Added.\n");
    goBack();
}

void final_install() {
    printf("Adding Final Installment Due...\n");
    add_due(30000);
    Sleep(1000);
    printf("Final Installment Due Added.\n");
    goBack();
}

void enqueue(int reg) {
    struct qnode *newnode;
    newnode = (struct qnode*)malloc(sizeof(struct qnode));

    newnode->reg = reg;
    newnode->next = NULL;

    if (qhead == NULL) {
        qhead = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
}

int dequeue() {
    struct qnode *temp;
    int reg;

    if (qhead == NULL) {
        printf("Queue is Empty\n");
        return -1;
    }

    temp = qhead;
    reg = qhead->reg;
    qhead = qhead->next;

    if (qhead == NULL) {
        tail = NULL;
    }

    free(temp);
    return reg;
}

void payment() {
    int reg, pay, found = 0;
    struct node *temp = head;

    printf("Registration No: ");
    scanf("%d", &reg);

    while (temp != NULL) {
        if (temp->reg == reg) {
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (found == 0) {
        printf("Student not found.\n");
        return;
    }

    printf("Payment Amount: ");
    scanf("%d", &pay);

    temp->due -= pay;

    printf("\nPayment Done for Registration No: %d\n", temp->reg);
    printf("Remaining Due: %d\n", temp->due);

    if (temp->due <= 0) {
        printf("Registration Clearance Is Now Available\n");
        enqueue(temp->reg);
    }
}

void single_pay() {
    printf("=== Single Student Payment ===\n\n");
    payment();
    goBack();
}

void multi_pay() {
    int n, i;

    printf("=== Multiple Student Payment ===\n\n");
    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        printf("\nPayment for Student No. %d\n", i);
        payment();
    }

    goBack();
}

void qdisplay() {
    struct qnode *temp = qhead;
    int i = 1;

    printf("=== Students With Clearance List ===\n\n");

    if (temp == NULL) {
        printf("Queue is Empty\n");
    } else {
        while (temp != NULL) {
            printf("%d. Registration No: %d\n", i, temp->reg);
            temp = temp->next;
            i++;
        }
    }

    goBack();
}

void apply_sec() {
    int a = 0, b = 0, c = 0, d = 0;
    int stu, sec;

    printf("=== Section Application ===\n\n");

    while ((a < 20 || b < 20 || c < 20 || d < 20) && qhead != NULL) {
        stu = dequeue();

        printf("\nRemaining Seats:\n");
        printf("A = %d, B = %d, C = %d, D = %d\n\n", 20 - a, 20 - b, 20 - c, 20 - d);

        printf("Select Section for Registration No. %d\n", stu);
        printf("[1] A\n");
        printf("[2] B\n");
        printf("[3] C\n");
        printf("[4] D\n");

        while (1) {
            printf("Enter Your Choice: ");
            scanf("%d", &sec);

            if (sec == 1 && a < 20) {
                A[a++] = stu;
                break;
            } else if (sec == 2 && b < 20) {
                B[b++] = stu;
                break;
            } else if (sec == 3 && c < 20) {
                C[c++] = stu;
                break;
            } else if (sec == 4 && d < 20) {
                D[d++] = stu;
                break;
            } else {
                printf("Section is full or invalid. Choose again.\n");
            }
        }
    }

    goBack();
}

void section_list() {
    int i;

    printf("=== Section Based Student List ===\n\n");
    printf("No. |   A   |   B   |   C   |   D   |\n");
    printf("--------------------------------------\n");

    for (i = 0; i < 20; i++) {
        printf("%2d  | %5d | %5d | %5d | %5d |\n", i + 1, A[i], B[i], C[i], D[i]);
    }

    goBack();
}

int main() {
    while (1) {
        int choice = menu();

        if (choice == 1)
            a_student();
        else if (choice == 2)
            multi_student();
        else if (choice == 3)
            first_install();
        else if (choice == 4)
            final_install();
        else if (choice == 5)
            single_pay();
        else if (choice == 6)
            multi_pay();
        else if (choice == 7)
            display();
        else if (choice == 8)
            qdisplay();
        else if (choice == 9)
            apply_sec();
        else if (choice == 10)
            section_list();
        else if (choice == 91) {
            printf("Program Closed.\n");
            break;
        } else {
            printf("Invalid Choice.\n");
            Sleep(1000);
            system("cls");
        }
    }

    return 0;
}
