//����program node��ȥ��program����ʣ�����command list node��
//����command list node���� command list nodeȥ����
// <program> ::= program <command list>
public class ProgramNode extends Node {
    private Node commandListNode;
    public void parse(Context context) throws ParseException {
        context.skipToken("program");// context ����֮����
        commandListNode = new CommandListNode();
        commandListNode.parse(context);
    }
    public String toString() {
        return "[program " + commandListNode + "]";
    }
}
