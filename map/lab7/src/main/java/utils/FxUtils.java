package utils;

import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.MouseEvent;

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

    public static Alert createConfirmationAlert(String message) {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setContentText(message);
        return alert;
    }

    public static <E> void addTableDeselect(TableView<E> table) {
        table.setRowFactory(tableView2 -> {
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

    public static void addFieldNumber(TextField field) {
        field.textProperty().addListener((obs, oldValue, newValue) -> {
            String cleanValue = newValue.replaceAll("[^\\d]", "");
            field.setText(cleanValue);
        });
    }
}
