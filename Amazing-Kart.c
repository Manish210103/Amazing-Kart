#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

//This is a struct for cart
typedef struct
{
    char bname[100];
    char cart[100];
    int bills;
    int qty;
}billing;

//This is a struct for the employee
typedef struct
{
    char name[100];
    int age;
    float basicsal;
    int ecode;
    double number;
    char pos[100];
}emp;

//This is the struct for new customer
typedef struct
{
    char cusname[100];
    int pass;
    int acc;
    char address[100];
    int mobno;
}cust;

    char cart[30][100];
    int pnum[100][2],q=0,bill[100];
    int rate[30]={100,100000,450,150,45000,275,100,20000,750,25,30000,100,50,500,150,100,7000,450,225,3500,1500,250,45000,20,5,75000,250,225,20000,1500};
    //This are the items in the product list
    char items[30][100]={" Sugar  "," Laptop  "," Shirt  "," Rice   "," Phone    "," T-Shirt"," Dal    "," Fridge  "," Pant   "," Milk     "," Oven    "," Gloves  "," Eggs   "," Charger  "," Cap    "," Flour  "," Watch  "," Scarf  "," Wheat  "," Earbuds"," Shoes  "," Juice  "," Homepod"," Bands  "," Chips  "," TV       "," Mask   "," Meat   "," Speakers"," Ring   "};


void modifyrate()
{
    //This is to modify rate for the products
    emp e;
    FILE *fp,*rt;
    fp = fopen("emp.DAT","rb+");
    rt=fopen("rate.txt","rb+");
    //to clear the screen
    system("cls");
    //system("color 0B") is used to make the menu in blue colour
    system("color 0B");
    int size=sizeof(e);
    char cart[30][100],empname[100],emppass[100],emprole[100];
    int pnum[100][2],q=0,bill[100],rate1;
    //To check if the employee is allowed to modify rate
    printf("\nLOGIN CREDENTIALS\n\n");
    printf("\n\tEnter your Role : ");
    scanf("%s",emprole);
    printf("\n\tEnter Password : ");
    scanf("%s",emppass);
    if(strcmpi(emppass,"MOD@123")==0 && strcmpi(emprole,"EMPLOYEE")==0)
    {
        system("cls");
        printf("\nPERMISSION GRANTED.....");
        sleep(2);
        system("cls");
        //to go to the start of the file
        rewind(fp);
        //the product list is printed for the customer to choose
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("|GROCERIES\t\t\t|ELECTRONICS\t\t\t|CLOTHING\t\t\t|\n");
        printf("|-------------------------------|-------------------------------|-------------------------------|\n");
        int i=0,c;
        while(fread(&rate1,sizeof(rate1),1,rt)==1)
        {
            printf("|%d.%s\t\t%d\t",i+1,items[i],rate1);
            if ((i+1)%3==0)
                printf("|\n");
            i++;
            if(i==30)
            {
                break;
            }
        }
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("\n\n\n");
        char eyes='y';
        while(eyes=='y')
        {
            //asks the user to enter the product for which the rate to be changed
            printf("\n\n\tEnter the item number to change its rate : ");
            scanf("%d",&c);
            if(c<=30)
            {
                printf("\n\tEnter the new rate : ");
                scanf("%d",&rate[c-1]);
                printf("\n\t\t\t\tEnter 'y' to add another record :");
                fflush(stdin);
                eyes=getche();
            }
        }
        fclose(rt);
        //The screen is cleared
        system("cls");
        //system("color 0B") is used to make the menu in blue colour
        system("color 0B");
        //The rate file is chosen
        rt = fopen("rate.txt","wb");
        //the rate after changing is now printed
        printf("------------------------------\n");
        printf("The new rate after changing\n");
        printf("------------------------------\n");
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("|GROCERIES\t\t\t|ELECTRONICS\t\t\t|CLOTHING\t\t\t|\n");
        printf("|-------------------------------|-------------------------------|-------------------------------|\n");
        for (i=0;i<30;i++)
        {
            printf("|%d.%   s\t-  \t%d\t",i+1,items[i],rate[i]);
            if ((i+1)%3==0)
                printf("|\n");
            fwrite(&rate,size,1,rt);
        }
        printf("-------------------------------------------------------------------------------------------------\n");
        printf("\n\n\n");
        //the rate file is closed
        fclose(rt);
        fclose(fp);
    }
    else
    {
        system("cls");
        printf("\nPERMISSION DENIED");
        sleep(2);
        system("cls");
        fflush(stdin);
    }
}


