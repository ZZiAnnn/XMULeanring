public class Singleton {
    private static Singleton singleton;
    private Singleton() {
    	singleton = new Singleton();
    }

    public static Singleton getInstance() {
      //if (singleton==null) {
    	//  singleton = new Singleton();
      //}
    	return singleton;
    }
}

