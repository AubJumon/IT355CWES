import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;
import java.util.regex.*;

//CWE-489: Active Debug Code - All debug code has been removed
//CWE-563: Assignment to Variable without Use - All variables assigned are used 
//CWE-510: Trapdoor - No trapdoors within program 

public class FileHandler {

    //CWE-862: Missing Authorization - Makes sure that user is only able to read files in inputted directory
    public void readFile(String userInput, String dir) throws IOException {
        
        // Validate user input to ensure it does not contain any path traversal characters (CWE-23)
        if (userInput.contains("../") || userInput.contains("/..")) {
            throw new IllegalArgumentException("Invalid input");
        }

        // Normalize the user input to remove any path traversal sequences (CWE-24, CWE-25, CWE-26)
        Path inputPath = Paths.get(userInput).normalize();

        // Build the absolute path to the file
        Path filePath = Paths.get(dir, inputPath.toString()).normalize();
        File file = filePath.toFile();
        

        // Ensure the file is located within the uploads directory (CWE-23, CWE-24, CWE-25, CWE-26)
        if (!file.toPath().startsWith(dir)) {
            throw new IllegalArgumentException("Invalid input");
        }

         
        // Process the file contents
        try(BufferedReader br = new BufferedReader(new FileReader(file))) 
        {
            
            // Mitigating CWE-230: Initialize variables with default or placeholder values
            String name = "";
            String email = "";
            String phoneNumber = "";
            String inputString = "";
            int salary;
            //CWE-681: Incorrect Conversion between Numeric Types- Using Integer.parseInt() ensures that the conversion from string to int produces the expected results
            int numPeople = Integer.parseInt(br.readLine());
            Person[] people = new Person[numPeople];


            //Fill People Array
            for(int i = 0; i < numPeople; i++)
            {
                inputString = br.readLine();
                // Mitigating CWE-229: Check for null or empty values and handle appropriately
                if (!inputString.isEmpty()) 
                {
                    name = inputString;
                }
                else
                {
                    name = null;
                }
                inputString = br.readLine();
                if (!inputString.isEmpty()) 
                {
                    email = inputString;
                }
                else
                {
                    email = null;
                }
                inputString = br.readLine();
                if (!inputString.isEmpty()) 
                {
                    phoneNumber = inputString;
                }
                else
                {
                    phoneNumber = null;
                }
                inputString = br.readLine();
                if (!inputString.isEmpty()) 
                {
                    //CWE-681: Incorrect Conversion between Numeric Types- Using Integer.parseInt() ensures that the conversion from string to int produces the expected results
                    salary =  Integer.parseInt(inputString);
                }
                else
                {
                    salary = -1;
                }
                people[i] = new Person(name, email, phoneNumber, salary);
                br.readLine();
            }
            selectMenu(people);
        
        } 
        catch (IOException ex) {
            ex.printStackTrace();
        }
        
    }


   
    public void getPerson(Person[] people, int index)
    {
        String regex = "[a-zA-Z]";
        Pattern pattern = Pattern.compile(regex);
        String emailRegex = "^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$";
        Pattern emailPattern = Pattern.compile(emailRegex);
        
        //CWE -129: Improper Validation of Array Index 
        if(index > people.length || index < 0)
        {
            
            System.out.println("Invalid Index");
            return; 
        }
        
        // CWE-232: Check for undefined values and handle appropriately
        if(people[index].name == null)
        {
            System.out.println("Missing name");
        }
        else
        {
            System.out.println(people[index].name);
        }
        if(people[index].email == null)
        {
            System.out.println("Missing email");
        }
        else
        {
            // Mitigating CWE-231: Check for unexpected or extra values and handle appropriately
            Matcher matcher = emailPattern.matcher(people[index].email);
            if(matcher.matches())
            {
                System.out.println(people[index].email);
            }
            else
            {
                System.out.println("Email is invalid");
            }
           
        }
        if(people[index].phoneNumber == null)
        {
            System.out.println("Missing phone number");
        }
        else
        {
            // Mitigating CWE-231: Check for unexpected or extra values and handle appropriately
            Matcher matcher = pattern.matcher(people[index].phoneNumber);
            if(matcher.find() == true || people[index].phoneNumber.length() > 10 || people[index].phoneNumber.length() < 10)
            {
             System.out.println("Phone number is invalid");
            }
            else
            {
                System.out.println(people[index].phoneNumber);
            }
        }
        if(people[index].salary == -1)
        {
            System.out.println("Salary is invalid");
        }
        else
        {
            System.out.println(people[index].salary);
        }
        System.out.println(" ");
    }

    public int avgSalary(Person[] people)
    {
        int numPeople = people.length;
        int average = 0;
        //CWE-369: Divide By Zero 
        //Prevents dvivide by zero error by checking length of the array
        if(numPeople == 0)
        {
            average = -1;
        }
        else
        {
            for(int i = 0; i < people.length; i++)
            {
                average += people[i].salary;
            }
            average = average / numPeople;
        }
        return average;
    }

    public void selectMenu(Person[] people)
    {
        Scanner scanner = new Scanner(System.in);
        int input = 1;
        while(input != 0)
        {
            System.out.println("0 to exit");
            System.out.println("1 to view array data");
            System.out.println("2 to get average salary");
            System.out.println("3 to find duplicates");
            System.out.println("Enter Input: ");
            
            input = scanner.nextInt();
            System.out.println(" ");
            try
            {
                switch(input)
                {
                    case 0:
                        break;
                    case 1:
                        System.out.println("Enter index you wish to view");
                        System.out.println("Enter Input: ");
                        try
                        {
                            int index = scanner.nextInt();
                            System.out.println(" ");
                            getPerson(people, index);
                        }
                        catch(Exception e)
                        {
                            System.out.println("Invalid Input");
                        }
                        break;
                    case 2:
                        int average = avgSalary(people);
                        //CWE-252: Unchecked Return Value - Checks if the return value is greater than 0
                        if(average > 0)
                        {
                            System.out.println("Average salary is: "+average);
                        }
                        else
                        {
                            System.out.println("One or more salaries are missing or incorrect");
                        }
                        
                        break;
                    case 3:
                        findDuplicate(people);
                        break;
                }
            }
            catch(Exception e)
            {
                System.out.println("Invalid Input");
                scanner.next();
            }
            
        }
        scanner.close();
    }


    public void findDuplicate(Person[] people)
    {
        int numDuplicates = 0;
       
        for(int i = 0; i < people.length-1; i++)
        {
           for(int j = 1; j < people.length; j++)
           {
                //CWE-697: Incorrect Comparison
                if(people[i].equals(people[j]))
                {
                    numDuplicates++;
                }
           }
        }
        System.out.println("Number of objects that match is: "+numDuplicates);
       
    }

    class Person
    {
        public String name;
        public String email;
        public String phoneNumber;
        public int salary;

        Person(String name, String email, String phoneNumber, int salary)
        {
            this.name = name;
            this.email = email;
            this.phoneNumber = phoneNumber;
            this.salary = salary;
        }

    }
    
}
