import java.io.IOException;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        FileHandler fileHandler = new FileHandler();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter path of directory (I.E. C:/folder1/folder2/..):");
        String dir = scanner.nextLine();
        System.out.println("Enter file name:");
        String fileName = scanner.nextLine();
        try {
            fileHandler.readFile(fileName, dir);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            System.out.println("Invalid input: " + e.getMessage());
        }
        scanner.close();
    }
}
