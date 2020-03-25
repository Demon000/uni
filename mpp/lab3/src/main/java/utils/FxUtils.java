package utils;

import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.MouseEvent;

import java.util.concurrent.Callable;
import java.util.function.Predicate;

public class FxUtils {
    public static Alert createErrorAlert(String message) {
        Alert alert = new Alert(AlertType.ERROR, message, ButtonType.OK);
        alert.setContentText(message);
        return alert;
    }

    public static void showErrorAlert(String message) {
        Alert alert = createErrorAlert(message);
        alert.showAndWait();
    }

    public static void addFieldNumber(TextField field) {
        field.textProperty().addListener((obs, oldValue, newValue) -> {
            String cleanValue = newValue.replaceAll("[^\\d]", "");
            field.setText(cleanValue);
        });
    }

    public static <E> void addTableDeselect(TableView<E> table) {
        table.setRowFactory(tableView -> {
            final TableRow<E> row = new TableRow<>();

            row.addEventFilter(MouseEvent.MOUSE_PRESSED, event -> {
                final int index = row.getIndex();
                if (index >= 0 && index < table.getItems().size() && table.getSelectionModel().isSelected(index)  ) {
                    table.getSelectionModel().clearSelection();
                    event.consume();
                }
            });

            return row;
        });
    }

    public static <E> void addTableUnselectable(TableView<E> table) {
        table.setRowFactory(tableView -> {
            final TableRow<E> row = new TableRow<>();

            row.addEventFilter(MouseEvent.MOUSE_PRESSED, event -> {
                table.getSelectionModel().clearSelection();
                event.consume();
            });

            return row;
        });
    }
}
