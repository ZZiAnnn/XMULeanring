package Adaptor;

public class Main {
    public static void main(String[] args) {
        English englishPerson = new EnglishPerson();
        Chinese chinesePerson = new ChinesePerson();
        Adaptor adaptor = new Adaptor(englishPerson, chinesePerson);

        System.out.println("翻译之前：");
        chinesePerson.speakChinese("你好吗？");
        englishPerson.speakEnglish("I'm fine\n");

        System.out.println("翻译之后：");
        adaptor.speakEnglish("你好，你好吗？");
        adaptor.speakChinese("Hello,I'm fine");
    }
}