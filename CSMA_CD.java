public class CSMA_CD {
	public static void main(String[] args) {

		System.out.println("<��� ����: 4��, ���� ������ ũ��: 5msec>\n");
		System.out.println("��ø� ��ٸ��ʽÿ�. ������ ����� �Ϸ�Ǹ� �Ϸ� ���ڸ� ����մϴ�...");
		for(int i = 0; i<60; i++) {
			System.out.print(".");
		}
		System.out.println("");
		Node[] node = new Node[5];// ��� ����
		
		Link link = new Link();
		
		for (int j = 1; j < 5; j++) {// ��� �ϳ� �� ������ �ϳ��� �������
			node[j] = new Node(j); // ���
		}

		for (int i = 1; i < 5; i++) {// ������ ���� ����
			node[i].start();
		}
		
		link.start();

	}
}