void listemp()
{
    emp e;
    FILE *fp;
    char empname[100],emprole[100],emppass[100];
    int size=sizeof(e);
    fp = fopen("emp.DAT","rb+");
    system("cls");
    system("color 0B");
    //rewind is used to go to the start of the file
    rewind(fp);
    //to print all the records present in the file
    //to check if the particular lines contains any data
    printf("\nLOGIN CREDENTIALS\n\n");
    printf("\n\tEnter your Role : ");
    scanf("%s",emprole);
    printf("\n\tEnter Password : ");
    scanf("%s",emppass);
    if(strcmpi(emprole,"HR")==0 && strcmpi(emppass,"HR@123")==0)
    {
        system("cls");
        printf("\nPERMISSION GRANTED....");
        sleep(2);
        system("cls");
        printf("\n\nEMPLOYEE RECORDS");
        //prints each record
        while(fread(&e,size,1,fp)==1)
        {
            printf("\n\n------------------------------\n");
            printf("NAME: %s\nAGE: %d\nBASIC SALARY: %.2f\nECODE: %d\nMOB NO: %.0lf\nROLE: %s\n",e.name,e.age,e.basicsal,e.ecode,e.number,e.pos);
            printf("------------------------------\n");
        }
    }
    else
    {
        system("cls");
        printf("PERMISSION DENIED....");
        sleep(2);
        system("cls");
    }
    fflush(stdin);
    fclose(fp);
}


