class Person implements Cloneable {
    String name;
    int age;
    Address address;  // 引用类型

    public Person(String name, int age, Address address) {
        this.name = name;
        this.age = age;
        this.address = address;
    }

    // 浅克隆
    public Person shallowClone() {
        try {
            return (Person) super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }

    // 深克隆
    public Person deepClone() {
        try {
            Person cloned = (Person) super.clone();
            cloned.address = new Address(address.street); // 创建新的Address实例
            return cloned;
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}

class Address {
    String street;

    public Address(String street) {
        this.street = street;
    }
}

public class Main {
    public static void main(String[] args) {
        Address address = new Address("1234 Park Ave");
        Person original = new Person("John", 30, address);

        System.out.println("Original Address: " + original.address.street);
        // 浅克隆
        Person shallowCloned = original.shallowClone();

        // 深克隆
        Person deepCloned = original.deepClone();
        original.address.street = "5678 Elm St";

        System.out.println("Changed Address: " + original.address.street);
        System.out.println("Shallow Cloned Address: " + shallowCloned.address.street);
        System.out.println("Deep Cloned Address: " + deepCloned.address.street);
    }
}
