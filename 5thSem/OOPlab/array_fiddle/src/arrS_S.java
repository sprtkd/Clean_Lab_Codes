import java.util.Scanner;

public class arrS_S {
	public static void main(String args[])
	{
		int arr[], arr_size;
		Scanner scan = new Scanner(System.in);
		System.out.print("Enter the size of your array: ");
		arr_size = scan.nextInt();
		
		arr = new int[arr_size];
		
		for(int i=0; i < arr.length; i++)
		{
			System.out.print("Enter element " + (i+1) + " :");
			arr[i] = scan.nextInt();
		}
		
		System.out.println("Your array is: ");
		
		for(int i=0; i < arr.length; i++)
		{
			System.out.print(arr[i] + " ");
		}
		
		bubbleSort(arr);
		
		System.out.println("\nYour sorted array is: ");
		
		for(int i=0; i < arr.length; i++)
		{
			System.out.print(arr[i] + " ");
		}
		
		
	}
	
	
	public static void bubbleSort(int arr[])
	{
		int temp;
		
		for(int i=0; i < arr.length - 1; i++)
			for(int j=0; j < arr.length - i - 1; j++)
				if(arr[j] > arr[j+1])
				{
					temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
	}

}
