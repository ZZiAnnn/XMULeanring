module cn.xmu.edu.gumballstate {
    requires javafx.controls;
    requires javafx.fxml;

    opens cn.xmu.edu.gumballstate to javafx.fxml;
    exports cn.xmu.edu.gumballstate;
}