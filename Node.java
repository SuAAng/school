import java.lang.Math;

class Node extends Thread {
	
	//������ ��尡 ���� ����ϴ� ����
	private int name;// ����ȣ
	private int count = 0;//reject Ƚ��
	private int request_time = 0;//�ٽ� ��û ���� �ð�
	private int[] add_request_time;//��û ������ ���� ���ϴ� �ð�
	private int[] dest_node;//���� ������ �̸� ���س��� �迭
	private int index = 0;//send�� receive�� �����ϱ� ���� ���
	private String log;//�α� ����

	//Link���� Node�� ��û�� ���� �ߴ���, ���� ���������� �����ϱ����� ����ϴ� ����
	public static int[] request_receiver = new int[5];//���ۿ�û ���� ����ȣ�� �����, ex)request_receiver[2] = 3 Node2�� Node3 ���� ���ۿ�û��
	public static int sender;//��û �� ��� ��ȣ, ���ÿ� ��û���� �� ���⿡ ����� ��尡 ��û��.
	public static int request = 0;//� ������ ��û�� �ϸ� +1
	public static int real_sender = 0;//���� �����ϴ� ��� ��ȣ
	public static int real_receiver = 0;//���� ���۹޴� ��� ��ȣ
	public static int start_time = -100;//���� ���� �ð�.
	public static int send_request_time = 0;//���� ��û�� ���� �ð�
	
	Node() {

	}// ������
	
	Node(int name){
		this.name = name;// ����ȣ
		
		add_request_time = new int[100];//������ ���� ��û �ð� 100�� �̸� �����س���.
		dest_node = new int[100];//������ ���� ��� 100�� �̸� �����س���.
		
		for (int i = 0; i < 100; i++) {
			add_request_time[i] = (int)(Math.random() * 20000 + 2);
			int dest_node_num = (int)((Math.random() * 3 ) + 1 ); 
			if(dest_node_num == name) {//�ڱ� �ڽ��� receiver�� �����Ǵ� ���
				dest_node_num = name * 3 % 4 + 1;//�ٸ� ���� ����
			}
			dest_node[i] = dest_node_num;
		}
	}
	
	//���� ���� ������ �� �ð� �����ִ� �Լ�
	public int BackoffTimer(int transNum) {
		int rndom;
		int temp;
		temp = Math.min(transNum, 10);
		rndom = (int) (Math.random() * (Math.pow(2, temp) - 1) +1);

		return rndom;
	}
	
	//dest�� ��尡 ������ ���� ��û
	//dest�� ���� ��û ���� ����ȣ
	public void request_work(int dest) {
		request++;//��û���� ǥ��(link���� Ȯ��)
		request_receiver[name] = dest;//���ۿ�û ���� ����ȣ�� �����, request_receiver[1]���� Node1�� ���ۿ�û�� ��� ��ȣ�� �����
		sender = name;//���� ��û�� ��� ��ȣ �����.
		log = "Node" + name + " Data Send Request To Node"+ dest;//��û �α� ���
		send_request_time = Link.time;
		Link.write.Time(send_request_time,name,log);
	}	
	
	//��ũ�κ��� ��û ���� ����
	//dest�� ���� ��û ���� ����ȣ
	public void request_accept(int dest) {
		real_receiver = dest;//������ ���۹��� ��� ����
		real_sender = name;//������ ������ ��� ����
		start_time = send_request_time;//������ ���� ���� �ð��� ����
		request_time = start_time + 5 + add_request_time[index];//���� ��û �ð��� ����
		index++;//���� �ð��� ������ ���� ��带 �޾ƿ� �迭�� index�� 1 �÷���
		count = 0;//�浹 0���� �ʱ�ȭ
		request = 0;//��û öȸ
		
		log = "Node"+ name + " Data Send Request Accept from Link";//accept ���� log ���
		Link.write.Time(start_time,name,log);
		
		
	}
	
