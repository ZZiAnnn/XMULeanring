package idcard;
import framework.*;

public class IDCard extends Product {
    private String owner;
    IDCard(String owner) {
        System.out.println("����" + owner + "�Ŀ���");
        this.owner = owner;
    }
    public void use () {
        System.out.println("ʹ��" + owner + "�Ŀ���");
    }
    public String getOwner() {
        return owner;
    }
}

