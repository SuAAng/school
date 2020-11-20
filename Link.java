class Link extends Thread {

	public static int state = 0;//현재 무슨 상태인지, 0은 버스 비었음. 1은 버스 참.
	public static int time = 0;//현재 시간
	public static int real_receiver = -1;//지금 전송을 받고 있는 노드
	public static int real_sender = -1;//지금 전송중인 노드
	
	
	private int name = 0;
	private String log;
	
	public static Write write = new Write();
	
	Link() {

	}// 생성자


	public void run() {		
		//시간 시작 로그 출력		
		log = "Link Start //00 min 00 sec 000 msec";//링크 시작 log 출력
		write.Time(time, name, log);
		log = "System Clock Start //00 min 00 sec 000 msec";//System Clock 시작 log 출력
		write.Time(time, name, log);
		
		while (true) {
			//시간 올려줌
			try {
				Thread.sleep(1);
				
				if(time%1000 == 0) {//1초마다 .출력
					System.out.print(".");
				}
				
				time++;
				
			} catch (InterruptedException e) {
					System.err.println("error ");
			}

			//전송 수락하고 전송 완료 시간이 되었을 때 로그 출력과 출력에 사용된 변수 초기화
			if(time == (Node.start_time) + 5) {
				log = "Node" + real_sender + " Data Send Finished To Node" + real_receiver;//finish 로그 출력
				write.Time(time, name, log);
				real_sender = 0;
				real_receiver = 0;
				state = 0;
			}
			
			// 한 시점에서 하나의 노드만 요청
			if (Node.request == 1) {
				log = "Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//링크가 요청 받았다는 로그 출력
				write.Time(Node.send_request_time, name, log);
				
				// accept의 경우
				if (state == 0) {
					log = "Accept: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//accept했다는 로그 출력
					write.Time(Node.send_request_time, name, log);
					
				
					real_sender = Node.sender;//현재 데이터를 전송하려는 노드번호(이름)
					real_receiver = Node.request_receiver[Node.sender];//데이터를 전송 받으려는 노드번호(이름)
					state = 1;//버스 사용중
				} 
				// reject의 경우
				else {
					log = "Reject: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[Node.sender];//reject했다는 로그 출력
					write.Time(Node.send_request_time, name, log);
				}
			} 
			
			
			
			// 한 시점에 2개 이상의 노드가 동시에 요청
			else if (Node.request >= 2) {
				//아무도 bus를 사용하지 않을 때 노드 하나만 accept 나머지 노드는 reject
				if (state == 0) {	
					for (int i = 1; i < 5; i++) {
						//request_receiver 배열이 0이 아니면 요청한 노드를 뜻함.
						if (Node.request_receiver[i] != 0) {
							log = "Node" + (i) + " Data Send Request To Node" + Node.request_receiver[i];//요청 로그 출력
							write.Time(Node.send_request_time, name, log);
						}
						
						//요청허락되었을 때
						if (i == (Node.sender)) {
							log = "Accept: Node" + Node.sender + " Data Send Request To Node" + Node.request_receiver[i];
							write.Time(Node.send_request_time, name, log);
							
	
							real_sender = Node.sender;
							real_receiver = Node.request_receiver[Node.sender];
							state = 1;
						
						} 
						//요청거절되었을 때
						else if (i != Node.sender) {
							log = "Reject: Node" + i + " Data Send Request To Node" + Node.request_receiver[i];
							write.Time(Node.send_request_time, name, log);
			
						}
					}
				} 
				
				//bus가 사용되고 있을 때 요청한 노드 전부 거절 
				else if (state == 1) {
					for (int i = 1; i < 5; i++) {
						
						//요청한 노드들 전부 거절
						if (Node.request_receiver[i] != 0) {
							log = "Node" + i + " Data Send Request To Node" + Node.request_receiver[i];//request 로그 출력
							write.Time(Node.send_request_time, name, log);
							log = "Reject: Node" + i + " Data Send Request To Node" + Node.request_receiver[i];//reject 로그 출력
							write.Time(Node.send_request_time, name, log);
						}
					}
				}

			}
			

			// 시간 체크
			if (time > 59999 && state == 0) {//1분에 들어온 request까지 받고 출력 종료
				break;//while문 벗어남
			}
		
		}
		log = "System Clock Finished";//종료 로그 출력
		write.Time(time, name, log);
		log = "Link Finished";
		write.Time(time, name, log);
		System.out.println("완료\nLog의 작성이 완료되었습니다. txt파일을 확인해주세요.");
	}
}
