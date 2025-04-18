import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;

public class ColleagueCheckbox extends Checkbox implements ItemListener, Colleague {
    private Mediator mediator;
    public ColleagueCheckbox(String caption, CheckboxGroup group, boolean state) {  // 构造子
        super(caption, group, state);
    }
    public void setMediator(Mediator mediator) {            // 保留Mediator
        this.mediator = mediator;
    }
    public void setColleagueEnabled(boolean enabled) {      // Mediator指示有效／无效
        setEnabled(enabled);
    }
    public void itemStateChanged(ItemEvent e) {             // 若状态有变
        mediator.colleagueChanged(this);
    }
}

