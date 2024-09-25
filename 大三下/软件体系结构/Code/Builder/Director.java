public class Director {
    private Builder builder;
    public Director(Builder builder) {   // 先把Builder的子类的实例， 
        this.builder = builder;          // 储存在builder属性
    }
    public Object construct() {                   // 建立文件
        builder.makeTitle("Greeting");            // 标题
        builder.makeString("从早上到白天結束");      // 字串
        builder.makeItems(new String[]{           // 项目
            "早安。",
            "午安。",
        });
        builder.makeString("到了晚上");              // 另一个字串
        builder.makeItems(new String[]{             // 另一个项目
            "晚安。",
            "祝你有个好梦。",
            "再见。",
        });
        return builder.getResult();                 // 完成的文件就是返回值
    }
}

