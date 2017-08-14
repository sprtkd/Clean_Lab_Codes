import java.util.*;

class bank_account
{
    String cust_name, address;
    int cust_age;
    float balance;
    float si_rate;
    Date dateOfCreation;
    bank_account(String name,String add,int age, float bal, float rate)
    {
        cust_name = name;
        cust_age = age;
        address = add;
        balance = bal;
        si_rate = rate;
    }
    
    float get_balance()
    {
        return balance;
    }
    
    void print_details()
    {
        System.out.println("-----------------------------");
        System.out.println("Name: "+cust_name);
        System.out.println("Address: "+address);
        System.out.println("Age: "+cust_age);
        System.out.println("Balance: "+balance);
        System.out.println("Simple Interest Rate: "+si_rate);
        System.out.println("-----------------------------");
    }
    
    float GetInterest()
    {
        return balance*si_rate;
    }
    
    float DepositAmt(float amount)
    {
    	balance = balance + amount;
    	System.out.println("Deposit successful");
    	return balance;
    }
    
    float WithdrawAmt(float amount)
    {
    	if(amount> balance)
    	{
    		System.out.println("You don't have enough balance");
    	}
    	else
    	{
    		balance = balance - amount;
    		System.out.println("Withdrawal successful");
    		
    	}
    	return balance;
    }
    
    void updateAddress(String add)
    {
    	address = add;
    	System.out.println("Update successful");
    }
    
    
}


public class Bank
{
    public static void main(String args[])
    {
    	String a,d;
    	int b;
    	float c;
    	bank_account customer;
    	Scanner scan = new Scanner(System.in);
    	
    	System.out.println("Enter your Name:");
    	a = scan.nextLine();
    	System.out.println("Enter your Address:");
    	d = scan.nextLine();
    	System.out.println("Enter your Age:");
    	b = scan.nextInt();
    	
    	customer = new bank_account(a,d,b,0,(float) 7.54);
    	
    	do
    	{
    		System.out.println("Enter:\n\t<1> to Know Account info\n\t<2> to Get Interest Amount"
    				+ "\n\t<3> to Deposit\n\t<4> to Withdraw\n\t<5> to update Address\n\t<0> to exit");
    		b = scan.nextInt();
    		switch(b)
    		{
    			case 1:	customer.print_details();
    					break;
    			case 2:	System.out.println("You will receive: Rs"+customer.GetInterest()+" as interest");
						break;
    			case 3:	System.out.println("Enter Deposit Amount:");
    					c = scan.nextFloat();
    					System.out.println("Your new balance: Rs "+customer.DepositAmt(c));
						break;
    			case 4:	System.out.println("Enter Withdrawal Amount:");
						c = scan.nextFloat();
						System.out.println("Your new balance: Rs "+customer.WithdrawAmt(c));
						break;
    			case 5:	System.out.println("Enter your new Address:");
    	    			d = scan.nextLine();
    	    			customer.updateAddress(d);
						break;
    			case 0: break;
    		}
    	}while(b!=0);
    	
    	
    }
}
