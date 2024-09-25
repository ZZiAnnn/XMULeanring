package Adaptor;

public class Adaptor implements Chinese,English {
    private English englishPerson;
    private Chinese chinesePerson;

    public Adaptor(English englishPerson, Chinese chinesePerson) {
        this.englishPerson = englishPerson;
        this.chinesePerson = chinesePerson;
    }
    @Override
    public void speakEnglish(String message) {
        // 中文转换成英语
        //这里简单地假设直接返回翻译后的句子
        this.chinesePerson.speakChinese("how are you");
    }
    @Override
    public void speakChinese(String message) {
        // 英文转换成中文
        //这里简单地假设直接返回翻译后的句子
        this.englishPerson.speakEnglish("我很好");
    }

}
