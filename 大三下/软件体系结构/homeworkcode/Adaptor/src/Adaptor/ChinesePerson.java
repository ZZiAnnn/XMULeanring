package Adaptor;

public class ChinesePerson implements Chinese{
    @Override
    public void speakChinese(String message) {
        System.out.println("中国人:"+message);
    }
}
