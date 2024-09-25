public class RepTempRuleTwo extends RepTempRule{
  public void replace() throws Exception{
    newString=oldString.replaceFirst("aaa", "ccc");
    System.out.println("this is replace Two:");
  }
}