/*  ͼ�����ϵͳ
    1����Ҫʵ�ֵĹ���
        ��1��������Ա����ɾ��ġ���軹��������
        ��2�����û�����軹��������
    2������ʵ��
        ��1��������Ա
            a����ɾ��ģ������ڲ��ҹ��ܣ��ҵ����ݵ�λ�ý�����صĲ�����д��������У�
               �����������硢ISBN�������߹���Ϊ�鼮��Ϣ�������鼮���ID��ϵͳ���պ�������
            b����軹�����ĳһ��ѧ�ţ���������ĳһ���鼮���ڼ�������в�ѯ
            c�������ڣ�����ĳһ����Ľ軹����
            e���½����޸ġ�ɾ���û�
        ��2�����û�
            a����ѯĳ�����Ƿ��ڼܣ���һ��ࣺ���鼮��Ϣ����������ѯ����������Ϣ
            b����ѯ�Լ��Ľ��Ľ�ֹʱ��ͽ��ļ�¼
            c����ѯ�����鼮��Ԥ�ڹ黹ʱ��
    3������ṹ
        ��1�������ݴ洢�ṹ
            a��user.txt          �洢�û���Ϣ�ļ�
            b��bookshelf.txt     �洢ͼ����Ϣ�ļ�
            c��history.dat       ͼ�����״̬�ļ�
        ��2�������ֵ����ݽṹ
            a�����������͡��ַ��͡��ṹ�����
            b��ָ�룺�ļ�ָ�����������ָ�����
        ��3����������ṹ
            a��main              ����ʼ�ĵط�,�����˶Ը������ܵĵ����Լ�ѭ���Ŀ���
            b��search_tool       ���������Ϣ�м�������Ŀ��ļ�����֮ƥ������ݣ����ظ�λ������
            c��append_book       ��ѯbookshelf���ݿ⣬���û�������ԱȨ�ޣ�ѡ������
            d��append_user       ��ѯuser���ݿ⣬���û�������ԱȨ�ޣ�ѡ��ɾ��
            e��change            �������ݿ����Լ���Ҫ���ĵ����ݡ��޸ĺ�����ݽ����޸�
            f��login             ��main�������ȵ��ò�ȷ�����û���Ȩ�ޣ�������Ӧ�Ĺ��ܲ˵�
            g��menu              ����ȫ�ֱ����洢���û�Ȩ�޸�����ͬ�Ĳ˵��ͺ������ù�ϵ
            h��del_book          ɾ���鼮
            i��del_user          ɾ���û��˻�
            j������Ĺ��ܸ�������     �����ַ����ȶԡ�char��int����ת�����Զ������������˵�����ʾ��������ɾ������......
*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "string.h"


int debug_mode=0;//debugר�ñ�����0Ϊ��debug��1Ϊģ���û�debug��2Ϊ����Աdebug


struct useragent_inf
{
    int id;
    int authority;
    char name[30];
    char password[30];
}useragent={.authority=0,.name="\0",.password="\0"};//��ȫ�ֱ����д洢�ɹ���¼���û��������ڹ��ܺ����ķ���
void append_book();
void del_book();
int search_tool(char *,char *,char *);
void change(char *,char *,char *);
void login();
void book_search(int);
void history();
void menu_bottom_bar();
void new_screen();//�´��ڴ򿪺���
void clear();//����Ӧ��������
void menu(int user_type);
int compare_str(char *,char *);
int trans_int(char *);
int del_row(char *,char *);
void append_user();
void del_user();
void change_book();
void change_user();
void clear_str(char *);
void borrow_book();
void history();
void loan_search();
char *trans_char(int,char *);
void return_book();
void time_back(char *);

int main()
{
    new_screen();
    int k=0;
    if (!debug_mode)
    {
        printf("��1����¼\t\t\t\t��2���˳�");
        menu_bottom_bar();
        scanf("%d",&k);
    }
    if (debug_mode)
    {
        //login();
        useragent.authority= debug_mode;
        strcpy(useragent.password,"debug");
        strcpy(useragent.name,"debug");
        useragent.id=0;
        menu(debug_mode);
        //user();
        exit(0);
    }
    if (k==1)
    {
        login();
        menu(useragent.authority);
        //user();
    }
    else exit(0);
    return 0;
}

void menu_bottom_bar()
{
    printf("\n_____________________________________\n�밴���ּ�ѡ������Ҫִ�еĲ���:");
}

void time_back(char result[])
{
    FILE *p;
    //char result[3001]="\0";
    p=fopen("qwertyuiop.dat","w+");
    time_t now;
    struct tm *now_time;
    time(&now);
    now_time= localtime(&now);
    fprintf(p,"%d��%d��%d��",1900+now_time->tm_year,1+now_time->tm_mon,now_time->tm_mday);
    rewind(p);
    fgets(result,3000,p);
    fclose(p);
    remove("qwertyuiop.dat");
}

void new_screen()
{
    clear();//������������
    time_t now;
    struct tm *now_time;
    time(&now);
    now_time= localtime(&now);
    printf("*****��ӭʹ��ͼ�����ϵͳ\t\t������");
    printf("%d��%d��%d��  %d��%d��%d��*****\n",1900+now_time->tm_year,1+now_time->tm_mon,now_time->tm_mday,
           now_time->tm_hour,now_time->tm_min,now_time->tm_sec);

}

char *trans_char(int x,char x_trans[1])
{
    FILE *fp_1;
    fp_1=fopen("ca.dat","w+");
    fprintf(fp_1,"%d",x);
    rewind(fp_1);
    fscanf(fp_1,"%s",x_trans);
    fclose(fp_1);
    remove("ca.dat");
    return x_trans;
}

void clear()//��ȡ��ǰ������ϵͳ����ͬ״̬����ϵͳ���Ͳ�ͬ������ָ��
{
#ifdef __MACH__
    system("clear");
#elif WIN32
    system("cls");
#else
    system("clear");
#endif
}
int compare_str(char *s1,char *s2)//�����µıȽ��ַ��������������ַ���һ���򷵻�1
{
    int val=1;
    for(int i=0;s1[i]!='\0'||s2[i]!='\0';i++)
    {
        if (s1[i]!=s2[i])
        {
            val=0;
            break;
        }
    }
    return val;
}
int search_tool(char file_name[],char goal_char[],char output[])
{
    int value=-1;
    FILE *fp_1,*fp_2;
    fp_1= fopen(file_name,"r+");
    fp_2= fopen(file_name,"r+");
    //fp_3= fopen("cache.dat","w+");
    int rows=0;
    char s[10000]="\0";
    strcpy(s,goal_char);
    while(!feof(fp_1))
    {
        char temp[10000]="\0",check[5000]="\0";
        int jud=1;
        fseek(fp_2, ftell(fp_1),0);
        fgets(temp,9999,fp_1);
        rows++;
        while(ftell(fp_2)+1< ftell(fp_1))
        {
            //printf("fp are %ld\t%ld\n", ftell(fp_2), ftell(fp_1));
            fscanf(fp_2,"%s",check);
            if (compare_str(s,check))
            {
                //printf("��%d���ҵ��˺��ʵ���Ϣ\n",rows);
                jud=0;
                value=rows;
                strcpy(output,temp);
                break;
            }
        }//printf("2��ѭ�����\n");
        if (jud)
        {
            //fprintf(fp_3,"%s",temp);
        }
    }
    //printf("���ѭ�����\n");
    fclose(fp_1);
    fclose(fp_2);
    //remove(file_name);
    //fclose(fp_3);
    //rename("cache.dat",file_name);
    return value;
}
void clear_str(char s[])
{
    for (int i=0;s[i]!='\0';i++)
    {
        s[i]='\0';
    }
}
void change(char file_name[],char old_char_non_repeat[],char ctrl_new_char[] )
{
    //int value;
    FILE *fp_1,*fp_2,*fp_3;
    fp_1= fopen(file_name,"r+");
    fp_2= fopen(file_name,"r+");
    fp_3= fopen("cache.dat","w+");
    int rows=0;
    char s[10000]="\0";
    strcpy(s,old_char_non_repeat);
    while(!feof(fp_1))
    {
        char temp[10000]="\0",check[5000]="\0";
        int jud=1;
        fseek(fp_2, ftell(fp_1),0);
        fgets(temp,9999,fp_1);
        rows++;
        while(ftell(fp_2)+1< ftell(fp_1))
        {
            //printf("fp are %ld\t%ld\n", ftell(fp_2), ftell(fp_1));
            fscanf(fp_2,"%s",check);
            if (compare_str(s,check))
            {
                //printf("��%d���ҵ��˺��ʵ���Ϣ\n",rows);
                jud=0;
                //value=rows;
                //fprintf(fp_3,ctrl_new_char,);
                fputs(ctrl_new_char,fp_3);
                break;
            }
        }//printf("2��ѭ�����\n");
        if (jud)
        {
            fprintf(fp_3,"%s",temp);
        }
    }
    //printf("���ѭ�����\n");
    fclose(fp_1);
    fclose(fp_2);
    remove(file_name);
    fclose(fp_3);
    rename("cache.dat",file_name);
    //return value;
}
void login()
{
    new_screen();
    FILE *file_head;

    int login_event=0;//��¼״̬��0ʧ�ܣ�1�ɹ���¼Ϊ�û���2�ɹ���¼Ϊ����Ա
    struct users
    {
        int id;
        char name[30];
        char password[16];
        char right[10];//����Ȩ�ޱ�־
    }
    inputs={.name='\0',.password = '\0',.right='\0'},
    standard={.name='\0',.password='\0',.right='\0'};//�����ݿ��в��ϵĶ�����֤�û�����
    //system("clear");
    file_head=fopen("user.txt","r+");//�ֲ���������user�ļ��׵�ַ
    if (file_head==NULL)
    {
        printf("���ݿ�ͷ�ļ�ָ���ȡ����\n��ѡ�������\n��1����ʼ���û�����\t��2���쳣�˳�");
        menu_bottom_bar();
        int k;
        scanf("%d", &k);
        switch (k) {
            case 1:{
                file_head=fopen("user.txt","w+");
                if(file_head == NULL){
                    printf("���Գ�ʼ��ʧ�ܣ������쳣�˳�...");
                    system("pause");
                } else{
                    struct{
                        char id[10];
                        char name[30];
                        char password[30];
                        char authority[10];
                    }user = {.name = "system", .id = "10001", .password = "10001", .authority = "admin"}, use = {.name = "Name", .id = "ID", .password = "PWD", .authority = "POW"};
                    if((fprintf(file_head,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",use.id,use.name,use.password,use.authority) == EOF) || (fprintf(file_head,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",user.id,user.name,user.password,user.authority)==EOF)) {
                        printf("д����Ϣʧ��!\n");
                        printf("���Գ�ʼ��ʧ�ܣ������쳣�˳�...");
                        system("pause");
                        exit(0);
                    }
                    printf("��ʼ����ɣ���ʹ���˻�10001  ����10001��¼ϵͳ�����µĹ���Ա�˻���");
                    system("pause");
                    fclose(file_head);
                    login();
                }
                break;
            }
            case 2:{
                exit(0);
            }
        }
    }
    char qtmd[300]="\0";
    fgets(qtmd,298,file_head);//ָ�����һ��
    printf("�����������˻���");
    scanf("%s",inputs.name);
    printf("�������������룺");
    scanf("%s",inputs.password);
    //�˴���ʼ��������ַ���ת��Ϊ���ͱ�����ʵ��ѧ�����������¼
    int counter=0,x=0,breaker=0;
    char *k=inputs.name;

    for (int i=0;k[i]!='\0';i++)
    {
        if(k[i]<'0'||k[i]>'9')
        {
            x=0;breaker=1;
            break;
        }
        counter++;
    }
    for (int i=0;(breaker==0)&&(counter>0);counter--,i++)
    {
        x+= ((int)k[i]-48)*pow(10,counter-1);
    }
    inputs.id=x;

    while (!feof(file_head))
    {
        int check_name=1,check_pd=1;//��������˻������ʼֵ
        if (fscanf(file_head, "%d\t\t\t%s\t\t\t%s\t\t\t%s\n",&standard.id,standard.name,
                   standard.password, standard.right) == EOF)
            printf("˳��������ݿ����");
        //else printf("˳��������ݿ�ɹ�");
        for(int i=0;inputs.name[i]!='\0'||standard.name[i]!='\0';i++)
        {
            if (inputs.id==standard.id)break;
            if (inputs.name[i]!=standard.name[i])
            {
                check_name=0;
                break;
            }
        }
        for (int i=0;check_name!=0&&(inputs.password[i]!='\0'||standard.password[i]!='\0');i++)
        {
            if (inputs.password[i]!=standard.password[i])
            {
                check_pd=0;
                break;
            }
        }
        if ((check_name==1)&&(check_pd==1))//ͨ�������״̬
        {
            char *power;
            //*inputs.right=*standard.right;
            strcpy(inputs.right,standard.right);
            //*inputs.name=*standard.name;
            strcpy(inputs.name,standard.name);
            inputs.id=standard.id;
            //if (*standard.right==*"admin")
            if (compare_str(standard.right,"admin"))
            {
                power = "����Ա";
                login_event=2;
            }
            else
            {
                login_event=1;
                power = "�û�";
            }
            //*useragent.name=*inputs.name;//�����¼��ɵ��û�����ȫ�ֱ���
            strcpy(useragent.name,inputs.name);
            strcpy(useragent.password,standard.password);
            useragent.authority=login_event;//�����¼��ɵ�Ȩ�ޱ�ʶ��ȫ�ֱ���
            useragent.id=inputs.id;//�����¼��ɵ��û�id
            new_screen();
            printf("%s:%s(%d),��ӭ����\n",power,standard.name,inputs.id);
            break;
        }
    }
    //while(*standard.name!=*"@end_here");
    if (login_event==0)
    {
        int chosen;//��¼ѡ��
        printf("��������˻�����������\n��1������\t\t\t\t��2���˳�ϵͳ");
        menu_bottom_bar();
        scanf("%d",&chosen);
        if (chosen==1)
        {
            login();
        }
        else exit(0);

    }
    if(fclose(file_head)==EOF) printf("����");
    //return login_event;
}
/*void del_dat(char goal[100],char filename[100])
{
    FILE *pin_1,*pin_2;
    if(NULL==(pin_1 = fopen(filename,"r+"))) printf("��%sʧ�ܣ�\n",filename);
    if(NULL==(pin_2 = fopen("cache.txt","w"))) printf("����cacheʧ�ܣ�\n");
    if(NULL==(pin_2 = fopen("cache.txt","r+"))) printf("��cacheʧ�ܣ�\n");
    while(!feof(pin_1))
    {
        char q[100]={'\0'};
        fscanf(pin_1,"%s\n",q);
        int k=1;
        for (int i=0;goal[i]!='\0'||q[i]!='\0';i++)
        {
            if(goal[i]!=q[i])
            {
                k=0;break;
            }
        }
        if(!k)
        {
            fprintf(pin_2,"%s\n",q);
        }
    }
    if(fclose(pin_1)==EOF) printf("�ر�%sʧ��\n",filename);
    if(!remove(filename)) printf("ɾ��%sʧ��\n",filename);
    if(fclose(pin_2)==EOF) printf("�ر�cacheʧ��\n");
    if(!rename("cache.txt",filename)) printf("������cacheʧ��\n");
}*/
int del_row(char file_name[60],char goal_char[10000])
{
    int value=-1;
    FILE *fp_1,*fp_2,*fp_3;
    fp_1= fopen(file_name,"r+");
    fp_2= fopen(file_name,"r+");
    fp_3= fopen("cache.dat","w+");
    int rows=0;
    char s[10000]="\0";
    strcpy(s,goal_char);
    while(!feof(fp_1))
    {
        char temp[10000]="\0",check[5000]="\0";
        int jud=1;
        fseek(fp_2, ftell(fp_1),0);
        fgets(temp,9999,fp_1);
        rows++;
        while(ftell(fp_2)+1< ftell(fp_1))
        {
            //printf("fp are %ld\t%ld\n", ftell(fp_2), ftell(fp_1));
            fscanf(fp_2,"%s",check);
            if (compare_str(s,check))
            {
                //printf("��%d���ҵ��˺��ʵ���Ϣ\n",rows);
                jud=0;
                value=rows;
                break;
            }
        }//printf("2��ѭ�����\n");
        if (jud)
        {
            fprintf(fp_3,"%s",temp);
        }
    }
    //printf("���ѭ�����\n");
    fclose(fp_1);
    fclose(fp_2);
    remove(file_name);
    fclose(fp_3);
    rename("cache.dat",file_name);
    return value;
}
int trans_int(char *k)
{
    int counter=0,x=0,breaker=0;
    for (int i=0;k[i]!='\0';i++)
    {
        if(k[i]<'0'||k[i]>'9')
        {
            x=0;breaker=1;
            break;
        }
        counter++;
    }
    for (int i=0;(breaker==0)&&(counter>0);counter--,i++)
    {
        x+= ((int)k[i]-48)*pow(10,counter-1);
    }
    return x;
}
void book_search(int attach)
{
    if (!attach) new_screen();
    int find_book=0;char aim_f[30];
    struct search_methods
    {
        char book_name[30];
        char publisher[30];
        char author[10];
        char isbn[15];
        char id[10];
        char user_inf[30];
        char on_shelf[3];//�ڼ����  0�����1�ڼ�
    }book_inf_input={.book_name='\0',.author='\0',.publisher='\0',.isbn='\0',.id=0,.user_inf='\0',.on_shelf=1},
    book_found={.book_name='\0',.author='\0',.publisher='\0',.isbn='\0',.id=0,.user_inf='\0',.on_shelf=1};
    FILE *pin;
    pin= fopen("bookshelf.txt","r+");
    if (pin==NULL)
    {
        printf("��ȡ���ݿ����(error:search bookshelf)\n");
        exit(2);
    }
    rewind(pin);
    int k=0;//out_put_all=0;
    if (useragent.authority==1)//Ȩ�ޱ�ʶΪѧ������ͨ�û�����ʱ��
    {
        printf("ѡ�����Ĳ�ѯ��ʽ��\n��1����������ѯ\t��2������Ų�ѯ\t��3�������߲�ѯ\n"
               "��4�����������ѯ\t��5����ISBN��ѯ\t��6��ֻ���ڼ��鼮");
        menu_bottom_bar();
        scanf("%d",&k);
        switch (k)
        {
            case 1:
            {
                printf("�������ѯ���鼮���ƣ�");
                scanf("%s",book_inf_input.book_name);
                strcpy(aim_f,book_inf_input.book_name);
                break;
            }
            case 2:
            {
                printf("�������ѯ���鼮��ţ�");
                scanf("%s",book_inf_input.id);
                strcpy(aim_f,book_inf_input.id);
                break;
            }
            case 3:
            {
                printf("�������ѯ���鼮���ߣ�");
                scanf("%s",book_inf_input.author);
                strcpy(aim_f,book_inf_input.author);
                break;
            }
            case 4:
            {
                printf("�������ѯ���鼮�ĳ����磺");
                scanf("%s",book_inf_input.publisher);
                strcpy(aim_f,book_inf_input.publisher);
                break;
            }
            case 5:
            {
                printf("�������ѯ���鼮��ISBN��");
                scanf("%s",book_inf_input.isbn);
                strcpy(aim_f,book_inf_input.isbn);
                break;
            }
            case 6:
            {
                //int check=0;
                //printf("��1����ʾ�ڼ��鼮\t\t\t��2����ʾ����鼮\n");
                //scanf("%d",&check);
                //if (check==1) ;
                //if (check==2) book_inf_input.on_shelf[0]='0';
                book_inf_input.on_shelf[0]='1';
                strcpy(aim_f,book_inf_input.on_shelf);
                break;
            }
        }

    }
    if (useragent.authority==2)//Ȩ�ޱ�ʶΪ����Ա��ʱ��
    {
        printf("ѡ�����Ĳ�ѯ��ʽ��\n��1����������ѯ\t\t��2������Ų�ѯ\t\t��3�������߲�ѯ\n"
               "��4�����������ѯ\t\t��5����ISBN��ѯ\t\t��6����������Ա��Ϣ��ѯ\n��7�����ڼ�����ѯ\t\t��8����ʾȫ��");
        menu_bottom_bar();
        scanf("%d",&k);
        switch (k)
        {
            case 1:
            {
                printf("�������ѯ���鼮���ƣ�");
                scanf("%s",book_inf_input.book_name);
                strcpy(aim_f,book_inf_input.book_name);
                break;
            }
            case 2:
            {
                printf("�������ѯ���鼮��ţ�");
                scanf("%s",book_inf_input.id);
                strcpy(aim_f,book_inf_input.id);
                break;
            }
            case 3:
            {
                printf("�������ѯ���鼮���ߣ�");
                scanf("%s",book_inf_input.author);
                strcpy(aim_f,book_inf_input.author);
                break;
            }
            case 4:
            {
                printf("�������ѯ���鼮�ĳ����磺");
                scanf("%s",book_inf_input.publisher);
                strcpy(aim_f,book_inf_input.publisher);
                break;
            }
            case 5:
            {
                printf("�������ѯ���鼮��ISBN��");
                scanf("%s",book_inf_input.isbn);
                strcpy(aim_f,book_inf_input.isbn);
                break;
            }
            case 6:
            {
                printf("���������Ա���������˺ţ�");
                scanf("%s",book_inf_input.user_inf);
                strcpy(aim_f,book_inf_input.user_inf);
                break;
            }
            case 7:
            {
                int check=0;
                printf("��1����ʾ�ڼ��鼮\t\t\t��2����ʾ����鼮\n");
                scanf("%d",&check);
                if (check==1) book_inf_input.on_shelf[0]='1';
                if (check==2) book_inf_input.on_shelf[0]='0';
                strcpy(aim_f,book_inf_input.on_shelf);
                break;
            }
            case 8:
            {
                //out_put_all=1;
                aim_f[0]='1';
            }
        }
    }
    FILE *cache;
//    if(NULL==(cache = fopen("cache.txt","w"))) printf("����cacheʧ�ܣ�\n");
//    if(NULL==(cache = fopen("cache.txt","r+"))) printf("��cacheʧ�ܣ�\n");
    //if(EOF== fprintf(cache,"���\t\t\t\t\t����\t\t\t\t\t����\t\t\t\t\t������\t\t\t\t\tISBN\t\t\t\t\t�Ƿ��ڼ�\n")) printf("д���ͷʧ�ܣ�\n");
    if(NULL==(cache = fopen("cache.txt","w+"))) printf("��cacheʧ�ܣ�\n");
    new_screen();
    printf("��ѯ������£�\n---------------------------------------------------------\n���\t\t\t\t\t����\t\t\t\t\t����\t\t\t\t\t������\t\t\t\t\tISBN\t\t\t\t\t�Ƿ��ڼ�\n");
    while (!feof(pin))
    {
        if (fscanf(pin,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn,book_found.on_shelf)==EOF)
            printf("�Ա�����ʧ�ܣ�error:read data in bookshelf.txt\n");
        if (k!=8)
        {
            if (compare_str(aim_f,book_found.book_name)|| compare_str(aim_f,book_found.author)|| compare_str(aim_f,book_found.publisher)||compare_str(aim_f,book_found.id)||compare_str(aim_f,book_found.isbn)||compare_str(aim_f,book_found.on_shelf))
            {
                //fprintf(cache,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
                printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
//                if (compare_str(book_found.on_shelf,"1")) fprintf(cache,"�ڼ�\n");
//                else fprintf(cache,"���\n");
                if (compare_str(book_found.on_shelf,"1")) printf("�ڼ�\n");
                else printf("���\n");
                find_book++;
            }
        }
        else
        {
            if (compare_str(book_found.on_shelf,"1")|| compare_str(book_found.on_shelf,"0"))
            {
                //fprintf(cache,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
                printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
//                if (compare_str(book_found.on_shelf,"1")) fprintf(cache,"�ڼ�\n");
//                else fprintf(cache,"���\n");
                if (compare_str(book_found.on_shelf,"1")) printf("�ڼ�\n");
                else printf("���\n");
                find_book++;
            }
        }
    }
    //if (k==8) fprintf(cache,"���г� %d ���鼮\n",find_book);
    if (k==8) printf("���г� %d ���鼮\n",find_book);
    else
    {
        if (compare_str(aim_f,"1"))
        {
            //fprintf(cache,"���ҵ�%d�� �ڼ� ���鼮\n",find_book);
            printf("���ҵ�%d�� �ڼ� ���鼮\n",find_book);
        }
        else
        {
            if (compare_str(aim_f,"0"))
            {
                //fprintf(cache,"���ҵ�%d�� �ѽ�� ���鼮\n",find_book);
                printf("���ҵ�%d�� �ѽ�� ���鼮\n",find_book);
            }
            else
            {
                //fprintf(cache,"���ҵ�%d��� %s �йص��鼮\n",find_book,aim_f);
                printf("���ҵ�%d��� %s �йص��鼮\n",find_book,aim_f);
            }
        }
    }
    if(fclose(cache)==EOF) printf("�ر�cacheʧ��");
    remove("cache.txt");
    if (!attach)
    {
        if (useragent.authority==1)
        {
            printf("---------------------------------\n��1���л����ҷ�ʽ\t\t��2���������˵�\n��3������ͼ��\t\t��4���˳�ϵͳ");
            menu_bottom_bar();
            int ki;
            scanf("%d", &ki);
            switch (ki) {
                case 1: {
                    new_screen();
                    book_search(0);
                    break;
                }
                case 2: {
                    new_screen();
                    menu(useragent.authority);
                    break;
                }
                case 3: {
                    borrow_book();
                    break;
                }
                case 4: {
                    exit(0);
                }
            }
        }
        if (useragent.authority==2)
        {
            printf("---------------------------------\n��1���л����ҷ�ʽ\t\t��2���������˵�\t\t��3���˳�ϵͳ\n");
            menu_bottom_bar();
            int ki;
            scanf("%d", &ki);
            switch (ki) {
                case 1: {
                    book_search(0);
                    break;
                }
                case 2: {
                    menu(useragent.authority);
                    break;
                }
                case 3: {
                    exit(0);
                }
            }
        }

    }

}
void append_book()
{
   new_screen();
   struct new_book
   {
       char name[30];
       char author[30];
       char publisher[30];
       char isbn[20];
       int num;
   }book={.name='\0',.author='\0',.isbn='\0',.publisher='\0',.num=1};
    printf("���������鼮��������");
    scanf("%s",book.name);
    printf("���������鼮�ĳ����磺");
    scanf("%s",book.publisher);
    printf("���������鼮�����ߣ�");
    scanf("%s",book.author);
    printf("���������鼮��ISBN��");
    scanf("%s",book.isbn);
    FILE *fp;
    if (NULL==(fp= fopen("bookshelf.txt","r+"))) printf("����error on open bookshelf\n");
    char std_inf[][30]={"\0","\0","\0","\0","\0","\0"},*k=std_inf[0];
    while(!feof(fp))
    if(fscanf(fp,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",std_inf[0],std_inf[1],std_inf[2],
              std_inf[3],std_inf[4],std_inf[5])==EOF) printf("������ܱ�Ŵ���:error:read id\n");
    //printf("��������id�ǣ�%s\n",std_inf[0]);
    int counter=0,x=0,breaker=0,id;
    for (int i=0;k[i]!='\0';i++)
    {
        if(k[i]<'0'||k[i]>'9')
        {
            x=0;breaker=1;
            break;
        }
        counter++;
    }
    for (int i=0;(breaker==0)&&(counter>0);counter--,i++)
    {
        x+= ((int)k[i]-48)*pow(10,counter-1);
    }
    //printf("%d",x);
    id=x+(int)(pow(2.7,sin(x)))+1;
    if(fprintf(fp,"%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%d\n",id,book.name,book.author,book.publisher,
               book.isbn,book.num)==EOF) printf("д����Ϣʧ�ܣ�error:book write in error!\n");
    if (EOF== fclose(fp)) printf("�ر��ļ�ʧ�ܣ�error:close fallen on bookshelf.txt\n");
    printf("д��������Ϣ�ɹ���ϵͳΪ���������Ϊ��%09d\n-----------"
           "-------------------------\nѡ�������ִ�еĲ�����\n��1���˳�ϵͳ\t��2������¼��\t��3���ص����˵�",id);
    menu_bottom_bar();
    int cho=0;
    scanf("%d",&cho);
    switch (cho)
    {
        case 1:
        {
            exit(0);
        }
        case 2:
        {
            append_book();
            break;
        }
        case 3:
        {
            new_screen();
            menu(useragent.authority);
            break;
        }
    }
}
void del_book()
{
    new_screen();
    printf("������ϵͳ�ڶ�Ҫɾ�����鼮��Ϣ���в���!\n");
    book_search(1);
    printf("����Ҫɾ�����鼮�ı�ţ�");
    int k=0;
    char id[15]="\0";
    scanf("%s",id);
    printf("ȷ��Ҫɾ����\n��1��ȷ��\t\t\t��2��ȡ��");
    menu_bottom_bar();
    scanf("%d",&k);
    int chose;
    switch (k)
    {

        case 1:
        {
            //del_dat(id,"bookshelf.txt");
            del_row("bookshelf.txt",id);
            printf("��Ϊ��ɾ�����%d���鼮���������Ĳ�����\n��1���������˵�\t\t��2��ɾ�������鼮\t\t��3���˳�ϵͳ", trans_int(id));
            menu_bottom_bar();
            scanf("%d",&chose);
            switch (chose)
            {
                case 1:
                {
                    menu(useragent.authority);
                    break;
                }
                case 2:
                {
                    del_book();
                    break;
                }
                case 3:
                {
                    exit(0);
                }
            }
            break;
        }
        case 2:
        {
            printf("ȡ��ɾ�������ɹ����������Ĳ�����\n��1���������˵�\t\t��2��ɾ�������鼮\t\t��3���˳�ϵͳ");
            menu_bottom_bar();
            scanf("%d",&chose);
            switch (chose)
            {
                case 1:
                {
                    new_screen();
                    menu(useragent.authority);
                    break;
                }
                case 2:
                {
                    del_book();
                    break;
                }
                case 3:
                {
                    exit(0);
                }
            }
            break;
        }
    }
}
void return_book()
{
    char bow_id[30]="\0",date_now[30]="\0",date_e[30]="\0";
    time_back(date_now);
    printf("������Ҫ�黹�ĵ��鼮�ı�ţ�");
    scanf("%s",bow_id);

    char found_id[15]="\0",found_inf[4500]="\0";
    strcpy(found_id,bow_id);
    struct bow_book_inf
    {
        char id[15];
        char name[30];
        char author[30];
        char publisher[50];
        char isbn[15];
        char on_shelf[3];
    }bk={.id="\0",.name="\0",.author="\0",.publisher="\0",.isbn="\0",.on_shelf="0"};
    int ki=search_tool("bookshelf.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("bookshelf.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    fscanf(fp,"%s",bk.id);
    fscanf(fp,"%s",bk.name);
    fscanf(fp,"%s",bk.author);
    fscanf(fp,"%s",bk.publisher);
    fscanf(fp,"%s",bk.isbn);
    fscanf(fp,"%s",bk.on_shelf);
    fclose(fp);
    if (compare_str(bk.on_shelf,"1"))
    {
        printf("�Բ����Ȿ���ڼܣ�����黹����������ѡ��\n");
        borrow_book();
    }
    //menu_bottom_bar();
    char pas[30]="\0";
    printf("����%s����������֤��ݣ�",useragent.name);
    scanf("%s",pas);
    int chek=0;
    if (!compare_str(pas,useragent.password))
    {
        int i=3;
        for (;i>0;i--)
        {
            printf("�������������%d�λ������ԣ�",i);
            clear_str(pas);
            scanf("%s",pas);
            if (compare_str(pas,useragent.password))
            {
                chek=1;
                break;
            }
        }
    } else chek=1;
    if (chek)
    {
        printf("ȷ��Ҫ�黹��%s����\n��1��ȷ��\t\t��2��ȡ��\n--------------------------\n�밴��ѡ��......",bk.name);
        int qtmn;
        scanf("%d",&qtmn);
        if (qtmn==1)
        {
//            printf("���� ��\\��\\�� �ĸ�ʽ����Ԥ�ڵĹ黹ʱ�䣺");
//            scanf("%s",date_e);
            FILE *p_1,*p_2;
            p_1= fopen("history.dat","r");
            p_2= fopen("history.dat","r");
            int raw_k;
            char temp_2456[2001]="\0",useragent_id[30]="\0",temp_useless_56[300]="\0",temp_rubbish[300]="\0";
            raw_k=search_tool("history.dat",bow_id,temp_useless_56);
            for (int i=1;i<raw_k;i++)
            {
                char temp_useless_654[3000]="\0";
                fgets(temp_useless_654,2999,p_1);
            }
            fseek(p_2, ftell(p_1),0);
            for (int i=1;i<4;i++)
            {
                clear_str(temp_rubbish);
                fscanf(p_2,"%s",temp_rubbish);
            }
            fscanf(p_2,"%s",date_e);
            char atc[500]="\0";
            FILE *sbc;
            sbc= fopen("sybstmd.dat","w+");
            fprintf(sbc,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",bk.id,bk.name,bk.author,bk.publisher,bk.isbn,"1");
            rewind(sbc);
            fgets(atc,4998,sbc);
            fclose(sbc);
            remove("sybstmd.dat");
            //printf("after edit:%s",atc);
            change("bookshelf.txt",bk.id,atc);
            FILE *tee;
            tee= fopen("cache_2456.lib","w+");
            fprintf(tee,"%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",useragent.id,bk.id,"�ѹ黹",date_e,date_now);
            rewind(tee);
            //fscanf(tee,"%s",temp_2456);
            fgets(temp_2456,2000,tee);
            fclose(tee);
            remove("cache_2456.lib");
            trans_char(useragent.id,useragent_id);
            change("history.dat", bk.id,temp_2456);
            fclose(p_1);
            fclose(p_2);
            printf("�ѳɹ��黹�鼮��\n");
        } else
            printf("��ȡ���黹����\n");
        printf("--------------------------------\n��ѡ��������Ĳ�����\n��1����������鼮\t��2���ص����˵�\t��3���˳�ϵͳ");
        menu_bottom_bar();
        int cho;
        scanf("%d",&cho);
        switch (cho)
        {
            case 1:
            {
                new_screen();
                book_search(0);
                break;
            }
            case 2:
            {
                new_screen();
                menu(useragent.authority);
                break;
            }
            case 3:
            {
                exit(0);
            }
        }
    }
    else
    {
        printf("���Ѿ�������������룬��ϵͳǿ���˳���������������ϵϵͳ����Ա��\n");
        exit(0);
    }
}
void borrow_book()
{
    char bow_id[30]="\0",date_now[30]="\0",date_e[30]="\0";
    time_back(date_now);
    printf("������Ҫ���ĵ��鼮�ı�ţ�");
    scanf("%s",bow_id);
    FILE *his;
    his= fopen("history.dat","a+");
    char found_id[15]="\0",found_inf[4500]="\0";
    strcpy(found_id,bow_id);
    struct bow_book_inf
    {
        char id[15];
        char name[30];
        char author[30];
        char publisher[50];
        char isbn[15];
        char on_shelf[3];
    }bk={.id="\0",.name="\0",.author="\0",.publisher="\0",.isbn="\0",.on_shelf="0"};
    int ki=search_tool("bookshelf.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("bookshelf.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    fscanf(fp,"%s",bk.id);
    fscanf(fp,"%s",bk.name);
    fscanf(fp,"%s",bk.author);
    fscanf(fp,"%s",bk.publisher);
    fscanf(fp,"%s",bk.isbn);
    fscanf(fp,"%s",bk.on_shelf);
    fclose(fp);
    if (compare_str(bk.on_shelf,"0"))
    {
        printf("�Բ����Ȿ���Ѿ��������������ѡ��\n");
        borrow_book();
    }
    //menu_bottom_bar();
    char pas[30]="\0";
    printf("����%s����������֤��ݣ�",useragent.name);
    scanf("%s",pas);
    int chek=0;
    if (!compare_str(pas,useragent.password))
    {
        int i=3;
        for (;i>0;i--)
        {
            printf("�������������%d�λ������ԣ�",i);
            clear_str(pas);
            scanf("%s",pas);
            if (compare_str(pas,useragent.password))
            {
                chek=1;
                break;
            }
        }
    } else chek=1;
    if (chek)
    {
        printf("ȷ��Ҫ���ġ�%s����\n��1��ȷ��\t\t��2��ȡ��\n--------------------------\n�밴��ѡ��......",bk.name);
        int qtmn;
        scanf("%d",&qtmn);
        if (qtmn==1)
        {
            printf("���� ��\\��\\�� �ĸ�ʽ����Ԥ�ڵĹ黹ʱ�䣺");
            scanf("%s",date_e);
            char atc[500]="\0";
            FILE *sbc;
            sbc= fopen("sybstmd.dat","w+");
            fprintf(sbc,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",bk.id,bk.name,bk.author,bk.publisher,bk.isbn,"0");
            rewind(sbc);
            fgets(atc,4998,sbc);
            fclose(sbc);
            remove("sybstmd.dat");
            //printf("after edit:%s",atc);
            change("bookshelf.txt",bk.id,atc);
            fprintf(his,"%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",useragent.id,bk.id,"������",date_now,date_e);
            fclose(his);
            printf("�ѳɹ������鼮��\n");
        } else
            printf("��ȡ�����ģ�\n");
        printf("--------------------------------\n��ѡ��������Ĳ�����\n��1����������鼮\t��2���ص����˵�\t��3���˳�ϵͳ");
        menu_bottom_bar();
        int cho;
        scanf("%d",&cho);
        new_screen();
        switch (cho)
        {
            case 1:
            {
                book_search(0);
                break;
            }
            case 2:
            {
                menu(useragent.authority);
                break;
            }
            case 3:
            {
                exit(0);
            }
        }
    }
    else
    {
        printf("���Ѿ�������������룬��ϵͳǿ���˳���������������ϵϵͳ����Ա��\n");
        exit(0);
    }
}
void loan_search()
{
    new_screen();
    FILE *fp,*fp_1;
    fp= fopen("history.dat","r");
    fp_1= fopen("history.dat","r");
    if (useragent.authority==1)
    {
        int counter=0;
        char result[][501]={"\0","\0"};
        while (!feof(fp))
        {
            fseek(fp_1, ftell(fp),0);
            char row_dat[501]="\0",check[161]="\0";
            fgets(row_dat,500,fp);
            fscanf(fp_1,"%s",check);
            if (useragent.id== trans_int(check))
            {
                fscanf(fp_1,"%s",check);
                fscanf(fp_1,"%s",check);//�˴��������Ա�ָ����Զ�ȡ��ͼ��״̬
                if (compare_str("������",check))
                {
                    //printf("�ҵ����˻��д��ڽ���״̬��ͼ����Ϣ��\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("�������˻����ܹ��ҵ���%d��ͼ�鴦�ڽ����У�\n",counter);
        printf("�����˻���\t\t�����鼮���\t\t�Ƿ��ڽ���״̬\t\t���Ŀ�ʼ����\t\t\t\t(Ԥ��)�黹����\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        fclose(fp);
        fclose(fp_1);
        int sel;
        printf("--------------------------\n������ɣ���ѡ��������Ĳ�����\n��1������\t��2���������˵�\t��3���˳�");
        scanf("%d",&sel);
        //new_screen();
        switch (sel)
        {
            case 1:
            {
                return_book();
                break;
            }
            case 2:
            {
                new_screen();
                menu(useragent.authority);
                break;
            }
            case 3:
            {
                exit(0);
            }
        }
    }
    if (useragent.authority==2)
    {
        printf("�����������ѯ���˺ţ�");
        //char ins_id[15]="\0";
        int ins_id;
        scanf("%d",&ins_id);
        int counter=0;
        char result[][501]={"\0","\0"};
        while (!feof(fp))
        {
            fseek(fp_1, ftell(fp),0);
            char row_dat[501]="\0",check[161]="\0";
            fgets(row_dat,500,fp);
            fscanf(fp_1,"%s",check);
            if (ins_id== trans_int(check))
            {
                fscanf(fp_1,"%s",check);
                fscanf(fp_1,"%s",check);//�˴��������Ա�ָ����Զ�ȡ��ͼ��״̬
                if (compare_str("������",check))
                {
                    //printf("�ҵ����˻��д��ڽ���״̬��ͼ����Ϣ��\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("��������ѯ���˻�:%d���ܹ��ҵ���%d��ͼ�鴦�ڽ����У�\n",ins_id,counter);
        printf("����ѯ���˻���\t\t�����鼮���\t\t�Ƿ��ڽ���״̬\t\t���Ŀ�ʼ����\t\t\t\t(Ԥ��)�黹����\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        int sel;
        printf("--------------------------\n������ɣ���ѡ��������Ĳ�����\n��1���������˵�\t��2���˳�");
        scanf("%d",&sel);
        new_screen();
        switch (sel)
        {
            case 1:
            {
                menu(useragent.authority);
                break;
            }
            case 2:
            {
                exit(0);
            }
        }
    }

}
void history()
{
    FILE *fp,*fp_1;
    fp= fopen("history.dat","r");
    fp_1= fopen("history.dat","r");
    if (useragent.authority==1)
    {
        int counter=0;
        char result[][501]={"\0","\0"};
        while (!feof(fp))
        {
            fseek(fp_1, ftell(fp),0);
            char row_dat[501]="\0",check[161]="\0";
            fgets(row_dat,500,fp);
            fscanf(fp_1,"%s",check);
            if (useragent.id== trans_int(check))
            {
                fscanf(fp_1,"%s",check);
                fscanf(fp_1,"%s",check);//�˴��������Ա�ָ����Զ�ȡ��ͼ��״̬
                //if (compare_str("������",check))
                {
                    //printf("�ҵ����˻��д��ڽ���״̬��ͼ����Ϣ��\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("�������˻����ܹ��ҵ���%d��ͼ��Ľ�����ʷ��\n",counter);
        printf("�����˻���\t\t�����鼮���\t\t�Ƿ��ڽ���״̬\t\t���Ŀ�ʼ����\t\t\t\tԤ�ƹ黹����\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        fclose(fp);
        fclose(fp_1);
    }
    if (useragent.authority==2)
    {
        printf("�����������ѯ���˺ţ�");
        //char ins_id[15]="\0";
        int ins_id;
        scanf("%d",&ins_id);
        int counter=0;
        char result[][501]={"\0","\0"};
        while (!feof(fp))
        {
            fseek(fp_1, ftell(fp),0);
            char row_dat[501]="\0",check[161]="\0";
            fgets(row_dat,500,fp);
            fscanf(fp_1,"%s",check);
            if (ins_id== trans_int(check))
            {
                fscanf(fp_1,"%s",check);
                fscanf(fp_1,"%s",check);//�˴��������Ա�ָ����Զ�ȡ��ͼ��״̬
                //if (compare_str("������",check))
                {
                    //printf("�ҵ����˻��д��ڽ���״̬��ͼ����Ϣ��\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("��������ѯ���˻�:%d���ܹ��ҵ���%d��ͼ��Ľ�����ʷ��\n",ins_id,counter);
        printf("����ѯ���˻���\t\t�����鼮���\t\t�Ƿ��ڽ���״̬\t\t���Ŀ�ʼ����\t\t\t\t(Ԥ��)�黹����\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
    }
    int sel;
    printf("--------------------------\n������ɣ���ѡ��������Ĳ�����\n��1���������˵�\t��2���˳�");
    scanf("%d",&sel);
    new_screen();
    switch (sel)
    {
        case 1:
        {
            menu(useragent.authority);
            break;
        }
        case 2:
        {
            exit(0);
        }
    }

}
void append_user()
{
    new_screen();
    struct new_user
    {
        char id[15];
        char name[30];
        char password[30];
        char authority[30];
    }user={.name='\0',.id='\0',.password='\0',.authority='\0'};
    printf("���������û������֣�");
    scanf("%s",user.name);
    printf("���������û���ID��");
    scanf("%s",user.id);
    printf("���������û������룺");
    scanf("%s",user.password);
    printf("���������û���Ȩ�ޣ�");
    scanf("%s",user.authority);
    FILE *fp;
    if (NULL==(fp= fopen("user.txt","a"))) printf("����error on open user list\n");
    if(fprintf(fp,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",user.id,user.name,user.password,user.authority)==EOF) printf("д����Ϣʧ�ܣ�error: new user write in error!\n");
    if (EOF== fclose(fp)) printf("�ر��ļ�ʧ�ܣ�error:close fallen on user.txt\n");
    printf("д�����û���Ϣ�ɹ���\n-----------"
           "-------------------------\nѡ�������ִ�еĲ�����\n��1���˳�ϵͳ\t��2������¼��\t��3���ص����˵�");
    menu_bottom_bar();
    int cho=0;
    scanf("%d",&cho);
    switch (cho)
    {
        case 1:
        {
            exit(0);
        }
        case 2:
        {
            append_user();
            break;
        }
        case 3:
        {
            menu(useragent.authority);
            break;
        }

    }
}
void del_user()
{
    new_screen();
    printf("����Ҫɾ�����û���ţ�");
    int k=0;
    char id[15]="\0";
    scanf("%s",id);
    printf("ȷ��Ҫɾ����\n��1��ȷ��\t\t\t��2��ȡ��");
    menu_bottom_bar();
    scanf("%d",&k);
    int chose;
    switch (k)
    {

        case 1:
        {
            //del_dat(id,"bookshelf.txt");
            del_row("user.txt",id);
            printf("��Ϊ��ɾ�����%d���û����������Ĳ�����\n��1���������˵�\t\t��2������ɾ�������û�\t\t��3���˳�ϵͳ", trans_int(id));
            menu_bottom_bar();
            scanf("%d",&chose);
            switch (chose)
            {
                case 1:
                {
                    menu(useragent.authority);
                    break;
                }
                case 2:
                {
                    del_user();
                    break;
                }
                case 3:
                {
                    exit(0);
                }
            }
            break;
        }
        case 2:
        {
            printf("ȡ��ɾ�������ɹ����������Ĳ�����\n��1���������˵�\t\t��2��ɾ�������鼮\t\t��3���˳�ϵͳ");
            menu_bottom_bar();
            scanf("%d",&chose);
            switch (chose)
            {
                case 1:
                {
                    menu(useragent.authority);
                    break;
                }
                case 2:
                {
                    del_book();
                    break;
                }
                case 3:
                {
                    exit(0);
                }
            }
            break;
        }
    }
}
void change_book()
{
    char found_id[15]="\0",found_inf[4500]="\0";
    struct book_inf
    {
        char id[15];
        char name[30];
        char author[30];
        char publisher[50];
        char isbn[15];
        char on_shelf[3];

    }bk={.id="\0",.name="\0",.author="\0",.publisher="\0",.isbn="\0",.on_shelf="\0"};
    new_screen();
    printf("���ȶ���Ҫ���ĵ��鼮���в��ң�");
    book_search(1);
    printf("����Ҫ�޸ĵ��鼮��ţ�");
    scanf("%s",found_id);
    int ki=search_tool("bookshelf.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("bookshelf.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    printf("ѡ����Ҫ�޸ĵ���Ϣ��\n��1���鼮����\t\t��2��������\n��3����������\t\t��4��ISBN");
    int chose;
    menu_bottom_bar();
    scanf("%d",&chose);
    switch (chose)
    {
        case 1:
        {

            fscanf(fp,"%s",bk.id);
            fscanf(fp,"%s",bk.name);
            clear_str(bk.name);
            printf("�����µ�������");
            scanf("%s",bk.name);
            fscanf(fp,"%s",bk.author);
            fscanf(fp,"%s",bk.publisher);
            fscanf(fp,"%s",bk.isbn);
            fscanf(fp,"%s",bk.on_shelf);
            fclose(fp);
            break;
        }
        case 2:
        {

            fscanf(fp,"%s",bk.id);
            fscanf(fp,"%s",bk.name);
            fscanf(fp,"%s",bk.author);
            clear_str(bk.author);
            printf("�����µ���������");
            scanf("%s",bk.author);
            fscanf(fp,"%s",bk.publisher);
            fscanf(fp,"%s",bk.isbn);
            fscanf(fp,"%s",bk.on_shelf);
            fclose(fp);
            break;
        }
        case 3:
        {

            fscanf(fp,"%s",bk.id);
            fscanf(fp,"%s",bk.name);
            fscanf(fp,"%s",bk.author);
            fscanf(fp,"%s",bk.publisher);
            clear_str(bk.publisher);
            printf("�����µĳ���������");
            scanf("%s",bk.publisher);
            fscanf(fp,"%s",bk.isbn);
            fscanf(fp,"%s",bk.on_shelf);
            fclose(fp);
            break;
        }
        case 4:
        {

            fscanf(fp,"%s",bk.id);
            fscanf(fp,"%s",bk.name);
            fscanf(fp,"%s",bk.author);
            fscanf(fp,"%s",bk.publisher);
            fscanf(fp,"%s",bk.isbn);
            clear_str(bk.isbn);
            printf("�����µ�ISBN��");
            scanf("%s",bk.isbn);
            fscanf(fp,"%s",bk.on_shelf);
            fclose(fp);
            break;
        }
    }
    printf("ȷ��Ҫ�޸���\n��1��ȷ��\t\t��2��ȡ��");
    menu_bottom_bar();
    int qtmn;
    scanf("%d",&qtmn);
    if (qtmn==1)
    {
        char atc[5000]="\0";
        FILE *sbc;
        sbc= fopen("sybstmd.dat","w+");
        fprintf(sbc,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",bk.id,bk.name,bk.author,bk.publisher,bk.isbn,bk.on_shelf);
        rewind(sbc);
        fgets(atc,4998,sbc);
        fclose(sbc);
        remove("sybstmd.dat");
        //printf("after edit:%s",atc);
        change("bookshelf.txt",bk.id,atc);
        printf("�ѱ�����ģ�\n");
    } else
        printf("��ȡ��������\n");
    printf("--------------------------------\n��ѡ��������Ĳ�����\n��1�������������鼮��Ϣ\t��2���ص����˵�\t��3���˳�ϵͳ");
    menu_bottom_bar();
    int cho;
    scanf("%d",&cho);
    switch (cho)
    {
        case 1:
        {
            change_book();
            break;
        }
        case 2:
        {
            menu(useragent.authority);
            break;
        }
        case 3:
        {
            exit(0);
        }
    }

}
void change_user()
{
    char found_id[15]="\0",found_inf[4500]="\0";
    struct book_inf
    {
        char id[15];
        char name[30];
        char password[30];
        char authority[20];
    }uer={.id="\0",.name="\0",.authority="\0",.password="\0"};
    new_screen();
//    printf("���ȶ���Ҫ���ĵ��鼮���в��ң�");
//    book_search(1);
    FILE *ttt;
    ttt= fopen("user.txt","r");
    int all_u=0;
    printf("����ϵͳ��ע����û�������Ϣ:\n");
    while (!feof(ttt))
    {
        char read_l[4999]="\0";
        fgets(read_l,4998,ttt);
        if (all_u>0) printf("%s",read_l);
        all_u++;
    }
    printf("�� %d ���û�\n",all_u-2);
    printf("����Ҫ�޸ĵ��û���ţ�");
    scanf("%s",found_id);
    int ki=search_tool("user.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("user.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    printf("ѡ����Ҫ�޸ĵ���Ϣ��\n��1���û�����\t\t��2���û�����\t\t��3���û�Ȩ��\n");
    int chose;
    menu_bottom_bar();
    scanf("%d",&chose);
    switch (chose)
    {
        case 1:
        {
            fscanf(fp,"%s",uer.id);
            fscanf(fp,"%s",uer.name);
            clear_str(uer.name);
            printf("�����µ��û�����");
            scanf("%s",uer.name);
            fscanf(fp,"%s",uer.password);
            fscanf(fp,"%s",uer.authority);
            fclose(fp);
            break;
        }
        case 2:
        {
            fscanf(fp,"%s",uer.id);
            fscanf(fp,"%s",uer.name);
            fscanf(fp,"%s",uer.password);
            clear_str(uer.password);
            printf("�����µ��û����룺");
            scanf("%s",uer.password);
            fscanf(fp,"%s",uer.authority);
            fclose(fp);
            break;
        }
        case 3:
        {
            fscanf(fp,"%s",uer.id);
            fscanf(fp,"%s",uer.name);
            fscanf(fp,"%s",uer.password);
            fscanf(fp,"%s",uer.authority);
            clear_str(uer.authority);
            printf("�����µ��û�Ȩ�ޣ�\n��user����ͨ�û�\t��admin��ϵͳ����Ա\n");
            menu_bottom_bar();
            scanf("%s",uer.authority);
            fclose(fp);
            break;
        }
    }
    printf("ȷ��Ҫ�޸���\n��1��ȷ��\t\t��2��ȡ��");
    menu_bottom_bar();
    int qtmn;
    scanf("%d",&qtmn);
    if (qtmn==1)
    {
        char atc[5000]="\0";
        FILE *sbc;
        sbc= fopen("sybstmdu.dat","w+");
        fprintf(sbc,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",uer.id,uer.name,uer.password,uer.authority);
        rewind(sbc);
        fgets(atc,4998,sbc);
        fclose(sbc);
        remove("sybstmdu.dat");
        //printf("after edit:%s",atc);
        change("user.txt",uer.id,atc);
        printf("�ѱ�����ģ�\n");
    } else
        printf("��ȡ��������\n");
    printf("--------------------------------\n��ѡ��������Ĳ�����\n��1�������������û���Ϣ\t��2���ص����˵�\t��3���˳�ϵͳ");
    menu_bottom_bar();
    int cho;
    scanf("%d",&cho);
    switch (cho)
    {
        case 1:
        {
            change_user();
            break;
        }
        case 2:
        {
            menu(useragent.authority);
            break;
        }
        case 3:
        {
            exit(0);
        }
    }

}
void menu(int user_type)
{
    int select;
    if (user_type==1)
    {
        printf("��1���鼮��ѯ\t\t��2���軹��ѯ\t\t��3�����ļ�¼");
        menu_bottom_bar();
        scanf("%d",&select);
        getchar();
        switch (select)
        {
            case 1:
            {
                book_search(0);break;
            }
            case 2:
            {
                loan_search();break;
            }
            case 3:
            {
                history();break;
            }
        }

    }
    if (user_type==2)
    {
        printf("��1���ݲ��鼮��ѯ\t��2��ѧ���軹��ѯ\t��3��ѧ�����ļ�¼\n"
               "��4��ѧ���˻�ע��\t��5��ѧ���˻�ɾ��\t��6��ѧ���˻��޸�\n"
               "��7���ݲ�ͼ��¼��\t��8���ݲ�ͼ��ɾ��\t��9���ݲ�ͼ���޸�");
        menu_bottom_bar();
        scanf("%d",&select);
        switch (select)
        {
            case 1:
            {
                book_search(0);
                break;
            }
            case 2:
            {
                loan_search();break;
            }
            case 3:
            {
                history();break;
            }
            case 7:
            {
                append_book();break;
            }
            case 8:
            {
                del_book();break;
            }
            case 4:
            {
                append_user();break;
            }
            case 5:
            {
                del_user();
                break;
            }
            case 9:
            {
                change_book();
                break;
            }
            case 6:
            {
                change_user();
                break;
            }
        }
    }
}