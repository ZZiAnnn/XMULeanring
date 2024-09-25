package cn.xmu.edu.gumballstate;

import javafx.event.ActionEvent;
import javafx.scene.control.*;

public class GumballController {
    public TextArea textArea;
    public Button insertQuarterButton;
    public Button ejectQuarterButton;
    public Button turnCrankButton;
    public Button dispenseButton;
    public Button refillButton;
    public Button exitButton;
    public Label textLabel;

    private GumballMachine gumballMachine;

    public void initialize() {
        gumballMachine = new GumballMachine(10);
        showLabel();
    }

    public void insertQuarterButtonPressed(ActionEvent actionEvent) {
        //textArea.appendText(gumballMachine.insertQuarter());
        textArea.appendText("2");
    }

    public void ejectQuarterButtonPressed(ActionEvent actionEvent) {
        //textArea.appendText(gumballMachine.ejectQuarter());
        textArea.appendText("1");
    }

    public void turnCrankButtonPressed(ActionEvent actionEvent) {
        //textArea.appendText(gumballMachine.turnCrank());
        textArea.appendText("2");
        showLabel();
    }

//    public void dispenseButtonPressed(ActionEvent actionEvent) {
//
//    }
//
//    public void refillButtonPressed(ActionEvent actionEvent) {
//        TextInputDialog dialog = new TextInputDialog();
//        dialog.setTitle("补充糖果机");
//        dialog.setHeaderText("请输入补充的糖果的个数:");
//        dialog.setContentText("糖果个数:");
//
//        dialog.showAndWait().ifPresent(input -> {
//            try {
//                int numGumballs = Integer.parseInt(input);
//                if (numGumballs > 0) {
//                    textArea.appendText(gumballMachine.refill(numGumballs));
//                    showLabel();
//                } else {
//                    Alert alert = new Alert(Alert.AlertType.ERROR);
//                    alert.setTitle("Error");
//                    alert.setHeaderText(null);
//                    alert.setContentText("Please enter a number greater than 0.");
//                    alert.showAndWait();
//                }
//            } catch (NumberFormatException e) {
//                Alert alert = new Alert(Alert.AlertType.ERROR);
//                alert.setTitle("Error");
//                alert.setHeaderText(null);
//                alert.setContentText("Invalid input. Please enter a valid number.");
//                alert.showAndWait();
//            }
//        });
//    }
//
//    public void exitButtonPressed(ActionEvent actionEvent) {
//        System.exit(0);
//    }

    public void showLabel() {
        textLabel.setText("当前糖果数量为：" + gumballMachine.getCount());
    }
}