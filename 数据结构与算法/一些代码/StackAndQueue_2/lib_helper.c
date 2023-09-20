/*  图书管理系统
    1、需要实现的功能
        （1）、管理员：增删添改、查借还、查逾期
        （2）、用户：查借还、查期限
    2、具体实现
        （1）、管理员
            a、增删添改：依赖于查找功能，找到数据的位置进行相关的操作；写入的数据有：
               书名、出版社、ISBN（此三者归纳为书籍信息，其中书籍编号ID由系统依照函数生成
            b、查借还：针对某一个学号（姓名）、某一册书籍的在籍情况进行查询
            c、查逾期：查找某一本书的借还日期
            e、新建、修改、删除用户
        （2）、用户
            a、查询某本书是否在架；由一查多：由书籍信息任意条件查询到其他的信息
            b、查询自己的借阅截止时间和借阅记录
            c、查询借阅书籍的预期归还时间
    3、程序结构
        （1）、数据存储结构
            a、user.txt          存储用户信息文件
            b、bookshelf.txt     存储图书信息文件
            c、history.dat       图书借阅状态文件
        （2）、出现的数据结构
            a、变量：整型、字符型、结构体变量
            b、指针：文件指针变量、数组指针变量
        （3）、主程序结构
            a、main              程序开始的地方,包含了对各个功能的调用以及循环的控制
            b、search_tool       从输入的信息中检索输入的库文件中与之匹配的内容，返回该位置行数
            c、append_book       查询bookshelf数据库，由用户（管理员权限）选择并增加
            d、append_user       查询user数据库，由用户（管理员权限）选择并删除
            e、change            输入数据库名以及需要更改的内容、修改后的内容进行修改
            f、login             由main函数最先调用并确定出用户的权限，给出相应的功能菜单
            g、menu              根据全局变量存储的用户权限给出不同的菜单和函数调用关系
            h、del_book          删除书籍
            i、del_user          删除用户账户
            j、其余的功能辅助函数     中文字符串比对、char与int互相转换、自动清屏函数、菜单栏提示函数、行删除函数......
*/
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "string.h"


int debug_mode=0;//debug专用变量，0为非debug，1为模拟用户debug，2为管理员debug


struct useragent_inf
{
    int id;
    int authority;
    char name[30];
    char password[30];
}useragent={.authority=0,.name="\0",.password="\0"};//在全局变量中存储成功登录的用户名，便于功能函数的访问
void append_book();
void del_book();
int search_tool(char *,char *,char *);
void change(char *,char *,char *);
void login();
void book_search(int);
void history();
void menu_bottom_bar();
void new_screen();//新窗口打开函数
void clear();//自适应清屏函数
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
        printf("【1】登录\t\t\t\t【2】退出");
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
    printf("\n_____________________________________\n请按数字键选择您将要执行的操作:");
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
    fprintf(p,"%d年%d月%d日",1900+now_time->tm_year,1+now_time->tm_mon,now_time->tm_mday);
    rewind(p);
    fgets(result,3000,p);
    fclose(p);
    remove("qwertyuiop.dat");
}

