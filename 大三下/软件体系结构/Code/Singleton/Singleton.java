public class Singleton {
    //private static Singleton singleton;
	//private Singleton() {
	  //  	singleton = new Singleton();
	private static Singleton singleton = new Singleton();
    private Singleton() {
        System.out.println("已产生对象实例。");
    }
    public static Singleton getInstance() {
    //    if (singleton==null) {
    //	  singleton = new Singleton();}
    	return singleton;
    }
}

