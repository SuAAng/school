import java.lang.Math;

class Node extends Thread {
	
	//각각의 노드가 따로 사용하는 변수
	private int name;// 노드번호
	private int count = 0;//reject 횟수
	private int request_time = 0;//다시 요청 보낼 시간
	private int[] add_request_time;//요청 보내기 위해 더하는 시간
	private int[] dest_node;//어디로 보낼지 미리 정해놓은 배열
	private int index = 0;//send와 receive에 접근하기 위해 사용
	private String log;//로그 내용

	//Link에서 Node가 요청을 누가 했는지, 어디로 보낼건지를 공유하기위해 사용하는 변수
	public static int[] request_receiver = new int[5];//전송요청 받은 노드번호가 저장됨, ex)request_receiver[2] = 3 Node2가 Node3 으로 전송요청함
	public static int sender;//요청 들어간 노드 번호, 동시에 요청했을 때 여기에 저장된 노드가 요청됨.
	public static int request = 0;//어떤 노드든지 요청을 하면 +1
	public static int real_sender = 0;//현재 전송하는 노드 번호
	public static int real_receiver = 0;//현재 전송받는 노드 번호
	public static int start_time = -100;//전송 시작 시간.
	public static int send_request_time = 0;//전송 요청을 보낸 시간
	
	Node() {

	}// 생성자
	
	Node(int name){
		this.name = name;// 노드번호
		
		add_request_time = new int[100];//더해질 전송 요청 시간 100개 미리 저장해놓음.
		dest_node = new int[100];//데이터 받을 노드 100개 미리 저장해놓음.
		
		for (int i = 0; i < 100; i++) {
			add_request_time[i] = (int)(Math.random() * 20000 + 2);
			int dest_node_num = (int)((Math.random() * 3 ) + 1 ); 
			if(dest_node_num == name) {//자기 자신이 receiver로 지정되는 경우
				dest_node_num = name * 3 % 4 + 1;//다른 노드로 설정
			}
			dest_node[i] = dest_node_num;
		}
	}
	
	//전송 거절 당했을 때 시간 돌려주는 함수
	public int BackoffTimer(int transNum) {
		int rndom;
		int temp;
		temp = Math.min(transNum, 10);
		rndom = (int) (Math.random() * (Math.pow(2, temp) - 1) +1);

		return rndom;
	}
	
	//dest로 노드가 데이터 전송 요청
	//dest는 전송 요청 받은 노드번호
	public void request_work(int dest) {
		request++;//요청함을 표시(link에서 확인)
		request_receiver[name] = dest;//전송요청 받은 노드번호가 저장됨, request_receiver[1]에는 Node1이 전송요청한 노드 번호가 저장됨
		sender = name;//전송 요청한 노드 번호 저장됨.
		log = "Node" + name + " Data Send Request To Node"+ dest;//요청 로그 출력
		send_request_time = Link.time;
		Link.write.Time(send_request_time,name,log);
	}	
	
	//링크로부터 요청 승인 받음
	//dest는 전송 요청 받은 노드번호
	public void request_accept(int dest) {
		real_receiver = dest;//데이터 전송받은 노드 저장
		real_sender = name;//데이터 전송할 노드 저장
		start_time = send_request_time;//데이터 전송 시작 시간을 저장
		request_time = start_time + 5 + add_request_time[index];//다음 요청 시간을 저장
		index++;//전송 시간과 데이터 받을 노드를 받아올 배열의 index를 1 올려줌
		count = 0;//충돌 0으로 초기화
		request = 0;//요청 철회
		
		log = "Node"+ name + " Data Send Request Accept from Link";//accept 받음 log 출력
		Link.write.Time(start_time,name,log);
		
		
	}
	
	//링크로부터 요청 거절당함
	public void request_reject() {
		request = 0;//요청 철회

	
		int transNum = (count %16) + 1;
		int wait_time = BackoffTimer(transNum);//얼마나 기다릴지 wait time 받음. 충돌은 16회까지 센다
		request_time = send_request_time + wait_time; //요청 거절 시점 + wait_time, 다시 요청하는 시간을 저장
		
		log = "Node" + name + " Data Send Request Reject from Link";//요청거절 log 출력
		Link.write.Time(send_request_time,name,log);	
		log = "Exponential Back-off Time: " + wait_time + " msec";//time 얼마 받았는지 log 출력
		Link.write.Time(send_request_time,name,log);
	}
	
	//receive node로 선정됨
	public void data_receive() {		
		
		//요청을 하기위해 기다리는 경우 원래 기다리던 시간과 전송 완료 후 시간 중 더 긴 시간을 기다리는 시간으로 저장
			if(request_time < (start_time+5)) {
				request_time = (start_time+5);
			}
		
		
		log = "Node" + name + " Data Receive Start from Node"+ real_sender;//receive 시작 log 출력
		Link.write.Time(start_time,name,log);
	}
		
	public void run() {
		
		//첫 요청 시간 지정해줌.
		if(request_time == 0) {
			request_time = add_request_time[index];
		}
		
		log = "Node" + name + " Start //00 min 00 sec 000 msec";//시작 로그 출력
		Link.write.Time(Link.time, name, log);

		while(true) {
			//시간 올려줌	
			try {
				Thread.sleep(1);
			} 
			catch (InterruptedException e) {
						System.err.println("error");
			}
			
			
			//성공시간이 되면 성공 log 출력
			if(Link.time == start_time+5) {
				//전송한 노드에게 데이터 전송 성공했다는 log 출력
				if(name == real_sender) {
					log = "Node" + real_sender + " Data Send Finished To Node" + real_receiver;
					Link.write.Time(start_time+5, real_sender, log);
				}
				
				//전송 받는 노드에게 데이터 받기 성공했다는 log 출력
				if(name == real_receiver) {
				log = "Node" + real_receiver + " Data Receive Finished from Node"+ real_sender;
				Link.write.Time(start_time+5,real_receiver,log);	
				}
				
				//Link에서 전송 완료를 하면 Node의 변수 초기화
				if(Link.real_sender == 0) {
					request_receiver[real_sender] = 0;//요청 받지 않음을 나타냄.
					
					if(request_receiver[real_sender] == 0) {
					real_receiver = 0;//전송 완료하여 전송받는 노드 없음을 나타냄
					real_sender = 0;//전송 완료하여 전송하는 노드 없음을 나타냄
					}
				}
				
			}
			
			//자기가 현재 전송받는 노드로 선정되면 
			if(real_receiver == name) {
				if(start_time == Link.time) {
				data_receive();
				}
			}
			
			//자기가 현재 전송받는 노드가 아니면
			else if(real_receiver != name) {
				//Link에게 전송 요청함.
				if(Link.time == request_time) {
					request_work(dest_node[index]);//요청하기
					
					//요청 허락한 경우 (bus가 비어있고 sender가 자기자신인 경우)
					if(Link.state == 0 && sender == name) {
						request_accept(dest_node[index]);	
						
						
						
					}
					//요청 거절한 경우 (bus사용중이거나 sender가 자기자신이 아닌 경우)
					else if(Link.state == 1 || sender != name) {
						request_reject();
						count++;//충돌 1회 더함
					}
				}
			}
			
			//1분에 들어온 request까지 받고 출력 종료
			if (Link.time > 59999 && Link.state == 0) {
				break;//while문 벗어남
			}

		}
		
		//종료 로그 출력
		log = "Node" + name + " Finished";
		Link.write.Time(Link.time, name, log);	
	}
}
