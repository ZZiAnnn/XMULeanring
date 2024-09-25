module cn.xmu.edu.composite {
    requires javafx.controls;
    requires javafx.fxml;
            
                            
    opens cn.xmu.edu.composite to javafx.fxml;
    exports cn.xmu.edu.composite;
}