import java.util.*;




public class HelloWorld {
    public static void main(String arg[])
    {
        String username;
        Scanner input = new Scanner(System.in);
        System.out.println("Please enter your name:");
        username = input.nextLine();
        System.out.println("Hello "+ username + "!");
        
    }
}
