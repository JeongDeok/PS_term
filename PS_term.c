#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int tag;
    char date[20];
    char p_info[20];
    char name[25];
    int age;
    char org[30];
    char job[15];
    struct person* next;
};

struct person p[100] = { 0 };

void newnode(struct person*, FILE**);//���������͸� newnode���� �ٷ�� ���� ������������ �ּҰ��� ���ڷ� ��
void linked_delete(char* name, struct person* head);//P6-2
void linked_one_new_insert(struct person* new_node, struct person* head);//P7
void calc_checksum(int*, int);
void main()
{
    FILE* myinFile, * myoutFile;
    int n = 0, i = 0, j = 0;
    int nni = 0;//newnodeindex
    struct person temp;
    const char* f_name = "Choi";
    struct person* ptr1;//������
    struct person* ptr2;
    struct person* head = (struct person*)malloc(sizeof(struct person));//���
    int checksum, readed_checksum, checksum2;
    char c, n_buf[20], * str = "";
    char* ptr;


    head->next = NULL;
    ptr1 = head;



    myinFile = fopen("registraion_data.txt", "r");
    if (myinFile == NULL) {
        printf("\nFile Could Not Be Opened");
        exit(1);
    }

    while (fscanf(myinFile, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%[^\n]\n", &p[n].tag, p[n].date, p[n].p_info, p[n].name, &p[n].age, p[n].org, p[n].job) > 0) {
        n++;
    }//verstion 1
    fseek(myinFile, 0, SEEK_SET);//Ŀ�� ����
    while (nni < n) {
        newnode(head, &myinFile);//head�� ����ǥ���� �ּҸ� �Է�
        nni++;
    }//verstion 2

    nni = 0;
    /*ptr1 = head;//reset ptr1
    while (nni < n) {//print linked list
        ptr1 = ptr1->next;
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
        nni++;
    }*/
    printf("arr choi===================================================================================\n");

    //P1-1
    for (i = 0; i < n; i++) {
        ptr = strstr(p[i].name, f_name);
        if (ptr != NULL) {
            printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
        }
    }

    printf("link choi===================================================================================\n");

    //P1-2
    ptr1 = head;
    while (ptr1->next != NULL) {
        ptr1 = ptr1->next;
        ptr = strstr(ptr1->name, f_name);
        if (ptr != NULL)
            printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);
    }

    printf("arr ga===================================================================================\n");

    //P2-1
    for (int k = 0; k < n - 1; k++) {
        for (int q = 0; q < n - k - 1; q++) {
            if (strcmp(p[q].org, p[q + 1].org) >= 0) {
                temp = p[q];
                p[q] = p[q + 1];
                p[q + 1] = temp;
            }
        }
    }

    /*
    ���� �ִ� ���� for���� ���б� �̸� ũ�⸦ ���ؼ� �迭�� ������
    �̸��� ���� ������ ���ĵ� ���� ���

    Australian National Universitystudent_1
    Cornell University_2
    Duke University_1
    Fudan University_1
    Gachon University_9 -> �ε����� ������ [5] ~ [13]
    Havard....���
    */

    for (i = 0; i < n; i++) {
        if (i >= 5 && i <= 13) {
            printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
        }
        else {
            continue;
        }
    }

    printf("link ga===================================================================================\n");

    //P2-2
    ptr1 = head;//reset ptr1 
    while (ptr1->next) {//print linked list
        ptr1 = ptr1->next;
        if (strcmp(ptr1->org, "Gachon University") == 0)
            printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
    }

    printf("tag sort===================================================================================\n");
    //P3-1
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].tag > p[j + 1].tag) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
    }
    printf("copy to link===================================================================================\n");

    //P4-1
    i = 0;
    ptr1 = head;//reset ptr1 
    for (i = 0; i < n; i++) {
        ptr1 = ptr1->next;
        ptr2 = ptr1->next;

        *ptr1 = p[i];
        ptr1->next = ptr2;
    }

    ptr1 = head;//reset ptr1 
    while (ptr1->next != NULL) {//print linked list
        ptr1 = ptr1->next;
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
    }
    printf("P5-1===================================================================================\n");
    //P5-1
    int min;

    for (i = 0; i < n - 1; i++) {
        min = i;

        for (j = i + 1; j < n; j++) {
            if (p[j].age < p[min].age)
                min = j;
        }

        if (i != min) {
            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }

    myoutFile = fopen("5-1.txt", "w");
    if (myoutFile == NULL) {
        printf("\nFile Could Not Be Opened");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        fprintf(myoutFile, "%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
    }

    fclose(myinFile);
    fclose(myoutFile);

    ptr1 = head;//reset ptr1
    while (nni < n) {//print linked list
        ptr1 = ptr1->next;
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
        nni++;
    }
    printf("\nP6-1===================================================================================\n");
    //P6-1
    printf("delete choi\n");
    int n2 = n;
    i = 0;
    j = 0;
    int k;
    while (p[i].tag != '\0')
    {
        char* ptr2 = strstr(p[i].name, "Choi");
        if (ptr2 != NULL)
        {
            for (k = i; k < n2; k++)
            {
                p[k] = p[k + 1];
            }
            n2 = n2 - 1;
        }
        i++;
    }
    //���߿� �����
    for (i = 0; i < n2; i++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
    }

    printf("\nP6-2===================================================================================\n");
    //P6-2
    //Every Choi cancled
    linked_delete(f_name, head);//f_name is "Choi"

    ptr1 = head;//reset ptr1
    while ((ptr1->next) != NULL) {//print linked list
        ptr1 = ptr1->next;
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
    }

    printf("\nP7-1===================================================================================\n");
    //P7-1
    printf("Add Paik\n");
    int a;
    struct person temp2[100];
    struct person Paik = { 100, "2020-11-30" , "yes", "Ildang Paik", 22, "Gachon University", "engineer" };

    for (i = 0; i < n2; i++)
    {
        if (p[i].age > Paik.age)
        {
            a = 0;
            temp2[a] = p[i];
            p[i] = Paik;

            n2 = n2 + 1;
            for (j = i + 1; j < n2; j++)
            {
                temp2[a + 1] = p[j];
                p[j] = temp2[a];
                a++;
            }
            break;
        }
    }
    //���߿� �����
    for (i = 0; i < n2; i++) {
        printf("%d/%s/%s/%s/%d/%s/%s\n", p[i].tag, p[i].date, p[i].p_info, p[i].name, p[i].age, p[i].org, p[i].job);
    }


    printf("\nP7-2===================================================================================\n");

    //P7-2
    //New Paik : 100/2020-11-30/yes/Ildang Paik/22/Gachon University/engineer

    struct person paik = { 100,"2020-11-30","yes","Ildang Paik",22,"Gachon University","engineer",NULL };
    ptr1 = &paik;

    linked_one_new_insert(ptr1, head);

    ptr1 = head;//reset ptr1
    while ((ptr1->next) != NULL) {//print linked list
        ptr1 = ptr1->next;
        printf("%d/%s/%s/%s/%d/%s/%s\n", ptr1->tag, ptr1->date, ptr1->p_info, ptr1->name, ptr1->age, ptr1->org, ptr1->job);//linked list ���
    }

    printf("\nP8-1===================================================================================\n");
    //8-1

    FILE* in, * out;
    checksum = checksum2 = 0;
    calc_checksum(&checksum, n2);//calculate checksum with last 5 names in p[]

    out = fopen("8-1.txt", "w");

    fprintf(out, "%d\n", checksum);
    for (i = n2 - 1; i > n2 - 6; i--)
        fprintf(out, "%s\n", p[i].name);

    printf("Copy to 8-1.txt completed.\n");
    fseek(out, 0, SEEK_SET);//Ŀ�� ����

    /*�� �������� in ���� �̸����� �о�鿩�� �ٽ�. �ѹ�checksum ����Ѵ�. �׷��� ���� original checksum�� ��ġ�ϴ��� Ȯ���ϸ� ��*/

    in = fopen("8-1.txt", "r");
    if (in == NULL) {
        printf("\nFile Could Not Be Opened");
        exit(1);
    }

    printf("Start comfirm checksum.\nOriginal checksum : %d\n\n", checksum);

    i = 0;
    while ((str = fgets(n_buf, sizeof(char) * 20, in)) != NULL)
    {
        if (i == 0)
        {
            i++;
            continue;
        }

        j = 0;
        while (str[j] != '\n')//���Ϸ� �о���� �̸��� ���� NULL���� '\0' �� �ƴ� \n�� ����!!
        {
            c = str[j];

            if (str[j] == ' ')
            {
                j++;
                continue;
            }

            if (checksum2 == 0)
                checksum2 = c;
            else
                checksum2 = checksum2 ^ c;
            j++;
        }

        printf("%s", str);
        i++;
    }

    printf("New calculated checksum : %d\n", checksum2);
    if (checksum == checksum2)
        printf("Checksum Confirmed.\n");

    else
        printf("Checksum is incorrect. File has been damaged.\n");



}

void newnode(struct person* head, FILE** FP)
{
    struct person* ptr;

    ptr = head;
    while (1) {
        if (ptr->next == NULL) {
            struct person* nnode = (struct person*)malloc(sizeof(struct person));
            ptr->next = nnode;
            ptr = ptr->next;
            fscanf(*FP, "%d/%[^/]/%[^/]/%[^/]/%d/%[^/]/%[^\n]\n", &nnode->tag, nnode->date, nnode->p_info, nnode->name, &nnode->age, nnode->org, nnode->job);
            nnode->next = NULL;
            break;
        }
        else
            ptr = ptr->next;
    }

}

void linked_delete(char* name, struct person* head)//P6-2, sjh
{

    struct person* prev_node, * node, * del_node;
    char* temp;
    node = head;
    while (node->next != NULL)
    {
        prev_node = node;
        node = node->next;

        temp = strstr(node->name, name); //name is "Choi"

        if (temp != NULL)
        {
            prev_node->next = node->next;//This way, we can't find "Choi" in the list anymore
            del_node = node;
            node = prev_node;

            free(del_node);
        }
    }
}


void linked_one_new_insert(struct person* new_node, struct person* head)//P7-2
{
    struct person* prev_node, * node;
    node = head;

    while (node->next != NULL)
    {
        prev_node = node;
        node = node->next;

        if (new_node->tag < node->tag)
        {
            new_node->next = node;
            prev_node->next = new_node;
            break;
        }
    }

    if (node->next == NULL)
    {
        node->next = new_node;
        new_node->next = NULL;
    }
}

void calc_checksum(int* checksum, int len)
{
    char c;
    int i, j;

    *checksum = 0;

    for (i = len - 1; i > len - 6; i--)
    {
        j = 0;
        while (p[i].name[j] != '\0')
        {
            c = p[i].name[j];

            if (p[i].name[j] == ' ')
            {
                j++;
                continue;
            }

            if (*checksum == 0)
                *checksum = c;
            else
                *checksum = *checksum ^ c;

            j++;
        }

    }
}