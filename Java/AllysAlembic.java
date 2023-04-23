import java.util.Scanner;

public class AllysAlembic {

	static InventoryManager inventoryManager = new InventoryManager();
	static Scanner scanner = new Scanner(System.in);

	public static void main(String[] args) {
		boolean quit = false;
		int menuItem;

		do {
			System.out.println("=========================INVENTORY=======================");
			System.out.println("=========================================================");
			System.out.println("Ally's Alembic - For your Potions and Potion Accessories!");
			System.out.println("=========================================================");
			System.out.println("1. Add Item");
			System.out.println("2. Remove Item");
			System.out.println("3. Update Item Retail Price");
			System.out.println("4. Print Inventory");
			System.out.println("5. Print Total Cost and Expected Profit");
			System.out.println("6. Attempt to create a potion");
			System.out.println("0. Quit");
			System.out.print("Choose menu item: ");

			try {
				menuItem = Integer.parseInt(scanner.next());
				// CWE - 396 Declaration of Catch for Generic Exception
				/*
				 * }catch(Exception e) e.getMessage(); } We want to use the exception below
				 * because it is more specific and we know exactly what happened based on the
				 * system output
				 */
			} catch (NumberFormatException e) { // CWE-248: Uncaught Exception
				System.out.println("Invalid input!");
				// CWE - 382 BadPractices: Use of System.Exit()
				// System.exit(1);
				menuItem = -1;
			}

			switch (menuItem) {
				case 0:
					System.out.println("Goodbye!");
					quit = true;
					break;
				case 1:
					System.out.print("\nPlease enter the item ID: ");
					String itemID = scanner.next();
					while (!itemID.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the item ID: ");
						itemID = scanner.next();
					}
					int itemIDint = Integer.parseInt(itemID);
					System.out.println("Select the category: ");
					int category = displayCategory(inventoryManager.getCategories());
					scanner.nextLine();
					System.out.print("Please enter the item description: ");
					String itemDesc = scanner.nextLine();
					System.out.print("Please enter the item cost: ");
					String itemCost = scanner.next();
					while (!itemCost.matches("[0-9]+.[0-9]+") && !itemCost.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the item cost: ");
						itemCost = scanner.next();
					}
					double itemCostDouble = Double.parseDouble(itemCost);

					System.out.print("Please enter the quantity: ");
					String quantity = scanner.next();
					// CWE-387 Declaration of Throws for Generic Exception
					/*
					 * if quantity is 0 we want to throw an exception throw new Exception();
					 * 
					 * Instead of throwing a generic exception we can throw an arithmeticException
					 * or just validate the user data beforehand to ensure our method precondition
					 * is met
					 * 
					 * in this case we instead use a regex to ensure proper input
					 */
					while (!quantity.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the quantity: ");
						quantity = scanner.next();
					}
					int quantityInt = Integer.parseInt(quantity);

					inventoryManager.addItem(category, itemIDint, itemDesc, itemCostDouble, quantityInt); // CWE-484:
					// Omitted break
					// statement in
					// Switch
					scanner.nextLine();
					break;
				case 2:
					System.out.print("Please enter the item ID: ");
					itemID = scanner.next();
					while (!itemID.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the item ID: ");
						itemID = scanner.next();
					}
					int itemIDInt = Integer.parseInt(itemID);
					System.out.print("Please enter the quantity to remove: ");
					String amount = scanner.next();
					while (!amount.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the quantity to remove: ");
						amount = scanner.next();
					}
					int amountInt = Integer.parseInt(amount);
					inventoryManager.removeItem(itemIDInt, amountInt); // CWE-484: Omitted break statement in Switch
					System.out.println();
					break;
				case 3:
					System.out.print("Please enter the item ID: ");
					itemID = scanner.next();
					while (!itemID.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the item ID: ");
						itemID = scanner.next();
					}
					itemIDInt = Integer.parseInt(itemID);

					System.out.println("Please enter the new retail cost: ");
					String retail = scanner.next();
					while (!retail.matches("[0-9]+.[0-9]") && !retail.matches("[0-9]+")) {
						System.out.println("Invalid");
						System.out.print("Please enter the new retail cost: ");
						retail = scanner.next();
					}
					double retailDouble = Double.parseDouble(retail);
					// CWE-767: Access to Critical Private Variable via public method
					// ***inventoryManager.inventory.get(itemID).setRetail(retail);***
					// we do not want someone to be able to change the retail price directly, we
					// need to ensure
					// that the new price is not below the cost
					inventoryManager.updateRetail(itemIDInt, retailDouble);

				case 4:
					System.out.println();
					inventoryManager.printInventory(); // CWE-484: Omitted break statement in Switch
					break;
				case 5:
					System.out.println();
					inventoryManager.printTotalCostAndProfit(); // CWE-484: Omitted break statement in Switch
					break;
				case 6:
					addPotionOptions();
					break;
				default:
					System.out.println("Invalid menu item!");
					System.out.println();
					break;
			}

		} while (!quit);
	}

	public static void addPotionOptions() {
		System.out.println("Please enter the first ingredient ID: ");
		String itemID = scanner.next();
		while (!itemID.matches("[0-9]+") || !inventoryManager.inInventory(Integer.parseInt(itemID))) {
			System.out.println("Invalid");
			System.out.print("Please enter the item ID: ");
			itemID = scanner.next();
		}
		int ingredientOne = Integer.parseInt(itemID);

		System.out.println("Please enter the second ingredient ID: ");
		itemID = scanner.next();
		while (!itemID.matches("[0-9]+") || !inventoryManager.inInventory(Integer.parseInt(itemID))) {
			System.out.println("Invalid");
			System.out.print("Please enter the item ID: ");
			itemID = scanner.next();
		}
		int ingredientTwo = Integer.parseInt(itemID);

		System.out.println("Please enter the third ingredient ID: ");
		itemID = scanner.next();
		while (!itemID.matches("[0-9]+") || !inventoryManager.inInventory(Integer.parseInt(itemID))) {
			System.out.println("Invalid");
			System.out.print("Please enter the item ID: ");
			itemID = scanner.next();
		}
		int ingredientThree = Integer.parseInt(itemID);

		double potionCost = (inventoryManager.startPotions(ingredientOne, ingredientTwo, ingredientThree));
		if (potionCost > 0) {
			addPotionPrompt(potionCost);
		} else {

		}

	}

	public static void addPotionPrompt(double potionCost) {
		System.out.print("\nPlease enter the item ID: ");
		String itemID = scanner.next();
		while (!itemID.matches("[0-9]+")) {
			System.out.println("Invalid");
			System.out.print("Please enter the item ID: ");
			itemID = scanner.next();
		}
		int itemIDint = Integer.parseInt(itemID);
		scanner.nextLine();
		System.out.print("Please enter the item description: ");
		String itemDesc = scanner.nextLine();

		inventoryManager.addNewPotion(itemIDint, itemDesc, potionCost);

	}

	public static int displayCategory(String[] categories) {
		for (int i = 0; i < categories.length; i++) {
			System.out.print("\t" + (i + 1) + ".) " + categories[i] + "\n");
		}
		// CWE-252: Unchecked Return Value
		/*
		 * System.out.print("Enter selection: "); return scanner.nextInt();
		 *
		 * if we do not check the user input before sending it then we could have
		 * problems for the calling method
		 */
		System.out.print("Enter selection: ");
		String choice = scanner.next();
		while (!choice.matches("[1-5]")) {
			System.out.println("Invalid");
			System.out.print("Enter selection: ");
			choice = scanner.next();
		}
		return Integer.parseInt(choice);

	}
}
