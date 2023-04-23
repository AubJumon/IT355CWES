public class Item {
	private int itemID;
	private String itemDesc;
	// CWE-493: Critical Public Variable Without Final Modifier
	// if we do not declare itemCost to be final then it can be
	// modified from an outside class
	private final double itemCost;
	// CWE-495 Critical Public Variable Without Final Modifier
	/*
	 * we want all of our items to have a 30% markup so we cannot allow this number
	 * to change. We use the static final modifier to ensure that.
	 */
	private static final double MARK_UP = .35;
	private double itemRetail;
	private int quantity;

	public Item(int id, String desc, double cost, int qty) {
		this.itemID = id;
		this.itemDesc = desc;
		this.itemCost = cost;
		this.itemRetail = cost + (cost * MARK_UP);
		this.quantity = qty;
	}

	public int getItemID() {
		return itemID;
	}

	public String getItemDesc() {
		return itemDesc;
	}

	public double getItemCost() {
		// CWE-197: Numeric Truncation Error
		// return (int)itemCost;
		// do not cast to a lower space if information
		// is necessary
		return itemCost;

	}

	public double getItemRetail() {
		return itemRetail;
	}

	public void setItemRetail(double retail) {
		this.itemRetail = retail;
	}

	public int getQuantity() {
		return quantity;
	}

	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
}

class Reagent extends Item {
	private String reagentType;

	public Reagent(int id, String desc, double cost, int qty) {
		super(id, desc, cost, qty);
	}
}

class Potion extends Item {
	private String potionType;

	public Potion(int id, String desc, double cost, int qty) {
		super(id, desc, cost, qty);
	}
}

class Mineral extends Item {
	private String mineralType;

	public Mineral(int id, String desc, double cost, int qty) {
		super(id, desc, cost, qty);
	}
}

class Solvent extends Item {
	private String solventType;

	public Solvent(int id, String desc, double cost, int qty) {
		super(id, desc, cost, qty);
	}
}
