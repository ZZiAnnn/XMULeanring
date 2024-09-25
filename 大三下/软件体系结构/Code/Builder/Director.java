public class Director {
    private Builder builder;
    public Director(Builder builder) {   // �Ȱ�Builder�������ʵ���� 
        this.builder = builder;          // ������builder����
    }
    public Object construct() {                   // �����ļ�
        builder.makeTitle("Greeting");            // ����
        builder.makeString("�����ϵ�����Y��");      // �ִ�
        builder.makeItems(new String[]{           // ��Ŀ
            "�簲��",
            "�簲��",
        });
        builder.makeString("��������");              // ��һ���ִ�
        builder.makeItems(new String[]{             // ��һ����Ŀ
            "����",
            "ף���и����Ρ�",
            "�ټ���",
        });
        return builder.getResult();                 // ��ɵ��ļ����Ƿ���ֵ
    }
}

