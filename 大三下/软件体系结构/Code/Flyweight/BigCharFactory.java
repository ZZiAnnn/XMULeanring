import java.util.Hashtable;

public class BigCharFactory {
    // �������е�BigChar�Ķ���ʵ��
    private Hashtable pool = new Hashtable();
    // Singleton Pattern
    private static BigCharFactory singleton = new BigCharFactory();
    // �����ӣ�Ϊ��ҪPrivate��
    private BigCharFactory() {
    	
    }
    // ȡ��Ψһ�Ķ���ʵ��
    public static BigCharFactory getInstance() {
        return singleton;
    }
    // ����������BigChar�Ķ���ʵ��
    public synchronized BigChar getBigChar(char charname) {
        BigChar bc = (BigChar)pool.get("" + charname);
        if (bc == null) {//���û������ַ����򴴽������Ҵ˶������
        	                //������һ��
            bc = new BigChar(charname); 	// �ڴ˲���BigChar�Ķ���ʵ��
            pool.put("" + charname, bc);
        }
        return bc;
    }
}

