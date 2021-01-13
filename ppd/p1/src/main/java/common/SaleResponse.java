package common;

import java.io.Serializable;

public class SaleResponse implements Serializable {
    public Sale sale;


    public SaleResponse(Sale sale) {
        this.sale = sale;
    }

    @Override
    public String toString() {
        return "SaleResponse{" +
                "sale=" + sale +
                '}';
    }
}