void addemp()
{
    //This is to add employee record
    FILE *fp;
    emp e;
    char empname[100],emprole[100],emppass[100],eyes='y';
    int size=sizeof(e);
    system("cls");
    fp = fopen("emp.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("emp.DAT","wb+");
        if(fp == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    //system("color 0B") is used to make the menu in blue color
    system("color 0B");
    //to make the cursor move to the last page
    fseek(fp,0,SEEK_END);
    //Now it prompts the user to give the employee details
    while(eyes=='y')
    {
        printf("\n\n\t\t----------------------------------------\n");
        printf("\t\t          ADD EMPLOYEE RECORD\n");
        printf("\t\t----------------------------------------\n");
        printf("\n\t\t\tEnter Employee name : ");
        scanf("%s",e.name);
        printf("\t\t\tEnter Employee age : ");
        scanf("%d", &e.age);
        printf("\t\t\tEnter basic salary : ");
        scanf("%f", &e.basicsal);
        printf("\t\t\tEnter Employee Code : ");
        scanf("%d",&e.ecode);
        printf("\t\t\tEnter Employee Mobile number : ");
        scanf("%lf",&e.number);
        printf("\t\t\tEnter Employee position : ");
        scanf("%*c%s",e.pos);
        //The record of the particular employee is added inside the file
        fwrite(&e,size,1,fp);
        if (strcmpi(e.pos,"MANAGER")==0)
        {
            printf("\n\t\t\tYou are a Manager In Amazing Kart,Congratulations\n\t\t\tYou have the ability to check the customer logs here\n\t\t\tlogin credentials\n\t\t\t\trole : MANAGER\n\t\t\t\tpassword : log@123");
        }
        else if (strcmpi(e.pos,"HR")==0)
        {
            printf("\n\t\t\tYou are a HR in Amazing Kart,Congratulations\n\t\t\tYou are able to access the list of employees available\n\t\t\tlogin credentials\n\t\t\t\trole : HR\n\t\t\t\tpassword : hr@123");
        }
        else if (strcmpi(e.pos,"EMPLOYEE")==0)
        {
            printf("\n\t\t\tYou are a Mod in Amazing Kart,Congratulations\n\t\t\tYou can change the price of the products available\n\t\t\tlogin credentials\n\t\t\t\trole : EMPLOYEE\n\t\t\t\tpassword : mod@123");
        }
        printf("\n\n\t\t----------------------------------------\n");
        //asking the user to add another employee record
        printf("\n\t\t\t\tEnter 'y' to add another record : ");
        fflush(stdin);
        //getting character for the infinite loop
        if(getche()!='y')
        {
            break;
        }
        system("cls");
    }
    fclose(fp);
}

//This is to see the log of customer's purchases
void employeelog()
{
    system("cls");
    FILE *log,*cus;
    cus = fopen("cus.DAT","r");
    log=fopen("history.DAT","r");
    rewind(log);
    billing pro;
    cust c;
    char empname[100],emprole[100],emppass[100],mem[100];
    int i=0;
    //This is to check if the person is authorized for log authorisation
    printf("\nLOGIN CREDENTIALS\n\n");
    printf("\n\tEnter your Role : ");
    scanf("%s",emprole);
    printf("\n\tEnter Password : ");
    scanf("%s",emppass);
    if(strcmpi(emprole,"MANAGER")==0 && strcmpi(emppass,"LOG@123")==0)
    {
        system("cls");
        printf("\nPERMISSION GRANTED....");
        sleep(2);
        system("cls");
        system("cls");
        printf("\n\nENTER THE CUSTOMER NAME TO BE CHECKED : ");
        scanf("%s",mem);
        system("cls");
        printf("------------------------------------------------------------\n");
        printf("\t%s history\n",mem);
        printf("------------------------------------------------------------\n");
        //If the person is in the logs their purhcase history will be printed
        while(fread(&pro,sizeof(pro),1,log)==1)
        {
            if(strcmpi(mem,pro.bname)==0)
            {
                printf("\n%s\t %d \t%d\n",pro.cart,pro.qty,pro.bills);
            }
        }
        printf("\n------------------------------------------------------------\n");
        system("cls");
        printf("------------------------------------------------------------\n");
        printf("\t%s history\n",mem);
        printf("------------------------------------------------------------\n");
        while(fread(&pro,sizeof(pro),1,log)==0)
        {
            printf("\n\t\tHAVEN'T PURCHASED YET\n");
            break;
        }
        printf("\n------------------------------------------------------------\n");
        fclose(log);
        fclose(cus);
        fflush(stdin);
    }
    else
    {
        system("cls");
        printf("\nPERMISSION DENIED");
        sleep(2);
        system("cls");
        fflush(stdin);
    }
}

//The menu for employee
void employee()
{
    char ch='y';
    do
    {
            emp e;
            system("cls");
            //system("color 0B") is used to make the menu in blue color
            system("color 0B");
            // a choice variable
            int ech;
            printf("\n\n\t\t------------------------------");
            printf("\n\t\t   EMPLOYEE DETAILS\n");
            printf("\t\t------------------------------\n");
            printf("\t\t 1. ADD EMPLOYEE RECORD\n");
            printf("\t\t 2. LIST ALL RECORD\n");
            printf("\t\t 3. MODIFY PRODUCTS\n");
            printf("\t\t 4. CUSTOMER LOG\n");
            printf("\t\t 5. EXIT\n");
            printf("\t\t------------------------------\n");
            printf("\n\t\t\tEnter your choice : ");
            scanf("%d",&ech);
            switch(ech)
            {
                case 1:
                    {
                        addemp();
                        printf("\n\n\t\t\tprevious page : ");
                        scanf("%c",&ch);
                        break;
                    }
                case 2:
                    {
                        listemp();
                        printf("\n\n\t\t\tprevious page : ");
                        scanf("%c",&ch);
                        break;
                    }
                case 3:
                    {
                        modifyrate();
                        printf("\n\n\t\t\tprevious page : ");
                        scanf("%c",&ch);
                        break;
                    }
                case 4:
                    {
                        employeelog();
                        printf("\n\n\t\t\tprevious page : ");
                        scanf("%c",&ch);
                        break;
                    }
                default:
                    {
                        //To get out of the loop and reach main menu
                        scanf("%c",&ch);
                        break;
                    }
            }
    }while(ch=='y'||ch=='Y');
}

//This is the history of the user's Previous purchases
void history(char * cusname)
{
    system("cls");
    FILE *log,*cus;
    cus = fopen("cus.DAT","r");
    //we open the history file to get the info from the file
    log=fopen("history.DAT","r");
    billing pro;
    cust c;
    char mem[100];
    system("cls");
    printf("------------------------------------------------------------\n");
    printf("\tProduct \t Qty \t Amount\n");
    while(fread(&pro,sizeof(pro),1,log)==1)
    {
        //To only get the info of cusname
        if(strcmpi(cusname,pro.bname)==0)
        {
            printf("\n\t%s\t %d \t%d\n",pro.cart,pro.qty,pro.bills);
        }
    }
    printf("\n------------------------------------------------------------\n");
    fclose(log);
    fclose(cus);
    fflush(stdin);
}

//This is the billing part for the customer
void billcus(char * cusname)
{
    FILE *temp,*log,*cus;
    billing b;
    cust c;
    cus = fopen("cus.DAT","r");
    log=fopen("history.DAT","a+");
    temp=fopen("buy.DAT","r");
    billing pro;
    strcpy(pro.bname,cusname);
    int z,i=0;
    float sum=0;
    //Printing the bill
    system("cls");
    system("color 0B");
    printf("\n\n\n\n");
    printf("\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t|---------------------------BILL------------------------|\n");
    printf("\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t|                    $  AMAZING KART  $                 |\n");
    printf("\t\t\t|-------------------------------------------------------|\n");
    printf("\t\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t\t|\tS No.\t Product \tQty \tPrice\t\t|\n");
    printf("\t\t\t|\t\t\t\t\t\t\t|\n");
    while(fread(&pro,sizeof(pro),1,temp)==1)
    {
        printf("\t\t\t|\t%d.\t%s  \t%d \t%d\t\t|\n",i+1,pro.cart,pro.qty,pro.bills);
        i++;
        sum+=pro.bills;
        //Adding all Products in the bill to the customer's purchase history
        fwrite(&pro,sizeof(pro),1,log);
    }
    printf("\t\t\t|\t\t\t\t\t\t\t|\n\t\t\t|\t\t\t\t       _______\t\t|\n");
    printf("\t\t\t|\t\t\t\tTOTAL =\t%.0f\t\t|\n",sum);
    printf("\t\t\t|\t\t\t\tGST   =\t%.0f\t+\t|\n",0.1*sum);
    printf("\t\t\t|\t\t\t\t       _______\t\t|\n");
    printf("\t\t\t|\t\t\tGRAND TOTAL  =  %.0f\t\t|\n",1.1*sum);
    printf("\t\t\t|\t\t\t\t\t\t\t|\n\t\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t\t|\tThank You For Purchasing in Amazing Kart\t|\n");
    printf("\t\t\t|\t\t\t\t\t\t\t|\n\t\t\t|\t\t\t\t\t\t\t|\n");
    printf("\t\t\t|-------------------------------------------------------|\n");
    printf("\n\n\t\t\t Enter 'y' for payment details: ");
    //TO proceed to the payment
    if(getch()=='y')
    {
        int choice,num1,dd,mm,yy,cvv,otp,otp1,count=0,temp=0;
        system("cls");
        printf("\n\n\t\t\tCHOOSE THE MODE OF PAYMENT\n\n");
        printf("\t\t\t1.ONLINE TRANSACTION\n\t\t\t2.CASH ON DELIVERY\n\n\t\t\t\tchoice: ");
        scanf("%d",&choice);
        char mem[100];
        switch(choice)
        {
            case 1:
            {
                //For Online Transaction
                w:
                system("cls");
                printf("\nCARD MEMBER NAME : ");
                scanf("%s",mem);
                printf("\nCARD NUMBER : ");
                scanf("%d",&num1);
                printf("\nCVV : ");
                scanf("%d",&cvv);
                printf("\nEXPIRES ON (dd/mm/yyyy) : ");
                scanf("%d/%d/%d",&dd,&mm,&yy);
                while(fread(&c,sizeof(c),1,cus)==1)
                {
                    if(strcmpi(mem,c.cusname)==0 && num1==c.acc)
                    {
                        z:
                        //OTP is generated
                        otp=rand()%1000;
                        printf("\nYOUR OTP IS %d\n\n",otp);
                        printf("ENTER THE OTP : ");
                        scanf("%d",&otp1);
                        if(otp!=otp1)
                        {
                            count++;
                            if(count<3)
                            {
                                rewind(cus);
                                printf("\nINVALID OTP. TRY AGAIN\n");
                                goto z;
                            }
                            else
                            {
                                printf("\n\t\t\tSORRY YOUR TRANSACTION HAS BEEN CANCELLED\n\n");
                                temp=1;
                                break;
                            }
                        }
                        else
                        {
                            system("cls");
                            printf("\n\n\t\t\tORDER IS BEING PROCESSED.....");
                            sleep(3);
                            system("cls");
                            printf("\n\n\t\t\tYOUR ORDER OF TOTAL %.2f HAS BEEN PLACED SUCCESSFULLY.....",sum);
                            printf("\n\n\t\t\tTHE ORDER WILL BE DELIVERED TO %s \n\n",c.cusname);
                            break;
                        }
                    }
                    else if(temp==0)
                    {
                        system("cls");
                        printf("\nINVALID NAME/CARD NUMBER\n\n");
                        printf("ENTER 'Y' TO TRY AGAIN\n");
                        if(getch()=='y'||getch()=='Y')
                        {
                            goto w;
                        }
                    }
                }
                break;
            }
            case 2:
            {
                //For Cash On Delivery
                count=0;
                int mno,temp=1;
                char add[100],mem1[100];
                system("cls");
                y:
                printf("\nCUSTOMER NAME: ");
                scanf("%s",mem1);
                printf("\nMOBILE NUMBER: ");
                scanf("%d",&mno);
                printf("\nADDRESS TO BE DELIVERED: ");
                scanf("%s",add);
                while(fread(&c,sizeof(c),1,cus)==1)
                {
                    if(strcmpi(mem1,c.cusname)==0 && mno==c.mobno)
                    {
                        system("cls");
                        printf("\n\n\t\t\tORDER IS BEING PROCESSED.....");
                        sleep(3);
                        system("cls");
                        printf("\n\n\t\t\tYOUR ORDER OF TOTAL %.2f HAS BEEN PLACED SUCCESSFULLY.....",sum);
                        printf("\n\n\t\t\tTHE ORDER WILL BE DELIVERED TO %s AT %s\n\n",c.cusname,add);
                        temp=0;
                        break;
                    }
                }
                if(temp==1)
                {
                    count++;
                    if(count<3)
                    {
                        rewind(cus);
                        printf("\nINVALID NAME/NUMBER\n");
                        goto y;
                    }
                    else
                    {
                        printf("\n\t\t\tSORRY YOUR ORDER HAS BEEN CANCELLED\n\n");
                        break;
                    }
                }
            }
            break;
        }
    }
    fclose(temp);
    temp=fopen("temp.DAT","w");
    while(fread(&pro,sizeof(pro),1,temp)==1)
    {

    }
    fflush(stdin);
    fclose(temp);
    fclose(log);
    fclose(cus);
}


void cartcus(char * cusname)
{
    FILE *kart,*buy;
    buy=fopen("buy.DAT","w");
    //Using temp file to save the products from the cart into this file
    kart=fopen("temp.DAT","r");
    billing b,b1[30];
    strcpy(b.bname,cusname);
    system("cls");
    printf("\n\n\t|-----------------------------------------------|\n");
    printf("\t|\t\tYour cart contains\t\t|\n");
    printf("\t|-----------------------------------------------|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    printf("\t|\t   Product \tQty \tPrice\t\t|\n");
    printf("\t|\t\t\t\t\t\t|\n");
    int r,i=0,pronum;
    while(fread(&b,sizeof(b),1,kart)==1)
    {
        printf("\t|\t%d. %s \t%d \t%d\t\t|\n",i+1,b.cart,b.qty,b.bills);
        strcpy(b1[i].bname,b.bname);
        strcpy(b1[i].cart,b.cart);
        b1[i].qty=b.qty;
        b1[i].bills=b.bills;
        i++;
    }
    r=i;
    printf("\t|\t\t\t\t\t\t|\n\t|\t\t\t\t\t\t|\n");
    printf("\t|-----------------------------------------------|\n");
    fflush(stdin);
    printf("\n\t\t\tDO YOU WANT TO\n\n\t\t\t1.ADD ANY PRODUCT\n\t\t\t2.CHANGE THE QUANTITY\n\t\t\t3.NO CHANGE\n\t\t\t\t\tchoice:  ");
    scanf("%d",&pronum);
    if(pronum==1)
    {
        //To add additional product
        FILE *temp,*rt;
        billing pro;
        rt=fopen("rate.txt","r");
        temp=fopen("temp.DAT","a+");
        int pnum[100][2],q=0,sum=0,rate,prize[30],z,i=0;
        char ch='y';
        system("cls");
        printf("------------------------------------------------------------------------------------------------------------------------ \n");
        printf("|GROCERIES\t\t\t\t|ELECTRONICS\t\t\t\t|CLOTHING\t\t\t\t| \n");
        printf("|---------------------------------------|---------------------------------------|--------------------------------------| \n");
        printf("|\t   PRODUCT\t\tPRICE\t|\t   PRODUCT\t\tPRICE\t|\t   PRODUCT\t\tPRICE\t| \n");
        printf("|\t\t\t\t\t|\t\t\t\t\t|\t\t\t\t\t| \n");
        while(fread(&rate,sizeof(rate),1,rt)==1)
        {
            printf("|\t%d.%s\t-\t%d\t",i+1,items[i],rate);
            prize[i]=rate;
            if ((i+1)%3==0)
                printf("| \n");
            i++;
            if(i==30)
            {
                break;
            }
        }
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printf("\n\n\n");
        fflush(stdin);
        char t='y';
        while(t=='y')
        {
            //asks the user to enter the product that they wish to buy
            printf("Enter the product number you wish to buy:\t");
            scanf("%d",&pnum[q][0]);
            strcpy(pro.cart,items[pnum[q][0]-1]);
            printf("Enter how many product:\t");
            scanf("%d",&pnum[q][1]);
            pro.qty=pnum[q][1];
            pro.bills=prize[pnum[q][0]-1]*pnum[q][1];
            strcpy(pro.bname,cusname);
            fwrite(&pro,sizeof(pro),1,temp);
            sum+=pro.bills;
            printf("Enter 'y' to add another record:");
            printf("\n");
            fflush(stdin);
            t=getche();
            printf("\n");
            q++;
            z=q;
        }
        fflush(stdin);
        fclose(temp);
        i=0;
        for(i=0;i<r;i++)
        {
            if(b1[i].qty==0)
            {

            }
            else
            {
                fwrite(&b1[i],sizeof(b1[i]),1,buy);
            }
        }
        fflush(stdin);
    }
    else if(pronum==2)
    {
        //to change the quantity of any product
        int proqty,pqty,crc=0;
        rewind(kart);
        char ch='y';
        while(ch=='y'||ch=='Y')
        {
            printf("\n\t\t\tenter the product number for which the quantity must be changed : ");
            scanf("%d",&proqty);
            printf("\n\t\t\tenter the new quantity : ");
            scanf("%d",&pqty);
            b1[proqty-1].bills=(b1[proqty-1].bills/b1[proqty-1].qty)*pqty;
            b1[proqty-1].qty=pqty;
            printf("\n\n\t\t\tDo u want to change further(y/n)");
            ch=getch();
        }
        system("cls");
        printf("\n\n\t|-----------------------------------------------|\n");
        printf("\t|\t\tYour cart contains\t\t|\n");
        printf("\t|-----------------------------------------------|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        printf("\t|\t   Product \tQty \tPrice\t\t|\n");
        printf("\t|\t\t\t\t\t\t|\n");
        for(i=0;i<r;i++)
        {
            if(b1[i].qty==0)
            {
                crc++;
            }
            else
            {
                printf("\t|\t%d. %s \t%d \t%d\t\t|\n",i+1-crc,b1[i].cart,b1[i].qty,b1[i].bills);
                fwrite(&b1[i],sizeof(b1[i]),1,buy);
            }
        }
        printf("\t|\t\t\t\t\t\t|\n\t|\t\t\t\t\t\t|\n");
        printf("\t|-----------------------------------------------|\n");
        fflush(stdin);
    }
    else if(pronum==3)
    {
        i=0;
        for(i=0;i<r;i++)
        {
            if(b1[i].qty==0)
            {

            }
            else
            {
                fwrite(&b1[i],sizeof(b1[i]),1,buy);
            }
        }
        fflush(stdin);
    }
    fclose(buy);
    fclose(kart);
}

void productlist(char * cusname)
{
    //Lists the products and prompts the user to buy them
    FILE *temp,*rt;
    billing pro;
    rt=fopen("rate.txt","r");
    temp=fopen("temp.DAT","a+");
    int pnum[100][2],q=0,sum=0,rate,z,prize[30],i=0;
    char ch='y';
    system("cls");
    printf("------------------------------------------------------------------------------------------------------------------------ \n");
    printf("|GROCERIES\t\t\t\t|ELECTRONICS\t\t\t\t|CLOTHING\t\t\t\t| \n");
    printf("|---------------------------------------|---------------------------------------|--------------------------------------| \n");
    printf("|\t   PRODUCT\t\tPRICE\t|\t   PRODUCT\t\tPRICE\t|\t   PRODUCT\t\tPRICE\t| \n");
    printf("|\t\t\t\t\t|\t\t\t\t\t|\t\t\t\t\t| \n");
    while(fread(&rate,sizeof(rate),1,rt)==1)
    {
        printf("|\t%d.%s\t-\t%d\t",i+1,items[i],rate);
        prize[i]=rate;
        if ((i+1)%3==0)
        printf("| \n");
        i++;
        if(i==30)
        {
            break;
        }
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n\n\n");
    fflush(stdin);
    char t='y';
    while(t=='y')
    {
        //asks the user to enter the product that they wish to buy
        printf("Enter the product number you wish to buy:\t");
        scanf("%d",&pnum[q][0]);
        strcpy(pro.cart,items[pnum[q][0]-1]);
        printf("Enter how many product:\t");
        scanf("%d",&pnum[q][1]);
        pro.qty=pnum[q][1];
        pro.bills=prize[pnum[q][0]-1]*pnum[q][1];
        strcpy(pro.bname,cusname);
        fwrite(&pro,sizeof(pro),1,temp);
        sum+=pro.bills;
        printf("Enter 'y' to add another record:");
        printf("\n");
        fflush(stdin);
        t=getche();
        printf("\n");
        q++;
        z=q;
    }
    fflush(stdin);
    fclose(temp);
}


void customer()
{
    //this is the customer menu
    system("cls");
    FILE *cus,*log;
    log=fopen("history.DAT","a+");
    cus = fopen("cus.DAT","a+");
    if(cus == NULL)
    {
        cus = fopen("cus.DAT","a+");
        if(cus == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    cust user;
    char cart[30][100],cusname[100],ch='y';
    int pnum[100][2],q=0,bill[100],flag=0,choice,cusnumber;
    billing pro;
    do
    {
        //To check the nature of Customer
        printf("\n\n\t\t------------------------------");
        printf("\n\t\t\tCUSTOMER");
        printf("\n\t\t------------------------------");
        printf("\n\n\t\t1.NEW USER\n\t\t2.EXISTING USER");
        printf("\n\n\t\t------------------------------");
        printf("\n\n\t\t\tEnter your choice : ");
        scanf("%d",&choice);
        if(choice==1)
        {
            system("cls");
            printf("\n\n\t\t\t------------------------------");
            printf("\n\t\t\t\tCUSTOMER DETAILS");
            printf("\n\t\t\t------------------------------");
            fseek(cus,0,SEEK_END);
            printf("\n\n\t\t\tEnter Customer name : ");
            scanf("%s",user.cusname);
            printf("\t\t\tEnter Mobile number : ");
            scanf("%d", &user.mobno);
            printf("\t\t\tEnter Password : ");
            scanf("%d", &user.pass);
            printf("\t\t\tEnter ACCOUNT number :");
            scanf("%d",&user.acc);
            printf("\t\t\tEnter Customer Address :");
            scanf("%s",user.address);
            //The record of the particular employee is added inside the file
            fwrite(&user,sizeof(user),1,cus);
            printf("\n\t\t\t------------------------------");
            printf("\n\n\t\t\tYOUR LOGIN HAS BEEN CREATED SUCCESSFULLY......");
            sleep(3);
            system("cls");
            printf("\n\n\n\t\t\tNOW LOGIN USING EXISTING USER WITH YOUR NEW NAME AND MOBILE NUMBER  ");
            fflush(stdin);
            fclose(cus);
            sleep(3);
            system("cls");
        }
        else if (choice==2)
        {
            //Verifying Existing User
            cus = fopen("cus.DAT","r");
            system("cls");
            rewind(cus);
            printf("\n\n\t\t---------------------------------");
            printf("\n\t\t   VERIFICATION OF CUSTOMER");
            printf("\n\t\t---------------------------------");
            printf("\n\n\t\tEnter Customer name : ");
            scanf("%s",cusname);
            printf("\n\t\tEnter your Mobile Number : ");
            scanf("%d",&cusnumber);
            while(fread(&user,sizeof(user),1,cus)==1)
            {
                if(strcmpi(cusname,user.cusname)==0 && (cusnumber==user.mobno))
                {
                    flag=1;
                    system("cls");
                    printf("\n\n\t\tWELCOME %s ......",cusname);
                    choice=3;
                    sleep(3);
                    do
                    {
                        system("cls");
                        //system("color 0B") is used to make the menu in blue colour
                        system("color 0B");
                        //The choice is printed
                        printf("\n\n\t\t------------------------------\n");
                        printf("\t\t   CUSTOMER\n");
                        printf("\t\t------------------------------\n");
                        printf("\t\t 1.PRODUCT LIST\n");
                        printf("\t\t 2.CART\n");
                        printf("\t\t 3.BILL\n");
                        printf("\t\t 4.ORDER HISTORY\n");
                        printf("\t\t 5.EXIT\n");
                        printf("\t\t------------------------------\n");
                        printf("\t\t\t Enter your choice: ");
                        scanf("%d",&ch);
                        printf("\n");
                        //the screen is cleared
                        //system("color 0B") is used to make the menu in blue colour
                        system("color 0B");
                        q=0;
                        switch(ch)
                        {
                            case 1:
                            {
                                productlist(cusname);
                                printf("\n\n\t\t\tprevious page : ");
                                scanf("%c",&ch);
                                break;
                            }
                            case 2:
                            {
                                cartcus(cusname);
                                printf("\n\n\t\t\tprevious page : ");
                                scanf("%c",&ch);
                                break;
                            }
                            case 3:
                            {
                                billcus(cusname);
                                printf("\n\n\t\t\tprevious page : ");
                                scanf("%c",&ch);
                                break;
                            }
                            case 4:
                            {
                                history(cusname);
                                printf("\n\n\t\t\tprevious page : ");
                                scanf("%c",&ch);
                                break;
                            }
                            case 5:
                            {
                                scanf("%c",&ch);
                                break;
                            }
                            default :
                            {
                                scanf("%c",&ch);
                                break;
                            }
                        }
                    }while(ch=='y'||ch=='Y');
                }
            }
            if(flag==0)
            {
                system("cls");
                printf("\n\n\t\tUSER NOT EXIXTS\n");
                printf("\n\t\tTry again or Register as New customer");
                sleep(3);
                system("cls");
            }
            fclose(cus);
        }
    }while(choice==1||choice==2);
}


int main()
{
    //The main menu
    system("color 0B");
    int choice;
    char ch='y';
    do
    {
        printf("\n\n\t\t------------------------------");
        printf("\n\t\t\tAMAZING KART\n");
        printf("\t\t------------------------------\n");
        printf("\n\t\t 1.EMPLOYEE\n");
        printf("\t\t 2.CUSTOMER\n");
        printf("\t\t 3.EXIT\n");
        printf("\t\t------------------------------\n");
        printf("\n\t\t    Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                employee();
                printf("\n\t\tPrevious page : ");
                scanf("%c",&ch);
                break;
            }
            case 2:
            {
                customer();
                printf("\n\t\tPrevious page : ");
                scanf("%c",&ch);
                break;
            }
            case 3:
            {
                exit(0);
            }
            default :
            {
                printf("invalid Number\n");
                exit(0);
            }
        }
    fflush(stdin);
    system("cls");
    }while(ch=='y'||ch=='Y');
}
