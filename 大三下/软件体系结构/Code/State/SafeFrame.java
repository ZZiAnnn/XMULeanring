import java.awt.Frame; 
import java.awt.Label; 
import java.awt.Color; 
import java.awt.Button; 
import java.awt.TextField; 
import java.awt.TextArea; 
import java.awt.Panel; 
import java.awt.BorderLayout; 
import java.awt.event.ActionListener; 
import java.awt.event.ActionEvent; 
 
public class SafeFrame extends Frame implements ActionListener, Context { 
    private TextField textClock = new TextField(60);	// 输出现在时间 
    private TextArea textScreen = new TextArea(10, 60);	// 输出保安中心 
    private Button buttonUse = new Button("使用金库");	// 使用金库的按键 
    private Button buttonAlarm = new Button("警铃");	// 警铃的按键 
    private Button buttonPhone = new Button("一般通话");	// 一般通话的按键 
    private Button buttonExit = new Button("结束");		// 结束的按键 
 
    private State state = null; //= NightState.getInstance();		// 现在状态 
 
    // 构造子 
    public SafeFrame(String title) { 
        super(title); 
        setBackground(Color.lightGray); 
        setLayout(new BorderLayout()); 
        // 输出textClock 
        add(textClock, BorderLayout.NORTH); 
        textClock.setEditable(false); 
        // 输出textScreen 
        add(textScreen, BorderLayout.CENTER); 
        textScreen.setEditable(false); 
        // 把按键放到面板上 
        Panel panel = new Panel(); 
        panel.add(buttonUse); 
        panel.add(buttonAlarm); 
        panel.add(buttonPhone); 
        panel.add(buttonExit); 
        // 输出面板 
        add(panel, BorderLayout.SOUTH); 
        // 输出到画面上 
        pack(); 
        show(); 
        // 设定命令监听者 
        buttonUse.addActionListener(this); 
        buttonAlarm.addActionListener(this); 
        buttonPhone.addActionListener(this); 
        buttonExit.addActionListener(this); 
    } 
    // 若有人按下按键，则跳到这里 
    public void actionPerformed(ActionEvent e) { 
        System.out.println("" + e); 
        if (e.getSource() == buttonUse) {           // 使用金库的按键 
            state.doUse(this); 
        } else if (e.getSource() == buttonAlarm) {  // 警铃的按键 
            state.doAlarm(this); 
        } else if (e.getSource() == buttonPhone) {  // 一般通话的按键 
            state.doPhone(this); 
        } else if (e.getSource() == buttonExit) {   // 结束的按键 
            System.exit(0); 
        } else { 
            System.out.println("?"); 
        } 
    } 
    // 设定时间 
    public void setClock(int hour) { 
        String clockstring = "现在时间是"; 
        if (hour < 10) { 
            clockstring += "0" + hour + ":00"; 
        } else { 
            clockstring += hour + ":00"; 
        } 
        System.out.println(clockstring); 
        textClock.setText(clockstring); 
        state.doClock(this, hour); 
    } 
    // 状态变化 
    public void changeState(State state) { 
        System.out.println("状态已经從" + this.state + "变成" + state + "。"); 
        this.state = state; 
    } 
    // 呼叫保安中心 
    public void callSecurityCenter(String msg) { 
        textScreen.append("call! " + msg + "\n"); 
    } 
    // 保安中心保留记录 
    public void recordLog(String msg) { 
        textScreen.append("record ... " + msg + "\n"); 
    } 
}

