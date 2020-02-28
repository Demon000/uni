package domain;

public class Product extends BaseEntity<String> {
    private final float price;

    public Product(String name, float price) {
        super(name);
        this.price = price;
    }

    public String getName() {
        return getId();
    }

    public float getPrice() {
        return price;
    }
}
