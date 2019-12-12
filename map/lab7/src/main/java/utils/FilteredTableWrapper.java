package utils;

import domain.BaseEntity;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;

import java.util.ArrayList;
import java.util.List;

public class FilteredTableWrapper<E extends BaseEntity<String>> {
    private final TableView<E> table;
    private final TextField field;

    public FilteredTableWrapper(TableView<E> table, TextField field) {
        this.table = table;
        this.field = field;
    }

    public E getSelected() {
        return table.getSelectionModel().getSelectedItem();
    }

    public void setSelected(E newSelected) {
        table.getItems().forEach(element -> {
            if (element.getId().equals(newSelected.getId())) {
                table.getSelectionModel().select(element);
            }
        });
    }

    public void setTableData(List<E> elements) {
        E lastSelected = getSelected();

        String input = field.getText();
        List<E> filtered = new ArrayList<>();
        for (E e : elements) {
            if (e.matches(input)) {
                filtered.add(e);
            }
        }

        table.getItems().setAll(filtered);

        if (lastSelected == null) {
            return;
        }

        setSelected(lastSelected);
    }
}
