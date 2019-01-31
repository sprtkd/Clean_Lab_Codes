#include<stdio.h>

struct date
{
int day;
int month;
int year;


};




struct employee
{
int ecode;
char ename[200];
float salary;
int dnum;
struct date doj;


};


int main()
{

struct employee emp[100];
int i,n;
puts("\nEnter the no. of employees in the company:");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("\nEnter details of employee no. %d:",i+1);
puts("\nEnter employee code:");
scanf("%d",&emp[i].ecode);
puts("\nEnter employee name:\n");
getchar();
scanf("%[^\n]",emp[i].ename);
puts("\nEnter salary: Rs.");
scanf("%f",&emp[i].salary);
puts("\nEnter Department no.:");
scanf("%d",&emp[i].dnum);
puts("\nEnter date of joining(dd/mm/yyyy):");
scanf("%d/%d/%d",&emp[i].doj.day,&emp[i].doj.month,&emp[i].doj.year);

}


puts("\nShowing list of employees in the company:");
printf("\nSl. Ecode. Name\t\tSalary\t\tDept. No. \t D.O.Joining");
for(i=0;i<n;i++)
{
puts("\n");

printf("\n%d.  %d  ",i+1,emp[i].ecode);
printf("\t%s",emp[i].ename);
printf("  Rs.%.2f\t%d\t\t%d/%d/%d",emp[i].salary,emp[i].dnum,emp[i].doj.day,emp[i].doj.month,emp[i].doj.year);



}



puts("\nShowing list of employees with salary>10000:");
printf("\nSl. Ecode. Name\t\tSalary\t\tDept. No. \t D.O.Joining");
for(i=0;i<n;i++)
{
if(emp[i].salary>=10000.0)
{
puts("\n");

printf("\n%d.  %d  ",i+1,emp[i].ecode);
printf("\t%s",emp[i].ename);
printf("  Rs.%.2f\t%d\t\t%d/%d/%d",emp[i].salary,emp[i].dnum,emp[i].doj.day,emp[i].doj.month,emp[i].doj.year);

}

}







return 0;
}

