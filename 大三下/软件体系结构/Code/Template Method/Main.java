public class Main {
    public static void main(String[] args) {
	// ����1����'H'��CharDisplay�Ķ���ʵ����
        AbstractDisplay d1 = new CharDisplay('H');
	// ����1����"Hello, world."��StringDisplay�Ķ���ʵ����
        AbstractDisplay d2 = new StringDisplay("Hello, world.");
	// ����1����"��á�"��StringDisplay�Ķ���ʵ����
        AbstractDisplay d3 = new StringDisplay("���������̣�");
        d1.display();	// d1,d2,d3����AbstractDisplay������Ķ���ʵ����
			// ��ˣ�
        d2.display();	// ���Ե��ü̳е���display������
        d3.display();	// ʵ�ʶ������ǹ涨����CharDisplay��StringDisplay��
    }
}

