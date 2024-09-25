import java.util.Hashtable;

public class BigCharFactory {
    // 管理现有的BigChar的对象实例
    private Hashtable pool = new Hashtable();
    // Singleton Pattern
    private static BigCharFactory singleton = new BigCharFactory();
    // 构造子，为何要Private？
    private BigCharFactory() {
    	
    }
    // 取得唯一的对象实例
    public static BigCharFactory getInstance() {
        return singleton;
    }
    // 产生（共享）BigChar的对象实例
    public synchronized BigChar getBigChar(char charname) {
        BigChar bc = (BigChar)pool.get("" + charname);
        if (bc == null) {//如果没有这个字符，则创建对象并且此对象仅仅
        	                //被创建一次
            bc = new BigChar(charname); 	// 在此产生BigChar的对象实例
            pool.put("" + charname, bc);
        }
        return bc;
    }
}

