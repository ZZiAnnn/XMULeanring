module com.example.gumball {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.kordamp.bootstrapfx.core;

    opens cn.xmu.edu.gumball to javafx.fxml;
    exports cn.xmu.edu.gumball;
}