import java.util.Scanner;

public class Main {

    public static void swap(int a, int b){

        a = a - b;
        b = a + b;
        a = b - a;

    }

	public static void main(String[] args){
    
    Scanner sc = new Scanner(System.in); //used to retrive user input
    int a,b;

    System.out.print("a = "); a = sc.nextInt();
    System.out.print("b = "); b = sc.nextInt();

    System.out.println("a = " + a + " b = " + b + "\nSWAP");
    swap(a,b);
    System.out.println("a = " + a + " b = " + b);
        
    }
}
