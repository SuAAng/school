public class CSMA_CD {
	public static void main(String[] args) {

		System.out.println("<노드 개수: 4개, 전송 데이터 크기: 5msec>\n");
		System.out.println("잠시만 기다리십시오. 데이터 출력이 완료되면 완료 문자를 출력합니다...");
		for(int i = 0; i<60; i++) {
			System.out.print(".");
		}
		System.out.println("");
		Node[] node = new Node[5];// 노드 개수
		
		Link link = new Link();
		
		for (int j = 1; j < 5; j++) {// 노드 하나 당 스레드 하나씩 만들어줌
			node[j] = new Node(j); // 노드
		}

		for (int i = 1; i < 5; i++) {// 스레드 동시 시작
			node[i].start();
		}
		
		link.start();

	}
}