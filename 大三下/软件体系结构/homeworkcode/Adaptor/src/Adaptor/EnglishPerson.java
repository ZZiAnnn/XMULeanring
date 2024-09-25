package Adaptor;

public class EnglishPerson implements English {
    @Override
    public void speakEnglish(String message) {
        System.out.println("英国人:"+message);
    }
}
