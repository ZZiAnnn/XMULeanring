public class PrintBanner extends Banner implements Print{
    public PrintBanner(String string) {
        super(string); //this 
    }
    public void printWeak() {
        showWithParen();
    }
    public void printStrong() {
        showWithAster();
    }
}
