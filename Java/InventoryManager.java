import java.text.DecimalFormat;
import java.util.ArrayList;

public class InventoryManager {
	private ArrayList<Item> inventory;
	DecimalFormat format = new DecimalFormat("0.00G");
	// CWE-582: Array Declared Public, Final, and Static
	// if categories was only declared final or static then it could still be
	// modified
	private String[] categories = { "Potion", "Reagent", "Solvent", "Mineral", "Misc" };

	// CWE-486: Public data assigned to private array-typed field
	/*
	 * public void setCategories(String[] newCategories) { categories = new
	 * String[newCategories.length];
	 * System.arraycopy(newCategories,0,categories,0,newCategories.length); }
	 * 
	 * We do not want to give public access to categories so we give the access
	 * modifier of private. If we provide a public method to modify the category
	 * then we might as well make the array public which is not what we want
	 */

	// CWE-495: Private Data Structure Returned from a public method
	/*
	 * public void getCategories() { return categories; } we do not want to send a
	 * reference to the private data member instead we make a copy and send that
	 */
	public String[] getCategories() {
		String[] copyCategories = new String[categories.length];
		for (int i = 0; i < categories.length; i++) {
			copyCategories[i] = categories[i];
		}
		return copyCategories;
	}

	public InventoryManager() {
		inventory = new ArrayList<Item>();
		addItem(2, 1, "BlueMountainFlower", 2, 40);
		addItem(2, 2, "TapRoot", 15, 5);
		addItem(2, 3, "SaberCatTooth", 30, 2);
		addItem(2, 4, "BlisterWart", 10, 12);
		addItem(2, 5, "BoneMeal", 2, 30);

		addItem(3, 6, "TreeSap", 35, 2);
		addItem(3, 7, "Spirits", 10, 3);
		addItem(3, 8, "Wine", 20, 5);

	}

	public void addItem(int category, int itemID, String itemDesc, double itemCost, int quantity) {
		switch (category) {
			case 1:
				inventory.add(new Potion(itemID, itemDesc, itemCost, quantity));
				break;
			case 2:
				inventory.add(new Reagent(itemID, itemDesc, itemCost, quantity));
				break;
			case 3:
				inventory.add(new Solvent(itemID, itemDesc, itemCost, quantity));
				break;
			case 4:
				inventory.add(new Mineral(itemID, itemDesc, itemCost, quantity));
				break;
			case 5:
				inventory.add(new Item(itemID, itemDesc, itemCost, quantity));
				break;
		}
	}

	public void removeItem(int itemID, int amount) {
		for (int i = 0; i < inventory.size(); i++) {
			// CWE-395:Use of NullPointerException Catch to Detect Null Pointer Dereference
			/*
			 * instead of using a try and catching nullPointerException, we are first going
			 * to check if it is null and remove it
			 */
			if (inventory.get(i) == null) {
				inventory.remove(i);
			} else {
				if (inventory.get(i).getItemID() == itemID) {
					// CWE-481: Assigning instead of comparing
					// if(amount = inventory.get(i).getQuantity())
					// we need to ensure we are using comparative operators
					// = is technically syntactically correct and will not
					// show an error
					if (amount == inventory.get(i).getQuantity()) {
						inventory.remove(i);
					} else {
						inventory.get(i).setQuantity(inventory.get(i).getQuantity() - amount);
					}
					break;
				}
			}
		}
	}

	public void updateRetail(int itemID, double retail) {
		for (int i = 0; i < inventory.size(); i++) {
			// CWE-476: NULL Pointer Dereference
			// if the item is null then it will get check first and we will not
			// experience an exception when accessing the itemID
			if (inventory.get(i) != null && inventory.get(i).getItemID() == itemID) {
				if (retail < inventory.get(i).getItemCost()) {
					System.out.println("Cannot go below item cost");
				} else {
					inventory.get(i).setItemRetail(retail);
				}
				break;
			}
		}
	}

	public void printInventory() {
		for (Item item : inventory) {
			// CWE-395:Use of NullPointerException Catch to Detect Null Pointer Dereference
			/*
			 * instead of using a try and catching nullPointerException, we are first going
			 * to check if it is null and remove it
			 */
			if (item == null) {
				inventory.remove(item);
			} else {
				if (item instanceof Reagent) {
					System.out.println("Reagent - ");
				} else if (item instanceof Potion) {
					System.out.println("Potion - ");
				} else if (item instanceof Solvent) {
					System.out.println("Solvent - ");
				} else if (item instanceof Mineral) {
					System.out.println("Mineral - ");
				} else {
					System.out.println("Misc - ");
				}

				System.out.println("\tItem ID: " + item.getItemID() + "\n\tItem Desc: " + item.getItemDesc()
						+ "\n\tItem Cost: " + format.format(item.getItemCost()) + "\n\tItem Retail: "
						+ format.format(item.getItemRetail()) + "\n\tQuantity: " + item.getQuantity());
				System.out.println();
			}
		}

	}

	public void printTotalCostAndProfit() {
		double totalCost = 0;
		double totalRetail = 0;
		for (Item item : inventory) {
			totalCost += (item.getItemCost() * item.getQuantity());
			totalRetail += (item.getItemRetail() * item.getQuantity());
		}
		System.out.println("Total Inventory Cost: " + format.format(totalCost));
		System.out.println("Total Inventory Retail: " + format.format(totalRetail));
		System.out.println("Total Expected Profit: " + format.format(totalRetail - totalCost));
		System.out.println();

	}

	public int getIndex(int id) {
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory.get(i).getItemID() == id) {
				return i;
			}
		}
		return -1;
	}

	public boolean inInventory(int id) {
		for (int i = 0; i < inventory.size(); i++) {
			if (id == inventory.get(i).getItemID()) {
				return true;
			}
		}
		return false;
	}

	public void addNewPotion(int id, String desc, double cost) {
		addItem(1, id, desc, cost, 3);
		inventory.get(getIndex(id)).setItemRetail(cost * 2);
	}

	public double startPotions(int one, int two, int three) {
		PotionHandler potionHandler = new PotionHandler();
		if (potionHandler.makePotion(one, two, three)) {
			return potionHandler.potionCost / 3;
		} else {
			return 0;
		}
	}

	private class PotionHandler {
		private Item ingredientOne;
		private Item ingredientTwo;
		private Item ingredientThree;
		private double potionCost;

		public PotionHandler() {

		}

		public boolean makePotion(int one, int two, int three) {

			Item[] ingredients = { inventory.get(getIndex(one)), inventory.get(getIndex(two)),
					inventory.get(getIndex(three)) };
			boolean hasSolvent = false;
			boolean hasReagent = false;
			for (int i = 0; i < ingredients.length; i++) {
				if (ingredients[i] instanceof Solvent && hasSolvent == false) {
					hasSolvent = true;
				}

				if (ingredients[i] instanceof Reagent && hasReagent == false) {
					hasReagent = true;
				}
			}
			if (hasSolvent && hasReagent) {
				removeItem(inventory.get(getIndex(one)).getItemID(), 1);
				removeItem(inventory.get(getIndex(two)).getItemID(), 1);
				removeItem(inventory.get(getIndex(three)).getItemID(), 1);
				potionCost = ingredients[0].getItemCost() + ingredients[1].getItemCost() + ingredients[2].getItemCost();
				System.out.println("Potion Successful!");
				return true;

			} else {
				System.out.println("Potion is not possible. Must contain at least one solvent and one reagent.");
				return false;
			}
		}
	}
}