	//��ũ�κ��� ��û ��������
	public void request_reject() {
		request = 0;//��û öȸ

	
		int transNum = (count %16) + 1;
		int wait_time = BackoffTimer(transNum);//�󸶳� ��ٸ��� wait time ����. �浹�� 16ȸ���� ����
		request_time = send_request_time + wait_time; //��û ���� ���� + wait_time, �ٽ� ��û�ϴ� �ð��� ����
		
		log = "Node" + name + " Data Send Request Reject from Link";//��û���� log ���
		Link.write.Time(send_request_time,name,log);	
		log = "Exponential Back-off Time: " + wait_time + " msec";//time �� �޾Ҵ��� log ���
		Link.write.Time(send_request_time,name,log);
	}
	
	//receive node�� ������
	public void data_receive() {		
		
		//��û�� �ϱ����� ��ٸ��� ��� ���� ��ٸ��� �ð��� ���� �Ϸ� �� �ð� �� �� �� �ð��� ��ٸ��� �ð����� ����
			if(request_time < (start_time+5)) {
				request_time = (start_time+5);
			}
		
		
		log = "Node" + name + " Data Receive Start from Node"+ real_sender;//receive ���� log ���
		Link.write.Time(start_time,name,log);
	}
		
	public void run() {
		
		//ù ��û �ð� ��������.
		if(request_time == 0) {
			request_time = add_request_time[index];
		}
		
		log = "Node" + name + " Start //00 min 00 sec 000 msec";//���� �α� ���
		Link.write.Time(Link.time, name, log);

		while(true) {
			//�ð� �÷���	
			try {
				Thread.sleep(1);
			} 
			catch (InterruptedException e) {
						System.err.println("error");
			}
			
			
			//�����ð��� �Ǹ� ���� log ���
			if(Link.time == start_time+5) {
				//������ ��忡�� ������ ���� �����ߴٴ� log ���
				if(name == real_sender) {
					log = "Node" + real_sender + " Data Send Finished To Node" + real_receiver;
					Link.write.Time(start_time+5, real_sender, log);
				}
				
				//���� �޴� ��忡�� ������ �ޱ� �����ߴٴ� log ���
				if(name == real_receiver) {
				log = "Node" + real_receiver + " Data Receive Finished from Node"+ real_sender;
				Link.write.Time(start_time+5,real_receiver,log);	
				}
				
				//Link���� ���� �ϷḦ �ϸ� Node�� ���� �ʱ�ȭ
				if(Link.real_sender == 0) {
					request_receiver[real_sender] = 0;//��û ���� ������ ��Ÿ��.
					
					if(request_receiver[real_sender] == 0) {
					real_receiver = 0;//���� �Ϸ��Ͽ� ���۹޴� ��� ������ ��Ÿ��
					real_sender = 0;//���� �Ϸ��Ͽ� �����ϴ� ��� ������ ��Ÿ��
					}
				}
				
			}
			
			//�ڱⰡ ���� ���۹޴� ���� �����Ǹ� 
			if(real_receiver == name) {
				if(start_time == Link.time) {
				data_receive();
				}
			}
			
			//�ڱⰡ ���� ���۹޴� ��尡 �ƴϸ�
			else if(real_receiver != name) {
				//Link���� ���� ��û��.
				if(Link.time == request_time) {
					request_work(dest_node[index]);//��û�ϱ�
					
					//��û ����� ��� (bus�� ����ְ� sender�� �ڱ��ڽ��� ���)
					if(Link.state == 0 && sender == name) {
						request_accept(dest_node[index]);	
						
						
						
					}
					//��û ������ ��� (bus������̰ų� sender�� �ڱ��ڽ��� �ƴ� ���)
					else if(Link.state == 1 || sender != name) {
						request_reject();
						count++;//�浹 1ȸ ����
					}
				}
			}
			
			//1�п� ���� request���� �ް� ��� ����
			if (Link.time > 59999 && Link.state == 0) {
				break;//while�� ���
			}

		}
		
		//���� �α� ���
		log = "Node" + name + " Finished";
		Link.write.Time(Link.time, name, log);	
	}
}
