public abstract class RepTempRule{
  protected String oldString="";
  RepTempRule(String oldString){
  	  this.oldString=oldString; 
  	}
  /*public void setOldString(String oldString){
    this.oldString=oldString; 
  }*/
  protected String newString="";
  public String getNewString(){
    return newString;
  }
  public abstract void replace() throws Exception;
}