void new_screen()
{
    clear();//调用清屏函数
    time_t now;
    struct tm *now_time;
    time(&now);
    now_time= localtime(&now);
    printf("*****欢迎使用图书管理系统\t\t现在是");
    printf("%d年%d月%d日  %d点%d分%d秒*****\n",1900+now_time->tm_year,1+now_time->tm_mon,now_time->tm_mday,
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

void clear()//读取当前的运行系统，不同状态下向系统发送不同的清屏指令
{
#ifdef __MACH__
    system("clear");
#elif WIN32
    system("cls");
#else
    system("clear");
#endif
}
int compare_str(char *s1,char *s2)//构造新的比较字符串函数，两个字符串一样则返回1
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
                //printf("在%d行找到了合适的信息\n",rows);
                jud=0;
                value=rows;
                strcpy(output,temp);
                break;
            }
        }//printf("2层循环完成\n");
        if (jud)
        {
            //fprintf(fp_3,"%s",temp);
        }
    }
    //printf("外层循环完成\n");
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
                //printf("在%d行找到了合适的信息\n",rows);
                jud=0;
                //value=rows;
                //fprintf(fp_3,ctrl_new_char,);
                fputs(ctrl_new_char,fp_3);
                break;
            }
        }//printf("2层循环完成\n");
        if (jud)
        {
            fprintf(fp_3,"%s",temp);
        }
    }
    //printf("外层循环完成\n");
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

    int login_event=0;//登录状态，0失败，1成功登录为用户，2成功登录为管理员
    struct users
    {
        int id;
        char name[30];
        char password[16];
        char right[10];//存入权限标志
    }
    inputs={.name='\0',.password = '\0',.right='\0'},
    standard={.name='\0',.password='\0',.right='\0'};//从数据库中不断的读入验证用户输入
    //system("clear");
    file_head=fopen("user.txt","r+");//局部变量存入user文件首地址
    if (file_head==NULL)
    {
        printf("数据库头文件指针读取错误！\n请选择操作：\n【1】初始化用户配置\t【2】异常退出");
        menu_bottom_bar();
        int k;
        scanf("%d", &k);
        switch (k) {
            case 1:{
                file_head=fopen("user.txt","w+");
                if(file_head == NULL){
                    printf("尝试初始化失败！程序异常退出...");
                    system("pause");
                } else{
                    struct{
                        char id[10];
                        char name[30];
                        char password[30];
                        char authority[10];
                    }user = {.name = "system", .id = "10001", .password = "10001", .authority = "admin"}, use = {.name = "Name", .id = "ID", .password = "PWD", .authority = "POW"};
                    if((fprintf(file_head,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",use.id,use.name,use.password,use.authority) == EOF) || (fprintf(file_head,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",user.id,user.name,user.password,user.authority)==EOF)) {
                        printf("写入信息失败!\n");
                        printf("尝试初始化失败！程序异常退出...");
                        system("pause");
                        exit(0);
                    }
                    printf("初始化完成！请使用账户10001  密码10001登录系统创建新的管理员账户！");
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
    fgets(qtmd,298,file_head);//指针后移一行
    printf("请输入您的账户：");
    scanf("%s",inputs.name);
    printf("请输入您的密码：");
    scanf("%s",inputs.password);
    //此处开始将输入的字符串转换为整型变量以实现学号姓名混输登录
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
        int check_name=1,check_pd=1;//检查输入账户密码初始值
        if (fscanf(file_head, "%d\t\t\t%s\t\t\t%s\t\t\t%s\n",&standard.id,standard.name,
                   standard.password, standard.right) == EOF)
            printf("顺序查找数据库错误！");
        //else printf("顺序查找数据库成功");
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
        if ((check_name==1)&&(check_pd==1))//通过检验的状态
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
                power = "管理员";
                login_event=2;
            }
            else
            {
                login_event=1;
                power = "用户";
            }
            //*useragent.name=*inputs.name;//存入登录完成的用户名到全局变量
            strcpy(useragent.name,inputs.name);
            strcpy(useragent.password,standard.password);
            useragent.authority=login_event;//存入登录完成的权限标识到全局变量
            useragent.id=inputs.id;//存入登录完成的用户id
            new_screen();
            printf("%s:%s(%d),欢迎您！\n",power,standard.name,inputs.id);
            break;
        }
    }
    //while(*standard.name!=*"@end_here");
    if (login_event==0)
    {
        int chosen;//记录选择
        printf("您输入的账户或密码有误！\n【1】重试\t\t\t\t【2】退出系统");
        menu_bottom_bar();
        scanf("%d",&chosen);
        if (chosen==1)
        {
            login();
        }
        else exit(0);

    }
    if(fclose(file_head)==EOF) printf("错误！");
    //return login_event;
}
/*void del_dat(char goal[100],char filename[100])
{
    FILE *pin_1,*pin_2;
    if(NULL==(pin_1 = fopen(filename,"r+"))) printf("打开%s失败！\n",filename);
    if(NULL==(pin_2 = fopen("cache.txt","w"))) printf("建立cache失败！\n");
    if(NULL==(pin_2 = fopen("cache.txt","r+"))) printf("打开cache失败！\n");
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
    if(fclose(pin_1)==EOF) printf("关闭%s失败\n",filename);
    if(!remove(filename)) printf("删除%s失败\n",filename);
    if(fclose(pin_2)==EOF) printf("关闭cache失败\n");
    if(!rename("cache.txt",filename)) printf("重命名cache失败\n");
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
                //printf("在%d行找到了合适的信息\n",rows);
                jud=0;
                value=rows;
                break;
            }
        }//printf("2层循环完成\n");
        if (jud)
        {
            fprintf(fp_3,"%s",temp);
        }
    }
    //printf("外层循环完成\n");
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
        char on_shelf[3];//在架情况  0借出，1在架
    }book_inf_input={.book_name='\0',.author='\0',.publisher='\0',.isbn='\0',.id=0,.user_inf='\0',.on_shelf=1},
    book_found={.book_name='\0',.author='\0',.publisher='\0',.isbn='\0',.id=0,.user_inf='\0',.on_shelf=1};
    FILE *pin;
    pin= fopen("bookshelf.txt","r+");
    if (pin==NULL)
    {
        printf("读取数据库错误！(error:search bookshelf)\n");
        exit(2);
    }
    rewind(pin);
    int k=0;//out_put_all=0;
    if (useragent.authority==1)//权限标识为学生（普通用户）的时候
    {
        printf("选择您的查询方式：\n【1】按书名查询\t【2】按编号查询\t【3】按作者查询\n"
               "【4】按出版社查询\t【5】按ISBN查询\t【6】只看在架书籍");
        menu_bottom_bar();
        scanf("%d",&k);
        switch (k)
        {
            case 1:
            {
                printf("请输入查询的书籍名称：");
                scanf("%s",book_inf_input.book_name);
                strcpy(aim_f,book_inf_input.book_name);
                break;
            }
            case 2:
            {
                printf("请输入查询的书籍编号：");
                scanf("%s",book_inf_input.id);
                strcpy(aim_f,book_inf_input.id);
                break;
            }
            case 3:
            {
                printf("请输入查询的书籍作者：");
                scanf("%s",book_inf_input.author);
                strcpy(aim_f,book_inf_input.author);
                break;
            }
            case 4:
            {
                printf("请输入查询的书籍的出版社：");
                scanf("%s",book_inf_input.publisher);
                strcpy(aim_f,book_inf_input.publisher);
                break;
            }
            case 5:
            {
                printf("请输入查询的书籍的ISBN：");
                scanf("%s",book_inf_input.isbn);
                strcpy(aim_f,book_inf_input.isbn);
                break;
            }
            case 6:
            {
                //int check=0;
                //printf("【1】显示在架书籍\t\t\t【2】显示借出书籍\n");
                //scanf("%d",&check);
                //if (check==1) ;
                //if (check==2) book_inf_input.on_shelf[0]='0';
                book_inf_input.on_shelf[0]='1';
                strcpy(aim_f,book_inf_input.on_shelf);
                break;
            }
        }

    }
    if (useragent.authority==2)//权限标识为管理员的时候
    {
        printf("选择您的查询方式：\n【1】按书名查询\t\t【2】按编号查询\t\t【3】按作者查询\n"
               "【4】按出版社查询\t\t【5】按ISBN查询\t\t【6】按借阅人员信息查询\n【7】按在架与否查询\t\t【8】显示全部");
        menu_bottom_bar();
        scanf("%d",&k);
        switch (k)
        {
            case 1:
            {
                printf("请输入查询的书籍名称：");
                scanf("%s",book_inf_input.book_name);
                strcpy(aim_f,book_inf_input.book_name);
                break;
            }
            case 2:
            {
                printf("请输入查询的书籍编号：");
                scanf("%s",book_inf_input.id);
                strcpy(aim_f,book_inf_input.id);
                break;
            }
            case 3:
            {
                printf("请输入查询的书籍作者：");
                scanf("%s",book_inf_input.author);
                strcpy(aim_f,book_inf_input.author);
                break;
            }
            case 4:
            {
                printf("请输入查询的书籍的出版社：");
                scanf("%s",book_inf_input.publisher);
                strcpy(aim_f,book_inf_input.publisher);
                break;
            }
            case 5:
            {
                printf("请输入查询的书籍的ISBN：");
                scanf("%s",book_inf_input.isbn);
                strcpy(aim_f,book_inf_input.isbn);
                break;
            }
            case 6:
            {
                printf("输入借阅人员的姓名或账号：");
                scanf("%s",book_inf_input.user_inf);
                strcpy(aim_f,book_inf_input.user_inf);
                break;
            }
            case 7:
            {
                int check=0;
                printf("【1】显示在架书籍\t\t\t【2】显示借出书籍\n");
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
//    if(NULL==(cache = fopen("cache.txt","w"))) printf("建立cache失败！\n");
//    if(NULL==(cache = fopen("cache.txt","r+"))) printf("打开cache失败！\n");
    //if(EOF== fprintf(cache,"编号\t\t\t\t\t书名\t\t\t\t\t作者\t\t\t\t\t出版社\t\t\t\t\tISBN\t\t\t\t\t是否在架\n")) printf("写入表头失败！\n");
    if(NULL==(cache = fopen("cache.txt","w+"))) printf("打开cache失败！\n");
    new_screen();
    printf("查询结果如下：\n---------------------------------------------------------\n编号\t\t\t\t\t书名\t\t\t\t\t作者\t\t\t\t\t出版社\t\t\t\t\tISBN\t\t\t\t\t是否在架\n");
    while (!feof(pin))
    {
        if (fscanf(pin,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn,book_found.on_shelf)==EOF)
            printf("对比数据失败！error:read data in bookshelf.txt\n");
        if (k!=8)
        {
            if (compare_str(aim_f,book_found.book_name)|| compare_str(aim_f,book_found.author)|| compare_str(aim_f,book_found.publisher)||compare_str(aim_f,book_found.id)||compare_str(aim_f,book_found.isbn)||compare_str(aim_f,book_found.on_shelf))
            {
                //fprintf(cache,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
                printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
//                if (compare_str(book_found.on_shelf,"1")) fprintf(cache,"在架\n");
//                else fprintf(cache,"借出\n");
                if (compare_str(book_found.on_shelf,"1")) printf("在架\n");
                else printf("借出\n");
                find_book++;
            }
        }
        else
        {
            if (compare_str(book_found.on_shelf,"1")|| compare_str(book_found.on_shelf,"0"))
            {
                //fprintf(cache,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
                printf("%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t",book_found.id,book_found.book_name,book_found.author,book_found.publisher,book_found.isbn);
//                if (compare_str(book_found.on_shelf,"1")) fprintf(cache,"在架\n");
//                else fprintf(cache,"借出\n");
                if (compare_str(book_found.on_shelf,"1")) printf("在架\n");
                else printf("借出\n");
                find_book++;
            }
        }
    }
    //if (k==8) fprintf(cache,"共列出 %d 本书籍\n",find_book);
    if (k==8) printf("共列出 %d 本书籍\n",find_book);
    else
    {
        if (compare_str(aim_f,"1"))
        {
            //fprintf(cache,"共找到%d册 在架 的书籍\n",find_book);
            printf("共找到%d册 在架 的书籍\n",find_book);
        }
        else
        {
            if (compare_str(aim_f,"0"))
            {
                //fprintf(cache,"共找到%d册 已借出 的书籍\n",find_book);
                printf("共找到%d册 已借出 的书籍\n",find_book);
            }
            else
            {
                //fprintf(cache,"共找到%d册和 %s 有关的书籍\n",find_book,aim_f);
                printf("共找到%d册和 %s 有关的书籍\n",find_book,aim_f);
            }
        }
    }
    if(fclose(cache)==EOF) printf("关闭cache失败");
    remove("cache.txt");
    if (!attach)
    {
        if (useragent.authority==1)
        {
            printf("---------------------------------\n【1】切换查找方式\t\t【2】返回主菜单\n【3】借阅图书\t\t【4】退出系统");
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
            printf("---------------------------------\n【1】切换查找方式\t\t【2】返回主菜单\t\t【3】退出系统\n");
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
    printf("输入新增书籍的书名：");
    scanf("%s",book.name);
    printf("输入新增书籍的出版社：");
    scanf("%s",book.publisher);
    printf("输入新增书籍的作者：");
    scanf("%s",book.author);
    printf("输入新增书籍的ISBN：");
    scanf("%s",book.isbn);
    FILE *fp;
    if (NULL==(fp= fopen("bookshelf.txt","r+"))) printf("错误：error on open bookshelf\n");
    char std_inf[][30]={"\0","\0","\0","\0","\0","\0"},*k=std_inf[0];
    while(!feof(fp))
    if(fscanf(fp,"%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",std_inf[0],std_inf[1],std_inf[2],
              std_inf[3],std_inf[4],std_inf[5])==EOF) printf("检验书架编号错误:error:read id\n");
    //printf("读出来的id是：%s\n",std_inf[0]);
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
               book.isbn,book.num)==EOF) printf("写入信息失败：error:book write in error!\n");
    if (EOF== fclose(fp)) printf("关闭文件失败！error:close fallen on bookshelf.txt\n");
    printf("写入新书信息成功！系统为该书分配编号为：%09d\n-----------"
           "-------------------------\n选择接下来执行的操作：\n【1】退出系统\t【2】继续录入\t【3】回到主菜单",id);
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
    printf("请先在系统内对要删除的书籍信息进行查找!\n");
    book_search(1);
    printf("输入要删除的书籍的编号：");
    int k=0;
    char id[15]="\0";
    scanf("%s",id);
    printf("确定要删除吗？\n【1】确定\t\t\t【2】取消");
    menu_bottom_bar();
    scanf("%d",&k);
    int chose;
    switch (k)
    {

        case 1:
        {
            //del_dat(id,"bookshelf.txt");
            del_row("bookshelf.txt",id);
            printf("已为您删除编号%d的书籍！接下来的操作：\n【1】返回主菜单\t\t【2】删除其他书籍\t\t【3】退出系统", trans_int(id));
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
            printf("取消删除操作成功！接下来的操作：\n【1】返回主菜单\t\t【2】删除其他书籍\t\t【3】退出系统");
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
    printf("输入您要归还的的书籍的编号：");
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
        printf("对不起！这本书在架，无需归还，请您重新选择！\n");
        borrow_book();
    }
    //menu_bottom_bar();
    char pas[30]="\0";
    printf("输入%s的密码以验证身份：",useragent.name);
    scanf("%s",pas);
    int chek=0;
    if (!compare_str(pas,useragent.password))
    {
        int i=3;
        for (;i>0;i--)
        {
            printf("输入错误，您还有%d次机会重试：",i);
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
        printf("确定要归还《%s》吗？\n【1】确定\t\t【2】取消\n--------------------------\n请按键选择......",bk.name);
        int qtmn;
        scanf("%d",&qtmn);
        if (qtmn==1)
        {
//            printf("请以 年\\月\\日 的格式输入预期的归还时间：");
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
            fprintf(tee,"%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",useragent.id,bk.id,"已归还",date_e,date_now);
            rewind(tee);
            //fscanf(tee,"%s",temp_2456);
            fgets(temp_2456,2000,tee);
            fclose(tee);
            remove("cache_2456.lib");
            trans_char(useragent.id,useragent_id);
            change("history.dat", bk.id,temp_2456);
            fclose(p_1);
            fclose(p_2);
            printf("已成功归还书籍！\n");
        } else
            printf("已取消归还程序！\n");
        printf("--------------------------------\n请选择接下来的操作：\n【1】浏览其他书籍\t【2】回到主菜单\t【3】退出系统");
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
        printf("您已经输错了三次密码，被系统强制退出！忘记密码请联系系统管理员！\n");
        exit(0);
    }
}
void borrow_book()
{
    char bow_id[30]="\0",date_now[30]="\0",date_e[30]="\0";
    time_back(date_now);
    printf("输入您要借阅的书籍的编号：");
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
        printf("对不起！这本书已经借出，请您重新选择！\n");
        borrow_book();
    }
    //menu_bottom_bar();
    char pas[30]="\0";
    printf("输入%s的密码以验证身份：",useragent.name);
    scanf("%s",pas);
    int chek=0;
    if (!compare_str(pas,useragent.password))
    {
        int i=3;
        for (;i>0;i--)
        {
            printf("输入错误，您还有%d次机会重试：",i);
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
        printf("确定要借阅《%s》吗？\n【1】确定\t\t【2】取消\n--------------------------\n请按键选择......",bk.name);
        int qtmn;
        scanf("%d",&qtmn);
        if (qtmn==1)
        {
            printf("请以 年\\月\\日 的格式输入预期的归还时间：");
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
            fprintf(his,"%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%s\n",useragent.id,bk.id,"借阅中",date_now,date_e);
            fclose(his);
            printf("已成功借阅书籍！\n");
        } else
            printf("已取消借阅！\n");
        printf("--------------------------------\n请选择接下来的操作：\n【1】浏览其他书籍\t【2】回到主菜单\t【3】退出系统");
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
        printf("您已经输错了三次密码，被系统强制退出！忘记密码请联系系统管理员！\n");
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
                fscanf(fp_1,"%s",check);//此处做两次以便指针可以读取到图书状态
                if (compare_str("借阅中",check))
                {
                    //printf("找到您账户中处于借阅状态的图书信息：\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("在您的账户中总共找到了%d本图书处于借阅中：\n",counter);
        printf("您的账户名\t\t借阅书籍编号\t\t是否处于借阅状态\t\t借阅开始日期\t\t\t\t(预计)归还日期\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        fclose(fp);
        fclose(fp_1);
        int sel;
        printf("--------------------------\n检索完成！请选择接下来的操作：\n【1】还书\t【2】返回主菜单\t【3】退出");
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
        printf("输入您打算查询的账号：");
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
                fscanf(fp_1,"%s",check);//此处做两次以便指针可以读取到图书状态
                if (compare_str("借阅中",check))
                {
                    //printf("找到您账户中处于借阅状态的图书信息：\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("在您所查询的账户:%d中总共找到了%d本图书处于借阅中：\n",ins_id,counter);
        printf("您查询的账户名\t\t借阅书籍编号\t\t是否处于借阅状态\t\t借阅开始日期\t\t\t\t(预计)归还日期\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        int sel;
        printf("--------------------------\n检索完成！请选择接下来的操作：\n【1】返回主菜单\t【2】退出");
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
                fscanf(fp_1,"%s",check);//此处做两次以便指针可以读取到图书状态
                //if (compare_str("借阅中",check))
                {
                    //printf("找到您账户中处于借阅状态的图书信息：\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("在您的账户中总共找到了%d本图书的借阅历史：\n",counter);
        printf("您的账户名\t\t借阅书籍编号\t\t是否处于借阅状态\t\t借阅开始日期\t\t\t\t预计归还日期\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
        fclose(fp);
        fclose(fp_1);
    }
    if (useragent.authority==2)
    {
        printf("输入您打算查询的账号：");
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
                fscanf(fp_1,"%s",check);//此处做两次以便指针可以读取到图书状态
                //if (compare_str("借阅中",check))
                {
                    //printf("找到您账户中处于借阅状态的图书信息：\n")
                    //printf("%s",row_dat);
                    strcpy(result[counter],row_dat);
                    counter++;
                }
            }
        }
        printf("在您所查询的账户:%d中总共找到了%d本图书的借阅历史：\n",ins_id,counter);
        printf("您查询的账户名\t\t借阅书籍编号\t\t是否处于借阅状态\t\t借阅开始日期\t\t\t\t(预计)归还日期\n");
        for (int i=0;i<counter;i++)
        {
            printf("%s",result[i]);
        }
    }
    int sel;
    printf("--------------------------\n检索完成！请选择接下来的操作：\n【1】返回主菜单\t【2】退出");
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
    printf("输入新增用户的名字：");
    scanf("%s",user.name);
    printf("输入新增用户的ID：");
    scanf("%s",user.id);
    printf("输入新增用户的密码：");
    scanf("%s",user.password);
    printf("输入新增用户的权限：");
    scanf("%s",user.authority);
    FILE *fp;
    if (NULL==(fp= fopen("user.txt","a"))) printf("错误：error on open user list\n");
    if(fprintf(fp,"%s\t\t\t%s\t\t\t%s\t\t\t%s\n",user.id,user.name,user.password,user.authority)==EOF) printf("写入信息失败：error: new user write in error!\n");
    if (EOF== fclose(fp)) printf("关闭文件失败！error:close fallen on user.txt\n");
    printf("写入新用户信息成功！\n-----------"
           "-------------------------\n选择接下来执行的操作：\n【1】退出系统\t【2】继续录入\t【3】回到主菜单");
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
    printf("输入要删除的用户编号：");
    int k=0;
    char id[15]="\0";
    scanf("%s",id);
    printf("确定要删除吗？\n【1】确定\t\t\t【2】取消");
    menu_bottom_bar();
    scanf("%d",&k);
    int chose;
    switch (k)
    {

        case 1:
        {
            //del_dat(id,"bookshelf.txt");
            del_row("user.txt",id);
            printf("已为您删除编号%d的用户！接下来的操作：\n【1】返回主菜单\t\t【2】继续删除其他用户\t\t【3】退出系统", trans_int(id));
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
            printf("取消删除操作成功！接下来的操作：\n【1】返回主菜单\t\t【2】删除其他书籍\t\t【3】退出系统");
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
    printf("请先对需要更改的书籍进行查找：");
    book_search(1);
    printf("输入要修改的书籍编号：");
    scanf("%s",found_id);
    int ki=search_tool("bookshelf.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("bookshelf.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    printf("选择您要修改的信息：\n【1】书籍名称\t\t【2】作者名\n【3】出版社名\t\t【4】ISBN");
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
            printf("输入新的书名：");
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
            printf("输入新的作者名：");
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
            printf("输入新的出版社名：");
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
            printf("输入新的ISBN：");
            scanf("%s",bk.isbn);
            fscanf(fp,"%s",bk.on_shelf);
            fclose(fp);
            break;
        }
    }
    printf("确定要修改吗？\n【1】确定\t\t【2】取消");
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
        printf("已保存更改！\n");
    } else
        printf("已取消操作！\n");
    printf("--------------------------------\n请选择接下来的操作：\n【1】更改其他的书籍信息\t【2】回到主菜单\t【3】退出系统");
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
//    printf("请先对需要更改的书籍进行查找：");
//    book_search(1);
    FILE *ttt;
    ttt= fopen("user.txt","r");
    int all_u=0;
    printf("已在系统中注册的用户及其信息:\n");
    while (!feof(ttt))
    {
        char read_l[4999]="\0";
        fgets(read_l,4998,ttt);
        if (all_u>0) printf("%s",read_l);
        all_u++;
    }
    printf("共 %d 个用户\n",all_u-2);
    printf("输入要修改的用户编号：");
    scanf("%s",found_id);
    int ki=search_tool("user.txt",found_id,found_inf);
    FILE *fp;
    fp= fopen("user.txt","r");
    for (int i=0;i<ki-1;i++)
    {
        char sybs[10000]="\0";
        fgets(sybs,9999,fp);
    }
    printf("选择您要修改的信息：\n【1】用户名称\t\t【2】用户密码\t\t【3】用户权限\n");
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
            printf("输入新的用户名：");
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
            printf("输入新的用户密码：");
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
            printf("输入新的用户权限：\n【user】普通用户\t【admin】系统管理员\n");
            menu_bottom_bar();
            scanf("%s",uer.authority);
            fclose(fp);
            break;
        }
    }
    printf("确定要修改吗？\n【1】确定\t\t【2】取消");
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
        printf("已保存更改！\n");
    } else
        printf("已取消操作！\n");
    printf("--------------------------------\n请选择接下来的操作：\n【1】更改其他的用户信息\t【2】回到主菜单\t【3】退出系统");
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
        printf("【1】书籍查询\t\t【2】借还查询\t\t【3】借阅记录");
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
        printf("【1】馆藏书籍查询\t【2】学生借还查询\t【3】学生借阅记录\n"
               "【4】学生账户注册\t【5】学生账户删除\t【6】学生账户修改\n"
               "【7】馆藏图书录入\t【8】馆藏图书删除\t【9】馆藏图书修改");
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