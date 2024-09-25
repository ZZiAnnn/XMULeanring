public class RepTempRuleOne extends RepTempRule{
  public void replace() throws Exception{
    //replaceFirst是jdk1.4新特性
    newString=oldString.replaceFirst("aaa", "bbbb");
    System.out.println("this is replace one:");
  }
}