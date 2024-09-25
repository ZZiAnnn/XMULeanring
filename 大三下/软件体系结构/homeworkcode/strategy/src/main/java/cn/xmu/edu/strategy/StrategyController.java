package cn.xmu.edu.strategy;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.layout.*;

import java.lang.reflect.InvocationTargetException;

public class StrategyController {
    public TextArea textArea;
    public TextArea resultArea;
    public Button confirmButton;
    public Button resetButton;
    public TextField player1TextField;
    public TextField player2TextField;
    public ComboBox player1ComboBox;
    public ComboBox player2ComboBox;
    @FXML
    private VBox rootVBox;

    @FXML
    public void initialize() {
        Image backgroundImage = new Image(getClass().getResource("/img.png")
                .toExternalForm());
        BackgroundImage background = new BackgroundImage(backgroundImage,
                BackgroundRepeat.NO_REPEAT,
                BackgroundRepeat.NO_REPEAT,
                BackgroundPosition.CENTER,
                BackgroundSize.DEFAULT);
        rootVBox.setBackground(new Background(background));
        player1ComboBox.getItems().addAll("ProbStrategy", "WinningStrategy");
        player2ComboBox.getItems().addAll("ProbStrategy", "WinningStrategy");

    }

    @FXML
    protected void confirm() throws ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        if(player1TextField.getText().isEmpty() || player2TextField.getText().isEmpty() || player1ComboBox.getSelectionModel().isEmpty() || player2ComboBox.getSelectionModel().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText(null);
            alert.setContentText("Please input username and strategy");
            alert.showAndWait();
        }
        else {
            long seed1 = System.currentTimeMillis();
            long seed2 = System.currentTimeMillis() + 271828;
            Strategy strategy1 = (Strategy) Class.forName("cn.xmu.edu.strategy." + player1ComboBox.getValue())
                    .getConstructor(long.class)
                    .newInstance(seed1);

            Strategy strategy2 = (Strategy) Class.forName("cn.xmu.edu.strategy." + player2ComboBox.getValue())
                    .getConstructor(long.class)
                    .newInstance(seed2);

            Player player1 = new Player(player1TextField.getText(), strategy1);
            Player player2 = new Player(player2TextField.getText(), strategy2);

            textArea.clear();
            resultArea.clear();
            for(int i = 0; i < 100; ++i) {
                Hand nextHand1 = player1.nextHand();
                Hand nextHand2 = player2.nextHand();
                if (nextHand1.isStrongerThan(nextHand2)) {
                    textArea.appendText("Winner:" + player1 + "\n");
                    player1.win();
                    player2.lose();
                } else if (nextHand2.isStrongerThan(nextHand1)) {
                    textArea.appendText("Winner:" + player2 + "\n");
                    player1.lose();
                    player2.win();
                } else {
                    textArea.appendText("Even..." + "\n");
                    player1.even();
                    player2.even();
                }
            }

            resultArea.appendText("Total result:\n");
            resultArea.appendText(player1 + "\n");
            resultArea.appendText(player2 + "\n");
        }
    }

    @FXML
    protected void reset() {
        player1TextField.clear();
        player2TextField.clear();
        textArea.clear();
        resultArea.clear();
        player1ComboBox.getSelectionModel().clearSelection();
        player2ComboBox.getSelectionModel().clearSelection();
    }
}
