class Link extends Thread {

	public static int state = 0;//���� ���� ��������, 0�� ���� �����. 1�� ���� ��.
	public static int time = 0;//���� �ð�
	public static int real_receiver = -1;//���� ������ �ް� �ִ� ���
	public static int real_sender = -1;//���� �������� ���
	
	
	private int name = 0;
	private String log;
	
	public static Write write = new Write();
	
	Link() {

	}// ������


	public void run() {		
		//�ð� ���� �α� ���		
		log = "Link Start //00 min 00 sec 000 msec";//��ũ ���� log ���
		write.Time(time, name, log);
		log = "System Clock Start //00 min 00 sec 000 msec";//System Clock ���� log ���
		write.Time(time, name, log);
		
		while (true) {
			//�ð� �÷���
			try {
				Thread.sleep(1);
				
				if(time%1000 == 0) {//1�ʸ��� .���
					System.out.print(".");
				}
				
				time++;
				
			} catch (InterruptedException e) {
					System.err.println("error ");
			}

			//���� �����ϰ� ���� �Ϸ� �ð��� �Ǿ��� �� �α� ��°� ��¿� ���� ���� �ʱ�ȭ
			if(time == (Node.start_time) + 5) {
				log = "Node" + real_sender + " Data Send Finished To Node" + real_receiver;//finish �α� ���
				write.Time(time, name, log);
				real_sender = 0;
				real_receiver = 0;
				state = 0;
			}
			
			// �� �������� �ϳ��� ��常 ��û
			if (Node.request == 1) {
				log = "Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//��ũ�� ��û �޾Ҵٴ� �α� ���
				write.Time(Node.send_request_time, name, log);
				
				// accept�� ���
				if (state == 0) {
					log = "Accept: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//accept�ߴٴ� �α� ���
					write.Time(Node.send_request_time, name, log);
					
				
					real_sender = Node.sender;//���� �����͸� �����Ϸ��� ����ȣ(�̸�)
					real_receiver = Node.request_receiver[Node.sender];//�����͸� ���� �������� ����ȣ(�̸�)
					state = 1;//���� �����
				} 
				// reject�� ���
				else {
					log = "Reject: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//reject�ߴٴ� �α� ���
					write.Time(Node.send_request_time, name, log);
				}
			} 
			
			
			
			// �� ������ 2�� �̻��� ��尡 ���ÿ� ��û
			else if (Node.request >= 2) {
				//�ƹ��� bus�� ������� ���� �� ��� �ϳ��� accept ������ ���� reject
				if (state == 0) {	
					for (int i = 1; i < 5; i++) {
						//request_receiver �迭�� 0�� �ƴϸ� ��û�� ��带 ����.
						if (Node.request_receiver[i] != 0) {
							log = "Node" + (i) + " Data Send Request To Node" + Node.request_receiver[i];//��û �α� ���
							write.Time(Node.send_request_time, name, log);
						}
						
						//��û����Ǿ��� ��
						if (i == (Node.sender)) {
							log = "Accept: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[i];
							write.Time(Node.send_request_time, name, log);
							
	
							real_sender = Node.sender;
							real_receiver = Node.request_receiver[Node.sender];
							state = 1;
						
						} 
						//��û�����Ǿ��� ��
						else if (i != Node.sender) {
							log = "Reject: Node" + i + " Data Send Request To Node" + Node.request_receiver[i];
							write.Time(Node.send_request_time, name, log);
			
						}
					}
				} 
				
				//bus�� ���ǰ� ���� �� ��û�� ��� ���� ���� 
				else if (state == 1) {
					for (int i = 1; i < 5; i++) {
						
						//��û�� ���� ���� ����
						if (Node.request_receiver[i] != 0) {
							log = "Node" + i + " Data Send Request To Node" + Node.request_receiver[i];//request �α� ���
							write.Time(Node.send_request_time, name, log);
							log = "Reject: Node" + i + " Data Send Request To Node" + Node.request_receiver[i];//reject �α� ���
							write.Time(Node.send_request_time, name, log);
						}
					}
				}

			}
			

			// �ð� üũ
			if (time > 59999 && state == 0) {//1�п� ���� request���� �ް� ��� ����
				break;//while�� ���
			}
		
		}
		log = "System Clock Finished";//���� �α� ���
		write.Time(time, name, log);
		log = "Link Finished";
		write.Time(time, name, log);
		System.out.println("�Ϸ�\nLog�� �ۼ��� �Ϸ�Ǿ����ϴ�. txt������ Ȯ�����ּ���.");
	}
}
