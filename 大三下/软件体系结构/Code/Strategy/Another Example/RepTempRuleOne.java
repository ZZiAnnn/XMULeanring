public class RepTempRuleOne extends RepTempRule{
  public void replace() throws Exception{
    //replaceFirst��jdk1.4������
    newString=oldString.replaceFirst("aaa", "bbbb");
    System.out.println("this is replace one:");
  }
}