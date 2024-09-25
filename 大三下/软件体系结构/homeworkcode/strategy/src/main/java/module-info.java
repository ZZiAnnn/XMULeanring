module com.example.strategy {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.kordamp.bootstrapfx.core;

    opens cn.xmu.edu.strategy to javafx.fxml;
    exports cn.xmu.edu.strategy;
}